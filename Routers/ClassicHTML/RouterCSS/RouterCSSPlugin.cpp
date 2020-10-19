#include "RouterCSSPlugin.h"
#include "RouterCSS.h"

#include <qqml.h>


void RouterCSSPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<RouterCSS>(uri, 1, 0, "RouterCSS");
}
