#include "RouterListen.h"
#include "Service.h"

#include <QDebug>

Service::Service(QQuickItem *parent)
: QQuickItem(parent)
{
  qInfo() << "parent:" << parent;
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

QQmlListProperty<Router> Service::guests()
{
    return QQmlListProperty<Router>(this, m_routes);
}

int Service::guestCount() const
{
    return m_routes.count();
}

Router *Service::guest(int index) const
{
    return m_routes.at(index);
}

Router *Service::mainRouter() {
    return m_mainRouter;
}

void Service::setDefaultPage(QString newDefaultPage) {
    m_defaultPage = newDefaultPage;
}

QString Service::getDefaultPage() {
    return m_defaultPage;
}

void Service::componentComplete() {
    qInfo() << "Service::componentComplete";
    qInfo() << "Root:" << m_root;
    qInfo() << "open FCGI on " << m_host;

    m_mainRouter = new Router(m_root);
    m_mainRouter->setDefaultPage(m_defaultPage);
    for (Router *route: m_routes) {
        m_mainRouter->addRoute(route->getUrl(), route);
    }

    // создаем и запускаем прослушивание в отдельном потоке:
    RouterListen *routerListen = new RouterListen(cgi(), queue(), m_mainRouter);
    routerListen->start();

}
