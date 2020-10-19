#ifndef ROUTERJS_H
#define ROUTERJS_H

#include "Router.h"

class RouterJS : public Router
{
public:
    RouterJS(Router* parent);
    RouterJS(QString root = "");

protected:
    bool route(FCGX_Request &req, QString url, Obj *obj);
};

#endif // ROUTERJS_H
