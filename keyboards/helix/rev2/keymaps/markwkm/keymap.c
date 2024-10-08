#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#    include "lufa.h"
#    include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
#    include "audio.h"
#endif
#ifdef SSD1306OLED
#    include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap
// matrix below. The underscores don't mean anything - you can have a layer
// called STUFF or any other name. Layer names don't all need to be of the
// same length, obviously, and you can also skip them entirely and just use
// numbers.
enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _DVORAK,
    _WORKMAN,
    _COLEMAKDH,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    DVORAK,
    WORKMAN,
    COLEMAKDH,
    LOWER,
    RAISE,
    ADJUST,
    MOUSE,
    BACKLIT,
    RGBRST,
    KC_BSPC_DEL
};

enum macro_keycodes {
    KC_SAMPLEMACRO,
};

// Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.              ,-----------------------------------------.
   * | Esc` |   1  |   2  |   3  |   4  |   5  |              |   6  |   7  |   8  |   9  |   0  | Ins  |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |              |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Bksp |   A  |   S  |   D  |   F  |   G  |              |   H  |   J  |   K  |   L  |   ;  |   '  |
   * |------+------+------+------+------+------+------.,------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | MODE ||RMODE |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * |Mouse |Adjust| Alt  | GUI  | Ctrl |Lower |Space ||Enter |Raise | Ctrl | GUI  | Alt  |Adjust|      |
   * `------------------------------------------------'`------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      QK_GESC,     KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_INS,  \
      KC_TAB,      KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
      KC_BSPC_DEL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                        KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT,     KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  RGB_MOD,    RGB_RMOD, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      MOUSE,       ADJUST, KC_LALT, KC_LGUI, KC_LCTL, LOWER, KC_SPC,     KC_ENT,   RAISE,  KC_RCTL, KC_RGUI, KC_RALT, ADJUST,  XXXXXXX  \
  ),

  /* Colemak
   * ,-----------------------------------------.              ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |              |   6  |   7  |   8  |   9  |   0  | Ins  |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   F  |   P  |   G  |              |   J  |   L  |   U  |   Y  |   ;  |   \  |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Bksp |   A  |   R  |   S  |   T  |   D  |              |   H  |   N  |   E  |   I  |   O  |   '  |
   * |------+------+------+------+------+------+------.,------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | MODE ||RMODE |   K  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * |Mouse |Adjust| Alt  | GUI  | Ctrl |Lower |Space ||Enter |Raise | Ctrl | GUI  | Alt  |Adjust|      |
   * `------------------------------------------------'`------------------------------------------------'
   */
  [_COLEMAK] = LAYOUT( \
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, \
      _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y,    _______, _______, \
      _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    _______, \
      _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______,    _______, KC_K,    KC_M,    _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______  \
  ),

  /* Dvorak
   * ,-----------------------------------------.              ,-----------------------------------------.
   * | ESC` |   1  |   2  |   3  |   4  |   5  |              |   6  |   7  |   8  |   9  |   0  | Ins  |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Tab  |   '  |   ,  |   .  |   P  |   Y  |              |   F  |   G  |   C  |   R  |   L  |   \  |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   U  |   I  |              |   D  |   H  |   T  |   N  |   S  |   /  |
   * |------+------+------+------+------+------+------.,------+------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  | MODE ||RMODE |   B  |   M  |   W  |   V  |   Z  |Shift |
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * |Mouse |Adjust| Alt  | GUI  | Ctrl |Lower |Space ||Enter |Raise | Ctrl | GUI  | Alt  |Adjust|      |
   * `------------------------------------------------'`------------------------------------------------'
   */
  [_DVORAK] = LAYOUT( \
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, \
      _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSLS, \
      _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, \
      _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    _______,    _______, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______, \
      _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______  \
      ),

  /* Workman
   * ,-----------------------------------------.              ,-----------------------------------------.
   * | ESC` |   1  |   2  |   3  |   4  |   5  |              |   6  |   7  |   8  |   9  |   0  | Ins  |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Tab  |   Q  |   D  |   R  |   W  |   B  |              |   J  |   F  |   U  |   P  |   ;  |   \  |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Bksp |   A  |   S  |   H  |   T  |   G  |              |   Y  |   N  |   E  |   O  |   I  |   '  |
   * |------+------+------+------+------+------+------.,------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   M  |   C  |   V  |      ||      |   K  |   L  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * |Mouse |Adjust| Alt  | GUI  | Ctrl |Lower |Space ||Enter |Raise | Ctrl | GUI  | Alt  |Adjust|      |
   * `------------------------------------------------'`------------------------------------------------'
   */
  [_WORKMAN] = LAYOUT( \
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, \
      _______, KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,                         KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, _______, \
      _______, KC_A,    KC_S,    KC_H,    KC_T,    KC_G,                         KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    _______, \
      _______, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    _______,    _______, KC_L,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______, \
      _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______  \
      ),

  /* Colemak-DH
   * ,-----------------------------------------.              ,-----------------------------------------.
   * | ESC` |   1  |   2  |   3  |   4  |   5  |              |   6  |   7  |   8  |   9  |   0  | Ins  |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   F  |   P  |   B  |              |   J  |   L  |   U  |   Y  |   ;  |   \  |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Bksp |   A  |   R  |   S  |   T  |   G  |              |   K  |   N  |   E  |   I  |   O  |   '  |
   * |------+------+------+------+------+------+------.,------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   D  |   V  | MODE ||RMODE |   M  |   H  |   ,  |   .  |  Up  |   /  |
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * |Mouse |Adjust| Alt  | GUI  | Ctrl |Lower |Space ||Enter |Raise | Ctrl | GUI  | Alt  |Adjust|      |
   * `------------------------------------------------'`------------------------------------------------'
   */
  [_COLEMAKDH] = LAYOUT( \
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, \
      _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______, \
      _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_K,    KC_N,    KC_E,    KC_I,    KC_O,    _______, \
      _______, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    _______,    _______, KC_M,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, _______, \
      _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______  \
      ),

  /* Lower
   * ,-----------------------------------------.              ,-----------------------------------------.
   * |      |      |      |      |      |      |              |      |      |      |      |      |      |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | ESC` |   1  |   2  |   3  |   4  |   5  |              |   6  |   7  |   8  |   9  |   0  | Ins  |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * |      |      |      |      |      |      |              |PageUp|   -  |   +  |   _  |   =  |      |
   * |------+------+------+------+------+------+------.,------+------+------+------+------+------+------|
   * | Shift|      |      |      |      |      |      ||      |PageDn|   [  |   ]  |   {  |   }  | Shift|
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      ||      |      |      |      |      |      |      |
   * `------------------------------------------------'`------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_INS,  \
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGUP, KC_MINS, KC_PLUS, KC_UNDS, KC_EQL,  XXXXXXX, \
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,    _______, KC_PGDN, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______, \
      XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX  \
      ),

  /* Raise
   * ,-----------------------------------------.              ,-----------------------------------------.
   * |      |      |      |      |      |      |              |      |      |      |      |      |      |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Tab  |      | Home |  Up  | End  |      |              |      |      |      |      |      |      |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | Del  |      | Left | Down |Right |      |              |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------.,------+------+------+------+------+------+------|
   * | Shift|      |      |      |      |      |      ||      |      |      |      |      |      | Shift|
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      ||      |      |      |      |      |      |      |
   * `------------------------------------------------'`------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      _______, XXXXXXX, KC_HOME, KC_UP,   KC_END,   XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_DEL,  XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_LBRC,    KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
      XXXXXXX, XXXXXXX, _______, _______, _______,  _______, _______,    _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX  \
      ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.              ,-----------------------------------------.
   * |Qwerty|Colemk|Dvorak|Workmn|Clmkdh|      |              |      |      |      |      |      | Mute |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * |RGB ON| MODE | HUE+ | SAT+ | VAL+ | EFF+ |              | Mac  |      |      |      |      | Vol+ |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * | CAPS |RMODE | HUE- | SAT- | VAL- | EFF- |              | Win  |      |      |      |      | Vol- |
   * |------+------+------+------+------+------+------.,------+------+------+------+------+------+------|
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      ||      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * |Reset |      | Acl0 | Acl1 | Acl2 |      |      ||      |      |      |      |      |      |RGBRST|
   * `------------------------------------------------'`------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      QWERTY,  COLEMAK,  DVORAK,  WORKMAN, COLEMAKDH, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, \
      RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI,   RGB_SPI,                    AG_NORM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_VOLU, \
      KC_CAPS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,   RGB_SPD,                    AG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_VOLD, \
      KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,     KC_F6,   XXXXXXX,  XXXXXXX, KC_F7,    KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
      QK_BOOT, _______,  KC_ACL0, KC_ACL1, KC_ACL2,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGBRST   \
      ),

  /* Mouse
   * ,-----------------------------------------.              ,-----------------------------------------.
   * |      |      |      |      |      |      |              |      |      |      |      |      |      |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * |      |      |      |             |      |              |      |WhLeft| MsUp |WhRigh| WhUp |      |
   * |------+------+------+------+------+------|              |------+------+------+------+------+------|
   * |      |      |      |      |      |      |              |      |MsLeft|MsDown|MsRigh|WhDown|      |
   * |------+------+------+------+------+------+------.,------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      ||      |      |Bttn1 |Bttn3 |Bttn2 |      |      |
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      ||      |      |Bttn4 |Bttn5 |Bttn6 |      |      |
   * `------------------------------------------------'`------------------------------------------------'
   */
  [_MOUSE] =  LAYOUT( \
      KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,     KC_F6,                      KC_F7,    KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
      RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI,   RGB_SPI,                    AG_NORM, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, KC_VOLU, \
      KC_CAPS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,   RGB_SPD,                    AG_SWAP, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_VOLD, \
      QWERTY,  COLEMAK,  DVORAK,  WORKMAN, COLEMAKDH, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, KC_MUTE, \
      QK_BOOT, _______,  KC_ACL0, KC_ACL1, KC_ACL2,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_BTN4, KC_BTN6, KC_BTN5, XXXXXXX, RGBRST   \
      )
};
// clang-format on

bool            shift_held = false;
static uint16_t held_shift = 0;

#ifdef AUDIO_ENABLE

float tone_qwerty[][2]    = SONG(QWERTY_SOUND);
float tone_dvorak[][2]    = SONG(DVORAK_SOUND);
float tone_colemak[][2]   = SONG(COLEMAK_SOUND);
float tone_plover[][2]    = SONG(PLOVER_SOUND);
float tone_plover_gb[][2] = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]    = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int  RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
#ifdef RGBLIGHT_ENABLE
        // rgblight_mode(RGB_current_mode);
#endif
        layer_on(layer3);
    } else {
        layer_off(layer3);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_RSFT:
        case KC_LSFT:
            shift_held = record->event.pressed;
            held_shift = keycode;
            break;
        case KC_BSPC_DEL:
            if (record->event.pressed) {
                if (shift_held) {
                    unregister_code(held_shift);
                    register_code(KC_DEL);
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                unregister_code(KC_DEL);
                unregister_code(KC_BSPC);
                if (shift_held) {
                    register_code(held_shift);
                }
            }
            return false;
        case QWERTY:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(tone_qwerty);
#endif
                persistent_default_layer_set(1UL << _QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(tone_colemak);
#endif
                persistent_default_layer_set(1UL << _COLEMAK);
            }
            return false;
            break;
        case DVORAK:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(tone_dvorak);
#endif
                persistent_default_layer_set(1UL << _DVORAK);
            }
            return false;
            break;
        case WORKMAN:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(tone_workman);
#endif
                persistent_default_layer_set(1UL << _WORKMAN);
            }
            return false;
            break;
        case COLEMAKDH:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(tone_workman);
#endif
                persistent_default_layer_set(1UL << _COLEMAKDH);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                // not sure how to have keyboard check mode and set it to a
                // variable, so my work around uses another variable that
                // would be set to true after the first time a reactive key
                // is pressed.
                if (TOG_STATUS) { // TOG_STATUS checks is another reactive
                                  // key currently pressed, only changes RGB
                                  // mode if returns false
                } else {
                    TOG_STATUS = !TOG_STATUS;
#ifdef RGBLIGHT_ENABLE
                    // rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
#endif
                }
                layer_on(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            } else {
#ifdef RGBLIGHT_ENABLE
                // rgblight_mode(RGB_current_mode);   // revert RGB to
                // initial mode prior to RGB mode change
#endif
                TOG_STATUS = false;
                layer_off(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                // not sure how to have keyboard check mode and set it to a
                // variable, so my work around uses another variable that
                // would be set to true after the first time a reactive key
                // is pressed.
                if (TOG_STATUS) { // TOG_STATUS checks is another reactive
                                  // key currently pressed, only changes RGB
                                  // mode if returns false
                } else {
                    TOG_STATUS = !TOG_STATUS;
#ifdef RGBLIGHT_ENABLE
                    // rgblight_mode(RGBLIGHT_MODE_SNAKE);
#endif
                }
                layer_on(_RAISE);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            } else {
#ifdef RGBLIGHT_ENABLE
                // rgblight_mode(RGB_current_mode);  // revert RGB to
                // initial mode prior to RGB mode change
#endif
                layer_off(_RAISE);
                TOG_STATUS = false;
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
        case MOUSE:
            if (record->event.pressed) {
                layer_on(_MOUSE);
            } else {
                layer_off(_MOUSE);
            }
            return false;
            break;
            // led operations - RGB mode change now updates the
            // RGB_current_mode to allow the right RGB mode to be set after
            // reactive keys are released
        case RGB_MOD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                rgblight_step();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            break;
    }
    return true;
}

void matrix_init_user(void) {
#ifdef AUDIO_ENABLE
    startup_user();
#endif
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
// SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
    iota_gfx_init(!has_usb()); // turns on the display
#endif
}

#ifdef AUDIO_ENABLE

void startup_user() {
    _delay_ms(20); // gets rid of tick
}

void shutdown_user() {
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void) {
    music_scale_user();
}

void music_scale_user(void) {
    PLAY_SONG(music_scale);
}

#endif

// SSD1306 OLED update loop, make sure to add #define SSD1306OLED in
// config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
    iota_gfx_task(); // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix       *dest,
                   const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

// assign the right code to your layers for OLED display
#    define L_BASE 0
#    define L_LOWER (1 << _LOWER)
#    define L_RAISE (1 << _RAISE)
#    define L_ADJUST (1 << _ADJUST)
#    define L_MOUSE (1 << _MOUSE)
#    define L_ADJUST_TRI (L_ADJUST | L_RAISE | L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {
    static const char helix_logo[] PROGMEM = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a,
        0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0,
        0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab,
        0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1,
        0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc,
        0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    matrix_write_P(matrix, helix_logo);
}

static void render_rgbled_status(bool                    full,
                                 struct CharacterMatrix *matrix) {
#    ifdef RGBLIGHT_ENABLE
    char buf[30];
    if (RGBLIGHT_MODES > 1 && rgblight_config.enable) {
        if (full) {
            snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                     rgblight_config.mode,
                     rgblight_config.hue / RGBLIGHT_HUE_STEP,
                     rgblight_config.sat / RGBLIGHT_SAT_STEP,
                     rgblight_config.val / RGBLIGHT_VAL_STEP);
        } else {
            snprintf(buf, sizeof(buf), "[%2d] ", rgblight_config.mode);
        }
        matrix_write(matrix, buf);
    }
#    endif
}

static void render_layer_status(struct CharacterMatrix *matrix) {
    // Define layers here
    char buf[10];
    matrix_write_P(matrix, PSTR("Layer: "));
    switch (layer_state) {
        case L_BASE:
            switch (get_highest_layer(layer_state | default_layer_state)) {
                case _QWERTY:
                    matrix_write_P(matrix, PSTR("Qwerty"));
                    break;
                case _COLEMAK:
                    matrix_write_P(matrix, PSTR("Colemak"));
                    break;
                case _DVORAK:
                    matrix_write_P(matrix, PSTR("Dvorak"));
                    break;
                case _WORKMAN:
                    matrix_write_P(matrix, PSTR("Workman"));
                    break;
                case _COLEMAKDH:
                    matrix_write_P(matrix, PSTR("Colemak-DH"));
                    break;
                default:
                    matrix_write_P(matrix, PSTR("Undefined"));
            }
            break;
        case L_RAISE:
            matrix_write_P(matrix, PSTR("Raise"));
            break;
        case L_LOWER:
            matrix_write_P(matrix, PSTR("Lower"));
            break;
        case L_ADJUST:
        case L_ADJUST_TRI:
            matrix_write_P(matrix, PSTR("Adjust"));
            break;
        case L_MOUSE:
            matrix_write_P(matrix, PSTR("Mouse"));
            break;
        default:
            matrix_write_P(matrix, PSTR("Undef-"));
            snprintf(buf, sizeof(buf), "%ld", layer_state);
            matrix_write(matrix, buf);
    }
}

void render_status(struct CharacterMatrix *matrix) {
    // Render to mode icon
    static const char os_logo[][2][3] PROGMEM = {
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}}};
    if (keymap_config.swap_lalt_lgui == false) {
        matrix_write_P(matrix, os_logo[0][0]);
        matrix_write_P(matrix, PSTR("\n"));
        matrix_write_P(matrix, os_logo[0][1]);
    } else {
        matrix_write_P(matrix, os_logo[1][0]);
        matrix_write_P(matrix, PSTR("\n"));
        matrix_write_P(matrix, os_logo[1][1]);
    }

    matrix_write_P(matrix, PSTR(" "));
    render_layer_status(matrix);
    matrix_write_P(matrix, PSTR("\n"));

    // Host Keyboard LED Status
    matrix_write_P(matrix, (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))
                               ? PSTR("NUMLOCK")
                               : PSTR("       "));
    matrix_write_P(matrix, (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK))
                               ? PSTR("CAPS")
                               : PSTR("    "));
    matrix_write_P(matrix,
                   (host_keyboard_leds() & (1 << USB_LED_SCROLL_LOCK))
                       ? PSTR("SCLK")
                       : PSTR("    "));
    matrix_write_P(matrix, PSTR("\n"));
    render_rgbled_status(true, matrix);
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;

#    if DEBUG_TO_SCREEN
    if (debug_enable) {
        return;
    }
#    endif

    matrix_clear(&matrix);
    if (is_master) {
        render_status(&matrix);
    } else {
        render_logo(&matrix);
        render_rgbled_status(false, &matrix);
        render_layer_status(&matrix);
    }
    matrix_update(&display, &matrix);
}

#endif
