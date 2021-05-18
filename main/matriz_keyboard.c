/*
 * matriz_keyboard.c
 *
 *  Created on: 18 may. 2021
 *      Author: German Velardez
 */




#include "matriz_keyboard.h"

#define NUM_ROW  4
#define NUM_COL  4



// columns are inputs

#define COL_1  GPIO_NUM_25
#define COL_2  GPIO_NUM_26
#define COL_3  GPIO_NUM_27
#define COL_4  GPIO_NUM_14

//rows are output


#define ROW_1    GPIO_NUM_18
#define ROW_2    GPIO_NUM_5
#define ROW_3    GPIO_NUM_17
#define ROW_4    GPIO_NUM_16


// Keypad layout: [row][col]
char const KEYS[4][4] = {
						  { '1', '2' , '3' ,'A' },
						  { '4', '5' , '6' ,'B' },
						  { '7', '8' , '9' ,'C' },
						  { '*', '0' , '#' ,'D' },
                         };




#define GPIO_INPUT_COLUMNS  ((1ULL<<COL_1) | (1ULL<<COL_2) | (1ULL<<COL_3) | (1ULL<<COL_4))
#define GPIO_OUTPUT_ROWS    ((1ULL<<ROW_1) | (1ULL<<ROW_2) | (1ULL<<ROW_3) | (1ULL<<ROW_4))
#define ESP_INTR_FLAG_DEFAULT 0
static uint8_t rows[NUM_ROW] = { ROW_1, ROW_2, ROW_3, ROW_4 };
static uint64_t cols[NUM_ROW] = { COL_1, COL_2, COL_3, COL_4 };

static xQueueHandle keypad_evt_queue= NULL;









static void config_columns(void) {
	gpio_config_t col_config;
	col_config.pin_bit_mask = GPIO_INPUT_COLUMNS;
	col_config.intr_type = GPIO_INTR_ANYEDGE; // interrupt type: falling and rising edge
	col_config.mode = GPIO_MODE_INPUT;
	col_config.pull_up_en = GPIO_PULLUP_ENABLE;
	col_config.pull_down_en = GPIO_PULLUP_DISABLE;
	gpio_config(&col_config);

}

static void config_rows(void) {

	gpio_config_t row_config;
	row_config.pin_bit_mask = GPIO_OUTPUT_ROWS;
	row_config.intr_type = GPIO_INTR_DISABLE;   // interrupt disable
	row_config.mode = GPIO_MODE_OUTPUT;
	row_config.pull_up_en = GPIO_PULLUP_DISABLE;
	row_config.pull_down_en = GPIO_PULLUP_DISABLE;
	gpio_config(&row_config);
}

void key_board_init() {
	config_rows();
	config_columns();
	keypad_evt_queue = xQueueCreate(10, sizeof(char));   //Queue ready
}



void task_keyboard(void *param) {
	gpio_set_level(rows[0], 1);
	gpio_set_level(rows[1], 1);
	gpio_set_level(rows[2], 1);
	gpio_set_level(rows[3], 1);

	for (;;) {
		for (uint8_t row = 0; row < NUM_ROW; row++) {
			gpio_set_level(rows[row], 0);
			for (uint8_t col = 0; col < NUM_COL; col++) {
				if (!gpio_get_level(cols[col])) {
					xQueueSend(keypad_evt_queue, &(KEYS[row][col]), 1000);
					vTaskDelay(50 / portTICK_RATE_MS);
				}
			}
			vTaskDelay(50 / portTICK_RATE_MS);
			gpio_set_level(rows[row], 1);

		}

	}

}





void task_keyprint(void *param) {

	char key_pressed;

	for (;;) {
		if (xQueueReceive(keypad_evt_queue, (void* ) &key_pressed,
				(portTickType) portMAX_DELAY)) {
			printf(" key pressed: %c\n", key_pressed);
		}

	}

}

