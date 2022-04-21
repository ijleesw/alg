#include <cstdio>
#include <sys/time.h>
#include <sys/resource.h>

void printMemoryUsage() {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        long mu = usage.ru_maxrss;
        printf("Memory usage: %ld B, %ld KB, %ld MB\n", mu, mu / 1024, mu / 1048576);
    }
}
