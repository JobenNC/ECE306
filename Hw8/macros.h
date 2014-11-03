//===========================================================================
// File Name : macros.h
//
// Description: Student defined macros
//
// Author: Joseph Jarriel
// Date: Sep 2014
// Compiler: Built with IAR Embedded Workbench (6.10.5)
// Globals: No globals defined in this file
// Functions: None
//===========================================================================

#define ALWAYS                  (1)
#define CNTL_STATE_INDEX        (3) // Control States
#define LCD_LINE_1           (0x80) // Position Cursor at Character 01 of Line 1
#define LCD_LINE_2           (0xC0) // Position Cursor at Character 01 of Line 2
#define LED1                 (0x01) // LED 1
#define LED2                 (0x02) // LED 2
#define LED3                 (0x04) // LED 3
#define LED4                 (0x08) // LED 4
#define LED5                 (0x10) // LED 5
#define LED6                 (0x20) // LED 6
#define LED7                 (0x40) // LED 7
#define LED8                 (0x80) // LED 8

#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2

#define CLEAR_REG            (0x00)
#define DIR_INPUT            (0x00)

#define V_DETECT_R (0x01) //
#define V_DETECT_L (0x02) //
#define IR_LED (0x04) //
#define V_THUMB (0x08) //
#define SPI_CS_LCD (0x10) // LCD Chip Select
#define RESET_LCD (0x20) // GPS Power Check from GPS
#define SPI_SIMO (0x40) // SPI mode - slave in/master out of USCI_B0
#define RS_LCD (0x80) // RS_LCD Command / Data selection
//Slave out not used for LCD, pin used as RS_LCD
#define SOMI_B (0x80) // SPI mode - slave out/master in of USCI_B0

#define CSLOCK                  (0x01) // Any incorrect password locks registers
#define MCLK_FREQ           (8000000L)
#define SMCLK_FREQ          (8000000L)
#define SMCLK_DIV                 (64)

#define USB_TXD (0x01)
#define USB_RXD (0x02)
#define SPI_SCK (0x04)
#define P_2_3   (0x08)
#define P_2_4   (0x10)
#define CPU_TXD (0x20)
#define CPU_RXD (0x40)
#define P_2_7   (0x80)

#define VAR_X (0x01)
#define VAR_Y (0x02)
#define VAR_Z (0x04)
#define LCD_BACKLITE (0x08)
#define R_FORWARD (0x10)
#define R_REVERSE (0x20)
#define L_FORWARD (0x40)
#define L_REVERSE (0x80)

#define GPS_PWR (0x01)
#define GPS_RESET (0x02)
#define GPS_PWRCNTL (0x04)
#define GPS_PWRCHK (0x08)

#define TIME_UP (25)
#define TIME_START (26)
#define OFF (0)
#define ON (1)

#define START (1)

#define RESTART (0)
#define RESET (0)

#define nib1Mask (0x0F)
#define nib2Mask (0xF0)
#define nib3Mask (0xF00)

#define numRange (10)

#define shift4 (4)
#define shift8 (8)

#define char1 (8)
#define char2 (9)
#define char3 (10)
#define char4 (11)

#define numOffset (48)
#define charOffset (55)

#define lcdCountFin (100)
#define bounceCountFin (200)

#define TSEQ_50 (50)
#define TSEQ_100 (100)
#define TSEQ_150 (150)
#define TSEQ_200 (200)
#define TSEQ_250 (250)

#define SLEEP_10 (10)
#define SLEEP_50 (50)
#define SLEEP_75 (75)

#define USLEEP_10_FIN (14)
#define FIVE_MSEC_FIN (1000)

#define FIVE_MSEC_OFFSET (2500)

#define ONE_SEC (200)
#define HALF_SEC (100)
#define TWO_SEC (400)
#define FIFTY_MIL (10)

#define ONE (1)

#define HALF (2)

#define BEFORE_START (-1)

#define SECOND (2)

#define THIRD (3)

#define FOURTH (4)

#define SIXTH (6)
#define SEVENTH (7)
#define EIGHTH (8)
#define TENTH (10)
#define TWELFTH (12)
#define offLine (20)

#define twoLoop (900)

#define seventy (70)

extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
extern volatile unsigned int five_msec_count;
extern volatile int waitCount;
extern volatile unsigned int fMCount;

extern volatile unsigned int starting;

extern volatile unsigned int isDebounce;
extern volatile unsigned int bounceCount;
extern volatile unsigned int switchPress;

extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int ADC_LD;
extern volatile unsigned int ADC_RD;
extern volatile unsigned int chan;

extern volatile unsigned int drive;

extern volatile unsigned int LED_White_LD;
extern volatile unsigned int LED_Black_LD;
extern volatile unsigned int LED_White_RD;
extern volatile unsigned int LED_Black_RD;

extern volatile unsigned int startTimer;
extern volatile unsigned int timerCount;

extern volatile char USB_Char_Tx[8];
extern volatile char USB_Char_Rx[16];

extern volatile int usb_tx_ring_wr;
extern volatile int usb_tx_ring_rd;

extern volatile int usb_rx_ring_wr;
extern volatile int usb_rx_ring_rd;

extern volatile int writeNext;