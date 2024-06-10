/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2015 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "stdlib.h"

/* USER CODE BEGIN Includes */
#include "zlg7290.h"
#include "stdio.h"
#include "stm32f4xx_hal_iwdg.h"		//????????????????????IWDG
#include "stm32f4xx_hal_iwdg.c"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define DE_A  		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET) 
#define DE_B  		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET)
#define DE_C    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET) 
#define DE_D      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_SET)

#define DE_AB  		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET) 
#define DE_BC  		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_RESET)
#define DE_CD    	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_SET) 
#define DE_DA     HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);HAL_GPIO_WritePin(GPIOH, GPIO_PIN_13,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6,GPIO_PIN_SET)

#define ZLG_READ_ADDRESS1         0x01
#define ZLG_READ_ADDRESS2         0x10
#define ZLG_WRITE_ADDRESS1        0x10
#define ZLG_WRITE_ADDRESS2        0x11
#define HAL_IWDG_DEFAULT_TIMEOUT            ((uint32_t)1000)    //看门狗时间1s
#define BUFFER_SIZE1              (countof(Tx1_Buffer))
#define BUFFER_SIZE2              (countof(Rx2_Buffer))
#define countof(a) (sizeof(a) / sizeof(*(a)))

typedef struct ValueAndBack{//数据备份结构体
	uint8_t Odata;
	uint8_t checksum;

	uint8_t back1;
	uint8_t checksum1;

	uint8_t back2;
	uint8_t checksum2;
}Data;

uint8_t flag;						//??????????????lag	  1????
uint8_t flag1 = 0;					//HAL???????d????	  	6|	 |2
uint8_t Rx2_Buffer[8]={0};			//8????????????????????????????????   7??????
uint8_t Tx1_Buffer[8]={0};			//						   5|	|3
uint8_t Rx1_Buffer[1]={0};			//??????					 4??????
IWDG_HandleTypeDef *hiwdg;

void SystemClock_Config(void);

void switch_key(void);				//??????????????lag
void switch_flag(void);				//?????????flag????????????
void BeeWater(void);				//??????????????
int ReadNumber(void);				//??????????????????????????
uint16_t _pow(uint8_t a, uint8_t b);	//????$?
uint8_t CheckData(void);			//???????ata?????
uint8_t Decode(uint8_t x);			//?????????Rx2????????????,??witch_flag??witch_key????????
void FaultDeal(void);				//????????????
void Init(void);						//??????????????????
void TempUpdate(uint8_t t);	//????????????Data?????
void FlushBoard(void);				//???Rx2??????'#'??????
void EnterSleep(void);				//????$????
void EnterMain(void);				//??????'*'????????????switch_flag
void IWDG_Init(void);

//?????????????????????
__attribute__((section(".uninit"),zero_init)) Data Temperature;		//?????????
__attribute__((section(".uninit"),zero_init)) uint16_t HotStart;	//????????
__attribute__((section(".uninit"),zero_init)) uint32_t DelayTime;	//?????????
__attribute__((section(".uninit"),zero_init)) uint8_t InputLen;		//?????????????????????
__attribute__((section(".uninit"),zero_init)) uint32_t LastTime;	//???????????????????et???

int main(void)
{
	Init();
	//随机延迟启动
	DelayTime = rand() % 21 + 80;
  	HAL_Delay(DelayTime);
	//printf("HotStart=%d\r\n",HotStart);
	if(HotStart != 0xffff){//冷启动
		printf("Cold Start!!!!HotStart=%d\r\n",HotStart);
		HotStart = 0xffff;
		TempUpdate(25);
	}else{//热启动
		printf("\r\nhotStart,HoyStart=%d\r\n",HotStart);
	}

	printf("\n\r-------------------------------------------------\r\n");
	printf("\n\r ---------------Fire watering System--------------\r\n");	
	
	//watch_dog		done
	IWDG_Init();		//看门狗初始化
	while (1)
	{
		if(flag1 == 1){		//检测到用户输入
			flag1 = 0;
			//喂狗
			__HAL_IWDG_RELOAD_COUNTER(hiwdg);
			//读取用户输入
			I2C_ZLG7290_Read(&hi2c1,0x71,0x01,Rx1_Buffer,1);
			//用户输入转换
			switch_key();
			I2C_ZLG7290_Read(&hi2c1,0x71,0x10,Rx2_Buffer,8);
			//??????????????
			LastTime = HAL_GetTick();
			//???????
			switch_flag();
			I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1+2,Tx1_Buffer+2,6);
			/*
			if((InputLen >= 2 && flag <= 9 && flag >= 0)){	//??????,????????????????????
				continue;
			}else{		//?????????????????????????????
				
				InputLen++;
			??*/
		}else{
			//????????$????
			printf("HAL_GetTICK:----->%d\n",HAL_GetTick());
			if((HAL_GetTick())%5050 - 0 > 5000){//????????????????????????????????
				FlushBoard();
				EnterSleep();
			}
			//EnterSleep();
			printf("\r\nhotStart, Temperature=%d\r\n",Temperature.Odata);
		}
	}
  /* USER CODE END 3 */
}


/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
void IWDG_Init(void)
{

  hiwdg->Instance = IWDG;
  hiwdg->Init.Prescaler = IWDG_PRESCALER_4;
  hiwdg->Init.Reload = 0x0ffff;
  HAL_IWDG_Init(hiwdg);
}

//??????
void Init(void){
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_USART1_UART_Init();
}

//??????
void EnterSleep(void){
	HAL_SuspendTick();
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
	HAL_ResumeTick();
}

//?????????????
void FaultDeal(void){
	printf("this is error while checking data\r");
	//????????????????????
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);
	HAL_Delay(20);
	FlushBoard();
}

//????????????
void FlushBoard(void){
	Tx1_Buffer[0] = 0x00;
	I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,8);
	InputLen = 0;
}

//'*'?????
void EnterMain(void){
		uint8_t temp1 = ReadNumber();				//??????????????
		uint8_t temp2 = ReadNumber();
		uint8_t ave = (temp1 + temp2)/2;
		//printf("--------------%d\r",ave);
		TempUpdate(ave);
			//printf("%---d--\r",Temperature.Odata);
		uint8_t yes = CheckData();
	//printf("yes:%d",yes);
	//printf("%---d--\r",Temperature.Odata);
		if(yes && Temperature.Odata - 1 > 40){
			printf("Tempreture is ==>%d\r",Temperature.Odata - 1);
			BeeWater();
		}else if(!yes){
			printf("check is error\r");
			FaultDeal();//???????#'?????ee???????????????????
		}else{
			printf("not so hot, I think there has no fire\r");
		}
		FlushBoard();	//???0???,???2???,??????????????
}

//??????????x2_buffer????????????
uint8_t Decode(uint8_t x){
	switch(x){
		case 0x0c:
			return 1;
		case 0xda:
			return 2;
		case 0xf2:
			return 3;
		case 0x66:
			return 4;
		case 0xb6:
			return 5;
		case 0xbe:
			return 6;
		case 0xe0:
			return 7;
		case 0xfe:
			return 8;
		case 0xe6:
			return 9;
		case 0xfc:
			return 0;
		default://ABCDEF??????0???
			return 0;
	}
}

//???????$?8??????????????
int ReadNumber(void){
	int i = 1;
	uint8_t temp = 0;
	while( i >= 0){
		if(Rx2_Buffer[i] != 0){
			temp += Decode(Rx2_Buffer[i]) * _pow(10, i);
		}
		i--;
	}
	return temp;
}

//???a?????
uint16_t _pow(uint8_t a, uint8_t b){
	uint16_t result = 1;
	while(b > 0){
		result *= a;
		b--;
	}
	return result;
}

//????????????????-?????1
uint8_t CheckData(void){
	if((Temperature.Odata ^ 0xff) != Temperature.checksum){
		if((Temperature.back1 ^ 0xff) == Temperature.checksum){
			Temperature.Odata = Temperature.back1;
			Temperature.checksum = Temperature.Odata ^ 0xff;
		}else{
			if((Temperature.back2 ^ 0xff) == Temperature.checksum2){
				Temperature.Odata = Temperature.back2;
				Temperature.checksum = Temperature.Odata ^ 0xff;
				Temperature.back1 = Temperature.back2;
				Temperature.checksum1 = Temperature.back1 ^ 0xff;
			}else{
				return 0;
			}
		}
	}
	return 1;
}

//??????????????
void BeeWater(void){
	while(flag1 == 0){
			//beep
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);
	HAL_Delay(5);
	//step_motor
	DE_A;
	HAL_Delay(3);
	DE_AB;
	HAL_Delay(3);
	DE_B;
	HAL_Delay(3);
	DE_BC;
	HAL_Delay(3);
	DE_C;
	HAL_Delay(3);
	DE_CD;
	HAL_Delay(3);
	DE_D;
	HAL_Delay(3);	
	DE_DA;
	HAL_Delay(3);
	}

}

//????????????'???'???
void TempUpdate(uint8_t temp){
	Temperature.Odata = temp + 1;
	Temperature.checksum = Temperature.Odata ^ 0xff;
	Temperature.back1 = temp + 1;
	Temperature.checksum1 = Temperature.back1 ^ 0xff;
	Temperature.back2 = temp + 1;
	Temperature.checksum2 = Temperature.back2 ^ 0xff;
}

void switch_key(void)
{
	switch(Rx1_Buffer[0])
	{
        case 0x1C:		
			flag = 1;			
        	break;
        case 0x1B:		
			flag = 2;
        	break;
        case 0x1A:		
			flag = 3;
        	break;
        case 0x14:		
			flag = 4;
        	break;   
		case 0x13:		
			flag = 5;
			break;
        case 0x12:		
			flag = 6;
          	break;
        case 0x0C:		
			flag = 7;
          	break;
        case 0x0B:      
			flag = 8;
          	break;
		case 0x0A:		
			flag = 9;
			break;
		case 0x03:		
			flag = 0;
			break;
		/*					//??????10?????????ban??
		case 0x19://a
			flag = 10;
			break;
		case 0x11://b
			flag = 11;
			break;
		case 0x09://c
			flag = 12;
			break;
		case 0x01://d
			flag = 13;
			break;
		*/
		case 0x02://#		//'#'????????*'??????
			flag = 14;
			break;
		case 0x04://*
			flag = 15;
			break;
        default:
        	break;
	}
}

void switch_flag(void){
	int rand_func;
	switch(flag){
		case 0:
			Tx1_Buffer[0] = 0xFC;
			if(Rx2_Buffer[0] == 0){
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
			}else{
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);						
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);						
			}
			break;
		case 1:
			Tx1_Buffer[0] = 0x0c;
			if(Rx2_Buffer[0] == 0){
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
			}else{									
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);					
			}
			break;
		case 2:
			Tx1_Buffer[0] = 0xDA;
			if(Rx2_Buffer[0] == 0){
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
			}else{
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);		
			}
			break;
		case 3:
			Tx1_Buffer[0] = 0xF2;
			if(Rx2_Buffer[0] == 0){
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
			}else{
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);						
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);		
			}
			break;
		case 4:
			Tx1_Buffer[0] = 0x66;
			if(Rx2_Buffer[0] == 0){
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
			}else{
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);						
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);					
			}
			break;
		case 5:
			Tx1_Buffer[0] = 0xB6;
			if(Rx2_Buffer[0] == 0){
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
			}else{
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);						
			}
			break;
		case 6:
			Tx1_Buffer[0] = 0xBE;
			if(Rx2_Buffer[0] == 0){
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
			}else{
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);						
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);						
			}
			break;
		case 7:
			Tx1_Buffer[0] = 0xE0;
			if(Rx2_Buffer[0] == 0){
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
			}else{
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);						
			}
			break;
		case 8:
			Tx1_Buffer[0] = 0xFE;
			if(Rx2_Buffer[0] == 0){
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
			}else{
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);					
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);							
			}
			break;
		case 9:
			Tx1_Buffer[0] = 0xE6;
			if(Rx2_Buffer[0] == 0){
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
			}else{
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);					
				I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);					
			}
			break;
		case 14:				//this is '#' for clear all buff
			FlushBoard();
			break;
		case 15://this is '*' for enter number
		  rand_func=rand()%3;
			switch(rand_func){
				case 0:
					EnterMain();
					break;
				case 1:
					EnterMain();
					break;
				case 2:
					EnterMain();
					break;
			}
		default:
			break;
		/*
		case 10:
			Tx1_Buffer[0] = 0xEE;
			if(Rx2_Buffer[0] == 0)
				{
					I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
				}
				else
				{
					I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);					
					I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);						
				}
			break;
		case 11:
			Tx1_Buffer[0] = 0x3E;
			if(Rx2_Buffer[0] == 0)
				{
					I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
				}
				else
				{
					I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);							
					I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);						
				}
			break;
		case 12:
			Tx1_Buffer[0] = 0x9C;
			if(Rx2_Buffer[0] == 0)
				{
					I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
				}
				else
				{
					I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);						
					I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);								
				}
			break;
		case 13:
			Tx1_Buffer[0] = 0x7A;
			if(Rx2_Buffer[0] == 0)
				{
					I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);
				}
				else
				{
					I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS2,Rx2_Buffer,BUFFER_SIZE2);						
					I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,1);									
				}
			break;
		*/
	}
}

HAL_StatusTypeDef HAL_IWDG_Init(IWDG_HandleTypeDef *hiwdg)
{
  uint32_t tickstart;

  /* Check the IWDG handle allocation */
  if(hiwdg == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_IWDG_ALL_INSTANCE(hiwdg->Instance));
  assert_param(IS_IWDG_PRESCALER(hiwdg->Init.Prescaler));
  assert_param(IS_IWDG_RELOAD(hiwdg->Init.Reload));

  /* Enable IWDG. LSI is turned on automaticaly */
  __HAL_IWDG_START(hiwdg);

  /* Enable write access to IWDG_PR and IWDG_RLR registers by writing 0x5555 in KR */
  IWDG_ENABLE_WRITE_ACCESS(hiwdg);

  /* Write to IWDG registers the Prescaler & Reload values to work with */
  hiwdg->Instance->PR = hiwdg->Init.Prescaler;
  hiwdg->Instance->RLR = hiwdg->Init.Reload;

  /* Check pending flag, if previous update not done, return timeout */
  tickstart = HAL_GetTick();

  /* Wait for register to be updated */
  while(hiwdg->Instance->SR != RESET)
  {
    if((HAL_GetTick() - tickstart ) > HAL_IWDG_DEFAULT_TIMEOUT)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Reload IWDG counter with value defined in the reload register */
  __HAL_IWDG_RELOAD_COUNTER(hiwdg);

  /* Return function status */
  return HAL_OK;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	flag1 = 1;
}

int fputc(int ch, FILE *f)
{ 
  uint8_t tmp[1]={0};
	tmp[0] = (uint8_t)ch;
	HAL_UART_Transmit(&huart1,tmp,1,10);	
	return ch;
}
/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
