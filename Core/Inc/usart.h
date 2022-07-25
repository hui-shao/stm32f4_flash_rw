/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    usart.h
 * @brief   This file contains all the function prototypes for
 *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

  /* USER CODE BEGIN Includes */

  /* USER CODE END Includes */

  extern UART_HandleTypeDef huart1;

  extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
#define UART3_RX_BUF_LEN 256
#define UART3_TX_BUF_LEN 256
  /* USER CODE END Private defines */

  void MX_USART1_UART_Init(void);
  void MX_USART3_UART_Init(void);

  /* USER CODE BEGIN Prototypes */
  extern char uart3_rx_buf[];
  extern char uart3_tx_buf[];
  extern uint8_t uart3_rx_size;
  void UART3_Start_ReceiveToIdle(void);
  /* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
