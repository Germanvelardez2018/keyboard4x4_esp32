 Example: Keyboard with freertos

This test code shows how to configure gpio and how to use keypad with freertos in ESP32.

## Files:

```c  
 matriz_keyboard.c
 matriz_keyboard.h
```



## GPIO Pins connected:

![img](matriz_keypad.png)


```c  

// columns are inputs

#define COL_1  GPIO_NUM_25
#define COL_2  GPIO_NUM_26
#define COL_3  GPIO_NUM_27
#define COL_4  GPIO_NUM_14

//rows are output

#define NUM_ROW  4
#define ROW_1    GPIO_NUM_18
#define ROW_2    GPIO_NUM_5
#define ROW_3    GPIO_NUM_17
#define ROW_4    GPIO_NUM_16

```



## ESP32 PINOUT
<p align="left">
  <img src="esp32_pinout.jpg" width="480" height="320" >
</p>





## Keypad functions:

 

```c  


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
```