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

Page *RouterCSS::route(FCGIRequest &req, QString url)
{
    read(root + url);

    Page* cssPage = new Page(Page::CSS, out(root + url));
//    req.send(cssPage);

//    return true;
    return cssPage;
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
