#pragma once

#include <time.h>

namespace Chal
{
    clock_t clock();
    time_t time(time_t*);
    double difftime (time_t end, time_t beginning);
    time_t mktime(struct tm *);

    char * asctime(const struct tm *);
    char * ctime(const time_t *);
    struct tm * gmtime(const time_t *);
    struct tm * localtime(const time_t *);
    size_t strftime(char *, size_t, const char *, const struct tm *);
}