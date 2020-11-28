#include "Router.h"
#include "Page.h"
#include "Chunk.h"
#include "FCGIRequest.h"
#include "Service.h"

#include <QFile>

#ifdef DEBUG
    #include <QDateTime>
    #include <QDebug>
    #include <iostream>
#endif

Router::Router(QString root, QObject *parent)
    : QMLTree(parent),
      root(root),
      m_pageWatcher(new QFileSystemWatcher(this))
{
    connect(m_pageWatcher, &QFileSystemWatcher::fileChanged,
            this, &Router::pageChanged);
}

Router::Router(Router &parent)
    : root(parent.root)
{
#ifdef DEBUG
    qInfo() << "\n    Router::Router(Router &parent)";
#endif
}

Router::Router(Router *router)
    : root(router->root)
{
}

Page* Router::request(FCGIRequest &req)
{
//    Request *obj = new Request(req, m_globObject);

#ifdef DEBUG
    qInfo() << "\n    " << QDateTime::currentDateTime().time().toString() << "\n-------";
    qInfo() << "request:";
#endif

    QString _method = req.method();
    QString _url = req.url(this);

#ifdef DEBUG
    qInfo() << "_method:" << _method;
    qInfo() << "_url:" << _url;
#endif

    return select(_url, _method)->route(req, _url);
}

Router *Router::select(QString url, QString method)
{
#ifdef DEBUG
    qInfo() << "\n    Router *Router::select(QString url, QString method)";
#endif
    for (Router *route: _routes) {
        if (url.startsWith(route->getUrl())) {
#ifdef DEBUG
    qInfo() << "OK:" << url << route;
#endif
    return route;
        }
#ifdef DEBUG
        else {
            qInfo() << "NOT:" << url;
        }
#endif
    }

    return this;
}


Page *Router::getPage(const char *url) {
#ifdef DEBUG
    qInfo() << "\n    Page *Router::getPage(" << url << ")";
    qInfo() << m_pages;
#endif
    Page *page;
    if (!m_pages.contains(url)) {
#ifdef DEBUG
    qInfo() << "if (!m_pages.contains(url))";
#endif
        QString file = root + url;
        page = new Page(root, url);
        if (QFile::exists(file)) {
            m_pageWatcher->addPath( file );
            m_pages[url] = page;
        }
    }
    else
        page = m_pages[url];

    return page;
}

void Router::setRoot(QString newRoot) { root = newRoot; }
QString Router::getRoot() const { return root; }

void Router::setUrl(QString newUrl) { m_url = newUrl; }
QString Router::getUrl() const { return m_url; }

void Router::setDefaultPage(QString newDefaultPage) { m_defaultPage = newDefaultPage; }
QString Router::getDefaultPage() const { return m_defaultPage; }

void Router::setObjGlob(ObjGlob *newObj) { m_globObject = newObj; }
ObjGlob *Router::getObjGlob() const { return m_globObject; }

void Router::updateService(Service *newService) {
    service = newService;
    int childrensCount = routerCount();
    for (int i = 0; i < childrensCount; i++)
        router(i)->updateService(newService);
}


Page *Router::route(FCGIRequest &req, QString url)
{
#ifdef DEBUG
    qInfo() << "_routes:" << _routes;
    for(Router* router: _routes)
        qInfo() << router << router->getUrl();
#endif

    Page *page;
    page = getPage(url.toUtf8());

    return page;
}


void Router::pageChanged(const QString &path) {
    if (!path.startsWith(root))
        return;

    QString key = path;
    key = key.remove(0, root.size());

#ifdef DEBUG
    qInfo() << "\n    void Router::pageChanged(const QString &path)";
    qInfo() << "request: ";
    qInfo() << "path: [" + path + "]";
    qInfo() << "key: [" + key + "]";
#endif


    if (m_pages.contains(key)) {
        m_pages.remove(key);
        m_pageWatcher->removePath(path);
#ifdef DEBUG
    qInfo() << path + " removed";
#endif
    }
}


