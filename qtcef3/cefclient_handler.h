#ifndef CEF_CLIENT_HANDLE_H_
#define CEF_CLIENT_HANDLE_H_

#include "include/cef_client.h"
#include "include/wrapper/cef_message_router.h"
#include "include/cef_render_process_handler.h"

#include <set>
#include <list>

class cefclient_handler : public CefClient,
						  public CefContextMenuHandler,
						  public CefDisplayHandler,
						  public CefDragHandler,
						  public CefGeolocationHandler,
						  public CefKeyboardHandler,
						  public CefLifeSpanHandler,
						  public CefLoadHandler,
						  public CefRequestHandler
{

public:
	cefclient_handler();
	~cefclient_handler();

	static cefclient_handler* GetInstance();

	// CefClient methods
	CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() OVERRIDE{
		return this;
	}

	CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE{
		return this;
	}
	CefRefPtr<CefDragHandler> GetDragHandler() OVERRIDE{
		return this;
	}
	CefRefPtr<CefGeolocationHandler> GetGeolocationHandler() OVERRIDE{
		return this;
	}
	CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() OVERRIDE{
		return this;
	}
	CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE{
		return this;
	}
	CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE{
		return this;
	}
	CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE{
		return this;
	}
	bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message) OVERRIDE;


	//CefDisplayHandler methods:
	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
								const CefString& title)OVERRIDE;

	//CefLifeSpanHandler methods
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser)OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser)OVERRIDE;


	//CefLoadHandler methods:
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
							 CefRefPtr<CefFrame> frame,
							 ErrorCode errorCode,
							 const CefString& errorText,
							 const CefString& failedUrl) OVERRIDE;

	//CefRequestHandler methods
	virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
						CefRefPtr<CefFrame> frame,
						CefRefPtr<CefRequest> request,
						bool is_redirect)OVERRIDE;

	//Request that all existing browser windows close

	void CloseAllBrowsers(bool force_close);

	bool IsClosing() const { return is_closing_; }
private:
	typedef std::set<CefMessageRouterBrowserSide::Handler*> MessageHandlerSet;

private:
	typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
	BrowserList browser_list_;
	CefRefPtr<CefMessageRouterBrowserSide> message_router_;
	MessageHandlerSet message_handler_set_;

	bool is_closing_;
public:
	CefRefPtr<CefBrowser> m_Browser;

	//Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(cefclient_handler);
	DISALLOW_COPY_AND_ASSIGN(cefclient_handler);

};






#endif // !CEF_CLIENT_HANDLE_H_
