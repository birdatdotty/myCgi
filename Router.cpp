#include "Router.h"
#include "Page.h"

#include <QFile>

#ifdef DEBUG
#include <iostream>
#endif

Router::Router(QString root, QObject *parent)
    : QObject(parent),
      root(root),
      watcher(new QFileSystemWatcher(this)),
      engine(new QJSEngine),
      obj(new Obj)
{
    QJSValue jsObj = engine->newQObject(obj);
    engine->globalObject().setProperty("Obj", jsObj);
    connect(watcher, &QFileSystemWatcher::fileChanged,
            this, &Router::fileChanged);
}

void Router::request(FCGX_Request &req)
{
    // https://developer.mozilla.org/ru/docs/Web/HTTP/Methods
    // GET, POST, maybe PUT, DELETE, HEAD, CONNECT, OPTIONS, TRACE, PATCH
    const char *method = FCGX_GetParam("REQUEST_METHOD", req.envp);
    /// uri: /index.dsfsd&dsdsf=22
    const char *uri = FCGX_GetParam("REQUEST_URI", req.envp);
    /// url: /index.dsfsd
    const char *url = FCGX_GetParam("DOCUMENT_URI", req.envp);
    /// get: dsdsf=22
    const char *getData = FCGX_GetParam("QUERY_STRING", req.envp);
    /// Content-type: text/html
    const char *ContentType = FCGX_GetParam("CONTENT_TYPE", req.envp);
    /// length of body (post)
    const int ContentLength = atoi(FCGX_GetParam("CONTENT_LENGTH", req.envp));

#ifdef DEBUG
    std::cout << "request:" << std::endl;
    std::cout << "method \t " << method << std::endl;
    std::cout << "ContentType \t " << ContentType << std::endl;
    std::cout << "uri \t " << uri << std::endl;
#endif


    char* postData;
    if (ContentLength > 0) {
      postData = (char*) malloc(ContentLength+1);
      FCGX_GetStr(postData, ContentLength, req.in);
      postData[ContentLength] = '\0';
      if (strcmp(ContentType, "application/x-www-form-urlencoded") == 0)
          obj->setPostUrlencoded(postData);
      else if (strcmp(ContentType, "application/json") == 0)
          obj->setPostJson(postData);
    }

#ifdef DEBUG
      std::cout << "postData: " << postData << std::endl;
#endif

    Page *page;
    if (!pages.contains(url)) {
        QString file = root + url;
        page = new Page(root, url);
        if (QFile::exists(file)) {
            watcher->addPath( file );
            pages[url] = page;
        }
    }
    else page = pages[url];

    QJsonObject json = str2json(getData);
    QJsonObject data;
    data["page"] = url;
#ifdef DEBUG
    data["method"] = method;
    data["url"] = url;
    data["get"] = getData;
#endif

    obj->set(data);
    QByteArray pageOut = page->out(engine,obj).toUtf8();

    //Завершаем запрос
    //DLLAPI int FCGX_PutStr(const char *str, int n, FCGX_Stream *stream);
    //DLLAPI int FCGX_FPrintF(FCGX_Stream *stream, const char *format, ...);
    //...
    FCGX_PutStr(pageOut, pageOut.size(), req.out);

    if (ContentLength > 0)
        free(postData);

    FCGX_Finish_r(&req);
}

QJsonObject Router::str2json(QString str)
{
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

void Router::fileChanged(const QString &path) {
    if (!path.startsWith(root))
        return;

    QString key = path;
    key = key.remove(0, root.size());

    if (pages.contains(key)) {
        pages.remove(key);
        watcher->removePath(path);
    }
}
