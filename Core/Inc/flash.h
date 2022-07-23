#ifndef __FLASH_H__
#define __FLASH_H__

#include "main.h"
#include "stm32f4xx_hal_flash_ex.h"

#define STM32_FLASH_SIZE 1024 //��ѡSTM32��FLASH������С(��λΪK)

#define FLASH_USER_START_ADDR 0x080E0000  //дFlash�ĵ�ַ������ӵ�62ҳ��ʼ
#define FLASH_USER_END_ADDR 0x080FFFFF    //дFlash�ĵ�ַ�������Ե�ҳ����
#define SECTOR_USER_INDEX FLASH_SECTOR_11 // ��ʼSector��� ��0��ʼ, Ϊ@ref FLASHEx_Sectors ����
#define SECTOR_USER_TOTAL 1               // Ҫ������Sector����

void Flash_Lock(void);
void Flash_Unlock(void);
uint32_t Flash_Erase_Sector(void);
void Flash_Write_Word(uint32_t *pBuffer, uint32_t NumToWrite);
void Flash_Read_Word(uint32_t *pBuffer, uint32_t NumToRead);
void Flash_RW_Test(void);

#endif
