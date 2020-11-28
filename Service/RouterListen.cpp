#include "RouterListen.h"
//#include "FCGIRequest.h"

RouterListen::RouterListen(QMutex &mutex, int socketId, QList<Router *> router, ObjGlob *objGlob, QObject *parent)
    : QThread(parent),
      mutex(mutex),
      socketId(socketId),
      router(router),
      objGlob(objGlob),
      request(new Request(FCGIReq, objGlob))
{
    // QJSEngine:
    jsObj = engine.newQObject(request);
    jsObjGlob = engine.newQObject(objGlob);

    engine.globalObject().setProperty("Obj", jsObj);
    engine.globalObject().setProperty("GlobObj", jsObjGlob);
}
