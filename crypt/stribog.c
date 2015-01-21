/*
 * Copyright (c) 2014, Konstantin Pugin. 
 * Based on Alexey Degtyarev`s implementation.
 * All rights reserved.
 *
 * GOST Hash main file.
 *
 */


#include "stribog.h"

#include <stribog-block.c>

void
__stribog_init_ctx(struct stribog_ctx *CTX)
{
    unsigned int i;

    memset(CTX, 0x00, sizeof(struct stribog_ctx));
    CTX->digest_size = 512;

    for (i = 0; i < 8; i++)
    {
       CTX->h.QWORD[i] = 0x00ULL;
    }
}

void
__stribog_process_bytes(const void *data, size_t len,struct stribog_ctx* CTX)
{
    size_t chunksize;

    while (len > 63 && CTX->bufsize == 0)
    {
        stage2(CTX, data);

        data += 64;
        len  -= 64;
    }

    while (len)
    {
        chunksize = 64 - CTX->bufsize;
        if (chunksize > len)
            chunksize = len;

        memcpy(&CTX->buffer[CTX->bufsize], data, chunksize);

        CTX->bufsize += chunksize;
        len -= chunksize;
        data += chunksize;
        
        if (CTX->bufsize == 64)
        {
            stage2(CTX, CTX->buffer);

            CTX->bufsize = 0;
        }
    }
}

void*
__stribog_finish_ctx(struct stribog_ctx *CTX, void *digest)
{
    stage3(CTX);

    CTX->bufsize = 0;

    memcpy(digest, &(CTX->hash.QWORD[0]), 64);
    memset(CTX, 0x00, sizeof (struct stribog_ctx));
    return digest;
}
