/*
 * Project_cfg.h
 *
 *  Created on: Oct 9, 2024
 *      Author: John Remon
 */

#ifndef PROJECT_CFG_H_
#define PROJECT_CFG_H_

#include "std_types.h"
//#include "ARM_ADC_DRIVER.h"


/***********************************************************************************************************
 *                                   user defined features
 ***********************************************************************************************************/
#define DEBUGGING_MOOD                       (STD_OFF)

#define DET_DEVELOPMENT_ERROR_REPORTING      (STD_ON)



//temprature monitor task
#define BUTTON_SEMAPHORE_MAX_COUNT                           (5U)
#define TEMPRATURE_MONITOR_PERIODIC_TIME_MS                  (10)
#define HEATER_CALCULATION_PERIODIC_TIME_MS                  (10)
#define HEATER_CALCULATIONS_MAX_BLOCKING_TIME_MS

#define MAX_TIME_IN_BLOCKING_STATE_MS                       pdMS_TO_TICKS(3000)//this macro is only to prevent a deadlock from happening
#define HEATER_CALCULATION_TASK_BLOCKING_DELAY_TIME_MS      pdMS_TO_TICKS (3000)

/**********************************************************************************************************
 *                                       definintions
 *********************************************************************************************************/

#define PF0                      (0U)
#define PF1                      (1U)
#define PF2                      (2U)
#define PF3                      (3U)
#define PF4                      (4U)

#define PA0                      (0U)
#define PA1                      (1U)
#define PA2                      (2U)
#define PA3                      (3U)


/*
 * driver seat button confirmation
 */
#define DRIVER_SEAT_PORT            PORTF
#define DRIVER_SEAT_PIN             PF0
#define DRIVER_SEAT_ID              (1U)
/*
 * co-driver seat button confirmation
 */
#define CO_DRIVER_SEAT_PORT         PORTF
#define CO_DRIVER_SEAT_PIN          PF4
#define CO_DRIVER_SEAT_ID           (2U)


#define DRIVER_ADC_PORT         ADC_PORTE
#define DRIVER_ADC_PIN          PE1
#define DRIVER_ADC_MODULE       ADC0

#define CO_DRIVER_ADC_PORT      ADC_PORTE
#define CO_DRIVER_ADC_PIN       PE1
#define CO_DRIVER_ADC_MODULE    ADC1

/*
 * tive c led configurations
 */

//driver heater seat leds
#define RED_LED_PORT_DRIVER_SEAT                PORTF
#define RED_LED_PIN_DRIVER_SEAT                 PF1

#define BLUE_LED_PORT_DRIVER_SEAT               PORTF
#define BLUE_LED_PIN_DRIVER_SEAT                PF2

#define GREEN_LED_PORT_DRIVER_SEAT              PORTF
#define GREEN_LED_PIN_DRIVER_SEAT               PF3


//co_driver heater seat leds
#define RED_LED_PORT_CO_DRIVER_SEAT             PORTA
#define RED_LED_PIN_CO_DRIVER_SEAT              PA1

#define BLUE_LED_PORT_CO_DRIVER_SEAT            PORTA
#define BLUE_LED_PIN_CO_DRIVER_SEAT             PA2

#define GREEN_LED_PORT_CO_DRIVER_SEAT           PORTA
#define GREEN_LED_PIN_CO_DRIVER_SEAT            PA3




#endif /* PROJECT_CFG_H_ */
