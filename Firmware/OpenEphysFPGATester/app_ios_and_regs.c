#include <avr/io.h>
#include "hwbp_core_types.h"
#include "app_ios_and_regs.h"

/************************************************************************/
/* Configure and initialize IOs                                         */
/************************************************************************/
void init_ios(void)
{	/* Configure input pins */
	io_pin2in(&PORTD, 7, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // BUTTON
	io_pin2in(&PORTA, 1, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);        // TEST0
	io_pin2in(&PORTA, 2, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);        // TEST1
	io_pin2in(&PORTA, 3, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);        // TEST2
	io_pin2in(&PORTA, 4, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);        // TEST3
	io_pin2in(&PORTA, 5, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);        // TEST4
	io_pin2in(&PORTA, 6, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);        // TEST5
	io_pin2in(&PORTA, 7, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);        // TEST6
	io_pin2in(&PORTB, 1, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);        // TEST7

	/* Configure input interrupts */
	io_set_int(&PORTD, INT_LEVEL_LOW, 0, (1<<7), false);                 // BUTTON

	/* Configure output pins */
	io_pin2out(&PORTD, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_D2
	io_pin2out(&PORTD, 4, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_D3
	io_pin2out(&PORTC, 4, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // ADD0
	io_pin2out(&PORTC, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // ADD1
	io_pin2out(&PORTC, 6, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // ADD2
	io_pin2out(&PORTC, 7, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // ADD3
	io_pin2out(&PORTC, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // TEST_CLK

	/* Initialize output pins */
	clr_LED_D2;
	clr_LED_D3;
	clr_ADD0;
	clr_ADD1;
	clr_ADD2;
	clr_ADD3;
	clr_TEST_CLK;
}

/************************************************************************/
/* Registers' stuff                                                     */
/************************************************************************/
AppRegs app_regs;

uint8_t app_regs_type[] = {
	TYPE_U8,
	TYPE_U8,
	TYPE_FLOAT,
	TYPE_FLOAT,
	TYPE_FLOAT,
	TYPE_FLOAT,
	TYPE_FLOAT,
	TYPE_FLOAT,
	TYPE_FLOAT,
	TYPE_FLOAT,
	TYPE_FLOAT,
	TYPE_FLOAT,
	TYPE_FLOAT,
	TYPE_FLOAT
};

uint16_t app_regs_n_elements[] = {
	1,
	4,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1
};

uint8_t *app_regs_pointer[] = {
	(uint8_t*)(&app_regs.REG_TEST_STARTED),
	(uint8_t*)(app_regs.REG_FAIL_EVENT),
	(uint8_t*)(&app_regs.REG_J1_2V5_7),
	(uint8_t*)(&app_regs.REG_J1_3V3_9),
	(uint8_t*)(&app_regs.REG_J1_3V3_11),
	(uint8_t*)(&app_regs.REG_J1_3V3_13),
	(uint8_t*)(&app_regs.REG_J1_5V_1),
	(uint8_t*)(&app_regs.REG_J1_5V_3),
	(uint8_t*)(&app_regs.REG_J1_5V_5),
	(uint8_t*)(&app_regs.REG_J1_RAMVDD_4),
	(uint8_t*)(&app_regs.REG_J1_RAMVDD_6),
	(uint8_t*)(&app_regs.REG_J2_3V3_2),
	(uint8_t*)(&app_regs.REG_J2_3V3_4),
	(uint8_t*)(&app_regs.REG_J2_3V3_6)
};