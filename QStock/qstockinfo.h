#ifndef QSTOCKINFO_H
#define QSTOCKINFO_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QNetworkAccessManager;
class QTimerEvent;
class QTimer;
class QNetworkReply;
QT_END_NAMESPACE

class QStockInfo : public QObject
{
	Q_OBJECT
public:
	explicit QStockInfo(QObject *parent = nullptr);

protected:
	void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
	void dealReplay(QNetworkReply *reply);

private:
	void dealSina();

private:
	QTimer* m_sinaTimer;
	int m_sina;
	QNetworkAccessManager* m_NetManager;
};

#endif // QSTOCKINFO_H
