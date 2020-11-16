#include "RouterListen.h"

#include "FCGIRequest.h"

RouterListen::RouterListen(QMutex &mutex, int socketId, QList<Router *> router, ObjGlob *objGlob, QObject *parent)
    : QThread(parent),
      mutex(mutex),
      socketId(socketId),
      router(router),
      objGlob(objGlob)
{
    FCGIReq = new FCGIRequest();

    // QJSEngine:
    engine = new QJSEngine;

    request = new Request(*FCGIReq, objGlob);
    QJSValue jsObj = engine->newQObject(request);
    QJSValue jsObjGlob = engine->newQObject(objGlob);

    engine->globalObject().setProperty("Obj", jsObj);
    engine->globalObject().setProperty("GlobObj", jsObjGlob);

    FCGIReq->setEngine(engine);
}


void RouterListen::run() {
    FCGX_InitRequest(&FCGIReq->request, socketId, 0);

    for(;;)
    {
        //попробовать получить новый запрос
        qInfo("Try to accept new request");
        mutex.lock();
        rc = FCGX_Accept_r(&FCGIReq->request);
        mutex.unlock();

        QString url = FCGIReq->url();
        for (Router *route: router) {
            if (route->startWith(url)) {
                route->request(*FCGIReq);
                break;
            }
        }
    }
}
