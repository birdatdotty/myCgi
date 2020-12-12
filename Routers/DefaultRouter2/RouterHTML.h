#ifndef ROUTERHTML_H
#define ROUTERHTML_H

#include "Router.h"

#include <QMap>

class RouterHTML : public Router
{
public:
    RouterHTML(Router* parent);
    RouterHTML(QString root = "");

    virtual Page* route(FCGIRequest &req, QString url);

protected:
    Page* getPage(const char *url);

public slots:
    void pageChanged(const QString &path);

private:
    QFileSystemWatcher* m_pageWatcher;
    QMap<QString, Page*> m_pages;
    Page::TYPE pageType;
};
#endif // ROUTERHTML_H
