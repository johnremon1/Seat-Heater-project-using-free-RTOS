/*
 * Det.c
 *
 *  Created on: Oct 9, 2024
 *      Author: johnr
 */
#include "DET.h"




void DET_errorReporting(uint8 taskid , uint8 errorId)
{
    switch (errorId)
    {
    case DET_ERROR_SEMAPHORE_CREATE_RETRUN_NULL :
      //  while(1);

        break;
    case DET_ERROR_TASK_CREATE_RETUN_PDFAIL:
       // while(1);

        break;
    case DET_ERROR_TEMPERATURE_SENSOR_OF_RANGE_FAILURE:
       // while(1);

        break;
    case DET_ERROR_EVENT_GROUP_CREATE_RETRUN_NULL :
       // while(1);

        break;
    case DET_ERROR_CONTROLLER_TASK_WRONG_INPUT:
       // while(1);

        break;
    case DET_ERROR_EVENT_GROUP_BIT_NOT_SET :
       // while(1);

        break;

    }

}
