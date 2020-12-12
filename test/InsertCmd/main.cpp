#include <QDebug>
#include <iostream>

#include "InsertCmd.h"

void print(InsertCmd* b, QString &d) {
    qInfo() << "script:" << d;
    for (int i = 0; i < b->count(); i++) {
        qInfo() << "i:" << i;
        qInfo() << "  fun: " << b->fun(i);
        qInfo() << "  args:" << b->args(i);
    }
    qInfo() << endl;
}

int main(int argc, char *argv[])
{
    QString script = "Obj.pl(ds).t()";
    QString script2 = "Obj.p2l(ds).t()";
    QString script3 = "Obj.pl(\" d ds\" dss sdsw23 w).t()";
    QString script4 = "Obj.pl(\" d ds\" dss sdsw23 w).t().sss(2\\ 2 55 ass)";
    QString script5 = "Obj.p\\(s()";

    QString startWith("Obj");
    QString d = script5;
    InsertCmd* b = new InsertCmd(startWith, d);

    print(b, d);

#ifdef DEBUG
    return EXIT_SUCCESS;
#endif

    b = new InsertCmd(startWith, script);
    print(b, script);
    b = new InsertCmd(startWith, script3);
    print(b, script3);
    b = new InsertCmd(startWith, script2);
    print(b, script2);
    b = new InsertCmd(startWith, script2);
    print(b, script2);


//    return a.exec();
}
