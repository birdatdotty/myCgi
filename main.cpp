// sudo apt-get install libfcgi-dev
// g++ cgi2.cc -lfcgi -o cgi2

// https://habr.com/ru/post/154187/
// https://developers.webasyst.ru/docs/installation/tips/nginx-fastcgi/
// https://stackoverflow.com/questions/12954196/how-to-access-a-body-of-post-request-using-fastcgi-c-c-application
// http://cgi.sourceforge.net/docs/fastcgi___cgi/tutorial/fastcgi.html
// http://chriswu.me/blog/getting-request-uri-and-content-in-c-plus-plus-fcgi/

#include "Router.h"
#include "RouterJs.h"
#include "RouterListen.h"
#include "RouterPost.h"
#include "RouterCss.h"
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
    qmlRegisterType<Router>("Service", 1,0, "Router");

    qmlRegisterType<RouterCSS>("RouterCSS", 1,0, "RouterCSS");
    qmlRegisterType<RouterJS>("RouterJS", 1,0, "RouterJS");
    qmlRegisterType<RouterPost>("RouterPost", 1,0, "RouterPost");

    QQmlEngine engine;
    QQmlComponent component(&engine, QUrl(ETC_FILE));
//    Service *service =
            qobject_cast<Service *>(component.create());



    return app.exec();
}
