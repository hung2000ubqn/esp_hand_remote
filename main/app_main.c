/*
    MAC RELAY(Chan den):   58:BF:25:37:AE:4C
    MAC SENSOR(Chan vang): 3C:61:05:12:5C:40
*/ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_now.h"


#include <assert.h>
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_system.h"

#include "esp_wifiAP.h"
#include "sensor_now.h"

#define BTN_UP_GPIO     18
#define BTN_DOWN_GPIO   19
#define BTN_POWER_GPIO  20
#define BTN_STOP_GPIO   21
#define GPIO_INPUT_PIN_SELECT (15<<BTN_UP_GPIO)
#define ESP_INTR_FLAG_DEFAULT 0

static QueueHandle_t gpio_evt_queue = NULL;

static char * TAG = "MAIN"; 

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

static void gpio_task_interrupt(void* arg)
{
    uint32_t io_num;
    uint8_t data;
    for(;;) {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            switch (io_num) 
            {
                case BTN_UP_GPIO: data = 1; break;
                case BTN_DOWN_GPIO: data = 2; break;
                case BTN_POWER_GPIO: data = 4; break;
                case BTN_STOP_GPIO: data = 8; break;
                default: data = 0; break;
            }
            if (esp_now_send(relay_add, &data, 8) == ESP_OK)
            {
                printf("Send successful\n");
            }else
            {
                printf("Send fail\n");
            }
        }
    }
}

void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    wifi_init_softap();
    
    esp32_now_init(); 

    gpio_config_t io_conf;
    //interrupt of rising edge
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    //bit mask of the pins, use GPIO4/5 here
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SELECT;
    //set as input mode    
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    //create a queue to handle gpio event from isr
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    xTaskCreate(gpio_task_interrupt, "gpio_task_interrupt", 10000, NULL, 10, NULL);

    //install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(BTN_UP_GPIO, gpio_isr_handler, (void*) BTN_UP_GPIO);
    gpio_isr_handler_add(BTN_DOWN_GPIO, gpio_isr_handler, (void*) BTN_DOWN_GPIO);
    gpio_isr_handler_add(BTN_POWER_GPIO, gpio_isr_handler, (void*) BTN_POWER_GPIO);
    gpio_isr_handler_add(BTN_STOP_GPIO, gpio_isr_handler, (void*) BTN_STOP_GPIO);
}


