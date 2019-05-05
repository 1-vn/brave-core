#include "chrome/browser/ui/views/frame/browser_view.h"
#include "onevn/browser/ui/views/frame/onevn_browser_view.h"

// For now, OnevnBrowserFrame only needs to run on !linux
// and build complains of unused variables if we include it.
#if defined(OS_WIN) || defined(OS_MACOSX) || defined(OS_CHROMEOS)
#include "onevn/browser/ui/views/frame/onevn_browser_frame.h"
#define BrowserFrame OnevnBrowserFrame
#endif

#define BrowserView OnevnBrowserView
#include "../../../../../../../chrome/browser/ui/views/frame/browser_window_factory.cc"
#undef BrowserView

#if defined(OS_WIN) || defined(OS_MACOSX) || defined(OS_CHROMEOS)
#undef BrowserFrame
#endif
