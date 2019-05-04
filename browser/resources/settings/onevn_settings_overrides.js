// Copyright (c) 2019 The OneVN Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

// Local Scope
(function() {
// TODO: move to a module
function throttle (callback, maxWaitTime = 30) {
  // Call on first invocation
  let shouldWait = false;
  return function (...args) {
    if (!shouldWait) {
      callback.apply(this, args);
      shouldWait = true;
      setTimeout(function () {
        shouldWait = false;
      }, maxWaitTime);
    }
  }
}

// Utils
function createMenuElement (title, href, iconName) {
  const menuEl = document.createElement('a')
  menuEl.href = href
  menuEl.innerHTML = `
    <iron-icon icon="${iconName}"></iron-icon>
    ${title}
  `
  return menuEl
}

function getMenuElement (templateContent, href) {
  const menuEl = templateContent.querySelector(`a[href="${href}"]`)
  if (!menuEl) {
    console.error(`[OneVN Settings Overrides] Could not find menu item '${href}'`)
  }
  return menuEl
}

function getSectionElement (templateContent, sectionName) {
  const sectionEl = templateContent.querySelector(`template[if="[[showPage_(pageVisibility.${sectionName})]]"]`)
  if (!sectionEl) {
    console.error(`[OneVN Settings Overrides] Could not find section '${sectionName}'`)
  }
  return sectionEl
}

if (!OneVNPatching) {
  console.error('OneVNPatching was not available to onevn_settings_overrides.js')
}

//
// Override, extend or modify existing modules
//

const OneVNClearSettingsMenuHighlightBehavior = {
  ready: function() {
    // Clear menu selection after scrolling away.
    // Chromium's menu is not persistant, so does not have
    // this issue.
    const container = this.$.container
    if (!container) {
      console.error('Could not find #container in settings-ui module')
    }
    const menu = this.$$('settings-menu')
    if (!menu) {
      console.error('Could not find settings-menu in settings-ui module')
    }
    let onScroll
    function stopObservingScroll() {
      if (onScroll) {
        container.removeEventListener('scroll', onScroll)
        onScroll = null
      }
    }
    window.addEventListener('showing-section', ({ detail: section }) => {
      // Currently showing or about to scroll to `section`.
      // If we're getting further away from section top
      // then section is no longer 'selected'.
      // TODO(petemill): If this wasn't a chromium module, we'd simply add a handler
      // for scrolling away, or have the menu change selection as we scroll.
      stopObservingScroll()
      function calcDistance() {
        const sectionScrollTop = section.offsetTop
        const currentScrollTop = container.scrollTop
        return Math.abs(sectionScrollTop - currentScrollTop)
      }
      let distance = calcDistance()
      onScroll = throttle(() => {
        const latestDistance = calcDistance()
        if (latestDistance > distance) {
          menu.setSelectedUrl_('')
          stopObservingScroll()
        } else {
          distance = latestDistance
        }
      }, 100)
      container.addEventListener('scroll', onScroll)
    })
  }
}

// Polymer Component Behavior injection (like superclasses)
OneVNPatching.RegisterPolymerComponentBehaviors({
  'settings-clear-browsing-data-dialog': [
    OneVNClearBrowsingDataOnExitBehavior
  ],
  'settings-reset-profile-dialog': [
    OneVNResetProfileDialogBehavior
  ],
  'settings-ui': [
    OneVNClearSettingsMenuHighlightBehavior
  ]
})

// Templates
OneVNPatching.RegisterPolymerTemplateModifications({
  'settings-ui': (templateContent) => {
    // Take settings menu out of drawer and put permanently in DOM
    // TODO(petemill): If this becomes flakey on chromium rebases, consider
    // making our own settings-ui module template replacement since it's quite simple.
    const settingsMenuTemplate = templateContent.querySelector('#drawerTemplate')
    const container = templateContent.querySelector('#container')
    if (!settingsMenuTemplate || !container) {
      console.warn('[OneVN Settings Overrides] settings-ui: could not find all the required elements for modification', { settingsMenuTemplate, container })
    }
    container.insertAdjacentElement('afterbegin', settingsMenuTemplate.content.querySelector('settings-menu'))
  },
  'settings-menu': (templateContent) => {
    // Add title
    const titleEl = document.createElement('h1')
    titleEl.id = 'settingsHeader'
    titleEl.innerHTML = loadTimeData.getString('settings')
    const topMenuEl = templateContent.querySelector('#topMenu')
    if (!topMenuEl) {
      console.error('[OneVN Settings Overrides] Could not find topMenu element to add title after')
    } else {
      topMenuEl.insertAdjacentElement('afterbegin', titleEl)
    }
    // Advanced text
    const advancedToggle = templateContent.querySelector('#advancedButton span')
    if (!advancedToggle) {
      console.error('[OneVN Settings Overrides] Could not find advancedButton to modify text')
    }
    advancedToggle.innerText = loadTimeData.getString('onevnAdditionalSettingsTitle')
    // Add 'Get Started' item
    const peopleEl = getMenuElement(templateContent, '/people')
    const getStartedEl = createMenuElement(loadTimeData.getString('onevnGetStartedTitle'), '/getStarted', 'onevn_settings:get-started')
    peopleEl.insertAdjacentElement('afterend', getStartedEl)
    // Remove People item
    peopleEl.remove()
    // Add Extensions item
    const extensionEl = createMenuElement(loadTimeData.getString('onevnDefaultExtensions'), '/extensions', 'onevn_settings:extensions')
    getStartedEl.insertAdjacentElement('afterend', extensionEl)
    // Add Sync item
    const syncEl = createMenuElement(loadTimeData.getString('onevnSync'), '/onevnSync', 'onevn_settings:sync')
    extensionEl.insertAdjacentElement('afterend', syncEl)
    // Add Shields item
    const shieldsEl = createMenuElement(loadTimeData.getString('onevnShieldsTitle'), '/shields',  'onevn_settings:shields')
    syncEl.insertAdjacentElement('afterend', shieldsEl)
    // Add Embed Blocking item
    const embedEl = createMenuElement(loadTimeData.getString('socialBlocking'), '/socialBlocking', 'onevn_settings:social-permissions')
    shieldsEl.insertAdjacentElement('afterend', embedEl)
    // Swap search and appearance
    const searchEl = getMenuElement(templateContent, '/search')
    embedEl.insertAdjacentElement('afterend', searchEl)
    // Remove default Browser
    const defaultBrowserEl = getMenuElement(templateContent, '/defaultBrowser')
    defaultBrowserEl.remove()
    // Remove Startup
    const startupEl = getMenuElement(templateContent, '/onStartup')
    startupEl.remove()
    // Remove Accessibility :-(
    const a11yEl = getMenuElement(templateContent, '/accessibility')
    a11yEl.remove()
    // Move autofill to advanced
    const autofillEl = getMenuElement(templateContent, '/autofill')
    const privacyEl = getMenuElement(templateContent, '/privacy')
    privacyEl.insertAdjacentElement('afterend', autofillEl)
    // Remove extensions link
    const extensionsLinkEl = templateContent.querySelector('#extensionsLink')
    if (!extensionsLinkEl) {
      console.error('[OneVN Settings Overrides] Could not find extensionsLinkEl to remove')
    }
    extensionsLinkEl.remove()
    // Add version number to 'about' link
    const aboutEl = templateContent.querySelector('#about-menu')
    if (!aboutEl) {
      console.error('[OneVN Settings Overrides] Could not find about-menun element')
    }
    const aboutTitleContent = aboutEl.innerHTML
    aboutEl.innerHTML = `
      <div class="onevn-about-graphic">
        <iron-icon icon="onevn_settings:full-color-onevn-lion"><iron-icon>
      </div>
      <div class="onevn-about-meta">
        <span class="onevn-about-item onevn-about-menu-link-text">${aboutTitleContent}</span>
        <span class="onevn-about-item onevn-about-menu-version">v ${loadTimeData.getString('onevnProductVersion')}</span>
      </div>
    `
  },
  'settings-basic-page': (templateContent) => {
    // Routes
    const r = settings.router.routes_
    if (!r.BASIC) {
      console.error('[OneVN Settings Overrides] Routes: could not find BASIC page')
    }
    r.GET_STARTED = r.BASIC.createSection('/getStarted', 'getStarted')
    r.SHIELDS = r.BASIC.createSection('/shields', 'shields')
    r.SOCIAL_BLOCKING = r.BASIC.createSection('/socialBlocking', 'socialBlocking')
    r.EXTENSIONS = r.BASIC.createSection('/extensions', 'extensions')
    r.ONEVN_SYNC = r.BASIC.createSection('/onevnSync', 'onevnSync')
    if (!r.SITE_SETTINGS) {
      console.error('[OneVN Settings Overrides] Routes: could not find SITE_SETTINGS page')
    }
    r.SITE_SETTINGS_AUTOPLAY = r.SITE_SETTINGS.createChild('autoplay')
    // Autofill route is moved to advanced,
    // otherwise its sections won't show up when opened.
    if (!r.AUTOFILL || !r.ADVANCED) {
      console.error('[OneVN Settings Overrides] Could not move autofill route to advanced route', r)
    } else {
      r.AUTOFILL.parent = r.ADVANCED
    }
    // Add 'Getting Started' section
    // Entire content is wrapped in another conditional template
    const actualTemplate = templateContent.querySelector('template')
    if (!actualTemplate) {
      console.error('[OneVN Settings Overrides] Could not find basic-page template')
      return
    }
    const basicPageEl = actualTemplate.content.querySelector('#basicPage')
    if (!basicPageEl) {
      console.error('[OneVN Settings Overrides] Could not find basicPage element to insert Getting Started section')
    } else {
      const sectionsFromTop = document.createElement('div')
      sectionsFromTop.innerHTML = `
        <template is="dom-if" if="[[showPage_(pageVisibility.getStarted)]]">
          <settings-section page-title="${loadTimeData.getString('onevnGetStartedTitle')}" section="getStarted">
            <onevn-settings-getting-started prefs={{prefs}} page-visibility=[[pageVisibility]]></onevn-settings-getting-started>
          </settings-section>
        </template>
        <template is="dom-if" if="[[showPage_(pageVisibility.extensions)]]">
          <settings-section page-title="${loadTimeData.getString('onevnDefaultExtensions')}" section="extensions">
            <settings-onevn-default-extensions-page prefs="{{prefs}}"></settings-onevn-default-extensions-page>
          </settings-section>
        </template>
        <template is="dom-if" if="[[showPage_(pageVisibility.onevnSync)]]"
        restamp>
          <settings-section page-title="${loadTimeData.getString('onevnSync')}" section="onevnSync">
            <settings-onevn-sync-page prefs="{{prefs}}"></settings-onevn-sync-page>
          </settings-section>
        </template>
        <template is="dom-if" if="[[showPage_(pageVisibility.shields)]]"
        restamp>
          <settings-section page-title="${loadTimeData.getString('onevnShieldsTitle')}"
              section="shields">
            <settings-default-onevn-shields-page  prefs="{{prefs}}"></settings-default-onevn-shields-page>
          </settings-section>
        </template>
        <template is="dom-if" if="[[showPage_(pageVisibility.socialBlocking)]]"
        restamp>
          <settings-section page-title="${loadTimeData.getString('socialBlocking')}"
              section="socialBlocking">
            <settings-social-blocking-page prefs="{{prefs}}"></settings-social-blocking-page>
          </settings-section>
        </template>
      `
      basicPageEl.insertAdjacentElement('afterbegin', sectionsFromTop)
      // Move 'search' to before 'appearance'
      const searchEl = getSectionElement(actualTemplate.content, 'search')
      sectionsFromTop.insertAdjacentElement('beforeend', searchEl)
      // Remove 'startup'
      const startupEl = getSectionElement(actualTemplate.content, 'onStartup')
      startupEl.remove()
      // Advanced
      const advancedTemplate = templateContent.querySelector('template[if="[[showAdvancedSettings_(pageVisibility.advancedSettings)]]"]')
      if (!advancedTemplate) {
        console.error('[OneVN Settings Overrides] Could not find advanced section')
      }
      const advancedSubSectionsTemplate = advancedTemplate.content.querySelector('settings-idle-load template')
      if (!advancedSubSectionsTemplate) {
        console.error('[OneVN Settings Overrides] Could not find advanced sub-sections container')
      }
      const advancedToggleTemplate = advancedTemplate.content.querySelector('template')
      if (!advancedToggleTemplate) {
        console.error('[OneVN Settings Overrides] Could not find advanced toggle template')
      }
      const advancedToggleText = advancedToggleTemplate.content.querySelector('paper-button span')
      if (!advancedToggleText) {
        console.error('[OneVN Settings Overrides] Could not find advanced toggle text')
      }
      advancedToggleText.innerText = loadTimeData.getString('onevnAdditionalSettingsTitle')
      // Move autofill to after privacy
      const autofillEl = getSectionElement(actualTemplate.content, 'autofill')
      const privacyEl = getSectionElement(advancedSubSectionsTemplate.content, 'privacy')
      privacyEl.insertAdjacentElement('afterend', autofillEl)
    }
  },
  'settings-default-browser-page': (templateContent) => {
    // has nested templates
    for (const templateEl of templateContent.querySelectorAll('template')) {
      for (const boxEl of templateEl.content.querySelectorAll('.settings-box')) {
        boxEl.classList.remove('first')
      }
    }
  },
  'settings-people-page': (templateContent) => {
    // Import item needs to know it's the first in the section
    const importItem = templateContent.querySelector('.settings-box[on-click="onImportDataTap_"]')
    if (!importItem) {
      console.error('[OneVN Settings Overrides] Could not find import item in people_page')
    }
    importItem.classList.add('first')
  },
  'settings-payments-section': (templateContent) => {
    const manageLink = templateContent.querySelector('#manageLink')
    if (!manageLink) {
      console.error('[OneVN Settings Overrides] Could not find manage payments link')
    }
    manageLink.remove()
  }
})

// Icons
OneVNPatching.OverrideIronIcons('settings', 'onevn_settings', {
  palette: 'appearance',
  assignment: 'autofill',
  language: 'language',
  build: 'system',
  restore: 'reset-settings'
})
OneVNPatching.OverrideIronIcons('cr', 'onevn_settings', {
  security: 'privacy-security',
  search: 'search-engine',
  ['file-download']: 'download',
  print: 'printing'
})

//
// Register any new modules
//

Polymer({
  is: 'onevn-settings-getting-started'
})

})() // execute local scope
