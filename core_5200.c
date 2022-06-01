#include "core.h"
#include "libatari800.h"
#include "libretro.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct keymap keymap[] = {
    // Basic mapping
    {RETROK_0, AKEY_5200_0},
    {RETROK_1, AKEY_5200_1},
    {RETROK_2, AKEY_5200_2},
    {RETROK_3, AKEY_5200_3},
    {RETROK_4, AKEY_5200_4},
    {RETROK_5, AKEY_5200_5},
    {RETROK_6, AKEY_5200_6},
    {RETROK_7, AKEY_5200_7},
    {RETROK_8, AKEY_5200_8},
    {RETROK_9, AKEY_5200_9},
    {RETROK_MINUS, AKEY_5200_ASTERISK},
    {RETROK_EQUALS, AKEY_5200_HASH},
    {RETROK_RETURN, AKEY_5200_START},
    {RETROK_p, AKEY_5200_PAUSE},
    {RETROK_r, AKEY_5200_RESET},
    // Keypad mapping
    {RETROK_KP0, AKEY_5200_0},
    {RETROK_KP1, AKEY_5200_1},
    {RETROK_KP2, AKEY_5200_2},
    {RETROK_KP3, AKEY_5200_3},
    {RETROK_KP4, AKEY_5200_4},
    {RETROK_KP5, AKEY_5200_5},
    {RETROK_KP6, AKEY_5200_6},
    {RETROK_KP7, AKEY_5200_7},
    {RETROK_KP8, AKEY_5200_8},
    {RETROK_KP9, AKEY_5200_9},
    {RETROK_KP_MULTIPLY, AKEY_5200_ASTERISK},
    {RETROK_KP_DIVIDE, AKEY_5200_HASH},
    {RETROK_KP_ENTER, AKEY_5200_START},
    {RETROK_KP_PLUS, AKEY_5200_PAUSE},
    {RETROK_KP_MINUS, AKEY_5200_RESET},
    {0},
};

struct retro_input_descriptor retro_input_desc[] = {
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Trigger 1"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Trigger 2"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "# (Hash)"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "* (Asterisk)"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Down"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Up"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Left"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Rigt"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Pause"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Next digit"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Prev digit"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R2, "Digit 9"},
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "Digit 0"},
    {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Analog X"},
    {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y, "Analog Y"},
    {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X, "2P Analog X"},
    {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y, "2P Analog Y"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Trigger 1"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Trigger 2"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "# (Hash)"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "* (Asterisk)"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Down"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Up"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Left"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Rigt"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Pause"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Next digit"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Prev digit"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R2, "Digit 9"},
    {1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "Digit 0"},
    {1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Analog X"},
    {1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y, "Analog Y"},
    {1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X, "1P Analog X"},
    {1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y, "1P Analog Y"},
    {0}};

struct retro_controller_description retro_controller_description[] = {
    {"5200 Joystick", RETRO_DEVICE_JOYPAD},
};
struct retro_controller_info retro_controller_info[] = {
    {retro_controller_description, 1}, {retro_controller_description, 1}, {0}};

struct retro_core_option_definition retro_options[] = {
    {"a800lib_artifacting",
     "NTSC Artifacting Emulation",
     "Alters display colors for games relying on the composite NTSC signal artifacts. Game reload required.",
     {
         {"None", 0},
         {"Auto", 0},
         {"Blue/Brown 1", 0},
         {"Blue/Brown 2", 0},
         {"GTIA", 0},
         {"CTIA", 0},
         {"New Blue/Brown 1", 0},
         {"New Blue/Brown 2", 0},
         {"New GTIA", 0},
         {"New CTIA", 0},
     },
     "Auto"},
    {0},
};

bool supports_no_game = false;

char *config_file_name = ".atari5200lib.cfg";

void core_get_system_info(struct retro_system_info *info) {
  info->library_name = "Atari 5200 (libatari800)";
  info->valid_extensions = "a52|car|bin";
}

static int min_analog, max_analog;
void handle_joystick(int player) {
  int left_x = input_state_cb(player, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X);
  int left_y = input_state_cb(player, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y);
  int right_x =
      input_state_cb(player ^ 1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X);
  int right_y =
      input_state_cb(player ^ 1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y);
  if (left_x > max_analog)
    max_analog = left_x;
  if (left_x < min_analog)
    min_analog = left_x;
  if (left_y > max_analog)
    max_analog = left_y;
  if (left_y < min_analog)
    min_analog = left_y;
  if (right_x > max_analog)
    max_analog = right_x;
  if (right_x < min_analog)
    min_analog = right_x;
  if (right_y > max_analog)
    max_analog = right_y;
  if (right_y < min_analog)
    min_analog = right_y;
  int val = input_state_cb(player, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_MASK);
  int dir = 0;
  if (val & (1 << RETRO_DEVICE_ID_JOYPAD_UP))
    dir |= 1, min_analog = -32000;
  if (val & (1 << RETRO_DEVICE_ID_JOYPAD_DOWN))
    dir |= 2, max_analog = 32000;
  if (val & (1 << RETRO_DEVICE_ID_JOYPAD_LEFT))
    dir |= 4, min_analog = -32000;
  if (val & (1 << RETRO_DEVICE_ID_JOYPAD_RIGHT))
    dir |= 8, max_analog = 32000;
  if (left_y < -ANALOG_MIN || right_y < -ANALOG_MIN)
    dir |= 1;
  if (left_y > ANALOG_MIN || right_y > ANALOG_MIN)
    dir |= 2;
  if (left_x < -ANALOG_MIN || right_x < -ANALOG_MIN)
    dir |= 4;
  if (left_x > ANALOG_MIN || right_x > ANALOG_MIN)
    dir |= 8;
  int trig = val & (1 << RETRO_DEVICE_ID_JOYPAD_A) ? 1 : 0;
  if (player == 0) {
    input.joy0 = dir;
    input.trig0 = trig;
  } else if (player == 1) {
    input.joy1 = dir;
    input.trig1 = trig;
  }

  extern uint8_t consol_mask;
  uint8_t consol = consol_mask ^ 0xf;
  if ((consol & 3) != player)
    return;

  static int numkeys[] = {
      AKEY_5200_0, AKEY_5200_1, AKEY_5200_2, AKEY_5200_3, AKEY_5200_4,
      AKEY_5200_5, AKEY_5200_6, AKEY_5200_7, AKEY_5200_8, AKEY_5200_9,
  };
  static int num[2], prev_val[2];
  if (val & (1 << (RETRO_DEVICE_ID_JOYPAD_L)) && !(prev_val[player] & (1 << (RETRO_DEVICE_ID_JOYPAD_L))) &&
      num[player] > 0)
    num[player]--;
  if (val & (1 << (RETRO_DEVICE_ID_JOYPAD_R)) && !(prev_val[player] & (1 << (RETRO_DEVICE_ID_JOYPAD_R))) &&
      num[player] < 9)
    num[player]++;
  prev_val[player] = val;

  if (val & (1 << (RETRO_DEVICE_ID_JOYPAD_L)) || val & (1 << (RETRO_DEVICE_ID_JOYPAD_R)))
    input.keycode = numkeys[num[player]];
  else if (val & (1 << (RETRO_DEVICE_ID_JOYPAD_L)) && (val & (1 << (RETRO_DEVICE_ID_JOYPAD_R))))
    input.keycode = AKEY_5200_RESET;
  else if (val & (1 << RETRO_DEVICE_ID_JOYPAD_START))
    input.keycode = AKEY_5200_START;
  else if (val & (1 << RETRO_DEVICE_ID_JOYPAD_SELECT))
    input.keycode = AKEY_5200_PAUSE;
  else if (val & (1 << RETRO_DEVICE_ID_JOYPAD_X))
    input.keycode = AKEY_5200_HASH;
  else if (val & (1 << RETRO_DEVICE_ID_JOYPAD_Y))
    input.keycode = AKEY_5200_ASTERISK;
  else if (val & (1 << RETRO_DEVICE_ID_JOYPAD_R2))
    input.keycode = AKEY_5200_9;
  else if (val & (1 << RETRO_DEVICE_ID_JOYPAD_L2))
    input.keycode = AKEY_5200_0;

  if (val & (1 << RETRO_DEVICE_ID_JOYPAD_B))
    input.shift = 1;
}
void core_handle_input(void) {
  min_analog = max_analog = 0;
  handle_joystick(0);
  handle_joystick(1);
  extern int INPUT_joy_5200_min, INPUT_joy_5200_max;
  if (min_analog)
    INPUT_joy_5200_min = 114 + min_analog * 100 / (32 * 1024);
  if (max_analog)
    INPUT_joy_5200_max = 114 + max_analog * 100 / (32 * 1024);
}

const char *get_artifacting_mode(uint32_t crc) {
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
  static struct {
    uint32_t crc;
    const char *mode;
  } auto_modes[] = {
      {0x9ad53bbc, "3"}, // Choplifter
      {0x931a454a, "2"}, // Microgammon
      {0xc597c087, "3"}, // Miniature Golf
      {0x35484751, "2"}, // AE
  };
  for (int i = 0; i < sizeof(auto_modes) / sizeof(auto_modes[0]); i++) {
    if (crc == auto_modes[i].crc)
      return auto_modes[i].mode;
  }
  return "0";
}
uint32_t CRC32_FromFile(FILE *f, uint32_t *result);
bool is_single_chip_16k(uint32_t crc) {
  static uint32_t list[] = {
      0xf43e7cd0, // Activision Decathlon, The (1984) (Activision).a52
      0x35484751, // AE (1984) (Atari) (Prototype).bin
      0x9bae58dc, // Beamrider (1984) (Activision).a52
      0xbe3cd348, // Berzerk (1983) (Atari).bin
      0x0624e6e7, // Blueprint (1982) (CBS).a52
      0x9ad53bbc, // Choplifter (1984) (Atari).a52
      0xd3bd3221, // Final Legacy (1982) (Atari) (Prototype).bin
      0x18a73af3, // H.E.R.O. (1984) (Activision).a52
      0x83517703, // Last Starfighter, The (1984) (Atari).a52
      0xab8e035b, // Meteorites (1983) (Electra Concepts).bin
      0x969cfe1a, // Millipede (1984) (Atari).a52
      0x7df1adfb, // Miner 2049 (1983) (Big Five Software).a52
      0xd0b2f285, // Moon Patrol (1983) (Atari).bin
      0x4b910461, // Pitfall II - The Lost Caverns (1984) (Activision).a52
      0xb5f3402b, // Quest for Quintana Roo (1984) (Sunrise Software).a52
      0x4252abd9, // Robotron 2084 (1983) (Atari).a52
      0x387365dc, // Space Shuttle - A Journey Into Space (1983) (Activision).bin
      0x0a4ddb1e, // Super Pac-Man (1982) (Atari) (Prototype).bin
      0x82e2981f, // Super Pac-Man (1982) (Atari) (Prototype) [h1].bin
      0x1187342f, // Tempest (1983) (Atari) (Prototype) [!].bin
      0x0ba22ece, // Track and Field (1984) (Atari).a52
      0xd6f7ddfd, // Wizard of Wor (1982) (CBS).a52
      0x2959d827, // Zone Ranger (1984) (Activision).a52
  };
  for (int i = 0; i < sizeof(list) / sizeof(list[0]); i++)
    if (list[i] == crc)
      return true;
  return false;
};

void core_load_game(const char *last_file_name) {
  FILE *fp = fopen(last_file_name, "rb");
  uint32_t crc = 0;
  CRC32_FromFile(fp, &crc);
  fseek(fp, 0, SEEK_END);
  int size = ftell(fp);
  l.log(RETRO_LOG_INFO, "cart file size %d, CRC %08x\n", size, crc);
  const char *cart_type = "1";
  if (size == 4 * 1024)
    cart_type = "20";
  else if (size == 8 * 1024)
    cart_type = "19";
  else if (size == 16 * 1024)
    cart_type = is_single_chip_16k(crc) ? "16" : "6";
  else if (size == 32 * 1024)
    cart_type = "4";
  else if (size == 40 * 1024)
    cart_type = "7";
  else if (size == 64 * 1024)
    cart_type = "71";
  else if (size == 128 * 1024)
    cart_type = "72";
  else if (size == 256 * 1024)
    cart_type = "73";
  else if (size == 512 * 1024)
    cart_type = "74";
  const char *test_args[] = {"-ntsc-artif", get_artifacting_mode_is_new() ? "ntsc-new" : "ntsc-old",
                             "-artif",      get_artifacting_mode(crc),
                             "-5200",       "-no-autosave-config",
                             "-config",     config_file_path,
                             "-ntsc",       "-audio16",
                             "-sound",      "-nostereo",
                             "-cart-type",  cart_type,
                             "-cart",       last_file_name,
                             NULL};
  libatari800_init(-1, (char **)test_args);
}

int core_get_main_memory_size() { return 16 * 1024; }
