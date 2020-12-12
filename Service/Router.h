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
#include "ObjGlob.h"

class Service;

class Router: public QMLTree
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

    Q_PROPERTY(Page::TYPE type
               READ getTypePage
               WRITE setTypePage
               NOTIFY sigTypePage)

public:
    explicit Router(QString root = "", QObject *parent = nullptr);
    explicit Router(Router& parent);

    bool startWith(QString path) {
        return path.startsWith(m_url);
    }

    void setRoot(QString newRoot);
    QString getRoot() const;

    void setUrl(QString newUrl);
    QString getUrl() const;

    void setDefaultPage(QString newDefaultPage);
    QString getDefaultPage() const;

    void setObjGlob(ObjGlob* newObj);
    ObjGlob* getObjGlob() const;

    void setTypePage(Page::TYPE newPageType) {
        pageType = newPageType;
    }
    Page::TYPE getTypePage() {
        return pageType;
    }

    virtual void updateService(Service* newService);

signals:
    void rootChanged();
    void urlChanged();


protected:
    QString root;
    QString m_url;
    Router* m_router;

protected:
    explicit Router(Router* router);

    Page* getPage(const char *url);

public:
    virtual Page* route(FCGIRequest &req, QString url);

public slots:
    Page *request(FCGIRequest &req);

private:
    ObjGlob* m_globObject;
    QString m_defaultPage;
    Service* service;
    Page::TYPE pageType;

signals:
    void sigDefaultPage();
    void sigUrl();
    void sigRoot();
    void sigObjGlob();
    void sigTypePage();
};

#endif // ROUTE_H
