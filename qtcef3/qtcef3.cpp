#include "qtcef3.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

qtcef3::qtcef3(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
}

qtcef3::~qtcef3()
{

}

void qtcef3::closeEvent(QCloseEvent *e)
{

}

void qtcef3::resizeEvent(QResizeEvent *e)
{
	centralWidget()->resize(size());
}

void qtcef3::JsTocppMessageParse(std::string message, CefRefPtr<Callback> &callback)
{
	QJsonParseError error;
	QByteArray byteArray = QByteArray::fromStdString(message);
	QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray, &error);
	if (error.error == QJsonParseError::NoError)
	{
		QJsonObject  jsonObj = jsonDoc.object();
		QJsonArray jsonArray = jsonObj["function"].toArray();
		for (int i = 0; i < jsonArray.size(); i++)
		{
			QJsonObject tempObj = jsonArray[i].toObject();
			JsTocppMessageFuncPro(tempObj);
		}
	}
	else
	{
		qDebug() << error.errorString();
	}

}


void qtcef3::JsTocppMessageFuncPro(QJsonObject jsonObjMsg)
{
	QString funcName;
	funcName = jsonObjMsg["name"].toString();
	if (funcName.contains("Minimize"))
	{
		this->showMinimized();
	}
	else if (funcName.contains("Maximize"))
	{
		this->showMaximized();
	}
	else if (funcName.contains("Closewindow"))
	{
		this->close();
	}
	else if (funcName.contains("Restore"))
	{
		this->showNormal();
	}
}