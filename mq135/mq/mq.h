#ifndef __mq_H__
#define __mq_H__

#include "driver.h"
#include "device.h"
#include <driver/gpio.h>
#include <sys/time.h>

#define mq_POLLING_MS         1000

static inline uint32_t get_time_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_usec;
}

#define timeout_expired(start, len) ((uint32_t)(get_time_us() - (start)) >= (len))

#define RETURN_CRTCAL(MUX, RES) do { portEXIT_CRITICAL(&MUX); return RES; } while(0)

static portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

class mq : public Device {
    private:

    public:
        // constructor
        mq();
        // override
        void init(void);
        void process(Driver *drv);
        int prop_count(void);
        bool prop_name(int index, char *name);
        bool prop_unit(int index, char *unit);
        bool prop_attr(int index, char *attr);
        bool prop_read(int index, char *value);
        bool prop_write(int index, char *value);
        // method
        char* random();
        int value(void);
};

#endif
