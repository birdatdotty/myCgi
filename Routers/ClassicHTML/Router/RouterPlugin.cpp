#include "RouterPlugin.h"
#include "Router.h"

#include <qqml.h>

void RouterPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<Router>(uri, 1, 0, "Router");
}
