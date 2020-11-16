#ifndef PAGE_H
#define PAGE_H

#include "FCGIRequest.h"

#include <QObject>


class QJSEngine;
class Request;
class ObjGlob;

class Page : public QObject
{
    Q_OBJECT
public:
    enum TYPE{HTML,JS,CSS,JSON};
    explicit Page(QStringList list, QObject *parent = nullptr);
    explicit Page(QString prefix, QString url, QObject *parent = nullptr);
    explicit Page(TYPE type, QByteArray &byteArray, QObject *parent = nullptr);
    explicit Page(TYPE type, QString byteArray, QObject *parent = nullptr);
    virtual QString out(ObjGlob *glob, FCGIRequest &req) const;
    virtual QString out(QJSEngine *engine) const;
    bool exist();
    QString contentType();

private:
    QStringList list;
    bool m_exist;

    TYPE type;

signals:

};

#endif // PAGE_H
