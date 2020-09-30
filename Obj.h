#ifndef OBJ_H
#define OBJ_H

#include <QObject>
#include <QJsonObject>

class Obj : public QObject
{
    Q_OBJECT
public:
    explicit Obj(QObject *parent = nullptr);

    void set(QJsonObject &newObj);
    void setPostUrlencoded(QString strPostData);
    void setPostJson(QString strPostData);

    // QJSEngine:
    Q_INVOKABLE QString menu();
    Q_INVOKABLE QString body();
    Q_INVOKABLE QString val(QString key);

private:
    QJsonObject obj;
    QJsonObject postData;
};

#endif // OBJ_H
