#include QMK_KEYBOARD_H


enum layers {
    _DEFAULT = 0,
    _LOWER = 1,
	_RAISE = 2,
	_ADJUST = 3,
    _MOUSE = 4, // 1 on sweep
    _NAVIGATION = 5,
    _SYMBOL_1 = 6,
    _SYMBOL_2 = 7,
    _FUNCTIONS = 8,
    _NUMBERS = 9,
    _QWERTY = 10,
    _EXTRAS = 11, // 7 on swee
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DEFAULT] = LAYOUT_split_3x6_3(
		KC_TAB , KC_A        , KC_Z                , KC_E           , KC_R              , KC_T        ,               KC_Y , KC_U              , KC_I                , KC_O             , KC_P        , KC_BSPC,
		KC_LCTL, LSFT_T(KC_Q), LT(_FUNCTIONS, KC_S), LT(_MOUSE,KC_D), LT(_SYMBOL_1,KC_F), KC_G        ,               KC_H , LT(_SYMBOL_2,KC_J), LT(_NAVIGATION,KC_K), LT(_NUMBERS,KC_L), RSFT_T(KC_M), KC_QUOT,
		KC_LSFT, KC_W        , LCTL_T(KC_X)        , RALT_T(KC_C)   , LGUI_T(KC_V)      , KC_B        ,               KC_N , RGUI_T(KC_SCLN)   , RALT_T(KC_COMM)     , RCTL_T(KC_DOT)   , KC_SLSH     , RSFT_T(KC_ESC),
				                                     KC_LGUI        , LT(_LOWER,KC_TAB) , KC_SPC      , LT(_EXTRAS,KC_ENT) , LT(_RAISE,KC_BSPC) , KC_RALT
	),
	[_LOWER] = LAYOUT_split_3x6_3(
		KC_TAB , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , 			KC_6   , KC_7       , KC_8   , KC_9    , KC_0   , KC_BSPC,
		KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,			KC_LEFT, KC_DOWN    , KC_UP  , KC_RIGHT, XXXXXXX, XXXXXXX,
		KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,			XXXXXXX, XXXXXXX    , XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX,
					               KC_LGUI, _______,  KC_SPC,           KC_ENT , MO(_ADJUST), KC_RALT
	),
	[_RAISE] = LAYOUT_split_3x6_3(
		KC_TAB , KC_EXLM, KC_AT  , KC_HASH, KC_DLR     , KC_PERC, 			KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
		KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, KC_LT      , KC_GT  ,			KC_MINS, KC_EQL , KC_BSLS, KC_LBRC, KC_RBRC,  KC_GRV,
		KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX    , XXXXXXX,			KC_UNDS, KC_PLUS, KC_PIPE, KC_LCBR, KC_RCBR,  KC_TILD,
					               KC_LGUI, MO(_ADJUST),  KC_SPC,           KC_ENT , _______, KC_RALT
	),
	[_ADJUST] = LAYOUT_split_3x6_3(
		QK_BOOT, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,           KC_F6  , KC_F7,   KC_F8  , KC_F9  , KC_F10 , KC_F11,
		RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,			KC_HOME, KC_PGDN, KC_PGUP, KC_END, XXXXXXX, KC_F12,
		RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,			XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
					                KC_LGUI, _______, KC_SPC,           KC_ENT, _______, KC_RALT
	),
    [_MOUSE] = LAYOUT_split_3x6_3(
        KC_TRNS, RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI,    RGB_SPI, KC_BTN1, KC_WH_U, KC_BTN2, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_BTN2,  KC_NO,   KC_BTN1, KC_TRNS,    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,    RGB_SPD, KC_WH_L, KC_WH_D, KC_WH_R, KC_TRNS, KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_NAVIGATION] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,      KC_TRNS,
        KC_TRNS, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_TRNS,     KC_TRNS, KC_LGUI, KC_NO,   LCTL(KC_LALT), LCA(KC_LSFT), KC_TRNS,
        KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END,  KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,      KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_SYMBOL_1] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS, KC_UNDS, KC_PIPE, KC_QUOT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_CIRC, KC_ASTR, KC_AMPR, KC_NO,    KC_TRNS,     KC_HASH, KC_TILD, KC_SLSH, KC_DQUO, KC_DLR,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS, KC_MINS, KC_BSLS, KC_GRV,  KC_TRNS, KC_TRNS,
                                   KC_TRNS, RGB_RMOD, KC_TRNS,     KC_TRNS, RGB_MOD, KC_TRNS
    ),
    [_SYMBOL_2] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_COLN, KC_LT,   KC_GT,   KC_SCLN,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_AT,        KC_TRNS, KC_NO,   KC_EQL,  KC_PLUS, KC_PERC, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_EXLM, KC_LBRC, KC_RBRC, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                   KC_TRNS, KC_VOLD, KC_TRNS,      KC_TRNS, KC_VOLU, KC_TRNS
    ),
    [_FUNCTIONS] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS,      KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10,KC_TRNS,
        KC_TRNS, KC_TRNS, KC_NO,   LCTL(KC_LALT), KC_LALT, KC_TRNS,      KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11,KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS,      KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F12,KC_TRNS,
                                   KC_TRNS,       KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_NUMBERS] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_PSLS, KC_7, KC_8,    KC_9,    KC_PPLS,      KC_TRNS, KC_TRNS, KC_TRNS      , KC_TRNS, KC_TRNS,KC_TRNS,
        KC_TRNS, KC_0,    KC_1, KC_2,    KC_3,    KC_PMNS,      KC_TRNS, KC_TRNS, LCTL(KC_LSFT), KC_NO,   KC_TRNS,KC_TRNS,
        KC_TRNS, KC_PAST, KC_4, KC_5,    KC_6,    KC_PEQL,      KC_TRNS, KC_TRNS, KC_TRNS      , KC_TRNS, KC_TRNS,KC_TRNS,
                                KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),
	[_QWERTY] = LAYOUT_split_3x6_3(
		KC_TAB , KC_Q, KC_W, KC_E   , KC_R   , KC_T,         KC_Y   , KC_U   , KC_I   , KC_O  , KC_P   , KC_BSPC,
		KC_LCTL, KC_A, KC_S, KC_D   , KC_F   , KC_G,         KC_H   , KC_J   , KC_K   , KC_L  , KC_M   , KC_QUOT,
		KC_LSFT, KC_Z, KC_X, KC_C   , KC_V   , KC_B,         KC_N   , KC_SCLN, KC_COMM, KC_DOT, KC_SLSH, KC_ESC,
                             KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
	),
    [_EXTRAS] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_COLN, KC_ESC,  KC_TRNS,      KC_TRNS     , KC_TRNS    , KC_TRNS    , KC_TRNS       , KC_TRNS , KC_BSPC,
        KC_TRNS, KC_GRV,  KC_PERC, KC_SLSH, KC_ENT,  KC_TRNS,      KC_LEFT     , KC_DOWN    , KC_UP      , KC_RGHT       , KC_TRNS , KC_QUOT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_EXLM, KC_TRNS,      DF(_DEFAULT), DF(_MOUSE) , DF(_QWERTY), RCTL_T(KC_DOT), KC_TRNS , KC_DEL,
                                   KC_TRNS, KC_TRNS, KC_TAB,       KC_NO       , KC_TRNS    , KC_TRNS
    ),
};

/* turn the power led OFF */
void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}

