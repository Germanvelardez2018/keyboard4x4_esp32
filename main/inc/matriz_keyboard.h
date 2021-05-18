/*
 * matriz_keyboard.h
 *
 *  Created on: 18 may. 2021
 *      Author: German Velardez
 */

#ifndef MAIN_INC_MATRIZ_KEYBOARD_H_
#define MAIN_INC_MATRIZ_KEYBOARD_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"





/**
  * @brief configure and initialize the esp32 pins
  *
  */
void key_board_init(void);



/**
  * @brief Task to perform the keyboard reading. Compact and simple code.
  * Using interrupts with this microcontroller is not always a good idea.
  *
  */
void task_keyboard(void* param);



/**
  * @brief Task Receiving the keys pressed through a queue.
  *
  */


void task_keyprint(void *param);




#endif /* MAIN_INC_MATRIZ_KEYBOARD_H_ */
