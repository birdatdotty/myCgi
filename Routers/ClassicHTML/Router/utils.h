#ifndef UTILS_H
#define UTILS_H

#include <cstring>

inline bool startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre
            ? false
            : memcmp(pre, str, lenpre) == 0;
}


#endif // UTILS_H
