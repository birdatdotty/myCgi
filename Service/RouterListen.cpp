#include "RouterListen.h"

RouterListen::RouterListen(QString path, int listenQueueBacklog, QList<Router *> router, QObject *parent)
    : QThread(parent),
      router(router)
{
    //Глубина стека запросов
    int listen_socket = FCGX_OpenSocket(path.toUtf8(), listenQueueBacklog);
    FCGX_InitRequest(&request, listen_socket, 0);
}

void RouterListen::run() {
    while(FCGX_Accept_r(&request) == 0) {
        const char* url = FCGX_GetParam("DOCUMENT_URI", request.envp);
        FCGIRequest FCGIReq(request);
        for (Router *route: router) {
            if (route->startWith(url)) {
                route->request(FCGIReq);
                break;
            }
        }
    }
}
