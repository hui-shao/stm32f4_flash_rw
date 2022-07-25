/* USER CODE BEGIN Header */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "flash.h"
/**
 ******************************************************************************
 * @file    usart.c
 * @brief   This file provides code for the configuration
 *          of the USART instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

char uart3_rx_buf[UART3_RX_BUF_LEN], uart3_tx_buf[UART3_TX_BUF_LEN];
char uart2_rx_buf[UART2_RX_BUF_LEN], uart2_tx_buf[UART2_TX_BUF_LEN];

uint8_t uart3_rx_size, uart2_rx_size; // 用于记录接受到的数据的长度
__IO uint8_t uart3_rx_flag = 0, uart2_rx_flag = 0;

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart3_rx;
DMA_HandleTypeDef hdma_usart3_tx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */
}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */
}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */
}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (uartHandle->Instance == USART1)
  {
    /* USER CODE BEGIN USART1_MspInit 0 */

    /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USER CODE BEGIN USART1_MspInit 1 */

    /* USER CODE END USART1_MspInit 1 */
  }
  else if (uartHandle->Instance == USART2)
  {
    /* USER CODE BEGIN USART2_MspInit 0 */

    /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 DMA Init */
    /* USART2_RX Init */
    hdma_usart2_rx.Instance = DMA1_Stream5;
    hdma_usart2_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_rx.Init.Mode = DMA_NORMAL;
    hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle, hdmarx, hdma_usart2_rx);

    /* USART2_TX Init */
    hdma_usart2_tx.Instance = DMA1_Stream6;
    hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx.Init.Mode = DMA_NORMAL;
    hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle, hdmatx, hdma_usart2_tx);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    /* USER CODE BEGIN USART2_MspInit 1 */

    /* USER CODE END USART2_MspInit 1 */
  }
  else if (uartHandle->Instance == USART3)
  {
    /* USER CODE BEGIN USART3_MspInit 0 */

    /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART3 DMA Init */
    /* USART3_RX Init */
    hdma_usart3_rx.Instance = DMA1_Stream1;
    hdma_usart3_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart3_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart3_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart3_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart3_rx.Init.Mode = DMA_NORMAL;
    hdma_usart3_rx.Init.Priority = DMA_PRIORITY_MEDIUM;
    hdma_usart3_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart3_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle, hdmarx, hdma_usart3_rx);

    /* USART3_TX Init */
    hdma_usart3_tx.Instance = DMA1_Stream3;
    hdma_usart3_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart3_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart3_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart3_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart3_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart3_tx.Init.Mode = DMA_NORMAL;
    hdma_usart3_tx.Init.Priority = DMA_PRIORITY_MEDIUM;
    hdma_usart3_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart3_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle, hdmatx, hdma_usart3_tx);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
    /* USER CODE BEGIN USART3_MspInit 1 */

    /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle)
{

  if (uartHandle->Instance == USART1)
  {
    /* USER CODE BEGIN USART1_MspDeInit 0 */

    /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);

    /* USER CODE BEGIN USART1_MspDeInit 1 */

    /* USER CODE END USART1_MspDeInit 1 */
  }
  else if (uartHandle->Instance == USART2)
  {
    /* USER CODE BEGIN USART2_MspDeInit 0 */

    /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);

    /* USART2 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
    /* USER CODE BEGIN USART2_MspDeInit 1 */

    /* USER CODE END USART2_MspDeInit 1 */
  }
  else if (uartHandle->Instance == USART3)
  {
    /* USER CODE BEGIN USART3_MspDeInit 0 */

    /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10 | GPIO_PIN_11);

    /* USART3 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
    /* USER CODE BEGIN USART3_MspDeInit 1 */

    /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{ // Size为接收到的数据大小
  if (huart->Instance == USART3)
  {
    HAL_UART_DMAStop(&huart3);                                                            // 关闭是为了重新设置发送多少数据，不关闭会造成数据错误
    uart3_rx_size = (Size < UART3_RX_BUF_LEN) ? (Size) : ((uint8_t)UART3_RX_BUF_LEN - 1); // 记录接受到的长度
    uart3_rx_buf[uart3_rx_size] = 0;                                                      // 设置结束位
    // printf("%s\r\n", uart3_rx_buf); // 打到串口一看看 for test
    uart3_rx_flag = 1;
  }
  else if (huart->Instance == USART2)
  {
    HAL_UART_DMAStop(&huart2);                                                            // 关闭是为了重新设置发送多少数据，不关闭会造成数据错误
    uart2_rx_size = (Size < UART2_RX_BUF_LEN) ? (Size) : ((uint8_t)UART2_RX_BUF_LEN - 1); // 记录接受到的长度
    uart2_rx_buf[uart2_rx_size] = 0;                                                      // 设置结束位
    uart2_rx_flag = 1;
  }
}

void UART3_Start_ReceiveToIdle(void)
{
  memset(uart3_rx_buf, 0, UART3_RX_BUF_LEN);
  uart3_rx_flag = 0;
  HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t *)uart3_rx_buf, UART3_RX_BUF_LEN - 1); //继续开启空闲中断DMA发送
  __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);                                     // 关闭半传输中断, 否则每次进中断时只能受到缓冲区大小一半的数据
}

void UART2_Start_ReceiveToIdle(void)
{
  memset(uart2_rx_buf, 0, UART2_RX_BUF_LEN);
  uart2_rx_flag = 0;
  HAL_UARTEx_ReceiveToIdle_DMA(&huart2, (uint8_t *)uart2_rx_buf, UART2_RX_BUF_LEN - 1); //继续开启空闲中断DMA发送
  __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);                                     // 关闭半传输中断, 否则每次进中断时只能受到缓冲区大小一半的数据
}

void UART_USER_Receive_Handler(void)
{
  if (uart3_rx_flag)
  {
    // 串口接收完成
    printf("UART3 Received.\r\n");
    float fix_k = 0.0f;
    char *p = strstr(uart3_rx_buf, "flash:");
    uint8_t num = sscanf(uart3_rx_buf, "flash:%f", &fix_k);
    if (p != NULL && num == 1)
    {
      // 进行flash读写
      printf("Flash Write start. fix_k=%f\r\n", fix_k);
      uint8_t text_buf[20] = {0};
      snprintf((char *)text_buf, 20, (const char *)"%f", fix_k);

      Flash_Unlock();
      Flash_Erase_Sector();
      Flash_Write_Word((uint32_t *)text_buf, (sizeof(text_buf) + 3) / 4);
      uint8_t read_buf[20] = {0};
      Flash_Read_Word((uint32_t *)read_buf, 5); // 注意最大长度。一方面不要超过Sector, 另一方面不要超过转为u32后数组长度
      printf("Read result: %s\r\n", read_buf);
      Flash_Lock();
    }
    UART3_Start_ReceiveToIdle(); // 再次开启中断接受
  }
  else if (uart2_rx_flag)
  {
    // 串口接收完成
    printf("UART2 Received.\r\n");
    float fix_k = 0.0f;
    char *p = strstr(uart2_rx_buf, "flash:");
    uint8_t num = sscanf(uart2_rx_buf, "flash:%f", &fix_k);
    if (p != NULL && num == 1)
    {
      // 进行flash读写
      printf("Flash Write start. fix_k=%f\r\n", fix_k);
      uint8_t text_buf[20] = {0};
      snprintf((char *)text_buf, 20, (const char *)"%f", fix_k);

      Flash_Unlock();
      Flash_Erase_Sector();
      Flash_Write_Word((uint32_t *)text_buf, (sizeof(text_buf) + 3) / 4);
      uint8_t read_buf[20] = {0};
      Flash_Read_Word((uint32_t *)read_buf, 5); // 注意最大长度。一方面不要超过Sector, 另一方面不要超过转为u32后数组长度
      printf("Read result: %s\r\n", read_buf);
      Flash_Lock();
    }
    UART2_Start_ReceiveToIdle(); // 再次开启中断接受
  }
}

/**
 * @description: 向 USART3 串口发送缓冲区中的原始数据 DMA模式 注意：调用前应设置好 uart3_tx_buf 内容
 * @param {uint16_t} len 所要发送数据的长度
 * @return {*}
 */
void u3_transmit_dma(uint16_t len)
{
  //等待上一次的数据发送完毕
  while (HAL_DMA_GetState(&hdma_usart3_tx) != HAL_DMA_STATE_READY)
    ;
  if (len > UART3_TX_BUF_LEN)
  {
    len = UART3_TX_BUF_LEN;
  }
  HAL_UART_Transmit_DMA(&huart3, (uint8_t *)uart3_tx_buf, len);
}

/**
 * @description: 向 USART3 串口发送缓冲区中字符串 DMA模式 注意，\00将被移除
 * @param {char} *fmt 需要发送的字符串
 * @return {*}
 */
void u3_printf_dma(char *fmt, ...)
{
  //等待上一次的数据发送完毕
  while (HAL_DMA_GetState(&hdma_usart3_tx) != HAL_DMA_STATE_READY)
    ;

  memset(uart3_tx_buf, 0, UART3_TX_BUF_LEN);
  uint16_t i, j;
  va_list ap;
  va_start(ap, fmt);
  vsprintf((char *)uart3_tx_buf, fmt, ap);
  va_end(ap);

  for (i = 0; i < UART3_TX_BUF_LEN; i++)
  {
    j = i + 1;
    if (uart3_tx_buf[i] == '\00')
    {
      for (; j < UART3_TX_BUF_LEN; j++)
      {
        uart3_tx_buf[j - 1] = uart3_tx_buf[j];
      }
    }
  }
  i = strlen((const char *)uart3_tx_buf);
  HAL_UART_Transmit_DMA(&huart3, (uint8_t *)uart3_tx_buf, i);
}

/**
 * @description: 将测到的数据打包, 通过蓝牙发送
 * @param {*}
 * @return {*}
 */
void Bluetooth_PackandSend(void)
{
  /* 临时测试用 */ // todo:
  float f = 1962.5f, Vpp = 1.025f, DC = 1.515f;
  uint8_t wave_type = 2;

  /* 字符串拼接 */
  char text[32];
  memset(text, 0, sizeof(text));
  memset(uart3_tx_buf, 0, UART3_TX_BUF_LEN);

  strcpy(uart3_tx_buf, "B,");

  memset(text, 0, sizeof(text));
  snprintf(text, 12, "%.3f,", f); // 频率
  strcat(uart3_tx_buf, text);

  memset(text, 0, sizeof(text));
  snprintf(text, 12, "%.3f,", Vpp); // 峰峰值
  strcat(uart3_tx_buf, text);

  memset(text, 0, sizeof(text));
  snprintf(text, 12, "%.3f,", DC); // 直流分量
  strcat(uart3_tx_buf, text);

  memset(text, 0, sizeof(text));
  snprintf(text, 12, "%d,", wave_type); // 波形类型
  strcat(uart3_tx_buf, text);

  strcat(uart3_tx_buf, "E\n");

  /* 发送 */
  uint16_t len = strlen(uart3_tx_buf);
  u3_transmit_dma(len);

  // memset(uart3_tx_buf, 0, UART3_TX_BUF_LEN); // 因为使用了DMA非阻塞执行，不应立即清空Buf，改为发送前清空
}

// 重定向 printf 到串口1
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
/* USER CODE END 1 */
