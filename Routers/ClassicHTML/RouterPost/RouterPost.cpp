#include "RouterPost.h"

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif



bool RouterPost::route(FCGX_Request &req, QString /*url*/, Request */*obj*/)
{
    #ifdef DEBUG
        qInfo() << "bool RouterPost::route(FCGX_Request &req, QString url, Obj *obj)";
    #endif
    FCGX_PutS("Content-type: text/html\n\nOK", req.out);
    FCGX_Finish_r(&req);

    return true;
}
