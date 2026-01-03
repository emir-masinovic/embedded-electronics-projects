#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <Keypad.h>

namespace Utils
{
    const char *const charsets[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ ",
        "abcdefghijklmnopqrstuvwxyz ",
        "0123456789",
        ".!-@_#$%&*()[]",
    };

    enum InputAction
    {
        ACT_NONE,
        ACT_UP,
        ACT_DOWN,
        ACT_LEFT,
        ACT_RIGHT,
        ACT_SELECT,
        ACT_DELETE,
        ACT_ALT,
        ACT_HOME,
        ACT_END,
        ACT_CONFIRM,
        ACT_BACK
    };

    // clang-format off
    inline InputAction getAction(char key)
    {
        switch (key)
        {
        case '2': return ACT_UP;
        case '8': return ACT_DOWN;
        case '4': return ACT_LEFT;
        case '6': return ACT_RIGHT;
        case '5': return ACT_SELECT;
        case 'A': return ACT_HOME;
        case 'B': return ACT_END;
        case 'C': return ACT_CONFIRM;
        case 'D': return ACT_BACK;
        case '7': return ACT_DELETE;
        case '*':
        case '#': return ACT_ALT;
        default:  return ACT_NONE;
        }
    }
    // clang-format on

    // Vertical menu navigation
    inline bool navigate(InputAction action, int &currentRow, int maxRows)
    {
        int oldRow = currentRow;
        if (action == ACT_UP && currentRow > 0)
            currentRow--;
        else if (action == ACT_DOWN && currentRow < maxRows - 1)
            currentRow++;
        return oldRow != currentRow;
    }

    inline bool shouldRepeat(KeyState state, unsigned long &timer, int interval = 150)
    {
        if (state != HOLD)
            return false;
        if (millis() - timer >= (unsigned long)interval)
        {
            timer = millis();
            return true;
        }
        return false;
    }

    inline void deleteChar(char *buf, int &cursor)
    {
        int strLen = (int)strlen(buf);
        if (strLen > 0 && cursor > 0)
        {
            for (int i = cursor - 1; i < strLen; i++)
                buf[i] = buf[i + 1];
            cursor--;
        }
    }

    inline void moveClamped(int &val, int delta, int min, int max)
    {
        int next = val + delta;
        if (next >= min && next <= max)
            val = next;
    }

    inline int wrapValue(int val, int delta, int max) { return (val + delta + max) % max; }
}
#endif