#include "RouterJSPlugin.h"
#include "RouterJS.h"

#include <qqml.h>


void RouterJSPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<RouterJS>(uri, 1, 0, "RouterJS");
}
