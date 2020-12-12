#ifndef ROUTERJS_H
#define ROUTERJS_H

#include "Router.h"

class RouterJS : public Router
{
public:
    RouterJS(Router* parent);
    RouterJS(QString root = "");

    virtual Page* route(FCGIRequest &req, QString url);
};

#endif // ROUTERJS_H
