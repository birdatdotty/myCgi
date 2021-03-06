#include "Page.h"

#include <QFile>
#include <QJSEngine>

#include "Obj.h"

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif


Page::Page(QStringList list, QObject *parent)
    : QObject(parent),
      list(list),
      m_exist(true)
{
    engine = new QJSEngine;
    obj = new Obj;

    QJSValue jsObj = engine->newQObject(obj);
    engine->globalObject().setProperty("Obj", jsObj);
}

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

QString Page::out(Obj* obj) const
{
    QJSEngine engine;
    QJSValue jsObj = engine.newQObject(obj);
//    QJSValue jsData = engine.newQObject(obj->getObj());
    engine.globalObject().setProperty("Obj", jsObj);


    QString ret = "Content-type: text/html\n\n";
    for (int i = 0; i < list.size(); i++) {
        if ((i & 1) == 0)
            ret += list.at(i);
        else {
            ret += engine.evaluate(list.at(i)).toString();
//            ret += list.at(i);
        }
    }

    return ret;
}

bool Page::exist() {
    return m_exist;
}
