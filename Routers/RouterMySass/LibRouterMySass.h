#ifndef ROUTERMYSASS_H
#define ROUTERMYSASS_H

#include "Router.h"
class MySass;

class LibRouterMySass: public Router
//class LibRouterMySass: public QObject
{
public:
    LibRouterMySass(Router* parent);
    LibRouterMySass(QString root = "");

    virtual Page* route(FCGIRequest &req, QString url);

private:
    QFileSystemWatcher* m_sassWatcher;
    QMap<QString, MySass*> m_sassList;

public slots:
    void sassChanged(const QString& path);
};

#endif // ROUTERMYSASS_H
