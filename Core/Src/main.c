/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "fatfs.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdlib.h"
#include "stdarg.h"
#include <stdio.h>
#include "myHFS_file.h"
#include "myHFS_html.h"
#include "myHFS_http.h"
#include "string.h"
#include "SDdriver.h"
#include "ESP8266.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define debug 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t Uart1_Rx_Cnt=0;
uint8_t aRxBuffer1=0;
char Uart1_RxBuffer[600]="";
uint16_t Uart2_Rx_Cnt=0;
char Uart2_RxBuffer[600]="";

FATFS fs;
FIL file;
uint8_t res=0;
UINT Br,Bw;
char path[4]="0:";
char *divide_line;
char List[200];
char success[]="Ok!\r\n";
char error[]="error!\r\n";
char mount[]="mount Ok! \r\n";
char open[]="τݾӑղߪ! \r\n";
char file_name[40];
char *p1, *p2, *p3;
char buf[2000];
	FILINFO ptr[10];
	DIR dir;
	int i=0;
char cur_state=0,next_state=0;
//char GET[]={0x47,0x45,0x54,0x20,0x2f};
//char HTTP[]={0x20,0x48,0x54,0x54,0x2f};
char *rear,*front;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_Delay(uint32_t Delay)
{
	uint16_t i=0;
	while(Delay--)
	{
		i=12000;
		while(i--);
	}
}
void vprint(const char *fmt, va_list argp) {
	char string[200];
	if (0 < vsprintf(string, fmt, argp)) // build string
			{
		HAL_UART_Transmit(&huart2, (uint8_t*) string, strlen(string),100); // send message via UART
		
	}
}
void my_printf(const char *fmt, ...) // custom printf() function
{
	va_list argp;
	va_start(argp, fmt);
	vprint(fmt, argp);
	va_end(argp);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
	uint8_t flag=0;
	char msg[900];
	uint8_t ReadBuffer[1000];
	int i=0;
	int size=0; 


  UNUSED(htim);
	if(cur_state==0)
	{
				#ifdef debug
				my_printf("cur_state=%d\r\n",cur_state);
				#endif 

				f_opendir (&dir,"FILE");
		f_readdir (&dir, &ptr[0]);
    while (ptr[i].fname[0]!=0)
    {
					i++;
					 
				
				f_readdir (&dir, &ptr[i]);	
			#ifdef debug
			my_printf("%d\r\n",ptr[i].fsize);
			#endif
    }
    f_closedir(&dir);
		
		

		//write
			f_mkdir ("FILE");
		
		
			

		

		get_dir(List);
		#ifdef debug
		my_printf("%s\r\n",List);
		#endif
			p3=List;
		while(f_open(&file,"FILE/hello.htm",FA_READ)!=FR_OK);
		f_read (&file, buf, f_size(&file),&Br);
    f_close(&file);


    //删除<!--myHFSdir.--><!--/myHFSdir.-->内容
    p1 = strstr(buf, "<!--myHFSdir.-->");
    p1 = p1 + 16;
    while (p1 != strstr(buf, "<!--/myHFSdir.-->"))
    {
        strdelete(p1);
    }
    //printf("%s", buf);

    //圿<!--myHFSdir.-->后面插入
    p1 = strstr(buf, "<!--myHFSdir.-->");
    p1 = p1 + 15;
    while (*p3 != '\0')
    {
        insert(p1++, *p3++);
    }
    //删除末尾乱码
    p1 = strstr(buf, "</html>");
    p1 += 7;
    while (*p1 != '\0')
    {
        strdelete(p1);
    }
		f_unlink ("FILE/hello.htm");	
		while(f_open(&file,"FILE/hello.htm",FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK);
		f_write(&file,buf,strlen(buf),&Bw);

    f_close(&file);
//					strcpy(msg,"HTTP/1.1 200 OK\r\n\r\n");
//		HAL_UART_Transmit(&huart2,msg,strlen(msg),100);
////					char temp_buf[200];
////					sprintf(temp_buf,"AT+CIPSEND=0,%d\r\n",strlen(msg));
////					HAL_UART_Transmit(&huart2,temp_buf,strlen(temp_buf),100);
//		
//		my_printf("HTTP/1.1 200 OK\r\n");
//		my_printf("AT+CIPSEND=0,18\r\n");
		next_state=1;
	}
	if(cur_state==1)
	{
				#ifdef debug
				my_printf("cur_state=%d\r\n",cur_state);
				#endif 
		f_open(&file,"FILE/log.txt",FA_OPEN_ALWAYS|FA_WRITE);
		f_lseek(&file, f_size(&file));
		f_write(&file,Uart1_RxBuffer,strlen(Uart1_RxBuffer),&Bw);
    f_close(&file);
		my_printf("HTTP/1.1 200 OK\r\n");
		next_state=2;
	}
	if(cur_state==2)
	{
				#ifdef debug
				my_printf("cur_state=%d\r\n",cur_state);
				#endif 
		if(strcmp(file_name,"")==0)
		{
			strcpy(file_name,"HELLO.HTM");
			flag=0;
			
		}
		else
		{
			flag=1;
		}
		for(i=0;ptr[i].fname[0]!=0;i++)
		{
			if(strcmp(file_name,ptr[i].fname)==0)
			{
					char str[100]="FILE/";

					size=ptr[i].fsize;
					


					strcpy(msg,"");
				if(flag==1)
				{
					sned_header(msg,file_name,size);
				}
				else
				{
					sprintf(msg,"HTTP/1.1 200 OK\r\nContent-Length:%d\r\nAccept-Ranges:bytes\r\nContent-Type:text/html\r\n\r\n",size);
					

				}
					my_printf("AT+CIPSEND=0,%d\r\n",strlen(msg));
					HAL_Delay(100);
					my_printf("%s",msg);

					
					strcpy(ReadBuffer,"");	
					f_open(&file,strcat(str,file_name),FA_READ);
					f_read (&file, ReadBuffer, sizeof(ReadBuffer),&Br);
					my_printf("AT+CIPSEND=0,%d\r\n",Br);
					HAL_Delay(100);
					HAL_UART_Transmit(&huart2,ReadBuffer,sizeof(ReadBuffer),100);
				while(Br==sizeof(ReadBuffer))
				{
						f_read (&file, ReadBuffer, sizeof(ReadBuffer),&Br);
						my_printf("AT+CIPSEND=0,%d\r\n",Br);
						HAL_Delay(100);
						HAL_UART_Transmit(&huart2,ReadBuffer,Br,100);
			
				}
				strcpy(ReadBuffer,"");	
					f_close(&file);
				

					
					
					
				break;
			}
		}
		next_state=3;
		
				
				
		
	}
	if(cur_state==3)
	{
				#ifdef debug
				my_printf("cur_state=%d\r\n",cur_state);
				#endif 
		next_state=4;
	}
	if(cur_state==4)
	{
						#ifdef debug
				my_printf("cur_state=%d\r\n",cur_state);
				#endif 

		

		next_state=5;
	}
	if(cur_state==5)
	{
						#ifdef debug
				my_printf("cur_state=%d\r\n",cur_state);
				#endif 

		next_state=6;
	}
	cur_state=next_state;
	if(cur_state==6)
	{
		#ifdef debug
		my_printf("cur_state=%d\r\n",cur_state);
		#endif 
		cur_state=0;
		HAL_TIM_Base_Stop_IT(&htim1);
	}
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
   */
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	char *p;
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function should not be modified, when the callback is needed,
	
           the HAL_UART_RxCpltCallback could be implemented in the user file
   */
		if(huart->Instance==USART2){
		Uart1_RxBuffer[Uart1_Rx_Cnt++]=aRxBuffer1;
		Uart2_RxBuffer[Uart2_Rx_Cnt++]=aRxBuffer1;
			if(strstr(p = strstr(Uart2_RxBuffer, "Content-Type: application/octet-stream"), "------WebKitFormBoundary") != NULL)
			{
				while(f_open(&file,"FILE/tmp.txt",FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK);
				f_write(&file,Uart2_RxBuffer,strlen(Uart2_RxBuffer),&Bw);
				f_close(&file);
				Uart2_Rx_Cnt=0;
			}
//			if((strstr(Uart1_RxBuffer, "POST") != NULL) && Uart1_Rx_Cnt<1000)
//			{
//				while(f_open(&file,"FILE/tmp.txt",FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK);
//				f_write(&file,Uart1_RxBuffer,strlen(Uart1_RxBuffer),&Bw);
//				f_close(&file);
//				strcpy(Uart1_RxBuffer,"");
//				Uart1_Rx_Cnt=0;
//			}
//	if((Uart1_RxBuffer[Uart1_Rx_Cnt-1]==0x0A)&&(Uart1_RxBuffer[Uart1_Rx_Cnt-2]==0x0D)&&(Uart1_RxBuffer[Uart1_Rx_Cnt-3])==0x2D&&(Uart1_RxBuffer[Uart1_Rx_Cnt-4])==0x2D)
//	{
//					while(f_open(&file,"FILE/tmp.txt",FA_OPEN_ALWAYS|FA_WRITE)!=FR_OK);
//					f_write(&file,Uart1_RxBuffer,strlen(Uart1_RxBuffer),&Bw);
//					f_close(&file);
//					Uart1_Rx_Cnt=0;
//	}

	if((Uart1_RxBuffer[Uart1_Rx_Cnt-1]==0x0A)&&(Uart1_RxBuffer[Uart1_Rx_Cnt-2]==0x0D)&&(Uart1_RxBuffer[Uart1_Rx_Cnt-3])==0x0A&&(Uart1_RxBuffer[Uart1_Rx_Cnt-4])==0x0D)
	{   
		if(strstr(Uart1_RxBuffer, "POST") != NULL)
		{
			divide_line=strstr(Uart1_RxBuffer,"boundary=----");
			divide_line+=strlen("boundary=----");
			divide_line=strtok(divide_line,"\r\n");

//				strcpy(divide_line,"");
		}

//		HAL_UART_Transmit(&huart2,(uint8_t *) Uart1_RxBuffer,strlen(Uart1_RxBuffer),100);
			if(strstr(Uart1_RxBuffer, "GET") != NULL)//在a中查找b，如果存在，
			{
//				HAL_UART_Transmit(&huart2,Uart1_RxBuffer,strlen((char*)Uart1_RxBuffer),100);
				strcpy(file_name,"");
				strcut(Uart1_RxBuffer,"GET /"," HTTP/",file_name);

				
//				my_printf("%s\r\n",file_name);
				cur_state=0;
				HAL_TIM_Base_Start_IT(&htim1);
				
			}
			
		Uart1_Rx_Cnt=0;
			

	}
	HAL_UART_Receive_IT(&huart2,(uint8_t *)&aRxBuffer1,1);
}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  MX_FATFS_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	#ifdef debug
my_printf("START");
#endif
	SD_init();

	res=f_mount(&fs,"0:",0);
	#ifdef debug
	if(res!=FR_OK){
		HAL_UART_Transmit(&huart2,(uint8_t *) &error,sizeof(error),100);
	}else{
		HAL_UART_Transmit(&huart2,(uint8_t *) &mount,sizeof(mount),100);
	}
	HAL_Delay(1000);
	#endif
		
	

//	f_chmod ("FILE/hello.html",AM_ARC,77);

//			HAL_UART_Transmit(&huart2,ReadBuffer,strlen((char*)ReadBuffer),100);
	 wifi_init();
		HAL_UART_Receive_IT(&huart2,(uint8_t *)&aRxBuffer1,1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

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

