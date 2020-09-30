#include "RouterListen.h"

RouterListen::RouterListen(QString path, int listenQueueBacklog, Router* router, QObject *parent)
    : QThread(parent),
      router(router)
{
    //Глубина стека запросов
//    int listenQueueBacklog = 400;
    int listen_socket = FCGX_OpenSocket(path.toUtf8(), listenQueueBacklog);
    FCGX_InitRequest(&request, listen_socket, 0);
}

void RouterListen::run() {
    while(FCGX_Accept_r(&request) == 0)
        router->request(request);
}
