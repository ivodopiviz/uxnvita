#include "../uxn.h"
#include "system.h"

#include <stdio.h>

/*
Copyright (c) 2022 Devine Lu Linvega, Andrew Alderwick

Permission to use, copy, modify, and distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE.
*/

static const char *errors[] = {
	"Working-stack underflow",
	"Return-stack underflow",
	"Working-stack overflow",
	"Return-stack overflow",
	"Working-stack division by zero",
	"Return-stack division by zero"};

static void
system_print(Stack *s, char *name)
{
	Uint8 i;
	fprintf(stderr, "<%s>", name);
	for(i = 0; i < s->ptr; i++)
		fprintf(stderr, " %02x", s->dat[i]);
	if(!i)
		fprintf(stderr, " empty");
	fprintf(stderr, "\n");
}

void
system_inspect(Uxn *u)
{
	system_print(&u->wst, "wst");
	system_print(&u->rst, "rst");
}

int
uxn_halt(Uxn *u, Uint8 error, Uint16 addr)
{
	Device *d = &u->dev[0];
	Uint16 vec = GETVECTOR(d);
	DEVPOKE16(0x4, addr);
	d->dat[0x6] = error;
	if(vec) {
		/* need to rearm to run System/vector again */
		d->dat[0] = 0;
		d->dat[1] = 0;
		if(error != 2) /* working stack overflow has special treatment */
			vec += 0x0004;
		return uxn_eval(u, vec);
	}
	system_inspect(u);
	fprintf(stderr, "Halted: %s#%04x, at 0x%04x\n", errors[error], u->ram[addr], addr);
	return 0;
}

/* IO */

Uint8
system_dei(Device *d, Uint8 port)
{
	switch(port) {
	case 0x2: return d->u->wst.ptr;
	case 0x3: return d->u->rst.ptr;
	default: return d->dat[port];
	}
}

void
system_deo(Device *d, Uint8 port)
{
	switch(port) {
	case 0x2: d->u->wst.ptr = d->dat[port]; break;
	case 0x3: d->u->rst.ptr = d->dat[port]; break;
	case 0xe: system_inspect(d->u); break;
	default: system_deo_special(d, port);
	}
}
