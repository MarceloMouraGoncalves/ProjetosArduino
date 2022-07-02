#include <EEPROM.h>

void EepromWriteInt(int address, int value)
{
    EEPROM.put(address, value);
}

int EepromReadInt(int address)
{
    int value;
    EEPROM.get(address, value);

    return value;
}

void EepromWriteFloat(int address, float value)
{
    EEPROM.put(address, value);
}

float EepromReadFloat(int address)
{
    float value;
    EEPROM.get(address, value);

    if (isnan(value))
    {
        value = 0;
    }

    return value;
}