#include "RouterJS.h"

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif


RouterJS::RouterJS(Router *parent): Router(parent) {}
RouterJS::RouterJS(QString root): Router(root) {}

bool RouterJS::route(FCGX_Request &req, QString url, Request */*obj*/)
{
#ifdef DEBUG
    qInfo() << "bool RouterJS::route(FCGX_Request &req, QString url, Obj *obj)";
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
