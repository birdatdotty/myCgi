#include "Obj.h"
#include "utils.h"

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif

#include <QFile>
#include <QJSEngine>
#include <QJsonDocument>


Obj::Obj(Router *parent)
    : QObject(nullptr),
      m_count(10)
{
    static ObjGlob* _glob = new ObjGlob(parent);

    glob = _glob;
}

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

void Obj::setMultipartFormData(QString strPostData, QString ContentType)
{
#ifdef DEBUG
    qInfo() << "--------------------";
    qInfo() << "void Obj::setMultipartFormData(QString strPostData):";
    qInfo() << strPostData;
    qInfo() << "--------------------";
#endif

    QJsonObject obj;

    const char* boundary = ContentType.split('=').at(1).toUtf8();
    #ifdef DEBUG
        std::cout << "boundary: [" << boundary << "]" << std::endl;
    #endif

    QString sBoundary = "--";
    QString eBoundary;
    sBoundary += boundary;
    eBoundary += sBoundary + "--";

    #ifdef DEBUG
        qInfo() << "sBoundary: {" + sBoundary + "]";
    #endif

    QString keyStr, value;

    int startPost = 0;
    int endPost = 0;

    while ((endPost = strPostData.indexOf(sBoundary, endPost + 1)) != -1) {
        startPost = endPost;
    }

    postData = obj;

    #ifdef DEBUG
        qInfo() << __LINE__ << "postData:" << postData;
    #endif
}

void Obj::setPostData(FCGX_Request &req, int ContentLength)
{
    const char *ContentType = FCGX_GetParam("CONTENT_TYPE", req.envp);

    char* postData;
    postData = (char*) malloc(ContentLength+1);
    FCGX_GetStr(postData, ContentLength, req.in);
    postData[ContentLength] = '\0';

    #ifdef DEBUG
        std::cout << "postData: \n" << postData << std::endl;
    #endif

    if (strcmp(ContentType, "application/x-www-form-urlencoded") == 0)
        setPostUrlencoded(postData);
    else if (strcmp(ContentType, "application/json") == 0)
        setPostJson(postData);
    else if (startsWith("multipart/form-data", ContentType))
        setMultipartFormData(postData, ContentType);

    free(postData);
}

void Obj::update(Obj *newObj) {
    obj = newObj->obj;
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

QString Obj::page(QString key)
{
    return obj[key].toString("").toHtmlEscaped();
}

QString Obj::script(QString file)
{
    QString ret;
    QFile qj(file);

    if (qj.open(QIODevice::ReadOnly)) {
        QString script = qj.readAll();
        QJSEngine engine;

        Obj self;
        self.obj = obj;
        QJSValue jsObj = engine.newQObject(&self);
        engine.globalObject().setProperty("Obj", jsObj);

        ret = engine.evaluate(script).toString();

        qj.close();
    }

    return ret;
}

QString Obj::file(QString file)
{
    QString ret;
    QFile qj(file);
    if (qj.open(QIODevice::ReadOnly))
        ret = qj.readAll();

    qj.close();

    return ret;
}

QString Obj::post(QString key) {
    return postData[key].toString("");
}

QString Obj::get(QString key) {
    return obj["get"].toObject()[key].toString("");
}

bool Obj::testPath(QString key, QString value) {
    if (obj[key].toString("").startsWith(value))
        return true;

    return false;
}



