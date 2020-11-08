#include "Page.h"

#include <QFile>
#include <QJSEngine>

#include "Request.h"
#include "ObjGlob.h"

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif


Page::Page(QStringList list, QObject *parent)
    : QObject(parent),
      list(list),
      m_exist(true),
      engine(new QJSEngine)
{}

Page::Page(QString prefix, QString url, QObject *parent)
    : QObject(parent)
{
    QString str;
    QFile f(prefix + url);

    if (!f.open(QIODevice::ReadOnly)) {
        list << "<h1>Page not found!</h1>";
        m_exist = false;
        return;
    }

    m_exist = true;
    str = f.readAll();

    QRegExp rx("\\b(Obj\\s*\\.\\w+\\(.*\\)){1,}");
    rx.setMinimal(true);
    int pos = 0;
    int s = 0;

    while ((pos = rx.indexIn(str, pos)) != -1) {
        list << str.mid(s, pos - s);
        list << rx.cap(1);
        pos += rx.matchedLength();
        s = pos;
    }
    f.close();

    list << str.mid(s);
}

QString Page::out(ObjGlob *glob, FCGIRequest& req) const
{
#ifdef DEBUG
    qInfo() << glob->chunk("/chunk1.chunk");
#endif
    QJSEngine engine;
    Request request(req.request, glob);
    QJSValue jsObj = engine.newQObject(&request);
    QJSValue jsObjGlob = engine.newQObject(glob);

    engine.globalObject().setProperty("Obj", jsObj);
    engine.globalObject().setProperty("GlobObj", jsObjGlob);

#ifdef DEBUG
    qInfo() << "glob:" << glob;
    qInfo() << list.size();
#endif


    QString ret = "Content-type: text/html\n\n";
    for (int i = 0; i < list.size(); i++) {
        if ((i & 1) == 0)
            ret += list.at(i);
        else {
            ret += engine.evaluate(list.at(i)).toString();
        }
    }

    return ret;
}

bool Page::exist() {
    return m_exist;
}
