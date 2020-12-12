#ifndef ROUTERPOST_H
#define ROUTERPOST_H

#include "Router.h"

class RouterPost : public Router
{
public:
    RouterPost(Router* parent);
    RouterPost(QString root = "");

    virtual Page* route(FCGIRequest &req, QString url);
};

#endif // ROUTERPOST_H
