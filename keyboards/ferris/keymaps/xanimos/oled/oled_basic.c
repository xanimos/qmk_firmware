#include "quantum.h"
#include "oled_basic.h"
#include "../xanimos.h"

void oled_render_keylock_status(uint8_t led_usb_state) {
  oled_write_P(PSTR(" Lock:"), false);
  oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
  oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
  oled_write_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void oled_render_mod_status(uint8_t modifiers) {
  oled_write_P(PSTR("Mods:"), false);
  oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
  oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
  oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
  oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void oled_render_mod_lock_status(void) {
  oled_render_mod_status(get_mods() | get_oneshot_mods());
  oled_render_keylock_status(host_keyboard_leds());
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case _ALPHA:
            oled_write_ln_P(PSTR("QWERT"), false);
            break;
        case _SYMBOLS:
            oled_write_ln_P(PSTR("$!@#\%"), false);
            break;
        case _NUMBERS:
            oled_write_ln_P(PSTR("12345"), false);
            break;
        case _FUNCTION:
            oled_write_ln_P(PSTR("Fn <>"), false);
            break;
        case _GIT:
            oled_write_ln_P(PSTR("Git:\\"), false);
            break;
        case _MODS:
            oled_write_ln_P(PSTR("Mods "), false);
            break;
        case _GAMING:
            oled_write_ln_P(PSTR("Game "), false);
            break;
        default:
            oled_write_ln_P(PSTR("Unkwn"), false);
            break;
    }
}

static void oled_render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_mod_lock_status();
    } else {
        oled_render_logo();
    }
    return false;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return rotation;  // flips the display 180 degrees if offhand
    }
    return OLED_ROTATION_90;
}
