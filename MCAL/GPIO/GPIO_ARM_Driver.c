/*
 * Gpio_ARM_Driver.c
 *
 *  Created on: Jul 3, 2024
 *      Author: john
 */


#include "GPIO_ARM_Driver.h"


static void(*PORTF_CallBack_ptr)(uint8 value) = NULL_PTR ;



void GPIO_SetPinDirection(GPIO_PORT_NAME port ,uint8 pin_number ,GPIO_PIN_DIRECTION pin_direction )
{
    if (port > PORTF || pin_number > 7 )
    {
        while(1);// be careful you enter a wrong port or wrong pin
    }


    switch (port)
    {
    case PORTA :

        SYSCTL_RCGCGPIO_REG |= 0x01;//first we must open the clock for port A and that is done by the GPIOSCG register
         while(!(SYSCTL_PRGPIO_REG & 0x01));

        GPIO_PORTA_AMSEL_REG &= ~(1<<pin_number);      /* Disable Analog on the pin */

        GPIO_PORTA_AFSEL_REG &= ~(1<<pin_number);      /* Disable alternative function on the pin */
        GPIO_PORTA_DEN_REG   |= (1<<pin_number);       /* Enable Digital I/O on the pin */


        GPIO_PORTA_PCTL_REG  &= ~(15<<(pin_number*4)) ;  /* Clear PMCx bits for the pin to use it as GPIO pin see the register for explanation  */


        if (pin_direction == OUTPUT)
        {
            GPIO_PORTA_DIR_REG   |= (1<<pin_number); /* Configure THE PIN as OUTPUT pin */

        }else if (pin_direction == INPUT)
        {

            GPIO_PORTA_DIR_REG   &= ~(1<<pin_number);      /* Configure PIN as INPUT pin */
        }

        else {
            while (1);
        }

        break ;
    case PORTB:
        SYSCTL_RCGCGPIO_REG |= 0x02;//first we must open the click for port B and that is done by the GPIOSCG register
        while(!(SYSCTL_PRGPIO_REG & 0x02));// this is for waiting the clock to be activated for the the port

        GPIO_PORTB_AMSEL_REG &= ~(1<<pin_number);      /* Disable Analog on the pin */
        GPIO_PORTB_AFSEL_REG &= ~(1<<pin_number);      /* Disable alternative function on the pin */
        GPIO_PORTB_DEN_REG   |= (1<<pin_number);       /* Enable Digital I/O on the pin */
        GPIO_PORTB_PCTL_REG  &= ~(15<<(pin_number*4));   /* Clear PMCx bits for the pin to use it as GPIO pin see the register for explanation  */

        if (pin_direction == OUTPUT)
        {
            GPIO_PORTB_DIR_REG   |= (1<<pin_number); /* Configure THE PIN as OUTPUT pin */

        }else if (pin_direction == INPUT)
        {

            GPIO_PORTB_DIR_REG   &= ~(1<<pin_number);      /* Configure PIN as INPUT pin */
        }

        else {
            while (1);
        }

        break ;
    case PORTC :
        SYSCTL_RCGCGPIO_REG |= 0x04;//first we must open the click for port C and that is done by the GPIOSCG register
        while(!(SYSCTL_PRGPIO_REG & 0x04));// this is for waiting the clock to be activated for the the port
        if ( (pin_number == 0) || (pin_number == 1) || (pin_number == 2) || (pin_number == 3) )
        {
            while (1); //remove this condition if you are knowing what you are doing as these three pins are connected to critical  peripheral named the JTAG and doing any thing wrong to it will cause the board to damage
        }

        GPIO_PORTC_AMSEL_REG &= ~(1<<pin_number);      /* Disable Analog on the pin */
        GPIO_PORTC_AFSEL_REG &= ~(1<<pin_number);      /* Disable alternative function on the pin */
        GPIO_PORTC_DEN_REG   |= (1<<pin_number);       /* Enable Digital I/O on the pin */
        GPIO_PORTC_PCTL_REG  &= ~(15<<(pin_number*4)) ;  /* Clear PMCx bits for the pin to use it as GPIO pin see the register for explanation  */

        if (pin_direction == OUTPUT)
        {
            GPIO_PORTC_DIR_REG   |= (1<<pin_number); /* Configure THE PIN as OUTPUT pin */

        }else if (pin_direction == INPUT)
        {

            GPIO_PORTC_DIR_REG   &= ~(1<<pin_number);      /* Configure PIN as INPUT pin */
        }

        else {
            while (1);
        }

        break ;
    case PORTD :
        SYSCTL_RCGCGPIO_REG |= 0x08;//first we must open the click for port D and that is done by the GPIOSCG register
        while(!(SYSCTL_PRGPIO_REG & 0x08));// this is for waiting the clock to be activated for the the port
        if (pin_number == 7)
        {
            GPIO_PORTD_LOCK_REG = 0x4C4F434B ;
            GPIO_PORTD_CR_REG |= 0x80; //take care of using that pin as it IS connected to critical peripherals
        }

        GPIO_PORTD_AMSEL_REG &= ~(1<<pin_number);      /* Disable Analog on the pin */
        GPIO_PORTD_AFSEL_REG &= ~(1<<pin_number);      /* Disable alternative function on the pin */
        GPIO_PORTD_DEN_REG   |= (1<<pin_number);       /* Enable Digital I/O on the pin */
        GPIO_PORTD_PCTL_REG  &= ~(15<<(pin_number*4));   /* Clear PMCx bits for the pin to use it as GPIO pin see the register for explanation  */

        if (pin_direction == OUTPUT)
        {
            GPIO_PORTD_DIR_REG   |= (1<<pin_number); /* Configure THE PIN as OUTPUT pin */

        }else if (pin_direction == INPUT)
        {

            GPIO_PORTD_DIR_REG   &= ~(1<<pin_number);      /* Configure PIN as INPUT pin */
        }

        else {
            while (1);
        }

        break ;
    case PORTE :

        if (pin_number >5)
        {
            while(1); // be careful as PORTE only has 5 pins only and you choose pin more than 4
        }

        SYSCTL_RCGCGPIO_REG |= 0x10;//first we must open the click for port a and that is done by the GPIOSCG register
        while(!(SYSCTL_PRGPIO_REG & 0x10));// this is for waiting the clock to be activated for the the port


        GPIO_PORTE_AMSEL_REG &= ~(1<<pin_number);      /* Disable Analog on the pin */
        GPIO_PORTE_AFSEL_REG &= ~(1<<pin_number);      /* Disable alternative function on the pin */
        GPIO_PORTE_DEN_REG   |= (1<<pin_number);       /* Enable Digital I/O on the pin */
        GPIO_PORTE_PCTL_REG  &= ~(15<<(pin_number*4));   /* Clear PMCx bits for the pin to use it as GPIO pin see the register for explanation  */

        if (pin_direction == OUTPUT)
        {
            GPIO_PORTE_DIR_REG   |= (1<<pin_number); /* Configure THE PIN as OUTPUT pin */

        }else if (pin_direction == INPUT)
        {

            GPIO_PORTE_DIR_REG   &= ~(1<<pin_number);      /* Configure PIN as INPUT pin */
        }

        else {
            while (1);
        }


        break ;
    case PORTF :
        if (pin_number >4)
        {
            while(1); //be careful as PORTF only has 4 pin and you entered more than 4
        }

        SYSCTL_RCGCGPIO_REG |= 0x20;//first we must open the click for port a and that is done by the GPIOSCG register
        while(!(SYSCTL_PRGPIO_REG & 0x20));// this is for waiting the clock to be activated for the the port
        if (pin_number == 0)
        {
            GPIO_PORTF_LOCK_REG = 0x4C4F434B ;
            GPIO_PORTF_CR_REG |= 0x01; //take care of using that pin as it connected to critical peripherals

        }

        GPIO_PORTF_AMSEL_REG &= ~(1<<pin_number);      /* Disable Analog on the pin */
        GPIO_PORTF_AFSEL_REG &= ~(1<<pin_number);      /* Disable alternative function on the pin */
        GPIO_PORTF_DEN_REG   |= (1<<pin_number);       /* Enable Digital I/O on the pin */
        GPIO_PORTF_PCTL_REG  &= ~(15<<(pin_number*4)) ;  /* Clear PMCx bits for the pin to use it as GPIO pin see the register for explanation  */

        if (pin_direction == OUTPUT)
        {
            GPIO_PORTF_DIR_REG   |= (1<<pin_number); /* Configure THE PIN as OUTPUT pin */

        }else if (pin_direction == INPUT)
        {

            GPIO_PORTF_DIR_REG   &= ~(1<<pin_number);      /* Configure PIN as INPUT pin */
        }
        else {
            while (1);
        }

        break ;
    }

}



void GPIO_WritePin(GPIO_PORT_NAME port_name ,uint8 pin_number , GPIO_PIN_LOGIC pin_logic)
{

    if (port_name > PORTF || pin_number > 7)
    {
        while(1); // take care you enter a wrong port number or a wrong pin number more than 7
    }

    switch (port_name)
    {
    case PORTA :
        if (((GPIO_PORTA_DIR_REG&(1<<pin_number))>>pin_number) == INPUT)
        {
            while(1); // be careful you are trying to write on an input pin and that do not make sense
        }

        if (pin_logic == HIGH)
        {
            GPIO_PORTA_DATA_REG |= (1<< pin_number);
        }
        else if (pin_logic == LOW)
        {
            GPIO_PORTA_DATA_REG &= ~(1<< pin_number);
        }
        else
        {
            while (1); // take care you enter a wrong pin logic the pin logic must be 1 or 0 or HIGH OT LOW
        }

        break ;
    case PORTB :
        if (((GPIO_PORTB_DIR_REG&(1<<pin_number))>>pin_number) == INPUT)
        {
            while(1); // be careful you are trying to write on an input pin and that do not make sense
        }

        if (pin_logic == HIGH)
        {
            GPIO_PORTB_DATA_REG |= (1<< pin_number);
        }
        else if (pin_logic == LOW)
        {
            GPIO_PORTB_DATA_REG &= ~(1<< pin_number);
        }
        else
        {
            while (1); // take care you enter a wrong pin logic the pin logic must be 1 or 0 or HIGH OT LOW
        }


        break ;
    case PORTC :

        if (((GPIO_PORTC_DIR_REG&(1<<pin_number))>>pin_number) == INPUT)
        {
            while(1); // be careful you are trying to write on an input pin and that do not make sense
        }

        if (pin_logic == HIGH)
        {
            GPIO_PORTC_DATA_REG |= (1<< pin_number);
        }
        else if (pin_logic == LOW)
        {
            GPIO_PORTC_DATA_REG &= ~(1<< pin_number);
        }
        else
        {
            while (1); // take care you enter a wrong pin logic the pin logic must be 1 or 0 or HIGH OT LOW
        }

        break ;
    case PORTD :
        if (((GPIO_PORTD_DIR_REG&(1<<pin_number))>>pin_number) == INPUT)
        {
            while(1); // be careful you are trying to write on an input pin and that do not make sense
        }

        if (pin_logic == HIGH)
        {
            GPIO_PORTD_DATA_REG |= (1<< pin_number);
        }
        else if (pin_logic == LOW)
        {
            GPIO_PORTD_DATA_REG &= ~(1<< pin_number);
        }
        else
        {
            while (1); // take care you enter a wrong pin logic the pin logic must be 1 or 0 or HIGH OT LOW
        }


        break ;
    case PORTE :
        if (((GPIO_PORTE_DIR_REG&(1<<pin_number))>>pin_number) == INPUT)
        {
            while(1); // be careful you are trying to write on an input pin and that do not make sense
        }

        if (pin_logic == HIGH)
        {
            GPIO_PORTE_DATA_REG |= (1<< pin_number);
        }
        else if (pin_logic == LOW)
        {
            GPIO_PORTE_DATA_REG &= ~(1<< pin_number);
        }
        else
        {
            while (1); // take care you enter a wrong pin logic the pin logic must be 1 or 0 or HIGH OT LOW
        }


        break ;
    case PORTF :
        if (((GPIO_PORTF_DIR_REG&(1<<pin_number))>>pin_number) == INPUT)
        {
            while(1); // be careful you are trying to write on an input pin and that do not make sense
        }

        if (pin_logic == HIGH)
        {
            GPIO_PORTF_DATA_REG |= (1<< pin_number);
        }
        else if (pin_logic == LOW)
        {
            GPIO_PORTF_DATA_REG &= ~(1<< pin_number);
        }
        else
        {
            while (1); // take care you enter a wrong pin logic the pin logic must be 1 or 0 or HIGH OT LOW
        }
        break ;
    }

}


uint8 GPIO_ReadPin(GPIO_PORT_NAME port_name ,uint8 pin_number)
{
    uint8 return_value = 0 ;

    if (port_name > PORTF || pin_number > 7)
    {
        while(1); // take care you enter a wrong port number or a wrong pin number more than 7
    }

    switch (port_name) {
    case PORTA:
        if (((GPIO_PORTA_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT )
        {
            while(1);//be carfeul you are trying to read from an OUTPUT file
        }
        return_value = (GPIO_PORTA_DATA_REG & (1<<pin_number))>>pin_number ;
        break;
    case PORTB:
        if (((GPIO_PORTB_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT )
        {
            while(1);// be carfeul you are trying to read from an OUTPUT file
        }
        return_value = (GPIO_PORTB_DATA_REG & (1<<pin_number))>>pin_number ;
        break;
    case PORTC:
        if (((GPIO_PORTC_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT )
        {
            while(1);// be carfeul you are trying to read from an OUTPUT file
        }
        return_value = (GPIO_PORTC_DATA_REG & (1<<pin_number))>>pin_number ;
        break;
    case PORTD:
        if (((GPIO_PORTD_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT )
        {
            while(1);// be carfeul you are trying to read from an OUTPUT file
        }
        return_value = (GPIO_PORTD_DATA_REG & (1<<pin_number))>>pin_number ;
        break;
    case PORTE:
        if (((GPIO_PORTE_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT )
        {
            while(1);// be carfeul you are trying to read from an OUTPUT file
        }
        return_value = (GPIO_PORTE_DATA_REG & (1<<pin_number))>>pin_number ;
        break;
    case PORTF:
        if (((GPIO_PORTF_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT )
        {
            while(1);// be carfeul you are trying to read from an OUTPUT file
        }
        return_value = (GPIO_PORTF_DATA_REG & (1<<pin_number))>>pin_number ;
        break;
    }

    return return_value ;

}


void GPIO_TogglePin(GPIO_PORT_NAME port_name ,uint8 pin_number)
{
    if (port_name > PORTF || pin_number > 7)
    {
        while(1); // take care you enter a wrong port number or a wrong pin number more than 7
    }

    switch (port_name)
    {
    case PORTA :
        if (((GPIO_PORTA_DIR_REG&(1<<pin_number))>>pin_number) == INPUT)
        {
            while(1); // be careful you are trying to write on an input pin and that do not make sense
        }
        GPIO_PORTA_DATA_REG ^= (1<< pin_number);
        break ;

    case PORTB :
        if (((GPIO_PORTB_DIR_REG&(1<<pin_number))>>pin_number) == INPUT)
        {
            while(1); // be careful you are trying to write on an input pin and that do not make sense
        }
        GPIO_PORTB_DATA_REG ^= (1<< pin_number);
        break ;

    case PORTC :

        if (((GPIO_PORTC_DIR_REG&(1<<pin_number))>>pin_number) == INPUT)
        {
            while(1); // be careful you are trying to write on an input pin and that do not make sense
        }
        GPIO_PORTC_DATA_REG ^= (1<< pin_number);
        break ;

    case PORTD :
        if (((GPIO_PORTD_DIR_REG&(1<<pin_number))>>pin_number) == INPUT)
        {
            while(1); // be careful you are trying to write on an input pin and that do not make sense
        }

        GPIO_PORTD_DATA_REG ^= (1<< pin_number);

        break ;

    case PORTE :
        if (((GPIO_PORTE_DIR_REG&(1<<pin_number))>>pin_number) == INPUT)
        {
            while(1); // be careful you are trying to write on an input pin and that do not make sense
        }

        GPIO_PORTE_DATA_REG ^= (1<< pin_number);

        break ;

    case PORTF :
        if (((GPIO_PORTF_DIR_REG&(1<<pin_number))>>pin_number) == INPUT)
        {
            while(1); // be careful you are trying to write on an input pin and that do not make sense
        }
        GPIO_PORTF_DATA_REG ^= (1<< pin_number);

        break ;
    }


}


void GPIO_PinPullUpEnable(GPIO_PORT_NAME port_name , uint8 pin_number ,GPIO_ENABLE_STATUS status)
{
    if (port_name > PORTF || pin_number > 7)
    {
        while(1); // take care you enter a wrong port number or a wrong pin number more than 7
    }

    switch (port_name) {
    case PORTA:
        if (((GPIO_PORTA_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT)
        {
            while(1); // be careful you are trying to write on an OUTPUT pin and that do not make sense
        }

        if (status == ENABLE )
        {
            GPIO_PORTA_PUR_REG |= (1 << pin_number);
        }
        else if (status == DISABLE )
        {
            GPIO_PORTA_PUR_REG &= ~(1 << pin_number);
        }

        break;
    case PORTB:
        if (((GPIO_PORTB_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT)
        {
            while(1); // be careful you are trying to write on an OUTPUT pin and that do not make sense
        }

        if (status == ENABLE )
        {
            GPIO_PORTB_PUR_REG |= (1 << pin_number);
        }
        else if (status == DISABLE )
        {
            GPIO_PORTB_PUR_REG &= ~(1 << pin_number);
        }

        break;

    case PORTC:
        if (((GPIO_PORTC_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT)
        {
            while(1); // be careful you are trying to write on an OUTPUT pin and that do not make sense
        }

        if (status == ENABLE )
        {
            GPIO_PORTC_PUR_REG |= (1 << pin_number);
        }
        else if (status == DISABLE )
        {
            GPIO_PORTC_PUR_REG &= ~(1 << pin_number);
        }

        break;

    case PORTD:
        if (((GPIO_PORTD_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT)
        {
            while(1); // be careful you are trying to write on an OUTPUT pin and that do not make sense
        }

        if (status == ENABLE )
        {
            GPIO_PORTD_PUR_REG |= (1 << pin_number);
        }
        else if (status == DISABLE )
        {
            GPIO_PORTD_PUR_REG &= ~(1 << pin_number);
        }

        break;

    case PORTE:
        if (((GPIO_PORTE_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT)
        {
            while(1); // be careful you are trying to write on an OUTPUT pin and that do not make sense
        }

        if (status == ENABLE )
        {
            GPIO_PORTE_PUR_REG |= (1 << pin_number);
        }
        else if (status == DISABLE )
        {
            GPIO_PORTE_PUR_REG &= ~(1 << pin_number);
        }

        break;

    case PORTF:
        if (((GPIO_PORTF_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT)
        {
            while(1); // be careful you are trying to write on an OUTPUT pin and that do not make sense
        }

        if (status == ENABLE )
        {
            GPIO_PORTF_PUR_REG |= (1 << pin_number);
        }
        else if (status == DISABLE )
        {
            GPIO_PORTF_PUR_REG &= ~(1 << pin_number);
        }

        break;
    }

}


void GPIO_PinPullDownEnable(GPIO_PORT_NAME port_name ,uint8 pin_number ,GPIO_ENABLE_STATUS status)
{
    if (port_name > PORTF || pin_number > 7)
    {
        while(1); // take care you enter a wrong port number or a wrong pin number more than 7
    }

    switch (port_name) {
    case PORTA:
        if (((GPIO_PORTA_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT)
        {
            while(1); // be careful you are trying to write on an OUTPUT pin and that do not make sense
        }

        if (status == ENABLE )
        {
            GPIO_PORTA_PDR_REG|= (1 << pin_number);
        }
        else if (status == DISABLE )
        {
            GPIO_PORTA_PDR_REG &= ~(1 << pin_number);
        }

        break;
    case PORTB:
        if (((GPIO_PORTB_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT)
        {
            while(1); // be careful you are trying to write on an OUTPUT pin and that do not make sense
        }

        if (status == ENABLE )
        {
            GPIO_PORTB_PDR_REG |= (1 << pin_number);
        }
        else if (status == DISABLE )
        {
            GPIO_PORTB_PDR_REG &= ~(1 << pin_number);
        }

        break;

    case PORTC:
        if (((GPIO_PORTC_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT)
        {
            while(1); // be careful you are trying to write on an OUTPUT pin and that do not make sense
        }

        if (status == ENABLE )
        {
            GPIO_PORTC_PDR_REG |= (1 << pin_number);
        }
        else if (status == DISABLE )
        {
            GPIO_PORTC_PDR_REG &= ~(1 << pin_number);
        }

        break;

    case PORTD:
        if (((GPIO_PORTD_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT)
        {
            while(1); // be careful you are trying to write on an OUTPUT pin and that do not make sense
        }

        if (status == ENABLE )
        {
            GPIO_PORTD_PDR_REG |= (1 << pin_number);
        }
        else if (status == DISABLE )
        {
            GPIO_PORTD_PDR_REG &= ~(1 << pin_number);
        }

        break;

    case PORTE:
        if (((GPIO_PORTE_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT)
        {
            while(1); // be careful you are trying to write on an OUTPUT pin and that do not make sense
        }

        if (status == ENABLE )
        {
            GPIO_PORTE_PDR_REG |= (1 << pin_number);
        }
        else if (status == DISABLE )
        {
            GPIO_PORTE_PDR_REG &= ~(1 << pin_number);
        }

        break;

    case PORTF:
        if (((GPIO_PORTF_DIR_REG&(1<<pin_number))>>pin_number) == OUTPUT)
        {
            while(1); // be careful you are trying to write on an OUTPUT pin and that do not make sense
        }

        if (status == ENABLE )
        {
            GPIO_PORTF_PDR_REG |= (1 << pin_number);
        }
        else if (status == DISABLE )
        {
            GPIO_PORTF_PDR_REG &= ~(1 << pin_number);
        }

        break;
    }
}


void  GPIO_InterruptPinEnable(GPIO_PORT_NAME port_name ,uint8 pin_number ,GPIO_ENABLE_STATUS status , GPIO_INTERRUPT_EVENT event ,uint8 priority)
{
    if (status == ENABLE)
    {
        Enable_Exceptions();
        Disable_Faults();
    }
    if (priority > 7)
    {
        while(1); //take care you entered a priority number more than 7 and that do not make sense as the maximum priority level is 7
    }




    switch (port_name) {
    case PORTA:
        if (status == ENABLE)
        {
            GPIO_PORTA_ICR_REG |= (1 << pin_number); // Clear any prior interrupt
            GPIO_PORTA_IM_REG |= (1 << pin_number);

            GPIO_PORTA_IBE_REG &= ~(1 << pin_number);
            NVIC_PRI0_REG   &= ~( NVIC_PRIX_INTA_MASK  ); //this for making sure that the priority bits are zero so the new number goes in alone
            NVIC_PRI0_REG |= (priority << NVIC_PRIX_INTA_POSITION); //putting the new priority in the register
            NVIC_EN0_REG |= (1<< NVIC_PORTA_ENABLE_BIT_POSITION ); // this is for enable the interrupt on GPIO PORTA
            if ( event == HIGH_LEVEL || event == LOW_LEVEL )
            {
                GPIO_PORTA_IS_REG |= (1 << pin_number);
                if (event == HIGH_LEVEL)
                {
                    GPIO_PORTA_IEV_REG |= (1 << pin_number );
                }
                else if (event == LOW_LEVEL)
                {

                    GPIO_PORTA_IEV_REG &=  ~(1 << pin_number );
                }
            }
            else if ( event == RISING_EDGE || event == FALLING_EDGE )
            {
                GPIO_PORTA_IS_REG &= ~(1 << pin_number);
                if (event == RISING_EDGE)
                {
                    GPIO_PORTA_IEV_REG |= (1 << pin_number );
                }
                else if (event == FALLING_EDGE)
                {
                    GPIO_PORTA_IEV_REG &=  ~(1 << pin_number );
                }

            }
            else if (event == BOTH_EDGES)
            {
                GPIO_PORTA_IBE_REG |= (1 << pin_number);

            }
            else
            {
                while (1); // be careful as you entered a wrong event
            }


        }
        else if (status == DISABLE)
        {
            NVIC_DIS0_REG |= (1 << NVIC_PORTA_ENABLE_BIT_POSITION); // this is for disable the interrupt on GPIO PORTA
        }


        break;

    case PORTB:
        if (status == ENABLE)
        {

            GPIO_PORTB_ICR_REG |= (1 << pin_number); // Clear any prior interrupt
            GPIO_PORTB_IM_REG |= (1 << pin_number);

            GPIO_PORTB_IBE_REG &= ~(1 << pin_number);
            NVIC_PRI0_REG   &= ~(NVIC_PRIX_INTB_MASK  ); //this for making sure that the priority bits are zero so the new number goes in alone
            NVIC_PRI0_REG |= (priority << NVIC_PRIX_INTB_POSITION); //putting the new priority in the register
            NVIC_EN0_REG |= (1 << NVIC_PORTB_ENABLE_BIT_POSITION); // this is for enable the interrupt on GPIO PORTA
            if ( event == HIGH_LEVEL || event == LOW_LEVEL )
            {
                GPIO_PORTB_IS_REG |= (1 << pin_number);
                if (event == HIGH_LEVEL)
                {
                    GPIO_PORTB_IEV_REG |= (1 << pin_number );
                }
                else if (event == LOW_LEVEL)
                {

                    GPIO_PORTB_IEV_REG &=  ~(1 << pin_number );
                }
            }
            else if ( event == RISING_EDGE || event == FALLING_EDGE )
            {
                GPIO_PORTB_IS_REG &= ~(1 << pin_number);
                if (event == RISING_EDGE)
                {
                    GPIO_PORTB_IEV_REG |= (1 << pin_number );
                }
                else if (event == FALLING_EDGE)
                {
                    GPIO_PORTB_IEV_REG &=  ~(1 << pin_number );
                }

            }
            else if (event == BOTH_EDGES)
            {
                GPIO_PORTB_IBE_REG |= (1 << pin_number);

            }
            else
            {
                while (1); // be careful as you entered a wrong event
            }



        }
        else if (status == DISABLE)
        {

            NVIC_DIS0_REG |= (1 << NVIC_PORTB_ENABLE_BIT_POSITION); // this is for disable the interrupt on GPIO PORTA

        }


        break;

    case PORTC:
        if (status == ENABLE)
        {
            GPIO_PORTC_ICR_REG |= (1 << pin_number); // Clear any prior interrupt
            GPIO_PORTC_IM_REG |= (1 << pin_number);

            GPIO_PORTC_IBE_REG &= ~(1 << pin_number);
            NVIC_PRI0_REG   &= ~(NVIC_PRIX_INTC_MASK  ); //this for making sure that the priority bits are zero so the new number goes in alone
            NVIC_PRI0_REG |= (priority << NVIC_PRIX_INTC_POSITION); //putting the new priority in the register
            NVIC_EN0_REG |= (1<< NVIC_PORTC_ENABLE_BIT_POSITION); // this is for enable the interrupt on GPIO PORTA
            if ( event == HIGH_LEVEL || event == LOW_LEVEL )
            {
                GPIO_PORTC_IS_REG |= (1 << pin_number);
                if (event == HIGH_LEVEL)
                {
                    GPIO_PORTC_IEV_REG |= (1 << pin_number );
                }
                else if (event == LOW_LEVEL)
                {

                    GPIO_PORTC_IEV_REG &=  ~(1 << pin_number );
                }
            }
            else if ( event == RISING_EDGE || event == FALLING_EDGE )
            {
                GPIO_PORTC_IS_REG &= ~(1 << pin_number);
                if (event == RISING_EDGE)
                {
                    GPIO_PORTC_IEV_REG |= (1 << pin_number );
                }
                else if (event == FALLING_EDGE)
                {
                    GPIO_PORTC_IEV_REG &=  ~(1 << pin_number );
                }

            }
            else if (event == BOTH_EDGES)
            {
                GPIO_PORTC_IBE_REG |= (1 << pin_number);

            }
            else
            {
                while (1); // be careful as you entered a wrong event
            }




        }
        else if (status == DISABLE)
        {

            NVIC_DIS0_REG |= (1 << NVIC_PORTC_ENABLE_BIT_POSITION); // this is for disable the interrupt on GPIO PORTA

        }


        break;

    case PORTD:
        if (status == ENABLE)
        {
            GPIO_PORTD_ICR_REG |= (1 << pin_number); // Clear any prior interrupt
            GPIO_PORTD_IBE_REG &= ~(1 << pin_number);
            GPIO_PORTD_IM_REG |= (1 << pin_number);

            NVIC_PRI0_REG   &= ~(NVIC_PRIX_INTD_MASK  ); //this for making sure that the priority bits are zero so the new number goes in alone
            NVIC_PRI0_REG |= (priority << NVIC_PRIX_INTD_POSITION); //putting the new priority in the register
            NVIC_EN0_REG |= (1<< NVIC_PORTD_ENABLE_BIT_POSITION); // this is for enable the interrupt on GPIO PORTA
            if ( event == HIGH_LEVEL || event == LOW_LEVEL )
            {
                GPIO_PORTD_IS_REG |= (1 << pin_number);
                if (event == HIGH_LEVEL)
                {
                    GPIO_PORTD_IEV_REG |= (1 << pin_number );
                }
                else if (event == LOW_LEVEL)
                {

                    GPIO_PORTD_IEV_REG &=  ~(1 << pin_number );
                }
            }
            else if ( event == RISING_EDGE || event == FALLING_EDGE )
            {
                GPIO_PORTD_IS_REG &= ~(1 << pin_number);
                if (event == RISING_EDGE)
                {
                    GPIO_PORTD_IEV_REG |= (1 << pin_number );
                }
                else if (event == FALLING_EDGE)
                {
                    GPIO_PORTD_IEV_REG &=  ~(1 << pin_number );
                }

            }
            else if (event == BOTH_EDGES)
            {
                GPIO_PORTD_IBE_REG |= (1 << pin_number);

            }
            else
            {
                while (1); // be careful as you entered a wrong event
            }


        }
        else if (status == DISABLE)
        {

            NVIC_DIS0_REG |= (1 << NVIC_PORTD_ENABLE_BIT_POSITION); // this is for disable the interrupt on GPIO PORTA

        }
        break;

    case PORTE:
        if (status == ENABLE)
        {

            GPIO_PORTE_ICR_REG |= (1 << pin_number); // Clear any prior interrupt
            GPIO_PORTE_IBE_REG   &= ~(1<<pin_number);      /* PF4 will detect a certain edge */
            GPIO_PORTE_IM_REG |= (1 << pin_number);

            NVIC_PRI0_REG   &= ~(NVIC_PRIX_INTA_MASK  ); //this for making sure that the priority bits are zero so the new number goes in alone
            NVIC_PRI0_REG |= (priority << NVIC_PRIX_INTA_POSITION); //putting the new priority in the register
            NVIC_EN0_REG |= (1<< NVIC_PORTE_ENABLE_BIT_POSITION); // this is for enable the interrupt on GPIO PORTE
            if ( event == HIGH_LEVEL || event == LOW_LEVEL )
            {
                GPIO_PORTE_IS_REG |= (1 << pin_number);
                if (event == HIGH_LEVEL)
                {
                    GPIO_PORTE_IEV_REG |= (1 << pin_number );
                }
                else if (event == LOW_LEVEL)
                {

                    GPIO_PORTE_IEV_REG &=  ~(1 << pin_number );
                }
            }
            else if ( event == RISING_EDGE || event == FALLING_EDGE )
            {
                GPIO_PORTE_IS_REG &= ~(1 << pin_number);
                if (event == RISING_EDGE)
                {
                    GPIO_PORTE_IEV_REG |= (1 << pin_number );
                }
                else if (event == FALLING_EDGE)
                {
                    GPIO_PORTE_IEV_REG &=  ~(1 << pin_number );
                }

            }
            else if (event == BOTH_EDGES)
            {
                GPIO_PORTE_IBE_REG |= (1 << pin_number);

            }
            else
            {
                while (1); // be careful as you entered a wrong event
            }


        }
        else if (status == DISABLE)
        {

            NVIC_DIS0_REG |= (1 << NVIC_PORTE_ENABLE_BIT_POSITION); // this is for disable the interrupt on GPIO PORTA

        }


        break;

    case PORTF:
        if (status == ENABLE)
        {
            GPIO_PORTF_ICR_REG |= (1 << pin_number); // Clear any prior interrupt
            GPIO_PORTF_IBE_REG   &= ~(1<<pin_number);      /* PF4 will detect a certain edge */
            GPIO_PORTF_IM_REG |= (1 << pin_number);

            NVIC_PRI7_REG   &= ~( NVIC_PRIX_INTC_MASK  ); //this for making sure that the priority bits are zero so the new number goes in alone
            NVIC_PRI7_REG |= (priority << NVIC_PRIX_INTC_POSITION); //putting the new priority in the register
            NVIC_EN0_REG |= (1 <<  NVIC_PORTF_ENABLE_BIT_POSITION); // this is for enable the interrupt on GPIO PORTF
            if ( event == HIGH_LEVEL || event == LOW_LEVEL )
            {
                GPIO_PORTF_IS_REG |= (1 << pin_number);
                if (event == HIGH_LEVEL)
                {
                    GPIO_PORTF_IEV_REG |= (1 << pin_number );
                }
                else if (event == LOW_LEVEL)
                {

                    GPIO_PORTF_IEV_REG &=  ~(1 << pin_number );
                }
            }
            else if ( event == RISING_EDGE || event == FALLING_EDGE )
            {
                GPIO_PORTF_IS_REG &= ~(1 << pin_number);
                if (event == RISING_EDGE)
                {
                    GPIO_PORTF_IEV_REG |= (1 << pin_number );
                }
                else if (event == FALLING_EDGE)
                {
                    GPIO_PORTF_IEV_REG &=  ~(1 << pin_number );
                }

            }
            else if (event == BOTH_EDGES)
            {
                GPIO_PORTF_IBE_REG |= (1 << pin_number);

            }
            else
            {
                while (1); // be careful as you entered a wrong event
            }



        }
        else if (status == DISABLE)
        {
            NVIC_DIS0_REG |= (1 << NVIC_PORTF_ENABLE_BIT_POSITION); // this is for disable the interrupt on GPIO PORTA

        }

        break;
    }

}


void GPIO_PortF_SetCallBackFuntion(  void(*functionHandler)(uint8 value)  )
{
    PORTF_CallBack_ptr = functionHandler;
}


void GPIOPortF_Handler(void)
{
    if(PORTF_CallBack_ptr != NULL_PTR)
    {

        if(GPIO_PORTF_RIS_REG & (1<<PF0))         // if the trigger from pf0
        {
            GPIO_PORTF_ICR_REG   |= (1<<PF0);       /* Clear Trigger flag for PF0 (Interrupt Flag) */
            (*PORTF_CallBack_ptr)(DRIVER_SEAT_ID);
        }
        else if(GPIO_PORTF_RIS_REG & (1<<PF4))     //if the interrupt is from pf4
        {
            GPIO_PORTF_ICR_REG   |= (1<<PF4);       /* Clear Trigger flag for PF4 (Interrupt Flag) */
            (*PORTF_CallBack_ptr)(CO_DRIVER_SEAT_ID);
        }


    }



}





