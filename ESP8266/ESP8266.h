#ifndef __ESP8266_H
#define __ESP8266_H
#include "main.h"
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern uint16_t Uart1_Rx_Cnt;
extern uint8_t aRxBuffer1;
extern char Uart1_RxBuffer[600];
static char *AT_RST = "AT+RST\r\n";	       
static char *AT_CWMODE = "AT+CWMODE=2\r\n";	        //өѯ٤طģʽ
static char *AT_CWLIF = "AT+CWLIF\r\n";
//AT+CIPSTART=2,"TCP","192.168.1.42",3333
static char *AT_CWSAP = "AT+CWSAP=\"143_[192.168.4.1]\",\"Cc123456\",6,4\r\n";
//AT+CIPSEND=2,8
static char *AT_CIPMUX= "AT+CIPMUX=1\r\n";
static char *AT_CIPSERVER= "AT+CIPSERVER=1,80\r\n";
//static uint8_t *AT_CWMODE= = "AT+CWMODE=3\r\n";
static char AT_CWJAP[] = "AT+CWJAP=\"";
//AT+CIPMUX=1

//AT+CIFSR
extern void my_printf(const char *fmt, ...);
extern uint8_t flag;
void wifi_init();
#endif
