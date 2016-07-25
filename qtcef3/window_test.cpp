#include "window_test.h"
#include "qtcef3.h"
extern qtcef3 *g_MainWnd;

namespace window_test{


const char kTestUrl[] = "http://tests/window";
const char kMessagePositionName[] = "WindowTest.Position";
const char kMessageMinimizeName[] = "WindowTest.Minimize";
const char kMessageMaximizeName[] = "WindowTest.Maximize";
const char kMessageRestoreName[] = "WindowTest.Restore";

class Handler :public CefMessageRouterBrowserSide::Handler{
public:
	Handler(){}

	virtual bool OnQuery(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		int64 query_id,
		const CefString& request,
		bool persistent,
		CefRefPtr<Callback> callback
		)OVERRIDE{
		const std::string& message_name = request;
		g_MainWnd->JsTocppMessageParse(message_name, callback);


		return true;

	}

};


	void CreateMessageHandlers(MessageHandlerSet& handlers){
		handlers.insert(new Handler());
	}


}