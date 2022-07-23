#ifndef __FLASH_H__
#define __FLASH_H__

#include "main.h"
#include "stm32f4xx_hal_flash_ex.h"

#define STM32_FLASH_SIZE 1024 //所选STM32的FLASH容量大小(单位为K)

#define FLASH_USER_START_ADDR 0x080E0000  //写Flash的地址，这里从第62页开始
#define FLASH_USER_END_ADDR 0x080FFFFF    //写Flash的地址，这里以第页结束
#define SECTOR_USER_INDEX FLASH_SECTOR_11 // 起始Sector标号 从0开始, 为@ref FLASHEx_Sectors 类型
#define SECTOR_USER_TOTAL 1               // 要擦除的Sector总数

void Flash_Lock(void);
void Flash_Unlock(void);
uint32_t Flash_Erase_Sector(void);
void Flash_Write_Word(uint32_t *pBuffer, uint32_t NumToWrite);
void Flash_Read_Word(uint32_t *pBuffer, uint32_t NumToRead);
void Flash_RW_Test(void);

#endif
