#include "RouterListen.h"

RouterListen::RouterListen(FCGX_Request &request, Router* router, QObject *parent)
    : QThread(parent),
      request(request),
      router(router)
{
}

void RouterListen::run() {
    while(FCGX_Accept_r(&request) == 0)
        router->request(request);
}
