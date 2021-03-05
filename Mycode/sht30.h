#ifndef __SHT30_H_
#define __SHT30_H_

#include "stdbool.h"

#define SHT_ADDR (0x44<<1)

uint8_t sht30_init();

uint8_t sht30_sample(float *t, float *h);

#endif