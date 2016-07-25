#pragma  once


#include "QtWidgets/QWidget"



class CefView :public QWidget
{
public:
		CefView(QWidget *parent);
		~CefView();

public:
	void resizeEvent(QResizeEvent *event);
	void CreateBrowser(std::string url);


};


