 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC.c
 *
 * Description: Source file for the TM4C123GH6PM ADC driver for TivaC general purpose timer
 *
 * Author: MAHMOUD TAREK
 *
 *******************************************************************************/
#include "adc.h"
#include "tm4c123gh6pm_registers.h"

void ADC_0_init(void)
{
    /*ADC Configurations*/
    SYSCTL_RCGCGPIO_REG |= (1<<4);/*Enable GPIOE*/
    SYSCTL_RCGCADC_REG |= (1<<0);/*Enable the adc clock*/
    GPIO_PORTE_AFSEL_REG |= (1<<3);/*Enable alternate functionality on pin 1 portE*/
    GPIO_PORTE_DEN_REG &= ~(1<<3);/*Disable digital functionality on pin 1 portE*/
    GPIO_PORTE_AMSEL_REG |= (1<<3);/*Disable the analog isolation circuit*/

    /*Sequencer Configurations*/
    ADC_0_ACTSS_REG &= ~(1<<3);/*Disable the sequencer*/
    ADC_0_EMUX_REG &= ~0xF000;/*Configure the trigger event to continuous*/
    ADC_0_SSMUX3_REG = 0;/*Select which pin the sequencer will work on*/
    ADC_0_SSCTL3_REG |= (1<<1)|(1<<2);/*Set the adc to generate interrupts and set the end of sequence*/
    ADC_0_ACTSS_REG |= (1<<3);/*Enable the sequencer*/

}

uint32 ADC_READ_VALUE(void)
{
    uint32 ADC_Value = 0;
    ADC_0_PSSI_REG |= (1<<3);
    while((ADC_0_RIS_REG & 8) == 0) ;
    ADC_Value = ADC_0_SSFIFO3_REG;
    ADC_0_ISC_REG = 8;
    return ADC_Value;
}


