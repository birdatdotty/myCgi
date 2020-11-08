#ifndef FCGIREQUEST_H
#define FCGIREQUEST_H

#include <fcgi_stdio.h>
#include <QObject>
#include <QJsonObject>

class FCGIRequest
{
public:
    FCGIRequest();
    FCGIRequest(FCGX_Request &request);

    QString url() const;
    QString method() const;

    QString uri() const;
    QString getData() const;
    QString contentType() const;
    int contentLength() const;
//    void setPostData(FCGX_Request &req, Request *obj);
    QJsonObject get2json() const;


    void finish();
    FCGX_Stream *out(){
        return request.out;
    }
    void send(QByteArray &byteArray);

//private:
    FCGX_Request request;

};

#endif // FCGIREQUEST_H
