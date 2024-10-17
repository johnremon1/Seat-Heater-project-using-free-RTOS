# Seat-Heater-project-using-free-RTOS
this project is for control the set heater of a driver and the passenger sitting besides the driver using free RTOS  with TIVA C by TM4C123GH6PM Microcontroller 

Author Name: john Remon Maher 
before reading the following description i must confirm that nearly everything is configurable so you can change the priority of every task , change the stack size and nearly every task dependencies also you can change the periodicity of every task , the maximum time in blocking state , pins of the temperature sensor , the pins of LEDs and buttons  by the project_cfg.h file attached with the project
Project Document
Seat heater project using freeRTOS 
Every function services two tasks so with total of 10 task and the 11 task is the runtime measurements 

void ControllerTask(void *pvparameters);
-	this is the higher priority task in the systems 
-	stays in the blocked stat until an isr set an event flag this task activate and to its function 
-	the task function is to control the desired heater level to be low or medium or high or off or emergency 
-	this function has the authority to wake up the system as we suspend the temperature monitoring function when the heater is off to save the CPU load 

void TempratureMonitorTask(void *pvParameters);
-	the only periodic task in the system And it is considered the first activator of the chain of activation that will happens as every event happens the task rise an event flag the task after it 

-	this task start the adc conversion and wait for an event flag to be raised from the adc from the adc ISR and then decided if to activate the task after if which is the heater calculation task or not or raise and emergency if the temperature is out of rang 

-	the task decide to raise an event flag or not based on If there is a change happened from the last time we activated the next task or not is not change happened that is like the temprature did not changed from the last time the task was activated so the temperature monitor task will not raise the flag to activate the task after is which is heater calculation task 


void HeaterClaculationTask(void *pvparameters);
-	this is an event based task with lower priority than the temperature monitor 
-	this task decides whether to activate the next task or not based on If a change happened so the heater intensity should change based on that change in temperature 

void HeaterAdjustmentTask(void *pvparameters);
-	this task is event based task comes after the heater calculation task in the chain of tasks and considered the last one in the chain
-	this task is considered to be controller of the heater so every time the heater calculation task activate is as indication to change this task takes the decision of the hearer intensity 


void ScreenReportingTask(void *pvParameters);
-	this is an event based task 
-	activate based on any change happens in all the systems and has the lowest priority 
-	if any task changed any thing that could appear on the screen will set a flag after the change and the screen monitor will be refreshed 
void vRunTimeMeasurementsTask(void *pvParameters);
-	 this task only calculate the runtime measurements of every task and of the cpu load 


 
