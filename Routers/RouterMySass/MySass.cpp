#include "MySass.h"

#include <QDebug>
#include <QStack>


MySass::MySass(QString draft)
    : root(new SS(-1, ""))
{
    int s;
    QString world;
    QString line;

    QList<SS> sassStuctDraft;

    for (QString l: draft.split("\n"))
        if ((s = sc(l)) != -1)
            sassStuctDraft.append(SS(s,l.trimmed()));

    for ( SS ss: sassStuctDraft ) {
        sassStuctDraftLine(ss);
    }
    sassStuctDraft.clear();
    dict.clear();
}

void MySass::print() {
    for (SS *it: sassStuct)
        qInfo() << __LINE__ << "it:" << it->depth() << it->line();
}

QString MySass::css() {
    if (sassStuct.size() == 0)
        return "";

    if (out.size() > 0)
        return out;

    QString ret;
    QString line;
    QStack<SS*> stack;
    stack.push(root);

    for (int i = 0; i < sassStuct.size(); i++) {
        SS *ss = sassStuct.at(i);
        QString kkk = ss->line();
        while (stack.top()->depth() >= ss->depth())
            stack.pop();

        if (ss->isSelector())
            stack.top()->addSelector(ss);
        else
            stack.top()->addParam(ss);

        stack.push(ss);
    }

    out = root->css();
    return  out;
    return "";
}

void MySass::sassStuctDraftLine(SS &ss) {
    b = 0;
    e = -1;
    s = -1;
    line = "";
    delimiter = ss.line().indexOf(":");

    if (ss.line().at(0) == '$') {
        dict[ss.line().mid(0, delimiter).trimmed()] = ss.line().mid(delimiter + 1).trimmed();
        return;
    }

    while ((s = ss.line().indexOf('$', s + 1)) != -1) {
        e = ss.line().indexOf(QRegExp("\\W"), s + 1);
        if (e != -1) {
            world = ss.line().mid(s, e-s);
        }
        else {
            world = ss.line().mid(s);
        }
        line += ss.line().mid(b, s - b);
        line += translate(world);
        b = e;
    }
    if (b != -1)
        line += ss.line().mid(b, s);

    sassStuct.append(new SS(ss.depth(), line));
}

QString MySass::translate(QString key) {
    if (dict.contains(key))
        return dict[key];

    return key;
}

int MySass::sc(QString &s) {
    return s.indexOf(QRegExp("\\S"));
}
