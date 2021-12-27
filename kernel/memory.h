#pragma once

#define KERNEL_BASE 0x1000
#define STACK_HEAD  0x00090000
#define IS_POINTER_VALID(ptr) ((ptr) >= (void*)KERNEL_BASE) && ((ptr) <= (void*)STACK_HEAD)

#define LOW_8(x) (uint8_t)((x) & 0xff)
#define HIGH_8(x) (uint8_t)((x >> 8))

#define LOW_16(x) (uint16_t)((x) & 0xffff)
#define HIGH_16(x) (uint16_t)((x >> 16))
