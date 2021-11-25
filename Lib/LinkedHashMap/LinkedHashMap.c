#include "LinkedHashMap.h"
#include <stdlib.h>


/*




    // Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
    // https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function


 */

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

static unsigned long hash_key(const char *key) {
    unsigned long hash = FNV_OFFSET;
    for (const char *p = key; *p; p++) {
        hash ^= (unsigned long long int) (unsigned char) (*p);
        hash *= FNV_PRIME;
    }
    return hash;
}


static const linkedHashMap LHM = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
};

const linkedHashMap *__restrict LinkedHashMapClass = &LHM;
