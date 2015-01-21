/*
 * Copyright (c) 2014, Konstantin Pugin. 
 * All rights reserved.
 *
 * GOST main header.
 *
 */

#ifndef _STRIBOG_H
#define _STRIBOG_H 1

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <endian.h>
#include <bits/wordsize.h>

#define ALIGN(x) __attribute__ ((__aligned__(x)))

ALIGN(16) union uint512_u
{
    unsigned long long QWORD[8];
} uint512_u;


ALIGN(16) struct stribog_ctx
{
    ALIGN(16) unsigned char buffer[64];
    ALIGN(16) union uint512_u hash;
    ALIGN(16) union uint512_u h;
    ALIGN(16) union uint512_u N;
    ALIGN(16) union uint512_u Sigma;
    size_t bufsize;
    unsigned int digest_size;
};

extern void __stribog_init_ctx (struct stribog_ctx *ctx) __THROW;  

extern void __stribog_process_bytes (const void *buffer, size_t len,
				    struct stribog_ctx *ctx) __THROW;
				    
extern void *__stribog_finish_ctx (struct stribog_ctx *ctx, void *resbuf)
  __THROW;

#endif /* stribog.h */
