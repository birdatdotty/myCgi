#ifndef QMLTREE_H
#define QMLTREE_H

#include <QObject>
#include <QQmlListProperty>

class Router;

class QMLTree : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Router> routes READ routes)
    Q_CLASSINFO("DefaultProperty", "routes")

public:
    QQmlListProperty<Router> routes();
    void appendRouter(Router*);
    int routerCount() const;
    Router *router(int i) const;
    void clearRouters();
    void replaceRouter(int, Router*);
    void removeLastRouter();
    QList<Router *> _routes;

private:
    static void appendRouter(QQmlListProperty<Router>*, Router*);
    static int routerCount(QQmlListProperty<Router>*);
    static Router* router(QQmlListProperty<Router>*, int);
    static void clearRouters(QQmlListProperty<Router>*);
    static void replaceRouter(QQmlListProperty<Router>*, int, Router*);
    static void removeLastRouter(QQmlListProperty<Router>*);
    // end QML

public:
    explicit QMLTree(QObject *parent = nullptr);

signals:

};

#endif // QMLTREE_H
