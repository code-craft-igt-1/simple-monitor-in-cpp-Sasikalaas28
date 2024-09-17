#pragma once
#include <iostream>
enum Language {
    TAMIL,
    GREEK
//  DUTCH supported in future
};
using namespace std;
void initializeWarnigMessages();
bool isTemperatureOk(float temperature);
bool isPulseRateOk(float pulseRate);
bool isSpo2Ok(float spo2);
void buffering();
bool isVitalsOk(float temperature, float pulseRate, float spo2);
void displayTemperatureWarning(float temperature, std::wstring &stream, Language lang);
void initializeWarnigMessages();
