#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;
/// @brief displayWarning function to display warning message
void buffering() {
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
bool isVitalsOk(float temperature, float pulseRate, float spo2) {
  return (isTemperatureOk(temperature) && isPulseRateOk(pulseRate) && isSpo2Ok(spo2));
}
/// @brief to check if the value is not in range
bool isNotInRange(float value, float lower, float upper) {
  if (upper == 0)
    return value < lower;
  else
    return value < lower || value > upper;
}
/// @brief to check if the temperature is in range
/// @param temperature
/// @return true if temperature is in range, false otherwise
bool isTemperatureOk(float temperature) {
  if (isNotInRange(temperature, 95, 102)) {
    cout << "Temperature is critical!\n";
    buffering();
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
bool isPulseRateOk(float pulseRate) {
  if (isNotInRange(pulseRate,60,100)) {
    cout << "Pulse Rate is out of range!\n";
    buffering();
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
bool isSpo2Ok(float spo2){
  if (isNotInRange(spo2,90,0)) {
    cout << "Oxygen Saturation out of range!\n";
    buffering();
    return false;
  }
  return true;
}
