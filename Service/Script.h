#ifndef SCRIPT_H
#define SCRIPT_H

#include "Request.h"

#include <QMap>
#include <QObject>
#include <QFileSystemWatcher>

class Script: public QObject
{
public:
    Script(QString prefix, QString url, QObject *parent = nullptr);
    QString out() const;

private:
    QString m_script;
};

class Scripts
{
public:
    Scripts (QObject *parent = nullptr);

public:
    void setScriptsDir(QString newDir) { m_scriptsDir = newDir; }
    QString getScriptsDir() const { return m_scriptsDir; }
    QString script(QJSEngine *engine, QString url);

private:
    QFileSystemWatcher m_scriptWatcher;
    QMap<QString, Script*> m_scriptsList;
    QString m_scriptsDir;

    void scriptChanged(const QString& path);
};

#endif // SCRIPT_H
