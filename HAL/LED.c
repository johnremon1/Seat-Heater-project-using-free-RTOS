/*
 * LED.c
 *
 *  Created on: Oct 9, 2024
 *      Author: johnr
 */

#include "LED.h"
void LED_init(GPIO_PORT_NAME portName , uint8 pinNumber)
{
    GPIO_SetPinDirection(portName, pinNumber, OUTPUT);
}

void LED_on(GPIO_PORT_NAME portName , uint8 pinNumber)
{
    GPIO_WritePin(portName, pinNumber, HIGH );
}

void LED_off(GPIO_PORT_NAME portName , uint8 pinNumber)
{
    GPIO_WritePin(portName, pinNumber, LOW);
}

void LED_toggle(GPIO_PORT_NAME portName , uint8 pinNumber)
{
    GPIO_TogglePin(portName, pinNumber);
}
