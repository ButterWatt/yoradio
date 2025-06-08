#ifndef myoptions_h
#define myoptions_h

#define DSP_MODEL DSP_ILI9341
#define DSP_HSPI true
#define LED_INVERT true
#define TFT_CS 15
#define TFT_DC 2
#define TFT_RST -1
#define LED_BUILTIN 17
#define BRIGHTNESS_PIN 21
#define I2S_INTERNAL true
#define PLAYER_FORCE_MONO true
//#define I2S_DOUT 22
//#define I2S_BCLK 16
//#define I2S_LRC 4
#define TS_MODEL TS_MODEL_XPT2046
#define TS_SPIPINS 25, 39, 32 /* SCK, MISO, MOSI */
#define TS_CS 33
//#define IR_PIN 27
#define LIGHT_SENSOR 34
#define AUTOBACKLIGHT_MAX 1024
#endife actual value can be calculated by the C compiler at compile time
 * as all inputs are literals. MAKE SURE TO ENABLE OPTIMISATION!
 */ 


#ifndef COMPILE_TIME_H_
#define COMPILE_TIME_H_

// extracts 1..4 characters from a string and interprets it as a decimal value
#define CONV_STR2DEC_1(str, i)  (str[i]>'0'?str[i]-'0':0)
#define CONV_STR2DEC_2(str, i)  (CONV_STR2DEC_1(str, i)*10 + str[i+1]-'0')
#define CONV_STR2DEC_3(str, i)  (CONV_STR2DEC_2(str, i)*10 + str[i+2]-'0')
#define CONV_STR2DEC_4(str, i)  (CONV_STR2DEC_3(str, i)*10 + str[i+3]-'0')

// Some definitions for calculation
#define SEC_PER_MIN             60UL
#define SEC_PER_HOUR            3600UL
#define SEC_PER_DAY             86400UL
#define SEC_PER_YEAR            (SEC_PER_DAY*365)
#define UNIX_START_YEAR         1970UL

// Custom "glue logic" to convert the month name to a usable number
#define GET_MONTH(str, i)      (str[i]=='J' && str[i+1]=='a' && str[i+2]=='n' ? 1 :     \
                                str[i]=='F' && str[i+1]=='e' && str[i+2]=='b' ? 2 :     \
                                str[i]=='M' && str[i+1]=='a' && str[i+2]=='r' ? 3 :     \
                                str[i]=='A' && str[i+1]=='p' && str[i+2]=='r' ? 4 :     \
                                str[i]=='M' && str[i+1]=='a' && str[i+2]=='y' ? 5 :     \
                                str[i]=='J' && str[i+1]=='u' && str[i+2]=='n' ? 6 :     \
                                str[i]=='J' && str[i+1]=='u' && str[i+2]=='l' ? 7 :     \
                                str[i]=='A' && str[i+1]=='u' && str[i+2]=='g' ? 8 :     \
                                str[i]=='S' && str[i+1]=='e' && str[i+2]=='p' ? 9 :     \
                                str[i]=='O' && str[i+1]=='c' && str[i+2]=='t' ? 10 :    \
                                str[i]=='N' && str[i+1]=='o' && str[i+2]=='v' ? 11 :    \
                                str[i]=='D' && str[i+1]=='e' && str[i+2]=='c' ? 12 : 0)

#define GET_MONTH2DAYS(month)  ((month == 1 ? 0 : 31 +                      \
                                (month == 2 ? 0 : 28 +                      \
                                (month == 3 ? 0 : 31 +                      \
                                (month == 4 ? 0 : 30 +                      \
                                (month == 5 ? 0 : 31 +                      \
                                (month == 6 ? 0 : 30 +                      \
                                (month == 7 ? 0 : 31 +                      \
                                (month == 8 ? 0 : 31 +                      \
                                (month == 9 ? 0 : 30 +                      \
                                (month == 10 ? 0 : 31 +                     \
                                (month == 11 ? 0 : 30))))))))))))           \


#define GET_LEAP_DAYS           ((__TIME_YEARS__-1968)/4 - (__TIME_MONTH__ <=2 ? 1 : 0))



#define __TIME_SECONDS__        CONV_STR2DEC_2(__TIME__, 6)
#define __TIME_MINUTES__        CONV_STR2DEC_2(__TIME__, 3)
#define __TIME_HOURS__          CONV_STR2DEC_2(__TIME__, 0)
#define __TIME_DAYS__           CONV_STR2DEC_2(__DATE__, 4)
#define __TIME_MONTH__          GET_MONTH(__DATE__, 0)
#define __TIME_YEARS__          CONV_STR2DEC_4(__DATE__, 7)

#define __TIME_UNIX__         ((__TIME_YEARS__-UNIX_START_YEAR)*SEC_PER_YEAR+       \
                                GET_LEAP_DAYS*SEC_PER_DAY+                          \
                                GET_MONTH2DAYS(__TIME_MONTH__)*SEC_PER_DAY+         \
                                __TIME_DAYS__*SEC_PER_DAY-SEC_PER_DAY+              \
                                __TIME_HOURS__*SEC_PER_HOUR+                        \
                                __TIME_MINUTES__*SEC_PER_MIN+                       \
                                __TIME_SECONDS__)

#endif /* COMPILE_TIME_H_ */
