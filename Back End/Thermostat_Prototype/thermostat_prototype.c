// Last modified by Kelsey Stokes 02/11/2022

/*
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== thermostat_prototype.c ========
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>




// Driver Header files
#include <ti/drivers/Timer.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>


// Driver configuration
#include "ti_drivers_config.h"

/*
 * ======= Global variables =======
 */

// I2C global variables
uint8_t sensorAddress;         // Temperature sensor address
uint8_t sensorReg;             // Sensor register
uint8_t txBuffer[1];           // Transmitting buffer
uint8_t rxBuffer[2];           // Receiving buffer
I2C_Transaction i2cTransaction;

int16_t setPoint;              // temperature the thermostat is set to
int16_t tempReading;           // temperature read by sensor (room temp)
bool heat = false;             // bool set to true when heat is on
bool ac = false;               // bool set to true when A/C is on

// Struct type for task info
typedef struct task {
   int state;                  // Task state
   unsigned long period;       // Task period
   unsigned long elapsedTime;  // Time elapsed since last task tick
   void (*TickFct)(void);      // Task tick function
} task;

// Struct type for date and time
typedef struct Timestamps {
    int min;
    int hr;


} Timestamp;

// tasks array
task tasks[4];


// Driver Handles
I2C_Handle i2c;
Timer_Handle timer0;

// Timer & button flags
volatile unsigned char TimerFlag = 0;     // Timer flag
volatile unsigned char ButtonFlag0 = 0;   // Set point decrease flag
volatile unsigned char ButtonFlag1 = 0;   // Set point increase flag
volatile unsigned char TempFlag = 0;      // Temp check flag

// Timers
volatile float timer = 0;            // Overall seconds counter
volatile float heatTimer = 0;           // Heat timer
volatile float acTimer = 0;             // A/C timer

// Heat and A/C hour variables
volatile float heatHours = 0;
volatile float acHours = 0;

/*
 * ======= timerCallback =======
 */
void timerCallback(Timer_Handle myHandle, int_fast16_t status)
{
    TimerFlag = 1;                          // Raise the timer flag
    unsigned int tasksCount;
    tasksCount = sizeof(tasks) / sizeof(tasks[0]);    // Get number of tasks
    const unsigned long tasksPeriodGCD = 100;   // Greatest Common Divisor of all tasks in ms

    unsigned int i;
    for (i = 0; i < tasksCount; ++i) { // Heart of the scheduler code
        if (tasks[i].elapsedTime >= tasks[i].period) { // Ready
            tasks[i].elapsedTime = 0;
            if (tasks[i].TickFct) {     // Check for non-NULL function
                tasks[i].TickFct();
            }
        }
        tasks[i].elapsedTime += tasksPeriodGCD;
    }
}

/*
 *  ======== gpioButtonFxn0 ========
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_0.
 *
 *  Note: GPIO interrupts are cleared prior to invoking callbacks.
 */
void gpioButtonFxn0(uint_least8_t index)
{
    // Raise Button0 flag
    ButtonFlag0 = 1;

}

/*
 *  ======== gpioButtonFxn1 ========
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_1.
 *
 *  Note: GPIO interrupts are cleared prior to invoking callbacks.
 */
void gpioButtonFxn1(uint_least8_t index)
{
    // Raise Button1 flag
    ButtonFlag1 = 1;

}

/*
 * ======= initTimer =======
 */
void initTimer(void) {
    Timer_Params params;

    // Initialize the timer driver
    Timer_init();

    // Configure the driver
    Timer_Params_init(&params);
    params.period = 100000;                         // Sets the timer period to 100 ms
    params.timerMode = Timer_CONTINUOUS_CALLBACK;   // Callback mode is continuous
    params.periodUnits = Timer_PERIOD_US;           // Timer period units is microseconds
    params.timerCallback = timerCallback;           // The defined timer callback function

    // Open the driver
    timer0 = Timer_open(CONFIG_TIMER_0, &params);

    if (timer0 == NULL) {
        printf("Failed to initialize timer.\n\r");
        while (1) {}    // Failed to initialize timer

    }

    if (Timer_start(timer0) == Timer_STATUS_ERROR) {
        printf("Failed to start timer.\n\r");
        while (1) {}    // Failed to start timer

    }

}



/*
 * ======= initI2C =======
 */
void initI2C(void) {

    I2C_Params  i2cParams;
    sensorAddress = 0x41;       // Assigns the temperature sensor's address
    sensorReg = 0x0001;         // Assigns the sensor's register

    // Init the driver
    I2C_init();

    // Configure the driver
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;

    // Open the driver
    i2c = I2C_open(CONFIG_I2C_0, &i2cParams);
    if (i2c == NULL) {
        while (1);      // Driver failed to open
    }

    // I2C transaction setup
    i2cTransaction.writeBuf = txBuffer;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readBuf = rxBuffer;
    i2cTransaction.readCount = 0;
    i2cTransaction.slaveAddress = sensorAddress;
    txBuffer[0] = sensorReg;

}

/*
 * ======= boardConfig =======
 */
void boardConfig(void) {

    // Configure the button pins
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);    // Button to lower set temp
    GPIO_setConfig(CONFIG_GPIO_BUTTON_1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);    // Button to raise set temp


    // Install Button callbacks
    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, gpioButtonFxn0);
    GPIO_setCallback(CONFIG_GPIO_BUTTON_1, gpioButtonFxn1);


    // Enable interrupts
    GPIO_enableInt(CONFIG_GPIO_BUTTON_0);
    GPIO_enableInt(CONFIG_GPIO_BUTTON_1);
}



/*
 * ======= dataDump =======
 */
void dataDump(void) {

    // convert seconds of usage to hours
    heatHours = heatTimer / 3600;
    acHours = acTimer / 3600;

    // Write to the .csv (overwriting existing contents)
    char const *fileName = "C:\\Users\\kelse\\OneDrive\\Documents\\NetBeansProjects\\sendData\\data.csv";
    FILE *f = fopen(fileName, "w");
    if(f == NULL) {
        printf("File error\n");
    }
    fprintf(f, "%.2f,%.2f\n", acHours, heatHours);
    fclose(f);


}

/*
 * ======= counterReset =======
 */

void counterReset(void) {

    // reset seconds timers
    timer = 0;
    heatTimer = 0;
    acTimer = 0;

    // reset usage hours
    heatHours = 0.00;
    acHours = 0.00;
}

/*
 * ======= getTime =======
 */
Timestamp getTime(void) {

    Timestamp timestamp;

    time_t rawTime;
    struct tm* timeInfo;

    // char arrays (strings) for each part of the date
    char hourStr[80];
    char minuteStr[80];
    char timeZone[80];

    // Get the local time
    time(&rawTime);
    timeInfo = localtime(&rawTime);

    // Store each part of the date and time in its own string for later comparison
    strftime(hourStr, 80, "%H", timeInfo);
    strftime(minuteStr, 80, "%M", timeInfo);
    strftime(timeZone, 80, "%Z", timeInfo);

    // Add each element to the timestamp
    timestamp.hr = atoi(hourStr);
    timestamp.min = atoi(minuteStr);    // convert to int for easier comparison

    // The microcrontroller cannot be changed from CST so correct hour for local time
    if(timestamp.hr == 23) {
        timestamp.hr = 0;
    }
    else {
        timestamp.hr += 1;
    }

    return timestamp;
}

/*
 * ======= TickFct_CheckButtons =======
 */
void TickFct_CheckButtons(void) {

    // Check the status of each button flag
    if (ButtonFlag0) {
        setPoint -= 1;      // Decrease the setPoint by 1
        ButtonFlag0 = 0;    // Lower Button0 flag
    }
    else if (ButtonFlag1) {
        setPoint += 1;      // Increase the setPoint by 1
        ButtonFlag1 = 0;    // Lower the button flag
    }
}

/*
 * ======= TickFct_CheckTemp =======
 */
void TickFct_CheckTemp(void) {

    // Raise the TempFlag
    TempFlag = 1;
}

/*
 * ======= TickFct_SetPointCompare
 */
void TickFct_SetPointCompare(void) {

    // Compare the setPoint and tempReading
    if (setPoint > tempReading) {
        heat = true;
        ac = false;
    }
    else if (setPoint < tempReading) {
        ac = true;
        heat = false;
    }
    else if (setPoint == tempReading) {
        ac = false;
        heat = false;
    }

    // Increment the timer variable
    ++timer;
    if(heat) {
        ++heatTimer;
    }
    else if(ac) {
        ++acTimer;
    }


}

/*
 * ======= TickFct_DetectLastMinute =======
 */

void TickFct_DetectLastMinute(void) {

    Timestamp currentTime;
    currentTime = getTime();

    // Dump data and reset counters at 23:59
    if(currentTime.hr == 23 && currentTime.min == 59) {
        dataDump();
        counterReset();

    }

}

/*
 * ======= fillTasks =======
 */

void fillTasks(task tasks[]) {


    unsigned int i = 0;

    // Check buttons task
    tasks[i].period = 200;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &TickFct_CheckButtons;
    ++i;
    // Check temperature task
    tasks[i].period = 500;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &TickFct_CheckTemp;
    ++i;
    // Update report task
    tasks[i].period = 1000;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &TickFct_SetPointCompare;
    ++i;
    // Check for 24th hour
    tasks[i].period = 60000;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &TickFct_DetectLastMinute;
}

/*
 * ======= readTemp =======
 */
int16_t readTemp(void) {

    int16_t temperature = 0;
    i2cTransaction.readCount = 2;       // Number of bytes to read from the I2C sensor at a time
    if (I2C_transfer(i2c, &i2cTransaction)) {   // If the I2C transaction is successful

        // Extract degrees C from the received data;
        temperature = (rxBuffer[0] << 8) | (rxBuffer[1]);
        temperature *= 0.0078125;


        /*
         * If the MSB is set '1', then we have a 2's complement
         *  negative value which needs to be sign extended
         */

        if (rxBuffer[0] & 0x80) {
            temperature |= 0xF000;
        }
    }

    else {
        printf("Error reading temperature sensor (%d)\n\r",i2cTransaction.status);
        printf("Please power cycle your board by unplugging USB and plugging back in.\n\r");
    }

    return temperature;
}


/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    // Call driver init functions
    GPIO_init();
    initI2C();
    initTimer();

    // Configure the pins and buttons
    boardConfig();

    // Fill tasks array
    fillTasks(tasks);

    // Set the temperature setPoint to the current room temperature
    setPoint = 21;

    // loop indefinitely waiting for flag raises to facilitate task completion
    while (1) {

        while (!TimerFlag){}       // Wait for timer period
        TimerFlag = 0;             // Lower timer flag


        while (!TempFlag) {}       // Wait for the temperature flag to be raised
        TempFlag = 0;              // Lower the temp flag
        tempReading = readTemp();  // Update the temperature reading

    }
}
