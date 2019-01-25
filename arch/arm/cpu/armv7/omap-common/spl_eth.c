/*
 * (C) Copyright 2000-2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2012
 * Ilya Yanok <ilya.yanok@gmail.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc.
 */
#include <common.h>
#include <net.h>
#include <asm/omap_common.h>

DECLARE_GLOBAL_DATA_PTR;

void spl_eth_load_image(void)
{
    int rv;

    env_init();
    env_relocate();
    setenv("autoload", "yes");
    load_addr = CONFIG_SYS_TEXT_BASE - sizeof(struct image_header);
    
    rv = eth_initialize(gd->bd);
    if (rv == 0) {
        printf("No Ethernet devices found\n");
        hang();
    }
    
    rv = NetLoop(BOOTP);
    if (rv < 0) {
        printf("Problem booting with BOOTP\n");
        hang();
    }
    
    spl_parse_image_header((struct image_header *)load_addr);
    
    if (ntohl(((struct image_header *)load_addr)->ih_magic) == IH_MAGIC)
    { 
        /* u-boot.img loaded */
        /* CRC32 check */
        struct image_header *image_header_p = (struct image_header *) load_addr;
        
        /* Copy header so we can blank CRC field for re-calculation */
        image_header_t header;
        memmove (&header, (char *)load_addr, sizeof(struct image_header));
        image_set_hcrc (&header, 0);

        /* calculate crc32 checksums */
        uint32_t crc32_header_calculated = crc32(0, (unsigned char *)&header, sizeof(struct image_header));
        uint32_t crc32_data_calculated   = crc32(0, (void *)(load_addr + sizeof(struct image_header)), ntohl(image_header_p->ih_size));
        
        if(crc32_header_calculated != ntohl(image_header_p->ih_hcrc))
        {
            printf ("header crc32: NOK\n");
            hang();
        }
        else
        {
            printf ("header crc32: OK\n");
        }
        
        if(crc32_data_calculated != ntohl(image_header_p->ih_dcrc))
        {
            printf ("data crc32: NOK\n");
            hang();
        }
        else
        {
            printf ("data crc32: OK\n");
        }
    }
    else
    {
        printf("Unexpected firmware header magic number found, probably wrong image loaded. (should be u-boot.img)\n");
        hang();
    }
}
