#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QQuickItem>

#include <QQmlListProperty>
#include "Router.h"

#include <QDebug>

class Service : public QQuickItem
{
    Q_OBJECT
// ![0]
    Q_PROPERTY(QString cgi READ cgi WRITE setCgi NOTIFY sigCgi)
    Q_PROPERTY(QString root READ root WRITE setRoot NOTIFY sigRoot)
    Q_PROPERTY(QString defaultPage READ getDefaultPage WRITE setDefaultPage NOTIFY sigDefaultPage)
    Q_PROPERTY(int queue READ queue WRITE setQueue NOTIFY sigQueue)
    Q_PROPERTY(QQmlListProperty<Router> routes READ routes)
    Q_CLASSINFO("DefaultProperty", "routes")
// ![0]
public:
    Service(QQuickItem *parent = nullptr);

    QString cgi() const;
    void setCgi(QString str);

    QString root() const;
    void setRoot(QString newRoot);

    int queue() const;
    void setQueue(int newQueue);

    QQmlListProperty<Router> routes();
    int routeCount() const;
    Router *route(int) const;

    Router* mainRouter();

    void setDefaultPage(QString newDefaultPage);
    QString getDefaultPage();


protected:
    void componentComplete();

private:
    QString m_host;
    QString m_root;
    QString m_defaultPage;
    int m_queue;
    Router* m_mainRouter;
    QList<Router *> m_routes;

signals:
    void sigDefaultPage();
    void sigCgi();
    void sigRoot();
    void sigQueue();
};


#endif // SERVICE_H
