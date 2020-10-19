#include "ClassicHTMLRouter.h"
#include "Router/Router.h"
#include "RouterJS/RouterJS.h"
#include "RouterCSS/RouterCSS.h"
#include "RouterPost/RouterPost.h"

#include <qqml.h>

void RouterPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<Router>(uri, 1, 0, "Router");
    qmlRegisterType<RouterJS>(uri, 1, 0, "RouterJS");
    qmlRegisterType<RouterCSS>(uri, 1, 0, "RouterCSS");
    qmlRegisterType<RouterPost>(uri, 1, 0, "RouterPost");
}
