import * as React from 'react'
import { ThemeProvider } from 'onevn-ui/theme'
import IOneVNTheme from 'onevn-ui/theme/theme-interface'

export type Props = {
  initialThemeType?: chrome.onevnTheme.ThemeType
  dark: IOneVNTheme,
  light: IOneVNTheme
}
type State = {
  themeType?: chrome.onevnTheme.ThemeType
}

function themeTypeToState (themeType: chrome.onevnTheme.ThemeType): State {
  return {
    themeType
  }
}

export default class OneVNCoreThemeProvider extends React.Component<Props, State> {
  constructor (props: Props) {
    super(props)
    if (props.initialThemeType) {
      this.state = themeTypeToState(props.initialThemeType)
    }
    chrome.onevnTheme.onOneVNThemeTypeChanged.addListener(this.setThemeState)
  }

  setThemeState = (themeType: chrome.onevnTheme.ThemeType) => {
    this.setState(themeTypeToState(themeType))
  }

  render () {
    // Don't render until we have a theme
    if (!this.state.themeType) return null
    // Render provided dark or light theme
    const selectedShieldsTheme = this.state.themeType === 'Dark'
                ? this.props.dark
                : this.props.light
    return (
      <ThemeProvider theme={selectedShieldsTheme}>
        {React.Children.only(this.props.children)}
      </ThemeProvider>
    )
  }
}
