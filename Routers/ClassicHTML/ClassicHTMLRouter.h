#ifndef ROUTERPLUGIN_H
#define ROUTERPLUGIN_H

#include <QQmlExtensionPlugin>

class RouterPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // ROUTERPLUGIN_H
