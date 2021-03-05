#ifndef __SHT30_H_
#define __SHT30_H_

#include "stdbool.h"
#include <stdint.h>

#define    SHT30_ADDR_WRITE    0x44<<1         //10001000
#define    SHT30_ADDR_READ        (0x44<<1)+1        //10001011


typedef enum
{
    /* ?????? */

    SOFT_RESET_CMD = 0x30A2,    
    /*
    ??????
    ????:Repeatability_CS_CMD
    CS: Clock stretching
    */
    HIGH_ENABLED_CMD    = 0x2C06,
    MEDIUM_ENABLED_CMD  = 0x2C0D,
    LOW_ENABLED_CMD     = 0x2C10,
    HIGH_DISABLED_CMD   = 0x2400,
    MEDIUM_DISABLED_CMD = 0x240B,
    LOW_DISABLED_CMD    = 0x2416,

    /*
    ??????
    ????:Repeatability_MPS_CMD
    MPS:measurement per second
    */
    HIGH_0_5_CMD   = 0x2032,
    MEDIUM_0_5_CMD = 0x2024,
    LOW_0_5_CMD    = 0x202F,
    HIGH_1_CMD     = 0x2130,
    MEDIUM_1_CMD   = 0x2126,
    LOW_1_CMD      = 0x212D,
    HIGH_2_CMD     = 0x2236,
    MEDIUM_2_CMD   = 0x2220,
    LOW_2_CMD      = 0x222B,
    HIGH_4_CMD     = 0x2334,
    MEDIUM_4_CMD   = 0x2322,
    LOW_4_CMD      = 0x2329,
    HIGH_10_CMD    = 0x2737,
    MEDIUM_10_CMD  = 0x2721,
    LOW_10_CMD     = 0x272A,
    /* ???????????? */
    READOUT_FOR_PERIODIC_MODE = 0xE000,
} SHT30_CMD;

static uint8_t    SHT30_Send_Cmd(SHT30_CMD cmd);
void SHT30_Reset(void);
uint8_t SHT30_Init(void);
uint8_t SHT30_Read_Dat(uint8_t* dat);
uint8_t CheckCrc8(uint8_t* const message, uint8_t initial_value);
uint8_t SHT30_Dat_To_Float(uint8_t* const dat, float* temperature, float* humidity);




#endif
