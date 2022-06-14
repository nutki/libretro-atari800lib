#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "core.h"
#include "libatari800/libatari800.h"
#include "libretro.h"
#include "osk.h"

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
    {RETROK_LEFTBRACKET, AKEY_LESS},
    {RETROK_RIGHTBRACKET, AKEY_GREATER},
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
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Toggle OSK"},
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
    {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Toggle OSK"},
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
     "Alters display colors for games relying on the composite NTSC signal artifacts.",
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
    {"atari800lib_leds",
     "IO Activity LEDs",
     "Indicate disk and tape IO.",
     {
         {"None", 0},
         {"On screen", 0},
         {"On screen with counter", 0},
         {"API passthrough", 0},
     },
     "API passthrough"},
    {0},
};
const char *get_artifacting_mode(void);

bool supports_no_game = false;

char *config_file_name = ".atari800lib.cfg";

void core_get_system_info(struct retro_system_info *info) {
  info->library_name = "Atari 800 (libatari800)";
  info->valid_extensions = "xfd|atr|cdm|cas|bin|atx|car|com|xex|m3u";
}

#define DISK_LED_ID 0
#define TAPE_LED_ID 1
static int disk_led_state;
static int tape_led_state;
static struct retro_led_interface led_if;
extern int Screen_show_disk_led;
extern int Screen_show_sector_counter;
static void init_leds() {
  disk_led_state = 0;
  tape_led_state = 0;
  const char *led_mode = get_variable("atari800lib_leds");
  Screen_show_disk_led = 0;
  Screen_show_sector_counter = 0;
  led_if.set_led_state = 0;
  if (!strcmp(led_mode, "API passthrough")) {
    environ_cb(RETRO_ENVIRONMENT_GET_LED_INTERFACE, &led_if);
  } else if (!strcmp(led_mode, "On screen")) {
    Screen_show_disk_led = 1;
  } else if (!strcmp(led_mode, "On screen with counter")) {
    Screen_show_disk_led = 1;
    Screen_show_sector_counter = 1;
  }
}
static void handle_leds() {
  if (!led_if.set_led_state)
    return;

  // LED Logic taken from screen.c
  extern int SIO_last_op_time;
  extern int CASSETTE_writable;
  extern int CASSETTE_readable;
  extern int CASSETTE_record;
  int new_tape_state = (CASSETTE_readable && !CASSETTE_record) || (CASSETTE_writable && CASSETTE_record);
  int new_disk_state = SIO_last_op_time > 0;
  if (new_disk_state)
    SIO_last_op_time--;

  if (disk_led_state != new_disk_state)
    led_if.set_led_state(DISK_LED_ID, new_disk_state);
  if (tape_led_state != new_tape_state)
    led_if.set_led_state(TAPE_LED_ID, new_tape_state);

  disk_led_state = new_disk_state;
  tape_led_state = new_tape_state;
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
  // If INPUT_direct_mouse is disabled and INPUT_mouse_mode is 0, the paddle pot register will be reset to the
  // disconnected state
  extern int INPUT_mouse_mode; /* device emulated with mouse, 1 = PADDLES */
  extern int INPUT_direct_mouse;
  int use_paddles = port_device[MOUSE_PORT] == RETRO_DEVICE_ATARI_PADDLES;
  input.mouse_mode = INPUT_mouse_mode = INPUT_direct_mouse = use_paddles;
  if (use_paddles) {
    int val = input_state_cb(MOUSE_PORT, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_MASK);
    int pot_a =
        input_state_cb(MOUSE_PORT, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X);
    int pot_b =
        input_state_cb(MOUSE_PORT, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X);
    input.mouse_buttons =
        ((val & (1 << RETRO_DEVICE_ID_JOYPAD_A)) ? 1 : 0) | ((val & (1 << RETRO_DEVICE_ID_JOYPAD_B)) ? 2 : 0);
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
  handle_osk(val);
  handle_leds();
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
    if (!*w && !isalpha(*s))
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
const char *core_get_auto_artifacting_mode(void) { return "0"; }

static void set_message(const char *text) {
  struct retro_message_ext msg;
  msg.duration = 3000;
  msg.level = RETRO_LOG_INFO;
  msg.target = RETRO_MESSAGE_TARGET_OSD;
  msg.msg = text;
  msg.type = 0;
  msg.priority = 0;
  msg.progress = 0;
  environ_cb(RETRO_ENVIRONMENT_SET_MESSAGE_EXT, &msg);
}

static bool is_ejected = false;
static unsigned disk_index = 0, max_disk_index = 3;
#define MAX_DISK_LABEL 128
#define MAX_DISKS 10
static struct {
  char label[MAX_DISK_LABEL];
  char path[FILENAME_MAX];
} disk_info[MAX_DISKS];

static bool set_eject_state(bool ejected) {
  is_ejected = ejected;
  return true;
}
static bool get_eject_state() { return is_ejected; }
static unsigned get_image_index() { return disk_index; }
static bool set_image_index(unsigned index) {
  if (index >= max_disk_index)
    return false;
  if (index == disk_index)
    return true;
  disk_index = index;
  libatari800_mount_disk_image(1, disk_info[disk_index].path, 0);
  static char message_text[MAX_DISK_LABEL + 100];
  snprintf(message_text, sizeof(message_text) - 1, "Inserted disk: %s", disk_info[disk_index].label);
  set_message(message_text);
  return true;
}
static unsigned get_num_images() { return max_disk_index; }
static bool get_image_label(unsigned index, char *label, size_t len) {
  strncpy(label, disk_info[index].label, len);
  return true;
}
static const char *load_m3u(const char *path) {
  static char line[FILENAME_MAX], content_dir[FILENAME_MAX];
  FILE *f = fopen(path, "ra");
  if (!f)
    return NULL;
  char *s;
  max_disk_index = 0;
  disk_index = 0;
  is_ejected = false;
  while ((s = fgets(line, sizeof(line), f))) {
    while (isspace(*s))
      s++;
    if (*s == '#')
      continue;
    int len = strlen(s);
    while (len && isspace(s[len - 1]))
      s[--len] = 0;
    char *label = strchr(s, '|');
    if (label) {
      *label++ = 0;
      len = strlen(s);
    }
    if (!len)
      continue;
    if (max_disk_index == MAX_DISKS) {
      break;
    }
    int dirlen = strlen(path);
    while (dirlen && !IS_SLASH(path[dirlen - 1])) {
      dirlen--;
    }
    if (dirlen >= FILENAME_MAX)
      dirlen = FILENAME_MAX - 1;
    memcpy(content_dir, path, dirlen);
    content_dir[dirlen] = 0;
    snprintf(disk_info[max_disk_index].label, MAX_DISK_LABEL - 1, "%s", label ? label : s);
    if (snprintf(disk_info[max_disk_index].path, FILENAME_MAX - 1, "%s%s", content_dir, s) > 0)
      max_disk_index++;
  }
  fclose(f);
  if (!max_disk_index)
    return NULL;
  return disk_info[0].path;
}

struct retro_disk_control_ext_callback disk_control = {
    set_eject_state,
    get_eject_state,
    get_image_index,
    set_image_index,
    get_num_images,
    0, //  replace_image_index,
    0, //  add_image_index,
    0, //  set_initial_image,
    0, //  get_image_path,
    get_image_label,
};

void core_set_environment() {
  bool res, has_ext_disk_control = environ_cb(RETRO_ENVIRONMENT_GET_DISK_CONTROL_INTERFACE_VERSION, &res) && res >= 1;
  environ_cb(has_ext_disk_control ? RETRO_ENVIRONMENT_SET_DISK_CONTROL_EXT_INTERFACE
                                  : RETRO_ENVIRONMENT_SET_DISK_CONTROL_INTERFACE,
             &disk_control);
}

bool strcaseendswith(const char *str, const char *suffix) {
  const char *suffix_pos = str + strlen(str) - strlen(suffix);
  return suffix_pos >= str && strcasecmp(suffix_pos, suffix) == 0;
}

void core_load_game(const char *filename) {
  init_leds();
  if (strcaseendswith(filename, ".m3u")) {
    filename = load_m3u(filename);
  }
  // Make sure that the value of the ESC_enable_sio_patch is reset to TRUE on each library init.
  // Otherwise sioaccel option cannot be changed back to false with argv alone.
  extern int ESC_enable_sio_patch;
  ESC_enable_sio_patch = 1;
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
