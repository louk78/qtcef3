#include "qtcef3.h"
#include <QtWidgets/QApplication>
#include "cefclient_app.h"
#include "cefview.h"
qtcef3 *g_MainWnd;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HINSTANCE hInstance = ::GetModuleHandle(NULL);	
	CefEnableHighDPISupport();
	void* sandbox_info = NULL;

	CefMainArgs main_args(hInstance);
	CefRefPtr<cefclient_app> app(new cefclient_app());
	int exit_code = CefExecuteProcess(main_args, app.get(), sandbox_info);
	if (exit_code >= 0)
		return exit_code;
	CefSettings settings;
	settings.multi_threaded_message_loop = TRUE;
	CefInitialize(main_args, settings, app.get(), sandbox_info);

	qtcef3 w;
	g_MainWnd = &w;
	w.resize(1000, 800);
	w.CreateBrowser();
	w.show();
	exit_code = a.exec();
	CefShutdown();
	return exit_code;
}
