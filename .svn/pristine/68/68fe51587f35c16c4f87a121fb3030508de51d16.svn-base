#include <common.h>
#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/mem.h>

#include "common_def.h"
#include "pmic.h"
#include "cpu_rtc_ss.h"

void tps65910_set_external_crystal(void)
{
    uchar buf[4];
    /*printf("tps65910: enabling external 32 kHz crystal.\n");*/
    if (i2c_probe(PMIC_CTRL_I2C_ADDR))
    {
        printf("tps65910_set_external_crystal() Error: no i2c device\n");
        return;
    }
    if (i2c_read(PMIC_CTRL_I2C_ADDR, PMIC_DEVCTRL_REG, 1, buf, 1))
        return;

    buf[0] &= PMIC_DEVCTRL_RTC_PWDN_POWERED;
    buf[0] &= PMIC_DEVCTRL_CK32K_CTRL_EXTCLK;

    if (i2c_write(PMIC_CTRL_I2C_ADDR, PMIC_DEVCTRL_REG, 1, buf, 1))
        return;
}
    
/****** Helper functions ****************************************/
static u8 rtc_read(u8 reg)
{
	return i2c_reg_read(PMIC_CTRL_I2C_ADDR, reg);
}

static void rtc_write(u8 reg, u8 val)
{
	i2c_reg_write(PMIC_CTRL_I2C_ADDR, reg, val);
}
/****************************************************************/

/* Get the current time from the RTC */
int rtc_get(struct rtc_time *tmp)
{
	u8 sec, min, hour, mday, wday, mon, year;

	sec        = rtc_read(RTC_SECONDS_REG_ADDR);
	min        = rtc_read(RTC_MINUTES_REG_ADDR);
	hour       = rtc_read(RTC_HOURS_REG_ADDR);
	mday       = rtc_read(RTC_DAYS_REG_ADDR);
	mon        = rtc_read(RTC_MONTHS_REG_ADDR);
	year       = rtc_read(RTC_YEARS_REG_ADDR);
	wday       = rtc_read(RTC_WEEKS_REG_ADDR);
	
    tmp->tm_sec   = bcd2bin(sec & 0x7F);
	tmp->tm_min   = bcd2bin(min & 0x7F);
	tmp->tm_hour  = bcd2bin(hour & 0x3F);
	tmp->tm_mday  = bcd2bin(mday & 0x3F);
	tmp->tm_mon   = bcd2bin(mon & 0x1F);
	tmp->tm_year  = bcd2bin(year) + 2000;
	tmp->tm_wday  = bcd2bin((wday - 1) & 0x07);
	tmp->tm_yday  = 0;
    tmp->tm_isdst = rtc_read(RTC_BCK1_REG_ADDR); /* used as: is date set ? */
   
    return 0;
}

/* Set the RTC */
int rtc_set(struct rtc_time *tmp)
{
	u8 ctrl_reg, status_reg;
    printf ("Setting I2C RTC: %02d-%02d-%02d %02d:%02d:%02d\r\n", tmp->tm_year, tmp->tm_mon, tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

    ctrl_reg   = rtc_read(RTC_CTRL_REG_ADDR);
    ctrl_reg &= 0xfe; /* freezes RTC */
    rtc_write(RTC_CTRL_REG_ADDR, ctrl_reg);

	while ((status_reg = rtc_read(RTC_STATUS_REG_ADDR)) & 0x2) /* polling for RTC is frozen */
        ;
        
	rtc_write(RTC_WEEKS_REG_ADDR,   bin2bcd(tmp->tm_wday + 1));
	rtc_write(RTC_YEARS_REG_ADDR,   bin2bcd(tmp->tm_year % 100));
	rtc_write(RTC_MONTHS_REG_ADDR,  bin2bcd(tmp->tm_mon));
	rtc_write(RTC_DAYS_REG_ADDR,    bin2bcd(tmp->tm_mday));
	rtc_write(RTC_HOURS_REG_ADDR,   bin2bcd(tmp->tm_hour));
	rtc_write(RTC_MINUTES_REG_ADDR, bin2bcd(tmp->tm_min));
	rtc_write(RTC_SECONDS_REG_ADDR, bin2bcd(tmp->tm_sec));
	rtc_write(RTC_BCK1_REG_ADDR, 1); /* date already programmed, indicates Battery good status */

    ctrl_reg   = rtc_read(RTC_CTRL_REG_ADDR);
    ctrl_reg ^= 0x01; // reactivate frozen RTC
    rtc_write(RTC_CTRL_REG_ADDR, ctrl_reg);
    
    cpu_rtc_ss_set (tmp);
	return 0;
}

/* Reset the RTC */
void rtc_reset(void)
{
    u8 ctrl_reg, status_reg;
    ctrl_reg   = rtc_read(RTC_CTRL_REG_ADDR);
    ctrl_reg &= 0xfe; /* freezes RTC */
    rtc_write(RTC_CTRL_REG_ADDR, ctrl_reg);

	while ((status_reg = rtc_read(RTC_STATUS_REG_ADDR)) & 0x2) /* polling for RTC is frozen */
        ;

    ctrl_reg   = rtc_read(RTC_CTRL_REG_ADDR);
    ctrl_reg ^= 0x01; // reactivate frozen RTC
    rtc_write(RTC_CTRL_REG_ADDR, ctrl_reg);
    
	rtc_write(RTC_BCK1_REG_ADDR, 0); /* date not programmed yet */
    
    return;
}


