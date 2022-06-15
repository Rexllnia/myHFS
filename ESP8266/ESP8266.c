#include "ESP8266.h"
#include "stdlib.h"
#include "cstring"
void wifi_init()
{
	HAL_UART_Transmit(&huart2,(uint8_t*)AT_RST,strlen((char*)AT_RST),100);

	HAL_Delay(1000);
	HAL_UART_Transmit(&huart2,(uint8_t*)AT_CWMODE,strlen((char*)AT_CWMODE ),100);
//	my_printf("AT+CWMODE=2\r\n");
	HAL_Delay(1000);
//	my_printf();
	HAL_UART_Transmit(&huart2,(uint8_t*)AT_CWSAP,strlen((char*)AT_CWSAP),100);
	HAL_Delay(1000);
//	my_printf("AT+CIPMUX=1\r\n");
	HAL_UART_Transmit(&huart2,(uint8_t*)AT_CIPMUX,strlen((char*)AT_CIPMUX),100);
	HAL_Delay(1000);
//	my_printf("AT+CIPSERVER=1,80\r\n");
	HAL_UART_Transmit(&huart2,(uint8_t*)AT_CIPSERVER,strlen((char*)AT_CIPSERVER),100);

}

//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(huart);
//  /* NOTE: This function should not be modified, when the callback is needed,
//	
//           the HAL_UART_TxHalfCpltCallback could be implemented in the user file
//   */
//	if(huart->Instance==USART1){
//		HAL_UART_Receive_DMA(&huart1,(uint8_t *)&aRxBuffer1,1);
//	}
//}

int dtoh(int hex)
{
    int temp=0;
    int i=1;
    while(hex) 
    {
        
        temp+=i*(hex%10);
        hex=hex/10;
        i*=16;
    }
    return temp;
}
