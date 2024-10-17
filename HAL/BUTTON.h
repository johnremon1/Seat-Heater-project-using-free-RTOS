/*
 * BUTTON.h
 *
 *  Created on: Oct 9, 2024
 *      Author: johnr
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "project_cfg.h"
#include "GPIO_ARM_Driver.h"

/***************************************************************************************************
 *                                               functions prototypes
 ***************************************************************************************************/

#define BUTTON_PRESSED              (LOGIC_HIGH)
#define BUTTON_NOT_PRESSED          (LOGIC_LOW)



void BUTTON_init(GPIO_PORT_NAME portName , uint8 pinNumber);

void BUTTON_pullUpEnable(GPIO_PORT_NAME portName , uint8 pinNumber , GPIO_ENABLE_STATUS status);

void BUTTON_pullDownEnable(GPIO_PORT_NAME portName , uint8 pinNumber , GPIO_ENABLE_STATUS status);

void BUTTON_interruptEnable(GPIO_PORT_NAME portName , uint8 pinNumber , GPIO_ENABLE_STATUS status , GPIO_INTERRUPT_EVENT event , uint8 priority );

void BUTTON_SetCallBackFunction ( void(*functionPtr)(uint8 Seat_id));

#endif /* BUTTON_H_ */
