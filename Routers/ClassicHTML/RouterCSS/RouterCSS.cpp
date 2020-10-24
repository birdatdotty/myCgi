#include "RouterCSS.h"

#include <QFile>
#include <QProcess>
#ifdef DEBUG
    #include <QDateTime>
    #include <QDebug>
#include <QFile>
#include <QProcess>
    #include <iostream>
#endif

RouterCSS::RouterCSS(Router *parent)
    : Router(parent),
      cssWatcher(new QFileSystemWatcher)
{}

RouterCSS::RouterCSS(QString root)
    : Router(root),
      cssWatcher(new QFileSystemWatcher)
{}

bool RouterCSS::route(FCGX_Request &req, QString url, Request */*obj*/)
{
#ifdef DEBUG
    qInfo() << "bool RouterCSS::route(FCGX_Request &req, QString url, Request *obj)";
#endif
    read(root + url);

    QByteArray pageOut = "Content-type: text/css\n\n";
    pageOut += out(root + url);
//    pageOut += obj->chunk("/style.css");

    // Завершаем запрос
    // DLLAPI int FCGX_PutStr(const char *str, int n, FCGX_Stream *stream);
    // DLLAPI int FCGX_FPrintF(FCGX_Stream *stream, const char *format, ...);
    // ...

    FCGX_PutStr(pageOut, pageOut.size(), req.out);
    FCGX_Finish_r(&req);

    return true;
}

bool RouterCSS::read(QString file)
{
#ifdef DEBUG
    qInfo() << "bool RouterCSS::read(QString file):" << root << file;
#endif
    if (!cssWatcher->files().contains(file)) {
        if (file.endsWith(".css"))
            RouterCSS::css(file);
        else
            return false;
    }

    return true;
}

QString RouterCSS::out(QString file) const {
    return files[file];
}

bool RouterCSS::css(QString &file)
{
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    files[file] = f.readAll();
    return true;
}
