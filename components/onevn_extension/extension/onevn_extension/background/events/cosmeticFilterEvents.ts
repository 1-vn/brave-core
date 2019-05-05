import cosmeticFilterActions from '../actions/cosmeticFilterActions'

let rule = {
  host: '',
  selector: ''
}

// parent menu
chrome.contextMenus.create({
  title: 'Onevn',
  id: 'onevn',
  contexts: ['all']
})
// block ad child menu
chrome.contextMenus.create({
  title: 'Block element via selector',
  id: 'addBlockElement',
  parentId: 'onevn',
  contexts: ['all']
})
chrome.contextMenus.create({
  title: 'Clear CSS rules for this site',
  id: 'resetSiteFilterSettings',
  parentId: 'onevn',
  contexts: ['all']
})
chrome.contextMenus.create({
  title: 'Clear CSS rules for all sites',
  id: 'resetAllFilterSettings',
  parentId: 'onevn',
  contexts: ['all']
})

// contextMenu listener - when triggered, grab latest selector
chrome.contextMenus.onClicked.addListener(function (info, tab) {
  switch (info.menuItemId) {
    case 'addBlockElement': {
      chrome.tabs.query({ active: true, currentWindow: true }, function (tabs: any) {
        chrome.tabs.sendMessage(tabs[0].id, { type: 'getTargetSelector' }, function (response: any) {
          if (response) {
            rule.selector = window.prompt('CSS selector to block: ', `${response}`) || ''
            chrome.tabs.insertCSS({
              code: `${rule.selector} {display: none;}`
            })
            cosmeticFilterActions.siteCosmeticFilterAdded(rule.host, rule.selector)
          }
        })
      })
      break
    }
    case 'resetSiteFilterSettings': {
      cosmeticFilterActions.siteCosmeticFilterRemoved(rule.host)
      break
    }
    case 'resetAllFilterSettings': {
      cosmeticFilterActions.allCosmeticFiltersRemoved()
      break
    }
    default: {
      console.warn('[cosmeticFilterEvents] invalid context menu option: ${info.menuItemId}')
    }
  }
})

// content script listener for right click DOM selection event
chrome.runtime.onMessage.addListener((msg, sender, sendResponse) => {
  const action = typeof msg === 'string' ? msg : msg.type
  switch (action) {
    case 'contextMenuOpened': {
      rule.host = msg.baseURI
      break
    }
  }
})
