#include <OneWire.h>
#include <DallasTemperature.h>

#define PINO_SENSOR_TEMP 13
#define TEMPERATURE_PRECISION 9

OneWire oneWire(PINO_SENSOR_TEMP);

DallasTemperature sensors(&oneWire);
DeviceAddress sensorTempAddress;

void IniciarLeituraDeTemperatura()
{
    sensors.begin();    
    sensors.getAddress(sensorTempAddress, 0);
    sensors.setResolution(sensorTempAddress, TEMPERATURE_PRECISION);
}

float LerTemperaturaC()
{
    sensors.requestTemperatures();

    return sensors.getTempC(sensorTempAddress);
}