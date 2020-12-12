#include "MySass.h"
#include "LibRouterMySass.h"

#include <QFile>


#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif


QString open(QString file) {
    QFile f(file);
    if (f.open(QIODevice::ReadOnly))
        return f.readAll();

    return "";
}

LibRouterMySass::LibRouterMySass(Router *parent): Router(parent), m_sassWatcher(new QFileSystemWatcher)
{
    QObject::connect(m_sassWatcher, &QFileSystemWatcher::fileChanged,
            this, &LibRouterMySass::sassChanged);

}
LibRouterMySass::LibRouterMySass(QString root): Router(root), m_sassWatcher(new QFileSystemWatcher)
{
    QObject::connect(m_sassWatcher, &QFileSystemWatcher::fileChanged,
            this, &LibRouterMySass::sassChanged);
}
#include <QDebug>
Page *LibRouterMySass::route(FCGIRequest &/*req*/, QString url) {
    MySass* _sass;
    qInfo() << __LINE__ << "m_sassList.keys():" << m_sassList.keys();
    qInfo() << __LINE__ << "url:" << url;
    if (!m_sassList.contains(url)) {
        qInfo() << __LINE__ << "if (!m_sassList.contains(url))";
        QString file = root + url;
        _sass = new MySass(open(root + url));
        if (QFile::exists(file)) {
            m_sassWatcher->addPath( file );
            m_sassList[url] = _sass;
#ifdef DEBUG
    qInfo() << __LINE__ << "sassWatcher->files():" << m_sassWatcher->files();
#endif
        }
#ifdef DEBUG
        else qInfo() << "QFile::exists(file): not exist - " << file;
#endif
    }
    else _sass = m_sassList[url];

//    MySass(open(root + url));
// /sass/1.sass

//    return true;
    Page* p = new Page(Page::CSS, _sass->css());
    return p;
}

void LibRouterMySass::sassChanged(const QString &path)
{
    if (!path.startsWith(root))
        return;

    QString key = path;
    key = key.remove(0, root.size());

#ifdef DEBUG
    std::cout << "request: " << std::endl;
    qInfo() << "path: [" + path + "]";
    qInfo() << "key: [" + key + "]";
    qInfo() << "m_chunksDir:" << m_sassList;
    qInfo() << "m_chunkWatcher->files():" << m_sassWatcher->files();
#endif

    if (m_sassList.contains(key)) {
        m_sassList.remove(key);
        m_sassWatcher->removePath(path);
#ifdef DEBUG
        qInfo() << path + " removed";
#endif
    }

}
