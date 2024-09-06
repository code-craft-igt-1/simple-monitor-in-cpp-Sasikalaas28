#pragma once

bool isTemperatureOk(float temperature);
bool isPulseRateOk(float pulseRate);
bool isSpo2Ok(float spo2);
void buffering();
bool isVitalsOk(float temperature, float pulseRate, float spo2);
