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
    enum TYPE{HTML,JS,CSS};
    explicit Page(QStringList list, QObject *parent = nullptr);
    explicit Page(QString prefix, QString url, QObject *parent = nullptr);
    QString out(ObjGlob *glob, FCGIRequest &req) const;
    bool exist();

private:
    QStringList list;
    bool m_exist;

    QJSEngine *engine;
    Request *obj;


signals:

};

#endif // PAGE_H
