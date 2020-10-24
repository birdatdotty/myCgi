#ifndef OBJ_H
#define OBJ_H

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
//    explicit Obj(Router *parent = nullptr);
    explicit Request(FCGX_Request &req, ObjGlob* glob): req(req), glob(glob) {}
    explicit Request(Request &obj): req(obj.req), glob(obj.glob) {}
    explicit Request(Request *obj): req(obj->req), glob(obj->glob) {}

    void set(QJsonObject &newObj);
    void setPostUrlencoded(QString strPostData);
    void setPostJson(QString strPostData);
    void setMultipartFormData(QString strPostData, QString ContentType);

    void setPostData(FCGX_Request &req, int ContentLength);

    void update(Request *newObj);
    QJsonObject& getObj() {return obj;}
    QString url() {
        return FCGX_GetParam("DOCUMENT_URI", req.envp);
    }


    // QJSEngine:
    Q_INVOKABLE QString body();
    Q_INVOKABLE QString val(QString key);
    Q_INVOKABLE QString page(QString key); /// return value from FCGX_Request
    Q_INVOKABLE QString file(QString file);
    Q_INVOKABLE QString post(QString key);
    Q_INVOKABLE QString get(QString key);

    Q_INVOKABLE bool testPath(QString key, QString value);
    Q_INVOKABLE int localCount();
    Q_INVOKABLE int globCount();

    Q_INVOKABLE QString chunk(ObjGlob *glob, QString url);
    Q_INVOKABLE QString script(ObjGlob *glob, QString file);


    QJsonObject obj;
private:
    FCGX_Request req;
    QJsonObject postData;

    int m_count;

    ObjGlob *glob;
    QString m_url;
};

#endif // OBJ_H
