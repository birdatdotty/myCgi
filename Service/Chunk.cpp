#include "Chunk.h"

#include <QFile>
#include <QFileSystemWatcher>

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif

Chunk::Chunk(/*QString prefix, */QString url, QObject *parent)
    : QObject(parent)
{
    #ifdef DEBUG
        qInfo() << "\n    Chunk::Chunk(QString prefix, QString url, QObject *parent)";
        qInfo() << "url:" << url;
    #endif
    QFile f(url);
    if (!f.open(QIODevice::ReadOnly)) {
        m_chunk = "<h1>Chunk (" + url + ") not found!</h1>";

        return;
    }
    m_chunk = f.readAll();
}

QString Chunk::out() const {
    return m_chunk;
}



Chunks::Chunks(QObject *parent)
    : m_chunkWatcher(new QFileSystemWatcher(parent))
{
}

QString Chunks::chunk(QString url)
{
    Chunk* _chunk;
    if (!m_chunksList.contains(url)) {
        QString file = m_chunksDir + url;
        _chunk = new Chunk(m_chunksDir + url);
        if (QFile::exists(file)) {
            m_chunkWatcher->addPath( file );
            m_chunksList[url] = _chunk;
#ifdef DEBUG
    qInfo() << __LINE__ << "chunkWatcher->files():" << m_chunkWatcher->files();
#endif
        }
#ifdef DEBUG
        else qInfo() << "QFile::exists(file): not exist - " << file;
#endif
    }
    else _chunk = m_chunksList[url];

    return _chunk->out();
}

//void Chunks::chunkChanged(const QString &path)
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
