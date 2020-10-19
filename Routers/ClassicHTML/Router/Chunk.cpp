#include "Chunk.h"

#include <QFile>

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif

Chunk::Chunk(QString prefix, QString url, QObject *parent)
    : QObject(parent)
{
    #ifdef DEBUG
        qInfo() << "Chunk::Chunk(QString prefix, QString url, QObject *parent)" << prefix << url;
    #endif
    QFile f(prefix + url);
    if (!f.open(QIODevice::ReadOnly)) {
        m_chunk = "<h1>Chunk not found!</h1>";

        return;
    }
    m_chunk = f.readAll();
}

QString Chunk::out() const {
    return m_chunk;
}


