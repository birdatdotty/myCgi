#ifndef MYCGI2ROUTETEST_H
#define MYCGI2ROUTETEST_H

#include "Router.h"
#include "Obj.h"

class MyCgi2RouteTest : public Router
{
    Q_OBJECT
public:
    MyCgi2RouteTest(Router* parent);
    MyCgi2RouteTest(QString root = "");

protected:
    bool route(FCGX_Request &req, QString, Obj *obj);
};

#endif // MYCGI2ROUTETEST_H
