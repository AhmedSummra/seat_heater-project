/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "std_types.h"
#include "tm4c123gh6pm_registers.h"
/* MCAL includes. */
#include "gpio.h"
#include "uart0.h"
#include "adc.h"
/* The HW setup function */
static void prvSetupHardware( void );

/* FreeRTOS tasks */
void vDriverMonitorTask(void *pvParameters);
void vPassengerMonitorTask(void *pvParameters);
void vLCDHandleTask(void *pvParameters);
void vHeatSensorMonitorTask(void *pvParameters);
void vOffLevelTask(void *pvParameters);
void vLowLevelTask(void *pvParameters);
void vMediumLevelTaskTask(void *pvParameters);
void vHighLevelTask(void *pvParameters);

/* FreeRTOS Binary Semaphores */
xSemaphoreHandle offlevelsemaphore;
xSemaphoreHandle lowlevelsemaphore;
xSemaphoreHandle mediumlevelsemaphore;
xSemaphoreHandle highlevelsemaphore;
xSemaphoreHandle lcdsemaphore;

/* Private Definitions */
#define MAX_VALID_TEMP 40
#define MIN_VALID_TEMP 5

typedef enum {
    OFF,LOW,MEDIUM,HIGH
}HeaterMode;

typedef enum {
    DRIVER,PASSENGER
}ActiveUser;

uint8_t activeuser;
uint8_t driverPressCount;
uint8_t PassengerPressCount;


int main()
{
    /* Setup the hardware for use with the Tiva C board. */
    prvSetupHardware();

    /* Create a binary semaphore */
    offlevelsemaphore = xSemaphoreCreateBinary();
    lowlevelsemaphore = xSemaphoreCreateBinary();
    mediumlevelsemaphore = xSemaphoreCreateBinary();
    highlevelsemaphore = xSemaphoreCreateBinary();
    lcdsemaphore = xSemaphoreCreateBinary();

    /* Create Tasks here */
    xTaskCreate(vDriverMonitorTask, "Driver Task", 256, NULL, 1, NULL);
    xTaskCreate(vPassengerMonitorTask, "Passenger Task", 256, NULL, 1, NULL);
    xTaskCreate(vLCDHandleTask, "LCD Task", 256, NULL, 2, NULL);
    xTaskCreate(vHeatSensorMonitorTask, "Sensor monitor Task", 256, NULL, 1, NULL);
    xTaskCreate(vOffLevelTask, "OFF level Task", 256, NULL, 3, NULL);
    xTaskCreate(vLowLevelTask, "LOW level Task", 256, NULL, 3, NULL);
    xTaskCreate(vMediumLevelTaskTask, "MEDIUM level Task", 256, NULL, 3, NULL);
    xTaskCreate(vHighLevelTask, "HIGH level Task", 256, NULL, 3, NULL);

    vTaskStartScheduler();

    /* Should never reach here!  If you do then there was not enough heap
    available for the idle task to be created. */
    for (;;);

}

static void prvSetupHardware( void )
{
    /* Place here any needed HW initialization such as GPIO, UART, etc.  */
    GPIO_BuiltinButtonsLedsInit();
    GPIO_SW1EdgeTriggeredInterruptInit();
    GPIO_SW2EdgeTriggeredInterruptInit();
    UART0_Init();
    ADC_0_init();
}

void vDriverMonitorTask(void *pvParameters)
{
    uint8_t desiredTemp;
    uint8_t actualTemp;


    for (;;) {

            actualTemp = ADC_READ_VALUE();

            switch (driverPressCount)
            {
            case LOW:
                desiredTemp = 25;
                if((desiredTemp-actualTemp) >= 10 )     /* for high intensity */
                {
                    xSemaphoreGive(highlevelsemaphore);
                }
                else if ((desiredTemp-actualTemp) >=5 && (desiredTemp-actualTemp) < 10)   /* for medium intensity */
                {
                    xSemaphoreGive(mediumlevelsemaphore);
                }
                else if ((desiredTemp-actualTemp) >=2 && (desiredTemp-actualTemp) < 5)    /* for low intensity */
                {
                    xSemaphoreGive(lowlevelsemaphore);
                }
                else    /* for the OFF condition */
                {
                    xSemaphoreGive(offlevelsemaphore);
                }
                break;
            case MEDIUM :
                desiredTemp = 30;
                if((desiredTemp-actualTemp) >= 10 )     /* for high intensity */
                {
                    xSemaphoreGive(highlevelsemaphore);
                }
                else if ((desiredTemp-actualTemp) >=5 && (desiredTemp-actualTemp) < 10)     /* for medium intensity */
                {
                    xSemaphoreGive(mediumlevelsemaphore);
                }
                else if ((desiredTemp-actualTemp) >=2 && (desiredTemp-actualTemp) < 5)      /* for low intensity */
                {
                    xSemaphoreGive(lowlevelsemaphore);
                }
                else     /* for the OFF condition */
                {
                    xSemaphoreGive(offlevelsemaphore);
                }
                break;
            case HIGH :
                desiredTemp = 35;
                if((desiredTemp-actualTemp) >= 10 )      /* for high intensity */
                {
                    xSemaphoreGive(highlevelsemaphore);
                }
                else if ((desiredTemp-actualTemp) >=5 && (desiredTemp-actualTemp) < 10)      /* for medium intensity */
                {
                    xSemaphoreGive(mediumlevelsemaphore);
                }
                else if ((desiredTemp-actualTemp) >=2 && (desiredTemp-actualTemp) < 5)      /* for low intensity */
                {
                    xSemaphoreGive(lowlevelsemaphore);
                }
                else      /* for the OFF condition */
                {
                    xSemaphoreGive(offlevelsemaphore);
                }
                break;
            default :
                xSemaphoreGive(offlevelsemaphore);
                driverPressCount =0;
                break;
            }

    }
}

void vPassengerMonitorTask(void *pvParameters)
{
    uint8_t desiredTemp;
    uint8_t actualTemp;


    for (;;) {

            actualTemp = ADC_READ_VALUE();

            switch (PassengerPressCount)
            {
            case LOW:
                desiredTemp = 25;
                if((desiredTemp-actualTemp) >= 10 )     /* for high intensity */
                {
                    xSemaphoreGive(highlevelsemaphore);
                }
                else if ((desiredTemp-actualTemp) >=5 && (desiredTemp-actualTemp) < 10)   /* for medium intensity */
                {
                    xSemaphoreGive(mediumlevelsemaphore);
                }
                else if ((desiredTemp-actualTemp) >=2 && (desiredTemp-actualTemp) < 5)    /* for low intensity */
                {
                    xSemaphoreGive(lowlevelsemaphore);
                }
                else    /* for the OFF condition */
                {
                    xSemaphoreGive(offlevelsemaphore);
                }
                break;
            case MEDIUM :
                desiredTemp = 30;
                if((desiredTemp-actualTemp) >= 10 )     /* for high intensity */
                {
                    xSemaphoreGive(highlevelsemaphore);
                }
                else if ((desiredTemp-actualTemp) >=5 && (desiredTemp-actualTemp) < 10)     /* for medium intensity */
                {
                    xSemaphoreGive(mediumlevelsemaphore);
                }
                else if ((desiredTemp-actualTemp) >=2 && (desiredTemp-actualTemp) < 5)      /* for low intensity */
                {
                    xSemaphoreGive(lowlevelsemaphore);
                }
                else     /* for the OFF condition */
                {
                    xSemaphoreGive(offlevelsemaphore);
                }
                break;
            case HIGH :
                desiredTemp = 35;
                if((desiredTemp-actualTemp) >= 10 )      /* for high intensity */
                {
                    xSemaphoreGive(highlevelsemaphore);
                }
                else if ((desiredTemp-actualTemp) >=5 && (desiredTemp-actualTemp) < 10)      /* for medium intensity */
                {
                    xSemaphoreGive(mediumlevelsemaphore);
                }
                else if ((desiredTemp-actualTemp) >=2 && (desiredTemp-actualTemp) < 5)      /* for low intensity */
                {
                    xSemaphoreGive(lowlevelsemaphore);
                }
                else      /* for the OFF condition */
                {
                    xSemaphoreGive(offlevelsemaphore);
                }
                break;
            default :
                xSemaphoreGive(offlevelsemaphore);
                driverPressCount =0;
                break;
            }

    }
}

void vOffLevelTask(void *pvParameters)
{
    /* initialization part */

    while(1)
    {
        if(xSemaphoreTake(offlevelsemaphore,0))
        {
            GPIO_BlueLedOff();
            GPIO_GreenLedOff();
            GPIO_RedLedOff();
        }
    }
}

void vLowLevelTask(void *pvParameters)
{
    /* initialization part */

    while(1)
    {
        if(xSemaphoreTake(lowlevelsemaphore,0))
        {
            GPIO_BlueLedOff();
            GPIO_GreenLedOff();
            GPIO_RedLedOff();
            GPIO_GreenLedOn();
        }
    }
}

void vMediumLevelTaskTask(void *pvParameters)
{
    /* initialization part*/

    while(1)
    {
        if(xSemaphoreTake(mediumlevelsemaphore,0))
        {
            GPIO_BlueLedOff();
            GPIO_GreenLedOff();
            GPIO_RedLedOff();
            GPIO_BlueLedOn();
        }
    }
}

void vHighLevelTask(void *pvParameters)
{
    /* initialization part */

    while(1)
    {
        if(xSemaphoreTake(highlevelsemaphore,0))
        {
            GPIO_BlueLedOff();
            GPIO_GreenLedOff();
            GPIO_RedLedOff();
            GPIO_BlueLedOn();
            GPIO_GreenLedOn();
        }
    }
}

void vHeatSensorMonitorTask(void *pvParameters)
{
    /* initialization part */
    uint8_t CurrentTemp;

    while(1)
    {
        CurrentTemp = ADC_READ_VALUE();
        if(CurrentTemp > MAX_VALID_TEMP || CurrentTemp < MIN_VALID_TEMP)
        {
            GPIO_BlueLedOff();
            GPIO_GreenLedOff();
            GPIO_RedLedOff();
            GPIO_RedLedOn();
        }
    }
}

void vLCDHandleTask(void *pvParameters)
{
    /* initialization part */
    uint8_t currenttemp;

    while(1)
    {
        if(xSemaphoreTake(lcdsemaphore,0))
        {
            switch(activeuser)
            {
            case DRIVER :
                UART0_SendString("Active User Is Driver \n");
                switch(driverPressCount)
                {
                case OFF :
                    UART0_SendString("Current Status: OFF \n");
                    break;
                case LOW :
                    UART0_SendString("Current Status: LOW \n");
                    break;
                case MEDIUM :
                    UART0_SendString("Current Status: MEDIUM \n");
                    break;
                case HIGH :
                    UART0_SendString("Current Status: HIGH \n");
                    break;
                default :
                    UART0_SendString("No Status Detected \n");
                    break;
                }
                break;
            case PASSENGER :
                UART0_SendString("Active User Is Passenger \n");

                switch(PassengerPressCount)
                {
                case OFF :
                    UART0_SendString("Current Status: OFF \n");
                    break;
                case LOW :
                    UART0_SendString("Current Status: LOW \n");
                    break;
                case MEDIUM :
                    UART0_SendString("Current Status: MEDIUM \n");
                    break;
                case HIGH :
                    UART0_SendString("Current Status: HIGH \n");
                    break;
                default :
                    UART0_SendString("No Status Detected \n");
                    break;
                }
                break;
            default :
                UART0_SendString("No Active User Detected \n");
                break;
            }

            currenttemp = ADC_READ_VALUE();
            UART0_SendString("Current Temperature: ");
            UART0_SendInteger(currenttemp);
        }
    }
}

void GPIOPortF_Handler(void)
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    if(GPIO_PORTF_RIS_REG & (1<<0))           /* PF0 handler code */
    {
        activeuser = DRIVER;                  /* to know who pressed the key (the active user)*/
        xSemaphoreGiveFromISR(lcdsemaphore,&pxHigherPriorityTaskWoken);  /* let the LCD display the current status */
        driverPressCount ++;                  /* change the mode of the active current user */
        GPIO_PORTF_ICR_REG   |= (1<<0);       /* Clear Trigger flag for PF0 (Interrupt Flag) */
    }
    else if(GPIO_PORTF_RIS_REG & (1<<4))      /* PF4 handler code */
    {
        activeuser = PASSENGER;              /* to know who pressed the key (the active user)*/
        xSemaphoreGiveFromISR(lcdsemaphore,&pxHigherPriorityTaskWoken);  /* let the LCD display the current status */
        PassengerPressCount ++;               /* change the mode of the active current user */
        GPIO_PORTF_ICR_REG   |= (1<<4);       /* Clear Trigger flag for PF4 (Interrupt Flag) */
    }
}
/*-----------------------------------------------------------*/
