/*
 * (C) Copyright 2000-2010
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2001 Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Andreas Heppel <aheppel@sysgo.de>
 *
 * (C) Copyright 2008 Atmel Corporation
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#include <common.h>
#include <environment.h>
#include <malloc.h>
#include <spi_flash.h>
#include <search.h>
#include <errno.h>

#ifndef CONFIG_ENV_SPI_BUS
# define CONFIG_ENV_SPI_BUS 0
#endif

#ifndef CONFIG_ENV_SPI_CS
# define CONFIG_ENV_SPI_CS 0
#endif

#ifndef CONFIG_ENV_SPI_MAX_HZ
# define CONFIG_ENV_SPI_MAX_HZ 1000000
#endif

#ifndef CONFIG_ENV_SPI_MODE
# define CONFIG_ENV_SPI_MODE SPI_MODE_3
#endif

#ifdef CONFIG_ENV_OFFSET_REDUND
static ulong env_offset = CONFIG_ENV_OFFSET;
static ulong env_new_offset = CONFIG_ENV_OFFSET_REDUND;

#define ACTIVE_FLAG   1
#define OBSOLETE_FLAG 0
#endif /* CONFIG_ENV_OFFSET_REDUND */

DECLARE_GLOBAL_DATA_PTR;

/* references to names in env_common.c */
extern uchar default_environment[];

char * env_name_spec = "SPI Flash";

static struct spi_flash *env_flash = NULL;

uchar env_get_char_spec(int index)
{
    return *((uchar *)(gd->env_addr + index));
}

int saveenv(void)
{
    env_t   env_new;
    ssize_t len = 0;
    char   *res = NULL;
    u32     saved_size = 0;
    u32     saved_offset = 0;
    char    *saved_buffer = NULL;
    u32     saved_buffer_startData;
    u32     saved_buffer_endData;
    u32     sector = 1;
    int     ret = 0;
    char    flag = OBSOLETE_FLAG;

    if (!env_flash)
    {
        env_flash = spi_flash_probe(CONFIG_ENV_SPI_BUS,
            CONFIG_ENV_SPI_CS,
            CONFIG_ENV_SPI_MAX_HZ, CONFIG_ENV_SPI_MODE);
            
        if (!env_flash) 
        {
            set_default_env("!spi_flash_probe() failed\n");
            return 1;
        }
    }

    res = (char *)&env_new.data;
    len = hexport_r(&env_htab, '\0', &res, ENV_SIZE);
    if (len < 0) 
    {
        error("Cannot export environment: errno = %d", errno);
        return 1;
    }
    env_new.crc   = crc32(0, env_new.data, ENV_SIZE);
#ifdef CONFIG_ENV_OFFSET_REDUND
    env_new.flags = ACTIVE_FLAG;
#endif
#ifdef CONFIG_SYS_ENVIRONMENT_VERSION
    env_new.revision = CONFIG_SYS_ENVIRONMENT_VERSION;
    env_new.size = ENV_SIZE;
#endif

    if (gd->env_valid == 1) 
    {
        env_new_offset = CONFIG_ENV_OFFSET_REDUND;
        env_offset = CONFIG_ENV_OFFSET;
    }
    else 
    {
        env_new_offset = CONFIG_ENV_OFFSET;
        env_offset = CONFIG_ENV_OFFSET_REDUND;
    }
    
    /* load other data stored in erase size, and write it back after erase */
    /* Is the sector larger than the env (i.e. embedded) */
    if (CONFIG_ENV_SECT_SIZE > CONFIG_ENV_SIZE) 
    {
        saved_size = CONFIG_ENV_SECT_SIZE - CONFIG_ENV_SIZE;
        saved_offset = env_new_offset + CONFIG_ENV_SIZE;
        saved_buffer = malloc(saved_size);
        if (!saved_buffer) 
        {
            ret = 1;
            puts ("malloc () failed\n");
            goto done;
        }
        printf("Reading from:        0x%08x..0x%08x ... ", (unsigned int) saved_offset, (unsigned int) (saved_offset + saved_size-1) );
        ret = spi_flash_read(env_flash, saved_offset,
                    saved_size, saved_buffer);
        if (ret)
        {
            puts ("failed\n");
            goto done;
        }
        puts ("done\n");
        for (saved_buffer_startData=saved_offset;saved_buffer_startData < saved_offset + saved_size - 1 && saved_buffer[saved_buffer_startData - saved_offset] == 0xff;saved_buffer_startData++)
            ;
        for (saved_buffer_endData=saved_offset + saved_size - 1;saved_buffer_endData > saved_offset && saved_buffer[saved_buffer_endData - saved_offset] == 0xff;saved_buffer_endData--)
            ;
        if (saved_buffer_startData <= saved_buffer_endData)
            printf("Extra data found:    0x%08x..0x%08x\n", (unsigned int) saved_buffer_startData, (unsigned int) saved_buffer_endData );
        else
            printf("No extra data found: 0x%08x..0x%08x\n", (unsigned int) saved_offset, (unsigned int) (saved_offset + saved_size-1) );
    }
    if (CONFIG_ENV_SIZE > CONFIG_ENV_SECT_SIZE) 
    {
        sector = CONFIG_ENV_SIZE / CONFIG_ENV_SECT_SIZE;
        if (CONFIG_ENV_SIZE % CONFIG_ENV_SECT_SIZE)
        {
            sector++;
        }
    }
    
#ifdef CONFIG_ENV_OFFSET_REDUND    
    /* set current environment to obsolete */
    printf("Marking obsolete:    0x%08x..0x%08x ... ", (unsigned int) (env_offset + offsetof(env_t, flags)), (unsigned int) (env_offset + offsetof(env_t, flags) + sizeof(env_new.flags)-1) );
    ret = spi_flash_write(env_flash, env_offset + offsetof(env_t, flags), sizeof(env_new.flags), &flag);
    if (ret)
    {
        puts("failed\n");
        goto done;
    }
    puts("done\n");
#endif

    printf("Erasing:             0x%08x..0x%08x ... ", (unsigned int) env_new_offset, (unsigned int) (env_new_offset + sector * CONFIG_ENV_SECT_SIZE-1) );
    ret = spi_flash_erase(env_flash, env_new_offset,
                sector * CONFIG_ENV_SECT_SIZE);
    if (ret)
    {
        puts("failed\n");
        goto done;
    }
    puts ("done\n");
    
    /* write back other data in sector */
    if (CONFIG_ENV_SECT_SIZE > CONFIG_ENV_SIZE) 
    {
        if (saved_buffer_startData <= saved_buffer_endData)
        {
            printf("Restoring:           0x%08x..0x%08x ... ", saved_buffer_startData, saved_buffer_endData);
            ret = spi_flash_write(env_flash, saved_buffer_startData, saved_buffer_endData - saved_buffer_startData + 1, saved_buffer);
        if (ret)
        {
            puts("failed\n");
            goto done;
        }
        puts("done\n");
    }
        else 
            printf("Restoring skipped:   0x%08x..0x%08x\n", saved_offset, saved_offset + saved_size - 1);
    }
    printf("Writing environment: 0x%08x..0x%08x ... ", (unsigned int) env_new_offset, (unsigned int) (env_new_offset + CONFIG_ENV_SIZE-1) );

    ret = spi_flash_write(env_flash, env_new_offset, CONFIG_ENV_SIZE, &env_new);
    if (ret)
    {
        puts("failed\n");
        goto done;
    }
    puts("done\n");
    
    gd->env_valid = (gd->env_valid == 2 ? 1 : 2);
    printf("Valid environment: %d\n", (int)gd->env_valid);
#ifdef CONFIG_ENV_OFFSET_REDUND
    /* write redundant part: */
    /* load other data stored in erase size, and write it back after erase */
    /* Is the sector larger than the env (i.e. embedded) */
    if (CONFIG_ENV_SECT_SIZE > CONFIG_ENV_SIZE) 
    {
        saved_offset = env_offset + CONFIG_ENV_SIZE;
        printf("Reading:             0x%08x..0x%08x ... ", (unsigned int) saved_offset, (unsigned int) (saved_offset + saved_size-1) );
        ret = spi_flash_read(env_flash, saved_offset, saved_size, saved_buffer);
        if (ret)
        {
            puts ("failed\n");
            goto done;
        }
        puts ("done\n");
        for (saved_buffer_startData=saved_offset;saved_buffer_startData < saved_offset + saved_size -1 && saved_buffer[saved_buffer_startData - saved_offset] == 0xff;saved_buffer_startData++)
            ;
        for (saved_buffer_endData=saved_offset + saved_size -1;saved_buffer_endData > saved_offset && saved_buffer[saved_buffer_endData - saved_offset] == 0xff;saved_buffer_endData--)
            ;
        if (saved_buffer_startData <= saved_buffer_endData)
            printf("Extra data found:    0x%08x..0x%08x\n", (unsigned int) saved_buffer_startData, (unsigned int) saved_buffer_endData );
        else
            printf("No extra data found: 0x%08x..0x%08x\n", (unsigned int) saved_offset, (unsigned int) (saved_offset + saved_size-1) );
    }
    
    printf("Erasing:             0x%08x..0x%08x ... ", (unsigned int)env_offset, (unsigned int) (env_offset + sector * CONFIG_ENV_SECT_SIZE-1) );
    ret = spi_flash_erase(env_flash, env_offset,
                sector * CONFIG_ENV_SECT_SIZE);
    if (ret)
    {
        puts("failed\n");
        goto done;
    }
    puts ("done\n");
    
    /* write back other data in sector */
    if (CONFIG_ENV_SECT_SIZE > CONFIG_ENV_SIZE) 
    {
        if (saved_buffer_startData <= saved_buffer_endData)
        {
            printf("Restoring:           0x%08x..0x%08x ... ", saved_buffer_startData, saved_buffer_endData);
            ret = spi_flash_write(env_flash, saved_buffer_startData, saved_buffer_endData - saved_buffer_startData + 1, saved_buffer);
        if (ret)
        {
            puts("failed\n");
            goto done;
        }
        puts("done\n");
    }
        else 
            printf("Restoring skipped:   0x%08x..0x%08x\n", saved_offset, saved_offset + saved_size - 1);
    }
    
    printf("Writing environment: 0x%08x..0x%08x ... ", (unsigned int)env_offset, (unsigned int) (env_offset + CONFIG_ENV_SIZE-1) );
    ret = spi_flash_write(env_flash, env_offset,
        CONFIG_ENV_SIZE, &env_new);
    if (ret)
    {
        puts("failed\n");
        goto done;
    }
    puts("done\n");
#endif
    gd->env_valid = 1;
    printf("Valid environment: 1, 2\n");
done:
    if (saved_buffer)
    {
        free(saved_buffer);
        saved_buffer = NULL;
    }
    return ret;
}

void env_relocate_spec(void)
{
    int ret=0;
    int crc1_ok = 0;
    env_t *tmp_env1 = NULL;
    env_t *tmp_env2 = NULL;
    env_t *ep = NULL;
    tmp_env1 = (env_t *)malloc(sizeof(env_t));
    int startSaveEnv = 0;
    if (!tmp_env1) 
    {
        set_default_env("!malloc() failed\n");
        goto out;
    }
    memset(tmp_env1, 0, sizeof(env_t));
    env_flash = spi_flash_probe(CONFIG_ENV_SPI_BUS, CONFIG_ENV_SPI_CS, CONFIG_ENV_SPI_MAX_HZ, CONFIG_ENV_SPI_MODE);
    if (!env_flash) 
    {
        set_default_env("!spi_flash_probe() failed\n");
        goto out;
    }
    printf("Reading environment from SPI flash 0x%x..0x%x ... ", (unsigned int)CONFIG_ENV_OFFSET, (unsigned int) (CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE) );
    ret = spi_flash_read(env_flash, CONFIG_ENV_OFFSET, CONFIG_ENV_SIZE, tmp_env1);
    if (ret) 
    {
        set_default_env("failed\n");
        goto err_read;
    }
    else
    {
        puts ("done\n");
        if (crc32(0, tmp_env1->data, ENV_SIZE) == tmp_env1->crc)
        {
            crc1_ok = 1;
            puts ("  CRC32 OK");
        }
        else
            puts ("  CRC32 bad");
    #ifdef CONFIG_ENV_OFFSET_REDUND
        if (tmp_env1->flags == ACTIVE_FLAG)
            puts (", flag: Active");
        else if (tmp_env1->flags == OBSOLETE_FLAG)
            puts (", flag: Obsolete");
        else if (tmp_env1->flags == 0xFF)
            puts (", flag: 0xFF");
        else
            puts (", flag: unknown");
    #endif
    #ifdef CONFIG_SYS_ENVIRONMENT_VERSION
        printf (", version: 0x%02x, env_size: 0x%04x\n", tmp_env1->revision, tmp_env1->size);
    #else
        puts ("\n");
    #endif
    }
#ifndef CONFIG_ENV_OFFSET_REDUND
    if (!crc1_ok) 
    {
        set_default_env("!bad CRC\n");
        goto err_read;
    }
    ep = tmp_env1;
#endif
#ifdef CONFIG_ENV_OFFSET_REDUND
    int crc2_ok = 0;
    tmp_env2 = (env_t *)malloc(sizeof(env_t));
    if (!tmp_env2) 
    {
        set_default_env("!malloc() failed\n");
        goto out;
    }
    memset(tmp_env2, 0, sizeof(env_t));
    printf("Reading environment from SPI flash 0x%x..0x%x ... ", (unsigned int)CONFIG_ENV_OFFSET_REDUND, (unsigned int) (CONFIG_ENV_OFFSET_REDUND + CONFIG_ENV_SIZE) );
    ret = spi_flash_read(env_flash, CONFIG_ENV_OFFSET_REDUND, CONFIG_ENV_SIZE, tmp_env2);
    if (ret)
    {
        error("failed");
    }
    else
    {
        puts ("done\n");
        if (crc32(0, tmp_env2->data, ENV_SIZE) == tmp_env2->crc)
        {
            crc2_ok = 1;
            puts ("  CRC32 OK");
        }
        else
            puts ("  CRC32 bad");
    #ifdef CONFIG_ENV_OFFSET_REDUND
        if (tmp_env2->flags == ACTIVE_FLAG)
            puts (", flag: Active");
        else if (tmp_env2->flags == OBSOLETE_FLAG)
            puts (", flag: Obsolete");
        else if (tmp_env2->flags == 0xFF)
            puts (", flag: 0xFF");
        else
            puts (", flag: unknown");
    #endif
    #ifdef CONFIG_SYS_ENVIRONMENT_VERSION
        printf (", version: 0x%02x, env_size: 0x%04x\n", tmp_env2->revision, tmp_env2->size);
    #else
        puts ("\n");
    #endif
    }
#ifdef CONFIG_ENV_OFFSET_REDUND
    if (!crc1_ok && !crc2_ok)
    {
        set_default_env("!bad CRC\n");
        goto err_read;
    }
    else if (crc1_ok && !crc2_ok)
    {
        gd->env_valid = 1;
        startSaveEnv = 1;
    }
    else if (!crc1_ok && crc2_ok)
    {
        gd->env_valid = 2;
        startSaveEnv = 1;
    }
    else if (tmp_env1->flags == ACTIVE_FLAG && tmp_env2->flags == OBSOLETE_FLAG)
    {
        gd->env_valid = 1;
        startSaveEnv = 1;
    }
    else if (tmp_env1->flags == OBSOLETE_FLAG && tmp_env2->flags == ACTIVE_FLAG) 
    {
        gd->env_valid = 2;
        startSaveEnv = 1;
    }
    else if (tmp_env1->flags == OBSOLETE_FLAG && tmp_env2->flags == OBSOLETE_FLAG) 
    {
        gd->env_valid = 1;
        startSaveEnv = 1;
    }
#else
    if (!crc1_ok)
    {
        set_default_env("!bad CRC\n");
        goto err_read;
    }
#endif
    else 
    {
        gd->env_valid = 1;
    }
    printf("Importing environment: %d\n", (int)gd->env_valid);
    if (gd->env_valid == 1)
    {
        ep = tmp_env1;
        free(tmp_env2);
        tmp_env2 = NULL;
    }
    else
    {
        ep = tmp_env2;
        free(tmp_env1);
        tmp_env1 = NULL;
    }
#endif
    ret = env_import((char *)ep, 0);
    if (!ret) 
    {
        error("Cannot import environment: errno = %d", errno);
        set_default_env("env_import failed\n");
    }
err_read:
    spi_flash_free(env_flash);
    env_flash = NULL;
out:
    free(tmp_env1);
    tmp_env1 = NULL;
#ifdef CONFIG_ENV_OFFSET_REDUND
    free(tmp_env2);
    tmp_env2 = NULL;
#endif
#ifdef CONFIG_ENV_OFFSET_REDUND
    if (startSaveEnv)
    {
        puts("Saving restored environment to flash ...\n");
        if (saveenv())
            puts("Environment saving failed\n");
        else
            puts("Environment saved successfully\n");
    }
#endif
    return;
}


int env_init(void)
{
    /* SPI flash isn't usable before relocation */
    gd->env_addr = (ulong)&default_environment[0];
    gd->env_valid = 1;

    return 0;
}
