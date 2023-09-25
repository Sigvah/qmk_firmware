// Mac version of keycodes
#define MAC_AT     KC_BSLS      // @
#define MAC_DLR    LSFT(KC_4)   // $
#define MAC_BSLS   LSFT(LALT(KC_7))   // (backslash)
#define MAC_PIPE   LALT(KC_7)         // |
#define MAC_LCBR   LSFT(LALT(KC_8))   // {
#define MAC_RCBR   LSFT(LALT(KC_9))   // }
#define MAC_PND    LALT(KC_3)         // £
#define MAC_EURO   LALT(KC_4)         // €
#define MAC_TILD   LALT(KC_RBRC)      // ~
#define MAC_QUOT   KC_GRV             // '
#define MAC_ACUT   KC_PLUS            // ´

#define MAC_PRV_WRD LALT(KC_LEFT)
#define MAC_NXT_WRD LALT(KC_RIGHT)
#define MAC_UNDO    LCMD(KC_Z)
#define MAC_CUT     LCMD(KC_X)
#define MAC_COPY    LCMD(KC_C)
#define MAC_PSTE    LCMD(KC_Z)


// PC version of keycodes
#define PC_AT      ALGR(KC_2)         // @
#define PC_DLR     ALGR(KC_4)         // $
#define PC_BSLS    KC_EQL             // (backslash)
#define PC_PIPE    KC_GRV             // |
#define PC_LCBR    ALGR(KC_7)         // {
#define PC_RCBR    ALGR(KC_0)         // }
#define PC_PND     ALGR(KC_3)         // £
#define PC_EURO    ALGR(KC_5)         // €
#define PC_TILD    ALGR(KC_RBRC)      // ~
#define PC_QUOT     KC_NUHS            // '

#define PC_PRV_WRD LCTL(KC_LEFT)
#define PC_NXT_WRD LCTL(KC_RIGHT)
#define PC_UNDO    LCTL(KC_Z)
#define PC_CUT     LCTL(KC_X)
#define PC_COPY    LCTL(KC_C)
#define PC_PSTE    LCTL(KC_Z)
