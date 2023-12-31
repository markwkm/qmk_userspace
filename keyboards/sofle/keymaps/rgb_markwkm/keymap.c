/* Copyright 2021 Dane Evans
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
// SOFLE RGB
#include <stdio.h>

#include QMK_KEYBOARD_H

#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s, Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv, Override)

// Light combinations

// clang-format off
#define SET_INDICATORS(...)                                                   \
    {0, RGB_INDICATOR, HSV_OVERRIDE_HELP(__VA_ARGS__, INDICATOR_BRIGHTNESS)}, \
    {RGBLED_NUM, RGB_INDICATOR, __VA_ARGS__}

#define SET_UNDERGLOW(...)                  \
    {RGB_INDICATOR, RGB_DROP, __VA_ARGS__}, \
    {RGBLED_NUM + RGB_INDICATOR, RGB_DROP, __VA_ARGS__}

#define SET_NUMPAD(...)                                           \
    {RGBLED_NUM + RGB_INDICATOR + RGB_DROP + 11, 4, __VA_ARGS__}, \
    {RGBLED_NUM + RGB_INDICATOR + RGB_DROP + 15, 4, __VA_ARGS__}, \
    {RGBLED_NUM + RGB_INDICATOR + RGB_DROP + 21, 4, __VA_ARGS__}

#define SET_NUMROW(...)                                           \
    {RGB_INDICATOR + RGB_DROP + 4, 2, __VA_ARGS__},               \
    {RGB_INDICATOR + RGB_DROP + 14, 2, __VA_ARGS__},              \
    {RGB_INDICATOR + RGB_DROP + 24, 2, __VA_ARGS__},              \
    {RGBLED_NUM + RGB_INDICATOR + RGB_DROP + 4, 2, __VA_ARGS__},  \
    {RGBLED_NUM + RGB_INDICATOR + RGB_DROP + 14, 2, __VA_ARGS__}, \
    RGBLED_NUM + RGB_INDICATOR + RGB_DROP + 24, 2, __VA_ARGS__}

#define SET_INNER_COL(...)                           \
    {RGB_INDICATOR + RGB_DROP + 25, 4, __VA_ARGS__}, \
    {RGBLED_NUM + RGB_INDICATOR + RGB_DROP + 25, 4, __VA_ARGS__}

#define SET_OUTER_COL(...)                          \
    {RGB_INDICATOR + RGB_DROP + 1, 4, __VA_ARGS__}, \
    {RGBLED_NUM + RGB_INDICATOR + RGB_DROP + 1, 4, __VA_ARGS__}

#define SET_THUMB_CLUSTER(...)                                   \
    {RGB_INDICATOR + RGB_DROP, 1, __VA_ARGS__},                  \
    {RGB_INDICATOR + RGB_DROP + 9, 2, __VA_ARGS__},              \
    {RGB_INDICATOR + RGB_DROP + 19, 2, __VA_ARGS__},             \
    {RGBLED_NUM + RGB_INDICATOR + RGB_DROP, 1, __VA_ARGS__},     \
    {RGBLED_NUM + RGB_INDICATOR + RGB_DROP + 9, 2, __VA_ARGS__}, \
    {RGBLED_NUM + RGB_INDICATOR + RGB_DROP + 19, 2, __VA_ARGS__}
// clang-format on

#define SET_LAYER_ID(hsv) \
    SET_INDICATORS(hsv), SET_UNDERGLOW(hsv), SET_THUMB_CLUSTER(hsv)

enum sofle_layers {
    _DEFAULTS = 0,
    _QWERTY   = 0,
    _COLEMAK,
    _COLEMAKDH,
    _DVORAK,
    _WORKMAN,
    _LOWER,
    _RAISE,
    _ADJUST,
    _SWITCH,
    _NUMPAD
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_COLEMAK,
    KC_COLEMAKDH,
    KC_DVORAK,
    KC_WORKMAN,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_NUMPAD,
    KC_BSPC_DEL
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | `Esc |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Ins  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   \  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Bspc |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |   '  |
     * |------+------+------+------+------+------| Bttn1 |    | Bttn2 |------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | Shift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            |  Alt | GUI  | Ctrl |LOWER | /Space  /       \Enter \  |RAISE | Ctrl | GUI  |  Alt |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'            '------''---------------------------'
     */
    [_QWERTY] = LAYOUT( \
        QK_GESC,             KC_1, KC_2,    KC_3,    KC_4,     KC_5,                          KC_6,     KC_7,     KC_8,    KC_9,   KC_0,    LT(_ADJUST, KC_INS),  \
        LT(_SWITCH, KC_TAB), KC_Q, KC_W,    KC_E,    KC_R,     KC_T,                          KC_Y,     KC_U,     KC_I,    KC_O,   KC_P,    KC_BSLS, \
        KC_BSPC_DEL,         KC_A, KC_S,    KC_D,    KC_F,     KC_G,                          KC_H,     KC_J,     KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
        KC_LSFT,             KC_Z, KC_X,    KC_C,    KC_V,     KC_B,     KC_BTN1,   KC_BTN2,  KC_N,     KC_M,     KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, \
                                   KC_LALT, KC_LGUI, KC_LCTL,  KC_LOWER, KC_SPC,    KC_ENT,   KC_RAISE, KC_RCTL,  KC_RGUI, KC_RALT),

    /*
     * COLEMAK
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | `Esc |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Ins  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  |   \  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Bspc |   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |   '  |
     * |------+------+------+------+------+------| Bttn1 |    | Bttn2 |------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  | Shift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | Alt  | GUI  | Ctrl |LOWER | /Space  /       \Enter \  |RAISE | Ctrl | GUI  |  Alt |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'            '------''---------------------------'
     */
    [_COLEMAK] = LAYOUT( \
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, \
        _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______, \
        _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    _______, \
        _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______,    _______, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______, \
                          _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______),

    /*
     * COLEMAK-DH
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | `Esc |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Ins  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  |   \  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Bspc |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |   '  |
     * |------+------+------+------+------+------| Bttn1 |    | Bttn2 |------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  | Shift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | Alt  | GUI  | Ctrl |LOWER | /Space  /       \Enter \  |RAISE | Ctrl | GUI  |  Alt |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'            '------''---------------------------'
     */
    [_COLEMAKDH] = LAYOUT( \
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, \
        _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______, \
        _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    _______, \
        _______, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    _______,    _______, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, _______, \
                          _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______),

    /*
     * DVORAK
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | `Esc |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Ins  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   '  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  |   \  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Bspc |   A  |   O  |   E  |   U  |   I  |-------.    ,-------|   D  |   H  |   I  |   N  |   S  |   /  |
     * |------+------+------+------+------+------| Bttn1 |    | Bttn2 |------+------+------+------+------+------|
     * | Shift|   ;  |   Q  |   J  |   K  |   X  |-------|    |-------|   B  |   M  |   W  |   V  |   Z  | Shift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | Alt  | GUI  | Ctrl |LOWER | /Space  /       \Enter \  |RAISE | Ctrl | GUI  |  Alt |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'            '------''---------------------------'
     */
    [_DVORAK] = LAYOUT( \
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, \
        _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    _______, \
        _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_I,    KC_N,    KC_S,    KC_SLSH, \
        _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    _______,    _______, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______, \
                          _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______),

    /*
     * WORKMAN
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | `Esc |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Ins  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   Q  |   D  |   R  |   W  |   B  |                    |   J  |   F  |   U  |   P  |   ;  |   \  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Bspc |   A  |   S  |   H  |   T  |   G  |-------.    ,-------|   Y  |   N  |   E  |   O  |   I  |   '  |
     * |------+------+------+------+------+------| Bttn1 |    | Bttn2 |------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   M  |   C  |   V  |-------|    |-------|   K  |   L  |   ,  |   .  |   /  | Shift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | Alt  | GUI  | Ctrl |LOWER | /Space  /       \Enter \  |RAISE | Ctrl | GUI  |  Alt |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'            '------''---------------------------'
     */
    [_WORKMAN] = LAYOUT( \
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, \
        _______, KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,                         KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, _______, \
        _______, KC_A,    KC_S,    KC_H,    KC_T,    KC_G,                         KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    KC_QUOT, \
        _______, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    _______,    _______, KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, _______, \
                          _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______),

    /* LOWER
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | `Esc |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Ins  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------.    ,-------|PageUp|   -  |   +  |   _  |   =  |      |
     * |------+------+------+------+------+------| Bttn1 |    | Bttn5 |------+------+------+------+------+------|
     * | Shift|      |      |      |      |      |-------|    |-------|PageDn|   [  |   ]  |   {  |   }  | Shift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | Alt  | GUI  | Ctrl |LOWER | /Space  /       \Enter \  |RAISE | Ctrl | GUI  |  Alt |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'            '------''---------------------------'
     */
    [_LOWER] = LAYOUT( \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             \
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    LT(_ADJUST, KC_INS), \
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGUP, KC_MINS, KC_PLUS, KC_UNDS, KC_EQL,  XXXXXXX,             \
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,    KC_BTN5, KC_PGDN, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______,             \
                          _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______),

    /* RAISE
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |   `  |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |   `  |      | Home |  Up  | End  |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Del  |      | Left | Down | Right|      |-------.    ,-------|      |      |      |      |      |      |
     * |------+------+------+------+------+------| Bttn4 |    | Bttn2 |------+------+------+------+------+------|
     * | Shift|      |      |      |      |      |-------|    |-------|      |      |      |      |      | Shift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | Alt  | GUI  | Ctrl |LOWER | /Space  /       \Enter \  |RAISE | Ctrl | GUI  |  Alt |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'            '------''---------------------------'
     */
    [_RAISE] = LAYOUT( \
        KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        KC_GRV,  XXXXXXX, KC_HOME, KC_UP,   KC_END ,  XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        KC_DEL,  XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_BTN4,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
                          _______, _______, _______,  _______, _______,    _______, _______, _______, _______, _______),

    /* ADJUST
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |Qwerty|Colemk|ClmkDH|Dvorak|Workmn|      |                    |      |      |      |      |      | Mute |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |RGB ON| MODE | HUE+ | SAT+ | VAL+ | EFF+ |                    | Mac  |      |      |      | BL+  | Vol+ |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | CAPS |RMODE | HUE- | SAT- | VAL- | EFF- |-------.    ,-------| Win  |      |      |      | BL-  | Vol- |
     * |------+------+------+------+------+------| Bttn3 |    | Bttn3 |------+------+------+------+------+------|
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------|    |-------|  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | Alt  | GUI  | Ctrl |LOWER | /Space  /       \Enter \  |RAISE | Ctrl | GUI  |  Alt |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'            '------''---------------------------'
     */
    [_ADJUST] = LAYOUT( \
        KC_QWERTY, KC_COLEMAK, KC_COLEMAKDH, KC_DVORAK, KC_WORKMAN, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, \
        RGB_TOG,   RGB_MOD,    RGB_HUI,      RGB_SAI,   RGB_VAI,    RGB_SPI,                      AG_NORM, XXXXXXX, XXXXXXX, XXXXXXX, BL_UP,   KC_VOLU, \
        KC_CAPS,   RGB_RMOD,   RGB_HUD,      RGB_SAD,   RGB_VAD,    RGB_SPD,                      AG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, BL_DOWN, KC_VOLD, \
        KC_F1,     KC_F2,      KC_F3,        KC_F4,     KC_F5,      KC_F6,   KC_BTN3,    KC_BTN3, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
                               _______,      _______,   _______,    _______, _______,    _______, _______, _______, _______, _______),

    /* SWITCH
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |      |WhLeft| MsUp |WhRigh| WhUp |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------.    ,-------|      |MsLeft|MsDown|MsRigh|WhDown|      |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|      |Bttn1 |Bttn3 |Bttn2 |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | Alt  | GUI  | Ctrl |NUMPAD| /Space  /       \Enter \  |RAISE | Ctrl | GUI  |  Alt |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'            '------''---------------------------'
     */
    [_SWITCH] = LAYOUT( \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX, \
                          _______, _______, _______, KC_NUMPAD, _______,    _______, _______, _______, _______, _______),

    /* NUMPAD
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    | NUM  |   7  |   8  |   9  |   /  |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |      |   4  |   5  |   6  |   *  |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------.    ,-------|      |   1  |   2  |   3  |   -  |      |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|      |   0  |   .  |      |   +  |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | Alt  | GUI  | Ctrl |LOWER | /Space  /       \Enter \  |RAISE | Ctrl | GUI  |  Alt |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'            '------''---------------------------'
     */
    [_NUMPAD] = LAYOUT( \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_NUM,  KC_P7, KC_P8,   KC_P9,   KC_PSLS, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_P4, KC_P5,   KC_P6,   KC_PAST, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_P1, KC_P2,   KC_P3,   KC_PMNS, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_P0, KC_P0,   XXXXXXX, KC_PPLS, XXXXXXX, \
                          _______, _______, _______, _______, _______,    _______, _______, KC_P0, KC_PDOT, _______),
};
// clang-format on

bool            shift_held = false;
static uint16_t held_shift = 0;

#ifdef RGBLIGHT_ENABLE
//  Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty_lights[] =
    RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_RED));

const rgblight_segment_t PROGMEM layer_colemakdh_lights[] =
    RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_PINK));

// _NUM,
// Light on outer column and underglow
const rgblight_segment_t PROGMEM layer_num_lights[] =
    RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_TEAL));
// _SYMBOL,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_symbol_lights[] =
    RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_BLUE));

// _COMMAND,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_command_lights[] =
    RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_PURPLE));

//_NUMPAD
const rgblight_segment_t PROGMEM layer_numpad_lights[] =
    RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_ORANGE), SET_NUMPAD(HSV_BLUE));

// _SWITCHER
const rgblight_segment_t PROGMEM layer_switcher_lights[] =
    RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_GREEN));

const rgblight_segment_t* const PROGMEM my_rgb_layers[] =
    RGBLIGHT_LAYERS_LIST(

        layer_qwerty_lights,
        layer_num_lights, // overrides layer 1
        layer_symbol_lights, layer_command_lights,
        layer_switcher_lights, // Overrides other layers
        layer_numpad_lights, layer_colemakdh_lights);

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(
        0, layer_state_cmp(state, _DEFAULTS) &&
               layer_state_cmp(default_layer_state, _QWERTY));
    rgblight_set_layer_state(
        7, layer_state_cmp(state, _DEFAULTS) &&
               layer_state_cmp(default_layer_state, _COLEMAKDH));

    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(4, layer_state_cmp(state, _SWITCH));
    rgblight_set_layer_state(5, layer_state_cmp(state, _NUMPAD));
    return state;
}

uint8_t mod_state;

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

    rgblight_mode(
        10); // haven't found a way to set this in a more useful way
}
#endif

#ifdef OLED_ENABLE

#ifdef LOGO
static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x0f, 0x3c, 0x70, 0xc0, 0x80, 0x80, 0xc0, 0x60,
0x70, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x8d, 0xd9, 0x79, 0x31, 0xf1, 0x79, 0x69, 0xcd, 0xc1,
0xc1, 0xc1, 0xf9, 0x19, 0x31, 0xb1, 0x63, 0x63, 0x7a, 0x06, 0x06, 0x02,
0x00, 0x01, 0x07, 0x1c, 0x18, 0xfc, 0xfe, 0x06, 0x06, 0xfe, 0x06, 0x06,
0xfe, 0xfc, 0x00, 0xff, 0x00, 0x00, 0xf8, 0x18, 0xff, 0x18, 0x18, 0x18,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0xe0, 0x78, 0x1c, 0x0f, 0x03, 0x03, 0x06, 0x0c, 0x18, 0x18, 0x30, 0x20,
0x60, 0x60, 0xff, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0xfe, 0xff,
0x01, 0x30, 0x30, 0xff, 0x30, 0x30, 0xff, 0x38, 0x30, 0xfe, 0xfe, 0x30,
0x30, 0xff, 0x30, 0x30, 0xfe, 0x30, 0x30, 0x30, 0x00, 0x00, 0x80, 0xe0,
0x60, 0x7f, 0xff, 0xc1, 0xc1, 0xff, 0xc1, 0xc1, 0xff, 0x7f, 0x01, 0xff,
0x00, 0x00, 0x3f, 0x30, 0xff, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x07, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00, 0x00, 0x00, 0x07,
0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x07, 0x03, 0x03,
0x03, 0x00, 0x00, 0x00, 0x00, 0x06, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00,
0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}
#endif /* LOGO */

/*
 * Remember that much of the status isn't transmitted to the controller over
 * TRRS.
 */
static void print_status_narrow(void) {
    led_t usb_state = host_keyboard_led_state();

    // Print current mode
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        case _COLEMAK:
            oled_write_ln_P(PSTR("Clmk"), false);
            break;
        case _COLEMAKDH:
            oled_write_ln_P(PSTR("CmDH"), false);
            break;
        case _DVORAK:
            oled_write_ln_P(PSTR("Dvrk"), false);
            break;
        case _WORKMAN:
            oled_write_ln_P(PSTR("WrkM"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        case _COLEMAK:
        case _COLEMAKDH:
        case _DVORAK:
        case _WORKMAN:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adj\n"), false);
            break;
        case _SWITCH:
            oled_write_P(PSTR("Swit\n"), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("Nump\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }

    oled_write_P(PSTR("\n"), false);
#    ifdef RGBLIGHT_ENABLE
    // Print LED information
    char buf[3];
    if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
        oled_write("M:", false);
        snprintf(buf, sizeof(buf), "%d", rgblight_get_mode());
        oled_write(buf, false);
        oled_write("\nH:", false);
        snprintf(buf, sizeof(buf), "%d",
                 rgblight_get_hue() / RGBLIGHT_HUE_STEP);
        oled_write(buf, false);
        oled_write("\nS:", false);
        snprintf(buf, sizeof(buf), "%d",
                 rgblight_get_sat() / RGBLIGHT_SAT_STEP);
        oled_write(buf, false);
        oled_write("\nV:", false);
        snprintf(buf, sizeof(buf), "%d",
                 rgblight_get_val() / RGBLIGHT_VAL_STEP);
        oled_write(buf, false);
        oled_write_P(PSTR("\n"), false);
    }
#    endif

    oled_write_P(PSTR("\n"), false);
    if (usb_state.caps_lock)
        oled_write_P(PSTR("CAPS"), false);
    else
        oled_write_P(PSTR("    "), false);
    oled_write_P(PSTR("\n"), false);
    if (usb_state.num_lock)
        oled_write_P(PSTR("NUM"), false);
    else
        oled_write_P(PSTR("   "), false);
    oled_write_P(PSTR("\n"), false);
    if (usb_state.scroll_lock)
        oled_write_P(PSTR("SCLK"), false);
    else
        oled_write_P(PSTR("    "), false);
    oled_write_P(PSTR("\n"), false);

    if (keymap_config.swap_lalt_lgui == false) {
        oled_write_P(PSTR("norm"), false);
    } else {
        oled_write_P(PSTR("swap"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
#    ifdef LOGO
        render_logo();
#    else
        oled_write_ln_P(PSTR("Sofle RGB"), false);
#    endif /* defined LOGO */
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
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
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case KC_COLEMAKDH:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAKDH);
            }
            return false;
        case KC_DVORAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            return false;
        case KC_WORKMAN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WORKMAN);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_NUMPAD:
            if (record->event.pressed) {
                layer_on(_NUMPAD);
            } else {
                layer_off(_NUMPAD);
            }
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
            case _COLEMAK:
            case _COLEMAKDH:
            case _DVORAK:
            case _WORKMAN:
                if (clockwise) {
                    tap_code(KC_MS_L);
                } else {
                    tap_code(KC_MS_R);
                }
                break;
            case _RAISE:
            case _LOWER:
                if (clockwise) {
                    tap_code(KC_WH_L);
                } else {
                    tap_code(KC_WH_R);
                }
                break;
            default:
                if (clockwise) {
                    tap_code(KC_MS_L);
                } else {
                    tap_code(KC_MS_R);
                }
                break;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
            case _COLEMAK:
            case _COLEMAKDH:
            case _DVORAK:
            case _WORKMAN:
                if (clockwise) {
                    tap_code(KC_MS_D);
                } else {
                    tap_code(KC_MS_U);
                }
                break;
            case _RAISE:
            case _LOWER:
                if (clockwise) {
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
                break;
            default:
                if (clockwise) {
                    tap_code(KC_MS_D);
                } else {
                    tap_code(KC_MS_U);
                }
                break;
        }
    }
    return false;
}
#endif

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encover_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY]    = {ENCODER_CCW_CW(KC_MS_U, KC_MS_D),
                    ENCODER_CCW_CW(KC_MS_L, KC_MS_R)},
    [_COLEMAK]   = {ENCODER_CCW_CW(KC_MS_U, KC_MS_D),
                    ENCODER_CCW_CW(KC_MS_L, KC_MS_R)},
    [_COLEMAKDH] = {ENCODER_CCW_CW(KC_MS_U, KC_MS_D),
                    ENCODER_CCW_CW(KC_MS_L, KC_MS_R)},
    [_DVORAK]    = {ENCODER_CCW_CW(KC_MS_U, KC_MS_D),
                    ENCODER_CCW_CW(KC_MS_L, KC_MS_R)},
    [_WORKMAN]   = {ENCODER_CCW_CW(KC_MS_U, KC_MS_D),
                    ENCODER_CCW_CW(KC_MS_L, KC_MS_R)},
    [_LOWER]     = {ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
                    ENCODER_CCW_CW(KC_WH_L, KC_WH_R)},
    [_RAISE]     = {ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
                    ENCODER_CCW_CW(KC_WH_L, KC_WH_R)},
    [_ADJUST]    = {ENCODER_CCW_CW(KC_MS_U, KC_MS_D),
                    ENCODER_CCW_CW(KC_MS_L, KC_MS_R)},
    [_SWITCH]    = {ENCODER_CCW_CW(KC_MS_U, KC_MS_D),
                    ENCODER_CCW_CW(KC_MS_L, KC_MS_R)},
    [_NUMPAD]    = {ENCODER_CCW_CW(KC_MS_U, KC_MS_D),
                    ENCODER_CCW_CW(KC_MS_L, KC_MS_R)},
};
#endif
