/*
 * pmic.h
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
#ifndef CPU_RTC_SS_H
#define CPU_RTC_SS_H
    #include <rtc.h>

    /* RTC register addresses */
    #define CPU_RTC_SS_BASEADDR              0x44E3E000
    #define CPU_RTC_SS_SECONDS_REG_ADDR     (CPU_RTC_SS_BASEADDR + 0x0)
    #define CPU_RTC_SS_MINUTES_REG_ADDR     (CPU_RTC_SS_BASEADDR + 0x4)
    #define CPU_RTC_SS_HOURS_REG_ADDR       (CPU_RTC_SS_BASEADDR + 0x8)
    #define CPU_RTC_SS_DAYS_REG_ADDR        (CPU_RTC_SS_BASEADDR + 0xc)
    #define CPU_RTC_SS_MONTHS_REG_ADDR      (CPU_RTC_SS_BASEADDR + 0x10)
    #define CPU_RTC_SS_YEARS_REG_ADDR       (CPU_RTC_SS_BASEADDR + 0x14)
    #define CPU_RTC_SS_WEEKS_REG_ADDR       (CPU_RTC_SS_BASEADDR + 0x18)
    #define CPU_RTC_SS_CTRL_REG_ADDR        (CPU_RTC_SS_BASEADDR + 0x40)
    #define CPU_RTC_SS_STATUS_REG_ADDR      (CPU_RTC_SS_BASEADDR + 0x44)

    #ifdef CONFIG_SPL_BUILD
        #define RTC_KICK0_REG		0x6c
        #define RTC_KICK1_REG		0x70
        #define RTC_OSC_REG		    0x54

        void rtc32k_enable(void);    
    #endif

    /* Get the current time from the RTC */
    int cpu_rtc_ss_get(struct rtc_time *tmp);
    
    /* Set the RTC */
    int cpu_rtc_ss_set(struct rtc_time *tmp);
    
    /* Reset the RTC */
    void cpu_rtc_ss_reset(void);
#endif
