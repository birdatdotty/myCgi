#ifndef ROUTE_H
#define ROUTE_H

#include <fcgi_stdio.h>

#include <QObject>
#include <QJSEngine>

#include "Obj.h"

#include <QMap>
#include <QFileSystemWatcher>

class Page;
class Chunk;

class Router : public QObject
{
    Q_OBJECT
public:
    explicit Router(QString root, QObject *parent = nullptr);
    QString chunk(QString key);
    QString getChunk(QString url);

protected:
    QString root;
    QFileSystemWatcher* pageWatcher;
    QMap<QString, Page*> pages;
    QMap<QString, Chunk*> chunks;
    QMap<QString, Router*> routes;

protected:
    explicit Router(Router* router) {}
    QJsonObject str2json(QString str);

    Page* getPage(const char *url);

    // select route
    // parse request:
    const char *method(FCGX_Request &req);
    const char *uri(FCGX_Request &req);
    const char *url(FCGX_Request &req);
    const char *getData(FCGX_Request &req);
    const char *contentType(FCGX_Request &req);
    int contentLength(FCGX_Request &req);
    void setPostData(FCGX_Request &req, Obj *obj);

    // routes:
//    bool routePost(FCGX_Request &req, QString /*url*/, Obj* obj);
//    bool routeDefault(FCGX_Request &req, const char* url, Obj* obj);
//    bool routeJs(FCGX_Request &req, QString url, Obj* obj);
    virtual bool route(FCGX_Request &req, QString url, Obj *obj);

public slots:
    void pageChanged(const QString& path);
    void request(FCGX_Request &req);
    void addRoute(Router* route) {}

private:
    Router* select(QString url, QString method);

signals:
};

#endif // ROUTE_H
