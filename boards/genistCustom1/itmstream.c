/**
 * itmstream.c
 *
 *  Created on: 2013-04-28
 *      Author: jeromeg
 */

#include <stdarg.h>
#include "ch.h"
#include "hal.h"


size_t ITMWrite(void *instance, const uint8_t *bp, size_t n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        ITM_SendChar(bp[i]);
    }
    return n;
}

msg_t ITMPut(void *instance, uint8_t b)
{
    ITM_SendChar(b);
    return 0;
}

struct BaseSequentialStreamVMT ITMStreamOpts = {
        .write = ITMWrite,
        .put = ITMPut
};

BaseSequentialStream ITMStream = {
        .vmt = &ITMStreamOpts
};
