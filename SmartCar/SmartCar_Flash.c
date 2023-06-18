/*
 * SmartCar_Flash.c
 *
 *  Created on: 2021Äê2ÔÂ3ÈÕ
 *      Author: ËïÎ¨
 */

#include "SmartCar_Flash.h"



void Sector_Erase(uint32 sector_num)
{
    uint32 flash = 0;
    uint16 end_init_sfty_pw;
    uint32 sector_addr = IfxFlash_dFlashTableEepLog[sector_num].start;

    end_init_sfty_pw = IfxScuWdt_getSafetyWatchdogPassword();

    IfxScuWdt_clearSafetyEndinit(end_init_sfty_pw);
    IfxFlash_eraseSector(sector_addr);
    IfxScuWdt_setSafetyEndinit(end_init_sfty_pw);

    IfxFlash_waitUnbusy(flash, IfxFlash_FlashType_D0);
}


void Page_Program(uint32 sector_num, uint32 page_num, uint32 *buf)
{

    uint32 errors = 0;
    uint32 flash = 0;
    uint16 end_init_sfty_pw;
    uint32 sector_addr = IfxFlash_dFlashTableEepLog[sector_num].start;

    end_init_sfty_pw = IfxScuWdt_getSafetyWatchdogPassword();

    uint32 page_addr = sector_addr + page_num * IFXFLASH_DFLASH_PAGE_LENGTH;
    errors = IfxFlash_enterPageMode(page_addr);

    IfxFlash_waitUnbusy(flash, IfxFlash_FlashType_D0);

    IfxFlash_loadPage(page_addr, buf[0], 0);

    IfxScuWdt_clearSafetyEndinit(end_init_sfty_pw);
    IfxFlash_writePage(page_addr);
    IfxScuWdt_setSafetyEndinit(end_init_sfty_pw);

    IfxFlash_waitUnbusy(flash, IfxFlash_FlashType_D0);
}

void Sector_Program(uint32 sector_num, uint32* buf)
{
    uint32* page_addr=buf;
    for(uint32 i=0;i<EEPROM_SECTOR_PAGE_NUM;i++)
    {
        Page_Program(sector_num, i, page_addr);
        page_addr++;
    }
}
