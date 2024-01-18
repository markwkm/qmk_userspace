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
#pragma once

// #define USE_MATRIX_I2C
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_OLED_ENABLE

/* Select hand configuration */

/// https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/

// #define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define CUSTOM_FONT

#define CUSTOM_LAYER_READ // if you remove this it causes issues - needs
                          // better guarding

#define QUICK_TAP_TERM 0
#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#    define TAPPING_TERM 200
#endif
#define ENCODER_DIRECTION_FLIP

#define RGBLIGHT_SLEEP
//
#define RGBLIGHT_LAYERS

/* ws2812 RGB LED */
#define WS2812_DI_PIN D3

/*
 * Use the number of LEDs for the values. For example, if there are no LEDs
 * installed for the indicator, set HAS_RGB_INDICATOR to 0.
 */
#define RGB_INDICATOR 1
#define RGB_DROP 6
#define RGB_PER_KEY 29
#define RGBLED_NUM \
    RGB_INDICATOR + RGB_DROP + RGB_PER_KEY // Number of LEDs per half

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_COUNT RGBLED_NUM
#endif

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE

#    define RGBLED_SPLIT           \
        {                          \
            RGBLED_NUM, RGBLED_NUM \
        } // haven't figured out how to use this yet

#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP 10
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_VAL_STEP 17
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES          // reacts to keypresses
#    define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when
                                           // suspended
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS \
        150 // limits maximum brightness of LEDs to 150 out of 255. Higher
            // may cause the controller to crash.

#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_GRADIENT_LEFT_RIGHT

#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10
#endif
