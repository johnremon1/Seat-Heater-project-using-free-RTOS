/*
 * ARM_ADC_DRIVER.h
 *
 *  Created on: Oct 9, 2024
 *      Author: johnr
 */

#ifndef ARM_ADC_DRIVER_H_
#define ARM_ADC_DRIVER_H_

#include "std_types.h"
#include "tm4c123gh6pm_registers.h"


/* the pins in case you do not know them
 *
 * AIN0  PE3 I Analog Analog-to-digital converter input 0.
 * AIN1  PE2 I Analog Analog-to-digital converter input 1.
 * AIN2  PE1 I Analog Analog-to-digital converter input 2.
 * AIN3  PE0 I Analog Analog-to-digital converter input 3.
 * AIN4  PD3 I Analog Analog-to-digital converter input 4.
 * AIN5  PD2 I Analog Analog-to-digital converter input 5.
 * AIN6  PD1 I Analog Analog-to-digital converter input 6.
 * AIN7  PD0 I Analog Analog-to-digital converter input 7.
 * AIN8  PE5 I Analog Analog-to-digital converter input 8.
 * AIN9  PE4 I Analog Analog-to-digital converter input 9.
 * AIN10 PB4 I Analog Analog-to-digital converter input 10.
 * AIN11 PB5 I Analog Analog-to-digital converter input 11
 *
 *
 * about that driver
 * that driver uses sample Sequencer 0 only and do
 */



/*********************************************************************************************************
 *                                   type definitions
 *********************************************************************************************************/

//this Enum is for the port name of the ADC pin
typedef enum{
    ADC_PORTB,
    ADC_PORTD,
    ADC_PORTE
}ADC_PORTID;


//this Enum is for the pin number of the adc pin
typedef enum{
    PE0  = 0x3
    ,PE1 = 0x2
    ,PE2 = 0x1
    ,PE3 = 0x0
    ,PE4 = 0X9
    ,PE5 = 0x8
    ,PD0 = 0x7
    ,PD1 = 0x6
    ,PD2 = 0x5
    ,PD3 = 0x4
    ,PB4 = 0xA
    ,PB5 = 0xB
}ADC_PIN_NAME;


typedef enum{
    ADC0,
    ADC1
}ADC_MODULE;


/********************************************************************************************************
 *                                          functions prototypes
 ********************************************************************************************************/


/************************************************************************************
* Service Name:
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Return value: None
* Description:
************************************************************************************/

void ADC_init(ADC_PORTID portnum ,ADC_PIN_NAME pinNumber ,ADC_MODULE ADC_module);


/************************************************************************************
* Service Name:
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Return value: None
* Description:
************************************************************************************/

uint16 ADC_u16ReadData(ADC_PORTID portnum ,ADC_PIN_NAME pinNumber ,ADC_MODULE ADC_module);



void ADC_startConversion(ADC_PORTID portnum ,ADC_PIN_NAME pinNumber ,ADC_MODULE ADC_module);



void ADC_interruptEnable(ADC_PORTID portnum ,ADC_PIN_NAME pinNumber ,ADC_MODULE ADC_module,uint8 priority);

void ADC0_SetCallBackFunction(void (*functionPtr)(uint16 return_value));

void ADC1_SetCallBackFunction(void (*functionPtr)(uint16 return_value));


#endif /* ARM_ADC_DRIVER_H_ */
