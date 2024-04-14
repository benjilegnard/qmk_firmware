/* Copyright 2022 splitkb.com <support@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

// The first four layers gets a name for readability, which is then used in the OLED below.
enum layers {
  _DEFAULT,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOUSE,
  _NAVIGATION,
  _SYMBOL_1,
  _SYMBOL_2,
  _FUNCTIONS,
  _NUMBERS,
  _QWERTY,
  _EXTRAS,
};

#ifdef OLED_ENABLE
// NOTE: Most of the OLED code was originally written by Soundmonster for the Corne,
// and has been copied directly from `crkbd/soundmonster/keymap.c`

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

static void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

static void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

static void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

static void render_logo(void) {
    static const char PROGMEM aurora_logo[] = {
        0x00, 0x00, 0x20, 0x60, 0xC0, 0x88, 0x30, 0x60,
        0x80, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40,
        0x60, 0x10, 0x80, 0xE0, 0x70, 0x00, 0x00, 0x80,
        0xC0, 0xE0, 0x70, 0x18, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x04, 0x00, 0x08, 0x11, 0x33, 0x27, 0x6E,
        0x59, 0x11, 0x2C, 0x04, 0x86, 0xC2, 0x42, 0x42,
        0x46, 0xE4, 0xF7, 0x39, 0x1C, 0x0E, 0x67, 0x33,
        0x11, 0xF8, 0x88, 0x0C, 0x06, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x10, 0x20,
        0x20, 0x90, 0xE0, 0x73, 0x39, 0x19, 0x32, 0x37,
        0x30, 0x18, 0x0F, 0x06, 0x06, 0x82, 0x06, 0x00,
        0x80, 0xF0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03,
        0x07, 0x0C, 0x08, 0x10, 0x20, 0x00, 0x00, 0x00,
    };
    oled_write_raw_P(aurora_logo, sizeof(aurora_logo));
    oled_set_cursor(0, 4);
}

static void render_logo_text(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _RAISE:
            oled_write_P(PSTR("raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("adjst"), false);
            break;
        case _MOUSE:
            oled_write_P(PSTR("mouse"), false);
            break;
        case _NAVIGATION:
            oled_write_P(PSTR("navig"), false);
            break;
        case _SYMBOL_1:
            oled_write_P(PSTR("symb1"), false);
            break;
        case _SYMBOL_2:
            oled_write_P(PSTR("symb2"), false);
            break;
        case _FUNCTIONS:
            oled_write_P(PSTR("funct"), false);
            break;
        case _NUMBERS:
            oled_write_P(PSTR("numbr"), false);
            break;
        case _QWERTY:
            oled_write_P(PSTR("qwert"), false);
            break;
        case _EXTRAS:
            oled_write_P(PSTR("extra"), false);
            break;
        default:
            oled_write_P(PSTR("corne"), false);
    }
}

static void render_kb_LED_state(void) {
    // Host Keyboard LED Status
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.num_lock ? PSTR("N ") : PSTR("  "), false);
    oled_write_P(led_usb_state.caps_lock ? PSTR("C ") : PSTR("  "), false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("S ") : PSTR("  "), false);
}

static void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _LOWER:
            oled_write_P(lower_layer, false);
            break;
        case _RAISE:
            oled_write_P(raise_layer, false);
            break;
        case _ADJUST:
            oled_write_P(adjust_layer, false);
            break;
        case _MOUSE:
            oled_write_P(lower_layer, false);
            break;
        case _NAVIGATION:
            oled_write_P(raise_layer, false);
            break;
        case _SYMBOL_1:
            oled_write_P(adjust_layer, false);
            break;
        case _SYMBOL_2:
            oled_write_P(adjust_layer, false);
            break;
        case _FUNCTIONS:
            oled_write_P(adjust_layer, false);
            break;
        case _NUMBERS:
            oled_write_P(adjust_layer, false);
            break;
        case _EXTRAS:
            oled_write_P(adjust_layer, false);
            break;
        default:
            oled_write_P(default_layer, false);
    }
}


bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {
        // Renders the current keyboard state (layers and mods)
        render_logo();
        render_logo_text();
        render_space();
        render_layer_state();
        render_space();
        render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
        render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
        render_kb_LED_state();
    } else {
        // clang-format off
        static const char PROGMEM aurora_art[] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0xC0,
            0xE0, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0,
            0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x3F, 0xFF, 0xFF, 0xF1, 0xE1, 0xC0,
            0xC0, 0xC0, 0xC0, 0xE1, 0xE1, 0xFF,
            0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xE0, 0xE0, 0xE1, 0xE1,
            0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
            0xE1, 0xE1, 0xE0, 0xE0, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x81, 0x81,
            0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
            0x81, 0x81, 0xC3, 0xFF, 0xFF, 0xF9,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x07, 0x87, 0xC7, 0xE7, 0xE7, 0xE7,
            0xF7, 0xF7, 0xE7, 0xE7, 0xE7, 0xC3,
            0x81, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xE3,
            0xE1, 0x01, 0xFF, 0xFF, 0xC1, 0xC1,
            0xE3, 0xFF, 0xFF, 0x3E, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0,
            0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
            0xE1, 0xE1, 0xE3, 0xE0, 0xE3, 0xE3,
            0xE3, 0xE3, 0xE1, 0xE1, 0xE0, 0xE0,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
            0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0xF9, 0xFF, 0xFF, 0xC7, 0x83, 0x01,
            0x01, 0x01, 0x01, 0x83, 0xC7, 0xFF,
            0xFF, 0xF9, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x83, 0xC7, 0xC7,
            0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF,
            0xC7, 0xC7, 0x83, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x7E, 0xFF,
            0xFF, 0xE3, 0xC3, 0x81, 0x81, 0x81,
            0x81, 0xC3, 0xC3, 0xFF, 0xFF, 0x7E,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xC0, 0xC1, 0xC3, 0xC3, 0xC7, 0xC7,
            0xC7, 0xC7, 0xC7, 0xC7, 0xC3, 0xC3,
            0xC1, 0xC0, 0x00, 0x00, 0x00, 0xC0,
            0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xE3, 0xE3, 0xE3, 0xE3,
            0xE3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE3,
            0xE3, 0xE3, 0xE3, 0xE3, 0x00, 0x00,
            0x00, 0x01, 0x03, 0x01, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x81, 0x81,
            0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
            0x81, 0x81, 0xC3, 0xFF, 0xFF, 0xF9,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x07, 0x07, 0x87, 0x87, 0x87, 0x87,
            0x87, 0x87, 0x87, 0x87, 0x87, 0xE3,
            0xE1, 0xE0, 0x80, 0x80, 0x80, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x3E, 0xBF, 0x3F, 0x07,
            0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
            0x07, 0x3F, 0x3F, 0x3F, 0x07, 0x07,
            0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x07, 0x0F,
            0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00,
        };
        // clang-format on
        oled_write_raw_P(aurora_art, sizeof(aurora_art));
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    // 0 is left-half encoder,
    // 1 is right-half encoder
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
#endif
