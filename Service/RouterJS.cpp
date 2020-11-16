#include "RouterJS.h"

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif


RouterJS::RouterJS(Router *parent): Router(parent) {}
RouterJS::RouterJS(QString root): Router(root) {}

bool RouterJS::route(FCGIRequest &req, QString /*url*/, Request */*obj*/) {
    Page* p = new Page(Page::JS, "console.log('bool RouterJS::route(FCGIRequest &req, QString url, Request *obj)')\n\n");

    req.send(p);

    return true;
}
