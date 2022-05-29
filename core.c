#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libatari800.h"
#include "libretro.h"

#define FRAME_BUF_WIDTH 384
#define FRAME_BUF_HEIGHT 240
static uint16_t frame_buf[FRAME_BUF_WIDTH * FRAME_BUF_HEIGHT];

input_template_t input;
static uint16_t palette[256] = {
    0,     6371,  14791, 23243, 31695, 38034, 44373, 48631, 52857, 57051, 59196, 61309, 63390, 65503, 65535, 65535,
    14496, 22784, 33153, 41506, 51940, 58308, 64643, 64835, 65059, 65126, 65225, 65322, 65450, 65486, 65523, 65523,
    16576, 28898, 39203, 45508, 51844, 58180, 64515, 64612, 64709, 64871, 65064, 65067, 65069, 65200, 65332, 65332,
    18592, 30913, 45282, 51459, 55587, 59847, 64138, 64268, 64397, 64495, 64625, 64755, 64853, 64983, 65081, 65081,
    45,    14477, 28942, 35153, 41364, 47575, 51705, 55867, 60061, 62206, 64383, 64479, 64575, 64703, 64831, 64831,
    10287, 16464, 22642, 28979, 35285, 41496, 49755, 53949, 58111, 60287, 62463, 64607, 64735, 64799, 64863, 64863,
    12369, 16469, 20602, 24922, 31290, 35418, 41627, 45789, 47903, 50015, 52159, 54303, 54431, 56575, 56671, 56671,
    240,   308,   2425,  8698,  17019, 19165, 23391, 25535, 29727, 33951, 38175, 38239, 40351, 44543, 50783, 50783,
    2097,  8404,  14710, 18936, 23163, 25309, 27455, 31679, 35903, 38015, 40159, 42271, 46463, 48607, 50719, 50719,
    6475,  6606,  6738,  6901,  7064,  13369, 19675, 19805, 21951, 30271, 36575, 38623, 40703, 44863, 51039, 51039,
    10752, 14976, 17152, 17346, 15524, 19685, 21831, 24042, 26254, 28431, 30640, 32721, 34802, 40948, 45046, 45046,
    2561,  2721,  4929,  5089,  5250,  7458,  7618,  7747,  9923,  18213, 28552, 32681, 34795, 40943, 47091, 47091,
    513,   641,   802,   930,   3138,  3267,  3427,  20003, 34500, 36676, 40900, 45032, 47083, 53229, 57328, 57328,
    417,   482,   2627,  10979, 19364, 23556, 25733, 34053, 42374, 44551, 46728, 50888, 55049, 59273, 63466, 63466,
    8576,  8640,  8704,  21155, 33606, 37894, 44231, 50471, 54696, 56839, 58951, 59078, 59174, 61323, 65519, 65519,
    16576, 22752, 28961, 35266, 43651, 45860, 48038, 54311, 58504, 60681, 64875, 64939, 65036, 65070, 65104, 65104};

static uint8_t keyboard_state[RETROK_LAST];
void retro_keyboard_event_cb(bool down, unsigned keycode, uint32_t character, uint16_t key_modifiers) {
  if (keycode)
    keyboard_state[keycode] = down;
}
static struct {
  unsigned retro_code;
  uint8_t a800_code;
} keymap[] = {
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
};

void retro_init(void) {
  // FILE *f = fopen("./default.act", "rb");
  // if (f) for (int i = 0; i < 256; i++) {
  //    uint8_t c[3];
  //    fread(c, 1, 3, f);
  //    palette[i] = (c[0] >> 3 << 11) | (c[1] >> 2 << 5) | (c[2] >> 3);
  //    printf("%d,",palette[i]);
  // }
}

void retro_deinit(void) {}

unsigned retro_api_version(void) { return RETRO_API_VERSION; }

void retro_set_controller_port_device(unsigned port, unsigned device) {
  (void)port;
  (void)device;
}

void retro_get_system_info(struct retro_system_info *info) {
  memset(info, 0, sizeof(*info));
  info->library_name = "Atari 5200 (libatari800)";
  info->library_version = "4.2.0";
  info->need_fullpath = true;
  //  info->valid_extensions = "xfd|atr|cdm|cas|bin|a52|atx|car|com|xex";
  info->valid_extensions = "a52|car|bin";
}

static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_environment_t environ_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;
const char *get_variable(const char *key) {
  struct retro_variable var = {key, 0};
  if (environ_cb)
    environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var);
  return var.value ? var.value : "";
}

void retro_get_system_av_info(struct retro_system_av_info *info) {
  info->timing.fps = libatari800_get_fps();
  info->timing.sample_rate = libatari800_get_sound_frequency();

  info->geometry.base_width = FRAME_BUF_WIDTH;
  info->geometry.base_height = FRAME_BUF_HEIGHT;
  info->geometry.max_width = FRAME_BUF_WIDTH;
  info->geometry.max_height = FRAME_BUF_HEIGHT;
  info->geometry.aspect_ratio = (float)FRAME_BUF_WIDTH / (float)FRAME_BUF_HEIGHT;
}

struct retro_core_option_definition retro_options[] = {
    {"a5200_artifacting",
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
const char *get_artifacting_mode(uint32_t crc) {
  const char *mode_str = get_variable("a5200_artifacting");
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
bool get_artifacting_mode_is_new(void) {
  const char *mode_str = get_variable("a5200_artifacting");
  if (!strncmp(mode_str, "New ", 4))
    return true;
  return false;
}

struct retro_controller_description retro_controller_description[] = {
    {"5200 Joystick", RETRO_DEVICE_JOYPAD},
};
struct retro_controller_info retro_controller_info[] = {
    {retro_controller_description, 1}, {retro_controller_description, 1}, {0}};

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

const char *system_dir;
char conf_file_name[FILENAME_MAX];
void dummy_log(enum retro_log_level level, const char *fmt, ...) {}
struct retro_log_callback l = {dummy_log};
void retro_set_environment(retro_environment_t cb) {
  enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_RGB565;

  environ_cb = cb;

  /* We know it's supported, it's internal to RetroArch. */
  environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt);
  struct retro_keyboard_callback kbcb = {retro_keyboard_event_cb};
  environ_cb(RETRO_ENVIRONMENT_SET_KEYBOARD_CALLBACK, &kbcb);
  bool bool_false = false, bool_true = true;
  environ_cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &bool_false);
  environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS, retro_options);
  environ_cb(RETRO_ENVIRONMENT_SET_CONTROLLER_INFO, retro_controller_info);
  environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, retro_input_desc);
  environ_cb(RETRO_ENVIRONMENT_SET_SUPPORT_ACHIEVEMENTS, &bool_true);
  uint64_t quirks = RETRO_SERIALIZATION_QUIRK_CORE_VARIABLE_SIZE;
  environ_cb(RETRO_ENVIRONMENT_SET_SERIALIZATION_QUIRKS, &quirks);
  environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &system_dir);
  environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &l);
  if (system_dir) {
    snprintf(conf_file_name, sizeof(conf_file_name) - 1, "%s/.atari5200lib.cfg", system_dir);
  } else {
    strcpy(conf_file_name, ".atari5200lib.cfg");
  }
  FILE *fp = fopen(conf_file_name, "ab");
  if (fp)
    fclose(fp);
}

void retro_set_audio_sample(retro_audio_sample_t cb) { audio_cb = cb; }

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) { audio_batch_cb = cb; }

void retro_set_input_poll(retro_input_poll_t cb) { input_poll_cb = cb; }

void retro_set_input_state(retro_input_state_t cb) { input_state_cb = cb; }

void retro_set_video_refresh(retro_video_refresh_t cb) { video_cb = cb; }

char *last_file_name;
void retro_reset(void) {
  retro_unload_game();
  retro_load_game(0);
}

#define ANALOG_MIN 4096
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
void handle_input(void) {
  min_analog = max_analog = 0;
  input.keycode = 0;
  input.shift = 0;
  input.control = 0;
#if 0
  input.select = val & (1 << RETRO_DEVICE_ID_JOYPAD_SELECT) ? 1 : 0;
  input.start = val & (1 << RETRO_DEVICE_ID_JOYPAD_START) ? 1 : 0;
  input.option = val & (1 << RETRO_DEVICE_ID_JOYPAD_Y) ? 1 : 0;
#endif
  handle_joystick(0);
  handle_joystick(1);
  extern int INPUT_joy_5200_min, INPUT_joy_5200_max;
  if (min_analog)
    INPUT_joy_5200_min = 114 + min_analog * 100 / (32 * 1024);
  if (max_analog)
    INPUT_joy_5200_max = 114 + max_analog * 100 / (32 * 1024);
  for (int i = 0; i < sizeof(keymap) / sizeof(keymap[0]); i++) {
    if (keyboard_state[keymap[i].retro_code]) {
      input.keycode = keymap[i].a800_code;
      break;
    }
  }
}
void retro_run(void) {
  input_poll_cb();
  handle_input();
  libatari800_next_frame(&input);

  uint8_t *frame = libatari800_get_screen_ptr();
  for (int i = 0; i < FRAME_BUF_HEIGHT * FRAME_BUF_WIDTH; i++) {
    frame_buf[i] = palette[frame[i]];
  }
  video_cb(frame_buf, FRAME_BUF_WIDTH, FRAME_BUF_HEIGHT, 2 * FRAME_BUF_WIDTH);

  int16_t *audio = (void *)libatari800_get_sound_buffer();
  int audio_len = libatari800_get_sound_buffer_len();
  int16_t audio_buf[10000];
  for (int i = 0; i < audio_len / 2; i++) {
    audio_buf[i * 2] = audio_buf[i * 2 + 1] = audio[i];
  }
  audio_batch_cb(audio_buf, audio_len / 2);
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

bool retro_load_game(const struct retro_game_info *info) {
  if (info) {
    if (last_file_name)
      free(last_file_name);
    last_file_name = strdup(info->path);
  }
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
  const char *test_args[] = {"-ntsc-artif",  get_artifacting_mode_is_new() ? "ntsc-new" : "ntsc-old",
                             "-artif",       get_artifacting_mode(crc),
                             "-5200",        "-no-autosave-config",
                             "-config",      conf_file_name,
                             "-ntsc",        "-audio16",
                             "-nostereo",    "-cart-type",
                             cart_type,      "-cart",
                             last_file_name, NULL};
  libatari800_init(-1, (char **)test_args);
  libatari800_clear_input_array(&input);
  return true;
}

void retro_unload_game(void) {
  libatari800_exit();
  free(last_file_name);
}

unsigned retro_get_region(void) { return RETRO_REGION_NTSC; }

bool retro_load_game_special(unsigned type, const struct retro_game_info *info, size_t num) {
  (void)type;
  (void)info;
  (void)num;
  return false;
}

size_t retro_serialize_size(void) { return STATESAV_MAX_SIZE; }

bool retro_serialize(void *data, size_t size) {
  if (size < STATESAV_MAX_SIZE)
    return false;
  libatari800_get_current_state(data);
  return true;
}

bool retro_unserialize(const void *data, size_t size) {
  if (size < STATESAV_MAX_SIZE)
    return false;
  libatari800_restore_state((void *)data);
  return true;
}

void *retro_get_memory_data(unsigned id) {
  if (id == RETRO_MEMORY_SYSTEM_RAM)
    return libatari800_get_main_memory_ptr();
  return NULL;
}

size_t retro_get_memory_size(unsigned id) {
  if (id == RETRO_MEMORY_SYSTEM_RAM)
    return 16 * 1024;
  return 0;
}

void retro_cheat_reset(void) {}

void retro_cheat_set(unsigned idx, bool enabled, const char *code) {
  (void)idx;
  (void)enabled;
  (void)code;
}
