#ifndef DEFAULTPAGE_H
#define DEFAULTPAGE_H

#include <QObject>

class DefaultPage
{
protected:
    void setDefaultPage(QString newDefaultPage) { m_defaultPage = newDefaultPage; }

public:
    QString getDefaultPage() const { return m_defaultPage; }

private:
    QString m_defaultPage;
};

#endif // DEFAULTPAGE_H
