// sudo apt-get install libfcgi-dev
// g++ cgi2.cc -lfcgi -o cgi2

// https://habr.com/ru/post/154187/
// https://developers.webasyst.ru/docs/installation/tips/nginx-fastcgi/
// https://stackoverflow.com/questions/12954196/how-to-access-a-body-of-post-request-using-fastcgi-c-c-application
// http://cgi.sourceforge.net/docs/fastcgi___cgi/tutorial/fastcgi.html
// http://chriswu.me/blog/getting-request-uri-and-content-in-c-plus-plus-fcgi/

#include "Router.h"
#include "RouterListen.h"
#include <QCoreApplication>
#include <QJSEngine>

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

    //Глубина стека запросов
    int listenQueueBacklog = 400;

    //Задаем unix socket
    const char* path = "/home/1/fcgi.sock";

    // Создаем router для оброботки входящих соединений:
    Router *router = new Router("/var/www/html/");

    // создаем и запускаем прослушивание в отдельном потоке:
    RouterListen *routerListen = new RouterListen(path, listenQueueBacklog, router);
    routerListen->start();
    chmod(path, ALLPERMS);


    return app.exec();
}
