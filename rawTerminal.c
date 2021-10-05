// header file
#include "rawTerminal.h"
// end header

struct termios orig_termios; // the original config of the terminal (before raw mode)

rawTerminal_action * rawTerminalActions = NULL; // all the possible action of the raw terminal

void dummy() { return; }

void enableTerminalRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit( disableTerminalRawMode );

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    /* init raw terminal actions*/
    rawTerminalActions = calloc(INPUT_ARROW_LEFT + 1, sizeof(rawTerminal_action));
    for (int i = 0; i < INPUT_ARROW_LEFT + 1; i++) {
        rawTerminalActions[i].func.void_function = &dummy;
        rawTerminalActions[i].type = VOID_FUNCTION;
    }
}

void disableTerminalRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    /** free space allocated to raw terminal actions*/
    free(rawTerminalActions);
}

char * getKeyboardInputCharValue(keyboard_input input) {
    char * charValue;
    if (input >= INPUT_a && input <= INPUT_z) { // is a lowercase letter
        charValue = calloc(1 + 1, sizeof(char));
        charValue[0] = 'a' + input;
        return charValue;
    } else if (input >= INPUT_A && input <= INPUT_Z) { // is a uppercase letter
        charValue = calloc(1 + 1, sizeof(char));
        charValue[0] = 'A' + input - 26; // the -26 offset to the correct value
        return charValue;
    } else if (input >= INPUT_ARROW_UP && input <= INPUT_ARROW_LEFT) {
        charValue = calloc(3 + 1, sizeof(char));
        switch (input)
        {
        case INPUT_ARROW_UP:
            charValue[0] = (char)27;
            charValue[1] = (char)91;
            charValue[2] = (char)65;
            return charValue;

        case INPUT_ARROW_DOWN:
            charValue[0] = (char)27;
            charValue[1] = (char)91;
            charValue[2] = (char)66;
            return charValue;

        case INPUT_ARROW_RIGHT:
            charValue[0] = (char)27;
            charValue[1] = (char)91;
            charValue[2] = (char)67;
            return charValue;

        case INPUT_ARROW_LEFT:
            charValue[0] = (char)27;
            charValue[1] = (char)91;
            charValue[2] = (char)68;
            return charValue;
        default: return NULL;
        }
    } else {
        switch (input)
        {
        case INPUT_ENTER:
            charValue = calloc(1 + 1, sizeof(char));
            charValue[0] = (char)10;
            return charValue;
        case INPUT_BACKSPACE:
            charValue = calloc(1 + 1, sizeof(char));
            charValue[0] = (char)127;
            return charValue[0] = (char)10;
        case INPUT_ESCAPE_CHAR:
            charValue = calloc(1 + 1, sizeof(char));
            charValue[0] = (char)27;
            return charValue;
        default: return NULL;
        }
    }
}

char * HandleRawModeKeyboard() {
    char * input = calloc(RAW_TERMINAL_BUFFER_SIZE, sizeof(char));

    int readReturnValue;
    readReturnValue = read(STDIN_FILENO, input, RAW_TERMINAL_BUFFER_SIZE);
    input = realloc(input, readReturnValue);

    int keyboardInputValue;
    if ((keyboardInputValue = getKeyboardInputType(input)) != -1) {
        switch (rawTerminalActions[keyboardInputValue].type)
        {
        case VOID_FUNCTION:
            rawTerminalActions[keyboardInputValue].func.void_function();
            break;
        
        default:
            break;
        }
    }

    return input;
}

keyboard_input getKeyboardInputType(char * pattern) {
    for (int enumElement = 0; enumElement <= INPUT_ARROW_LEFT; enumElement++)
    {
        char * enumCharValue = getKeyboardInputCharValue(enumElement);
        if (strcmp(pattern, enumCharValue) == 0) return enumElement; 
    }

    return -1; // no match found
}

void printEscapeSequence(char * str) {
    int i = 0;
    while (str[i] != '\0')
    {
        printf("%d, ", str[i]);
        i++;
    }
    printf("\n");
}

void assignActionToKeyBoardInput(keyboard_input input, rawTerminal_action * action) {
    rawTerminalActions[input].type = action->type;
    rawTerminalActions[input].func = action->func;
}