#ifndef CHUNK_H
#define CHUNK_H

#include <QObject>

class Chunk: public QObject
{
public:
    Chunk(QString prefix, QString url, QObject *parent = nullptr);
    QString out() const;

private:
    QString m_chunk;
};

#endif // CHUNK_H
