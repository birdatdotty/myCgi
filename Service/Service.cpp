#include "RouterListen.h"
#include "Service.h"

#ifdef DEBUG
    #include <QDebug>
#include <Router.h>
    #include <iostream>
#endif

Service::Service(QQuickItem *parent)
: QQuickItem(parent)
{
}

QString Service::cgi() const
{
    return m_host;
}

void Service::setCgi(QString c)
{
    m_host = c;
}

QString Service::root() const
{
    return m_root;
}

void Service::setRoot(QString newRoot)
{
    m_root = newRoot;
}

int Service::queue() const {
    return m_queue;
}

void Service::setQueue(int newQueue) {
    m_queue = newQueue;
}

QQmlListProperty<Router> Service::routes()
{
    // if you use qt >= 5.15 then need fix
    //   return QQmlListProperty<Router>(this, &m_routes);
    return QQmlListProperty<Router>(this, m_routes);
}

int Service::routeCount() const
{
    return m_routes.count();
}

Router *Service::route(int index) const
{
    return m_routes.at(index);
}

Router *Service::mainRouter() {
    return m_mainRouter;
}

void Service::setObjGlob(ObjGlob *newObj)
{
    m_globObject = newObj;
}

ObjGlob *Service::getObjGlob() const
{
    return m_globObject;
}

void Service::componentComplete() {
#ifdef DEBUG
    qInfo() << "Service::componentComplete";
    qInfo() << "Root:" << m_root;
    qInfo() << "open FCGI on " << m_host;
#endif




    // создаем и запускаем прослушивание в отдельном потоке:
    socketId = FCGX_OpenSocket(cgi().toUtf8(), queue());
    QList<RouterListen*> routerListens;
#ifdef DEBUG
    threads = 1;
#endif

    for (int i = 0; i < threads; i++) {
        RouterListen* req = new RouterListen(mutex, socketId, m_routes, m_globObject);
        routerListens << req;
    }

    for (Router* r: m_routes)
        r->updateService(this);

    for (RouterListen *routerListen: routerListens)
        routerListen->start();
}
