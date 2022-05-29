#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"
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
  info->need_fullpath = true;
  info->library_version = "4.2.0";
  core_get_system_info(info);
  //  info->valid_extensions = "xfd|atr|cdm|cas|bin|a52|atx|car|com|xex";
}

static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_environment_t environ_cb;
static retro_input_poll_t input_poll_cb;
retro_input_state_t input_state_cb;
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

bool get_artifacting_mode_is_new(void) {
  const char *mode_str = get_variable("a5200_artifacting");
  if (!strncmp(mode_str, "New ", 4))
    return true;
  return false;
}

const char *system_dir;
char config_file_path[FILENAME_MAX];
void dummy_log(enum retro_log_level level, const char *fmt, ...) {}
struct retro_log_callback l = {dummy_log};
void retro_set_environment(retro_environment_t cb) {
  enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_RGB565;

  environ_cb = cb;

  /* We know it's supported, it's internal to RetroArch. */
  environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt);
  struct retro_keyboard_callback kbcb = {retro_keyboard_event_cb};
  environ_cb(RETRO_ENVIRONMENT_SET_KEYBOARD_CALLBACK, &kbcb);
  bool supports_achievements = true;
  environ_cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &supports_no_game);
  environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS, retro_options);
  environ_cb(RETRO_ENVIRONMENT_SET_CONTROLLER_INFO, retro_controller_info);
  environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, retro_input_desc);
  environ_cb(RETRO_ENVIRONMENT_SET_SUPPORT_ACHIEVEMENTS, &supports_achievements);
  uint64_t quirks = RETRO_SERIALIZATION_QUIRK_CORE_VARIABLE_SIZE;
  environ_cb(RETRO_ENVIRONMENT_SET_SERIALIZATION_QUIRKS, &quirks);
  environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &system_dir);
  environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &l);
  if (system_dir) {
    snprintf(config_file_path, sizeof(config_file_path) - 1, "%s/%s", system_dir, config_file_name);
  } else {
    strcpy(config_file_path, config_file_name);
  }
  FILE *fp = fopen(config_file_path, "ab");
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

void handle_input(void) {
  input.keycode = 0;
  input.shift = 0;
  input.control = 0;
  core_handle_input();
#if 0
  input.select = val & (1 << RETRO_DEVICE_ID_JOYPAD_SELECT) ? 1 : 0;
  input.start = val & (1 << RETRO_DEVICE_ID_JOYPAD_START) ? 1 : 0;
  input.option = val & (1 << RETRO_DEVICE_ID_JOYPAD_Y) ? 1 : 0;
#endif
  for (int i = 0; keymap[i].retro_code; i++) {
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

bool retro_load_game(const struct retro_game_info *info) {
  if (info) {
    if (last_file_name)
      free(last_file_name);
    last_file_name = strdup(info->path);
  }
  core_load_game(last_file_name);
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
    return core_get_main_memory_size();
  return 0;
}

void retro_cheat_reset(void) {}

void retro_cheat_set(unsigned idx, bool enabled, const char *code) {
  (void)idx;
  (void)enabled;
  (void)code;
}
