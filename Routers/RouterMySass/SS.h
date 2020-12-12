#ifndef SS_H
#define SS_H

#include <QObject>

struct SS {
    int depth() const;
    QString line() const;

    SS(int depth, QString line, SS* parent = nullptr);
    bool isSelector() const;
    QString selector();
    void setParent(SS*parent);
    void addChild(SS* child);
    void addParam(SS* param);
    void addSelector(SS* selector);
    QString css(QString pre = "");

private:
    SS* _parent;
    int _depth;
    QString _line;
public:
    QList<SS*> children;
    QList<SS*> params;
    QList<SS*> selectors;
};

#endif // SS_H
