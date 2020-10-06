#include "Router.h"

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif

const char *Router::method(FCGX_Request &req) {
    /// https://developer.mozilla.org/ru/docs/Web/HTTP/Methods
    /// GET, POST, maybe PUT, DELETE, HEAD, CONNECT, OPTIONS, TRACE, PATCH
    const char* _method = FCGX_GetParam("REQUEST_METHOD", req.envp);
    #ifdef DEBUG
    std::cout << "method: [" << _method << "]" << std::endl;
    #endif

    return FCGX_GetParam("REQUEST_METHOD", req.envp);
}
const char *Router::uri(FCGX_Request &req) {
    /// uri: /index.dsfsd&dsdsf=22
    const char* _uri = FCGX_GetParam("REQUEST_URI", req.envp);
    #ifdef DEBUG
    std::cout << "uri: [" << _uri << "]" << std::endl;
    #endif

    return _uri;
}
const char *Router::url(FCGX_Request &req) {
    /// url: /index.dsfsd
    const char* _url = FCGX_GetParam("DOCUMENT_URI", req.envp);
    #ifdef DEBUG
    std::cout << "url: [" << _url << "]" << std::endl;
    #endif

    return _url;
}
const char *Router::getData(FCGX_Request &req) {
    const char* _getData = FCGX_GetParam("QUERY_STRING", req.envp);
    #ifdef DEBUG
    std::cout << "getData: [" << _getData << "]" << std::endl;
    #endif

    return _getData;
}

const char *Router::contentType(FCGX_Request &req) {
    /// Content-type: text/html
    const char *_contentType = FCGX_GetParam("CONTENT_TYPE", req.envp);
    #ifdef DEBUG
    std::cout << "ContentType:" << _contentType << std::endl;
    #endif

    return _contentType;
}
int Router::contentLength(FCGX_Request &req) {
    /// length of body (post)
    int _contentLength = atoi(FCGX_GetParam("CONTENT_LENGTH", req.envp));
    #ifdef DEBUG
    std::cout << "ContentLength:" << _contentLength << std::endl;
    #endif

    return _contentLength;
}

void Router::setPostData(FCGX_Request &req, Obj* obj) {
    int _contentLength;
    if ((_contentLength = contentLength(req)) > 0)
        obj->setPostData(req, _contentLength);
}
