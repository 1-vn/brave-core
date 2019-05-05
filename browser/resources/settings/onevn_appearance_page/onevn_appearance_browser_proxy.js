/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

cr.define('settings', function() {
  /** @interface */
  class OnevnAppearanceBrowserProxy {
    /**
     * @return {!Promise<string>}
     */
    getOnevnThemeList() {}
  }

  /**
   * @implements {settings.OnevnAppearanceBrowserProxy}
   */
  class OnevnAppearanceBrowserProxyImpl {
    /** @override */
    getOnevnThemeList() {
      return new Promise(resolve => chrome.onevnTheme.getOnevnThemeList(resolve))
    }
  }

  cr.addSingletonGetter(OnevnAppearanceBrowserProxyImpl);

  return {
    OnevnAppearanceBrowserProxy: OnevnAppearanceBrowserProxy,
    OnevnAppearanceBrowserProxyImpl: OnevnAppearanceBrowserProxyImpl,
  };
});
