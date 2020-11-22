#ifndef SERVICE1_H
#define SERVICE1_H

#include <QMutex>
#include <QObject>
#include <QQuickItem>

#include <QQmlListProperty>
#include "Router.h"

#include <QDebug>

#include "FCGIRequest.h"
#include "RouterListen.h"

class QJSEngine;

class Service : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString cgi
               READ cgi
               WRITE setCgi
               NOTIFY sigCgi)

    Q_PROPERTY(QString root
               READ root
               WRITE setRoot
               NOTIFY sigRoot)

    Q_PROPERTY(int queue
               READ queue
               WRITE setQueue
               NOTIFY sigQueue)

    Q_PROPERTY(int threads
               READ getThreads
               WRITE setThreads)

    Q_PROPERTY(ObjGlob* objGlob
               READ getObjGlob
               WRITE setObjGlob)

    Q_PROPERTY(QQmlListProperty<Router> routes
               READ routes)

    Q_CLASSINFO("DefaultProperty", "routes")

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

    void setObjGlob(ObjGlob* newObj);
    ObjGlob* getObjGlob() const;

    int getThreads() const { return threads; }
    void setThreads(int newThreads) { threads = newThreads; }

protected:
    void componentComplete();

private:
    QString m_host;
    QString m_root;
    QString m_defaultPage;
    int m_queue;
    Router* m_mainRouter;
    QList<Router *> m_routes;
    ObjGlob* m_globObject;

    int socketId;
    int threads;
    QMutex mutex;

signals:
    void sigDefaultPage();
    void sigCgi();
    void sigRoot();
    void sigQueue();
};


#endif // SERVICE1_H
