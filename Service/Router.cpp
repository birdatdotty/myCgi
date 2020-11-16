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

Router::Router(Router &parent) {
    #ifdef DEBUG
        qInfo() << "Router::Router(Router &parent)";
    #endif
    root = parent.root;
}

Router::Router(Router *router) {
#ifdef DEBUG
    qInfo() << "Router::Router(Router *router)";
#endif
    root = router->root;
}

void Router::request(FCGIRequest &req)
{
//    Obj *obj = new Obj(this);
//    FCGIRequest FCGIReq(req);
    Request *obj = new Request(req, m_globObject);

#ifdef DEBUG
    std::cout << "\n" << QDateTime::currentDateTime().time().toString().toStdString() << "\n-------\n";
//    qInfo() << "Obj.url():" << obj->url();
    qInfo() << "request:";
#endif
    // https://developer.mozilla.org/ru/docs/Web/HTTP/Methods
    // GET, POST, maybe PUT, DELETE, HEAD, CONNECT, OPTIONS, TRACE, PATCH
//    const char *_method = method(req);
    QString _method = req.method();
    /// url: /index.dsfsd
//    QString _url = url(req);
    QString _url = req.url();

#ifdef DEBUG
    qInfo() << "_method:" << _method;
    qInfo() << "_url:" << _url;
#endif

    select(_url, _method)->route(req, _url, obj);
}

Router *Router::select(QString url, QString method)
{
    for (Router *route: _routes) {
        if (url.startsWith(route->getUrl())) {
#ifdef DEBUG
    qInfo() << __LINE__ << "Router *Router::select(QString url, QString method)";
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
    qInfo() << "Page *Router::getPage(const char *url)";
#endif
    Page *page;
    if (!m_pages.contains(url)) {
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
QString Router::getDefaultPage() { return m_defaultPage; }

void Router::setObjGlob(ObjGlob *newObj) { m_globObject = newObj; }
ObjGlob *Router::getObjGlob() const { return m_globObject; }

void Router::updateService(Service *newService) {
    service = newService;
    int childrensCount = routerCount();
    for (int i = 0; i < childrensCount; i++)
        router(i)->updateService(newService);
}


bool Router::route(FCGIRequest &req, QString url, Request *obj)
{
    FCGIRequest *FCGIReq = new FCGIRequest(req);
#ifdef DEBUG
    qInfo() << "bool Router::route(FCGX_Request &req, QString url, Obj *obj)";
    qInfo() << "root:" << root;
    qInfo() << "_routes:" << _routes;
    for(Router* router: _routes)
        qInfo() << router << router->getUrl();
#endif
//    for(Router* it: _routes)
//        if (url.startsWith(it->getUrl()))
//            return it->route(req, url, obj);

//    setPostData(FCGIReq, obj);
    Page *page;
//    if (url == "/")
//        url = m_defaultPage;

    page = getPage(url.toUtf8());

//    service->request(req, page);
    req.send(page);

    return true;

}


void Router::pageChanged(const QString &path) {
    if (!path.startsWith(root))
        return;

    QString key = path;
    key = key.remove(0, root.size());

#ifdef DEBUG
    std::cout << "request: " << std::endl;
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


