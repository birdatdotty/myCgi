#ifndef ROUTE_H
#define ROUTE_H

#include <fcgi_stdio.h>

#include <QObject>
#include <QJSEngine>

#include "Obj.h"

#include <QMap>
#include <QFileSystemWatcher>

class Page;

class Router : public QObject
{
    Q_OBJECT
public:
    explicit Router(QString root, QObject *parent = nullptr);

private:
    QString root;
    QFileSystemWatcher* watcher;

    QJSEngine *engine;
    Obj *obj;
    QMap<QString, Page*> pages;

    QJsonObject str2json(QString str);

public slots:
    void fileChanged(const QString& path);
    void request(FCGX_Request &req);

signals:
};

#endif // ROUTE_H
