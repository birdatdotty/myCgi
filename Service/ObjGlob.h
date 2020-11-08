#ifndef OBJGLOB_H
#define OBJGLOB_H

#include <QObject>
#include <QJsonObject>
#include <fcgiapp.h>
#include <QJsonObject>
#include <QMap>

class Router;
//class Obj;

#include "Chunk.h"
#include "DefaultPage.h"
#include "Script.h"
#include "Page.h"
#include "FCGIRequest.h"

class ObjGlob:
        public QObject,
        public Chunks,
        public Scripts,
        public DefaultPage
{
    Q_OBJECT
    Q_PROPERTY(QString root
               READ getRoot
               WRITE setRoot
               NOTIFY sigRoot)

    Q_PROPERTY(QString chunks
               READ getChunksDir
               WRITE setChunksDir)

    Q_PROPERTY(QString scripts
               READ getScriptsDir
               WRITE setScriptsDir)

    Q_PROPERTY(QString  defaultPage
               READ getDefaultPage
               WRITE setDefaultPage)

// depricated
    Q_PROPERTY(int threads
               READ getThreads
               WRITE setThreads)
// end depricated

public:
    ObjGlob(Router *router = nullptr);
    QString auth(QString login, QString password);
    bool test(QString id);
    int count();
    void out(Page* page, FCGIRequest &FCGIReq);

    void setRoot(QString newRoot);
    QString getRoot() const;

// depricated
    int getThreads() const { return threads; }
    void setThreads(int newThreads) { threads = newThreads; }
// end depricated

private:
    QMap<QString,QString> users;
    QMap<QString,QString> ids;
    Router *m_router;
    int m_count;
    QString m_root;

// depricated
    int threads;
// end depricated


    QString getRandomString(int randomStringLength = 12) const;

signals:
    void sigRoot();
};

#endif // OBJGLOB_H
