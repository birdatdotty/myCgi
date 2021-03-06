#include "Router.h"
#include "Page.h"
#include "Chunk.h"
#include "utils.h"
#include "FCGIRequest.h"

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

void Router::request(FCGX_Request &req)
{
//    Obj *obj = new Obj(this);
    FCGIRequest FCGIReq(req);
    Request *obj = new Request(req, m_globObject);

#ifdef DEBUG
    std::cout << "\n" << QDateTime::currentDateTime().time().toString().toStdString() << "\n-------\n";
//    qInfo() << "Obj.url():" << obj->url();
    qInfo() << "request:";
#endif
    // https://developer.mozilla.org/ru/docs/Web/HTTP/Methods
    // GET, POST, maybe PUT, DELETE, HEAD, CONNECT, OPTIONS, TRACE, PATCH
//    const char *_method = method(req);
    QString _method = FCGIReq.method();
    /// url: /index.dsfsd
//    QString _url = url(req);
    QString _url = FCGIReq.url();

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


QJsonObject Router::str2json(QString str)
{
    QJsonObject obj;
    /// str: login=asd&pass=dd
    bool isKey = true;
    QString key, value;

    for (int i = 0; i < str.size(); i++) {
        QChar ch = str.at(i);
        if (isKey) {
            if (ch != '=') key += ch;
            else isKey = false;
        }
        else {
            if (ch != '&') value += ch;
            else {
                isKey = true;
                obj[key] = value;
                key = value = "";
            }
        }
    }
    if (key.size() > 0)
        obj[key] = value;

    return obj;
}

Page *Router::getPage(const char *url) {
    Page *page;
    if (!m_pages.contains(url)) {
        QString file = root + url;
        page = new Page(root, url);
        if (QFile::exists(file)) {
            m_pageWatcher->addPath( file );
            m_pages[url] = page;

        }
    }
    else page = m_pages[url];

    return page;
}

#include <QDebug>
void Router::updateGlobObj(ObjGlob *newGlobObject) {
    qInfo() << "void Router::updateGlobObj(ObjGlob *newGlobObject)";
    m_globObject = newGlobObject;
    int childrensCount = routerCount();
    for (int i = 0; i < childrensCount; i++)
        router(i)->updateGlobObj(newGlobObject);
}

void Router::setRoot(QString newRoot) { root = newRoot; }
QString Router::getRoot() const { return root; }

void Router::setUrl(QString newUrl) { m_url = newUrl; }
QString Router::getUrl() const { return m_url; }

void Router::setDefaultPage(QString newDefaultPage) { m_defaultPage = newDefaultPage; }
QString Router::getDefaultPage() { return m_defaultPage; }

void Router::setObjGlob(ObjGlob *newObj) { m_globObject = newObj; }
ObjGlob *Router::getObjGlob() const { return m_globObject; }


bool Router::route(FCGX_Request &req, QString url, Request *obj)
{
#ifdef DEBUG
    qInfo() << "bool Router::route(FCGX_Request &req, QString url, Obj *obj)";
    qInfo() << "root:" << root;
    qInfo() << "_routes:" << _routes;
    for(Router* router: _routes)
        qInfo() << router << router->getUrl();
#endif
    for(Router* it: _routes)
        if (url.startsWith(it->getUrl()))
            return it->route(req, url, obj);

    setPostData(req, obj);
    Page *page;
    if (url == "/")
        url = m_defaultPage;

    page = getPage(url.toUtf8());

    QJsonObject json = str2json(getData(req));
//    QJsonObject data;
//    data["page"] = uri(req);
//    data["method"] = method(req);
//    data["get"] = getData(req);
//    data["url"] = url;

//    obj->set(data);
    QByteArray pageOut = page->out(getObjGlob(), obj).toUtf8();
    m_globObject->out(page, obj);

    // Завершаем запрос
    // DLLAPI int FCGX_PutStr(const char *str, int n, FCGX_Stream *stream);
    // DLLAPI int FCGX_FPrintF(FCGX_Stream *stream, const char *format, ...);
    // ...
    FCGX_PutStr(pageOut, pageOut.size(), req.out);
    FCGX_Finish_r(&req);

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


