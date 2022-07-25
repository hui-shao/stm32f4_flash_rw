/*
 * @Author: Hui-Shao
 * @Date: 2022-07-22 15:30:44
 * @LastEditTime: 2022-07-25 10:45:09
 * @Description:
 *
 *  Flash读写 注意在 flash.h 进行相关配置
 *  目前已知, 实际能用, 但如果用Keil调试或者烧录, 可能会让PGPERR PGSERR置1,导致无法写入
 *  可以在Keil的Debug中把 Load Application at Startup 这个复选框取消掉, 然后就能用了
 *
 *
 * Copyright (c) 2022 by Hui-Shao, All Rights Reserved.
 */

#include "flash.h"
#include <stdio.h>

uint8_t TEXT_Buffer[] = {"FLASH_TEST_0.2f"}; //要写入到STM32 FLASH的字符串数组
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
    uint32_t SECTOR_Error = 0; // 存储错误码
    FLASH_EraseInitTypeDef EraseInitStruct = {0};

    EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.Sector = SECTOR_USER_INDEX;
    EraseInitStruct.NbSectors = SECTOR_USER_TOTAL;

    SET_BIT(FLASH->SR, (1 << 5 | 1 << 6)); // 要清除错误标志 不是很正常 todo:

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
        Address = Address + 4; //地址后移4个字节 因为是Word
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
            Address = Address + 4; //地址后移4个字节 因为是Word
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
    Flash_Unlock();                                                           // 先解锁
    Flash_Erase_Sector();                                                     // 再擦除
    Flash_Write_Word((uint32_t *)TEXT_Buffer, (sizeof(TEXT_Buffer) + 3) / 4); // 4个8位组成一个32位;加3是为了向上取整
    Flash_Lock();
#endif
    Flash_Read_Word((uint32_t *)Read_Buf, 10); // 注意最大长度。一方面不要超过Sector, 另一方面不要超过转为u32后数组长度
    printf("Read result: %s\r\n", Read_Buf);
}
