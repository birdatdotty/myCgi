#ifndef OBJ_H
#define OBJ_H

#include <QObject>
#include <QJsonObject>
#include <fcgiapp.h>
#include <QJsonObject>
#include <QMap>

class Router;

struct ObjGlob: public QObject {
    ObjGlob(Router *router = nullptr);
    QString auth(QString login, QString password);
    bool test(QString id);
    int count();
    QString chunk(QString key);

private:
    QMap<QString,QString> users;
    QMap<QString,QString> ids;
    Router *m_router;
    int m_count;


    QString getRandomString() const;
};

class Obj : public QObject
{
    Q_OBJECT
public:
    explicit Obj(Router *parent = nullptr);

    void set(QJsonObject &newObj);
    void setPostUrlencoded(QString strPostData);
    void setPostJson(QString strPostData);
    void setMultipartFormData(QString strPostData, QString ContentType);

    void setPostData(FCGX_Request &req, int ContentLength);

    void update(Obj *newObj);
    QJsonObject& getObj() {return obj;}


    // QJSEngine:
    Q_INVOKABLE QString body();
    Q_INVOKABLE QString val(QString key);
    Q_INVOKABLE QString page(QString key); /// return value from FCGX_Request
    Q_INVOKABLE QString script(QString file);
    Q_INVOKABLE QString file(QString file);
    Q_INVOKABLE QString post(QString key);
    Q_INVOKABLE QString get(QString key);

    Q_INVOKABLE bool testPath(QString key, QString value);
    Q_INVOKABLE int localCount() {return ++m_count;}
    Q_INVOKABLE int globCount() {return glob->count();}

    Q_INVOKABLE QString chunk(QString key) {return glob->chunk(key);}


private:
    QJsonObject obj;
    QJsonObject postData;

    int m_count;

    ObjGlob *glob;
};

#endif // OBJ_H
