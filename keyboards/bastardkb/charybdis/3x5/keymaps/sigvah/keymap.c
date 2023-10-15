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
    CX_ISMAC,
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

// ---------------OS CHECKER----------------

// ---------------COMBOS----------------
enum combos {
  NN_AA,
  GO_AE,
  GI_OE,
  ZX_F2,
  XC_F12,
  GM_CWT,
  DH_ESC,
  WF_F4,
  UY_DEL,
  SPC_TAB_ESC,
  BCK_ENT_DEL,
  NE_LPRN,
  EI_RPRN,
  LU_QUES,
};
_Bool isMac = true;
const uint16_t PROGMEM ae_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM ai_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM ao_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM bk_combo[] = {RSFT_T(KC_BSPC), LT(LAYER_NUM, KC_SPC), COMBO_END};
const uint16_t PROGMEM zx_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM gm_combo[] = {LT(LAYER_SYM, KC_SPC), LT(LAYER_NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM dh_combo[] = {KC_D, KC_H, COMBO_END};
const uint16_t PROGMEM wf_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM uy_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM spc_tab_esc_combo[] = {LT(LAYER_NAV, KC_SPC), LT(LAYER_FUN, KC_TAB), COMBO_END};
const uint16_t PROGMEM bck_ent_del_combo[] = {LT(LAYER_NUM, KC_BSPC), LT(LAYER_SYM, KC_ENT), COMBO_END};
const uint16_t PROGMEM ne_lprn_combo[] = {RCTL_T(KC_E), RSFT_T(KC_N), COMBO_END};
const uint16_t PROGMEM ei_rprn_combo[] = {RCTL_T(KC_E), LALT_T(KC_I), COMBO_END};
const uint16_t PROGMEM lu_ques_combo[] = {KC_L, KC_U, COMBO_END};


combo_t key_combos[] = {
  [NN_AA] = COMBO(ae_combo, KC_LBRC),
  [GO_AE] = COMBO(ai_combo, KC_QUOT),
  [GI_OE] = COMBO(ao_combo, KC_SCLN),
  [ZX_F2] = COMBO(zx_combo, KC_F2),
  [XC_F12] = COMBO(xc_combo, KC_F12),
  [GM_CWT] = COMBO(gm_combo, CW_TOGG),
  [DH_ESC] = COMBO(dh_combo, KC_ESC),
  [WF_F4] = COMBO(wf_combo, KC_F4),
  [UY_DEL] = COMBO(uy_combo, KC_DEL),
  [SPC_TAB_ESC] = COMBO(spc_tab_esc_combo, KC_ESC),
  [BCK_ENT_DEL] = COMBO(bck_ent_del_combo, KC_DEL),
  [NE_LPRN] = COMBO(ne_lprn_combo, NO_LPRN),
  [EI_RPRN] = COMBO(ei_rprn_combo, NO_RPRN),
    [LU_QUES] = COMBO(lu_ques_combo, NO_QUES),
};
// -----------------------------------------

// Automatically enable sniping when the mouse layer is on.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_MOUSE

#define ESC_NAV LT(LAYER_NAV, KC_ESC)
#define BAC_NUM LT(LAYER_NUM, KC_BSPC)
#define TAB_FUN LT(LAYER_FUN, KC_TAB)
#define ENT_SYM LT(LAYER_SYM, KC_ENT)
#define SPC_NAV LT(LAYER_NAV, KC_SPC)
#define MOUSE(KC) LT(LAYER_MOUSE, KC)
#define ESC_SLP LT(KC_SLEP, KC_ESC)
#define HYP_ESC LCMD_T(LCTL_T(LALT_T(KC_ESC)))
#define X_DRG LT(DRGSCRL, KC_X)

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
    NO_##k00, NO_##k01, NO_##k02, NO_##k03, NO_##k04, NO_##k05, NO_##k06, NO_##k07, NO_##k08, CX_##k09, \
    NO_##k10, NO_##k11, NO_##k12, NO_##k13, NO_##k14, NO_##k15, NO_##k16, NO_##k17, NO_##k18, NO_##k19, \
    NO_##k20, NO_##k21, NO_##k22, NO_##k23, NO_##k24, NO_##k25, NO_##k26, NO_##k27, NO_##k28, NO_##k29, \
    __VA_ARGS__
#define KC_LAYOUT_wrapper(...) _KC_LAYOUT_wrapper(__VA_ARGS__)

/** Base layer with BÉPO layout. */
#define LAYOUT_LAYER_BASE_BEPO KC_LAYOUT_wrapper(               \
       Q,    W,    F,    P,    B,    J,    L,    U,    Y, QUOT, \
       A,    R,    S,    T,    G,    M,    N,    E,    I,    O, \
       Z,    X,    C,    D,    V,    K,    H, COMM,  DOT, MINS, \
       KC_ESC, SPC_NAV, TAB_FUN,    ENT_SYM, BAC_NUM)

/** Convenience key shorthands. */
#define U_NA KC_NO // Present but not available for use.
#define U_NU KC_NO // Available but not used.

/** Convenience row shorthands. */
#define __________________RESET_L__________________ QK_BOOT,    U_NA,    U_NA,    U_NA,    U_NA
#define __________________RESET_R__________________    U_NA,    U_NA,    U_NA,    U_NA, QK_BOOT
#define ______________HOME_ROW_GASC_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,    U_NA
#define ______________HOME_ROW_GASC_R______________    U_NA, KC_RSFT, KC_LCTL, KC_LALT, KC_LGUI

/** Layers. */
// Navigation.
#define LAYOUT_LAYER_NAV                                                                      \
    KC_MPRV, KC_VOLD, KC_VOLU, KC_VOLD, KC_MNXT, USR_UND, USR_CUT, USR_CPY, USR_PST, USR_RDO, \
    KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_CAPS, ______________HOME_ROW_GASC_R______________, \
    KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_INS,  KC_MPRV, KC_VOLU, KC_VOLD, KC_VOLD, KC_MNXT, \
                U_NA,    U_NA,    U_NA,                 NO_EXLM, NO_QUES

// Mouse.
#define LAYOUT_LAYER_MOUSE                                                                    \
    QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, DPI_RMOD, S_D_MOD, DPI_MOD, XXXXXXX, EE_CLR,  QK_BOOT, \
    _______, DRGSCRL, KC_LCTL, KC_LSFT,     U_NA, ______________HOME_ROW_GASC_R______________, \
    _______, DRGSCRL, KC_LCTL, KC_LSFT,     U_NA, KC_BTN2,  KC_BTN1, KC_BTN2, DRGSCRL, _______, \
                        U_NA, KC_BTN1, KC_BTN2,       KC_ENT, KC_BSPC

// Symbols.
#define LAYOUT_LAYER_SYM                                                                      \
    NO_GRV, NO_AMPR,    CX_AT,   CX_AT, NO_HASH, __________________RESET_R__________________, \
    NO_AMPR, NO_LBRC, CX_LCBR, NO_LPRN, NO_PERC, ______________HOME_ROW_GASC_R______________, \
    CX_TILD, NO_RBRC, CX_RCBR, NO_RPRN,  CX_DLR,   KC_F5,  KC_F2, NO_RCBR, CX_ISMAC, CW_TOGG, \
                         U_NA, KC_MUTE, KC_MPLY,    U_NA, U_NA

// Numerals.
#define LAYOUT_LAYER_NUM                                                                      \
    CX_BSLS,    NO_7,    NO_8,    NO_9, NO_PLUS, CX_EURO,   CX_PND, CX_DLR, KC_SLEP, NO_ARNG, \
    CX_PIPE,    NO_4,    NO_5,    NO_6,  NO_EQL, ______________HOME_ROW_GASC_R______________, \
    NO_SLSH,    NO_1,    NO_2,    NO_3, NO_ASTR,  KC_F12,   NO_AE, NO_OSTR, NO_ARNG, NO_ARNG, \
                      U_NA,    NO_0, NO_RABK,    U_NA,    U_NA

// Function keys.
#define LAYOUT_LAYER_FUN                                                                      \
    __________________RESET_L__________________, KC_PSCR, KC_F7,   KC_F8,   KC_F9,   KC_F12, \
    ______________HOME_ROW_GASC_L______________, KC_SCRL, KC_F4,   KC_F5,   KC_F6,   KC_F11, \
    ______________HOME_ROW_GASC_L______________, KC_PAUS, KC_F1,   KC_F2,   KC_F3,   KC_F10, \
                         U_NA,    U_NA,    U_NA,  KC_SPC,  KC_APP

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
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10, LALT_T(L11), LCTL_T(L12), LSFT_T(L13),        L14,  \
             R15,  RSFT_T(R16), RCTL_T(R17), LALT_T(R18), RGUI_T(R19), \
     LGUI_T(L20),         L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,         R29,  \
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
            L20,        L21,        L22,        L23,        L24,  \
            R25,        R26,        R27,        R28, MOUSE(R29), \
      __VA_ARGS__
#define MOUSE_MOD(...) _MOUSE_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    MOUSE_MOD(HOME_ROW_MOD_GASC(LAYOUT_LAYER_BASE_BEPO))
  ),
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
    const uint16_t mod_shift = get_mods() & MOD_MASK_SHIFT; //track shift
    const uint16_t mod_ctrl = get_mods() & MOD_MASK_CTRL; //track ctrl
    const uint16_t mod_alt = get_mods() & MOD_MASK_ALT; //track alt
    const uint16_t mod_gui = get_mods() & MOD_MASK_GUI; //track gui
    is_apple = (os_type == OS_MACOS) || (os_type == OS_IOS);
    isMac = !is_apple;

    switch (keycode) {
        // ------HOME and END with Alt+Ctrl+Arrow------
        // case KC_LEFT:
        //     if (record->event.pressed) {
        //         if (mod_alt && mod_ctrl && !is_apple && !mod_gui) {
        //             unregister_mods(mod_alt);
        //             unregister_mods(mod_ctrl);
        //             tap_code16(KC_HOME);
        //             register_mods(mod_alt);
        //             register_mods(mod_ctrl);
        //         }
        //         else {
        //             tap_code16(KC_LEFT);
        //         }
        //     }
        //     return false;
        // break;
        // case KC_RIGHT:
        //     if (record->event.pressed) {
        //         if (mod_alt && mod_ctrl && !is_apple && !mod_gui) {
        //             unregister_mods(mod_alt);
        //             unregister_mods(mod_ctrl);
        //             tap_code16(KC_END);
        //             register_mods(mod_alt);
        //             register_mods(mod_ctrl);
        //         }
        //         else {
        //             tap_code16(KC_RIGHT);
        //         }
        //     }
        //     return false;
        // break;
        // case NO_LPRN:
        //     if(record->event.pressed && mod_alt && !is_apple) {
        //         tap_code16(NO_LCBR);
        //     } else {
        //         tap_code16(NO_LPRN);
        //     }
        //     return false;
        // break;
        // case NO_RPRN:
        //     if(record->event.pressed && mod_alt && !is_apple) {
        //         tap_code16(NO_RCBR);
        //     } else if (record->event.pressed && mod_gui && is_apple) {
        //         tap_code16(NO_RPRN);
        //     }
        //     return false;
        // break;

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
               if (mod_shift) {
                    tap_code16(KC_2); // (")
                }
                else if (mod_alt && !is_apple) {
                    unregister_mods(mod_alt);
                    tap_code16(NO_ACUT); // (´)
                    register_mods(mod_alt);
                }
                else if (mod_alt && is_apple) {
                    unregister_mods(mod_alt);
                    tap_code16(MAC_ACUT); // (´)
                    register_mods(mod_alt);
                }
                else if (mod_ctrl && !is_apple) {
                    unregister_mods(mod_ctrl);
                    tap_code16(NO_GRV); // (´)
                    register_mods(mod_ctrl);
                }
                else if (mod_gui && is_apple) {
                    unregister_mods(mod_gui);
                    tap_code16(NO_GRV); // (´)
                    register_mods(mod_gui);
                }
                else {
                    tap_code16((is_apple) ? MAC_QUOT : NO_QUOT);
                }
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
        case LALT_T(KC_R):
            return TAPPING_TERM + 35;
        case LCTL_T(KC_S):
            return TAPPING_TERM + 30;
        case RGUI_T(KC_O):
            return TAPPING_TERM + 40;
        case LALT_T(KC_I):
            return TAPPING_TERM + 35;
        case RCTL_T(KC_E):
            return TAPPING_TERM + 30;
        default:
            return TAPPING_TERM;
    }
}

const key_override_t delete_key_override = ko_make_basic(MOD_BIT(KC_LSFT), BAC_NUM, KC_DEL);
const key_override_t space_key_override = ko_make_basic(MOD_BIT(KC_LSFT), SPC_NAV, KC_ESC);
const key_override_t tab_key_override = ko_make_basic(MOD_BIT(KC_LSFT), TAB_FUN, NO_LABK);
const key_override_t ent_key_override = ko_make_basic(MOD_BIT(KC_RSFT), ENT_SYM, NO_RABK);
const key_override_t lprn_key_override = ko_make_basic(MOD_MASK_SHIFT, NO_LPRN, NO_LBRC);
const key_override_t rprn_key_override = ko_make_basic(MOD_MASK_SHIFT, NO_RPRN, NO_RBRC);
const key_override_t lprn2_key_override = ko_make_basic(MOD_MASK_GUI, NO_LPRN, NO_LABK);
const key_override_t rprn2_key_override = ko_make_basic(MOD_MASK_GUI, NO_RPRN, NO_RABK);
const key_override_t quest_key_override = ko_make_basic(MOD_MASK_SHIFT, NO_QUES, NO_EXLM);
const key_override_t lprn3_key_override = {.trigger_mods          = MOD_BIT(KC_LALT),
                                   .layers                 = ~(1 << 1),
                                   .suppressed_mods        = MOD_BIT(KC_LALT),
                                   .options                = ko_option_no_unregister_on_other_key_down,
                                   .negative_mod_mask      = (uint8_t) ~(MOD_BIT(KC_LALT)),
                                   .custom_action          = NULL,
                                   .context                = NULL,
                                   .trigger                = NO_LPRN,
                                   .replacement            = NO_LCBR,
                                    .enabled                = (bool *)&isMac};
const key_override_t rprn3_key_override = {.trigger_mods          = MOD_BIT(KC_LALT),
                                      .layers                 = ~(1 << 1),
                                      .suppressed_mods        = MOD_BIT(KC_LALT),
                                      .options                = ko_option_no_unregister_on_other_key_down,
                                      .negative_mod_mask      = (uint8_t) ~(MOD_BIT(KC_LALT)),
                                      .custom_action          = NULL,
                                      .context                = NULL,
                                      .trigger                = NO_RPRN,
                                      .replacement            = NO_RCBR,
                                        .enabled                = (bool *)&isMac};

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&delete_key_override,
    &space_key_override,
    &tab_key_override,
    &ent_key_override,
    &lprn_key_override,
    &rprn_key_override,
    &lprn2_key_override,
    &rprn2_key_override,
    &quest_key_override,
    &lprn3_key_override,
    &rprn3_key_override,
	NULL // Null terminate the array of overrides!
};
