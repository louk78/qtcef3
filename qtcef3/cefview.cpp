#include "cefview.h"
#include "cefclient_handler.h"

extern cefclient_handler* g_instance;

CefView::CefView(QWidget *parent) :QWidget(parent)
{

}

CefView::~CefView()
{

}

void CefView::resizeEvent(QResizeEvent *event)
{
	if (g_instance)
	{
		if (g_instance->m_Browser)
		{
			HWND hwnd = g_instance->m_Browser->GetHost()->GetWindowHandle();

			if (hwnd)
			{
				SetWindowPos(hwnd, NULL, 0, 0,
					width(),
					height(),
					SWP_NOZORDER
					);
			}
		}
	}
}

void CefView::CreateBrowser(std::string url)
{
	bool bRet;

	CefWindowInfo window_info;
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = width();
	rect.bottom = height();

	window_info.SetAsChild((HWND)winId(),rect);

	CefRefPtr<cefclient_handler> handler(new cefclient_handler());

	CefBrowserSettings browser_settings;

	url = "file:///index.html";
	bRet = CefBrowserHost::CreateBrowser(window_info, handler.get(), url,
		browser_settings, NULL);
}