#pragma once

int vitalsOk(float temperature, float pulseRate, float spo2);
bool checkTemperature(float temperature);
bool checkPulseRate(float pulseRate);
bool checkSpo2(float spo2);
void displayWarning();
