//https://habr.com/ru/post/154187/

#include <pthread.h>
#include <sys/types.h>
#include <QDebug>

#include "fcgi_config.h"
#include "fcgiapp.h"

#include <QObject>
#include <QTest>

#define THREAD_COUNT 4
#define SOCKET_PATH "127.0.0.1:9000"


class MyTest: public QObject {
public:
    MyTest(QString str): str(str) {}
    const char* p()  {return str.toUtf8();}

private:
    QString str;
};

//хранит дескриптор открытого сокета
static int socketId;
static int oo = 1;

pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;

static void *doit(void *a)
{
    int rc, i = ++oo;
    MyTest *myTest = (MyTest*) a;
    FCGX_Request request;
    char *server_name;

    if(FCGX_InitRequest(&request, socketId, 0) != 0)
    {
        //ошибка при инициализации структуры запроса
        qInfo("Can not init request");
        return NULL;
    }
    qInfo("Request is inited");

    for(;;)
    {

        //попробовать получить новый запрос
        qInfo("Try to accept new request");
        pthread_mutex_lock(&accept_mutex);
        rc = FCGX_Accept_r(&request);
        pthread_mutex_unlock(&accept_mutex);

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
            FCGX_PutS(myTest->p(), request.out);
        }

        //закрыть текущее соединение
        FCGX_Finish_r(&request);

        //завершающие действия - запись статистики, логгирование ошибок и т.п.

        //"заснуть" - имитация многопоточной среды
        QTest::qWait(i*1000);
    }

    return NULL;
}


int main(void)
{
    int i;
    pthread_t id[THREAD_COUNT];

    //инициализация библилиотеки
    FCGX_Init();
    qInfo("Lib is inited");

    //открываем новый сокет
    socketId = FCGX_OpenSocket(SOCKET_PATH, 20);
    if(socketId < 0)
    {
        //ошибка при открытии сокета
        return 1;
    }
    qInfo("Socket is opened");

    //
    MyTest *myTest[4] = {
        new MyTest("ss11\n"),
        new MyTest("bb22\n"),
        new MyTest("qq33\n"),
        new MyTest("tt44\n")
    };

    //создаём рабочие потоки
    for(i = 0; i < THREAD_COUNT; i++)
    {
//        pthread_create(&id[i], NULL, doit, NULL);
        pthread_create(&id[i], NULL, doit, myTest[i]);
    }

    //ждем завершения рабочих потоков
    for(i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(id[i], NULL);
    }

    return 0;
}
