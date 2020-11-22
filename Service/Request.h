#ifndef OBJ_H
#define OBJ_H

#include "FCGIRequest.h"

#include <QObject>
#include <QJsonObject>
#include <fcgiapp.h>
#include <QJsonObject>
#include <QMap>

#include <fcgi_stdio.h>

class Router;
class ObjGlob;

class Request : public QObject
{
    Q_OBJECT
public:
    explicit Request(FCGIRequest &req, ObjGlob* glob): req(req), glob(glob) {}

    void set(QJsonObject &newObj);
    void setPostUrlencoded(QString strPostData);
    void setPostJson(QString strPostData);
    void setMultipartFormData(QString strPostData, QString ContentType);

    void setPostData(FCGX_Request &req, int ContentLength);

    void update(Request *newObj);
    QJsonObject& getObj() {return obj;}


    QString url(const Router *router);
    // QJSEngine:
    Q_INVOKABLE QString url();
    Q_INVOKABLE QString uri();
    Q_INVOKABLE QString body();
    Q_INVOKABLE QString val(QString key);
    Q_INVOKABLE QString page(QString key); /// return value from FCGX_Request
    Q_INVOKABLE QString file(QString file);
    Q_INVOKABLE QString post(QString key);
    Q_INVOKABLE QString get(QString key);
    Q_INVOKABLE QString chunk(QString chunkPath);
    Q_INVOKABLE QString script(QString scriptPath);

    Q_INVOKABLE bool testPath(QString key, QString value);

    Q_INVOKABLE QString t() {return "Q_INVOKABLE QString t()";}

    void setRequest(FCGX_Request *newRequest) {
        req.setRequest(newRequest);
//        FCGX_Request request;
    }

    QJsonObject obj;
    FCGIRequest &req;
private:
    QJsonObject postData;

    int m_count;

    ObjGlob *glob;
    QString m_url;
};

#endif // OBJ_H
