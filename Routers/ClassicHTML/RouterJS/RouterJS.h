#ifndef ROUTERJS_H
#define ROUTERJS_H

#include "Router.h"
#include "Obj.h"

class RouterJS : public Router
{
public:
    RouterJS(Router* parent);
    RouterJS(QString root = "");

protected:
    bool route(FCGX_Request &req, QString url, Request *obj);
};

#endif // ROUTERJS_H
