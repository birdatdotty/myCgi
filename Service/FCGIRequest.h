#ifndef FCGIREQUEST_H
#define FCGIREQUEST_H

class Page;
class Router;

#include <fcgi_stdio.h>
#include <QObject>
#include <QJsonObject>

#include <QJSEngine>

class FCGIRequest
{
public:
    FCGIRequest();

    QString url(const Router *router) const;
    QString clearUrl() const;
    QString method() const;

    QString uri() const;
    QString getData() const;
    QString contentType() const;
    int contentLength() const;
    QJsonObject get2json() const;


    FCGX_Stream *out();

//private:
    FCGX_Request request;

};

#endif // FCGIREQUEST_H
