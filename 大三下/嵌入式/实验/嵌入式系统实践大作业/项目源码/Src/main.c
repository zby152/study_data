#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "stdlib.h"

/* USER CODE BEGIN Includes */
#include "zlg7290.h"
#include "stdio.h"
#include "stm32f4xx_hal_iwdg.h"		//看门狗,后面均使用独立看门狗IWDG
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
#define HAL_IWDG_DEFAULT_TIMEOUT            ((uint32_t)1000)    
#define BUFFER_SIZE1              (countof(Tx1_Buffer))
#define BUFFER_SIZE2              (countof(Rx2_Buffer))
#define countof(a) (sizeof(a) / sizeof(*(a)))

typedef struct ValueAndBack{//数据及备份，检验和采用与0xff异或
	uint8_t Odata;
	uint8_t checksum;
	uint32_t blank1;
	uint8_t back1;
	uint8_t checksum1;
	uint32_t blank2;
	uint8_t back2;
	uint8_t checksum2;
}Data;

uint8_t flag;						//数位板输入转为对应flag	  1——
uint8_t flag1 = 0;					//HAL回调，理解为时钟	  	6|	 |2
uint8_t Rx2_Buffer[8]={0};			//8个灯的显示————————————>   7——— 
uint8_t Tx1_Buffer[8]={0};			//						   5|	|3
uint8_t Rx1_Buffer[1]={0};			//按键输入					 4———
IWDG_HandleTypeDef *hiwdg;

void SystemClock_Config(void);

void switch_key(void);				//专门用于将键盘转为flag
void switch_flag(void);				//专门用于处理flag，进行显示或处理
void BeeWater(void);				//用于报警和开启水阀
int ReadNumber(void);				//用于将缓冲区中数据转换为十进制整数
uint16_t _pow(uint8_t a, uint8_t b);//阶乘计算
uint8_t CheckData(void);			//检查温度Data的校验
uint8_t Decode(uint8_t x);			//用于将数码管Rx2中的数据转回数字,和switch_flag和switch_key可能合并？
void FaultDeal(void);				//校验全错误的处理
void Init(void);					//整体初始化，不包括看门狗
void TempUpdate(uint8_t t);	        //更新或初始化温度Data结构体
void FlushBoard(void);				//刷新Rx2缓冲，将'#'功能独立
void EnterSleep(void);				//进入睡眠模式
void EnterMain(void);				//单独实现'*'号功能，用于合到switch_flag
void IWDG_Init(void);				//看门狗初始化

//该区域全局变量都会被0初始化
__attribute__((section(".uninit"),zero_init)) Data Temperature;		//全局温度变量
__attribute__((section(".uninit"),zero_init)) uint16_t HotStart;	//是否热启动
__attribute__((section(".uninit"),zero_init)) uint32_t DelayTime;	//延迟启动时间
__attribute__((section(".uninit"),zero_init)) uint8_t InputLen;		//用于限制输入个数在两位数之内
__attribute__((section(".uninit"),zero_init)) uint32_t LastTime;	//用于超时处理，记录上一次get时间
__attribute__((section(".uninit"),zero_init)) uint8_t id;		    //函数执行顺序
__attribute__((section(".uninit"),zero_init)) uint8_t first_num;    //读取的第一位数字
__attribute__((section(".uninit"),zero_init)) uint8_t second_num;   //读取的第二位数字
__attribute__((section(".uninit"),zero_init)) uint8_t num_no;       //读取的数字序号

int main(void)
{
	//HAL_Delay(20);
	//冷热启动
	//printf("HotStart=%d\r\n",HotStart);
	if(HotStart != 0x4514){//冷启动初始化
		//启动与开始之间的休眠时间		delay(80~100)	//done
		DelayTime = rand() % 21 + 80;
		HAL_Delay(DelayTime);
		Init();
		printf("Cold Start!!!!HotStart=%d\r\n",HotStart);
		HotStart = 0x4514;
		TempUpdate(25);
	}else{//热启动
		printf("\r\nhotStart,HoyStart=%d\r\n",HotStart);
		MX_GPIO_Init();
		int yes = CheckData();
		if(yes == 1){
			TempUpdate(Temperature.Odata - 1);
		}else{
			FaultDeal();
		}
	}
	printf("\n\r-------------------------------------------------\r\n");
	printf("\n\r ---------------Fire watering System--------------\r\n");	
	//watch_dog		done
	IWDG_Init();		//hiwdg变量无需定义，已经在iwdg.c中定义全局变量
	//__HAL_IWDG_START(&hiwdg);
	
	while (1)
	{
		MX_GPIO_Init();
		//__HAL_IWDG_RELOAD_COUNTER(hiwdg);
		if(flag1 == 1){		//证明有按键进来，所以超时判断不应该在这里
			flag1 = 0;
			//喂狗
			__HAL_IWDG_RELOAD_COUNTER(hiwdg);
			//读输入板
			I2C_ZLG7290_Read(&hi2c1,0x71,0x01,Rx1_Buffer,1);
			switch_key();
			Rx2_Buffer[1]=first_num;
			//I2C_ZLG7290_Read(&hi2c1,0x71,0x10,Rx2_Buffer,8);
			//来输入了，记录时间
			//LastTime = HAL_GetTick();
			//输入检查
			switch_flag();
			I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1+2,Tx1_Buffer+2,6);
			HAL_Delay(20);
		}else{		//睡眠躲避干扰
			printf("HAL_GetTICK:----->%d\r\n",HAL_GetTick());
			FlushBoard();
			EnterSleep();
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

//总初始化
void Init(void){
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_USART1_UART_Init();
}

//睡觉模式
void EnterSleep(void){
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

//用于数据赋值错误
void FaultDeal(void){
	printf("this is error while checking data\r");
	//待定，肯定是不能长时间蜂鸣
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);
	HAL_Delay(20);
	FlushBoard();
}

//用于清空输入缓冲
void FlushBoard(void){
	id = 0;
	Tx1_Buffer[0] = 0x00;
	I2C_ZLG7290_Write(&hi2c1,0x70,ZLG_WRITE_ADDRESS1,Tx1_Buffer,8);
	InputLen = 0;
}

//'*'号回车
void EnterMain(void){
		uint8_t temp1 = ReadNumber();				//读取两次取个平均值
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
			FaultDeal();//需要调用'#'功能并bee一下提示，清除并重新输入
		}else{
			printf("not so hot, I think there has no fire\r");
		}
		FlushBoard();	//输入0个数,超过2位数,回车之后，都会清空
}

//数码管解码,将Rx2_buffer转换为输入的数字
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
		default://ABCDEF会被当作0处理
			return 0;
	}
}

//读取数码管的8个转换成十进制温度
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

//用于a的b次方
uint16_t _pow(uint8_t a, uint8_t b){
	uint16_t result = 1;
	while(b > 0){
		result *= a;
		b--;
	}
	return result;
}

//检查数据合法性，返回-错0，对1
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

//用于报警和开启水阀
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

//用于更新或初始化'温度'结构
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
	if(id != 0) {
		FaultDeal();
	}else{
		id = 1;
	}
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
		/*					//温度输入10进制，将字母ban掉
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
		case 0x02://#		//'#'用于清空，'*'用于回车
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
	if(id != 1){
		FaultDeal();
	}else{
		id = 0;
	}
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
		  rand_func=rand()%3;  //随机乱序执行躲避攻击
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
	if(num_no==0){
		first_num=Tx1_Buffer[0];
		num_no=1;
	}
	else
	{
		num_no=0;
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