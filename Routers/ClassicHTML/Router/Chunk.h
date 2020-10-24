#ifndef CHUNK_H
#define CHUNK_H

#include <QMap>
#include <QObject>
#include <QFileSystemWatcher>

class Chunk: public QObject
{
public:
    Chunk(QString prefix, QString url, QObject *parent = nullptr);
    QString out() const;

private:
    QString m_chunk;
};

class Chunks
{
public:
    Chunks (QObject *parent = nullptr);

public:
    void setChunksDir(QString newDir) { m_chunksDir = newDir; }
    QString getChunksDir() const { return m_chunksDir; }
    QString chunk(QString url);

private:
    QFileSystemWatcher* m_chunkWatcher;
    QMap<QString, Chunk*> m_chunksList;
    QString m_chunksDir;

    void chunkChanged(const QString& path);


};

#endif // CHUNK_H
