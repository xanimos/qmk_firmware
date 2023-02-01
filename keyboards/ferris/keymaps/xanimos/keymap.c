#include QMK_KEYBOARD_H
#include "xanimos.h"
#include "tap_dance.h"

static const char * sendstring_commands[] = {
    "git init",
    "git clone ",
    "git add ",
    "git diff ",
    "git reset --soft ",
    "git branch --list",
    "git checkout ",
    "git checkout -b ",
    "git remote add upstream ",
    "git fetch ",
    "git pull",
    "git pull upstream ",
    "git push",
    "git push -u origin ",
    "git push --force-with-lease",
    "git commit ",
    "git commit -m \": [TFS-]\"",
    "git status",
    "git log",
    "git stash",
    "git stash list",
    "git stash pop ",
    "git stash show ",
    "git restore --staged "
};

enum macro_keycodes {
    // The start of this enum should always be equal to end of available keycodes + 1
    MOD_BOOT = SAFE_RANGE + 1,

    // Git Commands
    G_INIT,                 // git init
    G_CLONE,                // git clone
    G_ADD,                  // git add
    G_DIFF,                 // git diff
    G_RESET,                // git reset --soft
    G_BRANH,                // git branch list
    G_CHECK,                // git checkout
    G_CHECKB,               // git checkout -b
    G_REMTE,                // git remote add
    G_FETCH,                // git fetch
    G_PULL,                 // git pull
    G_PUPST,                // git pull upstream
    G_PUSH,                 // git push
    G_PSORG,                // git push -u origin
    G_PSFWL,                // git push --force-with-lease
    G_COMM,                 // git commit
    G_COMSG,                // git commit -m ": [TFS-]"
    G_STAT,                 // git status
    G_LOG,                  // git log
    G_STSH,                 // git stash
    G_STLS,                 // git stash list
    G_STSP,                 // git stash pop
    G_STSW,                 // git stash show
    G_RSTS                  // git restore --staged
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ALPHA] = LAYOUT( /* QWERTY */
    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,            KC_Y,      KC_U,       KC_I,       KC_O,       KC_P,
    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,            KC_H,      KC_J,       KC_K,       KC_L,       TD(COL_QU),
    SFT_T(KC_Z),KC_X,       KC_C,       KC_V,       KC_B,            KC_N,      KC_M,       KC_COMM,    KC_DOT, SFT_T(KC_SLSH),
                                   KC_SPC,  MO(_MODS),                  TO(_SYMBOLS), KC_BSPC
  ),

  [_SYMBOLS] = LAYOUT( /* [> Symbols <] */
    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,         KC_MINS,   KC_GRV,     KC_TILD,    KC_PIPE,    KC_BSLS,
    S(KC_6),    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,         KC_EQL,    KC_LT,      KC_GT,      KC_DQUO,    KC_QUOT,
    KC_UNDS,    KC_LBRC,    KC_RBRC,    KC_LCBR,    KC_RCBR,         KC_PLUS,   KC_COLN,    KC_COMM,    KC_DOT,     KC_QUES,
                                LT(_NUMBERS, KC_SPC), TD(AL_MOD),        TO(_FUNCTION), _______
  ),

  [_NUMBERS] = LAYOUT( /* [> Numbers <] */
    _______,    _______,    _______,    _______,    _______,         _______,   KC_7,       KC_8,       KC_9,       _______,
    _______,    _______,    _______,    _______,    _______,         _______,   KC_4,       KC_5,       KC_6,       _______,
    _______,    _______,    _______,    _______,    _______,         KC_0,      KC_1,       KC_2,       KC_3,       _______,
                                    _______, TD(AL_MOD),                _______, _______
  ),

  [_FUNCTION] = LAYOUT( /* [> Functions <] */
    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,           KC_F6,     KC_F7,      KC_F8,      KC_F9,      KC_F10,
    _______,    KC_LEFT,    KC_UP,      KC_RGHT,    _______,         KC_PSCR,   KC_INS,     KC_HOME,    KC_PGUP,    KC_F11,
    KC_CAPS,    _______,    KC_DOWN,    KC_NO,      KC_APP,         _______,    KC_DEL,     KC_END,     KC_PGDN,    KC_F12,
                                    _______, TD(AL_MOD),                 TO(_GIT), _______
  ),

  [_GIT] = LAYOUT( /* [> Git Commands <] */
    G_PUPST,    G_PULL,     G_PUSH,     G_PSORG,    G_PSFWL,         G_INIT,    G_CLONE,    G_REMTE,    G_RESET,    G_RSTS,
    G_ADD,      G_STAT,     G_DIFF,     G_FETCH,    G_LOG,           G_STLS,    G_STSH,     G_STSP,     G_STSW,     _______,
    G_CHECKB,   G_CHECK,    G_COMM,     G_COMSG,    G_BRANH,         _______,   _______,    _______,    _______,    _______,
                                    _______, TD(AL_MOD),               _______, _______
  ),

  [_MODS] = LAYOUT( /* [> Mods <] */
    C(KC_TAB),C(S(KC_ESC)), _______,    _______,    _______,         _______,    _______,    _______,    _______,    _______,
    KC_TAB,     KC_ESC,     _______,    LCA(KC_DEL),_______,         _______, TD(MH_CTL), TD(MH_ALT), TD(MH_SFT), TD(MH_GUI),
    A(KC_TAB),  C(KC_X),    C(KC_C),    C(KC_V),    _______,         MOD_BOOT,   _______,    _______,    _______,    _______,
                                     _______,     _______,              TO(_GAMING), KC_ENT
  ),

  [_GAMING] = LAYOUT( /* [> Mods <] */
    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,            KC_Y,      KC_U,       KC_I,       KC_O,       KC_P,
    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,            KC_H,      KC_J,       KC_K,       KC_L,       KC_SCLN,
    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,            KC_N,      KC_M,       KC_COMM,    KC_DOT,     KC_ESC,
                                     KC_SPC, KC_SLSH,                    TO(_ALPHA), KC_BSPC
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;
    uint8_t mod_state = get_mods();
    switch (keycode) {
        case MOD_BOOT:
        {
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        }
        case G_INIT ... G_RSTS:
        {
            if (record->event.pressed) {
                send_string_with_delay(sendstring_commands[keycode - G_INIT], 3);
            }
           return false;
        }
        case KC_BSPC:
        {
            static bool delkey_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    delkey_registered = true;
                    set_mods(mod_state);
                    return false;
                }
            } else {
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
            break;
        }
    }
    return true;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
