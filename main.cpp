// sudo apt-get install libfcgi-dev
// g++ cgi2.cc -lfcgi -o cgi2

// https://habr.com/ru/post/154187/
// https://developers.webasyst.ru/docs/installation/tips/nginx-fastcgi/
// https://stackoverflow.com/questions/12954196/how-to-access-a-body-of-post-request-using-fastcgi-c-c-application
// http://cgi.sourceforge.net/docs/fastcgi___cgi/tutorial/fastcgi.html
// http://chriswu.me/blog/getting-request-uri-and-content-in-c-plus-plus-fcgi/

//#include "Router.h"
//#include "RouterJS.h"
#include "RouterListen.h"
//#include "RouterPost.h"
//#include "RouterCss.h"
#include "Service.h"


#include <QCoreApplication>
#include <QJSEngine>

#include <QQmlEngine>
#include <QQmlComponent>

#include "config.h"

/**
send post with curl:
curl --header "Content-Type: application/x-www-form-urlencoded"   --request POST   --data 'text=sssq2s'   'http://localhost/put.unix'
*/

#include <string>
#include <stdlib.h>
#include <sys/stat.h>

#include <fcgi_stdio.h>

#ifdef DEBUG
    #include <iostream>
    #include <QDebug>
#endif

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    #ifdef DEBUG
        qInfo() << "DEBUG";
    #endif
    if(FCGX_Init())
        exit(1); //Инициализируем библиотеку перед работой.

    qmlRegisterType<Service>("Service", 1,0, "Service");

    QQmlEngine engine;
//    engine.addImportPath("/usr/local/lib/myCgi2/plugins/");
    engine.setImportPathList(QStringList() << "/usr/local/lib/myCgi2/plugins/");

    QString qmlFile;
    if (argc == 1)
        qmlFile = ETC_FILE;
    else
        qmlFile = argv[1];

    QQmlComponent component(&engine, QUrl(qmlFile));

    if (component.status() != QQmlComponent::Status::Ready)
    {
        qDebug() << "Component status is not ready";

        foreach(QQmlError err, component.errors())
        {
            qInfo() << engine.importPathList();
            qInfo() << "Description: " << err.description() << "\n\n";
            qDebug() << err.toString();
        }

        qDebug() << component.errorString();
        return -1;
    }
    else
    {
        component.create();
    }

    return app.exec();
}
