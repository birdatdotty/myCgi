#include "Router.h"
#include "Page.h"
#include "Chunk.h"
#include "utils.h"

#include <QFile>

#ifdef DEBUG
    #include <QDateTime>
    #include <QDebug>
    #include <iostream>
#endif

#include "RouterJs.h"
#include "RouterPost.h"

Router::Router(QString root, QObject *parent)
    : QMLTree(parent),
      root(root),
      m_pageWatcher(new QFileSystemWatcher(this)),
      m_chunkWatcher(new QFileSystemWatcher(this))
{
    connect(m_pageWatcher, &QFileSystemWatcher::fileChanged,
            this, &Router::pageChanged);
    connect(m_chunkWatcher, &QFileSystemWatcher::fileChanged,
            this, &Router::chunkChanged);
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

QString Router::chunk(QString key) {
    return "Router::chunk " + key;
}

//QString Router::chunk(QString key)
//{
//    QString ret = "QString Router::chunk(QString key):" + key;
//    return ret;
//}

void Router::request(FCGX_Request &req)
{
    Obj *obj = new Obj(this);

#ifdef DEBUG
    std::cout << "\n" << QDateTime::currentDateTime().time().toString().toStdString() << "\n-------\n";
    qInfo() << "request:";
#endif
    // https://developer.mozilla.org/ru/docs/Web/HTTP/Methods
    // GET, POST, maybe PUT, DELETE, HEAD, CONNECT, OPTIONS, TRACE, PATCH
    const char *_method = method(req);
    /// url: /index.dsfsd
    QString _url = url(req);

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
    qInfo() << "OK:" << url;
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

QString Router::getChunk(QString url)
{
    Chunk* _chunk;
    if (!m_chunks.contains(url)) {
        QString file = root + url;
        _chunk = new Chunk(root, url);
        if (QFile::exists(file)) {
            m_chunkWatcher->addPath( file );
            m_chunks[url] = _chunk;
#ifdef DEBUG
    qInfo() << "chunkWatcher->files():" << m_chunkWatcher->files();
#endif
        }
    }
    else _chunk = m_chunks[url];

    return _chunk->out();
}


bool Router::route(FCGX_Request &req, QString url, Obj *obj)
{
#ifdef DEBUG
    qInfo() << "bool Router::route(FCGX_Request &req, QString url, Obj *obj)";
    qInfo() << "root:" << root;
    qInfo() << "_routes:" << _routes;
    for(Router* router: _routes)
        qInfo() << router << router->getUrl();
#endif
    for(Router* it: _routes)
        if (url.startsWith(it->getUrl())) return it->route(req, url, obj);

    setPostData(req, obj);
    Page *page;
    if (url == "/")
        url = m_defaultPage;

    page = getPage(url.toUtf8());

    QJsonObject json = str2json(getData(req));
    QJsonObject data;
    data["page"] = uri(req);
    data["method"] = method(req);
    data["get"] = getData(req);
    data["url"] = url;

    obj->set(data);
    QByteArray pageOut = page->out(obj).toUtf8();

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

void Router::chunkChanged(const QString &path)
{
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
        m_chunks.remove(key);
        m_chunkWatcher->removePath(path);
#ifdef DEBUG
    qInfo() << path + " removed";
#endif
    }
}
