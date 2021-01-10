#include <stdio.h>
#include <string.h>
#include <math.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include "mq.h"
#include <driver/adc.h>

// #include "soc/timer_group_struct.h"
// #include "soc/timer_group_reg.h"

Ultrasonic_callback _callback;
Ultrasonic_callback _didEnter;

bool didEnter_enable = true;

int _previous_distance = -1;
int _distance = -1;

// int ADC2_CHANNEL_0 = 0;
// int ADC_ATTEN_0db = 0;
// int ADC_WIDTH_12Bit = 3;

mq::mq() {
  polling_ms = mq_POLLING_MS;
}

void mq_initial(const mq_sensor_t *dev)
{
    gpio_set_direction(dev->trigger_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(dev->echo_pin, GPIO_MODE_INPUT);

    //gpio_set_level(dev->trigger_pin, 0);
};

esp_err_t mq_measure_cm(const mq_sensor_t *dev, uint32_t max_distance, int *distance)
{
    if (!distance)
        return ESP_ERR_INVALID_ARG;

    portENTER_CRITICAL(&mux);

    return ESP_OK;
};

void mq_start(void *pvParamters)
{

    mq_sensor_t sensor;
    memset(&sensor, 0, sizeof(sensor));

    sensor.trigger_pin = TRIGGER_GPIO;
    sensor.echo_pin = ECHO_GPIO;

    mq_initial(&sensor);

    while (true)
    {
        int distance;
        esp_err_t res = mq_measure_cm(&sensor, MAX_DISTANCE_CM, &distance);

        // TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
        // TIMERG0.wdt_feed=1;
        // TIMERG0.wdt_wprotect=0;

        if (res != ESP_OK)
        {
            printf("Error: ");
            switch (res)
            {
                case ESP_ERR_ULTRASONIC_PING:
                    printf("Cannot ping (device is in invalid state)\n");
                    break;
                case ESP_ERR_ULTRASONIC_PING_TIMEOUT:
                    printf("Ping timeout (no device found)\n");
                    break;
                case ESP_ERR_ULTRASONIC_ECHO_TIMEOUT:
                    printf("Echo timeout (i.e. distance too big)\n");
                    break;
                default:
                    printf("%d\n", res);
            }
        }
        else
            printf("Distance: %d cm, %.02f m\n", distance, distance / 100.0);
            _distance = distance;

            if (distance < 0) {
                continue;
            }

            if (_callback) {
              _callback();
            }

            if ((distance < 10 && _didEnter) && didEnter_enable ) {
                _didEnter();
                didEnter_enable = false;
            }

            if (distance > 10) {
                didEnter_enable = true;
            }

        vTaskDelay(150 / portTICK_PERIOD_MS);
    }
};

void mq::init(void) {
    initialized = true;
    xTaskCreate(mq_start, "mq_start", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
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

void mq::callback(Ultrasonic_callback statement) {
  _callback = statement;
}

void mq::didEnter(Ultrasonic_callback statement) {
    _didEnter = statement;
}

int mq::distance(void) {
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

