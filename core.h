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

// System specific functions
void core_get_system_info(struct retro_system_info *info);
void core_load_game(const char *last_file_name);
int core_get_main_memory_size();
void core_handle_input(void);
struct retro_input_descriptor *core_get_retro_input_descriptors();

// Common Variables
extern input_template_t input;
extern retro_input_state_t input_state_cb;
extern uint8_t keyboard_state[RETROK_LAST];
#define NUM_PORTS 4
extern unsigned port_device[NUM_PORTS];
extern char config_file_path[], fake_exe_file_path[];

// Common functions
const bool get_artifacting_mode_is_new();
const char *get_variable(const char *key);

#endif
