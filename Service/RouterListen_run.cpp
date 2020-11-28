#include "RouterListen.h"
//#include "FCGIRequest.h"

#include <QDebug>
void RouterListen::run() {
    FCGX_InitRequest(&FCGIReq.request, socketId, 0);

    while(true) fcgx_accept_r();
}

void RouterListen::fcgx_accept_r()
{
    //попробовать получить новый запрос
#ifdef DEBUG
    qInfo("Try to accept new request");
#endif
    mutex.lock();
    rc = FCGX_Accept_r(&FCGIReq.request);
    mutex.unlock();

    QString url = FCGIReq.clearUrl();

    for (Router *route: router) {
        if (route->startWith(url)) {
            request->setRouter(route);
            if (url.endsWith('/'))
                url += route->getDefaultPage();

            page = route->route(FCGIReq, url);

            byteArray = page->contentType().toUtf8();
            FCGX_PutStr(byteArray, byteArray.size(), FCGIReq.out());
            FCGX_PutStr("\n\n", 2, FCGIReq.out());

            list = page->out(&engine);
            for (int i = 0; i < list.size(); i++) {
                str = list.at(i);

                if ((i & 0x1) == 1)
                    FCGX_PutStr(request->eng(str).toUtf8(), request->eng(str).toUtf8().size(), FCGIReq.out());
                else
                    FCGX_PutStr(str.toUtf8(), str.toUtf8().size(), FCGIReq.out());
            }
            break;
        }
    }
    FCGX_Finish_r(&FCGIReq.request);

}
