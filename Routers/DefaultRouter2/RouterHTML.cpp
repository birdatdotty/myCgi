#include "RouterHTML.h"

#include "Page.h"
#include "Chunk.h"
#include "FCGIRequest.h"
#include "Service.h"

#ifdef DEBUG
    #include <QDateTime>
    #include <QDebug>
    #include <iostream>
#endif


RouterHTML::RouterHTML(Router *parent)
    : Router(parent),
      m_pageWatcher(new QFileSystemWatcher),
      pageType(Page::HTML)
{
    connect(m_pageWatcher, &QFileSystemWatcher::fileChanged,
            this, &RouterHTML::pageChanged);
}

RouterHTML::RouterHTML(QString root)
    : m_pageWatcher(new QFileSystemWatcher),
      pageType(Page::HTML)
{
    connect(m_pageWatcher, &QFileSystemWatcher::fileChanged,
            this, &RouterHTML::pageChanged);
}

Page *RouterHTML::route(FCGIRequest &req, QString url)
{
    Page *page;
    page = getPage(url.toUtf8());

    return page;
}

Page *RouterHTML::getPage(const char *url)
{
#ifdef DEBUG
    qInfo() << "\n    Page *RouterHTML::getPage(" << url << ")";
    qInfo() << m_pages;
#endif
    Page *page;
    if (!m_pages.contains(url)) {
#ifdef DEBUG
    qInfo() << "if (!m_pages.contains(url))";
#endif
        QString file = root + url;
        page = new Page(root, url, pageType);
        if (QFile::exists(file)) {
            m_pageWatcher->addPath( file );
            m_pages[url] = page;
        }
    }
    else
        page = m_pages[url];

    return page;
}

void RouterHTML::pageChanged(const QString &path)
{
    if (!path.startsWith(root))
        return;

    QString key = path;
    key = key.remove(0, root.size());

#ifdef DEBUG
    qInfo() << "\n    void RouterHTML::pageChanged(const QString &path)";
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

