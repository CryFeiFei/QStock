#include "qstockinfo.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTimerEvent>

#include <QDebug>

QStockInfo::QStockInfo(QObject *parent) : QObject(parent)
{
	m_NetManager = new QNetworkAccessManager(this);

	connect(m_NetManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(dealReplay(QNetworkReply*)));
	m_sina = startTimer(2000);
}

void QStockInfo::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == m_sina)
	{
		dealSina();
	}
}

void QStockInfo::dealReplay(QNetworkReply *reply)
{
	qDebug()<<reply->readAll()<<endl;
}

void QStockInfo::dealSina()
{

	QNetworkRequest request(QUrl("http://hq.sinajs.cn/list=sh601006"));
	QNetworkReply* re = m_NetManager->get(request);


//	qDebug()<<QTime::currentTime()<<endl;
//	qDebug()<<re->readAll()<<endl;

//	switch (re->error()) {
//	case QNetworkReply::NoError:
//	{
////		QString strText = QString::fromUtf8(re->readAll());
//		qDebug()<<re->readAll()<<endl;
//	}
//		break;
//	default:
//		break;
//	}

}
