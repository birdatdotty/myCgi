#ifndef ROUTERJS_H
#define ROUTERJS_H

#include "Router.h"

class RouterJS : public Router
{
public:
    RouterJS(Router* parent);
    RouterJS(QString root = "");

protected:
    virtual bool route(FCGIRequest &req, QString url, Request *obj);
};

#endif // ROUTERJS_H
