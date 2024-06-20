/**********************************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC.h
 *
 * Description: Header file for the TM4C123GH6PM ADC driver for TivaC Built-in Buttons and LEDs
 *
 * Author: MAHMOUD TAREK
 *
 ***********************************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

#define ADC_MAX_VALUE      4095
#define ADC_REFERENCE_VOLTAGE  3.3
#define ADC_SENSETIVITY  0.0008

/*****************************************************************************
ADC0 Registers (ADC0)
*****************************************************************************/

#define ADC_0_ACTSS_REG         (*((volatile uint32 *) 0x40038000))
#define ADC_0_RIS_REG           (*((volatile uint32 *) 0x40038004))
#define ADC_0_IM_REG            (*((volatile uint32 *) 0x40038008))
#define ADC_0_EMUX_REG          (*((volatile uint32 *) 0x40038014))
#define ADC_0_SSMUX3_REG        (*((volatile uint32 *) 0x400380A0))
#define ADC_0_SSCTL3_REG        (*((volatile uint32 *) 0x400380A4))
#define ADC_0_SSFIFO3_REG       (*((volatile uint32 *) 0x400380A8))
#define ADC_0_ISC_REG           (*((volatile uint32 *) 0x4003800C))
#define ADC_0_PSSI_REG          (*((volatile uint32 *) 0x40038028))

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_0_init(void);
uint32 ADC_READ_VALUE(void);

#endif /* ADC_H_ */
