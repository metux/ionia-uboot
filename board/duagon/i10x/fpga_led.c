/* ==========================================================================
 *
 *  Purpose: turn on RED and GREEN Sys LEDs indicating that u-boot is running
 *
 *
 *  Licence: Duagon Software Licence (see file 'licence.txt')
 *
 * --------------------------------------------------------------------------
 *
 *  (C) COPYRIGHT, Duagon AG, CH-8953 Dietikon, Switzerland
 *  All Rights Reserved.
 *
 * ==========================================================================
 */
#include <common.h>
#pragma GCC optimize "O0"

u_int32_t fpga_LED_init( void )
{
    u_int32_t val;
    u_int32_t i;

    u_int32_t addr = 0x18000000;

    volatile u_int8_t *rbr_thr = (u_int8_t *)(addr + 0x10);
    volatile u_int8_t *lsr = (u_int8_t *)(addr + 0x1A);
    volatile u_int8_t *rsr = (u_int8_t *)(addr + 0x14);

    /* wait for fpga nios to start */
    udelay(10 * 1000 * 1000);
    
    printf("Turning on RED and GREEN Sys. LEDs\n");
    *lsr = 0x40;
    val = 0x0008010F;
    *rbr_thr = val & 0xFF;
    *rbr_thr = (val >>  8) & 0xFF;
    *rbr_thr = (val >> 16) & 0xFF;
    *rbr_thr = (val >> 24) & 0xFF;

    val = 0x00000011;
    *rbr_thr = val & 0xFF;
    *rbr_thr = (val >>  8) & 0xFF;
    *rbr_thr = (val >> 16) & 0xFF;
    *rbr_thr = (val >> 24) & 0xFF;

    val = 0x69766564;
    *rbr_thr = val & 0xFF;
    *rbr_thr = (val >>  8) & 0xFF;
    *rbr_thr = (val >> 16) & 0xFF;
    *rbr_thr = (val >> 24) & 0xFF;

    val = 0x735F6563;
    *rbr_thr = val & 0xFF;
    *rbr_thr = (val >>  8) & 0xFF;
    *rbr_thr = (val >> 16) & 0xFF;
    *rbr_thr = (val >> 24) & 0xFF;

    val = 0x65747379;
    *rbr_thr = val & 0xFF;
    *rbr_thr = (val >>  8) & 0xFF;
    *rbr_thr = (val >> 16) & 0xFF;
    *rbr_thr = (val >> 24) & 0xFF;

    val = 0x44454C6D;
    *rbr_thr = val & 0xFF;
    *rbr_thr = (val >>  8) & 0xFF;
    *rbr_thr = (val >> 16) & 0xFF;
    *rbr_thr = (val >> 24) & 0xFF;

    val = 0x00000000;
    *rbr_thr = val & 0xFF;
    *rbr_thr = (val >>  8) & 0xFF;
    *rbr_thr = (val >> 16) & 0xFF;
    *rbr_thr = (val >> 24) & 0xFF;

    val = 0x00000003;
    *rbr_thr = val & 0xFF;
    *rbr_thr = (val >>  8) & 0xFF;
    *rbr_thr = (val >> 16) & 0xFF;
    *rbr_thr = (val >> 24) & 0xFF;

    val = 0x00003433;
    *rbr_thr = val & 0xFF;
    *rbr_thr = (val >>  8) & 0xFF;
    *rbr_thr = (val >> 16) & 0xFF;
    *rbr_thr = (val >> 24) & 0xFF;

    /* wait for and flush reply */
    for ( i=1; i<2000; i++ ) {
        u_int8_t rcv;

        if ( *rsr ) {
            rcv = *rbr_thr;
        }
    }
    return 0;
}
