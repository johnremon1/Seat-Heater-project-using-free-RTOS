/*
 * ARM_ADC_DRIVER.c
 *
 *  Created on: Oct 9, 2024
 *      Author: john Remon
 */

#include "ARM_ADC_DRIVER.h"


static void(*ADC0_CallBack_ptr)(uint16 return_value) = NULL_PTR ;
static void(*ADC1_CallBack_ptr)(uint16 return_value) = NULL_PTR ;




void ADC_init(ADC_PORTID portnum ,ADC_PIN_NAME pinNumber ,ADC_MODULE ADC_module)
{
    //first we setting up the adc
    SYSCTL_RCGCADC_REG |= 0x03;//this is for enable the clock gating for the ADC0 and ADC1 module
    while(! (SYSCTL_PRADC_REG & 0x03) );

    switch (portnum) {
    case ADC_PORTB:
        SYSCTL_RCGCGPIO_REG |=  0x02;//first we must open the click for port B and that is done by the GPIOSCG register
        while (!(SYSCTL_PRGPIO_REG & (0x02) ) );// this is for waiting the clock to be activated for the the port
        //GPIO PIN configurations
        GPIO_PORTB_DIR_REG &= ~(1 << pinNumber); // this is for making the pin an input pin
        GPIO_PORTB_AFSEL_REG |= (1 << pinNumber); //this is for GPIO alternate function selection if the bit is set that has alternate funtion than a dio
        GPIO_PORTB_DEN_REG &= ~(1 << pinNumber); // this is for disable the digital circuits from the pin
        GPIO_PORTB_AMSEL_REG |= (1 << pinNumber); // this is for disable the analog circuit isolation is use the pin as adc pin
        break;
    case ADC_PORTD:
        SYSCTL_RCGCGPIO_REG |=  0x08;//first we must open the click for port D and that is done by the GPIOSCG register
        while (!(SYSCTL_PRGPIO_REG & (0x08) ) );// this is for waiting the clock to be activated for the the port
        //GPIO PIN configurations
        GPIO_PORTD_DIR_REG &= ~(1 << pinNumber); // this is for making the pin an input pin
        GPIO_PORTD_AFSEL_REG |= (1 << pinNumber); //this is for GPIO alternate function selection if the bit is set that has alternate funtion than a dio
        GPIO_PORTD_DEN_REG &= ~(1 << pinNumber); // this is for disable the digital circuits from the pin
        GPIO_PORTD_AMSEL_REG |= (1 << pinNumber); // this is for disable the analog circuit isolation is use the pin as adc pin
        break;
    case ADC_PORTE:
        SYSCTL_RCGCGPIO_REG |=  0x10;//first we must open the click for port E and that is done by the GPIOSCG register
        while (!(SYSCTL_PRGPIO_REG & (0x10) ) );// this is for waiting the clock to be activated for the the port
        //GPIO PIN configurations
        GPIO_PORTE_DIR_REG &= ~(1 << pinNumber); // this is for making the pin an input pin
        GPIO_PORTE_AFSEL_REG |= (1 << pinNumber); //this is for GPIO alternate function selection if the bit is set that has alternate funtion than a dio
        GPIO_PORTE_DEN_REG &= ~(1 << pinNumber); // this is for disable the digital circuits from the pin
        GPIO_PORTE_AMSEL_REG |= (1 << pinNumber); // this is for disable the analog circuit isolation is use the pin as adc pin
        break;
    default:

        break;
    }
    if (ADC_module == ADC0)
    {
        ADC0_ACTSS_REG &= ~(1 << 0);
        ADC0_EMUX_REG  = 0x00 ;// Processor (default)The trigger is initiated by setting the SSn bit in the ADCPSSI register.
       // ADC0_CTL_REG |= ( 1 << 6); //Dither mode enabled this mode helps to smooth the signal and exclude noise
        ADC0_SSMUX0_REG |= (pinNumber << 0); //1st Sample Input Select
        ADC0_SSCTL0_REG |= ( 1 << 1 );// 1st Sample is End of Sequence
        ADC0_ACTSS_REG |= (1 << 0);
    }
    else if (ADC_module == ADC1)
    {
        ADC1_ACTSS_REG &= ~(1 << 0);
        ADC1_EMUX_REG  = 0x00 ;// Processor (default)The trigger is initiated by setting the SSn bit in the ADCPSSI register.
        //ADC1_CTL_REG |= ( 1 << 6); //Dither mode enabled this mode helps to smooth the signal and exclude noise
        ADC1_SSMUX0_REG |= (pinNumber << 0); //1st Sample Input Select
        ADC1_SSCTL0_REG |= ( 1 << 1 );// 1st Sample is End of Sequence
        ADC1_ACTSS_REG |= (1 << 0);
    }
    else

    {
        //report an error
    }

}
//note that this function only use sample sequencer 0
void ADC_interruptEnable(ADC_PORTID portnum ,ADC_PIN_NAME pinNumber ,ADC_MODULE ADC_module,uint8 priority)
{


    if (ADC_module == ADC0)
    {
        ADC0_IM_REG |= (1 << 0); //The raw interrupt signal from Sample Sequencer 0 (ADCRIS register INR0 bit) is sent to the interrupt controller.
        ADC0_SSCTL0_REG |= ( 1 << 2);// 1st Sample Interrupt Enable The raw interrupt signal (INR0 bit) is asserted at the end of the first sample's conversion. If the MASK0 bit in the ADCIM register is set, the interrupt is promoted to the interrupt controller
        ADC0_ISC_REG |= (1 << 0);  // Clear interrupt flag for Sequencer 0
        //NVIC CONFIGRATIONS
        NVIC_PRI3_REG =  ( NVIC_PRI3_REG & ~(0x07 << 21)) | ((priority & 0x07) << 21);//setting the priority register for adc0
        NVIC_EN0_REG |= (1 << 14);//enabling interrupt for adc0
    }
    else if (ADC_module == ADC1)
    {
        ADC1_IM_REG |= (1 << 0); //The raw interrupt signal from Sample Sequencer 0 (ADCRIS register INR0 bit) is sent to the interrupt controller.
        ADC1_SSCTL0_REG |= ( 1 << 2);// 1st Sample Interrupt Enable The raw interrupt signal (INR0 bit) is asserted at the end of the first sample's conversion. If the MASK0 bit in the ADCIM register is set, the interrupt is promoted to the interrupt controller
        ADC1_ISC_REG |= (1 << 0);  // Clear interrupt flag for Sequencer 0
        NVIC_PRI12_REG = (NVIC_PRI12_REG & ~(0x7 << 5)) | ((priority & 0x07) << 5);//setting the priority register for adc1

        NVIC_EN1_REG |= (1 << 16);//enabling interrupt for adc1;
    }
}
//note that this function only use sample sequencer 0
void ADC_startConversion(ADC_PORTID portnum ,ADC_PIN_NAME pinNumber ,ADC_MODULE ADC_module)
{

    if (ADC_module == ADC0)
    {
        ADC0_PSSI_REG |= (1 << 0); //SS0 Initiate -- 1 means Begin sampling on Sample Sequencer 0, if the sequencer is enabled in the ADCACTSS register.

    }
    else if (ADC_module == ADC1)
    {
        ADC1_PSSI_REG |= (1 << 0); //SS0 Initiate -- 1 means Begin sampling on Sample Sequencer 0, if the sequencer is enabled in the ADCACTSS register.

    }
}


uint16 ADC_u16ReadData(ADC_PORTID portnum ,ADC_PIN_NAME pinNumber, ADC_MODULE ADC_module)
{
    uint16 return_value = 0 ;

    if (ADC_module == ADC0)
    {
        ADC0_PSSI_REG |= (1 << 0); //SS0 Initiate -- 1 means Begin sampling on Sample Sequencer 0, if the sequencer is enabled in the ADCACTSS register.
        while (! (ADC0_ISC_REG & (1 << 0) )) ; //waiting for the interrupt bit to be set as indication of end of conversion
        ADC0_ISC_REG |= ( 1 << 0);//write 1 to clear the flag
        return_value = ADC0_SSFIFO0_REG & 0xFFF ;
    }
    else if (ADC_module == ADC1)
    {
        ADC1_PSSI_REG |= (1 << 0); //SS0 Initiate -- 1 means Begin sampling on Sample Sequencer 0, if the sequencer is enabled in the ADCACTSS register.
        while (! (ADC1_ISC_REG & (1 << 0) )) ;//waiting for the interrupt bit to be set as indication of end of conversion
        ADC1_ISC_REG |= ( 1 << 0);//write 1 to clear the flag
        return_value = ADC1_SSFIFO0_REG & 0xFFF ;
    }
    return return_value ;
}



void ADC0_SS0_Handler (void)
{
   if ( ADC0_CallBack_ptr != NULL_PTR)
   {
       ADC0_ISC_REG |= ( 1 << 0);//write 1 to clear the flag
       (*ADC0_CallBack_ptr)(ADC0_SSFIFO0_REG & 0xFFF);
   }

}

void  ADC1_SS0_Handler(void)
{
    if ( ADC1_CallBack_ptr != NULL_PTR)
    {
        ADC1_ISC_REG |= ( 1 << 0);//write 1 to clear the flag
        (*ADC1_CallBack_ptr)(ADC1_SSFIFO0_REG & 0xFFF);
    }

}

void ADC0_SetCallBackFunction(void (*functionPtr)(uint16 return_value))
{
    ADC0_CallBack_ptr = functionPtr ;
}


void ADC1_SetCallBackFunction(void (*functionPtr)(uint16 return_value))
{

    ADC1_CallBack_ptr = functionPtr ;
}

