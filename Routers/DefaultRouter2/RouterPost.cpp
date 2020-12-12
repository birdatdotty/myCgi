#include "RouterPost.h"

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif

RouterPost::RouterPost(Router *parent): Router(parent) {}
RouterPost::RouterPost(QString root): Router(root) {}

Page *RouterPost::route(FCGIRequest &req, QString url) {
    Page* p = new Page(Page::JSON, "{\"page\":333,\"url\":\"" + url +"\"}");


//    return true;
    return p;
}
