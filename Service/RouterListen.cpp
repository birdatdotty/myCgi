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
    initEngine();
}

void RouterListen::initEngine()
{
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
#ifdef DEBUG
        qInfo("Try to accept new request");
#endif
        mutex.lock();
        rc = FCGX_Accept_r(&FCGIReq->request);
        mutex.unlock();

        QString url = FCGIReq->clearUrl();

        for (Router *route: router) {
            if (route->startWith(url)) {
                if (url.endsWith('/'))
                    url += route->getDefaultPage();

                QJSEngine engine;
                QString s;
                QStringList list;

                request = new Request(*FCGIReq, objGlob);
                QJSValue jsObj = engine.newQObject(request);
                QJSValue jsObjGlob = engine.newQObject(objGlob);

                engine.globalObject().setProperty("Obj", jsObj);
                engine.globalObject().setProperty("GlobObj", jsObjGlob);


                Page *page = route->route(*FCGIReq, url);
//                FCGIReq->send(page);
                QByteArray byteArray;
                byteArray += page->contentType();
                byteArray += "\n\n";
                FCGX_PutStr(byteArray, byteArray.size(), FCGIReq->out());

                list = page->out(&engine);
                for (int i = 0; i < list.size(); i++) {
                    if ((i & 1) == 0)
                        s = list.at(i);
                    else
                        s = engine.evaluate(list.at(i)).toString();

                    FCGX_PutStr(s.toUtf8(), s.toUtf8().size(), FCGIReq->out());
                }

                FCGX_Finish_r(&FCGIReq->request);

                break;
            }
        }
//        delete engine;
//        engine->deleteLater();
//        initEngine();
    }
}
