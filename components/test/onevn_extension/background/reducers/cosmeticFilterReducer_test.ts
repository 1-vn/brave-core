/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as shieldPanelTypes from '../../../../onevn_extension/extension/onevn_extension/constants/shieldsPanelTypes'
import * as cosmeticFilterTypes from '../../../../onevn_extension/extension/onevn_extension/constants/cosmeticFilterTypes'
import * as windowTypes from '../../../../onevn_extension/extension/onevn_extension/constants/windowTypes'
import * as tabTypes from '../../../../onevn_extension/extension/onevn_extension/constants/tabTypes'
import * as webNavigationTypes from '../../../../onevn_extension/extension/onevn_extension/constants/webNavigationTypes'
import shieldsPanelReducer from '../../../../onevn_extension/extension/onevn_extension/background/reducers/shieldsPanelReducer'
import * as shieldsAPI from '../../../../onevn_extension/extension/onevn_extension/background/api/shieldsAPI'
import cosmeticFilterReducer from '../../../../onevn_extension/extension/onevn_extension/background/reducers/cosmeticFilterReducer'
import * as cosmeticFilterAPI from '../../../../onevn_extension/extension/onevn_extension/background/api/cosmeticFilterAPI'
import * as tabsAPI from '../../../../onevn_extension/extension/onevn_extension/background/api/tabsAPI'
import * as shieldsPanelState from '../../../../onevn_extension/extension/onevn_extension/state/shieldsPanelState'
import { initialState } from '../../../testData'
import * as deepFreeze from 'deep-freeze-node'
import { ShieldDetails } from '../../../../onevn_extension/extension/onevn_extension/types/actions/shieldsPanelActions'
import * as actions from '../../../../onevn_extension/extension/onevn_extension/actions/shieldsPanelActions'
import { State } from '../../../../onevn_extension/extension/onevn_extension/types/state/shieldsPannelState'

describe('cosmeticFilterReducer', () => {
  it('should handle initial state', () => {
    expect(shieldsPanelReducer(undefined, actions.blockAdsTrackers('allow')))
      .toEqual(initialState.cosmeticFilter)
  })
  describe('ON_COMMITTED', () => {
    const tabId = 1
    let spy: jest.SpyInstance
    let resetNoScriptInfoSpy: jest.SpyInstance
    let resetBlockingResourcesSpy: jest.SpyInstance
    beforeEach(() => {
      spy = jest.spyOn(shieldsPanelState, 'resetBlockingStats')
      resetNoScriptInfoSpy = jest.spyOn(shieldsPanelState, 'resetNoScriptInfo')
      resetBlockingResourcesSpy = jest.spyOn(shieldsPanelState, 'resetBlockingResources')
    })
    afterEach(() => {
      spy.mockRestore()
      resetNoScriptInfoSpy.mockRestore()
      resetBlockingResourcesSpy.mockRestore()
    })
    it('calls resetBlockingStats when isMainFrame is true', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: webNavigationTypes.ON_COMMITTED,
        tabId: tabId,
        url: 'https://www.1-vn.com',
        isMainFrame: true
      })
      expect(spy).toBeCalledTimes(1)
      expect(spy.mock.calls[0][1]).toBe(tabId)
    })
    it('does not call resetBlockingStats when isMainFrame is false', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: webNavigationTypes.ON_COMMITTED,
        tabId: tabId,
        url: 'https://www.1-vn.com',
        isMainFrame: false
      })
      expect(spy).not.toBeCalled()
    })
    it('calls resetNoScriptInfo when isMainFrame is true', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: webNavigationTypes.ON_COMMITTED,
        tabId: tabId,
        url: 'https://www.1-vn.com',
        isMainFrame: true
      })
      expect(resetNoScriptInfoSpy).toBeCalledTimes(1)
      expect(resetNoScriptInfoSpy.mock.calls[0][1]).toBe(tabId)
      expect(resetNoScriptInfoSpy.mock.calls[0][2]).toBe('https://www.1-vn.com')
    })
    it('does not call resetNoScriptInfo when isMainFrame is false', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: webNavigationTypes.ON_COMMITTED,
        tabId: tabId,
        url: 'https://www.1-vn.com',
        isMainFrame: false
      })
      expect(resetNoScriptInfoSpy).not.toBeCalled()
    })
    it('calls resetBlockingResources when isMainFrame is true', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: webNavigationTypes.ON_COMMITTED,
        tabId: tabId,
        url: 'https://www.1-vn.com',
        isMainFrame: true
      })
      expect(spy).toBeCalledTimes(1)
      expect(spy.mock.calls[0][1]).toBe(tabId)
    })
    it('does not call resetBlockingResources when isMainFrame is false', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: webNavigationTypes.ON_COMMITTED,
        tabId: tabId,
        url: 'https://www.1-vn.com',
        isMainFrame: false
      })
      expect(spy).not.toBeCalled()
    })
  })
  describe('WINDOW_REMOVED', () => {
    const windowId = 1
    let spy: jest.SpyInstance
    beforeEach(() => {
      spy = jest.spyOn(shieldsPanelState, 'removeWindowInfo')
    })
    afterEach(() => {
      spy.mockRestore()
    })
    it('calls shieldsPanelState.removeWindowInfo', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: windowTypes.WINDOW_REMOVED,
        windowId
      })
      expect(spy).toBeCalledTimes(1)
      expect(spy.mock.calls[0][1]).toBe(windowId)
    })
  })
  describe('WINDOW_FOCUS_CHANGED', () => {
    const windowId = 1
    const tabId = 2
    let updateFocusedWindowSpy: jest.SpyInstance
    let requestShieldPanelDataSpy: jest.SpyInstance
    beforeEach(() => {
      updateFocusedWindowSpy = jest.spyOn(shieldsPanelState, 'updateFocusedWindow')
      requestShieldPanelDataSpy = jest.spyOn(shieldsAPI, 'requestShieldPanelData')
      const state = deepFreeze({
        ...initialState.shieldsPanel,
        windows: {
          1: tabId
        },
        tabs: {
          [tabId]: { url: 'https://1-vn.com' }
        }
      })
      shieldsPanelReducer(state, {
        type: windowTypes.WINDOW_FOCUS_CHANGED,
        windowId: windowId
      })
    })
    afterEach(() => {
      updateFocusedWindowSpy.mockRestore()
      requestShieldPanelDataSpy.mockRestore()
    })
    it('calls shieldsPanelState.updateFocusedWindow', () => {
      expect(updateFocusedWindowSpy).toBeCalledTimes(1)
      expect(updateFocusedWindowSpy.mock.calls[0][1]).toBe(windowId)
    })
    it('calls shieldsPanelState.requestShieldPanelDataSpy ', () => {
      expect(requestShieldPanelDataSpy).toBeCalledWith(tabId)
    })
  })
  describe('TAB_DATA_CHANGED', () => {
    const windowId = 1
    const tabId = 2
    const state = deepFreeze({ ...initialState.shieldsPanel, windows: { 1: tabId }, tabs: {} })
    let updateActiveTabSpy: jest.SpyInstance
    beforeEach(() => {
      updateActiveTabSpy = jest.spyOn(shieldsPanelState, 'updateActiveTab')
    })
    afterEach(() => {
      updateActiveTabSpy.mockRestore()
    })
    it('calls shieldsPanelState.updateActiveTab when the tab is active', () => {
      shieldsPanelReducer(state, {
        type: tabTypes.TAB_DATA_CHANGED,
        tabId: tabId,
        tab: {
          active: true,
          id: tabId,
          windowId,
          index: 1,
          pinned: false,
          highlighted: false,
          incognito: false,
          selected: false
        },
        changeInfo: {}
      })
      expect(updateActiveTabSpy).toBeCalledTimes(1)
      expect(updateActiveTabSpy.mock.calls[0][1]).toBe(windowId)
      expect(updateActiveTabSpy.mock.calls[0][2]).toBe(tabId)
    })
    it('does not call shieldsPanelState.updateActiveTab when the tab is not active', () => {
      shieldsPanelReducer(state, {
        type: tabTypes.TAB_DATA_CHANGED,
        tabId: tabId,
        tab: {
          active: false,
          id: tabId,
          windowId,
          index: 1,
          pinned: false,
          highlighted: false,
          incognito: false,
          selected: false
        },
        changeInfo: {}
      })
      expect(updateActiveTabSpy).not.toBeCalled()
    })
  })
  describe('TAB_CREATED', () => {
    const windowId = 1
    const tabId = 2
    const state = {
      ...initialState.shieldsPanel,
      windows: {
        1: tabId
      },
      tabs: {}
    }
    let updateActiveTabSpy: jest.SpyInstance
    beforeEach(() => {
      updateActiveTabSpy = jest.spyOn(shieldsPanelState, 'updateActiveTab')
    })
    afterEach(() => {
      updateActiveTabSpy.mockRestore()
    })
    it('calls shieldsPanelState.updateActiveTab when the tab is active', () => {
      shieldsPanelReducer(state, {
        type: tabTypes.TAB_CREATED,
        tab: {
          active: true,
          id: tabId,
          windowId,
          index: 1,
          pinned: false,
          highlighted: false,
          incognito: false,
          selected: false
        }
      })
      expect(updateActiveTabSpy).toBeCalledTimes(1)
      expect(updateActiveTabSpy.mock.calls[0][1]).toBe(windowId)
      expect(updateActiveTabSpy.mock.calls[0][2]).toBe(tabId)
    })
    it('does not call shieldsPanelState.updateActiveTab when the tab is not active', () => {
      shieldsPanelReducer(state, {
        type: tabTypes.TAB_CREATED,
        tab: {
          active: false,
          id: tabId,
          windowId,
          index: 1,
          pinned: false,
          highlighted: false,
          incognito: false,
          selected: false
        }
      })
      expect(updateActiveTabSpy).not.toBeCalled()
    })
  })
  const origin = 'https://1-vn.com'
  const state: State = deepFreeze({
    tabs: {
      2: {
        origin,
        hostname: '1-vn.com',
        adsBlocked: 0,
        controlsOpen: true,
        onevnShields: 'allow',
        trackersBlocked: 0,
        httpsRedirected: 0,
        javascriptBlocked: 0,
        fingerprintingBlocked: 0,
        id: 2,
        httpUpgradableResources: 'block',
        javascript: 'block',
        trackers: 'block',
        ads: 'block',
        fingerprinting: 'block',
        cookies: 'block',
        noScriptInfo: {},
        adsBlockedResources: [],
        fingerprintingBlockedResources: [],
        httpsRedirectedResources: [],
        javascriptBlockedResources: [],
        trackersBlockedResources: []
      }
    },
    windows: {
      1: 2
    },
    currentWindowId: 1
  })
  describe('SHIELDS_PANEL_DATA_UPDATED', () => {
    it('updates state detail', () => {
      const tabId = 2
      const details: ShieldDetails = {
        id: tabId,
        hostname: '1-vn.com',
        origin: '1-vn.com',
        ads: 'block',
        trackers: 'block',
        httpUpgradableResources: 'block',
        javascript: 'block',
        fingerprinting: 'block',
        cookies: 'block'
      }
      expect(
          shieldsPanelReducer(initialState.shieldsPanel, {
            type: shieldPanelTypes.SHIELDS_PANEL_DATA_UPDATED,
            details
          })).toEqual({
            currentWindowId: -1,
            tabs: {
              [tabId]: {
                adsBlocked: 0,
                trackersBlocked: 0,
                httpsRedirected: 0,
                javascriptBlocked: 0,
                fingerprintingBlocked: 0,
                hostname: '1-vn.com',
                origin: '1-vn.com',
                id: tabId,
                ads: 'block',
                trackers: 'block',
                httpUpgradableResources: 'block',
                javascript: 'block',
                fingerprinting: 'block',
                cookies: 'block',
                controlsOpen: true,
                onevnShields: 'allow',
                noScriptInfo: {},
                adsBlockedResources: [],
                fingerprintingBlockedResources: [],
                httpsRedirectedResources: [],
                javascriptBlockedResources: [],
                trackersBlockedResources: []
              }
            },
            windows: {}
          })
    })
  })
  describe('SHIELDS_TOGGLED', () => {
    let reloadTabSpy: jest.SpyInstance
    let setAllowOnevnShieldsSpy: jest.SpyInstance
    beforeEach(() => {
      reloadTabSpy = jest.spyOn(tabsAPI, 'reloadTab')
      setAllowOnevnShieldsSpy = jest.spyOn(shieldsAPI, 'setAllowOnevnShields')
    })
    afterEach(() => {
      reloadTabSpy.mockRestore()
      setAllowOnevnShieldsSpy.mockRestore()
    })
    it('should call setAllowOnevnShields', () => {
      expect(
        shieldsPanelReducer(state, {
          type: shieldPanelTypes.SHIELDS_TOGGLED,
          setting: 'allow'
        })).toEqual(state)
      expect(setAllowOnevnShieldsSpy).toBeCalledWith(origin, 'allow')
    })
  })
  describe('SITE_COSMETIC_FILTER_REMOVED', () => {
    let removeSiteFilterSpy: jest.SpyInstance
    beforeEach(() => {
      removeSiteFilterSpy = jest.spyOn(cosmeticFilterAPI, 'removeSiteFilter')
    })
    afterEach(() => {
      removeSiteFilterSpy.mockRestore()
    })
    it('should call removeSiteFilter', () => {
      expect(
        cosmeticFilterReducer(state, {
          type: cosmeticFilterTypes.SITE_COSMETIC_FILTER_REMOVED,
          origin
        })).toEqual(state)
    })
  })
  describe('ALL_COSMETIC_FILTERS_REMOVED', () => {
    let removeSiteFilterSpy: jest.SpyInstance
    beforeEach(() => {
      removeSiteFilterSpy = jest.spyOn(cosmeticFilterAPI, 'removeAllFilters')
    })
    afterEach(() => {
      removeSiteFilterSpy.mockRestore()
    })
    it('should call removeAllFilters', () => {
      expect(
        cosmeticFilterReducer(state, {
          type: cosmeticFilterTypes.ALL_COSMETIC_FILTERS_REMOVED
        })).toEqual(state)
    })
  })
  describe('SITE_COSMETIC_FILTER_ADDED', () => {
    let removeSiteFilterSpy: jest.SpyInstance
    beforeEach(() => {
      removeSiteFilterSpy = jest.spyOn(cosmeticFilterAPI, 'addSiteCosmeticFilter')
    })
    afterEach(() => {
      removeSiteFilterSpy.mockRestore()
    })
    it('should call addSiteCosmeticFilter', () => {
      const cssfilter = '#test'
      expect(
        cosmeticFilterReducer(state, {
          type: cosmeticFilterTypes.SITE_COSMETIC_FILTER_ADDED,
          origin,
          cssfilter
        })).toEqual(state)
    })
  })
})
