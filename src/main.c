#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main);

void main(void)
{
    const struct device *sensor = DEVICE_DT_GET_ANY(ti_tmag5273);

    if (sensor == NULL || !device_is_ready(sensor)) {
        LOG_ERR("TMAG5273 sensor not found or not ready");
        return;
    }

    struct sensor_value value;
    
    while (1) {
        // Fetch sensor data
        if (sensor_sample_fetch(sensor) < 0) {
            LOG_ERR("Failed to fetch sensor sample");
            return;
        }

        // Get sensor reading (magnetometer data, angle, etc.)
        if (sensor_channel_get(sensor, SENSOR_CHAN_MAGN_X, &value) == 0) {
            LOG_INF("Magnetometer X-axis: %d.%06d", value.val1, value.val2);
        }

        if (sensor_channel_get(sensor, SENSOR_CHAN_MAGN_Y, &value) == 0) {
            LOG_INF("Magnetometer Y-axis: %d.%06d", value.val1, value.val2);
        }

        if (sensor_channel_get(sensor, SENSOR_CHAN_MAGN_Z, &value) == 0) {
            LOG_INF("Magnetometer Z-axis: %d.%06d", value.val1, value.val2);
        }

        k_sleep(K_MSEC(1000)); // Sleep for 1 second
    }
}
