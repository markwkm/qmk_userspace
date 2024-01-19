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

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_USB_DETECT

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

/* ws2812 RGB LED */
#define WS2812_DI_PIN D3

#define INDICATOR_BRIGHTNESS 30

/*
 * Use the number of LEDs for the values. For example, if there are no LEDs
 * installed for the indicator, set HAS_RGB_INDICATOR to 0.
 */
#define RGB_INDICATOR 1
#define RGB_DROP 6
#define RGB_PER_KEY 29

#define RGBLED_NUM \
    RGB_INDICATOR + RGB_DROP + RGB_PER_KEY // Number of LEDs per half
#define RGBLED_SPLIT \
    { RGBLED_NUM, RGBLED_NUM }

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_MAX_LAYERS 16

#    define RGBLIGHT_LIMIT_VAL 150
#    define RGBLIGHT_SPLIT

#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_TWINKLE
#endif

#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR

#    define RGB_MATRIX_SPLIT \
        { RGBLED_NUM, RGBLED_NUM }
#    undef RGBLED_NUM
#    define RGBLED_NUM                                           \
        RGB_INDICATOR + RGB_DROP + RGB_PER_KEY + RGB_INDICATOR + \
            RGB_DROP + RGB_PER_KEY
#    define RGB_MATRIX_LED_COUNT                                 \
        RGB_INDICATOR + RGB_DROP + RGB_PER_KEY + RGB_INDICATOR + \
            RGB_DROP + RGB_PER_KEY
#    define DRIVER_LED_TOTAL RGB_MATRIX_LED_COUNT
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// limits maximum brightness of LEDs to 150 out of 255. Higher
// may cause the controller to crash.
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150

// #    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_GRADIENT_LEFT_RIGHT

#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_LED_MATRIX_BREATHING
#    define ENABLE_LED_MATRIX_BAND
#    define ENABLE_LED_MATRIX_BAND_PINWHEEL
#    define ENABLE_LED_MATRIX_BAND_SPIRAL
#    define ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_LED_MATRIX_CYCLE_UP_DOWN
#    define ENABLE_LED_MATRIX_CYCLE_OUT_IN
#    define ENABLE_LED_MATRIX_DUAL_BEACON
#    define ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT
#    define ENABLE_LED_MATRIX_WAVE_UP_DOWN

#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_BREATHING
#    define ENABLE_RGB_MATRIX_BAND_SAT
#    define ENABLE_RGB_MATRIX_BAND_VAL
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    define ENABLE_RGB_MATRIX_CYCLE_ALL
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN Enables
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define ENABLE_RGB_MATRIX_DUAL_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    define ENABLE_RGB_MATRIX_FLOWER_BLOOMING
#    define ENABLE_RGB_MATRIX_RAINDROPS
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    define ENABLE_RGB_MATRIX_HUE_BREATHING
#    define ENABLE_RGB_MATRIX_HUE_PENDULUM
#    define ENABLE_RGB_MATRIX_HUE_WAVE
#    define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#    define ENABLE_RGB_MATRIX_PIXEL_FLOW
#    define ENABLE_RGB_MATRIX_PIXEL_RAIN
#    define ENABLE_RGB_MATRIX_STARLIGHT
#    define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE
#    define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT
#    define ENABLE_RGB_MATRIX_RIVERFLOW

#    define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#    define ENABLE_RGB_MATRIX_DIGITAL_RAIN

#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    define ENABLE_RGB_MATRIX_SPLASH
#    define ENABLE_RGB_MATRIX_MULTISPLASH
#    define ENABLE_RGB_MATRIX_SOLID_SPLASH
#    define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#    define MEDIA_KEY_DELAY 2
#    define USB_POLLING_INTERVAL_MS 1
#endif
