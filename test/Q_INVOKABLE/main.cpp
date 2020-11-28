// https://doc.qt.io/qt-5/qobject.html#Q_INVOKABLE
#include <QCoreApplication>

#include "Test.h"
#include <QDebug>

QString inv(QObject* obj, QString fun, QString str) {
    QString retVal;
    QMetaObject::invokeMethod(obj, fun.toUtf8(), Qt::DirectConnection,
                              Q_RETURN_ARG(QString, retVal),
                              Q_ARG(QString, str));


    return retVal;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Test t;

    QString retVal;
    QMetaObject::invokeMethod(&t, "t", Qt::DirectConnection,
                              Q_RETURN_ARG(QString, retVal),
                              Q_ARG(QString, "sqrt1"),
                              Q_ARG(QString, "sqrt2"));
    qInfo() << "retVal:" << retVal;

    qInfo() << inv(&t, "t2", "TEST_INV");

    return EXIT_SUCCESS;
}
