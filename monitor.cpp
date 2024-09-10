#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <locale>
#include <codecvt>
#include <windows.h>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;
enum Language {
    TAMIL,
    GREEK
//  DUTCH supported in future
};
std::vector<std::wstring> Tamil;
std::vector<std::wstring> Greek;
std::map<Language, std::vector<std::wstring>> warningMessages;
std::map<std::string, int> MessageIndex;
void initializeWarnigMessages() {
    Tamil.push_back(L"தாழ்வெப்பநிலை");
    Tamil.push_back(L"ஹைப்போ அருகில்");
    Tamil.push_back(L"சாதாரண");
    Tamil.push_back(L"மிக அருகில்");
    Tamil.push_back(L"அதிவெப்பநிலை");
    warningMessages.insert({ Language::TAMIL, Tamil });
    Greek.push_back(L"υποθερμία");
    Greek.push_back(L"κοντά σε υπο");
    Greek.push_back(L"κανονικός");
    Greek.push_back(L"κοντά σε υπερ");
    Greek.push_back(L"υπερθερμία");
    warningMessages.insert({ Language::GREEK, Greek });
    MessageIndex.insert({ "HYPO_THERMIA", 0 });
    MessageIndex.insert({ "NEAR_HYPO", 1 });
    MessageIndex.insert({ "NORMAL", 2 });
    MessageIndex.insert({ "NEAR_HYPER", 3 });
    MessageIndex.insert({ "HYPER_THERMIA", 4 });
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
     return (value >= lower && value <= upper);
}

void displayMessage(int MsgInd, Language lang) {
    // Set console output to UTF-8
    SetConsoleOutputCP(CP_UTF8);
    if (MsgInd > 4) {
        MsgInd = 4;
    }
    // Print the wide string
    std::wcout.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
    std::wcout << warningMessages[lang][MsgInd] << std::endl;
}
void displayTemperatureWarning(float temperature, Language lang) {
     int MsgInd = 0;
     std::map<float, float> temperatureRange = { {0, 95}, {95, 96.53},
                                                {96.54, 100.47}, {100.48, 102}, {102, 102} };
      for (auto itr = temperatureRange.begin(); itr != temperatureRange.end(); ++itr) {
          if (isItInRange(temperature, itr->first, itr->second)) {
              break;
          }
          MsgInd++;
      }
      displayMessage(MsgInd, lang);
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
  displayTemperatureWarning(temperature, Language::TAMIL);
  displayTemperatureWarning(temperature, Language::GREEK);
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
