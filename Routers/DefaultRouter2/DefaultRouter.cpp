#include "DefaultRouter.h"
#include "RouterCSS.h"
#include "RouterHTML.h"
#include "RouterPost.h"
#include "RouterJS.h"
#include "RouterChunk.h"

#include <qqml.h>


void DefaultRouter::registerTypes(const char *uri)
{
    qmlRegisterType<RouterCSS>(uri, 1,0, "RouterCSS");
    qmlRegisterType<RouterJS>(uri, 1,0, "RouterJS");
    qmlRegisterType<RouterPost>(uri, 1,0, "RouterPost");
    qmlRegisterType<RouterHTML>(uri, 1,0, "RouterHTML");
    qmlRegisterType<RouterChunk>(uri, 1,0, "RouterChunk");
}
