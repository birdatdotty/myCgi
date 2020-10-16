#include "QMLTree.h"

QMLTree::QMLTree(QObject *parent) : QObject(parent)
{

}


#include "QMLTree.h"
#include "Router.h"

#ifdef DEBUG
    #include <QDateTime>
    #include <QDebug>
    #include <iostream>
#endif

QQmlListProperty<Router> QMLTree::routes()
{
    return QQmlListProperty<Router>(this, _routes);
//    return {this, this,
//             &QMLTree::appendRouter,
//             &QMLTree::routerCount,
//             &QMLTree::router,
//             &QMLTree::clearRouters,
//             &QMLTree::replaceRouter,
//             &QMLTree::removeLastRouter};
}

void QMLTree::appendRouter(Router *r)
{
    _routes.append(r);
}

int QMLTree::routerCount() const
{
    return _routes.count();
}

Router *QMLTree::router(int i) const
{
    return _routes.at(i);
}

void QMLTree::clearRouters()
{
    _routes.clear();
}

void QMLTree::replaceRouter(int i, Router *r)
{
    _routes[i] = r;
}

void QMLTree::removeLastRouter()
{
    _routes.removeLast();
}

void QMLTree::appendRouter(QQmlListProperty<Router> *list, Router *r)
{
    reinterpret_cast< Router* >(list->data)->appendRouter(r);
}

int QMLTree::routerCount(QQmlListProperty<Router> *list)
{
    return reinterpret_cast< Router* >(list->data)->routerCount();
}

Router *QMLTree::router(QQmlListProperty<Router> *list, int i)
{
        return reinterpret_cast< Router* >(list->data)->router(i);
}

void QMLTree::clearRouters(QQmlListProperty<Router> *list)
{
    reinterpret_cast< Router* >(list->data)->clearRouters();
}

void QMLTree::replaceRouter(QQmlListProperty<Router> *list, int i, Router *r)
{
    reinterpret_cast< Router* >(list->data)->replaceRouter(i, r);
}

void QMLTree::removeLastRouter(QQmlListProperty<Router> *list)
{
    reinterpret_cast< Router* >(list->data)->removeLastRouter();
}

