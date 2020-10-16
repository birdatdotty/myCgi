#include "mycgi2routetest_plugin.h"

#include "mycgi2routetest.h"

#include <qqml.h>

void MyCgi2RouteTestPlugin::registerTypes(const char *uri)
{
    // @uri MyCgi2RouteTest
    qmlRegisterType<MyCgi2RouteTest>(uri, 1, 0, "MyCgi2RouteTest");
}

