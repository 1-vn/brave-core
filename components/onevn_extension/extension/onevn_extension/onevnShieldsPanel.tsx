/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import * as ReactDOM from 'react-dom'
import shieldsDarkTheme from 'onevn-ui/theme/shields-dark'
import shieldsLightTheme from 'onevn-ui/theme/shields-light'
import { Provider } from 'react-redux'
import { Store } from 'react-chrome-redux'
import OneVNCoreThemeProvider from '../../../common/OneVNCoreThemeProvider'
import OneVNShields from './containers/onevnShields'
require('../../../fonts/muli.css')
require('../../../fonts/poppins.css')

const store: any = new Store({
  portName: 'ONEVN'
})

Promise.all([
  store.ready(),
  new Promise(resolve => chrome.onevnTheme.getOneVNThemeType(resolve))
])
.then(([ , themeType ]: [ undefined, chrome.onevnTheme.ThemeType ]) => {
  const mountNode: HTMLElement | null = document.querySelector('#root')
  ReactDOM.render(
    <Provider store={store}>
      <OneVNCoreThemeProvider
        initialThemeType={themeType}
        dark={shieldsDarkTheme}
        light={shieldsLightTheme}
      >
        <OneVNShields />
      </OneVNCoreThemeProvider>
    </Provider>,
    mountNode
  )
})
.catch((e) => {
  console.error('Problem mounting onevn shields')
  console.error(e)
})
