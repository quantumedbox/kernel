#pragma once

#define KERNEL_BASE 0x1000
#define STACK_HEAD  0x00090000
#define IS_POINTER_VALID(ptr) ((ptr) >= (void*)KERNEL_BASE) && ((ptr) <= (void*)STACK_HEAD)
