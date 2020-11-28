#ifndef TEST_H
#define TEST_H

#include <QObject>

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);

    Q_INVOKABLE QString t(QString s1, QString s2) {
        QString ret = "Q_INVOKABLE QString t(%1,%2)";
        return ret.arg(s1).arg(s2);
    }
    Q_INVOKABLE QString t2(QString str) {
        return "Q_INVOKABLE QString t2(" + str + ")";
    }

signals:

};

#endif // TEST_H
