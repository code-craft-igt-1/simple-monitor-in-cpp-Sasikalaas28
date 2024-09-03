#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;
/// @brief displayWarning function to display warning message
void displayWarning() {
  for (int i = 0; i < 6; i++) {
    cout << "\r* " << flush;
    sleep_for(seconds(1));
    cout << "\r *" << flush;
    sleep_for(seconds(1));
  }
}
/// @brief to check if the vitals are ok
/// @param temperature
/// @param pulseRate
/// @param spo2
/// @return 1 if vitals are ok, 0 otherwise
int vitalsOk(float temperature, float pulseRate, float spo2) {
  int result = 1;
  (!checkTemperature(temperature)) ? result = 0 : ((!checkPulseRate(pulseRate)) ? result = 0 : ((!checkSpo2(spo2)) ? result = 0 : (result = 1)));
  return result;
}
/// @brief to check if the temperature is in range
/// @param temperature
/// @return true if temperature is in range, false otherwise
bool checkTemperature(float temperature) {
  if (temperature > 102 || temperature < 95) {
    cout << "Temperature is critical!\n";
    displayWarning();
    return false;
  }
  return true;
}
/**
 * @brief Checks if the pulse rate is within the acceptable range.
 * 
 * @param pulseRate The pulse rate value to be checked.
 * @return True if the pulse rate is within the acceptable range, false otherwise.
 */
bool checkPulseRate(float pulseRate) {
  if (pulseRate < 60 || pulseRate > 100) {
    cout << "Pulse Rate is out of range!\n";
    displayWarning();
    return false;
  }
  return true;
}
/**
 * @brief Checks if the oxygen saturation (spo2) is within the acceptable range.
 * 
 * @param spo2 The spo2 value to be checked.
 * @return True if the spo2 is within the acceptable range, false otherwise.
 */
bool checkSpo2(float spo2) {
  if (spo2 < 90) {
    cout << "Oxygen Saturation out of range!\n";
    displayWarning();
    return false;
  }
  return true;
}
