#ifndef QMLROUTERMYSASS_H
#define QMLROUTERMYSASS_H

#include <QQmlExtensionPlugin>

class RouterChunk: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};


#endif // QMLROUTERMYSASS_H
