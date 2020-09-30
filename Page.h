#ifndef PAGE_H
#define PAGE_H

#include <QObject>


class QJSEngine;
class Obj;

class Page : public QObject
{
    Q_OBJECT
public:
    explicit Page(QStringList list, QObject *parent = nullptr);
    explicit Page(QString prefix, QString url, QObject *parent = nullptr);
    QString out(QJSEngine *engine, Obj *obj) const;
    bool exist();

private:
    QStringList list;
    bool m_exist;

signals:

};

#endif // PAGE_H
