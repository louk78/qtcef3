#ifndef QTCEF3_H
#define QTCEF3_H

#include <QtWidgets/QMainWindow>
#include <QJsonObject>
#include "ui_qtcef3.h"
#include "include/wrapper/cef_message_router.h"
typedef CefMessageRouterBrowserSide::Callback Callback;

class qtcef3 : public QMainWindow
{
	Q_OBJECT

public:
	qtcef3(QWidget *parent = 0);
	~qtcef3();
public:
	void JsTocppMessageParse(std::string message, CefRefPtr<Callback> &callback);
	void JsTocppMessageFuncPro(QJsonObject jsonObjMsg);

public:
	void closeEvent(QCloseEvent *e);
	void resizeEvent(QResizeEvent *e);

private:
	Ui::qtcef3Class ui;
};

#endif // QTCEF3_H
