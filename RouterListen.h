#ifndef ROUTERLISTEN_H
#define ROUTERLISTEN_H

#include <QThread>
#include <fcgi_stdio.h>
#include "Router.h"

class RouterListen : public QThread
{
    Q_OBJECT
public:
    explicit RouterListen(QString path, int listenQueueBacklog, QList<Router *> router, QObject *parent = nullptr);

protected:
    void run() override;

private:
    FCGX_Request request;
    QList<Router *> router;

signals:
    void sigRequest(FCGX_Request request);

};

#endif // ROUTERLISTEN_H
