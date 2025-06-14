/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "tim.h"
 #include "oled_drv.h"
 static volatile uint8_t oled_need_refresh = 0; // 文件内静态变量
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim6;

/* TIM6 init function */
void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 72000000/10000000-1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 10000-1;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspInit 0 */

  /* USER CODE END TIM6_MspInit 0 */
    /* TIM6 clock enable */
    __HAL_RCC_TIM6_CLK_ENABLE();

    /* TIM6 interrupt Init */
    HAL_NVIC_SetPriority(TIM6_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM6_IRQn);
  /* USER CODE BEGIN TIM6_MspInit 1 */

  /* USER CODE END TIM6_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspDeInit 0 */

  /* USER CODE END TIM6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM6_CLK_DISABLE();

    /* TIM6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM6_IRQn);
  /* USER CODE BEGIN TIM6_MspDeInit 1 */

  /* USER CODE END TIM6_MspDeInit 1 */
  }
}


/* USER CODE BEGIN 1 */
/* USER CODE BEGIN 1 */
/**
  * @brief  毫秒级别延时函数
  * @param  num 延时毫秒数 (1 <= num <= 1864)
  * @retval 无
//  */
//volatile static uint8_t tim6_delay_done = 0;

//void delay_ms(uint16_t num)
//{
//    // 重新配置定时器为1ms中断
//    htim6.Instance->PSC = 7200-1;        // 72MHz/7200 = 10kHz
//    htim6.Instance->ARR = num*10-1;      // 10kHz/10 = 1ms (num*10-1)
//    htim6.Instance->EGR = TIM_EGR_UG;    // 产生更新事件
//    
//    // 重置完成标志
//    tim6_delay_done = 0;
//    
//    // 启动定时器中断
//    HAL_TIM_Base_Start_IT(&htim6);
//    
//    // 等待延时完成
//    while(tim6_delay_done == 0);
//    
//    // 停止定时器
//    HAL_TIM_Base_Stop_IT(&htim6);
//}
//volatile uint32_t system_ticks = 0;
//void TIM6_IRQHandler(void)
//{
//	if(__HAL_TIM_GET_FLAG(&htim6,TIM_FLAG_UPDATE) != RESET){
//		__HAL_TIM_CLEAR_FLAG(&htim6,TIM_FLAG_UPDATE);
//	
//	system_ticks++;
//	if(system_ticks %10 == 0){
//							HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_9,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_8,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_10,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_11,GPIO_PIN_SET);
//	}
//	}
//}
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//    if (htim->Instance == TIM6) { // 检查是否是TIM6中断
//        static uint8_t need_refresh = 0;
//        static uint32_t counter = 0;
//        
//        counter++;
//        if (counter >= 10) { // 每1000次中断执行一次
//            counter = 0; 
//            need_refresh = 1;
//        }
//        
//        if (need_refresh == 1 && chui == 1) {
//					HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_9,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_8,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_10,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_11,GPIO_PIN_SET);
//            // 执行需要定期刷新的任务
//             // 例如刷新显示屏
//            need_refresh = 0; // 重置标志
//        }
//    }
//}

//// 在需要刷新时设置标志位
//void Update_Screen(void) {
//    OLED_ShowString(0, 0, "Updated");
//    oled_need_refresh = 1; // 下次中断时自动刷新
//}
/* USER CODE END 1 */
/* USER CODE END 1 */
