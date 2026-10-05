/**
 * @file VCU-Firmware - Core/Inc/eeprom.h
 *
 * Authors:
 *     Rakshay Narayanan <rakshay@terpmail.umd.edu>
*/

#ifndef __EEPROM_H
#define __EEPROM_H

#include "stm32f4xx_hal.h"

#define PAGE_SIZE ((uint32_t)0x20000) /* page size = 128KB */

/* device voltage range supposed to be [2.7V to 3.6V] */
#define VOLTAGE_RANGE ((uint8_t)FLASH_VOLTAGE_RANGE_3)

#define EEPROM_START_ADDRESS ((uint32_t)0x08020000) /* sector 5 */

/**/
#define PAGE0_BASE_ADDRESS ((uint32_t)(EEPROM_START_ADDRESS + 0x0000))
#define PAGE0_END_ADDRESS ((uint32_t)(EEPROM_START_ADDRESS + (PAGE_SIZE - 1)))
#define PAGE0_ID FLASH_SECTOR_5

#define PAGE1_BASE_ADDRESS ((uint32_t)(EEPROM_START_ADDRESS + PAGE_SIZE))
#define PAGE1_END_ADDRESS ((uint32_t)(EEPROM_START_ADDRESS + (PAGE_SIZE * 2 - 1)))
#define PAGE1_ID FLASH_SECTOR_6

/* page status markers in memory (first 2 bytes of page) */
#define ERASED ((uint16_t)0xFFFF)
#define RECEIVE_DATA ((uint16_t)0xEEEE)
#define VALID_PAGE ((uint16_t)0x0000)

/* number of variables */
#define NB_OF_VAR ((uint8_t)0x03)

typedef enum {
    EE_PAGE0,
    EE_PAGE1,
    EE_NO_VALID_PAGE,
    EE_PAGE_FULL
} EE_Page;

typedef enum {
    EE_READ_PAGE,
    EE_WRITE_PAGE
} EE_Operation;

uint16_t EE_Init(void);
uint16_t EE_ReadVariable(uint16_t VirtAddress, uint16_t *Data);
uint16_t EE_WriteVariable(uint16_t VirtAddress, uint16_t Data);

#endif /* __EEPROM_H */

