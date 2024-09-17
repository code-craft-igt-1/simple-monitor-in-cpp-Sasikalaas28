#include "./monitor.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <locale>
#include <codecvt>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

std::map<std::string, std::vector<float>> vitalLimits = {
    {"HYPO_THERMIA", {0, 95}},
    {"NEAR_HYPO", {95, 96.53}},
    {"NORMAL", {96.54, 100.47}},
    {"NEAR_HYPER", {100.48, 102}},
    {"HYPER_THERMIA", {102, 102}}
};
std::map<std::string, std::map<Language, std::wstring>> warningMessages;
void initializeWarnigMessages() {
    // Set console output to UTF-8
    system("chcp 65001");
    // Print the wide string
    std::wcout.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    std::map<Language, std::wstring> messages;
    messages.insert({ Language::TAMIL, L"தாழ்வெப்பநிலை"});
    messages.insert({ Language::GREEK, L"υποθερμία"});
    warningMessages.insert({"HYPO_THERMIA", messages});
    messages.clear(); 
    messages.insert({ Language::TAMIL, L"ஹைப்போ அருகில்"});
    messages.insert({ Language::GREEK, L"κοντά σε υπο"});
    warningMessages.insert({"NEAR_HYPO", messages});
    messages.clear();
    messages.insert({ Language::TAMIL, L"சாதாரண"});
    messages.insert({ Language::GREEK, L"κανονικός"});
    warningMessages.insert({"NORMAL", messages});
    messages.clear();
    messages.insert({ Language::TAMIL, L"மிக அருகில்"});
    messages.insert({ Language::GREEK, L"κοντά σε υπερ"});
    warningMessages.insert({"NEAR_HYPER", messages});
    messages.clear();
    messages.insert({ Language::TAMIL, L"அதிவெப்பநிலை"});
    messages.insert({ Language::GREEK, L"υπερθερμία"});
    warningMessages.insert({"HYPER_THERMIA", messages});
}
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
  initializeWarnigMessages();
  return (isTemperatureOk(temperature) && isPulseRateOk(pulseRate) && isSpo2Ok(spo2));
}

bool isItInRange(float value, float lower, float upper) {
    if(value > 102)
        return false;
    else
        return (value >= lower && value <= upper);
}

void displayMessage(std::map<std::string, std::vector<float>>::iterator warning, std::wstring& stream, Language lang) {
    if(warning == vitalLimits.end())
      {
        --warning;
      }
    std::wstring s(warningMessages[warning->first][lang]);
    stream += s;
    std::wcout << stream << std::endl;
}
void displayTemperatureWarning(float temperature, std::wstring& stream, Language lang) {
      std::map<std::string, std::vector<float>>::iterator itr;
      for (itr = vitalLimits.begin(); itr != vitalLimits.end(); ++itr) {
          if (isItInRange(temperature, itr->second[0], itr->second[1])) {
              break;
          }
      }
      
      stream = stream + L"Temperature is ";
      displayMessage(itr, stream, lang);
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
  bool isTempOk = false;
  if (isNotInRange(temperature, 95, 102)) {
    cout << "Temperature is critical!\n";
    buffering();
  } else {
      isTempOk = true;
  }
  std::wstring stream = L"";
  displayTemperatureWarning(temperature, stream, Language::TAMIL);
  displayTemperatureWarning(temperature, stream, Language::GREEK);
  return isTempOk;
}
/**
 * @brief Checks if the pulse rate is within the acceptable range.
 * 
 * @param pulseRate The pulse rate value to be checked.
 * @return True if the pulse rate is within the acceptable range, false otherwise.
 */
bool isPulseRateOk(float pulseRate) {
  if (isNotInRange(pulseRate, 60, 100)) {
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
bool isSpo2Ok(float spo2) {
  if (isNotInRange(spo2, 90, 0)) {
    cout << "Oxygen Saturation out of range!\n";
    buffering();
    return false;
  }
  return true;
}
