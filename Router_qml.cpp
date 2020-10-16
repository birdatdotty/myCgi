//#include "Router.h"

//#ifdef DEBUG
//    #include <QDateTime>
//    #include <QDebug>
//    #include <iostream>
//#endif

//QQmlListProperty<Router> Router::routes()
//{
//    return {this, this,
//             &Router::appendRouter,
//             &Router::routerCount,
//             &Router::router,
//             &Router::clearRouters,
//             &Router::replaceRouter,
//             &Router::removeLastRouter};
//}

//void Router::appendRouter(Router *r)
//{
//    _routes.append(r);
//}

//int Router::routerCount() const
//{
//    return _routes.count();
//}

//Router *Router::router(int i) const
//{
//    return _routes.at(i);
//}

//void Router::clearRouters()
//{
//    _routes.clear();
//}

//void Router::replaceRouter(int i, Router *r)
//{
//    _routes[i] = r;
//}

//void Router::removeLastRouter()
//{
//    _routes.removeLast();
//}

//void Router::appendRouter(QQmlListProperty<Router> *list, Router *r)
//{
//    reinterpret_cast< Router* >(list->data)->appendRouter(r);
//}

//int Router::routerCount(QQmlListProperty<Router> *list)
//{
//    return reinterpret_cast< Router* >(list->data)->routerCount();
//}

//Router *Router::router(QQmlListProperty<Router> *list, int i)
//{
//        return reinterpret_cast< Router* >(list->data)->router(i);
//}

//void Router::clearRouters(QQmlListProperty<Router> *list)
//{
//    reinterpret_cast< Router* >(list->data)->clearRouters();
//}

//void Router::replaceRouter(QQmlListProperty<Router> *list, int i, Router *r)
//{
//    reinterpret_cast< Router* >(list->data)->replaceRouter(i, r);
//}

//void Router::removeLastRouter(QQmlListProperty<Router> *list)
//{
//    reinterpret_cast< Router* >(list->data)->removeLastRouter();
//}

