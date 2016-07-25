#include "cefclient_handler.h"

#include <sstream>
#include <string>

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "window_test.h"



cefclient_handler* g_instance = NULL;


cefclient_handler::cefclient_handler()
: is_closing_(false){
	DCHECK(!g_instance);
	g_instance = this;
}

cefclient_handler::~cefclient_handler()
{
	g_instance = NULL;
}

cefclient_handler* cefclient_handler::GetInstance(){
	return g_instance;
}

void cefclient_handler::OnAfterCreated(CefRefPtr<CefBrowser> browser){
	CEF_REQUIRE_UI_THREAD();

	browser_list_.push_back(browser);
	m_Browser = browser;

	if (!message_router_)
	{
		CefMessageRouterConfig config;
		message_router_ = CefMessageRouterBrowserSide::Create(config);

		window_test::CreateMessageHandlers(message_handler_set_);
		MessageHandlerSet::const_iterator it = message_handler_set_.begin();
		for (; it != message_handler_set_.end(); ++it)
		{
			message_router_->AddHandler(*(it), false);
		}

	}

}

bool cefclient_handler::DoClose(CefRefPtr<CefBrowser> browser){
	CEF_REQUIRE_UI_THREAD();



	if (browser_list_.size() == 1){
		is_closing_ = true;
	}

	return false;
}

void cefclient_handler::OnBeforeClose(CefRefPtr<CefBrowser> browser){
	CEF_REQUIRE_UI_THREAD();

	BrowserList::iterator bit = browser_list_.begin();
	for (; bit != browser_list_.end(); ++bit){
		if ((*bit)->IsSame(browser)){
			browser_list_.erase(bit);
			break;
		}
	}

	if (browser_list_.empty()){
		CefQuitMessageLoop();
	}
}

void cefclient_handler::OnLoadError(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	ErrorCode errorCode,
	const CefString& errorText,
	const CefString& failedUrl){
	CEF_REQUIRE_UI_THREAD();

	if (errorCode == ERR_ABORTED)
		return;

	std::stringstream ss;

	ss << "<html><body bgcolor=\"white\">"
		"<h2>Failed to load URL " << std::string(failedUrl) <<
		"with error" << std::string(errorText) << " ( " << errorCode <<
		").</h2></body></html>";

	frame->LoadStringW(ss.str(), failedUrl);
}


void cefclient_handler::CloseAllBrowsers(bool force_close){
	if (!CefCurrentlyOn(TID_UI)){
		CefPostTask(TID_UI,
			base::Bind(&cefclient_handler::CloseAllBrowsers, this, force_close)
			);
	}

	if (browser_list_.empty())
		return;

	BrowserList::const_iterator it = browser_list_.begin();
	for (; it != browser_list_.end(); ++it)
		(*it)->GetHost()->CloseBrowser(force_close);
}


bool cefclient_handler::OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
										CefRefPtr<CefFrame> frame,
										CefRefPtr<CefRequest> request,
											bool is_redirect){
	CEF_REQUIRE_UI_THREAD();

	message_router_->OnBeforeBrowse(browser, frame);
	return false;

}


const char kFocusedNodeChangedMessage[] = "ClientRenderer.FocusedNodeChanged";
bool cefclient_handler::OnProcessMessageReceived(
	CefRefPtr<CefBrowser> browser,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message){
	CEF_REQUIRE_UI_THREAD();

	if (message_router_->OnProcessMessageReceived(browser,
		source_process,
		message
		))
	{
		return true;
	}

	std::string message_name = message->GetName();
	if (message_name == kFocusedNodeChangedMessage){

		return true;
	}


		return false;
}