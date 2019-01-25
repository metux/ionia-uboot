#include <common.h>
#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/mem.h>

#include "common_def.h"
#include "cpu_rtc_ss.h"

#ifdef CONFIG_SPL_BUILD
void rtc32k_enable(void)
{
	/* Unlock the rtc's registers */
	writel(0x83e70b13, (AM335X_RTC_BASE + RTC_KICK0_REG));
	writel(0x95a4f1e0, (AM335X_RTC_BASE + RTC_KICK1_REG));

	/* Enable the RTC 32K OSC */
	writel(0x48, (AM335X_RTC_BASE + RTC_OSC_REG));
}
#endif

/****** Helper functions ****************************************/
static u8 cpu_rtc_ss_read(u8 * reg)
{
    u8 cpu_rts_ss_val_read = *reg;
    /*printf ("cpu_rtc_ss_read (0x%p) = 0x%02x\r\n", reg, cpu_rts_ss_val_read );*/
	return cpu_rts_ss_val_read;
}

static void cpu_rtc_ss_write(u8 *reg, u8 val)
{
	/*printf ("cpu_rtc_ss_write(0x%p, 0x%02x)\r\n", reg, val);*/
    *reg = val;
}
/****************************************************************/

/* Get the current time from the RTC */
int cpu_rtc_ss_get (struct rtc_time *tmp)
{
	int ret = 0;
	u8 sec, min, hour, mday, wday, mon, year;

	sec        = cpu_rtc_ss_read((u8*)CPU_RTC_SS_SECONDS_REG_ADDR);
	min        = cpu_rtc_ss_read((u8*)CPU_RTC_SS_MINUTES_REG_ADDR);
	hour       = cpu_rtc_ss_read((u8*)CPU_RTC_SS_HOURS_REG_ADDR);
	mday       = cpu_rtc_ss_read((u8*)CPU_RTC_SS_DAYS_REG_ADDR);
	mon        = cpu_rtc_ss_read((u8*)CPU_RTC_SS_MONTHS_REG_ADDR);
	year       = cpu_rtc_ss_read((u8*)CPU_RTC_SS_YEARS_REG_ADDR);
	wday       = cpu_rtc_ss_read((u8*)CPU_RTC_SS_WEEKS_REG_ADDR);
	
    tmp->tm_sec   = bcd2bin(sec & 0x7F);
	tmp->tm_min   = bcd2bin(min & 0x7F);
	tmp->tm_hour  = bcd2bin(hour & 0x3F);
	tmp->tm_mday  = bcd2bin(mday & 0x3F);
	tmp->tm_mon   = bcd2bin(mon & 0x1F);
	tmp->tm_year  = bcd2bin(year) + 2000;
	tmp->tm_wday  = bcd2bin((wday - 1) & 0x07);
	tmp->tm_yday  = 0;
	tmp->tm_isdst = 0;
	
    return ret;
}

/* Set the RTC */
int cpu_rtc_ss_set(struct rtc_time *tmp)
{
	u8 ctrl_reg, status_reg;
    printf ("Setting CPU RTC: %02d-%02d-%02d %02d:%02d:%02d\r\n", tmp->tm_year, tmp->tm_mon, tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
    ctrl_reg  = cpu_rtc_ss_read((u8*)CPU_RTC_SS_CTRL_REG_ADDR);
    ctrl_reg &= 0xfe; /* freezes RTC */
    cpu_rtc_ss_write((u8*)CPU_RTC_SS_CTRL_REG_ADDR, ctrl_reg);

	while ((status_reg = cpu_rtc_ss_read((u8*)CPU_RTC_SS_STATUS_REG_ADDR)) & 0x1) /* polling for RTC is no longer busy */
        ;

	cpu_rtc_ss_write((u8*)CPU_RTC_SS_WEEKS_REG_ADDR,   bin2bcd(tmp->tm_wday + 1));
	cpu_rtc_ss_write((u8*)CPU_RTC_SS_YEARS_REG_ADDR,   bin2bcd(tmp->tm_year % 100));
	cpu_rtc_ss_write((u8*)CPU_RTC_SS_MONTHS_REG_ADDR,  bin2bcd(tmp->tm_mon));
	cpu_rtc_ss_write((u8*)CPU_RTC_SS_DAYS_REG_ADDR,    bin2bcd(tmp->tm_mday));
	cpu_rtc_ss_write((u8*)CPU_RTC_SS_HOURS_REG_ADDR,   bin2bcd(tmp->tm_hour));
	cpu_rtc_ss_write((u8*)CPU_RTC_SS_MINUTES_REG_ADDR, bin2bcd(tmp->tm_min));
	cpu_rtc_ss_write((u8*)CPU_RTC_SS_SECONDS_REG_ADDR, bin2bcd(tmp->tm_sec));

    ctrl_reg  = cpu_rtc_ss_read((u8*)CPU_RTC_SS_CTRL_REG_ADDR);
    ctrl_reg ^= 0x01; // reactivate frozen RTC
    cpu_rtc_ss_write((u8*)CPU_RTC_SS_CTRL_REG_ADDR, ctrl_reg);

	return 0;
}

/* Reset the RTC */
void cpu_rtc_ss_reset(void)
{
    u8 ctrl_reg, status_reg;
    ctrl_reg   = cpu_rtc_ss_read((u8*)CPU_RTC_SS_CTRL_REG_ADDR);
    ctrl_reg &= 0xfe; /* freezes RTC */
    cpu_rtc_ss_write((u8*)CPU_RTC_SS_CTRL_REG_ADDR, ctrl_reg);

	while ((status_reg = cpu_rtc_ss_read((u8*)CPU_RTC_SS_STATUS_REG_ADDR)) & 0x1) /* polling for RTC is no longer busy */
        ;

    ctrl_reg   = cpu_rtc_ss_read((u8*)CPU_RTC_SS_CTRL_REG_ADDR);
    ctrl_reg ^= 0x01; // reactivate frozen RTC
    cpu_rtc_ss_write((u8*)CPU_RTC_SS_CTRL_REG_ADDR, ctrl_reg);
    
    return;
}
