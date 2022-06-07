#ifndef _CORE_H
#define _CORE_H
#include "libatari800/libatari800.h"
#include "libretro.h"

// System specific variables
extern struct keymap {
  unsigned retro_code;
  uint8_t a800_code;
} keymap[];
extern struct retro_input_descriptor retro_input_desc[];
extern struct retro_controller_info retro_controller_info[];
extern struct retro_core_option_definition retro_options[];
extern bool supports_no_game;
extern char *config_file_name;
extern struct retro_log_callback l;

#define ANALOG_MIN 4096
#ifdef _WIN32
#define DEFAULT_SLASH "\\"
#else
#define DEFAULT_SLASH "/"
#endif

// System specific functions
void core_get_system_info(struct retro_system_info *info);
void core_load_game(const char *last_file_name);
int core_get_main_memory_size();
void core_handle_input(void);
struct retro_input_descriptor *core_get_retro_input_descriptors();
void core_set_environment(void);
void core_osk_overlay(uint16_t *frame_buf);
const char *core_get_auto_artifacting_mode(void);

// Common Variables
#define FRAME_BUF_WIDTH 384
#define FRAME_BUF_HEIGHT 240
extern input_template_t input;
extern retro_input_state_t input_state_cb;
extern retro_environment_t environ_cb;
extern uint8_t keyboard_state[RETROK_LAST];
#define NUM_PORTS 4
extern unsigned port_device[NUM_PORTS];
extern char config_file_path[], fake_exe_file_path[];
extern const char *content_dir;

// Common functions
const bool get_artifacting_mode_is_new();
const char *get_artifacting_mode(void);
const char *get_variable(const char *key);

// Missing key definitions from libatari800.h
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

#define AKEY_SHFT 0x40
#define AKEY_CTRL 0x80

#define AKEY_NONE -1
#define AKEY_WARMSTART -2
#define AKEY_COLDSTART -3
#define AKEY_EXIT -4
#define AKEY_BREAK -5
#define AKEY_START -10
#define AKEY_SELECT -11
#define AKEY_OPTION -12

#endif

#endif
