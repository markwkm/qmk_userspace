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
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_NUM,  KC_P7,   KC_P8,   KC_P9,   KC_PSLS, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PAST, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_P0,   KC_PDOT, XXXXXXX, KC_PPLS, XXXXXXX, \
                          _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______),
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

#    ifdef LOGO
static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xc0, 0xc0,
        0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0,
        0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x3c, 0x70, 0xc0, 0x80, 0x80,
        0xc0, 0x60, 0x70, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0xff, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x8d, 0xd9, 0x79, 0x31, 0xf1,
        0x79, 0x69, 0xcd, 0xc1, 0xc1, 0xc1, 0xf9, 0x19, 0x31, 0xb1, 0x63,
        0x63, 0x7a, 0x06, 0x06, 0x02, 0x00, 0x01, 0x07, 0x1c, 0x18, 0xfc,
        0xfe, 0x06, 0x06, 0xfe, 0x06, 0x06, 0xfe, 0xfc, 0x00, 0xff, 0x00,
        0x00, 0xf8, 0x18, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x80, 0xe0, 0x78, 0x1c, 0x0f, 0x03, 0x03, 0x06, 0x0c, 0x18, 0x18,
        0x30, 0x20, 0x60, 0x60, 0xff, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00,
        0x00, 0xfe, 0xff, 0x01, 0x30, 0x30, 0xff, 0x30, 0x30, 0xff, 0x38,
        0x30, 0xfe, 0xfe, 0x30, 0x30, 0xff, 0x30, 0x30, 0xfe, 0x30, 0x30,
        0x30, 0x00, 0x00, 0x80, 0xe0, 0x60, 0x7f, 0xff, 0xc1, 0xc1, 0xff,
        0xc1, 0xc1, 0xff, 0x7f, 0x01, 0xff, 0x00, 0x00, 0x3f, 0x30, 0xff,
        0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x07, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x00,
        0x00, 0x00, 0x07, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x03, 0x03,
        0x03, 0x07, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x06, 0x07,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}
#    endif /* LOGO */

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return rotation;
}

bool oled_task_user(void) {
    /* Use MASTER_LEFT and MASTER_RIGHT such that the key map for the left
     * side is always on the left, and the same for the right. */
#    ifdef MASTER_LEFT
    char buf1[2] = "A";
    char buf2[2] = "G";
    char buf3[2] = " ";
    char buf4[2] = " ";
    led_t usb_state = host_keyboard_led_state();

    if (keymap_config.swap_lalt_lgui) {
        buf1[0] = 'G';
        buf2[0] = 'A';
    }
    if (usb_state.caps_lock) buf3[0] = 'C';
    if (usb_state.num_lock) buf4[0] = 'N';

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            /* Max line:          123456789012345678901 */
            oled_write(buf1, false);
            oled_write_P(PSTR("Q| ^[ 1! 2@ 3# 4$ 5%"), false);
            oled_write(buf2, false);
            oled_write_ln_P(PSTR("W| ^I Q  W  E  R  T"), false);
            oled_write(buf3, false);
            oled_write_ln_P(PSTR("E| ^H A  S  D  F  G"), false);
            oled_write(buf4, false);
            oled_write_ln_P(PSTR("R| L2 Z  X  C  V  B"), false);
            break;
        case _COLEMAK:
            oled_write(buf1, false);
            oled_write_P(PSTR("C| ^[ 1! 2@ 3# 4$ 5%"), false);
            oled_write(buf2, false);
            oled_write_ln_P(PSTR("O| ^I Q  W  F  P  B"), false);
            oled_write(buf3, false);
            oled_write_ln_P(PSTR("L| ^H A  R  S  T  D"), false);
            oled_write(buf4, false);
            oled_write_ln_P(PSTR("E| L2 Z  X  C  V  B"), false);
            break;
        case _COLEMAKDH:
            oled_write(buf1, false);
            oled_write_P(PSTR("C| ^[ 1! 2@ 3# 4$ 5%"), false);
            oled_write(buf2, false);
            oled_write_ln_P(PSTR("O| ^I Q  W  F  P  B"), false);
            oled_write(buf3, false);
            oled_write_ln_P(PSTR("D| ^H A  R  S  T  G"), false);
            oled_write(buf4, false);
            oled_write_ln_P(PSTR("H| L2 Z  X  C  D  V"), false);
            break;
        case _DVORAK:
            oled_write(buf1, false);
            oled_write_P(PSTR("D| ^[ 1! 2@ 3# 4$ 5%"), false);
            oled_write(buf2, false);
            oled_write_ln_P(PSTR("V| ^I '\" ,< .> P  Y"), false);
            oled_write(buf3, false);
            oled_write_ln_P(PSTR("O| ^H A  O  E  U  I"), false);
            oled_write(buf4, false);
            oled_write_ln_P(PSTR("R| L2 ;: Q  J  K  X"), false);
            break;
        case _WORKMAN:
            oled_write(buf1, false);
            oled_write_P(PSTR("W| ^[ 1! 2@ 3# 4$ 5%"), false);
            oled_write(buf2, false);
            oled_write_ln_P(PSTR("O| ^I Q  D  R  W  B"), false);
            oled_write(buf3, false);
            oled_write_ln_P(PSTR("R| ^H A  S  H  T  G"), false);
            oled_write(buf4, false);
            oled_write_ln_P(PSTR("K| L2 Z  X  M  C  V"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Sofle RGB"), false);
    }
    switch (get_highest_layer(layer_state)) {
        case _RAISE:
            oled_write(buf1, false);
            oled_write_ln_P(PSTR("R| `"), false);
            oled_write(buf2, false);
            oled_write_ln_P(PSTR("A| `  Ho Up En"), false);
            oled_write(buf3, false);
            oled_write_ln_P(PSTR("I| ^? Le Do Ri"), false);
            oled_write(buf4, false);
            oled_write_ln_P(PSTR("S| L2"), false);
            break;
        case _LOWER:
            oled_write(buf1, false);
            oled_write_ln_P(PSTR("L|"), false);
            oled_write(buf2, false);
            oled_write_P(PSTR("O| ^[ 1! 2@ 3# 4$ 5%"), false);
            oled_write(buf3, false);
            oled_write_ln_P(PSTR("W|"), false);
            oled_write(buf4, false);
            oled_write_ln_P(PSTR("E| SHFT"), false);
            break;
        case _ADJUST:
            oled_write(buf1, false);
            oled_write_ln_P(PSTR("A| QW CO DH DV WO"), false);
            oled_write(buf2, false);
            oled_write_P(PSTR("D| RG M+ H+ S+ V+ E+"), false);
            oled_write(buf3, false);
            oled_write_P(PSTR("J| CL M- H- S- V- E-"), false);
            oled_write(buf4, false);
            oled_write_P(PSTR("U| F1 F2 F3 F4 F5 F6"), false);
            break;
        case _SWITCH:
            oled_write(buf1, false);
            oled_write_ln_P(PSTR("S|"), false);
            oled_write(buf2, false);
            oled_write_ln_P(PSTR("W|"), false);
            oled_write(buf3, false);
            oled_write_ln_P(PSTR("I|"), false);
            oled_write(buf4, false);
            oled_write_ln_P(PSTR("T|"), false);
            break;
        case _NUMPAD:
            oled_write(buf1, false);
            oled_write_ln_P(PSTR("N|"), false);
            oled_write(buf2, false);
            oled_write_ln_P(PSTR("U|"), false);
            oled_write(buf3, false);
            oled_write_ln_P(PSTR("M|"), false);
            oled_write(buf4, false);
            oled_write_ln_P(PSTR("P|"), false);
            break;
        case _QWERTY:
        case _COLEMAK:
        case _COLEMAKDH:
        case _DVORAK:
        case _WORKMAN:
        default:
            break;
    }
#    endif /* MASTER_LEFT */
#    ifdef MASTER_RIGHT
    char bufh[3] = "  ";
    char bufm[3] = "  ";
    char bufs[3] = "  ";
    char bufv[3] = "  ";
#        ifdef RGBLIGHT_ENABLE
    if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
        snprintf(bufm, sizeof(bufm), "%2d", rgblight_get_mode());
    }
    if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
        snprintf(bufh, sizeof(bufh), "%2d",
                 rgblight_get_hue() / RGBLIGHT_HUE_STEP);
    }
    if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
        snprintf(bufs, sizeof(bufs), "%2d",
                 rgblight_get_sat() / RGBLIGHT_SAT_STEP);
    }
    if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
        snprintf(bufv, sizeof(bufv), "%2d",
                 rgblight_get_val() / RGBLIGHT_VAL_STEP);
    }
#        endif
#        ifdef LOGO
    render_logo();
#        else
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write(bufm, false);
            oled_write_P(PSTR("|6^ 7& 8* 9( 0) INS"), false);
            oled_write(bufh, false);
            oled_write_ln_P(PSTR("|Y  U  I  O  P  \\|"), false);
            oled_write(bufs, false);
            oled_write_ln_P(PSTR("|H  J  K  L  ;: '\""), false);
            oled_write(bufv, false);
            oled_write_ln_P(PSTR("|N  M  ,< .> /? L2"), false);
            break;
        case _COLEMAK:
            oled_write(bufm, false);
            oled_write_P(PSTR("|6^ 7& 8* 9( 0) INS"), false);
            oled_write(bufh, false);
            oled_write_ln_P(PSTR("|J  L  U  Y  ;: \\|"), false);
            oled_write(bufs, false);
            oled_write_ln_P(PSTR("|H  N  E  I  O  '\""), false);
            oled_write(bufv, false);
            oled_write_ln_P(PSTR("|K  M  ,< .> /? L2"), false);
            break;
        case _COLEMAKDH:
            oled_write(bufm, false);
            oled_write_P(PSTR("|6^ 7& 8* 9( 0) INS"), false);
            oled_write(bufh, false);
            oled_write_ln_P(PSTR("|J  L  U  Y  ;  \\"), false);
            oled_write(bufs, false);
            oled_write_ln_P(PSTR("|M  N  E  I  O  '"), false);
            oled_write(bufv, false);
            oled_write_ln_P(PSTR("|K  H  ,< .> /  L2"), false);
            break;
        case _DVORAK:
            oled_write(bufm, false);
            oled_write_P(PSTR("|6^ 7& 8* 9( 0) INS"), false);
            oled_write(bufh, false);
            oled_write_ln_P(PSTR("|F  G  C  R  L  \\"), false);
            oled_write(bufs, false);
            oled_write_ln_P(PSTR("|D  H  I  N  S  /"), false);
            oled_write(bufv, false);
            oled_write_ln_P(PSTR("|B  M  W  V  Z  L2"), false);
            break;
        case _WORKMAN:
            oled_write(bufm, false);
            oled_write_P(PSTR("|6^ 7& 8* 9( 0) INS"), false);
            oled_write(bufh, false);
            oled_write_ln_P(PSTR("|J  F  U  P  ;  \\"), false);
            oled_write(bufs, false);
            oled_write_ln_P(PSTR("|Y  N  E  O  I  '"), false);
            oled_write(bufv, false);
            oled_write_ln_P(PSTR("|K  L  ,< .> /  L2"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Sofle RGB"), false);
    }
    switch (get_highest_layer(layer_state)) {
        case _RAISE:
            oled_write(bufm, false);
            oled_write_ln_P(PSTR("|"), false);
            oled_write(bufh, false);
            oled_write_ln_P(PSTR("|"), false);
            oled_write(bufs, false);
            oled_write_ln_P(PSTR("|"), false);
            oled_write(bufv, false);
            oled_write_ln_P(PSTR("|               L2"), false);
            break;
        case _LOWER:
            oled_write(bufm, false);
            oled_write_ln_P(PSTR("|"), false);
            oled_write(bufh, false);
            oled_write_P(PSTR("|6^ 7& 8* 9( 0) INS"), false);
            oled_write(bufs, false);
            oled_write_ln_P(PSTR("|PU -  +  _  ="), false);
            oled_write(bufv, false);
            oled_write_ln_P(PSTR("|PD [  ]  {  }  L2"), false);
            break;
        case _ADJUST:
            oled_write(bufm, false);
            oled_write_ln_P(PSTR("|               MU"), false);
            oled_write(bufh, false);
            oled_write_ln_P(PSTR("|MA          B+ V+"), false);
            oled_write(bufs, false);
            oled_write_ln_P(PSTR("|WI          B- V-"), false);
            oled_write(bufv, false);
            oled_write_ln_P(PSTR("|F7 F8 F9 10 11 12"), false);
            break;
        case _SWITCH:
            oled_write(bufm, false);
            oled_write_ln_P(PSTR("|"), false);
            oled_write(bufh, false);
            oled_write_ln_P(PSTR("|   WL MU WR WU"), false);
            oled_write(bufs, false);
            oled_write_ln_P(PSTR("|   ML MD MR WD"), false);
            oled_write(bufv, false);
            oled_write_ln_P(PSTR("|   B1 B3 B2"), false);
            break;
        case _NUMPAD:
            oled_write(bufm, false);
            oled_write_ln_P(PSTR("|NL 7  8  9  /"), false);
            oled_write(bufh, false);
            oled_write_ln_P(PSTR("|   4  5  6  *"), false);
            oled_write(bufs, false);
            oled_write_ln_P(PSTR("|   1  2  3  -"), false);
            oled_write(bufv, false);
            oled_write_ln_P(PSTR("|   0  .     +"), false);
            break;
        case _QWERTY:
        case _COLEMAK:
        case _COLEMAKDH:
        case _DVORAK:
        case _WORKMAN:
        default:
            break;
    }
#        endif /* defined LOGO */
#    endif     /* MASTER_RIGHT */
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
