#ifndef ROUTERCHUNK_H
#define ROUTERCHUNK_H

#include "RouterHTML.h"

class RouterChunk : public RouterHTML
{
public:
    RouterChunk(Router* parent): RouterHTML(parent) {}
    RouterChunk(QString root = ""): RouterHTML(root) {}

    virtual Page* route(FCGIRequest &req, QString url);

private:
    QMap<QString,Page*> pages;
};

#endif // ROUTERCHUNK_H
