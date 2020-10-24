#ifndef ROUTERPOST_H
#define ROUTERPOST_H

#include "Router.h"

class RouterPost : public Router
{
public:
    RouterPost(Router* parent): Router(parent) {}
    RouterPost(QString root = ""): Router(root) {}

protected:
    bool route(FCGX_Request &req, QString url, Request *obj);
};

#endif // ROUTERPOST_H
