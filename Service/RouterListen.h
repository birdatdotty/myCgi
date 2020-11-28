#ifndef ROUTERLISTEN_H
#define ROUTERLISTEN_H

#include <QMutex>
#include <QThread>
#include <fcgi_stdio.h>
#include "Router.h"


class FCGIRequest;
//#include "FCGIRequest.h"


class RouterListen : public QThread
{
    Q_OBJECT
public:
//    RouterListen(QMutex &mutex, int socketId, QString str)
    explicit RouterListen(QMutex &mutex, int socketId, QList<Router *> router, ObjGlob* objGlob, QObject *parent = nullptr);

    FCGIRequest FCGIReq;

protected:
    void run() override;

private:
    QMutex &mutex;
    QString path;
//    int listenQueueBacklog;
    int socketId;
    QList<Router *> router;
    ObjGlob* objGlob;
    QJSEngine engine;
    Request* request;

    QJSValue jsObj;
    QJSValue jsObjGlob;

    QString str;
    QStringList list;
    QByteArray byteArray;
    Page *page;

    int rc;

    void fcgx_accept_r();
};

#endif // ROUTERLISTEN_H
