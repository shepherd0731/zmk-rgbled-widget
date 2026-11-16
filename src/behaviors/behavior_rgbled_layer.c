#define DT_DRV_COMPAT zmk_behavior_rgbled_layer

#include <zephyr/device.h>
#include <zephyr/logging/log.h>

#include <drivers/behavior.h>
#include <zmk/behavior.h>

#include <zmk_rgbled_widget/widget.h>

#include <errno.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static int on_rgbled_layer_binding_pressed(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event) {

    if (binding->param1 > 7) {
        LOG_ERR("Invalid RGB LED color: %d", binding->param1);
        return -EINVAL;
    }

    set_layer_led_color(binding->param1);

    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_rgbled_layer_binding_released(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event) {
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_rgbled_layer_driver_api = {
    .binding_pressed = on_rgbled_layer_binding_pressed,
    .binding_released = on_rgbled_layer_binding_released,
    .locality = BEHAVIOR_LOCALITY_GLOBAL,
};

BEHAVIOR_DT_INST_DEFINE(
    0,
    NULL,
    NULL,
    NULL,
    NULL,
    POST_KERNEL,
    CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
    &behavior_rgbled_layer_driver_api
);

#endif
