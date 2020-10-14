#ifndef ROUTERCSS_H
#define ROUTERCSS_H

#include "Router.h"

class RouterCSS : public Router
{
public:
//    RouterCSS(Router* parent = nullptr): Router(parent), cssWatcher(new QFileSystemWatcher) {/*root=parent->root;*/}
    RouterCSS(Router* parent);
    RouterCSS(QString root = "");


protected:
    bool route(FCGX_Request &req, QString url, Obj *obj);

private:
    QFileSystemWatcher* cssWatcher;
    bool read(QString file);
    QString out() const;
    bool sass(QString &file);
    bool css(QString &file);

    QString cssFile;
};

#endif // ROUTERCSS_H
