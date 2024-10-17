/*
 * LED.h
 *
 *  Created on: Oct 9, 2024
 *      Author: johnr
 */

#ifndef LED_H_
#define LED_H_

#include "project_cfg.h"
#include "GPIO_ARM_Driver.h"

/***************************************************************************************************
 *                                               functions prototypes
 ***************************************************************************************************/

void LED_init(GPIO_PORT_NAME portName , uint8 pinNumber);

void LED_on(GPIO_PORT_NAME portName , uint8 pinNumber);

void LED_off(GPIO_PORT_NAME portName , uint8 pinNumber);

void LED_toggle(GPIO_PORT_NAME portName , uint8 pinNumber);


#endif /* LED_H_ */
