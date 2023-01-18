#pragma once

// Tap Dance keycodes
enum td_keycodes {
    AL_MOD,
    COL_QU,
    MH_SFT,
    MH_CTL,
    MH_ALT,
    MH_GUI
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD
} td_state_t;

typedef struct {
    uint8_t mod;
} tap_dance_mod_hold_t;

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void guial_finished(qk_tap_dance_state_t *state, void *user_data);
void guial_reset(qk_tap_dance_state_t *state, void *user_data);

void tap_dance_mod_hold_finished(qk_tap_dance_state_t *state, void *user_data);
void tap_dance_mod_hold_reset(qk_tap_dance_state_t *state, void *user_data);
