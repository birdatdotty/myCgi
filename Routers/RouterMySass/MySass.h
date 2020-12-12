#ifndef MYSASS_H
#define MYSASS_H

#include <QMap>
#include <QObject>

#include "SS.h"

class MySass {
public:
    MySass(QString draft);

    void print();
    QString css();
private:
    SS* root;
    QList<SS*> sassStuct;
    QStack<QString> *swww;
    QMap<QString,QString> dict;

    // for sassStuctDraft item:
    int s;
    int b = 0;
    int e = -1;
    QString world;
    QString line;
    int delimiter;
    QString out;

    void sassStuctDraftLine(SS& ss);
    QString translate(QString key);
    int sc(QString& s);

protected:
};

#endif // MYSASS_H
