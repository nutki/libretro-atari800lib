#include "core.h"
#include "libatari800/libatari800.h"
#include "libretro.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifndef AKEY_0

#define AKEY_0 0x32
#define AKEY_1 0x1f
#define AKEY_2 0x1e
#define AKEY_3 0x1a
#define AKEY_4 0x18
#define AKEY_5 0x1d
#define AKEY_6 0x1b
#define AKEY_7 0x33
#define AKEY_8 0x35
#define AKEY_9 0x30

#define AKEY_a 0x3f
#define AKEY_b 0x15
#define AKEY_c 0x12
#define AKEY_d 0x3a
#define AKEY_e 0x2a
#define AKEY_f 0x38
#define AKEY_g 0x3d
#define AKEY_h 0x39
#define AKEY_i 0x0d
#define AKEY_j 0x01
#define AKEY_k 0x05
#define AKEY_l 0x00
#define AKEY_m 0x25
#define AKEY_n 0x23
#define AKEY_o 0x08
#define AKEY_p 0x0a
#define AKEY_q 0x2f
#define AKEY_r 0x28
#define AKEY_s 0x3e
#define AKEY_t 0x2d
#define AKEY_u 0x0b
#define AKEY_v 0x10
#define AKEY_w 0x2e
#define AKEY_x 0x16
#define AKEY_y 0x2b
#define AKEY_z 0x17

#define AKEY_WARMSTART -2
#define AKEY_COLDSTART -3
#define AKEY_EXIT -4
#define AKEY_BREAK -5

#endif

struct keymap keymap[] = {
    {RETROK_0, AKEY_0},
    {RETROK_1, AKEY_1},
    {RETROK_2, AKEY_2},
    {RETROK_3, AKEY_3},
    {RETROK_4, AKEY_4},
    {RETROK_5, AKEY_5},
    {RETROK_6, AKEY_6},
    {RETROK_7, AKEY_7},
    {RETROK_8, AKEY_8},
    {RETROK_9, AKEY_9},
    {RETROK_SPACE, AKEY_SPACE},
    {RETROK_a, AKEY_a},
    {RETROK_b, AKEY_b},
    {RETROK_c, AKEY_c},
    {RETROK_d, AKEY_d},
    {RETROK_e, AKEY_e},
    {RETROK_f, AKEY_f},
    {RETROK_g, AKEY_g},
    {RETROK_h, AKEY_h},
    {RETROK_i, AKEY_i},
    {RETROK_j, AKEY_j},
    {RETROK_k, AKEY_k},
    {RETROK_l, AKEY_l},
    {RETROK_m, AKEY_m},
    {RETROK_n, AKEY_n},
    {RETROK_o, AKEY_o},
    {RETROK_p, AKEY_p},
    {RETROK_q, AKEY_q},
    {RETROK_r, AKEY_r},
    {RETROK_s, AKEY_s},
    {RETROK_t, AKEY_t},
    {RETROK_u, AKEY_u},
    {RETROK_v, AKEY_v},
    {RETROK_w, AKEY_w},
    {RETROK_x, AKEY_x},
    {RETROK_y, AKEY_y},
    {RETROK_z, AKEY_z},
    {RETROK_RETURN, AKEY_RETURN},
    {RETROK_ESCAPE, AKEY_ESCAPE},
    {RETROK_TAB, AKEY_TAB},
    {RETROK_BACKSPACE, AKEY_BACKSPACE},
    {RETROK_COMMA, AKEY_COMMA},
    {RETROK_PERIOD, AKEY_FULLSTOP},
    {RETROK_SLASH, AKEY_SLASH},
    {RETROK_SEMICOLON, AKEY_SEMICOLON},
    {RETROK_RALT, AKEY_ATARI},
    {RETROK_MINUS, AKEY_MINUS},
    {RETROK_EQUALS, AKEY_EQUAL},
    {RETROK_LEFTBRACE, AKEY_LESS},
    {RETROK_RIGHTBRACE, AKEY_GREATER},
    {RETROK_QUOTE, AKEY_PLUS},
    {RETROK_BACKSLASH, AKEY_ASTERISK},
    {RETROK_CAPSLOCK, AKEY_CAPSTOGGLE},

    // 1200XE
    {RETROK_HELP, AKEY_HELP},
    {RETROK_F1, AKEY_F1},
    {RETROK_F2, AKEY_F2},
    {RETROK_F3, AKEY_F3},
    {RETROK_F4, AKEY_F4},

    // macros
    {RETROK_UP, AKEY_UP},
    {RETROK_DOWN, AKEY_DOWN},
    {RETROK_LEFT, AKEY_LEFT},
    {RETROK_RIGHT, AKEY_RIGHT},
    {0},
};

struct retro_input_descriptor retro_input_desc_joystick[] = {
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Trigger"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "Space"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Option"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Return"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Down"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Up"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Left"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Rigt"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select"},
    {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Analog X"},
    {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y, "Analog Y"},
    {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X, "Paddle B"},
    {0}};
struct retro_input_descriptor retro_input_desc_paddles[] = {
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Trigger A"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Trigger B"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "Space"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Option"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Return"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select"},
    {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Paddle A"},
    {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X, "Paddle B"},
    {0}};

struct retro_input_descriptor retro_input_desc[64], retro_input_desc_empty;

#define RETRO_DEVICE_ATARI_PADDLES RETRO_DEVICE_SUBCLASS(RETRO_DEVICE_ANALOG, 0)
struct retro_controller_description retro_controller_description[] = {
    {"Atari Joystick", RETRO_DEVICE_JOYPAD},
    {"Atari Paddles", RETRO_DEVICE_ATARI_PADDLES},
};
struct retro_controller_info retro_controller_info[] = {{retro_controller_description, 2},
                                                        {retro_controller_description, 1},
                                                        {retro_controller_description, 1},
                                                        {retro_controller_description, 1},
                                                        {0}};

struct retro_input_descriptor *core_get_retro_input_descriptors() {
  struct retro_input_descriptor *dst = retro_input_desc;
  for (int i = 0; i < NUM_PORTS; i++) {
    struct retro_input_descriptor *base =
        port_device[0] == RETRO_DEVICE_ATARI_PADDLES ? retro_input_desc_paddles : retro_input_desc_joystick;
    for (; base->description; base++) {
      *dst = *base;
      dst->port = i;
      dst++;
    }
  }
  *dst++ = retro_input_desc_empty;
  return retro_input_desc;
}

struct retro_core_option_definition retro_options[] = {
    {"atari800lib_system",
     "Atari System",
     "Atari system to emulate.",
     {{"800", 0}, {"800XL", 0}, {"1200XL", 0}, {"130XE", 0}, {"XE 320K", 0}, {"XE 1088K", 0}},
     "800XL"},
    {
        "atari800lib_tvmode",
        "Video Standard",
        "Video Standard to use. Auto looks for 'PAL' in the file name.",
        {{"Auto", 0}, {"NTSC", 0}, {"PAL", 0}},
        "Auto",
    },
    {
        "atari800lib_internalbasic",
        "Internal BASIC",
        "Boot with Basic rom. Auto looks for 'BASIC' in the file name.",
        {{"Auto", 0}, {"Off", 0}, {"On", 0}},
        "Auto",
    },
    {"atari800lib_artifacting",
     "NTSC Artifacting Emulation",
     "Alters display colors for games relying on the composite NTSC signal artifacts. Game reload required.",
     {
         {"None", 0},
         {"Blue/Brown 1", 0},
         {"Blue/Brown 2", 0},
         {"GTIA", 0},
         {"CTIA", 0},
         {"New Blue/Brown 1", 0},
         {"New Blue/Brown 2", 0},
         {"New GTIA", 0},
         {"New CTIA", 0},
     },
     "None"},
    {
        "atari800lib_sioaccel",
        "SIO Acceleration",
        "When disabled emulates actual IO wait time.",
        {{"disabled", 0}, {"enabled", 0}},
        "enabled",
    },

    {0},
};

bool supports_no_game = false;

char *config_file_name = ".atari800lib.cfg";

void core_get_system_info(struct retro_system_info *info) {
  info->library_name = "Atari 800 (libatari800)";
  info->valid_extensions = "xfd|atr|cdm|cas|bin|atx|car|com|xex";
}

static int handle_joystick(int player, uint8_t *joy, uint8_t *trig) {
  if (port_device[player] != RETRO_DEVICE_JOYPAD)
    return 0;
  int left_x = input_state_cb(player, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X);
  int left_y = input_state_cb(player, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y);
  int val = input_state_cb(player, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_MASK);
  int dir = 0;
  if (val & (1 << RETRO_DEVICE_ID_JOYPAD_UP) || left_y < -ANALOG_MIN)
    dir |= 1;
  if (val & (1 << RETRO_DEVICE_ID_JOYPAD_DOWN) || left_y > ANALOG_MIN)
    dir |= 2;
  if (val & (1 << RETRO_DEVICE_ID_JOYPAD_LEFT) || left_x < -ANALOG_MIN)
    dir |= 4;
  if (val & (1 << RETRO_DEVICE_ID_JOYPAD_RIGHT) || left_x > ANALOG_MIN)
    dir |= 8;
  *trig = val & (1 << RETRO_DEVICE_ID_JOYPAD_A) ? 1 : 0;
  *joy = dir;
  return val;
}

#define MOUSE_PORT 0
#define POT_MIN 0
#define POT_MAX 228
static int handle_paddles(void) {
  input.mouse_mode = 1;
  if (port_device[MOUSE_PORT] == RETRO_DEVICE_ATARI_PADDLES) {
    int val = input_state_cb(MOUSE_PORT, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_MASK);
    int pot_a =
        input_state_cb(MOUSE_PORT, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X);
    int pot_b =
        input_state_cb(MOUSE_PORT, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X);
    input.mouse_buttons =
        ((val & (1 << RETRO_DEVICE_ID_JOYPAD_A)) ? 1 : 0) | ((val & (1 << RETRO_DEVICE_ID_JOYPAD_B)) ? 1 : 0);
    input.mousex = (pot_a + 32 * 1024) * POT_MAX / (64 * 1024);
    input.mousey = (pot_b + 32 * 1024) * POT_MAX / (64 * 1024);
    return val;
  }
  return 0;
}

void core_handle_input(void) {
  input.mouse_mode = 0;
  int val = handle_joystick(0, &input.joy0, &input.trig0) | handle_joystick(1, &input.joy1, &input.trig1) |
            handle_joystick(2, &input.joy2, &input.trig2) | handle_joystick(3, &input.joy3, &input.trig3) |
            handle_paddles();
  input.start = (val & (1 << RETRO_DEVICE_ID_JOYPAD_START)) || keyboard_state[RETROK_F5] ? 1 : 0;
  input.select = (val & (1 << RETRO_DEVICE_ID_JOYPAD_SELECT)) || keyboard_state[RETROK_F6] ? 1 : 0;
  input.option = (val & (1 << RETRO_DEVICE_ID_JOYPAD_Y)) || keyboard_state[RETROK_F7] ? 1 : 0;
  if (val & (1 << RETRO_DEVICE_ID_JOYPAD_X))
    input.keycode = AKEY_SPACE;
  if (val & (1 << RETRO_DEVICE_ID_JOYPAD_R))
    input.keycode = AKEY_RETURN;
  input.shift = keyboard_state[RETROK_LSHIFT] || keyboard_state[RETROK_RSHIFT] ? 1 : 0;
  input.control = keyboard_state[RETROK_LCTRL] || keyboard_state[RETROK_RCTRL] ? 1 : 0;
  input.special = keyboard_state[RETROK_F10] ? -AKEY_BREAK : 0;
  input.special = keyboard_state[RETROK_F9] ? -AKEY_WARMSTART : 0;
}

static int includes_word(const char *s, const char *word) {
  while (*s) {
    /* find start of a word */
    while (*s && !isalpha(*s))
      s++;
    if (!*s) { // Not found
      return 0;
    }
    const char *w = word;
    for (; *w && isalpha(*s); w++, s++) {
      if (tolower(*w) != tolower(*s))
        break;
    }
    if (!*w)
      return 1; // found complete key word
    /* find end of a word */
    while (isalpha(*s))
      s++;
  }
  return 0;
}
static const char *get_system_model(void) {
  const char *v = get_variable("atari800lib_system");
  if (!strcmp(v, "800"))
    return "-atari";
  if (!strcmp(v, "800XL"))
    return "-xl";
  if (!strcmp(v, "1200XL"))
    return "-1200";
  if (!strcmp(v, "130XE"))
    return "-xe";
  if (!strcmp(v, "XE 320K"))
    return "-320xe";
  if (!strcmp(v, "XE 1088K"))
    return "-1088xe";
  return "-error";
}
static const char *get_tv_mode(const char *filename) {
  const char *v = get_variable("atari800lib_tvmode");
  if (!strcmp(v, "NTSC"))
    return "-ntsc";
  if (!strcmp(v, "PAL"))
    return "-pal";
  int has_pal = filename && includes_word(filename, "pal");
  if (has_pal)
    l.log(RETRO_LOG_INFO, "Detected PAL content");
  return has_pal ? "-pal" : "-ntsc";
}
static int get_basic(const char *filename) {
  const char *v = get_variable("atari800lib_internalbasic");
  if (!strcmp(v, "Off"))
    return 0;
  if (!strcmp(v, "On"))
    return 1;
  // No content run, assume BASIC
  if (!filename)
    return 1;
  int has_basic = includes_word(filename, "basic");
  if (has_basic)
    l.log(RETRO_LOG_INFO, "Detected content requiring BASIC ROM");
  return has_basic;
}
static int get_sio_accel(void) {
  const char *v = get_variable("atari800lib_sioaccel");
  return strcmp(v, "enabled") == 0 ? 1 : 0;
}
const char *get_artifacting_mode(void) {
  const char *mode_str = get_variable("atari800lib_artifacting");
  if (!strncmp(mode_str, "New ", 4))
    mode_str += 4;
  if (!strcmp(mode_str, "None"))
    return "0";
  if (!strcmp(mode_str, "Blue/Brown 1"))
    return "1";
  if (!strcmp(mode_str, "Blue/Brown 2"))
    return "2";
  if (!strcmp(mode_str, "GTIA"))
    return "3";
  if (!strcmp(mode_str, "CTIA"))
    return "4";
  return "0";
}

void core_load_game(const char *filename) {
  const char *args[] = {fake_exe_file_path,
                        get_system_model(),
                        get_tv_mode(filename),
                        get_basic(filename) ? "-basic" : "-nobasic",
                        "-ntsc-artif",
                        get_artifacting_mode_is_new() ? "ntsc-new" : "ntsc-old",
                        "-artif",
                        get_artifacting_mode(),
                        "-config",
                        config_file_path,
                        get_sio_accel() ? "-sound" : "-nopatch",
                        "-directmouse",
                        "-mouse",
                        "pad",
                        "-nostereo",
                        "-audio16",
                        "-sound",
                        "-no-autosave-config",
                        filename,
                        NULL};
  libatari800_init(-1, (char **)args);
}

int core_get_main_memory_size() { return (strcmp(get_variable("atari800lib_system"), "800") == 0 ? 48 : 64) * 1024; }
