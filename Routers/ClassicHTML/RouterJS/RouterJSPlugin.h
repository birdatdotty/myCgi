#ifndef ROUTERJSPLUGIN_H
#define ROUTERJSPLUGIN_H

#include <QQmlExtensionPlugin>


class RouterJSPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // ROUTERJSPLUGIN_H
