/* GPIO Example: Matrix keypad with tasks.

 Author: German Velardez
 18/05/2021

*/
#include "matriz_keyboard.h"



void app_main(void)
{
   printf("iniciar el programa\n");
   key_board_init();
   xTaskCreatePinnedToCore(task_keyboard, "keypad read", 1024 * 10, NULL, 1,NULL, 1);
   xTaskCreatePinnedToCore(task_keyprint, "print keypress", 1024 * 10, NULL, 1,NULL, 1);
   while(1) {
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

