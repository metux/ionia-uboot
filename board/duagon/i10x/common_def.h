/*
 * common_def.h
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
#ifndef __COMMON_DEF_H__
#define __COMMON_DEF_H__

/* AM335X type */
#define BONE_BOARD	0
#define GP_BOARD	1
#define IA_BOARD	2
#define IPP_BOARD	3
#define BASE_BOARD	4
#define SK_BOARD	5
#define DUAGON_I10X_BOARD	100

/* Profiles */
#define PROFILE_NONE	0x0
#define PROFILE_0	(1 << 0)
#define PROFILE_1	(1 << 1)
#define PROFILE_2	(1 << 2)
#define PROFILE_3	(1 << 3)
#define PROFILE_4	(1 << 4)
#define PROFILE_5	(1 << 5)
#define PROFILE_6	(1 << 6)
#define PROFILE_7	(1 << 7)
#define PROFILE_ALL	0xFF

extern void pll_init(void);
extern void ddr_pll_config(unsigned int ddrpll_M);
extern void mpu_pll_config(int mpupll_M);
extern void enable_ddr2_clocks(void);
extern void enable_ddr3_clocks(void);

extern void enable_i2c0_pin_mux(void);
extern void enable_uart0_pin_mux(void);
extern void enable_DBG_LED_CPU_pin_mux(void);
extern void enable_SYSBOOT_pin_mux(void);

/* extern void enable_gpio0_7_pin_mux(void);*/
extern void configure_evm_pin_mux(unsigned char daughter_board_id,
					char daughter_board_version[],
					unsigned short daughter_board_profile,
					unsigned int daughter_board_flag);

#ifndef CONFIG_NO_ETH
extern void configure_i10x_rmii_pin_mux(unsigned char daughter_board_id,
					char daughter_board_version[],
					unsigned short daughter_board_profile,
					unsigned int daughter_board_flag);
                    
extern void configure_i10x_mii_pin_mux(unsigned char daughter_board_id,
					char daughter_board_version[],
					unsigned short daughter_board_profile,
					unsigned int daughter_board_flag);

#endif
/* Debug stuff */
/*#define debug(fmt,args...)      printf (fmt ,##args)*/ /*Does not boot in u-boot-spl*/
#endif/*__COMMON_DEF_H__ */
