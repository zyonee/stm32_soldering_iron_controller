/*
 * settings.h
 *
 *  Created on: Jan 12, 2021
 *      Author: David    Original work by Jose Barros (PTDreamer), 2017
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "main.h"
#include "pid.h"
#include "board.h"

#define ProfileSize       3                                         // Number of profiles
#define TipSize           20                                        // Number of tips for each profile
#define TipCharSize       5                                         // String size for each tip name (Including null terminator)
#define _BLANK_TIP        "    "

#ifndef PROFILE_VALUES

#define T12_Cal250        1190                                      // Default values to be used in the calibration if not adjusted
#define T12_Cal350        2021                                      // TODO: Move these values to the board profile, so each board can have a closer default calibration
#define T12_Cal450        2265                                      // But we don't have calibration data from users!

#define T12_BL_Cal250     1343
#define T12_BL_Cal400     2591
#define T12_ILS_Cal250    1227
#define T12_ILS_Cal400    2782
#define T12_BC1_Cal250    1244
#define T12_BC1_Cal400    2663
#define T12_BC2_Cal250    1198
#define T12_BC2_Cal400    2689
#define T12_BC3_Cal250    1160
#define T12_BC3_Cal400    2522
#define T12_D12_Cal250    1194
#define T12_D12_Cal400    2503
#define T12_D16_Cal250    1156
#define T12_D16_Cal400    2472
#define T12_JO2_Cal250    1197
#define T12_JO2_Cal400    2504
#define T12_K_Cal250      1236
#define T12_K_Cal400      2646
#define T12_KU_Cal250     1173
#define T12_KU_Cal400     2730

#define C210_Cal250       300
#define C210_Cal350       400
#define C210_Cal450       500

#define C245_Cal250       900
#define C245_Cal350       1000
#define C245_Cal450       1100

#endif

#define LANGUAGE_COUNT    4
//#define SWSTRING        "SW: v1.10"                               // For releases
#define SWSTRING          "SW: 21-09-23"                            // For git
#define SETTINGS_VERSION  13                                        // Change this if you change the struct below to prevent people getting out of sync
#define StoreSize         2                                         // In KB
#define FLASH_ADDR        (0x8000000 + ((FLASH_SZ-StoreSize)*1024)) // Last 2KB flash (Minimum erase size, page size=2KB)

enum{
  mode_shake              = 0,
  mode_stand              = 1,

  wake_off                = 0,
  wake_standby            = 1,
  wake_sleep              = 2,
  wake_all                = 3,

  wakeInput               = 0,
  wakeButton              = 1,

  no_update               = 0,
  needs_update            = 1,

  runaway_ok              = 0,
  runaway_25              = 1,
  runaway_50              = 2,
  runaway_75              = 3,
  runaway_100             = 4,
  runaway_500             = 5,

  runaway_triggered       = 1,

  disable                 = 0,
  enable                  = 1,

  old_reading             = 0,
  new_reading             = 1,

  read_average            = 0,
  read_unfiltered         = 1,

  encoder_normal          = 0,
  encoder_reverse         = 1,

  mode_Celsius            = 0,
  mode_Farenheit          = 1,

  mode_sleep              = 0,
  mode_standby            = 1,
  mode_run                = 2,
  mode_boost              = 3,

  initialized             = 0,

  profile_T12             = 0,
  profile_C245            = 1,
  profile_C210            = 2,
  profile_None            = 0xff,

  save_Settings           = 1,
  reset_Profiles          = 0x80,
  reset_Profile           = 0x81,
  reset_Settings          = 0x82,
  reset_All               = 0x83,

  keepProfiles            = 1,
  wipeProfiles            = 0x80,

  output_PWM,
  output_Low,
  output_High,

  lang_english             = 0,
  lang_russian             = 1,
  lang_swedish             = 2,
  lang_german              = 3,

  dim_off                  = 0,
  dim_sleep                = 1,
  dim_always               = 2,

  error_sleep              = 0,
  error_run                = 1,
  error_resume             = 2,

};


typedef struct{
  int8_t        coefficient;          // Filter normally applied
  int8_t        counter;              // Counter for threshold limit
  int8_t        min;                  // Minimum filtering when decreasing
  int8_t        step;                 // Start decreasing the filter coefficient, assume it's a fast temperature change, so provide faster response
  int8_t        count_limit;          // Count the spikes, if exceeding this limit, start reducing the filter coefficient.
  uint16_t      threshold;            // Base noise limit, if diff exceeds this limit, trigger threshold limit and start decreasing filtering
  uint16_t      reset_threshold;      // Threshold for completely resetting the filter
}filter_t;

typedef struct{
  uint16_t      calADC_At_250;
  uint16_t      calADC_At_400;
  char          name[TipCharSize];
  pid_values_t  PID;
}tipData_t;

typedef struct{
  uint8_t       NotInitialized;
  uint8_t       ID;
  uint8_t       impedance;
  uint8_t       tempUnit;
  uint8_t       currentNumberOfTips;
  uint8_t       currentTip;
  uint8_t       pwmMul;
  uint8_t       errorResumeMode;
  filter_t      tipFilter;
  uint16_t      standbyTemperature;
  uint16_t      UserSetTemperature;
  uint16_t      MaxSetTemperature;
  uint16_t      MinSetTemperature;
  uint16_t      boostTemperature;
  uint16_t      readPeriod;
  uint16_t      readDelay;
  uint16_t      noIronValue;
  uint16_t      power;
  uint16_t      calADC_At_0;
  uint16_t      Cal250_default;
  uint16_t      Cal400_default;
  tipData_t     tip[TipSize];
  uint32_t      errorTimeout;
  uint32_t      boostTimeout;
  uint32_t      sleepTimeout;
  uint32_t      standbyTimeout;
}profile_t;

typedef struct{
  uint8_t       NotInitialized;                                     // Always 1 if flash is erased
  uint8_t       language;
  uint8_t       contrast;
  uint8_t       OledOffset;
  uint8_t       dim_mode;
  uint8_t       dim_inSleep;
  uint8_t       currentProfile;
  uint8_t       saveSettingsDelay;
  uint8_t       initMode;
  uint8_t       tempStep;
  uint8_t       tempBigStep;
  uint8_t       tempUnit;
  uint8_t       activeDetection;
  uint8_t       buzzerMode;
  uint8_t       buttonWakeMode;                                     // 0=Nothing, 1= standby, 2= sleep,  3= both
  uint8_t       shakeWakeMode;
  uint8_t       shakeFiltering;
  uint8_t       WakeInputMode;
  uint8_t       StandMode;
  uint8_t       Pullup;
  uint8_t       NTC_detect;
  uint8_t       EncoderMode;
  uint8_t       lvp;
  uint8_t       debugEnabled;
  uint16_t      guiUpdateDelay;
  uint16_t      NTC_Beta;
  uint16_t      Pull_res;
  uint16_t      enableNTC;
  uint16_t      NTC_res;
  uint16_t      NTC_detect_high_res;
  uint16_t      NTC_detect_low_res;
  uint16_t      NTC_detect_high_res_beta;
  uint16_t      NTC_detect_low_res_beta;
  uint32_t      dim_Timeout;
  uint32_t      version;                                            // Used to track if a reset is needed on firmware upgrade
}settings_t;

typedef __attribute__((aligned(4)))  struct{
  settings_t    settings;
  uint32_t      settingsChecksum;
  profile_t     Profile;
  uint32_t      ProfileChecksum;
  uint8_t       save_Flag;
  uint8_t       setupMode;
  uint8_t       isSaving;
}systemSettings_t;

typedef __attribute__((aligned(4)))  struct{
  profile_t     Profile[ProfileSize];
  uint32_t      ProfileChecksum[ProfileSize];
  settings_t    settings;
  uint32_t      settingsChecksum;
}flashSettings_t;

extern systemSettings_t systemSettings;
extern flashSettings_t* flashSettings;

void Oled_error_init(void);
void checkSettings(void);
void saveSettingsFromMenu(uint8_t mode);
void saveSettings(uint8_t mode);
void restoreSettings();
uint32_t ChecksumSettings(settings_t* settings);
uint32_t ChecksumProfile(profile_t* profile);
void resetSystemSettings(void);
void resetCurrentProfile(void);
void storeTipData(uint8_t tip);
void loadProfile(uint8_t tip);

#endif /* SETTINGS_H_ */
