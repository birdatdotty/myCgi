#include "Request.h"
#include "ObjGlob.h"

#include "Router.h"

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif

#include <QFile>
#include <QJSEngine>
#include <QJsonDocument>
#include <QString>



void Request::set(QJsonObject &newObj) {
    obj = newObj;
}

void Request::setPostUrlencoded(QString strPostData)
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

void Request::setPostJson(QString strPostData)
{
    #ifdef DEBUG
        qInfo() << "void Request::setPostJson(QString strPostData)" << strPostData;
    #endif

    QJsonDocument doc = QJsonDocument::fromJson(strPostData.toUtf8());
    postData = doc.object();

    #ifdef DEBUG
        qInfo() << __LINE__ << "postData:" << postData;
    #endif
}

void Request::setMultipartFormData(QString strPostData, QString ContentType)
{
    #ifdef DEBUG
        qInfo() << "--------------------";
        qInfo() << "void Request::setMultipartFormData(QString strPostData):";
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

void Request::setPostData(FCGX_Request &req, int ContentLength)
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
//    else if (startsWith("multipart/form-data", ContentType))
//        setMultipartFormData(postData, ContentType);

    free(postData);
}

void Request::update(Request *newObj) {
    obj = newObj->obj;
}

QString Request::url(const Router* router) {
    return req.url(router);
}

QString Request::url(QString)
{
    return req.clearUrl();
}

QString Request::uri() {
    return req.uri();
}

QString Request::body() {
    if (obj["page"] == "/pass.unix")
        return "<h1>Page: /pass.unix</h1>";

    if (obj["page"] == "/index1")
        return "<h1>Page: /index1</h1>";

    return "<h1>NO BODY</h1>";
}

QString Request::val(QString key) {
    return postData[key].toString("").toHtmlEscaped();
}

QString Request::page(QString key)
{
    return obj[key].toString("").toHtmlEscaped();
}

QString Request::file(QString file)
{
    QString ret;
    QFile qj(file);
    if (qj.open(QIODevice::ReadOnly))
        ret = qj.readAll();

    qj.close();

    return ret;
}

QString Request::post(QString key) {
    return postData[key].toString("");
}

QString Request::get(QString key) {
    return obj["get"].toObject()[key].toString("");
}

QString Request::chunk(QString chunkPath) {
    return glob->chunk(chunkPath);
}

QString Request::script(QString scriptPath)
{
#ifdef DEBUG
    qInfo() << "\n    QString Request::script(" << glob->getScriptsDir() + scriptPath << ")";
#endif


    QJSEngine engine;
    QString s = glob->script(&engine, glob->getScriptsDir() + scriptPath);
    return s;
}

QString Request::router(QString str)
{
    int split;
    QString routeFun;
    QString routeParam;
    QString retVal;

    split = str.indexOf(' ');
    if (split == -1)
        QMetaObject::invokeMethod(_router, str.trimmed().toUtf8(), Qt::DirectConnection,
                                  Q_RETURN_ARG(QString, retVal));
    else
        QMetaObject::invokeMethod(_router, str.mid(0,split).trimmed().toUtf8(), Qt::DirectConnection,
                                  Q_RETURN_ARG(QString, retVal),
                                  Q_ARG(QString, str.mid(split+1).trimmed()));

    return retVal;
}

bool Request::testPath(QString key, QString value) {
#ifdef DEBUG
    qInfo() << "    bool Request::testPath(" << key << "," << value << ")";
#endif

    QString _url = key;
    if ( _url == "/" )
        _url = glob->getDefaultPage();

    if (_url.startsWith(value))
        return true;

    return false;
}

void Request::setRouter(Router *newRouter) {
    _router = newRouter;
}

QString Request::eng(QString str) {
    QString fun;
    QString paramStr;
    int posOpenBraket;
    int posCloseBraket;

    posOpenBraket = str.indexOf('(');
    posCloseBraket = str.lastIndexOf(')');
    paramStr = str.mid(posOpenBraket + 1,
                        posCloseBraket - posOpenBraket - 1 ).trimmed();

    fun = str.mid(4,posOpenBraket - 4);
    QString retVal;
    QMetaObject::invokeMethod(this, fun.toUtf8(), Qt::DirectConnection,
                              Q_RETURN_ARG(QString, retVal),
                              Q_ARG(QString, paramStr));

    return retVal;
}
