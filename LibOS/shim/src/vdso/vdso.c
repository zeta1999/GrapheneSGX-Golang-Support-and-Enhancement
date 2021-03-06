/* -*- mode:c; c-file-style:"k&r"; c-basic-offset: 4; tab-width:4; indent-tabs-mode:nil; mode:auto-fill; fill-column:78; -*- */
/* vim: set ts=4 sw=4 et tw=78 fo=cqt wm=0: */

/* Copyright (C) 2018 Intel Corporation
                      Isaku Yamahata <isaku.yamahata at gmail.com>
                                     <isaku.yamahata at intel.com>
   All Rights Reserved.

   This file is part of Graphene Library OS.

   Graphene Library OS is free software: you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   Graphene Library OS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <api.h>
#include <shim_types.h>
#include "glibc-version.h"

int __vdso_clock_gettime(clockid_t clock, struct timespec *t)
{
    __UNUSED(clock);
    __UNUSED(t);
    return 0;
}
int clock_gettime(clockid_t clock, struct timespec *t)
    __attribute__((weak, alias("__vdso_clock_gettime")));

int __vdso_gettimeofday(struct timeval *tv, struct timezone *tz)
{
    __UNUSED(tv);
    __UNUSED(tz);
    return 0;
}
int gettimeofday(struct timeval *tv, struct timezone *tz)
    __attribute__((weak, alias("__vdso_gettimeofday")));

time_t __vdso_time(time_t *t)
{
    __UNUSED(t);
    return 0;
}
time_t time(time_t *t) __attribute__((weak, alias("__vdso_time")));

long __vdso_getcpu(unsigned *cpu, struct getcpu_cache *unused)
{
    __UNUSED(cpu);
    __UNUSED(unused);
    return 0;
}
long getcpu(unsigned *cpu, struct getcpu_cache *unused)
    __attribute__((weak, alias("__vdso_getcpu")));


/* graphene specific symbols */
const int __vdso_glibc_version = GLIBC_VERSION;
extern int glibc_version __attribute__((weak, alias("__vdso_glibc_version")));

long __vdso_syscalldb(
    long a0, long a1, long a2, long a3, long a4, long a5, long a6)
{
    __UNUSED(a0);
    __UNUSED(a1);
    __UNUSED(a2);
    __UNUSED(a3);
    __UNUSED(a4);
    __UNUSED(a5);
    __UNUSED(a6);
    return -ENOSYS;
}
extern long syscalldb(
    long a0, long a1, long a2, long a3, long a4, long a5, long a6)
    __attribute__((alias("__vdso_syscalldb")));

/* notes section: .note.Linux */
__asm__(".pushsection .note.Linux, \"a\", @note\n");
struct __Elf64_Nhdr {
    Elf64_Nhdr nhdr;
    /* 6 = length of "Linux" (including tailing '\0')*/
    unsigned char name[6] __attribute__((aligned(sizeof(Elf64_Word))));
    // unsigned char desc[0] __attribute__((aligned(sizeof(Elf64_Word))));
    unsigned int desc __attribute__((aligned(sizeof(Elf64_Word))));
};

struct __Elf64_Nhdr __vdso_note_Linux
__attribute__((aligned(sizeof(Elf64_Word)), unused)) = {
    .nhdr.n_namesz = 6,
    .nhdr.n_descsz = sizeof(int),
    .nhdr.n_type = 0,
    .name = "Linux",
    .desc = 267008,  /* LINUX_VERSION_CODE */
};
struct __Elf64_Nhdr __vdso_note_Linux_salt
__attribute__((aligned(sizeof(Elf64_Word)), unused)) = {
    .nhdr.n_namesz = 6,
    .nhdr.n_descsz = sizeof(int),
    .nhdr.n_type = 0x100,
    .name = "Linux",
    .desc = 0,  /* CONFIG_BUILD_SALT TODO */
};
__asm__(".popsection\n");
