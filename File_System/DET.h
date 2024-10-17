/*
 * Det.h
 *
 *  Created on: Oct 9, 2024
 *      Author: johnr
 */

#ifndef FILE_SYSTEM_DET_H_
#define FILE_SYSTEM_DET_H_


#include "project_cfg.h"

/**********************************************************************************************************
 *                                       error reporting section
 *********************************************************************************************************/

#define NO_TASK_ID                                       (0U)

#define TEMPRATURE_MONITOR_TASK_ERROR_ID                 (1U)

#define HEATER_ADJUSTMENT_TASK_ERROR_ID                  (2U)

#define RUNTIME_MEASURMENT_TASK_ERROR_ID                 (3U)

#define SCREEN_REPORTING_TASK_ERROR_ID                   (4U)

#define CONTROLLER_TASK_ERROR_ID                         (5U)

#define HEATER_CALCULATION_TASK_ERROR_ID                 (6U)





//ERRORS

#define DET_ERROR_SEMAPHORE_CREATE_RETRUN_NULL               (0U)
#define DET_ERROR_TASK_CREATE_RETUN_PDFAIL                   (1U)
#define DET_ERROR_TEMPERATURE_SENSOR_OF_RANGE_FAILURE        (2U) // this error must be logged to the EEPROM
#define DET_ERROR_EVENT_GROUP_CREATE_RETRUN_NULL             (3U)
#define DET_ERROR_CONTROLLER_TASK_WRONG_INPUT                (4U)
#define DET_ERROR_EVENT_GROUP_BIT_NOT_SET                    (5U)//this happens if the xEventgroupwaitbit has time out with out the bit was set because of time out



void DET_errorReporting(uint8 taskid , uint8 errorId);


#endif /* FILE_SYSTEM_DET_H_ */
