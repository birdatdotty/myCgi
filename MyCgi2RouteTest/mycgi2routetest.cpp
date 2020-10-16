#include "mycgi2routetest.h"

MyCgi2RouteTest::MyCgi2RouteTest(Router *parent): Router(parent) {}
MyCgi2RouteTest::MyCgi2RouteTest(QString root): Router(root) {}

bool MyCgi2RouteTest::route(FCGX_Request &req, QString /*url*/, Obj *obj)
{
    QByteArray pageOut = "Content-type: text/html\n\n"
                         "bool MyCgi2RouteTest::route(FCGX_Request &req, QString url, Obj */*obj*/)";

//    pageOut += obj->chunk("/chunks/html/index.chunk");
    pageOut += QString::number(obj->globCount());

    FCGX_PutStr(pageOut, pageOut.size(), req.out);
    FCGX_Finish_r(&req);

    return true;
}
