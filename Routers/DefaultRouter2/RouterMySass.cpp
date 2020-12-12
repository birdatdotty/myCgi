#include "RouterMySass.h"
#include <qqml.h>

#include "LibRouterMySass.h"


void RouterMySass::registerTypes(const char *uri)
{
    qmlRegisterType<LibRouterMySass>(uri, 1, 0, "RouterMySass");
}
