#ifndef MYCGI2ROUTETEST_PLUGIN_H
#define MYCGI2ROUTETEST_PLUGIN_H

#include <QQmlExtensionPlugin>

class MyCgi2RouteTestPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // MYCGI2ROUTETEST_PLUGIN_H
