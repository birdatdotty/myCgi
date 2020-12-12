#include "RouterJS.h"

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif


RouterJS::RouterJS(Router *parent): Router(parent) {}
RouterJS::RouterJS(QString root): Router(root) {}

Page *RouterJS::route(FCGIRequest &/*req*/, QString /*url*/) {
    Page* p = new Page(Page::JS, "console.log('bool RouterJS::route(FCGIRequest &req, QString url)')\n\n");


//    return true;
    return p;
}
