#pragma once

#include "quantum.h"

#include "oled_driver.h"

void oled_render_keylock_status(uint8_t led_usb_state);
void oled_render_mod_status(uint8_t modifiers);
void oled_render_mod_lock_status(void);
void oled_render_layer_state(void);
static void oled_render_logo(void);
