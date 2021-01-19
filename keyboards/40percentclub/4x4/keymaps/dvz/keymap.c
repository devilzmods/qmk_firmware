#include QMK_KEYBOARD_H
#include "keymap_german.h"

enum combos {
  UML_AE,
  UML_OE,
  UML_UE,
  UML_SZ
};

const uint16_t PROGMEM ae_combo[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_O, KC_E, COMBO_END};
const uint16_t PROGMEM ue_combo[] = {KC_U, KC_E, COMBO_END};
const uint16_t PROGMEM sz_combo[] = {KC_S, DE_Z, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [UML_AE] = COMBO(ae_combo, DE_ADIA),
  [UML_OE] = COMBO(oe_combo, DE_ODIA),
  [UML_UE] = COMBO(ue_combo, DE_UDIA),
  [UML_SZ] = COMBO(sz_combo, DE_SS)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_4x16(KC_7, KC_8, KC_9, KC_PMNS, KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, DE_Z, KC_U, KC_I, KC_O, KC_P, KC_BSPC, \
                          KC_4, KC_5, KC_6, DE_PLUS, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SLSH, KC_NO, \
                          KC_1, KC_2, KC_3, KC_PENT, KC_LSFT, DE_Y, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_SFTENT, \
                          KC_NO, KC_0, KC_DOT, KC_NO, KC_LCTL, KC_LGUI, KC_LALT, MO(2), KC_SPC, KC_NO, LT(1, KC_SPC), KC_NO, KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT),
  [1] = LAYOUT_ortho_4x16(KC_TRNS, KC_TRNS, KC_TRNS, KC_PSLS, KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, DE_LPRN, DE_RPRN, KC_RPRN, KC_TRNS, \
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_PAST, KC_GRV, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DE_BSLS, DE_QUES, DE_LBRC, DE_RBRC,  LSFT(DE_HASH), KC_TRNS, \
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DE_BSLS, DE_LABK, DE_RABK, DE_LCBR, DE_RCBR, KC_PGUP, KC_TRNS, \
                          KC_TRNS, KC_TRNS, KC_COMM, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END),
  [2] = LAYOUT_ortho_4x16(KC_F7, KC_F8, KC_F9, KC_VOLD, DE_CIRC, KC_TRNS, KC_TRNS, KC_TRNS, RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
                          KC_F4, KC_F5, KC_F6, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DE_HASH, KC_TRNS, \
                          KC_F1, KC_F2, KC_F3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BRIU, KC_TRNS, \
                          KC_TRNS, KC_F10, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_BRID, KC_MNXT)
};
