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
//    m_chunkWatcher

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


