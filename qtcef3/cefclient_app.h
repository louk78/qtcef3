#include "include/cef_app.h"
#include "include/wrapper/cef_message_router.h"


class cefclient_app :public CefApp,
					 public CefBrowserProcessHandler,
					 public CefRenderProcessHandler
{

public:
	cefclient_app();
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
		OVERRIDE{ return this; }
	virtual CefRefPtr<CefRenderProcessHandler>GetRenderProcessHandler()OVERRIDE{
		return this;
	}
	virtual void OnContextInitialized()OVERRIDE;
	virtual void OnWebKitInitialized();
	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context);

private:
	HWND m_hParent;
	RECT m_WindowRect;
	CefRefPtr<CefMessageRouterRendererSide> message_router_;

	IMPLEMENT_REFCOUNTING(cefclient_app);

};