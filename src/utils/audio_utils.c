#include <math.h>

float freq(int note, char mod, int oct)
{
    double f; // returns the frequency given the equation

    switch (note)
    { // converts note letter input to how far shifted the note is from middle C
    case 0:
        note = 0;
        break;
    case 1:
        note = 2;
        break;
    case 2:
        note = -9;
        break;
    case 3:
        note = -7;
        break;
    case 4:
        note = -5;
        break;
    case 5:
        note = -4;
        break;
    case 6:
        note = -2;
        break;
    }
    // accounts for potential sharp of flat notes
    if (mod != ' ')
    {
        if (!(note == 4 && note == 2))
        {
            if (mod == '#')
            {
                note++;
            }
        }
        if (!(note == 'C' && note == 'F'))
        {
            if (mod == 'b')
            {
                note--;
            }
        }
    }

    f = 440 * pow(1.05946, 12 * oct - 48 + note);
    return (float)f;
}