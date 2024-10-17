/*
 * BUTTON.c
 *
 *  Created on: Oct 9, 2024
 *      Author: johnr
 */

#include "BUTTON.h"

void BUTTON_init(GPIO_PORT_NAME portName , uint8 pinNumber)
{
    GPIO_SetPinDirection(portName, pinNumber, INPUT);
}

void BUTTON_pullUpEnable(GPIO_PORT_NAME portName , uint8 pinNumber , GPIO_ENABLE_STATUS status)
{
    if (status == ENABLE)
    {
        GPIO_PinPullUpEnable(portName, pinNumber, ENABLE);
    }
    else if (status == DISABLE)
    {
        GPIO_PinPullUpEnable(portName, pinNumber, DISABLE);
    }
}


void BUTTON_pullDownEnable(GPIO_PORT_NAME portName , uint8 pinNumber , GPIO_ENABLE_STATUS status)
{
    if (status == ENABLE)
    {
        GPIO_PinPullDownEnable(portName, pinNumber, ENABLE);
    }
    else if (status == DISABLE)
    {
        GPIO_PinPullDownEnable(portName, pinNumber, DISABLE);
    }
}

void BUTTON_interruptEnable(GPIO_PORT_NAME portName , uint8 pinNumber , GPIO_ENABLE_STATUS status , GPIO_INTERRUPT_EVENT event , uint8 priority )
{
    GPIO_InterruptPinEnable(portName, pinNumber, status , event , priority);
}



void BUTTON_SetCallBackFunction ( void(*functionPtr)(uint8 Seat_id))
{
   GPIO_PortF_SetCallBackFuntion(functionPtr);
}




