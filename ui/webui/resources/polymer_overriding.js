// Copyright (c) 2019 The Onevn Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

// This module is in global scope,
// so create a temporary scope.
(function () {
  const debug = false
  // Re-write `Polymer(componentInfo)` function
  const oldFn = window.Polymer._polymerFn
  function newPolymerFn(component) {
    if (component && component.is) {
      if (debug) {
        console.debug(`Polymer component registering: ${component.is}`, component)
      }
      addOnevnBehaviors(component)
      addOnevnTemplateModifications(component)
      addOnevnStyleOverrides(component)
    }
    return oldFn(component)
  }
  window.Polymer._polymerFn = newPolymerFn

  const allBehaviorsMap = {}

  function addOnevnBehaviors(component) {
    if (allBehaviorsMap[component.is]) {
      component.behaviors = component.behaviors || []
      component.behaviors.push(...allBehaviorsMap[component.is])
      delete allBehaviorsMap[component.is]
    }
  }

  const allOnevnTemplateModificationsMap = {}

  function addOnevnTemplateModifications(component) {
    if (allOnevnTemplateModificationsMap[component.is]) {
      const moduleName = component.is
      const domModule = Polymer.DomModule.import(moduleName)
      if (domModule) {
        const template = domModule.querySelector('template')
        if (template) {
          const templateContent = template.content
          const t0 = performance.now()
          allOnevnTemplateModificationsMap[component.is](templateContent)
          const t1 = performance.now()
          console.debug(`Modifying template '${component.is}' took ${t1 - t0}ms`)
        }
      }
      delete allOnevnTemplateModificationsMap[component.is]
    }
  }

  function addOnevnStyleOverrides(component) {
    // does have template style element?
    const moduleName = component.is
    const domModule = Polymer.DomModule.import(moduleName)
    if (!domModule) {
      return
    }
    // has override?
    const overrideModuleName = `onevn-override-style-${moduleName}`
    const hasOverride = !!Polymer.DomModule.import(overrideModuleName)
    if (!hasOverride) {
      return
    }
    const template = domModule.querySelector('template')
    if (!template) {
      return
    }
    const styleElement = template.content.querySelector('style')
    if (!styleElement) {
      return
    }
    styleElement.setAttribute(
      'include',
      `${styleElement.getAttribute('include')} ${overrideModuleName}`
    )
  }

  function RegisterPolymerComponentBehaviors(behaviorsMap) {
    Object.assign(allBehaviorsMap, behaviorsMap)
  }

  function RegisterPolymerTemplateModifications(modificationsMap) {
    Object.assign(allOnevnTemplateModificationsMap, modificationsMap)
  }

  function OverrideIronIcons(iconSetName, overridingIconSetName, iconOverrides) {
    // Here, we change the underlying DOM.
    // We cannot simply change `IconSet._icons` since
    // there are occasions where this will get re-parsed from DOM elements.
    const meta = Polymer.Base.create('iron-meta', {type: 'iconset'})
    const srcIconSet = meta.byKey(iconSetName)
    const overrideIconSet = meta.byKey(overridingIconSetName)
    for (const chromiumIconName in iconOverrides) {
      const chromiumIcon = srcIconSet.querySelector(`#${chromiumIconName}`)
      if (!chromiumIcon) {
        console.error(`[onevn overrides] Could not find chromium icon '${chromiumIconName}' in iconset '${iconSetName}' for replacement!`)
        continue
      }
      const onevnIconName = iconOverrides[chromiumIconName]
      const onevnIcon = overrideIconSet.querySelector(`#${onevnIconName}`)
      if (!onevnIcon) {
        console.error(`[onevn overrides] Could not find onevn icon '${onevnIconName}' in iconset '${overridingIconSetName}' for replacement!`)
        continue
      }
      // replace
      chromiumIcon.innerHTML = onevnIcon.innerHTML
    }
    // Ensure icons get re-parsed if already parseds
    // `getIconNames` ensures this._icons in iron-iconset-svg is re-parsed
    // from DOM. If that changes, we'll need to find another way,
    // perhaps `srcIconSet._icons = srcIconSet._createIconMap()`
    srcIconSet.getIconNames()
  }

  // Accessible to other modules
  window.OnevnPatching = Object.assign({}, window.OnevnPatching, {
    RegisterPolymerComponentBehaviors,
    RegisterPolymerTemplateModifications,
    OverrideIronIcons
  })
})()
