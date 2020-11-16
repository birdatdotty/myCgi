#include "FCGIRequest.h"

#ifdef DEBUG
    #include <iostream>
    #include <QDebug>
#include <QByteArray>
#endif

#include "Page.h"

FCGIRequest::FCGIRequest()
{
    engine = new QJSEngine;
}

//FCGIRequest::FCGIRequest(FCGX_Request request)
//    : request(request)
//{
//    engine = new QJSEngine;
//}

QString FCGIRequest::url() const
{
    return FCGX_GetParam("DOCUMENT_URI", request.envp);
}

QString FCGIRequest::method() const {
    /// https://developer.mozilla.org/ru/docs/Web/HTTP/Methods
    /// GET, POST, maybe PUT, DELETE, HEAD, CONNECT, OPTIONS, TRACE, PATCH

    return FCGX_GetParam("REQUEST_METHOD", request.envp);
}

QString FCGIRequest::   uri() const {
    /// uri: /index.dsfsd&dsdsf=22
    const char* _uri = FCGX_GetParam("REQUEST_URI", request.envp);
#ifdef DEBUG
    std::cout << "uri: [" << _uri << "]" << std::endl;
#endif

    return _uri;
}

QString FCGIRequest::getData() const {
    const char* _getData = FCGX_GetParam("QUERY_STRING", request.envp);
#ifdef DEBUG
    std::cout << "getData: [" << _getData << "]" << std::endl;
#endif

    return _getData;
}

QString FCGIRequest::contentType() const {
    /// Content-type: text/html
    const char *_contentType = FCGX_GetParam("CONTENT_TYPE", request.envp);
#ifdef DEBUG
    std::cout << "ContentType:" << _contentType << std::endl;
#endif

    return _contentType;
}

int FCGIRequest::contentLength() const {
    /// length of body (post)
    return atoi(FCGX_GetParam("CONTENT_LENGTH", request.envp));
}

QJsonObject FCGIRequest::get2json() const
{
    QString str = FCGX_GetParam("QUERY_STRING", request.envp);
    QJsonObject obj;
    /// str: login=asd&pass=dd
    bool isKey = true;
    QString key, value;

    for (int i = 0; i < str.size(); i++) {
        QChar ch = str.at(i);
        if (isKey) {
            if (ch != '=') key += ch;
            else isKey = false;
        }
        else {
            if (ch != '&') value += ch;
            else {
                isKey = true;
                obj[key] = value;
                key = value = "";
            }
        }
    }
    if (key.size() > 0)
        obj[key] = value;

    return obj;
}

void FCGIRequest::finish() {
    FCGX_Finish_r(&request);
}

FCGX_Stream *FCGIRequest::out(){
    return request.out;
}

#include <QTest>
void FCGIRequest::send(QByteArray &byteArray) {
    FCGX_PutStr(byteArray, byteArray.size(), request.out);
    FCGX_Finish_r(&request);

//    QTest::qWait(6000);
}

void FCGIRequest::send(Page *page)
{
    QByteArray byteArray;
    byteArray += page->contentType();
    byteArray += "\n\n";
    byteArray += page->out(engine);

    FCGX_PutStr(byteArray, byteArray.size(), request.out);
    FCGX_Finish_r(&request);

    qInfo() << __FILE__ << __LINE__ << "engine:" << engine << engine->evaluate("Obj.t()").toString();
}

void FCGIRequest::setEngine(QJSEngine *newEngine) {
    engine = newEngine;
    qInfo() << __FILE__ << __LINE__ << "engine:" << engine << engine->evaluate("Obj.t()").toString();
}
