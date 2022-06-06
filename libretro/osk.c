#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"
#include "libatari800/libatari800.h"
#include "libretro.h"
#include "osk.h"

#define OSK_NUM_COLUMNS 12
#define OSK_NUM_ROWS 6

static struct osk_desc {
  char normal[4], shift[4], ctrl[4];
  int val;
} osk_desc[OSK_NUM_COLUMNS * OSK_NUM_ROWS] = {
    {"HLP", "HLP", "HLP", AKEY_HELP}, // page 1, line 1
    {"STA", "STA", "STA", AKEY_START},
    {"SEL", "SEL", "SEL", AKEY_SELECT},
    {"OPT", "OPT", "OPT", AKEY_OPTION},
    {"RES", "RES", "RES", AKEY_WARMSTART},
    {" F1", " F1", " F1", AKEY_F1},
    {" F2", " F2", " F2", AKEY_F2},
    {" F3", " F3", " F3", AKEY_F3},
    {" F4", " F4", " F4", AKEY_F4},
    {" < ", "Clr", " < ", AKEY_LESS},
    {" > ", "Ins", " > ", AKEY_GREATER},
    {"Bsp", "Del", "Bsp", AKEY_BACKSPACE},

    {"Esc", "Esc", "Esc", AKEY_ESCAPE}, // page 1, line 2
    {" 1 ", " ! ", " \xb1 ", AKEY_1},
    {" 2 ", " \" ", " \xb2 ", AKEY_2},
    {" 3 ", " # ", " \xb3 ", AKEY_3},
    {" 4 ", " $ ", " \xb4 ", AKEY_4},
    {" 5 ", " % ", " \xb5 ", AKEY_5},
    {" 6 ", " & ", " \xb6 ", AKEY_6},
    {" 7 ", " \' ", " \xb7 ", AKEY_7},
    {" 8 ", " @ ", " \xb8 ", AKEY_8},
    {" 9 ", " ( ", " \xb9 ", AKEY_9},
    {" 0 ", " ) ", " \xb0 ", AKEY_0},
    {"Brk", "Brk", "Brk", AKEY_BREAK},

    {"Tab", "Tab", "Tab", AKEY_TAB}, // page 1, line 3
    {" q ", " Q ", "Q \x11", AKEY_q},
    {" w ", " W ", "W \x17", AKEY_w},
    {" e ", " E ", "E \x05", AKEY_e},
    {" r ", " R ", "R \x12", AKEY_r},
    {" t ", " T ", "T \x14", AKEY_t},
    {" y ", " Y ", "Y \x19", AKEY_y},
    {" u ", " U ", "U \x15", AKEY_u},
    {" i ", " I ", "I \x09", AKEY_i},
    {" o ", " O ", "O \x0f", AKEY_o},
    {" p ", " P ", "P \x10", AKEY_p},
    {"Ret", "Ret", "Ret", AKEY_RETURN},

    {"Ctl", "Ctl", "CTL", AKEY_CTRL}, // page 1, line 4
    {" a ", " A ", "A \x01", AKEY_a},
    {" s ", " S ", "S \x13", AKEY_s},
    {" d ", " D ", "D \x04", AKEY_d},
    {" f ", " F ", "F \x06", AKEY_f},
    {" g ", " G ", "G \x07", AKEY_g},
    {" h ", " H ", "H \x08", AKEY_h},
    {" j ", " J ", "J \x0a", AKEY_j},
    {" k ", " K ", "K \x0b", AKEY_k},
    {" l ", " L ", "L \x0c", AKEY_l},
    {" ; ", " : ", "; \x7b", AKEY_SEMICOLON},
    {"Cap", "Cap", "Cap", AKEY_CAPSTOGGLE},

    {"Shf", "SHF", "Shf", AKEY_SHFT}, // page 1, line 5
    {" z ", " Z ", "Z \x1a", AKEY_z},
    {" x ", " X ", "X \x18", AKEY_x},
    {" c ", " C ", "C \x03", AKEY_c},
    {" v ", " V ", "V \x16", AKEY_v},
    {" b ", " B ", "B \x02", AKEY_b},
    {" n ", " N ", "N \x0e", AKEY_n},
    {" m ", " M ", "M \x0d", AKEY_m},
    {" , ", " [ ", ", \x00", AKEY_COMMA},
    {" . ", " ] ", ". \x60", AKEY_FULLSTOP},
    {" \x9c ", " \x9c ", " \x9c ", AKEY_UP},
    {"Inv", "Inv", "Inv", AKEY_ATARI},

    {"OPC", "OPC", "OPC", 1000}, // page 1, line 6
    {"Spc", "Spc", "Spc", AKEY_SPACE},
    {" + ", " \\ ", " \x1e ", AKEY_PLUS},
    {" - ", " _ ", " \x1c ", AKEY_MINUS},
    {" = ", " | ", " \x1d ", AKEY_EQUAL},
    {" * ", " ^ ", " \x1f ", AKEY_ASTERISK},
    {" / ", " ? ", " / ", AKEY_SLASH},
    {"", "", "", AKEY_NONE},
    {"", "", "", AKEY_NONE},
    {" \x9e ", " \x9e ", " \x9e ", AKEY_LEFT},
    {" \x9d ", " \x9d ", " \x9d ", AKEY_DOWN},
    {" \x9f ", " \x9f ", " \x9f ", AKEY_RIGHT},
};

static int osk_opacity = 0;

#define RGB565(r, g, b) (((r) << (5 + 6)) | ((g) << 6) | (b))

static void put_pixel(uint16_t *frame, int x, int y, uint16_t c) {
  frame += x + y * FRAME_BUF_WIDTH;
  *frame = osk_opacity ? ((*frame & 0xF7DE) >> 1) + ((c & 0xF7DE) >> 1) : c;
}

static void draw_box(unsigned short *mbuffer, int x, int y, int dx, int dy, unsigned color) {
  for (int i = x; i < x + dx; i++) {
    put_pixel(mbuffer, i, y, color);
    put_pixel(mbuffer, i, y + dy, color);
  }
  for (int j = y; j < y + dy; j++) {
    put_pixel(mbuffer, x, j, color);
    put_pixel(mbuffer, x + dx, j, color);
  }
}

void MEMORY_GetCharset(uint8_t *cs);

static void draw_text(uint16_t *mbuffer, int x, int y, uint16_t fg, uint16_t bg, const char *string) {
  static uint8_t charset[0x400];
  static int initialised = 0;
  if (!initialised) {
    MEMORY_GetCharset(charset);
    initialised = 1;
  }
  int len = strlen(string);
  for (int ypixel = 0; ypixel < 8; ypixel++) {
    for (int col = 0; col < len; col++) {
      uint8_t b = charset[(string[col] & 0x7f) * 8 + ypixel] ^ (string[col] & 0x80 ? 0 : 255);
      for (int bit = 0; bit < 8; bit++) {
        put_pixel(mbuffer, x + col * 8 + bit, y + ypixel, (b & (1 << (7 - bit))) ? fg : bg);
      }
    }
  }
}

#define XSIDE 27
#define YSIDE 15
#define YBASE (FRAME_BUF_HEIGHT - OSK_NUM_ROWS * YSIDE - 16)
#define XBASE ((FRAME_BUF_WIDTH - OSK_NUM_COLUMNS * XSIDE) / 2)

int osk_x = 0, osk_y = 0, osk_active = 0, prev_buttons = 0, shift_mode = 0, ctrl_mode = 0;
void core_osk_overlay(uint16_t *pix) {
  if (!osk_active)
    return;
  for (int x = 0; x < OSK_NUM_COLUMNS; x++) {
    for (int y = 0; y < OSK_NUM_ROWS; y++) {
      struct osk_desc *key = &osk_desc[y * OSK_NUM_COLUMNS + x];
      char *str = input.shift ? key->shift : input.control ? key->ctrl : key->normal;
      int selected = x == osk_x && y == osk_y;
      int col = selected ? RGB565(0, 31, 0) : RGB565(31, 31, 31);
      draw_box(pix, XBASE + x * XSIDE, YBASE + y * YSIDE, XSIDE, YSIDE, RGB565(0, 0, 0));
      if (key->val == AKEY_SHFT && input.shift)
        col = selected ? RGB565(0, 31, 31) : RGB565(0, 31, 21);
      if (key->val == AKEY_CTRL && input.control)
        col = selected ? RGB565(0, 31, 31) : RGB565(0, 31, 21);
      draw_text(pix, XBASE + 2 + x * XSIDE, YBASE + 4 + YSIDE * y, col, 0, str);
    }
  }
  draw_box(pix, XBASE + osk_x * XSIDE, YBASE + osk_y * YSIDE, XSIDE, YSIDE, RGB565(31, 0, 0));
}

int osk_get_keycode(int x, int y) { return osk_desc[y * OSK_NUM_COLUMNS + x].val; }

static int clicked_frame;
int clicked_with_repeat(int buttons, int button) {
  if (!(buttons & (1 << button)))
    return 0;
  if (!(prev_buttons & (1 << button)))
    return 1;
  if (clicked_frame >= 20 && clicked_frame % 10 == 0)
    return 1;
  return 0;
}
void handle_osk_active(int buttons) {
  clicked_frame = buttons == prev_buttons ? clicked_frame + 1 : 0;
  if (clicked_with_repeat(buttons, RETRO_DEVICE_ID_JOYPAD_LEFT))
    osk_x = (osk_x + OSK_NUM_COLUMNS - 1) % OSK_NUM_COLUMNS;
  if (clicked_with_repeat(buttons, RETRO_DEVICE_ID_JOYPAD_RIGHT))
    osk_x = (osk_x + 1) % OSK_NUM_COLUMNS;
  if (clicked_with_repeat(buttons, RETRO_DEVICE_ID_JOYPAD_UP))
    osk_y = (osk_y + OSK_NUM_ROWS - 1) % OSK_NUM_ROWS;
  if (clicked_with_repeat(buttons, RETRO_DEVICE_ID_JOYPAD_DOWN))
    osk_y = (osk_y + 1) % OSK_NUM_ROWS;
  if (buttons & (1 << RETRO_DEVICE_ID_JOYPAD_A)) {
    int clicked = !(prev_buttons & (1 << RETRO_DEVICE_ID_JOYPAD_A));
    int key = osk_get_keycode(osk_x, osk_y);
    if (key == AKEY_SHFT && clicked)
      shift_mode = !shift_mode;
    if (key == AKEY_CTRL && clicked)
      ctrl_mode = !ctrl_mode;
    if (key == 1000 && clicked)
      osk_opacity = !osk_opacity;
    if (key == AKEY_START)
      input.start = 1;
    if (key == AKEY_SELECT)
      input.select = 1;
    if (key == AKEY_OPTION)
      input.option = 1;
    if ((key == AKEY_WARMSTART || key == AKEY_BREAK) && clicked)
      input.special = -key;
    if (key == 0) {
      input.keychar = shift_mode ? 'L' : 'l';
    } else if (key > 0 && key < 256 && (key & 0x3F)) {
      input.keycode = key | (shift_mode ? AKEY_SHFT : 0) | (ctrl_mode ? AKEY_CTRL : 0);
    }
  };
  if (shift_mode)
    input.shift = 1;
  if (ctrl_mode)
    input.control = 1;
}
void handle_osk(int buttons) {
  if (buttons & (1 << RETRO_DEVICE_ID_JOYPAD_L) && !(prev_buttons & (1 << RETRO_DEVICE_ID_JOYPAD_L)))
    osk_active = !osk_active;
  if (osk_active) {
    handle_osk_active(buttons);
    input.joy0 = input.joy1 = input.joy2 = input.joy3 = 0;
    input.trig0 = input.trig1 = input.trig2 = input.trig3 = 0;
  }
  prev_buttons = buttons;
}

// TODO CTRL-L, CTRL-1
