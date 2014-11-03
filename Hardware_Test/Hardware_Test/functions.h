//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************
// Functions

// Initialization
void Init_Conditions(void);

// Ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(char clock_state);
void Init_Port4(void);
void Init_PortJ(void);

// Clocks
void Init_Clocks(void);

// Timers
void Init_Timers(void);
void Init_Timer0_A(void);
void Init_Timer1_A(void);
void Init_Timer0_B(void);
void Init_Timer1_B(void);
void Init_Timer2_B(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);

// Configure ADC10
void Init_ADC(void);
void ADC_Process(void);

// Serial
void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);
void Transmit_U(void);
void alphabet(void);
void outchar(char character);
void print_CR(void);
void menu(void);
void grab_a_character(void);
int wait_for_character(void);
void increment_usb_rx_ring(void);
void increment_gps_rx_ring(void);
void menu_program(void);
void outhex (unsigned int hexvalue);
void outshorthex (unsigned int hexvalue);

// GPS
void gps_system_init(void);
void gps_meassage_type(void);
void GPS_process(void);
void GPS_process_simple(void);
void GPS_clean_buffer(void);
void GPS_test(void);
void gps_wakeup(void);

// SPI
void Init_SPI_B0(void);
void SPI_B0_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_chipselect_idle(void);
void spi_chipselect_active(void);
void SPI_test(void);

// LCD
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);
void lcd_out(char *s, char line);
void lcd_write(char data, char command);
void lcd_command( char data);
void LCD_test(void);
void LCD_gps_meassage_print(int nema_index);
void Display_Process(void);
void display_ADC (void);

// LEDs
void Init_LEDs(void);
void WHEELS_test(void);
void LED5_SMCLK_switch(char selection);

//void LCD_PRINT(char *d, char line);
//void LCD_COMMAND( char cData);
//void LCD_INIT();
void delay_ms( int duration_time);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);


// Interrupts
void enable_interrupts(void);
__interrupt void Timer1_A0_ISR(void);
__interrupt void TIMER0_A1_ISR(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void TIMER0_B1_ISR(void);
__interrupt void switch_interrupt(void);
__interrupt void USCI_B0_ISR(void);
