#include "Obj.h"

#ifdef DEBUG
    #include <QDebug>
#endif

#include <QJsonDocument>


Obj::Obj(QObject *parent)
    : QObject(parent)
{}

void Obj::set(QJsonObject &newObj) {
    obj = newObj;
}

void Obj::setPostUrlencoded(QString strPostData)
{
    QJsonObject obj;
    /// get: login=asd&ss=dd
    bool isKey = true;
    QString key, value;
    for (int i = 0; i < strPostData.size(); i++) {
        QChar ch = strPostData.at(i);
        if (isKey) {
            if (ch != '=') key += ch;
            else isKey = false;
        }
        else {
            if (ch != '&') value += ch;
            else {
                isKey = true;
                obj[key] = value;
                key = value = "";
            }
        }
    }
    if (key.size() > 0)
        obj[key] = value;

    postData = obj;
}

void Obj::setPostJson(QString strPostData)
{
#ifdef DEBUG
    qInfo() << "void Obj::setPostJson(QString strPostData)" << strPostData;
#endif

    QJsonDocument doc = QJsonDocument::fromJson(strPostData.toUtf8());
    postData = doc.object();

#ifdef DEBUG
    qInfo() << __LINE__ << "postData:" << postData;
#endif
}

void Obj::update(Obj *newObj) {
    obj = newObj->obj;
}

QString Obj::menu() {
    QString ret = "__MENU__%1:%2__";

    return ret.arg(obj["page"].toString("/index.unix")).arg(obj["index"].toString(""));
}

QString Obj::body() {
    if (obj["page"] == "/pass.unix")
        return "<h1>Page: /pass.unix</h1>";

    if (obj["page"] == "/index1")
        return "<h1>Page: /index1</h1>";

    return "<h1>NO BODY</h1>";
}

QString Obj::val(QString key) {
    return postData[key].toString("").toHtmlEscaped();
}
