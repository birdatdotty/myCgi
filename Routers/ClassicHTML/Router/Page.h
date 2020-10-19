#ifndef PAGE_H
#define PAGE_H

#include <QObject>


class QJSEngine;
class Obj;

class Page : public QObject
{
    Q_OBJECT
public:
    enum TYPE{HTML,JS,CSS};
    explicit Page(QStringList list, QObject *parent = nullptr);
    explicit Page(QString prefix, QString url, QObject *parent = nullptr);
    QString out(Obj *obj) const;
    bool exist();

private:
    QStringList list;
    bool m_exist;

    QJSEngine *engine;
    Obj *obj;


signals:

};

#endif // PAGE_H
