#include <stdio.h>
#include <string.h>
#include <math.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include "mq.h"
#include <driver/adc.h>

mq::mq() {
  polling_ms = mq_POLLING_MS;
}

void mq::init(void) {
    initialized = true;
}

int mq::prop_count(void) {
  // not supported
  return 0;
}

bool mq::prop_name(int index, char *name) {
  // not supported
  return false;
}

bool mq::prop_unit(int index, char *unit) {
  // not supported
  return false;
}

bool mq::prop_attr(int index, char *attr) {
  // not supported
  return false;
}

bool mq::prop_read(int index, char *value) {
  // not supported
  return false;
}

bool mq::prop_write(int index, char *value) {
  // not supported
  return false;
}

void mq::process(Driver *drv) {
//  char buffer[64];
//  sprintf(buffer, "%lldms\n", (esp_timer_get_time() / 1000));
//  uart_write_bytes(UART_NUM_0, (const char*)buffer, strlen(buffer));
}

char* mq::random() {
  return "nat-random";
}

int mq::value(void) {
  int value;
  adc2_config_channel_atten( ADC2_CHANNEL_0, ADC_ATTEN_0db );

  esp_err_t r = adc2_get_raw( ADC2_CHANNEL_0, ADC_WIDTH_12Bit, &value);
  if ( r == ESP_OK ) {
      printf("%d\n", value );
  } else if ( r == ESP_ERR_TIMEOUT ) {
      printf("ADC2 used by Wi-Fi.\n");
      value = -1;
  }
  return value;
}

