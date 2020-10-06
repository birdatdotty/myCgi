#ifndef ROUTERJS_H
#define ROUTERJS_H

#include "Router.h"

class RouterJs : public Router
{
public:
    RouterJs(Router* parent = nullptr);

protected:
    bool route(FCGX_Request &req, QString url, Obj *obj);

};

#endif // ROUTERJS_H
