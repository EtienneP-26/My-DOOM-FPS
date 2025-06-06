/*
** EPITECH PROJECT, 2025
** My-DOOM FPS
** File description:
** keybinds
*/

#include <SFML/Window/Keyboard.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

const char *keybinds_list[] = {
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "Num0",
    "Num1",
    "Num2",
    "Num3",
    "Num4",
    "Num5",
    "Num6",
    "Num7",
    "Num8",
    "Num9",
    "Escape",
    "LControl",
    "LShift",
    "LAlt",
    "LSystem",
    "RControl",
    "RShift",
    "RAlt",
    "RSystem",
    "Menu",
    "LBracket",
    "RBracket",
    "Semicolon",
    "Comma",
    "Period",
    "Quote",
    "Slash",
    "Backslash",
    "Tilde",
    "Equal",
    "Dash",
    "Space",
    "Return",
    "Backspace",
    "Tab",
    "PageUp",
    "PageDown",
    "End",
    "Home",
    "Insert",
    "Delete",
    "Add",
    "Subtract",
    "Multiply",
    "Divide",
    "Left",
    "Right",
    "Up",
    "Down",
    "Numpad0",
    "Numpad1",
    "Numpad2",
    "Numpad3",
    "Numpad4",
    "Numpad5",
    "Numpad6",
    "Numpad7",
    "Numpad8",
    "Numpad9",
    NULL
};

const sfKeyCode keybinds_values[] = {
    sfKeyA,
    sfKeyB,
    sfKeyC,
    sfKeyD,
    sfKeyE,
    sfKeyF,
    sfKeyG,
    sfKeyH,
    sfKeyI,
    sfKeyJ,
    sfKeyK,
    sfKeyL,
    sfKeyM,
    sfKeyN,
    sfKeyO,
    sfKeyP,
    sfKeyQ,
    sfKeyR,
    sfKeyS,
    sfKeyT,
    sfKeyU,
    sfKeyV,
    sfKeyW,
    sfKeyX,
    sfKeyY,
    sfKeyZ,
    sfKeyNum0,
    sfKeyNum1,
    sfKeyNum2,
    sfKeyNum3,
    sfKeyNum4,
    sfKeyNum5,
    sfKeyNum6,
    sfKeyNum7,
    sfKeyNum8,
    sfKeyNum9,
    sfKeyEscape,
    sfKeyLControl,
    sfKeyLShift,
    sfKeyLAlt,
    sfKeyLSystem,
    sfKeyRControl,
    sfKeyRShift,
    sfKeyRAlt,
    sfKeyRSystem,
    sfKeyMenu,
    sfKeyLBracket,
    sfKeyRBracket,
    sfKeySemicolon,
    sfKeyComma,
    sfKeyPeriod,
    sfKeyQuote,
    sfKeySlash,
    sfKeyBackslash,
    sfKeyTilde,
    sfKeyEqual,
    sfKeyDash,
    sfKeySpace,
    sfKeyReturn,
    sfKeyBackspace,
    sfKeyTab,
    sfKeyPageUp,
    sfKeyPageDown,
    sfKeyEnd,
    sfKeyHome,
    sfKeyInsert,
    sfKeyDelete,
    sfKeyAdd,
    sfKeySubtract,
    sfKeyMultiply,
    sfKeyDivide,
    sfKeyLeft,
    sfKeyRight,
    sfKeyUp,
    sfKeyDown,
    sfKeyNumpad0,
    sfKeyNumpad1,
    sfKeyNumpad2,
    sfKeyNumpad3,
    sfKeyNumpad4,
    sfKeyNumpad5,
    sfKeyNumpad6,
    sfKeyNumpad7,
    sfKeyNumpad8,
    sfKeyNumpad9
};

int finds_keycode(char *keybind)
{
    for (int i = 0; keybinds_list[i] != NULL; i++) {
        if (strcmp(keybinds_list[i], keybind) == 0)
            return i;
    }
    return -1;
}
