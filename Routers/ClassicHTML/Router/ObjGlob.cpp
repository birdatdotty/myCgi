#include "ObjGlob.h"
#include "Request.h"

#include "Router.h"

#ifdef DEBUG
    #include <QDebug>
    #include <iostream>
#endif

ObjGlob::ObjGlob(Router *router)
    : QObject(nullptr),
      Chunks(router),
      Scripts(router),
      m_router(router),
      m_count(20)
{
}

QString ObjGlob::auth(QString login, QString password)
{
    if (users.contains(login)) {
        QString pass = users[login];
        if (password == pass) {
            if (ids.contains(login))
                return "{auth:true,id:" + ids[login] + "}";

            QString id = getRandomString();
            ids[login] = id;
            return "{auth:true,id:" + id + "}";
        }
    }

    return "{auth:false}";
}

bool ObjGlob::test(QString id)
{
    return ids.contains(id);
}

int ObjGlob::count()
{
    return ++m_count;
}

QString ObjGlob::getRandomString(int randomStringLength) const
{
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    QString randomString;
    for(int i=0; i<randomStringLength; ++i)
    {
        int index = rand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}

void ObjGlob::setRoot(QString newRoot)  { m_root = newRoot; }
QString ObjGlob::getRoot() const { return m_root; }

