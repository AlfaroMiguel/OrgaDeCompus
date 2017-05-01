#include <mips/regdef.h>
#include <sys/syscall.h>
#include "base64.h"
    .text
    .align 2
    .globl base64_encode
    .ent base64_encode

base64_encode:
