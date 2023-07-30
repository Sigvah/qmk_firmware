/**
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

enum charybdis_keymap_bstiq_layers {
    LAYER_BASE = 0,
    LAYER_MBO,
    LAYER_MEDIA,
    LAYER_NAV,
    LAYER_MOUSE,
    LAYER_SYM,
    LAYER_NUM,
    LAYER_FUN,
};

// Automatically enable sniping when the mouse layer is on.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_MOUSE

#define ESC_NAV LT(LAYER_NAV, KC_ESC)
#define TAB_SYM LT(LAYER_SYM, KC_TAB)
#define ENT_SFT LSFT_T(KC_ENT)
#define BAC_SYM LT(LAYER_SYM, KC_BSPC)
#define SPC_NUM LT(LAYER_NUM, KC_SPC)
#define MOUSE(KC) LT(LAYER_MOUSE, KC)

#define USR_RDO KC_AGAIN
#define USR_PST LCTL(KC_V)
#define USR_CPY LCTL(KC_C)
#define USR_CUT LCTL(KC_X)
#define USR_UND KC_UNDO

#define MS_L KC_MS_LEFT
#define MS_R KC_MS_RIGHT
#define MS_D KC_MS_DOWN
#define MS_U KC_MS_UP

#define WH_L KC_MS_WH_LEFT
#define WH_R KC_MS_WH_RIGHT
#define WH_D KC_MS_WH_DOWN
#define WH_U KC_MS_WH_UP

// clang-format off
/** Convenience macro. */
#define _KC_LAYOUT_wrapper(                                                                             \
         k00,      k01,      k02,      k03,      k04,      k05,      k06,      k07,      k08,      k09, \
         k10,      k11,      k12,      k13,      k14,      k15,      k16,      k17,      k18,      k19, \
         k20,      k21,      k22,      k23,      k24,      k25,      k26,      k27,      k28,      k29, \
         ...)                                                                                           \
    NO_##k00, NO_##k01, NO_##k02, NO_##k03, NO_##k04, NO_##k05, NO_##k06, NO_##k07, NO_##k08, NO_##k09, \
    NO_##k10, NO_##k11, NO_##k12, NO_##k13, NO_##k14, NO_##k15, NO_##k16, NO_##k17, NO_##k18, NO_##k19, \
    NO_##k20, NO_##k21, NO_##k22, NO_##k23, NO_##k24, NO_##k25, NO_##k26, NO_##k27, NO_##k28, NO_##k29, \
    __VA_ARGS__
#define KC_LAYOUT_wrapper(...) _KC_LAYOUT_wrapper(__VA_ARGS__)

/** Base layer with BÉPO layout. */
#define LAYOUT_LAYER_BASE_BEPO KC_LAYOUT_wrapper(               \
       Q,    W,    F,    P,    B,    J,    L,    U,    Y, QUOT, \
       A,    R,    S,    T,    G,    M,    N,    E,    I,    O, \
       Z,    X,    C,    D,    V,    K,    H, COMM,  DOT, MINS, \
       ESC_NAV, TAB_SYM, ENT_SFT,    BAC_SYM, SPC_NUM)

/** Convenience key shorthands. */
#define U_NA KC_NO // Present but not available for use.
#define U_NU KC_NO // Available but not used.

/** Convenience row shorthands. */
#define __________________RESET_L__________________ QK_BOOT,    U_NA,    U_NA,    U_NA,    U_NA
#define __________________RESET_R__________________    U_NA,    U_NA,    U_NA,    U_NA, QK_BOOT
#define ______________HOME_ROW_GASC_L______________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL,    U_NA
#define ______________HOME_ROW_GASC_L_MAC__________ KC_LCTL, KC_LALT, KC_LSFT, KC_LGUI,    U_NA
#define ______________HOME_ROW_ALGR_L______________    U_NA, KC_ALGR,    U_NA,    U_NA,    U_NA
#define ______________HOME_ROW_GASC_R______________    U_NA, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI
#define ______________HOME_ROW_GASC_R_MAC__________    U_NA, KC_LGUI, KC_LSFT,  KC_CTL, KC_LGUI
#define ______________HOME_ROW_ALGR_R______________    U_NA,    U_NA,    U_NA, KC_ALGR,    U_NA

/** Layers. */

// Buttons.
#define LAYOUT_LAYER_MBO                                                                      \
    __________________RESET_L__________________, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    ______________HOME_ROW_GASC_L______________, KC_CAPS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, \
    KC_BTN3, KC_ALGR, KC_BTN2, KC_BTN1,    U_NA,  KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, \
                         U_NA,    U_NA,    U_NA,  KC_ENT,  KC_DEL

// Media. Bytt denne ut.
#define LAYOUT_LAYER_MEDIA                                                                    \
    __________________RESET_L__________________, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_DEL,    U_NU,    MS_L,    MS_D,    MS_U,    MS_R, \
    KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_DEL,    U_NU,    WH_L,    WH_D,    WH_U,    WH_R, \
                         U_NA,    U_NA,    U_NA, KC_BTN1, KC_BTN3

// Navigation.
#define LAYOUT_LAYER_NAV                                                                      \
    __________________RESET_L__________________, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, \
    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_DEL, ______________HOME_ROW_GASC_R______________, \
    KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_DEL,    U_NU, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, \
                         U_NA,    U_NA,    U_NA, KC_MSTP, KC_MPLY

// Mouse.
#define LAYOUT_LAYER_MOUSE                                                                    \
    S_D_MOD, USR_PST, USR_CPY, USR_CUT, USR_UND, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    DPI_MOD, DRGSCRL, KC_LSFT, KC_LCTL, _______, KC_CAPS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, \
    USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND,    U_NU,    WH_L,    WH_D,    WH_U,    WH_R, \
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN1, KC_BTN3

// Symbols.
#define LAYOUT_LAYER_SYM                                                                      \
    NO_LCBR, NO_AMPR, NO_ASTR, NO_LPRN, NO_RCBR, __________________RESET_R__________________, \
    NO_COLN,  NO_DLR, NO_PERC, NO_CIRC, NO_PLUS, ______________HOME_ROW_GASC_R______________, \
    NO_TILD, NO_EXLM,   NO_AT, NO_HASH, NO_PIPE, ______________HOME_ROW_ALGR_R______________, \
                      NO_LPRN, NO_RPRN, NO_UNDS,    U_NA,    U_NA

// Numerals.
#define LAYOUT_LAYER_NUM                                                                      \
    NO_LBRC,    NO_7,    NO_8,    NO_9, NO_RBRC, __________________RESET_R__________________, \
    NO_SCLN,    NO_4,    NO_5,    NO_6,  NO_EQL, ______________HOME_ROW_GASC_R______________, \
     NO_GRV,    NO_1,    NO_2,    NO_3, NO_BSLS,  KC_F12,  KC_F12,   KC_F2,   KC_F5, KC_PSCR, \
                       NO_DOT,    NO_0, NO_MINS,    U_NA,    U_NA

// Function keys.
#define LAYOUT_LAYER_FUN                                                                      \
     KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR, __________________RESET_R__________________, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL, ______________HOME_ROW_GASC_R______________, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS, ______________HOME_ROW_ALGR_R______________,\
                       KC_APP,  KC_SPC,  KC_TAB,    U_NA,    U_NA

/**
 * Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GASC (Gui, Alt, Shift, Ctl)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYOUT_LAYER_BASE_BEPO` defined above, eg.:
 *
 *     HOME_ROW_MOD_GASC(LAYOUT_LAYER_BASE_BEPO)
 */
#define _HOME_ROW_MOD_GASC(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LSFT_T(L12), LCTL_T(L13),        L14,  \
             R15,  RCTL_T(R16), RSFT_T(R17), LALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GASC(...) _HOME_ROW_MOD_GASC(__VA_ARGS__)

/**
 * Add mouse layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYOUT_LAYER_BASE_BEPO` defined above, eg.:
 *
 *     MOUSE_MOD(LAYOUT_LAYER_BASE_BEPO)
 */
#define _MOUSE_MOD(                                               \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,             \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,             \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,             \
    ...)                                                          \
            L00,        L01,        L02,        L03,        L04,  \
            R05,        R06,        R07,        R08,        R09,  \
            L10,        L11,        L12,        L13,        L14,  \
            R15,        R16,        R17,        R18,        R19,  \
      MOUSE(L20),       L21,        L22,        L23,        L24,  \
            R25,        R26,        R27,        R28,  MOUSE(R29), \
      __VA_ARGS__
#define MOUSE_MOD(...) _MOUSE_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    MOUSE_MOD(HOME_ROW_MOD_GASC(LAYOUT_LAYER_BASE_BEPO))
  ),
  [LAYER_MBO] = LAYOUT_wrapper(LAYOUT_LAYER_MBO),
  [LAYER_MEDIA] = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
  [LAYER_NAV] = LAYOUT_wrapper(LAYOUT_LAYER_NAV),
  [LAYER_MOUSE] = LAYOUT_wrapper(LAYOUT_LAYER_MOUSE),
  [LAYER_SYM] = LAYOUT_wrapper(LAYOUT_LAYER_SYM),
  [LAYER_NUM] = LAYOUT_wrapper(LAYOUT_LAYER_NUM),
  [LAYER_FUN] = LAYOUT_wrapper(LAYOUT_LAYER_FUN),
};
// clang-format on

#if defined(POINTING_DEVICE_ENABLE) && defined(CHARYBDIS_AUTO_SNIPING_ON_LAYER)
layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#endif // POINTING_DEVICE_ENABLE && CHARYBDIS_AUTO_SNIPING_ON_LAYER

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb(RGB_RED);
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif // RGB_MATRIX_ENABLE
}
