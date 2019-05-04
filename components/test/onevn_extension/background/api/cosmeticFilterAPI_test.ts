
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as sinon from 'sinon'
import * as cosmeticFilterAPI from '../../../../onevn_extension/extension/onevn_extension/background/api/cosmeticFilterAPI'

describe('cosmeticFilterTestSuite', () => {
  describe('addSiteCosmeticFilter', () => {
    const url = 'https://www.1-vn.com'
    const filter = '#cssFilter'
    let getStorageStub: any
    let setStorageStub: any
    beforeAll(() => {
      getStorageStub = sinon.stub(chrome.storage.local, 'get')
      setStorageStub = sinon.stub(chrome.storage.local, 'set')
    })
    afterAll(() => {
      getStorageStub.restore()
      setStorageStub.restore()
    })
    beforeEach(() => {
      getStorageStub.resetHistory()
      setStorageStub.resetHistory()
    })

    it('passes only 1 arg to chrome.storage.local.set', () => {
      getStorageStub.yields({
        'list': {
          'hostname': ['samplefilter']
        }
      })
      cosmeticFilterAPI.addSiteCosmeticFilter(url, filter)
        .catch(() => {
          expect(true).toBe(false)
        })
      expect(setStorageStub.getCall(0).args.length).toBe(1)
    })
    it('passes the correct arguments to chrome.storage.local.set when storage is empty', () => {
      getStorageStub.yields({})
      cosmeticFilterAPI.addSiteCosmeticFilter(url, filter)
        .catch(() => {
          expect(true).toBe(false)
        })
      expect(setStorageStub.getCall(0).args[0]).toEqual({
        cosmeticFilterList: {
          'https://www.1-vn.com': ['#cssFilter']
        }
      })
    })
    it('passes the correct arguments to chrome.storage.local.set when storage is undefined', () => {
      getStorageStub.yields(undefined)
      cosmeticFilterAPI.addSiteCosmeticFilter(url, filter)
        .catch(() => {
          expect(true).toBe(false)
        })
      expect(setStorageStub.getCall(0).args[0]).toEqual({
        cosmeticFilterList: {
          'https://www.1-vn.com': ['#cssFilter']
        }
      })
    })
    it('can add more than 1 filter', () => {
      getStorageStub.yields({
        'cosmeticFilterList': {
          'hostname': ['samplefilter']
        }
      })
      cosmeticFilterAPI.addSiteCosmeticFilter('hostname', 'samplefilter2')
        .catch(() => {
          expect(true).toBe(false)
        })
      expect(setStorageStub.getCall(0).args[0]).toEqual({
        'cosmeticFilterList': {
          'hostname': ['samplefilter', 'samplefilter2']
        }
      })
    })
  })
  describe('removeSiteFilter', () => {
    const url = 'https://www.1-vn.com'
    const filter = '#cssFilter'
    let getStorageStub: any
    let setStorageStub: any

    beforeAll(() => {
      getStorageStub = sinon.stub(chrome.storage.local, 'get')
      setStorageStub = sinon.stub(chrome.storage.local, 'set')
    })
    afterAll(() => {
      getStorageStub.restore()
      setStorageStub.restore()
    })
    beforeEach(() => {
      getStorageStub.resetHistory()
      setStorageStub.resetHistory()
    })

    it('passes only 1 arg to chrome.storage.local.set', () => {
      getStorageStub.yields({
        'cosmeticFilterList': {
          url: filter
        }
      })
      cosmeticFilterAPI.removeSiteFilter(url)
      expect(setStorageStub.getCall(0).args.length).toBe(1)
    })
    it('removes the correct filter', () => {
      getStorageStub.yields({
        cosmeticFilterList: {
          'https://www.1-vn.com': ['#cssFilter'],
          'https://not1-vn.com': ['notACSSFilter']
        }
      })
      cosmeticFilterAPI.removeSiteFilter(url)
      expect(setStorageStub.getCall(0).args[0]).toEqual({
        cosmeticFilterList: {
          'https://not1-vn.com': ['notACSSFilter']
        }
      })
    })
    it('handles empty storage', () => {
      getStorageStub.yields({})
      cosmeticFilterAPI.removeSiteFilter(url)
      expect(setStorageStub.getCall(0).args[0]).toEqual({
        cosmeticFilterList: {}
      })
    })
    it('handles undefined storage', () => {
      getStorageStub.yields(undefined)
      cosmeticFilterAPI.removeSiteFilter(url)
      expect(setStorageStub.getCall(0).args[0]).toEqual({
        cosmeticFilterList: {}
      })
    })
    it('handles url not in storage', () => {
      getStorageStub.yields({
        cosmeticFilterList: {
          url: filter
        }
      })
      cosmeticFilterAPI.removeSiteFilter('urlNotInStorage')
      expect(setStorageStub.getCall(0).args[0]).toEqual({
        cosmeticFilterList: {
          url: filter
        }
      })
    })
  })
  describe('removeAllFilters', () => {
    let getStorageStub: any
    let setStorageStub: any
    beforeAll(() => {
      getStorageStub = sinon.stub(chrome.storage.local, 'get')
      setStorageStub = sinon.stub(chrome.storage.local, 'set')
    })

    afterAll(() => {
      getStorageStub.restore()
      setStorageStub.restore()
    })
    beforeEach(() => {
      getStorageStub.resetHistory()
      setStorageStub.resetHistory()
    })

    it('sets empty list object', () => {
      getStorageStub.yields({
        cosmeticFilterList: {
          'hostname': 'isNotEmpty'
        }
      })
      cosmeticFilterAPI.removeAllFilters()
      expect(setStorageStub.getCall(0).args[0]).toEqual({
        cosmeticFilterList: {}
      })
    })
  })
  describe('applySiteFilters', () => {
    const filter = '#cssFilter'
    const filter2 = '#cssFilter2'

    let getStorageStub: any
    let setStorageStub: any
    let insertCSSStub: any

    beforeAll(() => {
      getStorageStub = sinon.stub(chrome.storage.local, 'get')
      setStorageStub = sinon.stub(chrome.storage.local, 'set')
      insertCSSStub = sinon.stub(chrome.tabs, 'insertCSS')
    })
    afterAll(() => {
      getStorageStub.restore()
      setStorageStub.restore()
      insertCSSStub.restore()
    })
    beforeEach(() => {
      getStorageStub.resetHistory()
      setStorageStub.resetHistory()
      insertCSSStub.resetHistory()
    })
    it('applies the correct filter', () => {
      getStorageStub.yields({
        cosmeticFilterList: {
          '1-vn.com': [filter]
        }
      })
      cosmeticFilterAPI.applySiteFilters('1-vn.com')
      expect(insertCSSStub.getCall(0).args[0]).toEqual({
        code: `${ filter } {display: none;}`,
        runAt: 'document_start'
      })
    })
    it('applies multiple filters correctly', () => {
      getStorageStub.yields({
        cosmeticFilterList: {
          '1-vn.com': [filter, filter2]
        }
      })
      cosmeticFilterAPI.applySiteFilters('1-vn.com')
      expect(insertCSSStub.getCall(0).args[0]).toEqual({
        code: `${ filter } {display: none;}`,
        runAt: 'document_start'
      })
      expect(insertCSSStub.getCall(1).args[0]).toEqual({
        code: `${ filter2 } {display: none;}`,
        runAt: 'document_start'
      })

    })
    // chrome.local.storage.get() always returns an empty object if nothing exists
    it('doesn\'t apply filters if storage for host is implicitly undefined', () => {
      getStorageStub.yields({
        cosmeticFilterList: {}
      })
      cosmeticFilterAPI.applySiteFilters('1-vn.com')
      expect(insertCSSStub.called).toBe(false)
    })
    it('doesn\'t apply filters if storage is explicitly undefined', () => {
      getStorageStub.yields({
        cosmeticFilterList: {
          '1-vn.com': undefined
        }
      })
      cosmeticFilterAPI.applySiteFilters('1-vn.com')
      expect(insertCSSStub.called).toBe(false)
    })
  })
})
