#ifndef ROUTERCSS_H
#define ROUTERCSS_H

#include "Router.h"

#include <QMap>

class RouterCSS : public Router
{
public:
//    RouterCSS(Router* parent = nullptr): Router(parent), cssWatcher(new QFileSystemWatcher) {/*root=parent->root;*/}
    RouterCSS(Router* parent);
    RouterCSS(QString root = "");


protected:
    bool route(FCGX_Request &req, QString url, Request *obj);

private:
    QFileSystemWatcher* cssWatcher;
    bool read(QString file);
    QString out(QString file) const;

    bool css(QString &file);
    QMap<QString,QString> files;

    QString cssFile;
};

#endif // ROUTERCSS_H
