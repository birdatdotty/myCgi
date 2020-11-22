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

    FCGIRequest *FCGIReq;
    void setEngine(QJSEngine* newEngine) {
        engine = newEngine;
        FCGIReq->setEngine(newEngine);
    }
    void initEngine();


protected:
    void run() override;

private:
    QMutex &mutex;
    QString path;
    int listenQueueBacklog;
    int socketId;
    QList<Router *> router;
    ObjGlob* objGlob;
//    FCGIRequest *request;
    FCGX_Request fcgx_request;
    QJSEngine* engine;
    Request *request;


    int rc;
};

#endif // ROUTERLISTEN_H
