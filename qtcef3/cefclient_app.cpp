#include "cefclient_app.h"

#include <string>

#include "cefclient_handler.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h"


cefclient_app::cefclient_app()
{


}

void cefclient_app::OnContextInitialized(){
	CEF_REQUIRE_UI_THREAD();
	
}

void cefclient_app::OnWebKitInitialized()
{
	CefMessageRouterConfig config;
	message_router_ = CefMessageRouterRendererSide::Create(config);
}

void cefclient_app::OnContextCreated(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context){

	message_router_->OnContextCreated(browser, frame, context);
}
