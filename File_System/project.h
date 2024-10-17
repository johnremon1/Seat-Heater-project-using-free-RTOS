/*
 * project.h
 *
 *  Created on: Oct 9, 2024
 *      Author: John Remon
 */

/*what is the project.h ?
 * this is a way to define all the global variables and ENUMS and everything that could be in the upper part of the project source file
 * so the code is readable and divided in more than one file so it can be readable
 *
 * this file is part of file systems tree that you can find in the project description as a tree
 * as a conclusion instead of searching for the tree this file includes the project_cfg.h which includes the std_types.h
 *
 * the main project source file must include that file
 *
 * any user are not allowed to change in that file you can only change in the project_cfg.h file and the change will appear here if is is changeable
 */


#ifndef FILE_SYSTEM_PROJECT_H_
#define FILE_SYSTEM_PROJECT_H_


/**********************************************************************************************************
 *                                       #includes
 *********************************************************************************************************/

#include "Project_cfg.h"
#include "tm4c123gh6pm_registers.h"
#include "uart0.h"
#include "LED.h"
#include "BUTTON.h"
#include "ARM_ADC_DRIVER.h"
#include "DET.h"
#include "GPTM.h"



/**********************************************************************************************************
 *                                       type definitions
 *********************************************************************************************************/
typedef enum{
    HEATER_OFF ,
    HEATER_LOW  ,
    HEATER_MEDIUM,
    HEATER_HIGH,
    HEATER_ERROR
}HEATER_INTENSITY;

typedef enum{
    OFF_HEAT = 0,
    LOW_HEAT = 25,
    MEDIUM_HEAT = 30,
    HIGH_HEAT = 35
}DESIRED_LEVEL;



typedef struct
{
    uint8 id ;                                 //a way to differential between every seat
    uint8 seatTemp;                            // this variable to represent the actual temperature on the seat in any time
    DESIRED_LEVEL desiredLevel;                // this variable represents the heating level does the user choose from the panal
    HEATER_INTENSITY heaterLevel;                //this variable represents the heater intensity at any time
    uint8 TempratureSensorFailure ;             //a way to record the number of errors
    ADC_MODULE ADC_module ;

    SemaphoreHandle_t buttonSemaphore ;        //a counting semaphore to keep tracking of the button pressed by the isr
    SemaphoreHandle_t SeatMutix ;             //THIS MUTIX is to save every mutual exclusion the seat task can have

    EventGroupHandle_t Changes_Happened;

    TaskHandle_t  temperatureMointorTask_Handle ;
    TaskHandle_t  heaterCalculationTask_Handle ;
    TaskHandle_t  ControllerTask_Handle;
    TaskHandle_t  HeaterAdjustmentTask_Handle;
    TaskHandle_t  ScreenReportingTask_Handle;

} seat_structure;


/*********************************************************************************************************
 *                                          defenitions
 ********************************************************************************************************/

//tasks priorities

#define CONTROLLER_TASK_PRIORITY               4
#define TEMPRATURE_MONITOR_TASK_PRIORITY       3
#define HEATER_CALCULATION_TASK_PRIORITY       2
#define HEATER_ADJUSTMENT_TASK_PRIORITY        2
#define SCREEN_REPORTING_TASK_PRIORITY         1
#define RUNTIME_MEASUREMENTS_TASK_PRIORITY     1



#define SENSOR_MAX_VALUE                       45

#define TASK_STACK_SIZE                        300

//Event Group Bits
#define EVENT_GROUP_SCREEN_REPORTING_REFRESH_REQUIRED_BIT                 (1 << 0U)//this is for screen reporting for a change
#define EVENT_GROUP_HEATER_INTENSITY_SHOULD_CHANGE_BIT                    (1 << 1U) //this bit responsible for let the heater task start when the heat change and we need to change the heater intensity
#define EVENT_GROUP_ADC0_END_OF_CONVERSION_BIT                            (1 << 2U)
#define EVENT_GROUP_ADC1_END_OF_CONVERSION_BIT                            (1 << 3U)
#define EVENT_GROUP_HEAT_CALCULATION_TASK_START_BIT                       (1 << 4U)//this bit is to let the heater calculation task start
//mixed definitions

/*********************************************************************************************************
 *                                       Decelerations
 *********************************************************************************************************/

//driver seat structure deceleration
seat_structure driverSeat = { DRIVER_SEAT_ID       //this is only an id to differentiate between the two seats
                              ,30                  // the default value in the beginning of the system will  -- in the future that value will be taken from the EEPROM
                              ,OFF_HEAT        //the default desired heat until data is stored from EEPROM
                              ,HEATER_OFF          //the default Heater intensity
                              ,0
                              ,ADC0
};

//co_driver seat structure deceleration
seat_structure co_driverSeat ={ CO_DRIVER_SEAT_ID  //this is only an id to differentiate between the two seats
                               ,30                 // the default value in the beginning of the system will  -- in the future that value will be taken from the EEPROM
                               ,OFF_HEAT       //the default desired heat until data is stored from EEPROM
                               ,HEATER_OFF         //the default Heater intensity
                               ,0
                               ,ADC1
 };

xSemaphoreHandle UART_Mutix = NULL_PTR ;
TaskHandle_t runTimeMeasurementsTask_Handle = NULL_PTR ;

uint32 ullTasksOutTime[12];
uint32 ullTasksInTime[12];
uint32 ullTasksTotalTime[12];
uint32 ullTasksExecutionTime[12];



/* task Description
 *
 *
 */
void TempratureMonitorTask(void *pvParameters);



/* task Description
 *
 *
 */
void ControllerTask(void *pvparameters);



/* task Description
 *
 *
 */
void HeaterAdjustmentTask(void *pvparameters);


/* task Description
 *
 *
 */
void vRunTimeMeasurementsTask(void *pvParameters);


/* task Description
 *
 *
 */
void ScreenReportingTask(void *pvParameters);

/*
 *
 *
 */
void HeaterClaculationTask(void *pvparameters);



/* task Description
 *
 *
 */





/********************************************************************************************************
 *                                            function prototypes
 ********************************************************************************************************/



void PORTF_upperLayerCallBackFunction (uint8 driver_id);

void ADC0_upperLayerCallBackFunction(uint16 return_value);

void ADC1_upperLayerCallBackFunction(uint16 return_value);

void SystemWakeUp(seat_structure *user); // this will be function not task

static void prvSetupHardware( void );


void SystemShutDown(seat_structure *user);// this will be function not task

void vApplicationMallocFailedHook( void );

void vApplicationStackOverflowHook( TaskHandle_t xTask,char *pcTaskName );

void GPIO_PortF_SetCallBackFuntion( void(*functionHandler)(uint8 value)  );

#endif /* FILE_SYSTEM_PROJECT_H_ */







/* Notes for me
 *
 * -make sure to connect the external button as a PULL UP  to avoid a short circuit as the internal button is already coneccted PULL UP
 *  and the two button are on the same pin
 *
 *
 *
 *
 *
 *
 */

