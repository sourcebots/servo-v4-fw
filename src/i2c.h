#pragma once

#include <stdint.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void i2c_init(void);

void i2c_start_message(uint8_t addr);
void i2c_stop_message(void);

void i2c_send_byte(char c);
bool i2c_recv_bytes(uint8_t addr, uint8_t* buf, uint8_t len);

// Set expander into byte/bank mode (IOCON.SEQOP=0, IOCON.BANK=0)
// configure pin directions and pullups
void init_expander(uint8_t addr);
void get_expander_status(uint8_t addr);

#define CURRENT_SENSE_ADDR 0x40
#define I2C_EXPANDER_ADDR 0x21
void init_current_sense(uint8_t addr);
void measure_current_sense(uint8_t addr);

void reset_i2c_watchdog(void);

extern volatile bool i2c_timed_out;
