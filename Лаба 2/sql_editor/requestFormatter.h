#ifndef REQUESTFORMATTER_H
#define REQUESTFORMATTER_H
#include <QWidget>

class requestFormatter : public QObject
{
    Q_OBJECT
private:
    QString request;

public:
    requestFormatter(QObject *parent = nullptr)
    {
        setParent(parent);
    }

public slots:
    void slotFormatRequest(QString *req)
    {
        request = *req;
        //smth
        emit signalSendRequest(&request);
    }

signals:
    void signalSendRequest(QString *request);

};

#endif // REQUESTFORMATTER_H
