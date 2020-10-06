#ifndef ROUTERPOST_H
#define ROUTERPOST_H

#include "Router.h"

class RouterPost : public Router
{
public:
    RouterPost(Router *parent);

protected:
    bool route(FCGX_Request &req, QString url, Obj *obj);
};

#endif // ROUTERPOST_H
