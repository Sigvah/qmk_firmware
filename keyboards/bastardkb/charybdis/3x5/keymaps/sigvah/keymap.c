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
#include "config.h"
#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "keymap_norwegian.h"
#include "keymap_norwegian_mac.h"

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_SLSH:
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}
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

// Define custom keycodes
enum keycodes {
    // keys that differ between Mac and PC
    CX_AT = QK_USER,
    CX_DLR,
    CX_BSLS,
    CX_PIPE,
    CX_LCBR,
    CX_RCBR,
    CX_TILD,
    CX_QUOT,
    CX_PND,
    CX_EURO,
    CX_PVWD,
    CX_NXWD,
    CX_UNDO,
    CX_CUT,
    CX_COPY,
    CX_PSTE,
};


// ---------------AUTO MOUSE----------------
// bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record) {
//     switch(keycode) {
//         case DRGSCRL:
//             return true;
//         default:
//             return false;
//     }
// }

// void pointing_device_init_user(void) {
//     set_auto_mouse_enable(true);
// }
// -----------------------------------------

// ---------------OS CHECKER----------------
#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)

os_variant_t os_type;

uint32_t startup_exec(uint32_t trigger_time, void *cb_arg) {
    if (is_keyboard_master()) {
        os_type = detected_host_os();
        if (os_type) {
            bool is_mac = (os_type == OS_MACOS) || (os_type == OS_IOS);
            if (keymap_config.swap_lctl_lgui != is_mac) {
                keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = is_mac;
                eeconfig_update_keymap(keymap_config.raw);
            }


#    ifdef UNICODE_COMMON_ENABLE
            set_unicode_input_mode_soft(keymap_config.swap_lctl_lgui ? UNICODE_MODE_MACOS : UNICODE_MODE_WINCOMPOSE);
#    endif
            switch (os_type) {
                case OS_UNSURE:
                    break;
                case OS_LINUX:
                    break;
                case OS_WINDOWS:
                    break;
#    if 0
                case OS_WINDOWS_UNSURE:
                    break;
#    endif
                case OS_MACOS:
                    break;
                case OS_IOS:
                    break;
#    if 0
                case OS_PS5:
                    break;
                case OS_HANDHELD:
                    break;
#    endif
            }
        }
    }

    return os_type ? 0 : 500;
}
#endif
void keyboard_post_init_user(void) {


#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
    defer_exec(100, startup_exec, NULL);
#endif
}

// -----------------------------------------


enum combos {
  NN_AA,
  GO_AE,
  GI_OE,
  BK_SP_DEL,
  ENT_SFT_ESC,
  ZX_F2,
  XC_F12,
  GM_CWT
};

const uint16_t PROGMEM ae_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM ai_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM ao_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM bk_combo[] = {RSFT_T(KC_BSPC), LT(LAYER_NUM, KC_SPC), COMBO_END};
const uint16_t PROGMEM es_combo[] = {LT(LAYER_SYM, KC_ENT), LT(LAYER_NAV, KC_TAB), COMBO_END};
const uint16_t PROGMEM zx_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM gm_combo[] = {KC_G, KC_M, COMBO_END};


combo_t key_combos[] = {
  [NN_AA] = COMBO(ae_combo, KC_LBRC),
  [GO_AE] = COMBO(ai_combo, KC_QUOT),
  [GI_OE] = COMBO(ao_combo, KC_SCLN),
  [BK_SP_DEL] = COMBO(bk_combo, KC_DEL),
  [ENT_SFT_ESC] = COMBO(es_combo, KC_ESC),
  [ZX_F2] = COMBO(zx_combo, KC_F2),
  [XC_F12] = COMBO(xc_combo, KC_F12),
    [GM_CWT] = COMBO(gm_combo, CW_TOGG),
};

// Automatically enable sniping when the mouse layer is on.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_MOUSE

#define ESC_NAV LT(LAYER_NAV, KC_ESC)
#define BAC_NUM LT(LAYER_NUM, KC_BSPC)
#define TAB_SFT LSFT_T(KC_TAB)
#define ENT_SFT RSFT_T(KC_ENT)
#define SPC_SYM LT(LAYER_SYM, KC_SPC)
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
       Q,    W,    F,    P,    B,    J,    L,    U,    Y, PLUS, \
       A,    R,    S,    T,    G,    M,    N,    E,    I,    O, \
       Z,    X,    C,    D,    V,    K,    H, COMM,  DOT, MINS, \
       ESC_NAV, SPC_SYM, TAB_SFT,    ENT_SFT, BAC_NUM)

/** Convenience key shorthands. */
#define U_NA KC_NO // Present but not available for use.
#define U_NU KC_NO // Available but not used.

/** Convenience row shorthands. */
#define __________________RESET_L__________________ QK_BOOT,    U_NA,    U_NA,    U_NA,    U_NA
#define __________________RESET_R__________________    U_NA,    U_NA,    U_NA,    U_NA, QK_BOOT
#define ______________HOME_ROW_GASC_L______________ KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL,    U_NA
#define ______________HOME_ROW_GASC_L_MAC__________ KC_LCTL, KC_LALT, KC_LSFT, KC_LGUI,    U_NA
#define ______________HOME_ROW_GASC_R______________    U_NA, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT
#define ______________HOME_ROW_GASC_R_MAC__________    U_NA, KC_LGUI, KC_LSFT,  KC_CTL, KC_LGUI

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
    __________________RESET_L__________________,    U_NU, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, \
    KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_CAPS, ______________HOME_ROW_GASC_R______________, \
    KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_DEL,    U_NU, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, \
                         U_NA,    U_NA,    U_NA, KC_MUTE, KC_MPLY

// Mouse.
#define LAYOUT_LAYER_MOUSE                                                                    \
    QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, DPI_RMOD, S_D_MOD, DPI_MOD, XXXXXXX, EE_CLR,  QK_BOOT, \
    _______, DRGSCRL, SNIPING, KC_LCTL,    U_NA, ______________HOME_ROW_GASC_R______________, \
    _______, DRGSCRL, SNIPING, QK_BOOT,  EE_CLR, KC_BTN2,  KC_BTN1, KC_BTN2, DRGSCRL, _______, \
                      DRGSCRL, KC_BTN1, KC_BTN2, OSM(MOD_LSFT), KC_BTN1

// Symbols.
#define LAYOUT_LAYER_SYM                                                                      \
    __________________RESET_L__________________, NO_PERC,   CX_AT, NO_DQUO, NO_AMPR,  NO_GRV, \
    ______________HOME_ROW_GASC_L______________, NO_HASH, NO_LPRN, CX_LCBR, NO_LBRC, CX_QUOT, \
    KC_F12,   KC_F12,   KC_F2,   KC_F5, CW_TOGG,  CX_DLR, NO_RPRN, CX_RCBR, NO_RBRC, CX_TILD, \
                               U_NA, U_NA, U_NA,    U_NA,    U_NA

// Numerals.
#define LAYOUT_LAYER_NUM                                                                      \
    CX_BSLS,    NO_7,    NO_8,    NO_9, NO_EXLM, CX_EURO,   CX_PND, CX_DLR, KC_SLEP, NO_ARNG, \
    CX_PIPE,    NO_4,    NO_5,    NO_6,  NO_EQL, ______________HOME_ROW_GASC_R______________, \
    NO_SLSH,    NO_1,    NO_2,    NO_3, NO_ASTR,  KC_F12,   NO_AE, NO_OSTR, NO_ARNG, NO_ARNG, \
                      NO_LABK,    NO_0, NO_RABK,    U_NA,    U_NA

// Function keys.
#define LAYOUT_LAYER_FUN                                                                      \
     KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR, __________________RESET_R__________________, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL, ______________HOME_ROW_GASC_R______________, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS, ______________HOME_ROW_GASC_R______________,\
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
             L10, LGUI_T(L11), LALT_T(L12), LCTL_T(L13),         L14,  \
             R15,  RCTL_T(R16), LALT_T(R17), RGUI_T(R18),        R19, \
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
     MOUSE(L10),        L11,        L12,        L13,        L14,  \
            R15,        R16,        R17,        R18,        R19,  \
            L20,       L21,         L22,        L23,        L24,  \
            R25,        R26,        R27,        R28, MOUSE(R29), \
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool is_apple;
    is_apple = (os_type == OS_MACOS) || (os_type == OS_IOS);
    switch (keycode) {

        // Handle keycodes that differ between Mac and PC
        case CX_AT:
            if(record->event.pressed) {
                register_code16((is_apple) ? MAC_AT : NO_AT);
            } else {
                unregister_code16((is_apple) ? MAC_AT : NO_AT);
            }
            return false;
        break;
        case CX_DLR:
            if(record->event.pressed) {
                register_code16((is_apple) ? MAC_DLR : NO_DLR);
            } else {
                unregister_code16((is_apple) ? MAC_DLR : NO_DLR);
            }
            return false;
        break;
        case CX_BSLS:
            if(record->event.pressed) {
                register_code16((is_apple) ? MAC_BSLS : NO_BSLS);
            } else {
                unregister_code16((is_apple) ? MAC_BSLS : NO_BSLS);
            }
            return false;
        break;
        case CX_PIPE:
            if(record->event.pressed) {
                register_code16((is_apple) ? MAC_PIPE : NO_PIPE);
            } else {
                unregister_code16((is_apple) ? MAC_PIPE : NO_PIPE);
            }
            return false;
        break;
        case CX_LCBR:
            if(record->event.pressed) {
                register_code16((is_apple) ? MAC_LCBR : NO_LCBR);
            } else {
                unregister_code16((is_apple) ? MAC_LCBR : NO_LCBR);
            }
            return false;
        break;
        case CX_RCBR:
            if(record->event.pressed) {
                register_code16((is_apple) ? MAC_RCBR : NO_RCBR);
            } else {
                unregister_code16((is_apple) ? MAC_RCBR : NO_RCBR);
            }
            return false;
        break;
        case CX_PND:
            if(record->event.pressed) {
                register_code16((is_apple) ? MAC_PND : NO_PND);
            } else {
                unregister_code16((is_apple) ? MAC_PND : NO_PND);
            }
            return false;
        break;
        case CX_EURO:
            if(record->event.pressed) {
                register_code16((is_apple) ? MAC_EURO : NO_EURO);
            } else {
                unregister_code16((is_apple) ? MAC_EURO : NO_EURO);
            }
            return false;
        break;
        case CX_TILD:
            if(record->event.pressed) {
                register_code16((is_apple) ? MAC_TILD : NO_TILD);
            } else {
                unregister_code16((is_apple) ? MAC_TILD : NO_TILD);
            }
            return false;
        break;
        case CX_QUOT:
            if(record->event.pressed) {
                register_code16((is_apple) ? MAC_QUOT : NO_QUOT);
            } else {
                unregister_code16((is_apple) ? MAC_QUOT : NO_QUOT);
            }
            return false;
        break;

    }

    return true;
}
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(LAYER_MOUSE, KC_A):
            return TAPPING_TERM + 40;
        case LGUI_T(KC_R):
            return TAPPING_TERM + 35;
        case LALT_T(KC_S):
            return TAPPING_TERM + 30;
        case LGUI_T(KC_O):
            return TAPPING_TERM + 35;
        case LALT_T(KC_I):
            return TAPPING_TERM + 30;
        default:
            return TAPPING_TERM;
    }
}
