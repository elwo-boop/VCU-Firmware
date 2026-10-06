/**
 * @file VCU-Firmware - Core/Src/eeprom.c
 *
 * Authors:
 *     Rakshay Narayanan <rakshay@terpmail.umd.edu>
*/

#include "eeprom.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_flash.h"
#include "stm32f4xx_hal_flash_ex.h"
#include <stdint.h>

uint16_t data_var = 0;
uint16_t virt_address_var_tab[NB_OF_VAR];

static HAL_StatusTypeDef EE_Format(void);
static HAL_StatusTypeDef EE_EraseSector(uint32_t sector);
static uint16_t EE_FindValidPage(uint8_t operation);
static uint16_t EE_VerifyPageFullWriteVariable(uint16_t virtaddress, uint16_t data);
static uint16_t EE_PageTransfer(uint16_t virtaddress, uint16_t data);

HAL_StatusTypeDef EE_Init(void)
{
    uint16_t page0status = 1, page1status = 1;
    uint16_t eepromstatus = 0, readstatus = 0;
    HAL_StatusTypeDef flashstatus;
    uint16_t x = -1, varidx = 0;

    page0status = (*(__IO uint16_t *)PAGE0_BASE_ADDRESS);
    page1status = (*(__IO uint16_t *)PAGE1_BASE_ADDRESS);

    switch (page0status) {
    case ERASED:
        if (page1status == VALID_PAGE) {
            HAL_FLASH_Unlock();
            EE_EraseSector(PAGE0_ID);
            HAL_FLASH_Lock();
        } else if (page1status == RECEIVE_DATA) {

            FLASH_Erase_Sector(PAGE0_ID, VOLTAGE_RANGE);

            // mark page1 as valid
            flashstatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, PAGE1_BASE_ADDRESS, VALID_PAGE);
            if (flashstatus != HAL_OK)
                return flashstatus;
        } else {
            flashstatus = EE_Format();

            if (flashstatus != HAL_OK)
                return flashstatus;
        }
        break;

    case RECEIVE_DATA:
        if (page1status == VALID_PAGE) {
            for (;;;) {

            }
        }
    }

    return HAL_OK;
}

static HAL_StatusTypeDef EE_EraseSector(uint32_t sector)
{
    FLASH_EraseInitTypeDef eraseinfo = {0};
    uint32_t sectorerror;

    eraseinfo.TypeErase = 0U;
    eraseinfo.NbSectors = 1U;
    eraseinfo.Sector = sector;
    eraseinfo.VoltageRange = VOLTAGE_RANGE;

    return HAL_FLASHEx_Erase(&eraseinfo, &sectorerror);
}
