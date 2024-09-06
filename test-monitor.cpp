#include "./monitor.h"

#include "gtest/gtest.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_FALSE(isVitalsOk(99, 102, 70));
  ASSERT_TRUE(isVitalsOk(98.1, 70, 98));
}

TEST(Monitor, OkWhenAllVitalsAreInRange) {
  ASSERT_TRUE(isVitalsOk(100, 99, 91));
  ASSERT_TRUE(isVitalsOk(98.6, 90, 95));
  ASSERT_TRUE(isVitalsOk(97.5, 80, 100));
}

TEST(Monitor, NotOkWhenTemperatureIsOutOfRange) {
  ASSERT_FALSE(isVitalsOk(95, 100, 80));
  ASSERT_FALSE(isVitalsOk(105, 100, 80));
}

TEST(Monitor, NotOkWhenPulseRateIsOutOfRange) {
  ASSERT_FALSE(isVitalsOk(100, 60, 80));
  ASSERT_FALSE(isVitalsOk(100, 120, 80));
}

TEST(Monitor, NotOkWhenBloodPressureIsOutOfRange) {
  ASSERT_FALSE(isVitalsOk(100, 100, 60));
  ASSERT_FALSE(isVitalsOk(100, 100, 55));
}

TEST(Monitor, NotOkWhenHeartRateIsBelowRange) {
  ASSERT_FALSE(isVitalsOk(95, 100, 80));
  ASSERT_FALSE(isVitalsOk(97.5, 101, 95));
}

TEST(Monitor, NotOkWhenHeartRateIsAboveRange) {
  ASSERT_FALSE(isVitalsOk(105, 100, 80));
  ASSERT_FALSE(isVitalsOk(102.5, 90, 95));
}

TEST(Monitor, NotOkWhenOxygenLevelIsBelowRange) {
  ASSERT_FALSE(isVitalsOk(100, 95, 80));
  ASSERT_FALSE(isVitalsOk(98.6, 85, 89));
}

TEST(Monitor, NotOkWhenOxygenLevelIsAboveRange) {
  ASSERT_FALSE(isVitalsOk(100, 105, 80));
  ASSERT_FALSE(isVitalsOk(98.6, 100, 69));
}

TEST(Monitor, NotOkWhenTemperatureIsBelowRange) {
  ASSERT_FALSE(isVitalsOk(100, 100, 75));
  ASSERT_FALSE(isVitalsOk(92.8, 90, 97.5));
}

TEST(Monitor, NotOkWhenTemperatureIsAboveRange) {
  ASSERT_FALSE(isVitalsOk(100, 100, 85));
  ASSERT_FALSE(isVitalsOk(103, 90, 100));
}
