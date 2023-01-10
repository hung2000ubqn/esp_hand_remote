#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "esp_log.h"
#include "esp_crc.h"
#include "esp_now.h"


#include "sensor_now.h"

const char * TAG = "ESP NOW"; 
esp_now_peer_info_t peerInfor; 

static uint32_t pinState = 0;

void esp32_now_init(void)
{
    // ESP NOW Init
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_send_cb(esp32_now_send_cb));
    ESP_ERROR_CHECK(esp_now_register_recv_cb(esp32_now_recv_cb));
    //ESP_ERROR_CHECK(esp_now_set_pmk((uint8_t *)CONFIG_ESPNOW_PMK) );

    peerInfor.channel = 0;
    peerInfor.ifidx = WIFI_IF_STA;
    peerInfor.encrypt = false;
    memcpy(peerInfor.peer_addr, relay_add, 6);
    ESP_ERROR_CHECK( esp_now_add_peer(&peerInfor));
}
