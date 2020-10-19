#ifndef ROUTERCSSPLUGIN_H
#define ROUTERCSSPLUGIN_H

#include <QQmlExtensionPlugin>


class RouterCSSPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // ROUTERCSSPLUGIN_H
