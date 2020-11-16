#ifndef FCGIREQUEST_H
#define FCGIREQUEST_H

class Page;

#include <fcgi_stdio.h>
#include <QObject>
#include <QJsonObject>

#include <QJSEngine>

class FCGIRequest
{
public:
    FCGIRequest();
//    FCGIRequest(FCGX_Request request);

    QString url() const;
    QString method() const;

    QString uri() const;
    QString getData() const;
    QString contentType() const;
    int contentLength() const;
//    void setPostData(FCGX_Request &req, Request *obj);
    QJsonObject get2json() const;


    void finish();
    FCGX_Stream *out();
    void send(QByteArray &byteArray);
    void send(Page* page);

    void setRequest(FCGX_Request *newRequest) {
        request = *newRequest;
    }


//private:
    FCGX_Request request;

    void setEngine(QJSEngine *newEngine);

//private:
    QJSEngine *engine;

};

#endif // FCGIREQUEST_H
