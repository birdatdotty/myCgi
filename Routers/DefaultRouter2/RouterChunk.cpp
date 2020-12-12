#include "RouterChunk.h"

#include <QDebug>
Page *RouterChunk::route(FCGIRequest &req, QString url)
{
    qInfo() << "Page *RouterChunk::route(FCGIRequest &req, QString url)";
    Page *page;
    qInfo() << "url:" << url;
    qInfo() << "getUrl():" << getUrl();
    qInfo() << url.mid(getUrl().size() - 1);
    qInfo() << "Obj.chunk(/" + url.mid(getUrl().size() - 1) + ")";
//    page = getPage(url.mid(getUrl().size() - 1).toUtf8());
    if (!pages.contains(url)) {
        pages[url] = new Page(QStringList() <<
                        "" <<
                        "Obj.chunk(/" + url.mid(getUrl().size() - 1) + ")" <<
                        "");
    }

    return pages[url];
}
