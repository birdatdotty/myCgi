#ifndef ROUTE_H
#define ROUTE_H

#include <fcgi_stdio.h>

#include <QObject>
#include <QJSEngine>

#include "Request.h"

#include <QMap>
#include <QFileSystemWatcher>
#include <QQmlListProperty>

#include "QMLTree.h"
#include "Page.h"
#include "Chunk.h"

class Router : public QMLTree
{
    Q_OBJECT
    Q_PROPERTY(QString  url
               READ getUrl
               WRITE setUrl
               NOTIFY sigUrl)

    Q_PROPERTY(QString  root
               READ getRoot
               WRITE setRoot
               NOTIFY sigRoot)

    Q_PROPERTY(ObjGlob* objGlob
               READ getObjGlob
               WRITE setObjGlob
               NOTIFY sigObjGlob)

    Q_PROPERTY(QString  defaultPage
               READ getDefaultPage
               WRITE setDefaultPage
               NOTIFY sigDefaultPage)


public:
    explicit Router(QString root = "", QObject *parent = nullptr);
    explicit Router(Router& parent);

    void setRoot(QString newRoot);
    QString getRoot() const;

    void setUrl(QString newUrl);
    QString getUrl() const;

    void setDefaultPage(QString newDefaultPage);
    QString getDefaultPage();

    void setObjGlob(ObjGlob* newObj);
    ObjGlob* getObjGlob() const;

signals:
    void rootChanged();
    void urlChanged();

protected:
    QString root;
    QString m_url;
    QFileSystemWatcher* m_pageWatcher;
    QMap<QString, Page*> m_pages;
    Router* m_router;

protected:
    explicit Router(Router* router);
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
    void setPostData(FCGX_Request &req, Request *obj);

    // routes:
    virtual bool route(FCGX_Request &req, QString url, Request *obj);

public slots:
    void pageChanged(const QString& path);
    void request(FCGX_Request &req);

private:
    Router* select(QString url, QString method);
    ObjGlob* m_globObject;
    QString m_defaultPage;

signals:
    void sigDefaultPage();
    void sigUrl();
    void sigRoot();
    void sigObjGlob();
};

#endif // ROUTE_H
