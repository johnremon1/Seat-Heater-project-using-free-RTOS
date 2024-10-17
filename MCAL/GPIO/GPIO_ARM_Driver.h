/*
 * GPIO_ARM_Driver.h
 *
 *  Created on: Jul 11, 2024
 *      Author: johnr
 */


#ifndef GPIO_ARM_DRIVER_H_
#define GPIO_ARM_DRIVER_H_

#include "project_cfg.h"
#include "tm4c123gh6pm_registers.h"




/*************************************************************************************************
 *                                       Types Declaration
 ***************************************************************************************************/
typedef enum{

    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF,
}GPIO_PORT_NAME;


typedef enum{
   INPUT,
   OUTPUT
}GPIO_PIN_DIRECTION;

typedef enum{
    LOW,
    HIGH,
}GPIO_PIN_LOGIC;


typedef enum{
    DISABLE,
    ENABLE
}GPIO_ENABLE_STATUS;

typedef enum{
    RISING_EDGE,
    FALLING_EDGE,
    HIGH_LEVEL,
    LOW_LEVEL,
    BOTH_EDGES
}GPIO_INTERRUPT_EVENT ;


#define NVIC_PRIX_INTD_MASK       0xE0000000  // Interrupt 115 Priority Mask
#define NVIC_PRIX_INTC_MASK       0x00E00000  // Interrupt 114 Priority Mask
#define NVIC_PRIX_INTB_MASK       0x0000E000  // Interrupt 113 Priority Mask
#define NVIC_PRIX_INTA_MASK       0x000000E0  // Interrupt 112 Priority Mask
#define NVIC_PRIX_INTD_POSITION       29
#define NVIC_PRIX_INTC_POSITION       21
#define NVIC_PRIX_INTB_POSITION       13
#define NVIC_PRIX_INTA_POSITION       5

#define NVIC_PORTA_ENABLE_BIT_POSITION 0
#define NVIC_PORTB_ENABLE_BIT_POSITION 1
#define NVIC_PORTC_ENABLE_BIT_POSITION 2
#define NVIC_PORTD_ENABLE_BIT_POSITION 3
#define NVIC_PORTE_ENABLE_BIT_POSITION 4
#define NVIC_PORTF_ENABLE_BIT_POSITION 30


/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")

/*************************************************************************************************
 *                                       FUNCTIONS PROTOTYPE
 ***************************************************************************************************/

/*
 * function description :
 * this function is for setting the direction of the pin
 * take care of using the PF0 and PD7  as these pins are connected to critical like nmi
 * the PC0 & PC1 & PC2 & PC3 can not be used as they are connected to the JTAG peripheral and can cause the board to damage
 * you can use the pin direction to be INPUT, OUTPUT
 * if you used pin number more than 7 or port other than the ports we define of port that has number more than 5 the function will go into while(1) and can only be found in a debug session
 */
void GPIO_SetPinDirection(GPIO_PORT_NAME port ,uint8 pin_number ,GPIO_PIN_DIRECTION pin_direction );



/*
 * this port is for writing on a specific pin
 * if you tried to write on a input pin the function will enter a while(1) loop and only can be configured using a debug session
 * if you entered a wrong port or pin number more than 7 the function will go into a while(1) loop and will only csn be found in a debug session
 */
void GPIO_WritePin(GPIO_PORT_NAME port_name , uint8 pin_number , GPIO_PIN_LOGIC pin_logic);



/*
 * this function is for returning the the logic on the selected pin
 * if you tried to read from an output pin the function will enter a while(1) loop and only will be detected throw a debug session
 * this function returns a uint8 or can be defined as unsigned char and 8 bytes
 */
uint8 GPIO_ReadPin(GPIO_PORT_NAME port_name ,uint8 pin_number);


/*
 * this function toggle the logic on the pin
 * if you tried to toggle an input pin the function will go into a while(1) and only can be found by a debug session
 * if you tried to enter a wrong port name or wrong pin number the function will enter a while(1) loop and only can be found by a debug session
 */
void GPIO_TogglePin(GPIO_PORT_NAME port ,uint8 pin_number);




/*
 * this function if for enabling OR disabling the pull UP on a pin
 * the status variable should be ENABLE or DIABLE
 * if you tried to enable the pull up on a OUTPUT pin the function will go into a while(1) loop and will only be found during a debug session
 * PULL UP means that the default on the pin is HIGH until you press the button
 * if the button is pressed then the logic on the pin will be LOW
 */
void GPIO_PinPullUpEnable(GPIO_PORT_NAME port_name ,uint8 pin_number ,GPIO_ENABLE_STATUS status);


/*
 * this function if for enabling OR disabling the pull DOWN on a pin
 * the status variable should be ENABLE or DIABLE
 * if you tried to enable the pull up on a OUTPUT pin the function will go into a while(1) loop and will only be found during a debug session
 * PULL DOWN means that the default on the pin is LOW until you press the button
 * if the button is pressed then the logic on the pin will be HIGH
 */
void GPIO_PinPullDownEnable(GPIO_PORT_NAME port_name , uint8 pin_number ,GPIO_ENABLE_STATUS status);


/*
 * this enables or disble the interrupt from the pin on the gpio
 * take care as the interrupt are on the port not on the pin
 * the edge or the level is the only thing that applied on the pin
 * you need to go and change the name of the handler in the start up code to
 */
void  GPIO_InterruptPinEnable(GPIO_PORT_NAME port_name ,uint8 pin_number ,GPIO_ENABLE_STATUS status ,GPIO_INTERRUPT_EVENT event ,uint8 priority);


void GPIO_PortF_SetCallBackFuntion(  void(*functionHandler)(uint8 value)  );

#endif /* GPIO_ARM_DRIVER_H_ */
