#include "quantum.h"
#include "tap_dance.h"
#include "xanimos.h"

// Create a global instance of the tapdance state type
static td_state_t td_state;

void tap_dance_mod_hold_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_mod_hold_t *mod_hold = (tap_dance_mod_hold_t *)user_data;
    switch(cur_dance(state)) {
        case TD_SINGLE_TAP:
        {
            if ((get_oneshot_mods() & mod_hold->mod) != mod_hold->mod) {
                add_oneshot_mods(mod_hold->mod);
            } else {
                del_oneshot_mods(mod_hold->mod);
            }
            break;
        }
        case TD_SINGLE_HOLD:
        {
            if ((get_mods() & mod_hold->mod) != mod_hold->mod) {
                add_mods(mod_hold->mod);
            } else {
                del_mods(mod_hold->mod);
            }
            break;
        }
        default:
        {
            // clear both mods
            del_oneshot_mods(mod_hold->mod);
            del_mods(mod_hold->mod);
            break;
        };
    }
}

void tap_dance_mod_hold_reset(qk_tap_dance_state_t *state, void *user_data) { }

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            return TD_SINGLE_TAP;
        return TD_SINGLE_HOLD;
    }
    return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

void alphamod_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: layer_move(_ALPHA); break;
        case TD_SINGLE_HOLD: layer_on(_MODS); break;
        default: break;
    }
}

void alphamod_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_HOLD: layer_off(_MODS); break;
        default: break;
    }
}

#define ACTION_TAP_DANCE_MOD_HOLD(mod) \
    { .fn = {NULL, tap_dance_mod_hold_finished, tap_dance_mod_hold_reset}, .user_data = (void *)&((tap_dance_mod_hold_t){mod}), }

qk_tap_dance_action_t tap_dance_actions[] = {
    [AL_MOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alphamod_finished, alphamod_reset),
    [COL_QU] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
    [MH_SFT] = ACTION_TAP_DANCE_MOD_HOLD(MOD_LSFT),
    [MH_CTL] = ACTION_TAP_DANCE_MOD_HOLD(MOD_LCTL),
    [MH_ALT] = ACTION_TAP_DANCE_MOD_HOLD(MOD_LALT),
    [MH_GUI] = ACTION_TAP_DANCE_MOD_HOLD(MOD_LGUI)
};
