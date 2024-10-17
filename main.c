#include "FreeRTOS.h"
#include "task.h"
//#include "queue.h"
#include "semphr.h"
#include "event_groups.h"


#include "project.h"



/* The HW setup function */


int main(void)
{
    uint8 taskCreationError = 0;

    UART_Mutix = xSemaphoreCreateMutex();//this is a mutex to control the access of the UART module
    if (UART_Mutix == NULL_PTR)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_SEMAPHORE_CREATE_RETRUN_NULL);
    }


    /* Setup the hardware for use with the Tiva C board. */
    prvSetupHardware();



    //FREE RTOS object creation section

    //this semaphore is for the interrupt handler to tell the task that button is pressed
    //this is a counting semaphore so that is more than one click is recorded
    driverSeat.buttonSemaphore = xSemaphoreCreateCounting( BUTTON_SEMAPHORE_MAX_COUNT  , 0 );
    if (driverSeat.buttonSemaphore == NULL_PTR)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_SEMAPHORE_CREATE_RETRUN_NULL);
    }
    co_driverSeat.buttonSemaphore = xSemaphoreCreateCounting( BUTTON_SEMAPHORE_MAX_COUNT , 0 );
    if (co_driverSeat.buttonSemaphore == NULL_PTR)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_SEMAPHORE_CREATE_RETRUN_NULL);
    }


    //this mutix to manage any mutual exclusion the seat task variables shared data need need
    driverSeat.SeatMutix = xSemaphoreCreateMutex();
    if ( driverSeat.SeatMutix == NULL_PTR)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_SEMAPHORE_CREATE_RETRUN_NULL);
    }
    co_driverSeat.SeatMutix = xSemaphoreCreateMutex();//any shared data for the
    if (co_driverSeat.SeatMutix == NULL_PTR)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_SEMAPHORE_CREATE_RETRUN_NULL);
    }





    //this event group is for the screen reporting task so it can only execute is a change happens to the data
    driverSeat.Changes_Happened = xEventGroupCreate() ;
    if (driverSeat.Changes_Happened == NULL_PTR)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_EVENT_GROUP_CREATE_RETRUN_NULL);
    }
    co_driverSeat.Changes_Happened = xEventGroupCreate() ;
    if (co_driverSeat.Changes_Happened == NULL_PTR)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_EVENT_GROUP_CREATE_RETRUN_NULL);
    }

#if(DEBUGGING_MOOD == STD_ON)
    xSemaphoreTake(UART_Mutix , portMAX_DELAY);
    UART0_SendString(" ___ done creating all FREE RTOS objects ___\r\n");
    xSemaphoreGive(UART_Mutix);
#endif

    // task creation sections


    taskCreationError = xTaskCreate(ControllerTask, "Driver_Controller Task" , TASK_STACK_SIZE ,(void *) &driverSeat, CONTROLLER_TASK_PRIORITY , &driverSeat.ControllerTask_Handle);
    if (taskCreationError == pdFAIL)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_TASK_CREATE_RETUN_PDFAIL);
    }
    taskCreationError = xTaskCreate(ControllerTask, "co_Drviver Controller Task" , TASK_STACK_SIZE ,(void *) &co_driverSeat , CONTROLLER_TASK_PRIORITY , &co_driverSeat.ControllerTask_Handle);
    if (taskCreationError == pdFAIL)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_TASK_CREATE_RETUN_PDFAIL);
    }

    /*creating the task that monitors the temperature on the seat of the driver
     * note that the two seats tasks will share the same function but different structures will be sent
     *
     */
    taskCreationError = xTaskCreate(TempratureMonitorTask, "Driver TempratureMonitorTask", TASK_STACK_SIZE ,(void *) &driverSeat, TEMPRATURE_MONITOR_TASK_PRIORITY  , &driverSeat.temperatureMointorTask_Handle);
    if (taskCreationError == pdFAIL)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_TASK_CREATE_RETUN_PDFAIL);
    }
    taskCreationError = xTaskCreate(TempratureMonitorTask, "CO_Driver TempratureMonitorTask", TASK_STACK_SIZE ,(void *)&co_driverSeat, TEMPRATURE_MONITOR_TASK_PRIORITY  , &co_driverSeat.temperatureMointorTask_Handle);
    if (taskCreationError == pdFAIL)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_TASK_CREATE_RETUN_PDFAIL);
    }


    //we gave the HeaterClaculationTask a handler because we will suspend it in the future
    taskCreationError = xTaskCreate(HeaterClaculationTask, "Driver HeaterClaculationTask ", TASK_STACK_SIZE ,(void *)&driverSeat, HEATER_CALCULATION_TASK_PRIORITY   , &driverSeat.heaterCalculationTask_Handle );
    if (taskCreationError == pdFAIL)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_TASK_CREATE_RETUN_PDFAIL);
    }
    taskCreationError = xTaskCreate(HeaterClaculationTask, "Co_Driver HeaterClaculationTask ", TASK_STACK_SIZE ,(void *)&co_driverSeat, HEATER_CALCULATION_TASK_PRIORITY   , &co_driverSeat.heaterCalculationTask_Handle );
    if (taskCreationError == pdFAIL)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_TASK_CREATE_RETUN_PDFAIL);
    }


    taskCreationError = xTaskCreate(HeaterAdjustmentTask , "Driver HeaterAdjustmentTask ", TASK_STACK_SIZE ,(void *)&driverSeat, HEATER_ADJUSTMENT_TASK_PRIORITY    ,  &driverSeat.HeaterAdjustmentTask_Handle );
    if (taskCreationError == pdFAIL)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_TASK_CREATE_RETUN_PDFAIL);
    }
    taskCreationError = xTaskCreate(HeaterAdjustmentTask , "CO_Driver HeaterAdjustmentTask ", TASK_STACK_SIZE ,(void *)&co_driverSeat, HEATER_ADJUSTMENT_TASK_PRIORITY    ,  &co_driverSeat.HeaterAdjustmentTask_Handle );
    if (taskCreationError == pdFAIL)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_TASK_CREATE_RETUN_PDFAIL);
    }


    taskCreationError = xTaskCreate(ScreenReportingTask, "Driver ScreenReportingTask", TASK_STACK_SIZE,(void *)&driverSeat, SCREEN_REPORTING_TASK_PRIORITY , &driverSeat.ScreenReportingTask_Handle);
    if (taskCreationError == pdFAIL)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_TASK_CREATE_RETUN_PDFAIL);
    }
    taskCreationError = xTaskCreate(ScreenReportingTask, "CO_Driver ScreenReportingTask", TASK_STACK_SIZE,(void *)&co_driverSeat, SCREEN_REPORTING_TASK_PRIORITY , &co_driverSeat.ScreenReportingTask_Handle);
    if (taskCreationError == pdFAIL)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_TASK_CREATE_RETUN_PDFAIL);
    }


    taskCreationError = xTaskCreate(vRunTimeMeasurementsTask, "Run time", TASK_STACK_SIZE, NULL, RUNTIME_MEASUREMENTS_TASK_PRIORITY, &runTimeMeasurementsTask_Handle);
    if (taskCreationError == pdFAIL)
    {
        DET_errorReporting(NO_TASK_ID, DET_ERROR_TASK_CREATE_RETUN_PDFAIL);
    }

   //runtime measurements configurations

    vTaskSetApplicationTaskTag(driverSeat.ControllerTask_Handle ,            ( TaskHookFunction_t ) 1 );
    vTaskSetApplicationTaskTag(co_driverSeat.ControllerTask_Handle ,         ( TaskHookFunction_t ) 2 );
    vTaskSetApplicationTaskTag(driverSeat.temperatureMointorTask_Handle ,    ( TaskHookFunction_t ) 3 );
    vTaskSetApplicationTaskTag(co_driverSeat.temperatureMointorTask_Handle , ( TaskHookFunction_t ) 4 );
    vTaskSetApplicationTaskTag(driverSeat.heaterCalculationTask_Handle ,     ( TaskHookFunction_t ) 5 );
    vTaskSetApplicationTaskTag(co_driverSeat.heaterCalculationTask_Handle ,  ( TaskHookFunction_t ) 6 );
    vTaskSetApplicationTaskTag(driverSeat.HeaterAdjustmentTask_Handle ,      ( TaskHookFunction_t ) 7 );
    vTaskSetApplicationTaskTag(co_driverSeat.HeaterAdjustmentTask_Handle ,   ( TaskHookFunction_t ) 8 );
    vTaskSetApplicationTaskTag(driverSeat.ScreenReportingTask_Handle ,       ( TaskHookFunction_t ) 9 );
    vTaskSetApplicationTaskTag(co_driverSeat.ScreenReportingTask_Handle ,    ( TaskHookFunction_t ) 10);
    vTaskSetApplicationTaskTag(runTimeMeasurementsTask_Handle ,              ( TaskHookFunction_t ) 11);


#if(DEBUGGING_MOOD == STD_ON)
    xSemaphoreTake(UART_Mutix , portMAX_DELAY);
    UART0_SendString(" ___done creating all the tasks with no errors___\r\n");
    UART0_SendString(" ___ vTaskStartScheduler() started___\r\n");
    xSemaphoreGive(UART_Mutix);
#endif


    vTaskStartScheduler();


}

static void prvSetupHardware( void )
{
#if (DEBUGGING_MOOD == STD_ON)
    xSemaphoreTake(UART_Mutix , portMAX_DELAY);
    UART0_SendString(" ___ done entering the prvSetupHardware  ___\r\n");
    xSemaphoreGive(UART_Mutix);
#endif
    //GPTM initialization
    GPTM_WTimer0Init();

    /* Explaining that function { BUTTON_SetCallBackFunction(PORTF_upperLayerCallBackFunction); }
     * as we know the app layer can not call the mcal layer direct so to achieve a call back function mechanism
     * without breaking the rules of layer architecture abstraction we had to send the address to the HAL layer and
     * then the HAL layer send it to the MCAL layer and by that we do not violate the principles
     */
    BUTTON_SetCallBackFunction(PORTF_upperLayerCallBackFunction);
    ADC0_SetCallBackFunction(ADC0_upperLayerCallBackFunction);
    ADC1_SetCallBackFunction(ADC1_upperLayerCallBackFunction);

    //ADC0 configurations for driver temperature sensor
    ADC_init(DRIVER_ADC_PORT, DRIVER_ADC_PIN  , DRIVER_ADC_MODULE );
    ADC_interruptEnable(DRIVER_ADC_PORT, DRIVER_ADC_PIN, DRIVER_ADC_MODULE, 6);

    //ADC1 configurations for driver temperature sensor
    ADC_init(CO_DRIVER_ADC_PORT, CO_DRIVER_ADC_PIN  , CO_DRIVER_ADC_MODULE );
    ADC_interruptEnable(CO_DRIVER_ADC_PORT, CO_DRIVER_ADC_PIN, CO_DRIVER_ADC_MODULE, 6);



    BUTTON_init(DRIVER_SEAT_PORT, DRIVER_SEAT_PIN);//Driver seat initialization
    BUTTON_pullDownEnable(DRIVER_SEAT_PORT, DRIVER_SEAT_PIN, ENABLE);//Enable the bull down on the switch
    BUTTON_interruptEnable(DRIVER_SEAT_PORT, DRIVER_SEAT_PIN , ENABLE, FALLING_EDGE , 6);//enable interrupt for the driver seat button

    BUTTON_init(CO_DRIVER_SEAT_PORT,CO_DRIVER_SEAT_PIN);// co-Driver seat initialization
    BUTTON_pullDownEnable(CO_DRIVER_SEAT_PORT, CO_DRIVER_SEAT_PIN, ENABLE);//Enable the bull down on the switch
    BUTTON_interruptEnable(CO_DRIVER_SEAT_PORT, CO_DRIVER_SEAT_PIN , ENABLE, FALLING_EDGE , 6 ); //enable interrupt for the co_driver seat button

    LED_init(GREEN_LED_PORT_DRIVER_SEAT, GREEN_LED_PIN_DRIVER_SEAT);
    LED_on(GREEN_LED_PORT_DRIVER_SEAT, GREEN_LED_PIN_DRIVER_SEAT);
    LED_init(BLUE_LED_PORT_DRIVER_SEAT, BLUE_LED_PIN_DRIVER_SEAT);
    LED_on(BLUE_LED_PORT_DRIVER_SEAT, BLUE_LED_PIN_DRIVER_SEAT);
    LED_init(RED_LED_PORT_DRIVER_SEAT, RED_LED_PIN_DRIVER_SEAT);
    LED_on(RED_LED_PORT_DRIVER_SEAT, RED_LED_PIN_DRIVER_SEAT);

    LED_init(GREEN_LED_PORT_CO_DRIVER_SEAT , GREEN_LED_PIN_CO_DRIVER_SEAT);
    LED_on(GREEN_LED_PORT_CO_DRIVER_SEAT, GREEN_LED_PIN_CO_DRIVER_SEAT);
    LED_init(BLUE_LED_PORT_CO_DRIVER_SEAT, BLUE_LED_PIN_CO_DRIVER_SEAT);
    LED_on(BLUE_LED_PORT_CO_DRIVER_SEAT, BLUE_LED_PIN_CO_DRIVER_SEAT);
    LED_init(RED_LED_PORT_CO_DRIVER_SEAT, RED_LED_PIN_CO_DRIVER_SEAT);
    LED_on(RED_LED_PORT_CO_DRIVER_SEAT, RED_LED_PIN_CO_DRIVER_SEAT);


#if (DEBUGGING_MOOD == STD_ON)
    xSemaphoreTake(UART_Mutix , portMAX_DELAY);
    UART0_SendString("___Done initiating LEDs and buttons and call back function__\r\n");
    xSemaphoreGive(UART_Mutix);
#endif

}

/*task description
 * this is a periodic tasks that check the value of the temperature sensor every predefined periodic time and update the member in the
 * user structure with the new temperature
 *
 * why we did not sent the temperature to the queue by that task and we did it by another task ???
 * 1- if a failure happened and the queue is full then the heater will not be shut down immediately
 * 2- if the queue is empty then most probably the temperature we are looping on a queue in case we make the delay of it zero then
 *    we will be looping and take the CPU LOAD
 * 3- making this task as short as possible is very important as it is the higher priority task so it must end very quickly
 * 4- this task has the ability to shut down the heater until the temperature range is in the normal range and that authority can not ber
 *    given to more than one task and can not be given to a lower priority task
 *
 * a.Off: The feature is off, and the temperature is not controlled.
 * b.Low: the desired temperature is 25°C.
 * c.Medium: the desired temperature is 30°C.
 * d.High: the desired temperature is 35°C.
 *
 *
 */
void TempratureMonitorTask(void *pvParameters)
{
    seat_structure* user = (seat_structure*)(pvParameters);//using the seat structure to know in which task are we in

    TickType_t xLastWakeTime = xTaskGetTickCount();//making variable for vtaskDelayUntil so this function resume periodically

    uint8 previousTemp = 0 ;


#if (DEBUGGING_MOOD == STD_ON)
    xSemaphoreTake(UART_Mutix , portMAX_DELAY);
    UART0_SendString("___done entering Temperature Monitor Task for the first time for user id : ");
    UART0_SendInteger(user->id);
    UART0_SendString("___\r\n");
    xSemaphoreGive(UART_Mutix);
#endif



    while(1)
    {
        if (user->id == DRIVER_SEAT_ID)
        {
           user->seatTemp = ADC_u16ReadData(DRIVER_ADC_PORT, DRIVER_ADC_PIN, ADC0);
           if ( ! ((xEventGroupWaitBits(driverSeat.Changes_Happened, EVENT_GROUP_ADC0_END_OF_CONVERSION_BIT, pdTRUE, pdTRUE,  MAX_TIME_IN_BLOCKING_STATE_MS)) &  (EVENT_GROUP_ADC0_END_OF_CONVERSION_BIT) ) )
           {
               DET_errorReporting(TEMPRATURE_MONITOR_TASK_ERROR_ID, DET_ERROR_EVENT_GROUP_BIT_NOT_SET);

           }
#if (DEBUGGING_MOOD == STD_ON)
            xSemaphoreTake(UART_Mutix , portMAX_DELAY);
            UART0_SendString(" ___ TempratureMonitorTask-> after waiting for driver seat adc to end of conversion the conversion ended ___\r\n");
            xSemaphoreGive(UART_Mutix);
#endif

        }
        else if (user->id == CO_DRIVER_SEAT_ID)
        {
            user->seatTemp = ADC_u16ReadData(CO_DRIVER_ADC_PORT, CO_DRIVER_ADC_PIN, ADC1);
            //if ( ! ((xEventGroupWaitBits(co_driverSeat.Changes_Happened, EVENT_GROUP_ADC1_END_OF_CONVERSION_BIT, pdTRUE, pdTRUE,  MAX_TIME_IN_BLOCKING_STATE_MS)) &  (EVENT_GROUP_ADC1_END_OF_CONVERSION_BIT) ) )
           // {
            //    DET_errorReporting(TEMPRATURE_MONITOR_TASK_ERROR_ID, DET_ERROR_EVENT_GROUP_BIT_NOT_SET);

           // }
#if (DEBUGGING_MOOD == STD_ON)
                xSemaphoreTake(UART_Mutix , portMAX_DELAY);
            UART0_SendString(" ___ TempratureMonitorTask-> after waiting for co_driver seat adc to end of conversion the conversion ended ___\r\n");
            xSemaphoreGive(UART_Mutix);
#endif

        }

        /*if an error happens in the temperature and the sensor got out of range an error must me reported and the
         * seat heater must be shut down immediately
         *
         */
#if (DEBUGGING_MOOD == STD_ON)
        xSemaphoreTake(UART_Mutix , portMAX_DELAY) ;
        UART0_SendString("__ done entering the while(1) of temperature monitoring task __\r\n");
        xSemaphoreGive(UART_Mutix);
#endif

        if ( (user->seatTemp < 5) || (user->seatTemp > 40) )
        {

#if (DEBUGGING_MOOD == STD_ON)
            xSemaphoreTake(UART_Mutix , portMAX_DELAY) ;
            UART0_SendString("__ Temperature out of range so DEM error reporting __\r\n");
            xSemaphoreGive(UART_Mutix);
#endif
            user->TempratureSensorFailure = TRUE ;
            xEventGroupSetBits(user->Changes_Happened, EVENT_GROUP_SCREEN_REPORTING_REFRESH_REQUIRED_BIT);//this is for the screen reproting for an error
            //user->numberOfNonReportedErrors++ ;this could be a counting semaphore
            // DET_errorReporting(TEMPRATURE_MONITOR_TASK_ERROR_ID, DET_ERROR_TEMEPRATURE_SENSOR_OF_RANGE_FAILURE)// this error must be reported to the EEPROM
        }else
        {

            if ( previousTemp != user->seatTemp)
            {
                user->TempratureSensorFailure = FALSE ;
                 previousTemp =  user->seatTemp ;
                xEventGroupSetBits(user->Changes_Happened, EVENT_GROUP_SCREEN_REPORTING_REFRESH_REQUIRED_BIT);//this is for the screen reporting as the screen task will only execute in case of change
                xEventGroupSetBits(user->Changes_Happened, EVENT_GROUP_HEAT_CALCULATION_TASK_START_BIT);
            }
        }
        vTaskDelayUntil( &xLastWakeTime , pdMS_TO_TICKS(TEMPRATURE_MONITOR_PERIODIC_TIME_MS));
    }
}


void ControllerTask(void *pvparameters)
{
    seat_structure *user = (seat_structure *)(pvparameters);//using the seat structure to know in which task are we in

    while(1)
    {
        //this semaphore is given by the ISR so the controller task work only when the user pressthe button
        //that is explaining the portMAX_DELAY

        xSemaphoreTake(user->buttonSemaphore,portMAX_DELAY);

        if (xSemaphoreTake(user->SeatMutix,MAX_TIME_IN_BLOCKING_STATE_MS) == pdPASS)
        {
#if (DEBUGGING_MOOD == STD_ON)
    xSemaphoreTake(UART_Mutix , portMAX_DELAY);
    UART0_SendString(" ___ done entering the controller task after a button is pressed  ___\r\n");
    xSemaphoreGive(UART_Mutix);
#endif

            switch ( user->desiredLevel ) {
            case OFF_HEAT:
                user->desiredLevel = LOW_HEAT ;//we will go to wake up task that resumes all tasks in the system
                SystemWakeUp(user);
                break;
            case LOW_HEAT:
                user->desiredLevel = MEDIUM_HEAT ;
                break;
            case MEDIUM_HEAT:
                user->desiredLevel = HIGH_HEAT ;
                break;
            case HIGH_HEAT:
                user->desiredLevel = OFF_HEAT ;

                break;
            default:
                DET_errorReporting(CONTROLLER_TASK_ERROR_ID, DET_ERROR_CONTROLLER_TASK_WRONG_INPUT);
                break;

            }
            xSemaphoreGive(user->SeatMutix);
        }
    }

}


void HeaterClaculationTask(void *pvparameters)
{
    seat_structure *user = (seat_structure *) pvparameters ;
    uint8 temperatureDifference = 0 ;
    uint8 HeaterNewIntensity = 0 ;

    while(1)
    {

        xEventGroupWaitBits(user->Changes_Happened, EVENT_GROUP_HEAT_CALCULATION_TASK_START_BIT, pdTRUE, pdTRUE, portMAX_DELAY);

        //we must protect that critical section that have shared data
        if( xSemaphoreTake( user->SeatMutix , HEATER_CALCULATION_TASK_BLOCKING_DELAY_TIME_MS ) == pdPASS )
        {
#if (DEBUGGING_MOOD == STD_ON)
            xSemaphoreTake(UART_Mutix , portMAX_DELAY);
            UART0_SendString(" ___ done entering the HeaterClaculationTask ___\r\n");
            xSemaphoreGive(UART_Mutix);
#endif

            if (user->TempratureSensorFailure == TRUE  )
            {
                HeaterNewIntensity = HEATER_ERROR ;

            }
            else if ( (user->desiredLevel) > (user->seatTemp) )
            {
                temperatureDifference = (user->desiredLevel - user->seatTemp) ;
                if (temperatureDifference >= 10)
                {
                    HeaterNewIntensity = HEATER_HIGH ;
                }
                else if (temperatureDifference >= 5 )
                {
                    HeaterNewIntensity = HEATER_MEDIUM ;
                }
                else if  (temperatureDifference >= 2 )
                {
                    HeaterNewIntensity = HEATER_LOW ;
                }
                else
                {
                    HeaterNewIntensity = HEATER_OFF ;//that means that the temperature difference is 1 or 0 which will also turn the heater off
                }

            }
            else
            {
                HeaterNewIntensity = HEATER_OFF ;//that means that the seat heat is bigger than the desired temperature which will also turn the heater off
            }


            if (user->heaterLevel != HeaterNewIntensity)
            {
#if (DEBUGGING_MOOD == STD_ON)
                xSemaphoreTake(UART_Mutix , portMAX_DELAY);
                UART0_SendString(" ___ the user->heaterLevel so an event is raised so the HeaterAdjustmentTask must start  ___\r\n");
                xSemaphoreGive(UART_Mutix);
#endif

                xEventGroupSetBits(user->Changes_Happened, EVENT_GROUP_HEATER_INTENSITY_SHOULD_CHANGE_BIT);
            }

        }

    }

}



void HeaterAdjustmentTask(void *pvparameters)
{
    seat_structure *user = (seat_structure *) pvparameters ;
#if (DEBUGGING_MOOD == STD_ON)
    xSemaphoreTake(UART_Mutix , portMAX_DELAY);
    UART0_SendString("__done entering the Heater Adjustment Task for the first time__ \r\n ");
    xSemaphoreGive(UART_Mutix);
#endif

    while(1)
    {
        xEventGroupWaitBits(user->Changes_Happened, EVENT_GROUP_HEATER_INTENSITY_SHOULD_CHANGE_BIT , pdTRUE, pdTRUE , portMAX_DELAY);
#if (DEBUGGING_MOOD == STD_ON)
        xSemaphoreTake(UART_Mutix , portMAX_DELAY);
        UART0_SendString("__done entering the Heater Adjustment Task while(1){} and and event flag is raised__ \r\n ");
        xSemaphoreGive(UART_Mutix);
#endif
        switch ( user->heaterLevel )
        {
        case HEATER_HIGH:
            if (user->id == DRIVER_SEAT_ID)
            {
                LED_on(GREEN_LED_PORT_DRIVER_SEAT, GREEN_LED_PIN_DRIVER_SEAT);
                LED_on(BLUE_LED_PORT_DRIVER_SEAT, BLUE_LED_PIN_DRIVER_SEAT);
                LED_off(RED_LED_PORT_DRIVER_SEAT, RED_LED_PIN_DRIVER_SEAT);
            }
            else if (user->id == CO_DRIVER_SEAT_ID)
            {
                LED_on(GREEN_LED_PORT_CO_DRIVER_SEAT, GREEN_LED_PIN_CO_DRIVER_SEAT);
                LED_on(BLUE_LED_PORT_CO_DRIVER_SEAT, BLUE_LED_PIN_CO_DRIVER_SEAT);
                LED_off(RED_LED_PORT_CO_DRIVER_SEAT,  RED_LED_PIN_CO_DRIVER_SEAT);
            }
            else
            {
                // do nothing
            }

            break;
        case HEATER_MEDIUM:
            if (user->id == DRIVER_SEAT_ID)
            {
                LED_off(GREEN_LED_PORT_DRIVER_SEAT, GREEN_LED_PIN_DRIVER_SEAT);
                LED_on(BLUE_LED_PORT_DRIVER_SEAT, BLUE_LED_PIN_DRIVER_SEAT);
                LED_off(RED_LED_PORT_DRIVER_SEAT,  RED_LED_PIN_DRIVER_SEAT);

            }
            else if (user->id == CO_DRIVER_SEAT_ID)
            {
                LED_off(GREEN_LED_PORT_CO_DRIVER_SEAT, GREEN_LED_PIN_CO_DRIVER_SEAT);
                LED_on(BLUE_LED_PORT_CO_DRIVER_SEAT, BLUE_LED_PIN_CO_DRIVER_SEAT);
                LED_off(RED_LED_PORT_CO_DRIVER_SEAT,  RED_LED_PIN_CO_DRIVER_SEAT);

            }
            else
            {
                //error reporting
            }

            break;
        case HEATER_LOW:
            if (user->id == DRIVER_SEAT_ID)
            {
                LED_on(GREEN_LED_PORT_DRIVER_SEAT, GREEN_LED_PIN_DRIVER_SEAT);
                LED_off(BLUE_LED_PORT_DRIVER_SEAT, BLUE_LED_PIN_DRIVER_SEAT);
                LED_off(RED_LED_PORT_DRIVER_SEAT,  RED_LED_PIN_DRIVER_SEAT);
            }
            else if (user->id == CO_DRIVER_SEAT_ID)
            {
                LED_on(GREEN_LED_PORT_CO_DRIVER_SEAT, GREEN_LED_PIN_CO_DRIVER_SEAT);
                LED_off(BLUE_LED_PORT_CO_DRIVER_SEAT, BLUE_LED_PIN_CO_DRIVER_SEAT);
                LED_off(RED_LED_PORT_CO_DRIVER_SEAT,  RED_LED_PIN_CO_DRIVER_SEAT);
            }
            else
            {
                //error reporting
            }

            break;
        case HEATER_OFF:
            if (user->id == DRIVER_SEAT_ID)
            {
                LED_off(GREEN_LED_PORT_DRIVER_SEAT, GREEN_LED_PIN_DRIVER_SEAT);
                LED_off(BLUE_LED_PORT_DRIVER_SEAT, BLUE_LED_PIN_DRIVER_SEAT);
                LED_off(RED_LED_PORT_DRIVER_SEAT,  RED_LED_PIN_DRIVER_SEAT);

            }
            else if (user->id == CO_DRIVER_SEAT_ID)
            {
                LED_off(GREEN_LED_PORT_CO_DRIVER_SEAT, GREEN_LED_PIN_CO_DRIVER_SEAT);
                LED_off(BLUE_LED_PORT_CO_DRIVER_SEAT, BLUE_LED_PIN_CO_DRIVER_SEAT);
                LED_off(RED_LED_PORT_CO_DRIVER_SEAT,  RED_LED_PIN_CO_DRIVER_SEAT);
            }
            /*what is SystemShutDown(user);
             * this function suspends temperature monitor task and heater calculation task becuase these two task
             * are periodic tasks so the other two task (screen reporting task and heater controller task ) will not
             * execute as they are event based task based on the two periodic tasks that has been susbended
             * only the controller task and the runtime task and the error reporting task will be on and that is for
             * reducing the CPU load when the heater is off
             */

            if (user->desiredLevel == OFF_HEAT)
            {
                SystemShutDown(user);
            }

            break;
        case HEATER_ERROR:
            if (user->id == DRIVER_SEAT_ID)
            {
                LED_off(GREEN_LED_PORT_DRIVER_SEAT, GREEN_LED_PIN_DRIVER_SEAT);
                LED_off(BLUE_LED_PORT_DRIVER_SEAT, BLUE_LED_PIN_DRIVER_SEAT);
                LED_on(RED_LED_PORT_DRIVER_SEAT,  RED_LED_PIN_DRIVER_SEAT);

            }
            else if (user->id == DRIVER_SEAT_ID)
            {
                LED_off(GREEN_LED_PORT_CO_DRIVER_SEAT, GREEN_LED_PIN_CO_DRIVER_SEAT);
                LED_off(BLUE_LED_PORT_CO_DRIVER_SEAT, BLUE_LED_PIN_CO_DRIVER_SEAT);
                LED_on(RED_LED_PORT_CO_DRIVER_SEAT,  RED_LED_PIN_CO_DRIVER_SEAT);
            }
            else
            {
                //error reporting
            }

            break;
            //default :

            //   DET_errorReporting(taskid, errorId)

        }
    }
}



void ScreenReportingTask(void *pvparameters)
{
    seat_structure *user = (seat_structure *) pvparameters ;


    while(1)
    {
        xEventGroupWaitBits(user->Changes_Happened, EVENT_GROUP_SCREEN_REPORTING_REFRESH_REQUIRED_BIT, pdTRUE, pdTRUE, portMAX_DELAY)  ;

        if (xSemaphoreTake(UART_Mutix,MAX_TIME_IN_BLOCKING_STATE_MS) == pdTRUE )
        {
            if (user->TempratureSensorFailure == TRUE)
            {
                if (user->id == DRIVER_SEAT_ID)
                {
                    UART0_SendString("ERROR __ there is failure in driver seat temperature sensor \r\n");
                }
                else if (user->id == CO_DRIVER_SEAT_ID)
                {
                    UART0_SendString("ERROR __ there is failure in co_driver seat temperature sensor \r\n");
                }
            }
            else if (user->id == DRIVER_SEAT_ID)
            {
                UART0_SendString("Driver Seat Screen Reporting \r\n");

            }
            else if (user->id == CO_DRIVER_SEAT_ID)
            {
                UART0_SendString("CO_Driver Seat Screen Reporting \r\n");
            }
            else
            {
                //error reporting
            }
            UART0_SendString("seat temperature is ");
            UART0_SendByte(user->seatTemp);
            UART0_SendString("/r/n Desired heat level is  ");
            switch (user->desiredLevel) {
            case OFF_HEAT:
                UART0_SendString("( OFF )") ;
                break;
            case LOW_HEAT:
                UART0_SendString("( LOW )") ;
                break;
            case MEDIUM_HEAT:
                UART0_SendString("( MEDIUM )") ;
                break;
            case HIGH_HEAT:
                UART0_SendString("( HIGH )") ;
                break;
            default:
                break;
            }
            UART0_SendString("/r/n");
            xSemaphoreGive(UART_Mutix);
        }
    }


}



void PORTF_upperLayerCallBackFunction(uint8 driver_id)
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    if (driver_id == DRIVER_SEAT_ID && driverSeat.buttonSemaphore != NULL)
    {
        xSemaphoreGiveFromISR(driverSeat.buttonSemaphore, &pxHigherPriorityTaskWoken);
    }
    else if (driver_id == CO_DRIVER_SEAT_ID && co_driverSeat.buttonSemaphore != NULL)
    {
        xSemaphoreGiveFromISR(co_driverSeat.buttonSemaphore, &pxHigherPriorityTaskWoken);
    }
    portYIELD_FROM_ISR( pxHigherPriorityTaskWoken );

}




void ADC0_upperLayerCallBackFunction(uint16 return_value)
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;

    driverSeat.seatTemp = (float)return_value * (SENSOR_MAX_VALUE / 4095.0f) ;
    xEventGroupSetBitsFromISR(driverSeat.Changes_Happened, EVENT_GROUP_ADC0_END_OF_CONVERSION_BIT , &pxHigherPriorityTaskWoken);

    portYIELD_FROM_ISR( pxHigherPriorityTaskWoken );

}



void ADC1_upperLayerCallBackFunction(uint16 return_value)
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;

    co_driverSeat.seatTemp = (float)return_value * (SENSOR_MAX_VALUE / 4095.0f) ;
    xEventGroupSetBitsFromISR(co_driverSeat.Changes_Happened,EVENT_GROUP_ADC1_END_OF_CONVERSION_BIT , &pxHigherPriorityTaskWoken);
    portYIELD_FROM_ISR( pxHigherPriorityTaskWoken );
}

void vRunTimeMeasurementsTask(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        uint8 ucCounter, ucCPU_Load;
        uint32 ullTotalTasksTime = 0;
        vTaskDelayUntil(&xLastWakeTime,  RUNTIME_MEASUREMENTS_TASK_PERIODICITY);
        for(ucCounter = 1; ucCounter < 12; ucCounter++)
        {
            ullTotalTasksTime += ullTasksTotalTime[ucCounter];
        }
        ucCPU_Load = (ullTotalTasksTime * 100) /  GPTM_WTimer0Read();

        if(xSemaphoreTake(UART_Mutix,MAX_TIME_IN_BLOCKING_STATE_MS)==pdTRUE)
        {
            UART0_SendString("CPU Load is ");
            UART0_SendInteger(ucCPU_Load);
            UART0_SendString("% \r\n");
            for(ucCounter = 1; ucCounter < 12; ucCounter++)
            {
                UART0_SendString("TAG NUMBER");
                UART0_SendByte(ucCounter);
                UART0_SendString("execution time is ");
                UART0_SendInteger(ullTasksExecutionTime[ucCounter] / 10);
                UART0_SendString(" msec \r\n");
            }

            xSemaphoreGive(UART_Mutix);

        }

    }
}

/*what is SystemShutDown(user);
 * this function suspends temperature monitor task and heater calculation task becuase these two task
 * are periodic tasks so the other two task (screen reporting task and heater controller task ) will not
 * execute as they are event based task based on the two periodic tasks that has been susbended
 * only the controller task and the runtime task and the error reporting task will be on and that is for
 * reducing the CPU load when the heater is off
 */
void SystemShutDown(seat_structure *user)
{
    vTaskSuspend(user->temperatureMointorTask_Handle);
#if (DEBUGGING_MOOD == STD_ON)
    xSemaphoreTake(UART_Mutix , portMAX_DELAY);
    UART0_SendString(" ___ done system shut down  ___\r\n");
    xSemaphoreGive(UART_Mutix);
#endif
}


/*what SystemWakeUp(seat_structure *user);
 * this function resumes the temperature monitor task and the heater calculation task so because of the the other two
 * event based function will resumes they are event based on vents happens in the two periodic tasks that has been
 * resumed
 */
void SystemWakeUp(seat_structure *user)
{
    vTaskResume(user->temperatureMointorTask_Handle);
#if (DEBUGGING_MOOD == STD_ON)
    xSemaphoreTake(UART_Mutix , portMAX_DELAY);
    UART0_SendString(" ___ done system wake up  ___\r\n");
    xSemaphoreGive(UART_Mutix);
#endif
}



