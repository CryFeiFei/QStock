#include "qstockinfo.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTimerEvent>

#include <QDebug>
#include <QTextCodec>

namespace
{
const QString SinaAddress = "http://hq.sinajs.cn/list=";
}

QStockInfo::QStockInfo(QObject *parent) : QObject(parent)
{
	m_netManager = new QNetworkAccessManager(this);

	connect(m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(dealReplay(QNetworkReply*)));
	m_sina = startTimer(2000);

	QString strCode = SinaAddress + QString::fromUtf8("sh601006");
	m_sinaCodeList.append(strCode);
}

void QStockInfo::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == m_sina)
	{
		dealSina();
	}
}

QString unicodeToUtf8(const QString resStr)
{
QString temp;
for(int i=0;i<resStr.length();)
{
	if(resStr.at(i)=='\\')
	{
			QString str = resStr.mid(i+2,i+4);
			temp.append(str.mid(0,2).toUShort(0,16));
			i=i+4;
	}else
	{
			   temp.append(resStr.at(i));
			   ++i;
	}
}
return temp;
}

QString unicodeToUtf81(const QByteArray resStr)
{
QString temp;
for(int i=0;i<resStr.length();)
{
	if(resStr.at(i)=='\\')
	{
			QString str = resStr.mid(i+2,i+4);
			temp.append(str.mid(0,2).toUShort(0,16));
			i=i+4;
	}else
	{
			   temp.append(resStr.at(i));
			   ++i;
	}
}
return temp;
}

void QStockInfo::dealReplay(QNetworkReply *reply)
{
	qDebug()<<reply->url()<<endl;
	qDebug()<<reply->readAll()<<endl;
	QString strText = QString::fromUtf8(reply->readAll());
	qDebug()<<"11	"<<strText<<endl;

	QString strText2 = unicodeToUtf81(reply->readAll());
	qDebug()<<"22	"<<strText2<<endl;

//	QB

//	QByteArray byteArr = reply->readAll();
//	qDebug()<<byteArr<<endl;
//	qDebug()<<"2	"<<byteArr.toUShort()<<endl;
//	qDebug()<<QString::fromUtf16(&byteArr.toUShort())<<endl;

	QByteArray aa = "\\xB4\\xF3\\xC7\\xD8\\xCC\\xFA\\xC2\\xB7";

	QByteArray testHex = QByteArray::fromHex(aa);

	qDebug()<<testHex<<endl;
	QString test = unicodeToUtf8(aa);
	qDebug()<<test<<endl;
//	QString str  = QString::fromUtf16("\xB4\xF3\xC7\xD8\xCC\xFA\xC2\xB7");
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	QString strText1 = codec->toUnicode(test.toLatin1().data());
	qDebug()<<strText1<<endl;

	reply->deleteLater();
}

void QStockInfo::dealSina()
{
	foreach (auto& code, m_sinaCodeList)
	{
		QUrl url(code);
		QNetworkRequest request(url);
		request.setRawHeader("Accept", "text/html,application/json;charset=UTF-8;");
		request.setRawHeader("Content-Type", "application/json;charset=UTF-8");
//		request.setRawHeader("Accept-Encoding", "gzip, deflate");
//		request.setRawHeader("Accept-Language", "zh-CN,zh;q=0.9");
		request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.122 Safari/537.36");
		m_netManager->get(request);
	}
//	QNetworkRequest request(QUrl("http://hq.sinajs.cn/list=sh601006"));
//	QNetworkReply* re = m_NetManager->get(request);

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
