/*
 * @Author: Hui-Shao
 * @Date: 2022-07-22 15:30:44
 * @LastEditTime: 2022-07-25 10:45:09
 * @Description:
 *
 *  Flash��д ע���� flash.h �����������
 *  Ŀǰ��֪, ʵ������, �������Keil���Ի�����¼, ���ܻ���PGPERR PGSERR��1,�����޷�д��
 *  ������Keil��Debug�а� Load Application at Startup �����ѡ��ȡ����, Ȼ���������
 *
 *
 * Copyright (c) 2022 by Hui-Shao, All Rights Reserved.
 */

#include "flash.h"
#include <stdio.h>

uint8_t TEXT_Buffer[] = {"FLASH_TEST_0.2f"}; //Ҫд�뵽STM32 FLASH���ַ�������
uint8_t Read_Buf[100] = {0};

void Flash_Unlock(void)
{
    if (HAL_FLASH_Unlock() != HAL_OK)
    {
        printf("Unlock Error\r\n");
        Error_Handler();
    }
}

void Flash_Lock(void)
{
    if (HAL_FLASH_Lock() != HAL_OK)
    {
        printf("Lock Error\r\n");
        Error_Handler();
    }
}

uint32_t Flash_Erase_Sector(void)
{
    uint32_t SECTOR_Error = 0; // �洢������
    FLASH_EraseInitTypeDef EraseInitStruct = {0};

    EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.Sector = SECTOR_USER_INDEX;
    EraseInitStruct.NbSectors = SECTOR_USER_TOTAL;

    SET_BIT(FLASH->SR, (1 << 5 | 1 << 6)); // Ҫ��������־ ���Ǻ����� todo:

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTOR_Error) != HAL_OK)
    {
        Flash_Lock();
        printf("Erase Error...\r\n");
        Error_Handler();
    }

    return SECTOR_Error;
}

void Flash_Read_Word(uint32_t *pBuffer, uint32_t NumToRead)
{
    uint16_t i = 0;
    uint32_t Address = FLASH_USER_START_ADDR;
    printf("Flash read start.\r\n");
    while ((Address < FLASH_USER_END_ADDR) && (i < NumToRead))
    {
        pBuffer[i++] = *(__IO uint32_t *)Address;
        Address = Address + 4; //��ַ����4���ֽ� ��Ϊ��Word
    }
}

void Flash_Write_Word(uint32_t *pBuffer, uint32_t NumToWrite)
{
    uint16_t i = 0;
    uint32_t Address = FLASH_USER_START_ADDR;
    while ((Address < FLASH_USER_END_ADDR) && (i < NumToWrite))
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, pBuffer[i]) == HAL_OK)
        {
            Address = Address + 4; //��ַ����4���ֽ� ��Ϊ��Word
            i++;
        }
        else
        {
            printf("Write Error at %d..\r\n", i);
            Error_Handler();
        }
    }
    printf("Write Finished.\r\n");
}

void Flash_RW_Test(void)
{
#if _FLASH_TEST_WRITE
    Flash_Unlock();                                                           // �Ƚ���
    Flash_Erase_Sector();                                                     // �ٲ���
    Flash_Write_Word((uint32_t *)TEXT_Buffer, (sizeof(TEXT_Buffer) + 3) / 4); // 4��8λ���һ��32λ;��3��Ϊ������ȡ��
    Flash_Lock();
#endif
    Flash_Read_Word((uint32_t *)Read_Buf, 10); // ע����󳤶ȡ�һ���治Ҫ����Sector, ��һ���治Ҫ����תΪu32�����鳤��
    printf("Read result: %s\r\n", Read_Buf);
}
