/*
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef __CONFIG_AM335X_EVM_H
    #define __CONFIG_AM335X_EVM_H

    /* #define DEBUG */                     /* Be careful may, prevent booting in u-boot-spl */
    #define CONFIG_AM335X
    #define CONFIG_TI81XX
    #define CONFIG_SYS_NO_FLASH
    #ifndef CONFIG_SPI_BOOT
        #define CONFIG_NAND_ENV
    #endif
    
    /* don't move headers to top, because some defines above are necessary... */
    #include <asm/arch/cpu.h>               /* get chip and board defs */
    #include <asm/arch/hardware.h>
    #include <config_cmd_default.h>

    #define CONFIG_CMD_DATE                 /* support for RTC, date/time...*/

    #define CONFIG_CMD_ASKENV

    #define CONFIG_ENV_SIZE                 0x2000
    
    #ifdef CONFIG_UBI
        #define CONFIG_SYS_MALLOC_LEN       (2*CONFIG_ENV_SIZE + (512 * 1024))
    #else
        #define CONFIG_SYS_MALLOC_LEN       (2*CONFIG_ENV_SIZE + (128 * 1024))
    #endif
    
    #define CONFIG_ENV_OVERWRITE
    #define CONFIG_SYS_LONGHELP
    #define CONFIG_SYS_PROMPT               "U-Boot# "
    
    /* Use HUSH parser to allow command parsing */
    #define CONFIG_SYS_HUSH_PARSER
    #define CONFIG_SYS_PROMPT_HUSH_PS2      "> "
    #define CONFIG_CMDLINE_TAG              /* enable passing of ATAGs */
    #define CONFIG_SETUP_MEMORY_TAGS
    #define CONFIG_INITRD_TAG               /* Required for ramdisk support */

    /*#define CONFIG_MMC */
    #define CONFIG_NAND
    #define CONFIG_SPI

    #define CONFIG_EXTRA_ENV_SETTINGS \
        "autoload=no\0" \
        "bootargs_defaults=setenv bootargs console=${console} ${optargs} bootp_dev_delay=200\0" \
        "bootfile=uImage\0" \
        "console=ttyO0,115200n8\0" \
        "ip_method=none\0" \
        "serverip=192.168.5.99\0" \
        "kloadaddr=0x80007fc0\0" \
        "loadaddr=0x82000000\0" \
        "nand_args=run bootargs_defaults;setenv bootargs ${bootargs} root=${nand_root} noinitrd rootfstype=${nand_root_fs_type} ip=${ip_method}\0" \
        "nand_boot=nand bad;echo Booting from nand ...;run nand_args;nandecc hw 2;nand read.i ${kloadaddr} ${nand_src_addr} ${nand_img_siz};bootm ${kloadaddr}\0" \
        "nand_img_siz=0x380000\0" \
        "nand_root=ubi0:rootfs rw ubi.mtd=15,4096\0" \
        "nand_root_fs_type=ubifs rootwait=1\0" \
        "nand_src_addr=0x200000\0" \
        "net_args=run bootargs_defaults;setenv bootargs ${bootargs} root=/dev/nfs nfsroot=${serverip}:${rootpath},${nfsopts} rw ip=${ip_method}\0" \
        "net_boot=echo Booting from network (static IP)...;setenv ip_method none;setenv autoload no;tftp ${kloadaddr} ${bootfile};run net_args;bootm ${kloadaddr}\0" \
        "net_boot_dhcp=echo Booting from network (DHCP)...;setenv ip_method dhcp;setenv autoload no;dhcp;tftp ${kloadaddr} ${bootfile};run net_args;bootm ${kloadaddr}\0" \
        "nfsopts=nolock\0" \
        "optargs=\0" \
        "rootpath=/export/rootfs\0" \
        "spi_args=run bootargs_defaults;setenv bootargs ${bootargs} root=${nand_root} rootfstype=${nand_root_fs_type} ip=${ip_method}\0" \
        "spi_boot=echo Booting default uImage from spi ...;run spi_args;sf probe ${spi_bus_no}:0;sf read ${kloadaddr} ${spi_src_addr} ${spi_img_siz};bootm ${kloadaddr}\0" \
        "spi_boot2=echo Booting recovery uImage from spi ...;run spi_args;sf probe ${spi_bus_no}:0;sf read ${kloadaddr} ${spi_src_addr2} ${spi_img_siz};bootm ${kloadaddr}\0" \
        "spi_bus_no=0\0" \
        "spi_img_siz=0x380000\0" \
        "spi_nand_boot=echo Booting kernel from SPI flash, rootfs from NAND flash...;run nand_args;sf probe ${spi_bus_no}:0;sf read ${kloadaddr} ${spi_src_addr} ${spi_img_siz};bootm ${kloadaddr}\0" \
        "spi_src_addr=0x80000\0" \
        "spi_src_addr2=0x480000\0" \
        "uboot_load=setenv autoload no;dhcp;mw.b 0x82000000 0xffffffff 0x60000;tftp 0x82000000 MLO.spi;tftp 0x82020000 u-boot.bin\0" \
        "uboot_flash=sf probe 0;sf erase 0x0 0x60000;sf write 0x82000000 0x0 0x60000\0" \


    #ifndef CONFIG_RESTORE_FLASH
        /* set to negative value for no autoboot */
        #ifdef JAQUET
            #define CONFIG_BOOTDELAY                        12
        #else
            #define CONFIG_BOOTDELAY                        3
        #endif

        #define CONFIG_BOOTCOMMAND      "run spi_boot;run spi_boot2;echo no valid uImage in SPI flash found. Booting from Ethernet ...;run net_boot_dhcp"

        #ifdef JAQUET
            /* ADDED BY Marcos Barandun, JAQUET TG to avoid accidental system hanging */
            #define CONFIG_AUTOBOOT_KEYED
            #define CONFIG_AUTOBOOT_STOP_STR            "JmaZd=?VX"
            #define CONFIG_BOOT_RETRY_TIME              5
            #define CONFIG_RESET_TO_RETRY               5
            #define CONFIG_AUTOBOOT_PROMPT \
                "autoboot in %d seconds\n",bootdelay
            /* ---------------------------------------------------------------------- */
        #endif
    #else
        #ifdef JAQUET
            #define CONFIG_BOOTDELAY                        12
        #else
            #define CONFIG_BOOTDELAY                        3
        #endif
        #define CONFIG_BOOTCOMMAND                      "run net_boot_dhcp" 
    #endif

    #define CONFIG_MISC_INIT_R
    #define CONFIG_SYS_AUTOLOAD                         "yes"
    #define CONFIG_CMD_CACHE
    #define CONFIG_CMD_ECHO
    
    #define CONFIG_SYS_MAXARGS                          32                  /* max number of command args */
    #define CONFIG_SYS_CBSIZE                           512                 /* Console I/O Buffer Size */
    
    /* Print Buffer Size */
    #define CONFIG_SYS_PBSIZE                           (CONFIG_SYS_CBSIZE \
                                                        + sizeof(CONFIG_SYS_PROMPT) + 16)
    #define CONFIG_SYS_BARGSIZE                         CONFIG_SYS_CBSIZE   /* Boot Argument Buffer Size */
    
    /*
     * memtest works on 8 MB in DRAM after skipping 64MB from
     * start addr of ram disk
     */
    #define CONFIG_SYS_MEMTEST_START                    (PHYS_DRAM_1 + (64 * 1024 * 1024))
    #define CONFIG_SYS_MEMTEST_END                      (CONFIG_SYS_MEMTEST_START \
                                                        + (8 * 1024 * 1024))

    #define CONFIG_SYS_LOAD_ADDR                        0x81000000          /* Default load address */

     /* Physical Memory Map */
    #define CONFIG_NR_DRAM_BANKS                        1                   /* 1 bank of DRAM */
    #define PHYS_DRAM_1                                 0x80000000          /* DRAM Bank #1 */
    #define PHYS_DRAM_1_SIZE                            0x10000000          /* 256 MiB */
    #define CONFIG_MAX_RAM_BANK_SIZE                    (1024 << 20)        /* 1GB */

    #define CONFIG_SYS_SDRAM_BASE       PHYS_DRAM_1
    #define CONFIG_SYS_INIT_RAM_ADDR    SRAM0_START
    #define CONFIG_SYS_INIT_RAM_SIZE    SRAM0_SIZE
    #define CONFIG_SYS_INIT_SP_ADDR     (CONFIG_SYS_INIT_RAM_ADDR + \
                                        CONFIG_SYS_INIT_RAM_SIZE - \
                                        GENERATED_GBL_DATA_SIZE)

    /* Defines for SPL (Secondary P Loader)*/
    #define CONFIG_SPL
    #define CONFIG_SPL_BOARD_INIT
    #define CONFIG_SPL_TEXT_BASE                        0x402F0400
    #define CONFIG_SPL_MAX_SIZE                         (101 * 1024)
    #define CONFIG_SPL_STACK                            LOW_LEVEL_SRAM_STACK

    #define CONFIG_SPL_BSS_START_ADDR                   0x80000000
    #define CONFIG_SPL_BSS_MAX_SIZE                     0x80000             /* 512 KB */

    #ifndef CONFIG_SPI_BOOT
        #define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR 0x300               /* address 0x60000 */
        #define CONFIG_SYS_U_BOOT_MAX_SIZE_SECTORS      0x200               /* 256 KB */
        #define CONFIG_SYS_MMC_SD_FAT_BOOT_PARTITION    1
        #define CONFIG_SPL_FAT_LOAD_PAYLOAD_NAME        "u-boot.img"
        #define CONFIG_SPL_FAT_SUPPORT
    #endif

    #define CONFIG_SPL_LIBCOMMON_SUPPORT
    #define CONFIG_SPL_LIBDISK_SUPPORT
    #define CONFIG_SPL_I2C_SUPPORT
    #define CONFIG_SPL_LIBGENERIC_SUPPORT
    #define CONFIG_SPL_SERIAL_SUPPORT
    #define CONFIG_SPL_YMODEM_SUPPORT
    #define CONFIG_SPL_POWER_SUPPORT
    #define CONFIG_SPL_NET_SUPPORT
    #define CONFIG_SPL_NET_VCI_STRING                   "AM335x U-Boot SPL"
    #define CONFIG_SPL_ETH_SUPPORT
    #define CONFIG_SPL_LDSCRIPT                         "$(CPUDIR)/omap-common/u-boot-spl.lds"

    /* NAND boot config */
    #ifndef CONFIG_SPI_BOOT
        /*These values are not correct with used NAND flash type check*/
        #define CONFIG_SPL_NAND_SIMPLE
        #define CONFIG_SPL_NAND_SUPPORT
        #define CONFIG_SYS_NAND_5_ADDR_CYCLE
        #define CONFIG_SYS_NAND_PAGE_COUNT                  (CONFIG_SYS_NAND_BLOCK_SIZE / \
                                                            CONFIG_SYS_NAND_PAGE_SIZE)
        #define CONFIG_SYS_NAND_PAGE_SIZE                   4096
        #define CONFIG_SYS_NAND_OOBSIZE                     128
        #define CONFIG_SYS_NAND_BLOCK_SIZE                  (128*4096)
        #define CONFIG_SYS_NAND_BAD_BLOCK_POS               NAND_LARGE_BADBLOCK_POS
        #define CONFIG_SYS_NAND_ECCPOS      { 2, 3, 4, 5, 6, 7, 8, 9, \
                             10, 11, 12, 13, 14, 15, 16, 17, \
                             18, 19, 20, 21, 22, 23, 24, 25, \
                             26, 27, 28, 29, 30, 31, 32, 33, \
                             34, 35, 36, 37, 38, 39, 40, 41, \
                             42, 43, 44, 45, 46, 47, 48, 49, \
                             50, 51, 52, 53, 54, 55, 56, 57, \
                             58, 59, 60, 61, 62, 63, 64, 65, \
                             66, 67, 68, 69, 70, 71, 72, 73, \
                             74, 75, 76, 77, 78, 79, 80, 81, \
                             82, 83, 84, 85, 86, 87, 88, 89, \
                             90, 91, 92, 93, 94, 95, 96, 97, \
                             98, 99,100,101,102,103,104,105, \
                            106,107,108,109,110,111,112,113  }

        #define CONFIG_SYS_NAND_ECCSIZE                     512
        #define CONFIG_SYS_NAND_ECCBYTES                    14

        #define CONFIG_SYS_NAND_ECCSTEPS                    8
        #define CONFIG_SYS_NAND_ECCTOTAL                    (CONFIG_SYS_NAND_ECCBYTES * \
                                                            CONFIG_SYS_NAND_ECCSTEPS)

        #define CONFIG_SYS_NAND_U_BOOT_START                CONFIG_SYS_TEXT_BASE

        #define CONFIG_SYS_NAND_U_BOOT_OFFS                 0x80000
    #endif

    /* SPI boot config */
    #define CONFIG_SPL_SPI_SUPPORT
    #define CONFIG_SPL_SPI_FLASH_SUPPORT
    #define CONFIG_SPL_SPI_LOAD
    #define CONFIG_SPL_SPI_BUS                          0
    #define CONFIG_SPL_SPI_CS                           0
    #define CONFIG_SYS_SPI_U_BOOT_OFFS                  0x20000         /* first U-Boot */
    #define CONFIG_SYS_SPI_REDUNDANT_U_BOOT_OFFS        0x420000        /* second U-Boot used if first U-Boot CRC32 is wrong */
    #define CONFIG_SYS_SPI_U_BOOT_SIZE                  0x40000

    /*
     * 1MB into the SDRAM to allow for SPL's bss at the beginning of SDRAM.
     * 64 bytes before this address should be set aside for u-boot.img's
     * header. That is 0x800FFFC0--0x80100000 should not be used for any
     * other needs.
     */
    #define CONFIG_SYS_TEXT_BASE                        0x80100000
    #define CONFIG_SYS_SPL_MALLOC_START                 0x80208000
    #define CONFIG_SYS_SPL_MALLOC_SIZE                  0x100000

    /* Since SPL did all of this for us, we don't need to do it twice. */
    #ifndef CONFIG_SPL_BUILD
        #define CONFIG_SKIP_LOWLEVEL_INIT
    #endif

    /**
     * Clock related defines
     */
    #define V_OSCK                                      24000000            /* Clock output from T2 */
    #define V_SCLK                                      (V_OSCK)
    #define CONFIG_SYS_TIMERBASE                        0x48040000          /* Use Timer2 */
    #define CONFIG_SYS_PTV                              2                   /* Divisor: 2^(PTV+1) => 8 */
    #define CONFIG_SYS_HZ                               1000

    /* NS16550 Configuration */
    #define CONFIG_SYS_NS16550
    #define CONFIG_SYS_NS16550_SERIAL
    #define CONFIG_SYS_NS16550_REG_SIZE                 (-4)
    #define CONFIG_SYS_NS16550_CLK                      (48000000)
    #define CONFIG_SYS_NS16550_COM1                     0x44e09000          /* Base EVM has UART0 */
    #define CONFIG_SYS_NS16550_COM4                     0x481A6000          /* UART3 on IA BOard */

    #define CONFIG_BAUDRATE                             115200
    #define CONFIG_SYS_BAUDRATE_TABLE   { 110, 300, 600, 1200, 2400, \
    4800, 9600, 14400, 19200, 28800, 38400, 56000, 57600, 115200 }

    /*
     * select serial console configuration
     */
    #define CONFIG_SERIAL1                              1
    #define CONFIG_CONS_INDEX                           1
    #define CONFIG_SYS_CONSOLE_INFO_QUIET

    #if defined(CONFIG_NO_ETH)
        # undef CONFIG_CMD_NET
    #else
        # define CONFIG_CMD_DHCP
        # define CONFIG_CMD_PING
    #endif

    #if defined(CONFIG_CMD_NET)
        # define CONFIG_DRIVER_TI_CPSW
        # define CONFIG_MII
        # define CONFIG_BOOTP_DEFAULT
        # define CONFIG_BOOTP_DNS
        # define CONFIG_BOOTP_DNS2
        # define CONFIG_BOOTP_SEND_HOSTNAME
        # define CONFIG_BOOTP_GATEWAY
        # define CONFIG_BOOTP_SUBNETMASK
        # define CONFIG_NET_RETRY_COUNT                 10
        # define CONFIG_NET_MULTI
        # define CONFIG_PHY_GIGE
    #endif

    #if defined(CONFIG_SYS_NO_FLASH)
        # define CONFIG_ENV_IS_NOWHERE
    #endif

    /* NAND support */
    #ifdef CONFIG_NAND
        #ifdef CONFIG_UBI
            #define CONFIG_CMD_UBI      /* support for UBI command */
            #define CONFIG_CMD_UBIFS    /* support for UBI file system command */
            #define CONFIG_RBTREE
            #define CONFIG_MTD_DEVICE
            #define CONFIG_MTD_PARTITIONS
            #define CONFIG_CMD_MTDPARTS
            #define CONFIG_LZO
        #endif
        
        #define CONFIG_MTD_DEBUG
        #define CONFIG_MTD_DEBUG_VERBOSE 1
        #define CONFIG_CMD_NAND_LOCK_UNLOCK
        #define CONFIG_SYS_NAND_ONFI_DETECTION
        #define CONFIG_CMD_NAND
        #define CONFIG_NAND_TI81XX
        #define GPMC_NAND_ECC_LP_x16_LAYOUT             1
        #define NAND_BASE                               (0x08000000)
        #define CONFIG_SYS_NAND_ADDR                    NAND_BASE       /* physical address to access nand */
        #define CONFIG_SYS_NAND_BASE                    NAND_BASE       /* physical address to access nand at CS0 */
        #define CONFIG_SYS_MAX_NAND_DEVICE              1               /* Max number of NAND devices */
    #endif

    /* ENV in NAND */
    #if defined(CONFIG_NAND_ENV)
        #undef CONFIG_ENV_IS_NOWHERE
        #define CONFIG_ENV_IS_IN_NAND
        #define CONFIG_SYS_MAX_FLASH_SECT               520             /* max no of sectors in a chip */
        #define CONFIG_SYS_MAX_FLASH_BANKS              2               /* max no of flash banks */
        #define CONFIG_SYS_MONITOR_LEN                  (256 << 10)     /* Reserve 2 sectors */
        #define CONFIG_SYS_FLASH_BASE                   PISMO1_NAND_BASE
        #define CONFIG_SYS_MONITOR_BASE                 CONFIG_SYS_FLASH_BASE
        #define MNAND_ENV_OFFSET                        0x100000        /* environment starts here */
        #define CONFIG_SYS_ENV_SECT_SIZE                (128 << 10)     /* 128 KiB */
        #define CONFIG_ENV_OFFSET                       MNAND_ENV_OFFSET
        #define CONFIG_ENV_OFFSET_REDUND                (MNAND_ENV_OFFSET+CONFIG_SYS_ENV_SECT_SIZE)
        #define CONFIG_SYS_REDUNDAND_ENVIRONMENT
        #define CONFIG_ENV_ADDR                         MNAND_ENV_OFFSET
    #endif /* NAND support */

    /*
     * NOR Size = 16 MB
     * No.Of Sectors/Blocks = 128
     * Sector Size = 128 KB
     * Word lenght = 16 bits
     */
    #if defined(CONFIG_NOR)
        # undef CONFIG_ENV_IS_NOWHERE
        # undef CONFIG_SYS_MALLOC_LEN
        # define CONFIG_SYS_FLASH_USE_BUFFER_WRITE      1
        # define CONFIG_SYS_MALLOC_LEN                  (0x100000)
        # define CONFIG_SYS_FLASH_CFI
        # define CONFIG_FLASH_CFI_DRIVER
        # define CONFIG_FLASH_CFI_MTD
        # define CONFIG_SYS_MAX_FLASH_SECT              128
        # define CONFIG_SYS_MAX_FLASH_BANKS             1
        # define CONFIG_SYS_FLASH_BASE                  (0x08000000)
        # define CONFIG_SYS_MONITOR_BASE                CONFIG_SYS_FLASH_BASE
        # define CONFIG_ENV_IS_IN_FLASH                 1
        # define NOR_SECT_SIZE                          (128 * 1024)
        # define CONFIG_SYS_ENV_SECT_SIZE               (NOR_SECT_SIZE)
        # define CONFIG_ENV_SECT_SIZE                   (NOR_SECT_SIZE)
        # define CONFIG_ENV_OFFSET                      (8 * NOR_SECT_SIZE)                         /* After 1 MB */
        # define CONFIG_ENV_OFFSET_REDUND               (8 * NOR_SECT_SIZE+CONFIG_ENV_SECT_SIZE)    /* After 1 MB */
        # define CONFIG_SYS_REDUNDAND_ENVIRONMENT
        # define CONFIG_ENV_ADDR                        (CONFIG_SYS_FLASH_BASE + \
                                                        CONFIG_ENV_OFFSET)
        # define CONFIG_MTD_DEVICE
    #endif  /* NOR support */

    /* SPI support */
    #ifdef CONFIG_SPI
        #define BOARD_LATE_INIT
        #define CONFIG_OMAP3_SPI
        #define CONFIG_MTD_DEVICE
        #define CONFIG_SPI_FLASH
        #define CONFIG_SPI_FLASH_STMICRO
        #define CONFIG_CMD_SF
        #define CONFIG_SF_DEFAULT_SPEED                 (15000000)  /* default:(75000000)*/ /*This value does not have influence on SPI Flash writes and reads, only for detection*/
    #endif

    /* ENV in SPI */
    #if defined(CONFIG_SPI_BOOT)
        # undef CONFIG_ENV_IS_NOWHERE
        #ifndef CONFIG_RESTORE_FLASH
            #define CONFIG_ENV_IS_IN_SPI_FLASH
        #endif
        # define CONFIG_ENV_SPI_MAX_HZ                  CONFIG_SF_DEFAULT_SPEED
        # define CONFIG_ENV_OFFSET                      (0x60000)
        # define CONFIG_ENV_OFFSET_REDUND               (0x70000)
        # define CONFIG_ENV_OFFSET_REDUND2              (0x460000)
        # define CONFIG_ENV_OFFSET_REDUND3              (0x470000)
        # define CONFIG_SYS_REDUNDAND_ENVIRONMENT
        # define CONFIG_SYS_ENVIRONMENT_VERSION         0x1
        # define CONFIG_ENV_SECT_SIZE                   (64 << 10)                                  /* 64 KB sectors = 0x10000 */
    #endif /* SPI support */

    /* I2C */
    #define CONFIG_I2C
    #define CONFIG_CMD_I2C
    #define CONFIG_HARD_I2C
    #define CONFIG_SYS_I2C_SPEED                        100000
    #define CONFIG_SYS_I2C_SLAVE                        1
    #define CONFIG_I2C_MULTI_BUS
    #define CONFIG_DRIVER_TI81XX_I2C

    /* HSMMC support */
    #ifdef CONFIG_MMC
        #define CONFIG_GENERIC_MMC
        #define CONFIG_OMAP_HSMMC
        #define CONFIG_CMD_MMC
        #define CONFIG_DOS_PARTITION
        #define CONFIG_CMD_FAT
        #define CONFIG_CMD_EXT2
    #endif

    /* Unsupported features */
    #undef CONFIG_USE_IRQ

#endif  /* ! __CONFIG_AM335X_EVM_H */
