/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

(function() {
'use strict';

Polymer({
  is: 'settings-onevn-appearance-theme',

  properties: {
    onevnThemeList_: [],
  },

  /** @private {?settings.OneVNAppearanceBrowserProxy} */
  browserProxy_: null,

  /** @override */
  created: function() {
    this.browserProxy_ = settings.OneVNAppearanceBrowserProxyImpl.getInstance();
  },

  /** @override */
  ready: function() {
    this.browserProxy_.getOneVNThemeList().then(list => {
      this.onevnThemeList_ = JSON.parse(list);
    });
  },
});

/**
 * 'settings-onevn-appearance-toolbar' is the settings page area containing
 * onevn's appearance settings related to the toolbar.
 */
Polymer({
  is: 'settings-onevn-appearance-toolbar',
});
})();
