#include "Request.h"
#include "Script.h"

#include <QFile>
#include <QFileSystemWatcher>
#include <QJSEngine>

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif

Script::Script(QString prefix, QString url, QObject *parent)
    : QObject(parent)
{
    #ifdef DEBUG
        qInfo() << "Script::Chunk(QString prefix, QString url, QObject *parent)" << prefix << url;
    #endif
    QFile f(prefix + url);
    if (!f.open(QIODevice::ReadOnly)) {
        m_script = "<h1>Chunk not found!</h1>" + prefix + url;

        return;
    }
    m_script = f.readAll();
}

QString Script::out() const {
    return m_script;
}

Scripts::Scripts(QObject *parent)
//    : m_chunkWatcher(new QFileSystemWatcher(parent))
{
}

QString Scripts::script(QJSEngine *engine, QString url)
{
    QString ret;
    QFile qj(url);

    if (qj.open(QIODevice::ReadOnly)) {
        QString script = qj.readAll();
        ret = engine->evaluate(script).toString();

        qj.close();
    }

    return ret;
}
