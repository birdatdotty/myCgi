#ifndef ROUTERCSS_H
#define ROUTERCSS_H

#include "Router.h"

#include <QMap>

class RouterCSS : public Router
{
public:
    RouterCSS(Router* parent);
    RouterCSS(QString root = "");


protected:
    virtual bool route(FCGIRequest &req, QString url, Request *obj);

private:
    QFileSystemWatcher* cssWatcher;
    bool read(QString file);
    QString out(QString file) const;

    bool css(QString &file);
    QMap<QString,QString> files;

    QString cssFile;
};

#endif // ROUTERCSS_H
