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
      pageType(Page::HTML)
{}

Router::Router(Router &parent)
    : root(parent.root),
      pageType(Page::HTML)
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

//    return select(_url, _method)->route(req, _url);
    return route(req, _url);
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
    static Page *page = new Page(Page::HTML, "NOT ROUTE");
//    page = getPage(url.toUtf8());

    return page;
}


