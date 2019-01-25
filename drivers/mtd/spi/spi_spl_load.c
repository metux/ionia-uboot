/*
 * Copyright (C) 2011 OMICRON electronics GmbH
 *
 * based on drivers/mtd/nand/nand_spl_load.c
 *
 * Copyright (C) 2011
 * Heiko Schocher, DENX Software Engineering, hs@denx.de.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
/*#include <net.h>*/
#include <asm/omap_common.h>
#include <spi_flash.h>

DECLARE_GLOBAL_DATA_PTR;

static int spi_boot_image(int img_id)
{
    int res = 0;
    struct spi_flash *flash;
    void (*uboot)(void) __noreturn;
    image_header_t header;
    u32 spi_offset_addr = 0;
    
    /* get offset address of selected u-boot image */
    switch(img_id)
    {
        case 0:
            spi_offset_addr = CONFIG_SYS_SPI_U_BOOT_OFFS;
            break;
        case 1:
            #ifdef CONFIG_SYS_SPI_REDUNDANT_U_BOOT_OFFS 
            spi_offset_addr = CONFIG_SYS_SPI_REDUNDANT_U_BOOT_OFFS;
            #else
            printf("%s - CONFIG_SYS_SPI_REDUNDANT_U_BOOT_OFFS not defined for redundant u-boot image (see include/config/*)!\r\n", __func__);
            hang();
            #endif
            break;
        default:
            /* abort operation! (only possbile in development) */
            printf("%s - Check img_id!\r\n", __func__);
            hang();
            break;
    }

    /* initialize SPI connection */
    printf("SPI Flash probe ... \r\n");
    flash = spi_flash_probe(
                CONFIG_SPL_SPI_BUS, 
                CONFIG_SPL_SPI_CS,
                CONFIG_SF_DEFAULT_SPEED, 
                SPI_MODE_3);
    if (!flash) 
    {
        puts("failed.\r\n");
        hang();
    }    
    
    /* read flash image */
    printf("SPI Flash read to RAM: 0x%08X..0x%08X -> 0x%p\r\n", spi_offset_addr, spi_offset_addr + CONFIG_SYS_SPI_U_BOOT_SIZE, (void *)CONFIG_SYS_TEXT_BASE - sizeof(struct image_header));
    spi_flash_read(
                flash, 
                spi_offset_addr,
                CONFIG_SYS_SPI_U_BOOT_SIZE,
                (void *) (CONFIG_SYS_TEXT_BASE - sizeof(struct image_header))
               );

    spl_parse_image_header((struct image_header *)(CONFIG_SYS_TEXT_BASE - sizeof(struct image_header)));
    
    if (ntohl(((struct image_header *)(CONFIG_SYS_TEXT_BASE - sizeof(struct image_header)))->ih_magic) == IH_MAGIC)
    { 
        /* u-boot.img loaded (Check CRC32) */
        struct image_header * image_header_p = (struct image_header *) spl_image.load_addr;
        
        /* Copy header so we can blank CRC field for re-calculation */
        memmove (&header, (char *)spl_image.load_addr, sizeof(struct image_header));
        image_set_hcrc (&header, 0);
        
        /* calculate CRC32 checksums */
        uint32_t crc32_header_calculated = crc32(0, (unsigned char *)&header, sizeof(struct image_header));
        uint32_t crc32_data_calculated   = crc32(0, (void *)(spl_image.load_addr + sizeof(struct image_header)), ntohl(image_header_p->ih_size));
        
        if(crc32_header_calculated != ntohl(image_header_p->ih_hcrc))
        {
            printf("Header CRC32             : NOK\n");
            res = -1;
        }
        else
        {
            printf("Header CRC32             : OK\n");
        }
        
        if(crc32_data_calculated != ntohl(image_header_p->ih_dcrc))
        {
            printf("Data CRC32               : NOK\n");
            res = -1;
        }
        else
        {
            printf("Data CRC32               : OK\n");
        }
    }
    else
        res = -1;
    
    /*
     * Jump to U-Boot image if crc is ok
     */
    if(0 == res)
    {
        uboot = (void *) CONFIG_SYS_TEXT_BASE;
        (*uboot)();
    }
    return res;
}

/*
 * The main entry for SPI booting. It's necessary that SDRAM is already
 * configured and available since this code loads the main U-Boot image
 * from SPI into SDRAM and starts it from there.
 */
int spi_boot(void)
{
    int res = 0;
    
    /* try first u-boot image */
    printf("Try SPI Image #1:\n");
    res = spi_boot_image(0);
    
    #ifdef CONFIG_SYS_SPI_REDUNDANT_U_BOOT_OFFS 
    /* on error try second u-boot image */
    if(-1 == res)
    {
        printf("\nTry SPI Image #2:\n");
        res = spi_boot_image(1);
    }
    #endif
    
    return res;
}
