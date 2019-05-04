/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

cr.define('settings', function() {
  /** @interface */
  class OneVNPrivacyBrowserProxy {
    /**
     * @return {!Promise<string>}
     */
    getWebRTCPolicy() {}
    /**
     * @param {string} policy name.
     */
    setWebRTCPolicy(policy) {}
  }

  /**
   * @implements {settings.OneVNPrivacyBrowserProxy}
   */
  class OneVNPrivacyBrowserProxyImpl {
    /** @override */
    getWebRTCPolicy() {
      return cr.sendWithPromise('getWebRTCPolicy');
    }

    /** @override */
    setWebRTCPolicy(policy) {
      chrome.send('setWebRTCPolicy', [policy]);
    }
  }

  cr.addSingletonGetter(OneVNPrivacyBrowserProxyImpl);

  return {
    OneVNPrivacyBrowserProxy: OneVNPrivacyBrowserProxy,
    OneVNPrivacyBrowserProxyImpl: OneVNPrivacyBrowserProxyImpl,
  };
});
