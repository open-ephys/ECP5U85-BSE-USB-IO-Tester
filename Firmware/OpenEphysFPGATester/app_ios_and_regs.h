#ifndef _APP_IOS_AND_REGS_H_
#define _APP_IOS_AND_REGS_H_
#include "cpu.h"

void init_ios(void);
/************************************************************************/
/* Definition of input pins                                             */
/************************************************************************/
// BUTTON                 Description: Switch
// TEST0                  Description: Test input 0
// TEST1                  Description: Test input 1
// TEST2                  Description: Test input 2
// TEST3                  Description: Test input 3
// TEST4                  Description: Test input 4
// TEST5                  Description: Test input 5
// TEST6                  Description: Test input 6
// TEST7                  Description: Test input 7

#define read_BUTTON read_io(PORTD, 7)           // BUTTON
#define read_TEST0 read_io(PORTA, 1)            // TEST0
#define read_TEST1 read_io(PORTA, 2)            // TEST1
#define read_TEST2 read_io(PORTA, 3)            // TEST2
#define read_TEST3 read_io(PORTA, 4)            // TEST3
#define read_TEST4 read_io(PORTA, 5)            // TEST4
#define read_TEST5 read_io(PORTA, 6)            // TEST5
#define read_TEST6 read_io(PORTA, 7)            // TEST6
#define read_TEST7 read_io(PORTB, 1)            // TEST7

/************************************************************************/
/* Definition of output pins                                            */
/************************************************************************/
// LED_D2                 Description: User LED D2
// LED_D3                 Description: User LED D3
// ADD0                   Description: Multiplexer address 0
// ADD1                   Description: Multiplexer address 1
// ADD2                   Description: Multiplexer address 2
// ADD3                   Description: Multiplexer address 3
// TEST_CLK               Description: Test clock

/* LED_D2 */
#define set_LED_D2 set_io(PORTD, 3)
#define clr_LED_D2 clear_io(PORTD, 3)
#define tgl_LED_D2 toggle_io(PORTD, 3)
#define read_LED_D2 read_io(PORTD, 3)

/* LED_D3 */
#define set_LED_D3 set_io(PORTD, 4)
#define clr_LED_D3 clear_io(PORTD, 4)
#define tgl_LED_D3 toggle_io(PORTD, 4)
#define read_LED_D3 read_io(PORTD, 4)

/* ADD0 */
#define set_ADD0 set_io(PORTC, 4)
#define clr_ADD0 clear_io(PORTC, 4)
#define tgl_ADD0 toggle_io(PORTC, 4)
#define read_ADD0 read_io(PORTC, 4)

/* ADD1 */
#define set_ADD1 set_io(PORTC, 5)
#define clr_ADD1 clear_io(PORTC, 5)
#define tgl_ADD1 toggle_io(PORTC, 5)
#define read_ADD1 read_io(PORTC, 5)

/* ADD2 */
#define set_ADD2 set_io(PORTC, 6)
#define clr_ADD2 clear_io(PORTC, 6)
#define tgl_ADD2 toggle_io(PORTC, 6)
#define read_ADD2 read_io(PORTC, 6)

/* ADD3 */
#define set_ADD3 set_io(PORTC, 7)
#define clr_ADD3 clear_io(PORTC, 7)
#define tgl_ADD3 toggle_io(PORTC, 7)
#define read_ADD3 read_io(PORTC, 7)

/* TEST_CLK */
#define set_TEST_CLK set_io(PORTC, 0)
#define clr_TEST_CLK clear_io(PORTC, 0)
#define tgl_TEST_CLK toggle_io(PORTC, 0)
#define read_TEST_CLK read_io(PORTC, 0)


/************************************************************************/
/* Registers' structure                                                 */
/************************************************************************/
typedef struct
{
	uint8_t REG_TEST_STARTED;
	uint8_t REG_FAIL_EVENT[4];
	float REG_J1_2V5_7;
	float REG_J1_3V3_9;
	float REG_J1_3V3_11;
	float REG_J1_3V3_13;
	float REG_J1_5V_1;
	float REG_J1_5V_3;
	float REG_J1_5V_5;
	float REG_J1_RAMVDD_4;
	float REG_J1_RAMVDD_6;
	float REG_J2_3V3_2;
	float REG_J2_3V3_4;
	float REG_J2_3V3_6;
} AppRegs;

/************************************************************************/
/* Registers' address                                                   */
/************************************************************************/
/* Registers */
#define ADD_REG_TEST_STARTED                32 // U8     This event indicates that the test has started
#define ADD_REG_FAIL_EVENT                  33 // U8     [Address] [Test] [IOState] [NumOfHighs]
#define ADD_REG_J1_2V5_7                    34 // FLOAT  Contains the voltage value present on connector J1 pin 7
#define ADD_REG_J1_3V3_9                    35 // FLOAT  Contains the voltage value present on connector J1 pin 9
#define ADD_REG_J1_3V3_11                   36 // FLOAT  Contains the voltage value present on connector J1 pin 11
#define ADD_REG_J1_3V3_13                   37 // FLOAT  Contains the voltage value present on connector J1 pin 13
#define ADD_REG_J1_5V_1                     38 // FLOAT  Contains the voltage value present on connector J1 pin 1
#define ADD_REG_J1_5V_3                     39 // FLOAT  Contains the voltage value present on connector J1 pin 3
#define ADD_REG_J1_5V_5                     40 // FLOAT  Contains the voltage value present on connector J1 pin 5
#define ADD_REG_J1_RAMVDD_4                 41 // FLOAT  Contains the voltage value present on connector J1 pin 4
#define ADD_REG_J1_RAMVDD_6                 42 // FLOAT  Contains the voltage value present on connector J1 pin 6
#define ADD_REG_J2_3V3_2                    43 // FLOAT  Contains the voltage value present on connector J2 pin 2
#define ADD_REG_J2_3V3_4                    44 // FLOAT  Contains the voltage value present on connector J2 pin 4
#define ADD_REG_J2_3V3_6                    45 // FLOAT  Contains the voltage value present on connector J2 pin 6

/************************************************************************/
/* PWM Generator registers' memory limits                               */
/*                                                                      */
/* DON'T change the APP_REGS_ADD_MIN value !!!                          */
/* DON'T change these names !!!                                         */
/************************************************************************/
/* Memory limits */
#define APP_REGS_ADD_MIN                    0x20
#define APP_REGS_ADD_MAX                    0x2D
#define APP_NBYTES_OF_REG_BANK              53

/************************************************************************/
/* Registers' bits                                                      */
/************************************************************************/

#endif /* _APP_REGS_H_ */