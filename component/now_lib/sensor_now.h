#ifndef SENSOR_NOW_H 
#define SENSOR_NOW_H

typedef void (*esp_now_cb_t)(int _state); 

void esp32_now_init(void); 
static uint8_t relay_add[] = { 0x7C , 0x9E , 0xBD , 0x4C , 0x2E , 0x94 }; //7c:9e:bd:4c:2e:94

#endif