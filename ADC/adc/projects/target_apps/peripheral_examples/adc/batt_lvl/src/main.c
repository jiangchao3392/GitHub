/**
 ****************************************************************************************
 *
 * @file main.c
 *
 * @brief Battery level example for DA14580/581 SDK
 *
 * Copyright (C) 2012. Dialog Semiconductor Ltd, unpublished work. This computer 
 * program includes Confidential, Proprietary Information and is a Trade Secret of 
 * Dialog Semiconductor Ltd.  All use, disclosure, and/or reproduction is prohibited 
 * unless authorized in writing. All Rights Reserved.
 *
 * <bluetooth.support@diasemi.com> and contributors.
 *
 ****************************************************************************************
 */
#include <stdio.h>

#include "global_io.h"
#include "common_uart.h"
#include "user_periph_setup.h"
#include "battery.h"
#include "gpio.h"
void system_init(void);
void batt_test(void);

void delay_us(uint16_t num);  
void delay_ms(uint16_t num);
void delay_s(uint16_t num);
/**
 ****************************************************************************************
 * @brief  Main routine of the battery level example
 * 
 ****************************************************************************************
 */
int main (void)
{
    system_init();
	  periph_init();
	 
	  GPIO_ConfigurePin(GPIO_PORT_1, GPIO_PIN_3, OUTPUT, PID_GPIO, false); //POWER_ON
	  GPIO_ConfigurePin(GPIO_PORT_2, GPIO_PIN_7, OUTPUT, PID_GPIO, false);  //5VCTL
	
	  GPIO_SetActive(GPIO_PORT_1, GPIO_PIN_3);
	  GPIO_SetActive(GPIO_PORT_2, GPIO_PIN_7);
	  
	  GPIO_ConfigurePin(GPIO_PORT_0, GPIO_PIN_1, INPUT, PID_ADC, false);   	 //PID_ADC
   
	batt_test();
	
    while(1)
	{
		delay_s(2);
		printf_byte_dec(battery_get_lvl(BEILIANG_1380mA));
    printf_string("V ");
	}
}

 /**
 ****************************************************************************************
 * @brief System Initiialization 
 *
 * 
 ****************************************************************************************
 */

void system_init(void)
{
    SetWord16(CLK_AMBA_REG, 0x00);                 // set clocks (hclk and pclk ) 16MHz
    SetWord16(SET_FREEZE_REG,FRZ_WDOG);            // stop watch dog    
    SetBits16(SYS_CTRL_REG,PAD_LATCH_EN,1);        // open pads
    SetBits16(SYS_CTRL_REG,DEBUGGER_ENABLE,1);     // open debugger
    SetBits16(PMU_CTRL_REG, PERIPH_SLEEP,0);       // exit peripheral power down
}

/**
 ****************************************************************************************
 * @brief Battery Level Indication  example function 
 * 
 ****************************************************************************************
 */
void batt_test(void)
{
    printf_string("\n\r\n\r");
    printf_string("*******************\n\r");
    printf_string("* 3V BATTERY TEST *\n\r");
    printf_string("*******************\n\r");

#if BATT_CR2032    
    printf_string("\n\rBattery type: ±¶Á¿1380mA");  
    printf_string("\n\rCurrent battery level (%): ");           
//    printf_byte_dec(battery_get_lvl(BATT_CR2032));
	  printf_byte_dec(battery_get_lvl(BEILIANG_1380mA));
    printf_string("% left");
#else
    printf_string("\n\rBattery type unknown");  
#endif
    printf_string("\n\rEnd of test\n\r");
}


void delay_us(uint16_t num)   //36us
{
  uint16_t i = 80*num;
	while(i--);
}
void delay_ms(uint16_t num)   
{
  uint16_t i,j;	
		for(j=0;j<num;j++)					 //
	{
		for(i=0;i<1000;i++);
	}
}

void delay_s(uint16_t num)   
{
  uint16_t i,j;	
		for(j=0;j<num;j++)					 //
	{
		for(i=0;i<1000;i++)
		{
			delay_ms(1);
		}
	}
}

