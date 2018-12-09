#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_bepo.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum custom_keycodes {
  EPRM = SAFE_RANGE,
  VRSN,
  RGB_SLD
};

// A 'transparent' key code (that falls back to the layers below it).
#define ___ KC_TRANSPARENT

// Some combined keys (one normal keycode when tapped and one modifier or layer
// toggle when held).
#define ESC_FN    LT(SYMB, KC_ESC)        // ESC key and FN layer toggle.
#define M_RSFT    MT(MOD_RSFT, BP_M)    // 'M' key and right shift modifier.
#define W_RCTL    MT(MOD_RCTL, BP_W)    // 'W' key and right control modifier.
#define M_RCTL    MT(MOD_RCTL, BP_M)
#define W_RSFT    MT(MOD_RSFT, BP_W)
#define SPC_RALT  MT(MOD_RALT, KC_SPC)  // SPACE key and right alt modifier.
#define PERC_FN   LT(SYMB, BP_PERC)      // '%' key and FN layer toggle.
#define ECRC_FN   LT(SYMB, BP_ECRC)      // 'Ê'' and FN layer toggle.

// The most portable copy/paste keys (windows (mostly), linux, and some terminal emulators).
#define MK_CUT    LSFT(KC_DEL)  // shift + delete
#define MK_COPY   LCTL(KC_INS)  // ctrl + insert
#define MK_PASTE  LSFT(KC_INS)  // shift + insert

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   $    |   "  |   <  |   >  |   (  |   )  |  @  |            | DEL  |   @  |   +  |   -  |   /  |   *  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   B  |   É  |   P  |   O  |   È  |  L1  |           | BkSp |   ^! |   V  |   D  |   L  |   J  |   Z    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   A  |   U  |   I  |   E  |   ,  |------|           |------|   C  |   T  |   S  |   R  |N / L2|M/RCtrl |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LCtrl  |À/Ctrl|   Y  |   X  |   .  |   K  |      |           |      |   '  |   Q  |   G  |   H  |F/Ctrl|W/LShift|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Esc/L1|Ê / Fn|  Cmd |[/LAlt|]/RAlt|                                       |   {  |   }  |  ~L1 |   ç  |% / Fn|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Left |Right |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       |  Up  |        |      |
 *                                 | Enter|Backsp|------|       |------|  Tab   |Space |
 *                                 |      |ace   | End  |       | Down |        |      |
 *                                 `--------------------'       `----------------------'
 */(  )
[BASE] = LAYOUT_ergodox(
// left hand
        BP_DLR,          BP_DQOT,        BP_GRTR,       BP_LESS, BP_LPRN, BP_RPRN, KC_DEL,
        KC_TAB,          BP_B,           BP_ECUT,       BP_P,    BP_O,    BP_EGRV, TG(SYMB),
        KC_LSFT,         BP_A,           BP_U,          BP_I,    BP_E,    BP_COMM,
        CTL_T(KC_ESC),   CTL_T(BP_AGRV), BP_Y,          BP_X,    BP_DOT,  BP_K,    ALL_T(KC_NO),
        TT(SYMB),        ECRC_FN,        KC_LGUI,       LALT_T(BP_LBRC),  RALT_T(BP_RBRC),
        ALT_T(KC_APP), KC_LGUI,
        KC_HOME,
        KC_ENT, KC_BSPC, KC_END,
// right hand
        KC_DEL,       BP_AT,    BP_PLUS, BP_MINS, BP_SLSH, BP_ASTR,        BP_EQL,
        KC_BSPC,      BP_DCRC,  BP_V,    BP_D,    BP_L,    BP_J,           BP_Z,
        BP_C,         BP_T,     BP_S,    BP_R,    LT(MDIA, BP_N), M_RCTL,
        MEH_T(KC_NO), BP_APOS,  BP_Q,    BP_G,    BP_H,    CTL_T(BP_F),    W_RSFT,
        BP_LCBR,      BP_RCBR,  KC_FN1,  BP_CCED, PERC_FN,
        KC_LEFT, KC_RIGHT,
        KC_UP,
        KC_DOWN, KC_TAB, KC_SPC
),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|Solid |       | Left |Right |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|Toggle|       | PgUp |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |PgDown|      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
        // left hand
        VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   ___,
        ___, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, ___,
        ___, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,
        ___, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, ___,
        EPRM,    ___, ___, ___, ___,
        RGB_MOD, RGB_SLD,
        RGB_TOG,
        RGB_VAD, RGB_VAI, ___,
// right hand
        ___, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        ___, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
        KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, ___,
        ___, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, ___,
        ___, KC_DOT,  KC_0,    KC_EQL,  ___,
        KC_HOME, KC_END,
        KC_PGUP,
        KC_PGDN, RGB_HUD, RGB_HUI
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MDIA] = LAYOUT_ergodox(
        // left hand
        ___, ___, ___, ___, ___, ___, ___,
        ___, ___, ___, KC_MS_U, ___, ___, ___,
        ___, ___, KC_MS_L, KC_MS_D, KC_MS_R, ___,
        ___, ___, ___, ___, ___, ___, ___,
        ___, ___, ___, KC_BTN1, KC_BTN2,
        ___, ___,
        ___,
        ___, ___, ___,
// right hand
        ___, ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, KC_MPLY,
        ___, ___, ___, KC_MPRV, KC_MNXT, ___, ___,
        KC_VOLU, KC_VOLD, KC_MUTE, ___, ___,
        ___, ___,
        ___,
        ___, ___, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case EPRM:
        eeconfig_init();
        return false;
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};
