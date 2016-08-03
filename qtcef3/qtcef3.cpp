#include "qtcef3.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include "cefview.h"

qtcef3::qtcef3(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	m_pCefView = NULL;
	
}


qtcef3::~qtcef3()
{
	if (m_pCefView)
	{
		delete m_pCefView;
	}
}

void qtcef3::closeEvent(QCloseEvent *e)
{
	
}

void qtcef3::resizeEvent(QResizeEvent *e)
{
	centralWidget()->resize(size());
}

void qtcef3::showEvent(QShowEvent *e)
{
}

void qtcef3::CreateBrowser()
{
	if (m_pCefView == NULL)
	{
		m_pCefView = new CefView(this);
	   m_pCefView->resize(width(), height());
		m_pCefView->CreateBrowser("");
		setCentralWidget(m_pCefView);
	}
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
			JsTocppMessageFuncPro(tempObj,callback);
		}
	}
	else
	{
		qDebug() << error.errorString();
	}

}


void qtcef3::JsTocppMessageFuncPro(QJsonObject jsonObjMsg,CefRefPtr<Callback> &callback)
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