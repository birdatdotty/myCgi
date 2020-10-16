#ifndef ROUTE_H
#define ROUTE_H

#include <fcgi_stdio.h>

#include <QObject>
#include <QJSEngine>

#include "Obj.h"

#include <QMap>
#include <QFileSystemWatcher>
#include <QQmlListProperty>

#include "QMLTree.h"

class Page;
class Chunk;

class Router : public QMLTree
{
    Q_OBJECT
    Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY sigUrl)
    Q_PROPERTY(QString root READ getRoot WRITE setRoot NOTIFY sigRoot)
    Q_PROPERTY(QString defaultPage READ getDefaultPage WRITE setDefaultPage NOTIFY sigDefaultPage)

public:
    explicit Router(QString root = "", QObject *parent = nullptr);
    explicit Router(Router& parent);
    QString chunk(QString key);
    QString getChunk(QString url);

    void setRoot(QString newRoot) {
        root = newRoot;
    }
    QString getRoot() const {
        return root;
    }

    void setUrl(QString newUrl) {
        m_url = newUrl;
    }
    QString getUrl() const {
        return m_url;
    }

    void setDefaultPage(QString newDefaultPage) {
        m_defaultPage = newDefaultPage;
    }
    QString getDefaultPage() {
        return m_defaultPage;
    }


signals:
    void rootChanged();
    void urlChanged();

protected:
    QString root;
    QString m_url;
    QFileSystemWatcher* m_pageWatcher;
    QFileSystemWatcher* m_chunkWatcher;
    QMap<QString, Page*> m_pages;
    QMap<QString, Chunk*> m_chunks;
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
    void setPostData(FCGX_Request &req, Obj *obj);

    // routes:
    virtual bool route(FCGX_Request &req, QString url, Obj *obj);

public slots:
    void pageChanged(const QString& path);
    void chunkChanged(const QString& path);
    void request(FCGX_Request &req);

private:
    Router* select(QString url, QString method);
    QString m_defaultPage;

signals:
    void sigDefaultPage();
    void sigUrl();
    void sigRoot();
};

#endif // ROUTE_H
