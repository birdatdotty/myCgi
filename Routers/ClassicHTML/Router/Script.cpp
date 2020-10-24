#include "Obj.h"
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

QString Scripts::script(Request *obj, QString url)
{
    QString ret;
    QFile qj(m_scriptsDir + url);

    if (qj.open(QIODevice::ReadOnly)) {
        QString script = qj.readAll();
        QJSEngine engine;

        Request *self = new Request(obj);
        QJSValue jsObj = engine.newQObject(self);

        engine.globalObject().setProperty("Obj", jsObj);

        ret = engine.evaluate(script).toString();

        qj.close();
    }

    return ret;
}

//void Scripts::chunkChanged(const QString &path)
//{
//    if (!path.startsWith(m_chunksDir))
//        return;

//    QString key = path;
//    key = key.remove(0, m_chunksDir.size());

//#ifdef DEBUG
//    std::cout << "request: " << std::endl;
//    qInfo() << "path: [" + path + "]";
//    qInfo() << "key: [" + key + "]";
//#endif

//    if (m_chunksDir.contains(key)) {
//        m_chunksDir.remove(key);
//        m_chunkWatcher->removePath(path);
//#ifdef DEBUG
//        qInfo() << path + " removed";
//#endif
//    }
//}
