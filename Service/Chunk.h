#ifndef CHUNK_H
#define CHUNK_H

#include <QMap>
#include <QObject>
#include <QFileSystemWatcher>

class Chunk: public QObject
{
public:
    Chunk(/*QString prefix,*/ QString url, QObject *parent = nullptr);
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
    Q_INVOKABLE QString chunk(QString url);

protected:
    QFileSystemWatcher* m_chunkWatcher;
    QMap<QString, Chunk*> m_chunksList;
    QString m_chunksDir;

};

#endif // CHUNK_H
