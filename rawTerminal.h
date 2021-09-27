/**
 * sources:
 * - https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
 */
#ifndef RAW_TERMINAL_H
#define RAW_TERMINAL_H

// standard import
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// custom import
// NONE
// const
#define RAW_TERMINAL_BUFFER_SIZE 10
// defining types
typedef enum keyboard_inputs {
    /* letters */
    // lower case
    INPUT_a = 0,
    INPUT_b,
    INPUT_c,
    INPUT_d,
    INPUT_e,
    INPUT_f,
    INPUT_g,
    INPUT_h,
    INPUT_i,
    INPUT_j,
    INPUT_k,
    INPUT_l,
    INPUT_m,
    INPUT_n,
    INPUT_o,
    INPUT_p,
    INPUT_q,
    INPUT_r,
    INPUT_s,
    INPUT_t,
    INPUT_u,
    INPUT_v,
    INPUT_w,
    INPUT_x,
    INPUT_y,
    INPUT_z,
    // uppercase
    INPUT_A,
    INPUT_B,
    INPUT_C,
    INPUT_D,
    INPUT_E,
    INPUT_F,
    INPUT_G,
    INPUT_H,
    INPUT_I,
    INPUT_J,
    INPUT_K,
    INPUT_L,
    INPUT_M,
    INPUT_N,
    INPUT_O,
    INPUT_P,
    INPUT_Q,
    INPUT_R,
    INPUT_S,
    INPUT_T,
    INPUT_U,
    INPUT_V,
    INPUT_W,
    INPUT_X,
    INPUT_Y,
    INPUT_Z,
    /* direction arrows */
    INPUT_ARROW_UP,
    INPUT_ARROW_DOWN,
    INPUT_ARROW_RIGHT,
    INPUT_ARROW_LEFT
} keyboard_input;

// https://stackoverflow.com/questions/16770690/function-pointer-to-different-functions-with-different-arguments-in-c
// https://stackoverflow.com/questions/16770690/function-pointer-to-different-functions-with-different-arguments-in-c

typedef enum {
    VOID_FUNCTION,
} rawTerminal_actionFunctionType;

typedef union {
    void (*void_function)();
} rawTerminal_actionFunction;

typedef struct {
    rawTerminal_actionFunction func;
    rawTerminal_actionFunctionType type;
} rawTerminal_action;


/**
 * The enableTerminalRawMode() function will change the terminal mode to raw mode (canonical mode by default)
 */
void enableTerminalRawMode();

/**
 * The disableTerminalRawMode() function will return the terminal to it's original mode.
 */
void disableTerminalRawMode();

/**
 * The getKeyboardInputCharValue() function return the char value of a special key from the keyboard (eg. directionnal arrows)
 * 
 * @param input the keyboard input type
 * 
 * @return the str corresponding to the specified input
 */
char * getKeyboardInputCharValue(keyboard_input input);

/**
 * The HandleRawModeKeyboard() function return the array of char entered in the terminal it will handle special keys like directionnal arrows.
 * 
 * @return the array of char entered in the terminal
 */
char * HandleRawModeKeyboard();

/**
 * The getKeyboardInputType() function return the input type corresponding to the char pattern entered
 * 
 * @param pattern the char pattern to check
 * 
 * @return the keyboard input mapped to the entered pattern or -1 if no corresponding keyboard_input
 */
keyboard_input getKeyboardInputType(char * pattern);

/**
 * The printEscapeSequence() function will display all string in the terminal (eg. escape sequence).
 */
void printEscapeSequence(char * str);


void assignActionToKeyBoardInput(keyboard_input input, rawTerminal_action * action);

#endif //RAW_TERMINAL_H