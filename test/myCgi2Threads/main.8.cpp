//https://habr.com/ru/post/154187/
//https://www.opennet.ru/docs/RUS/qt3_prog/c7638.html

#include <pthread.h>
#include <sys/types.h>

#include <QCoreApplication>
#include <QDebug>

#include "fcgi_config.h"
#include "fcgiapp.h"

#include <QMutex>
#include <QObject>
#include <QTest>
#include <QThread>

#define THREAD_COUNT 4
#define SOCKET_PATH "127.0.0.1:9000"

static QMutex mutex;

class A: public QThread
{
public:
    A(int socketId, QString str): socketId(socketId), str(str) {}
    const char* p()  {return str.toUtf8();}

private:
    int socketId;
    QString str;

public:
    void run() override {
    int rc;
    FCGX_Request request;
    char *server_name;

    if(FCGX_InitRequest(&request, socketId, 0) != 0)
    {
        //ошибка при инициализации структуры запроса
        qInfo("Can not init request");
    }
    qInfo("Request is inited");

    for(;;)
    {

        //попробовать получить новый запрос
        qInfo("Try to accept new request");
        mutex.lock();
        rc = FCGX_Accept_r(&request);
        mutex.unlock();

        if(rc < 0)
        {
            //ошибка при получении запроса
            qInfo("Can not accept new request");
            break;
        }
        qInfo("request is accepted");

        //получить значение переменной
        server_name = FCGX_GetParam("SERVER_NAME", request.envp);
        {
            //вывести все HTTP-заголовки (каждый заголовок с новой строки)
            FCGX_PutS("Content-type: text/html\r\n", request.out);

            //между заголовками и телом ответа нужно вывести пустую строку
            FCGX_PutS("\r\n", request.out);

            //вывести тело ответа (например - html-код веб-страницы)
//            FCGX_PutS(s[i].toUtf8(), request.out);
            FCGX_PutS(p(), request.out);
        }

        //закрыть текущее соединение
        FCGX_Finish_r(&request);

        //завершающие действия - запись статистики, логгирование ошибок и т.п.

        //"заснуть" - имитация многопоточной среды
        QTest::qWait(3000);
    }

    }
};


int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    int i;

    //инициализация библилиотеки
    FCGX_Init();
    qInfo("Lib is inited");

    //открываем новый сокет
    int socketId = FCGX_OpenSocket(SOCKET_PATH, 20);
    if(socketId < 0)
    {
        //ошибка при открытии сокета
        return 1;
    }
    qInfo("Socket is opened");

    A *a[4] = {
        new A(socketId, "ss11\n"),
        new A(socketId, "bb22\n"),
        new A(socketId, "qq33\n"),
        new A(socketId, "tt44\n")
    };

    //ждем завершения рабочих потоков
    for(i = 0; i < THREAD_COUNT; i++)
        a[i]->start();

    return app.exec();
}
