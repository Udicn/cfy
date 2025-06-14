/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "oled_drv.h"
#include "stdio.h"
#include <stdlib.h>


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

unsigned char BMP1[] =
{
//����

	0x00,0x00,0xFE,0x7F,0x0F,0x77,0x17,0x76,0x02,0x83,0xC3,0xC3,0x82,0x02,0x76,0x17,
	0x77,0x0F,0x7F,0xFE,0x00,0x00,0xF8,0x7F,0x07,0x00,0x00,0x70,0xF0,0xD8,0x18,0x18,
	0x09,0x09,0x08,0x18,0xD8,0xF0,0x70,0x00,0x00,0x07,0x7F,0xF8,0x3F,0x3C,0x00,0x1F,
	0x3F,0x06,0x06,0x07,0x01,0x00,0x00,0x00,0x00,0x01,0x07,0x06,0x06,0x3F,0x1F,0x00,
	0x3C,0x3F,/*"C:\Users\Administrator\Desktop\1.BMP",0*/

};

unsigned char	BMP2[] =
{
//�ض�
	0x18,0x17,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x17,0x18,/*"C:\Users\Administrator\Desktop\2.BMP",0*/
};

unsigned char BMP3[] = 
{
//����
	0x60,0xF8,0xFC,0xFC,0xFC,0x7C,0x3E,0x1F,0x0F,0x07,0x07,0x0F,0xDE,0xFE,0xFC,0x30,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x7F,0xFF,0xE3,0xC1,0x80,0xC0,
	0xE0,0xF0,0xF8,0x7E,0xFF,0xFF,0xFF,0xFD,0xF8,0xF0,0xF0,0xE0,0xC0,0x80,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x01,0x01,
	0x03,0x07,0x0F,0x1F,0x1F,0x3F,0x3F,0x3F,0x3F,0x3E,0x3C,/*"C:\Users\Administrator\Desktop\3.bmp",0*/
	
};
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
#define TIME  1500
char win_temp=0;
char huan_pic=0;
	uint8_t rnd = 0;
	char temp=0;
		unsigned char chui = 0;
		char jiao = 0;
		uint16_t shijain = 0;
		int num =0;
// ȫ�ֱ���
volatile uint32_t countdown_target = 0;
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void win()
{
	OLED_Clear();		//����
					//��ϲ��򵽵����ˣ�
	OLED_ShowCHinese(40,2, 22);
	OLED_ShowCHinese(56,2, 23);
	OLED_ShowCHinese(72,2, 24);
	OLED_ShowCHinese(16,4, 25);
	OLED_ShowCHinese(32,4, 26);
	OLED_ShowCHinese(48,4, 27);
	OLED_ShowCHinese(64,4, 28);
	OLED_ShowCHinese(80,4, 29);
	OLED_ShowCHinese(98,4, 30);
	HAL_Delay(500);
}

void gg()
{
	OLED_Clear();
	//���ź���Ϸʧ��
	OLED_ShowCHinese(40,2, 17);
	OLED_ShowCHinese(56,2, 18);
	OLED_ShowCHinese(72,2, 19);
	OLED_ShowCHinese(32,4, 13);
	OLED_ShowCHinese(48,4, 14);
	OLED_ShowCHinese(64,4, 20);
	OLED_ShowCHinese(80,4, 21);
	HAL_Delay(500);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
	
	
int main(void)
{

  /* USER CODE BEGIN 1 */

//  uint8_t zzb=0;

//	Delay_ms(1000);
	

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM6_Init();
//	HAL_Delay(200);

  /* USER CODE BEGIN 2 */
	
	HAL_TIM_Base_Start_IT(&htim6);   
	
	OLED_Hinit();       //OLED�˿�����      
	OLED_SInit();		//OLED�ڲ���ʼ��
	
	GG:
	
	OLED_Clear();		//����
		//׼�������𣿰������������ʼ��Ϸ��
	OLED_ShowCHinese(35,0, 11);
	OLED_ShowCHinese(48,0, 12);
	OLED_ShowCHinese(64,0, 13);
	OLED_ShowCHinese(80,0, 14);
	
	while(jiao==0);
	jiao=0;	
	huan_pic=0;
	rnd=0;
  HAL_Delay(1000);

		
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		rnd = get_random_0_to_4();
		dishu();
		while(temp==0)
		{
			if(huan_pic==1)
			{
				rnd = get_random_0_to_4();
				dishu();
				huan_pic=0;
			}
			if(jiao==rnd)
			{
				temp=0;
				win();
				huan_pic=1;
				win_temp=1;
				jiao=0;
			}
			else if(jiao !=rnd &&jiao !=0)
			{
				temp=0;
				gg();
				win_temp=2;
				jiao=0;
				goto GG ;
					

			}
		}
//		while(win_temp==1)
//		{
//			
//			rnd = get_random_0_to_4();
//			dishu();
//			while(temp==0)
//			{
//				if(jiao==rnd)
//				{
//					win();
//					temp=0;
//				}
//				else 
//				{
//					win_temp=0;
//				}
//			}

//		}
		
//			shuchu();
//	    dishu();
//				if(countdown_target && (HAL_GetTick() >= countdown_target)) {
//  	OLED_Clear();		//����\
    countdown_target = 0; // ���Ŀ��ʱ��
//  }
//		delay_ms(500);
//		OLED_Clear();		//����
		
//		yanshi();
//		if(shijain == 1)
//		{
//				OLED_Clear();		//����
//		}
//		

//		if(rnd == 0 ||rnd == 1||rnd == 3 ){
//			HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_10,GPIO_PIN_SET);
//		}
    /* USER CODE END WHILE */
//				OLED_ShowCHinese(16,0, 0);
//		OLED_Refresh_Full();

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
uint8_t get_random_0_to_4(void) {

    // �ö�ʱ���� ADC ������Ϊ���ӣ�����ÿ�ο�����ͬ��
    uint32_t seed = HAL_GetTick();  // ��ϵͳ�δ��ʱ��
    srand(seed);
    // ���� 0~3 �������
    return ((rand() % 4)+1);

}
uint8_t shuchu(void){
				if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_7) == 0||
   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8) == 0 ||
   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9) == 0 ||
   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_10) == 0)
			{
				HAL_Delay(50);
							if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_7) == 0||
   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8) == 0 ||
   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9) == 0 ||
   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_10) == 0)
			{
				 rnd = get_random_0_to_4();
				
				
			}
			}
			return rnd;
}
void StartCountdown() {
  countdown_target = HAL_GetTick() + 50; // �������ʱ���
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if(GPIO_Pin == GPIO_PIN_7)
	{
		int time=TIME;
		while(time--);
		time=TIME;
		if(GPIO_Pin == GPIO_PIN_7)
		{
			jiao=1;
			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_8);
		}

	}
	else if(GPIO_Pin == GPIO_PIN_8)
	{
		int time=TIME;
		while(time--);
		time=TIME;
		if(GPIO_Pin == GPIO_PIN_8)
		{
				jiao=2;
				HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_8);
		}
			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_9);
	}
	else if(GPIO_Pin == GPIO_PIN_9)
	{
		int time=TIME;
		while(time--);
		time=TIME;
		if(GPIO_Pin == GPIO_PIN_9)
		{
			jiao=3;
			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_8);
		}
			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_10);
	}
	else if(GPIO_Pin == GPIO_PIN_10)
	{
		int time=TIME;
		while(time--);
		time=TIME;
		if(GPIO_Pin == GPIO_PIN_10)
		{
			jiao=4;
			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_8);
		}
		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_11);
	}
	
}
//uint16_t pin=GPIO_PIN_8;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim )
{
//	uint8_t kai = 0;
  if(htim->Instance==TIM6)
  {
		//if(chui == 1)
		//{
	//		dujiao();
//			shuchu();
			
    //  num  ++;
		
		//	if(num < 5000)
		//	{
//					kai = 1;
//				if(jiao == rnd){
//				
////				HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_10,GPIO_PIN_SET);
//				OLED_Clear();		//����
//					//��ϲ��򵽵����ˣ�
//	OLED_ShowCHinese(40,2, 22);
//	OLED_ShowCHinese(56,2, 23);
//	OLED_ShowCHinese(72,2, 24);
//	OLED_ShowCHinese(16,4, 25);
//	OLED_ShowCHinese(32,4, 26);
//	OLED_ShowCHinese(48,4, 27);
//	OLED_ShowCHinese(64,4, 28);
//	OLED_ShowCHinese(80,4, 29);
//	OLED_ShowCHinese(98,4, 30);
//				chui =0;
//				num = 0;

//			}
//				else if((jiao != rnd) &&(kai == 1) ){
//					OLED_Clear();
//	//���ź���Ϸʧ��
//	OLED_ShowCHinese(40,2, 17);
//	OLED_ShowCHinese(56,2, 18);
//	OLED_ShowCHinese(72,2, 19);
//	OLED_ShowCHinese(32,4, 13);
//	OLED_ShowCHinese(48,4, 14);
//	OLED_ShowCHinese(64,4, 20);
//	OLED_ShowCHinese(80,4, 21);
//			chui =0;
//			num = 0;
//					kai = 0;
//					
//				}
		//}
//else 
	//	{
//		OLED_Clear();
//	//���ź���Ϸʧ��
//	OLED_ShowCHinese(40,2, 17);
//	OLED_ShowCHinese(56,2, 18);
//	OLED_ShowCHinese(72,2, 19);
//	OLED_ShowCHinese(32,4, 13);
//	OLED_ShowCHinese(48,4, 14);
//	OLED_ShowCHinese(64,4, 20);
//	OLED_ShowCHinese(80,4, 21);
//			chui =0;
//			num = 0;

//		}


			

//}
//	}
}
	}
//uint16_t yanshi(void )
//{
//	HAL_Delay(500);
//	shijain = 1;
//	return shijain;
//}

// �ڶ�ʱ���ж��е��ã���1ms�жϣ�
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
//    if (htim->Instance == TIM6) { // ����Ƿ���TIM6�ж�
//        static uint8_t need_refresh = 0;
//        static uint32_t counter = 0;
//        
//        counter++;
//        if (counter >= 10) { // ÿ1000���ж�ִ��һ��
//            counter = 0; 
//            need_refresh = 1;
//        }
//        
//        if (need_refresh == 1 && chui == 1) {
//					HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_9,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_8,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_10,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(GPIOD ,GPIO_PIN_11,GPIO_PIN_SET);
//            // ִ����Ҫ����ˢ�µ�����
//             // ����ˢ����ʾ��
//            need_refresh = 0; // ���ñ�־
//        }
//    }
//}
void dishu(void)
{
	if(rnd==1)
	{
		OLED_Clear();		//����
		OLED_ShowCHinese(0,0, 31);
		OLED_ShowCHinese(0+16,0, 32);
		OLED_ShowCHinese(0+16+16,0, 33);
		OLED_ShowCHinese(0+16+16+16,0, 34);
		OLED_ShowCHinese(0+16+16+16+16,0, 35);
		OLED_DrawBMP(4,(64-24)/8,4+22,(64)/8,BMP1);
		
		OLED_DrawBMP(1,(64-5)/8,1+30,64/8,BMP2);
		OLED_DrawBMP(33,(64-5)/8,33+30,64/8,BMP2);
		OLED_DrawBMP(65,(64-5)/8,65+30,64/8,BMP2);
		OLED_DrawBMP(97,(64-5)/8,97+30,64/8,BMP2);
				// chui = chui + 1;
	}
	if(rnd==2)
	{
		OLED_Clear();		//����
		OLED_ShowCHinese(0,0, 31);
		OLED_ShowCHinese(0+16,0, 32);
		OLED_ShowCHinese(0+16+16,0, 33);
		OLED_ShowCHinese(0+16+16+16,0, 34);
		OLED_ShowCHinese(0+16+16+16+16,0, 35);
		OLED_DrawBMP(36,(64-24)/8,36+22,(64)/8,BMP1);
		
		OLED_DrawBMP(1,(64-5)/8,1+30,64/8,BMP2);
		OLED_DrawBMP(33,(64-5)/8,33+30,64/8,BMP2);
		OLED_DrawBMP(65,(64-5)/8,65+30,64/8,BMP2);
		OLED_DrawBMP(97,(64-5)/8,97+30,64/8,BMP2);
				 //chui = chui + 1;
		
	}
		if(rnd == 3)
		{
			OLED_Clear();		//����
			OLED_ShowCHinese(0,0, 31);
			OLED_ShowCHinese(0+16,0, 32);
			OLED_ShowCHinese(0+16+16,0, 33);
			OLED_ShowCHinese(0+16+16+16,0, 34);
			OLED_ShowCHinese(0+16+16+16+16,0, 35);
			OLED_DrawBMP(68,(64-24)/8,68+22,(64)/8,BMP1);
			OLED_DrawBMP(1,(64-5)/8,1+30,64/8,BMP2);
			OLED_DrawBMP(33,(64-5)/8,33+30,64/8,BMP2);
			OLED_DrawBMP(65,(64-5)/8,65+30,64/8,BMP2);
			OLED_DrawBMP(97,(64-5)/8,97+30,64/8,BMP2);
			chui = chui + 1;
		
		}
		if(rnd == 4)
		{
			OLED_Clear();		//����
			OLED_ShowCHinese(0,0, 31);
			OLED_ShowCHinese(0+16,0, 32);
			OLED_ShowCHinese(0+16+16,0, 33);
			OLED_ShowCHinese(0+16+16+16,0, 34);
			OLED_ShowCHinese(0+16+16+16+16,0, 35);
			OLED_DrawBMP(100,(64-24)/8,100+22,(64)/8,BMP1);
		
			OLED_DrawBMP(1,(64-5)/8,1+30,64/8,BMP2);
			OLED_DrawBMP(33,(64-5)/8,33+30,64/8,BMP2);
			OLED_DrawBMP(65,(64-5)/8,65+30,64/8,BMP2);
			OLED_DrawBMP(97,(64-5)/8,97+30,64/8,BMP2);
					 //chui = chui + 1;
		
		}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
