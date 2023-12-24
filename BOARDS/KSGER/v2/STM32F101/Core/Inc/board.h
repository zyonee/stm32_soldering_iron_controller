
#ifndef SETUP_H_
#define SETUP_H_
/*
 * Setup.h file
*/

/*
    BOARD PROFILE FOR KSGER v2.x
*/

#define HWSTRING "HW: KSGER v2.x"

/********************************
 *       Display Settings    *
 ********************************/
//#define DISPLAY_SPI                                         // SPI display
#define DISPLAY_I2C                                           // I2C display
//#define I2C_TRY_HW                                          // Try I2C HW first, use I2C SW if not detected
#define DISPLAY_ADDRESS       (0x3c<<1)                       // Only used for I2C
//#define DISPLAY_DEVICE      hi2c2                           // SPI / I2C handler if used. Enables HW mode, otherwise SW mode is used (DISPLAY_DEVICE must be defined)
#define FILL_DMA              hdma_memtomem_dma1_channel2     // DMA mem2mem for filling
//#define USE_RST                                             // Reset pin is used
//#define USE_DC                                              // DC pin is used
//#define USE_CS                                              // CS pin is used
#define DISPLAY_START_COLUMN  2                               // Display column offset
#define DISPLAY_START_LINE    0                               // Display line offset

/********************************
 *       PWM Settings        *
 ********************************/
//#define PWM_TIMER_HALFCLOCK                                 // Timer runs at FCY/2
//#define READ_TIMER_HALFCLOCK                                // Timer runs at FCY/2
#define READ_TIMER          htim4                             // Timer for the dead time
#define PWM_TIMER           htim3                             // PWM Timer
#define PWM_CHANNEL         TIM_CHANNEL_3                     // PWM Timer Channel
//#define PWM_CHxN                                            // Using CHxN Output type
#define PWM_CHx                                               // Using CHx Output type
//#define DEBUG_PWM                                           // To enable a test signal and some printing through SWO (Create a output GPIO called PWM_DBG)


/********************************
 *       ADC Settings        *
 ********************************/
#define ADC_DEVICE          hadc1                             // ADC device
#define ADC_BFSIZ           (16+2)                            // ADC DMA buffer size Buffer[ADC_BFSIZ][Adc_Buffer_Elements](+2 to compensate min/max value discard in filtering)

// Order for secondary measurements, ADC channels not requiring sampling in the PWM low period. Order as ADC rank order (usually ch0-ch18)
#define ADC_1st             TIP                               // ADC 1st used channel (CH2)
#define ADC_2nd             NTC                               // ADC 2nd used channel (CH7)
#define ADC_3rd             VIN                               // ADC 3nd used channel (CH9)
#define ADC_4th             INT_TMP                           // ADC 4th used channel (CH16)
//#define ADC_5th           VREF                              // ADC 5th used channel
#define ADC_Num             4                                 // Number of channels

// Channel assignment
#define ADC_CH_1ST          ADC_CHANNEL_2                     // CH2 = IRON TIP
#define ADC_CH_2ND          ADC_CHANNEL_7                     // CH7 = NTC
#define ADC_CH_3RD          ADC_CHANNEL_9                     // CH9 = VIN
#define ADC_CH_4TH          ADC_CHANNEL_TEMPSENSOR            // CH16 = INT TEMP
//#define ADC_CH_5TH        ADC_CHANNEL__                     // CH? = ?

// To enable specific functions in code
//#define USE_VREF
#define USE_VIN
#define USE_NTC
#define ENABLE_INT_TEMP                                       // Enable internal temperature if NTC fails or disabled in options (Depends on USE_NTC)


/********************************
 *       TIP calibration    *
 ********************************/
#define PROFILE_VALUES                                        // Enable profile values

#ifdef PROFILE_VALUES
#define T12_Cal250        1900
#define T12_Cal400        2800

#define C210_Cal250       800
#define C210_Cal400       1500

#define C245_Cal250       1800
#define C245_Cal400       2800
#endif


/********************************
 *       Buzzer        *
 ********************************/
#define BUZZER_OFF          HAL_GPIO_WritePin(BUZ0_GPIO_Port, BUZ0_Pin, GPIO_PIN_SET);  \
                            HAL_GPIO_WritePin(BUZ1_GPIO_Port, BUZ1_Pin, GPIO_PIN_SET);  \
                            HAL_GPIO_WritePin(BUZ2_GPIO_Port, BUZ2_Pin, GPIO_PIN_SET);

#define BUZZER_ON           HAL_GPIO_WritePin(BUZ0_GPIO_Port, BUZ0_Pin, GPIO_PIN_RESET);  \
                            HAL_GPIO_WritePin(BUZ1_GPIO_Port, BUZ1_Pin, GPIO_PIN_RESET);  \
                            HAL_GPIO_WritePin(BUZ2_GPIO_Port, BUZ2_Pin, GPIO_PIN_RESET);

#define BUZZER_TOGGLE       HAL_GPIO_TogglePin(BUZ0_GPIO_Port, BUZ0_Pin); \
                            HAL_GPIO_TogglePin(BUZ1_GPIO_Port, BUZ1_Pin); \
                            HAL_GPIO_TogglePin(BUZ2_GPIO_Port, BUZ2_Pin);

/********************************
 *       Addons/Extras    *
 ********************************/
//#define ENABLE_ADDON_FUME_EXTRACTOR      // addon for controlling a fume extractor, must define a gpio output pin "EXTRACTOR" to use
#define ENABLE_ADDON_SWITCH_OFF_REMINDER // addon to beep periodically in sleep mode


/********************************
 *       Misc    *
 ********************************/
//#define NOSAVESETTINGS                                      // Don't use flash to save or load settings. Always use defaults (for debugging purposes)
//#define SWO_PRINT                                           // To enable printing through SWO


#ifdef USE_NTC

#define NTC_RES       10000
#define NTC_BETA      3450
#define PULL_RES      4700
#define PULLUP

#endif

// To stop peripherals when debugging
#define DebugOpts()         __HAL_DBGMCU_FREEZE_IWDG(); \
                            __HAL_DBGMCU_FREEZE_TIM3(); \
                            __HAL_DBGMCU_FREEZE_TIM4()

#endif
