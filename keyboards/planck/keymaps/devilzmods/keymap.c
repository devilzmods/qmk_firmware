#include QMK_KEYBOARD_H
#include "keymap_german.h"
//#include "drivers\chibios\spi_master.h" //only for testing purposes
#ifdef KeymapBT
    #include "Adafruit_BLE.h"
    #include "report.h"
#endif


float rgb_tog_song[][2] = SONG(COIN_SOUND);

enum combos {
  UML_AE,
  UML_OE,
  UML_UE,
  UML_SZ
};

bool bluetooth_available = false;


// Light LED 2 in cyan when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 1, HSV_GREEN}
);
// Light LED 9 in purple when keyboard layer 4 is active
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_PURPLE}
);
// Light LED 2 and 9 in orange when keyboard layer 6 is active
const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_ORANGE},
    {8, 1, HSV_ORANGE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer3_layer,
    my_layer4_layer,    // Overrides caps lock layer
    my_layer6_layer     // Overrides other layers
);

//Initialization
void keyboard_post_init_user() {
    #ifdef KeymapBT
        // Is a bluefruit connected
        bluetooth_available = adafruit_ble_enable_keyboard();
        wait_ms(1100);

        if (bluetooth_available) {
            PLAY_SONG(rgb_tog_song);
        }
    #endif
        // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

//Rotary encoder keycodes
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    }
}

const uint16_t PROGMEM ae_combo[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_O, KC_E, COMBO_END};
const uint16_t PROGMEM ue_combo[] = {KC_U, KC_E, COMBO_END};
const uint16_t PROGMEM sz_combo[] = {KC_S, KC_Y, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [UML_AE] = COMBO(ae_combo, DE_ADIA),
  [UML_OE] = COMBO(oe_combo, DE_ODIA),
  [UML_UE] = COMBO(ue_combo, DE_UDIA),
  [UML_SZ] = COMBO(sz_combo, DE_SS)
};

//Audio cues
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
                PLAY_SONG(rgb_tog_song);
            } else {
                // Do something else when release
            }
            return true; // Skip all further processing of this key
        default:
            #ifdef KeymapBT
                if (adafruit_ble_is_connected()) {

                    adafruit_ble_send_keys(report->mods, report->keys, sizeof(report->keys));
                    return false;
                }
            #endif

            return true; // Process all other keycodes normally
    }
};

//int matrix_counter = 0;
//int matrix_divisor = 100; //set higher to reduce frequency of events called every Nth matrix scan

void matrix_scan_user() {
    /*if (bluetooth_available)
    {
        if (matrix_counter >= matrix_divisor) {
            matrix_counter = 0;
            //insert functions to be called every Nth scan
            adafruit_ble_task();
        } else {
            matrix_counter++;
        }
    }*/
    #ifdef KeymapBT
        adafruit_ble_task();
    #endif
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_4x12(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, \
                            KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, DE_PLUS, DE_MINS, \
                            LSFT_T(KC_TAB), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_SFTENT, \
                            KC_LCTL, KC_RALT, KC_LGUI, KC_LALT, MO(3), KC_NO, KC_SPC, MO(4), KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT),
	[1] = LAYOUT_ortho_4x12(KC_TRNS, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_TRNS, \
                            KC_TRNS, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_TRNS, \
                            KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
                            DF(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT_ortho_4x12(KC_TRNS, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_TRNS, \
                            KC_TRNS, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_SLSH, \
                            KC_TRNS, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_TRNS, \
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[3] = LAYOUT_ortho_4x12(KC_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
                            KC_TILD, KC_UNDS, KC_NO, KC_NO, KC_NO, KC_NO, LCA(KC_NUBS), KC_UNDS, LCA(KC_8), LCA(KC_9), LSFT(DE_HASH), LCA(DE_LABK), \
                            KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NUBS, LSFT(KC_NUBS), LCA(KC_7), LCA(KC_0), KC_VOLU, KC_TRNS, \
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(6), KC_TRNS, KC_BRID, KC_VOLD, KC_BRIU),
	[4] = LAYOUT_ortho_4x12(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, \
                            KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, DE_HASH, LCA(DE_SS), \
                            KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_COMM, KC_DOT, KC_PGUP, KC_TRNS, \
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(6), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END),
	[5] = LAYOUT_ortho_4x12(KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, \
                            KC_NO, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, \
                            KC_NO, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, \
                            KC_TRNS, KC_NO, KC_NO, KC_C, KC_V, KC_NO, KC_NO, KC_TRNS, KC_M, KC_NO, KC_NO, KC_NO),
	[6] = LAYOUT_ortho_4x12(KC_TRNS, RESET, DEBUG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_M_P, RGB_M_B, RGB_M_SW, KC_DEL, \
                            KC_TRNS, KC_TRNS, MU_MOD, AU_ON, AU_OFF, AG_NORM, AG_SWAP, DF(0), DF(1), DF(2), TO(5), KC_TRNS, \
                            KC_TRNS, MUV_DE, MUV_IN, MU_ON, MU_OFF, MI_ON, MI_OFF, TERM_ON, TERM_OFF, KC_TRNS, KC_TRNS, KC_TRNS, \
                            KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, 3));
    rgblight_set_layer_state(1, layer_state_cmp(state, 4));
    rgblight_set_layer_state(2, layer_state_cmp(state, 6));
    return state;
}
