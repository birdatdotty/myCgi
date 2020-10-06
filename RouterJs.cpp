#include "RouterJs.h"

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif


RouterJs::RouterJs(Router *parent)
    : Router(parent)
{

}

bool RouterJs::route(FCGX_Request &req, QString url, Obj */*obj*/)
{
#ifdef DEBUG
    qInfo() << "bool RouterJs::route(FCGX_Request &req, QString url, Obj *obj)";
#endif
    QByteArray pageOut = "Content-type: application/javascript\n\n";
    if (url.startsWith("/js/header.js")) {
        pageOut += "console.log('/js/header.js')";
    }

    // Завершаем запрос
    // DLLAPI int FCGX_PutStr(const char *str, int n, FCGX_Stream *stream);
    // DLLAPI int FCGX_FPrintF(FCGX_Stream *stream, const char *format, ...);
    // ...
    FCGX_PutStr(pageOut, pageOut.size(), req.out);
    FCGX_Finish_r(&req);

    return true;
}
