#pragma once

#include <stdint.h>
#include <stdbool.h>

#define NUM_SERVOS 12
#define NUM_SERVO_PHASES 3
#define ROUND_UP_DIV(x, y) (uint8_t)(((x) + (y) - 1) / (y))
#define SERVOS_PER_PHASE ROUND_UP_DIV(NUM_SERVOS, NUM_SERVO_PHASES)
#define SERVO_STEPS_PER_PHASE (SERVOS_PER_PHASE * 2)

#if NUM_SERVOS > 12
#error "Board only supports 12 servos"
#endif

#if NUM_SERVOS > 8
// 16 bit transfer takes 95uS
#define US_BETWEEN_EDGES 125
#else
// 8 bit transfer takes 72.5uS
#define US_BETWEEN_EDGES 100
#endif

// in uS
#define MIN_SERVO_PULSE (US_BETWEEN_EDGES * SERVOS_PER_PHASE)
#define MAX_SERVO_PULSE 4000

typedef struct {
    uint8_t idx;
    bool enabled;
    bool rising;
    uint16_t next_steps;  // in timer ticks
} servo_step_t;

void servo_init(void);
void servo_deinit(void);
void servo_set_pos(uint8_t idx, uint16_t pulse_us);
void servo_disable(uint8_t idx);
uint16_t servo_get_pos(uint8_t idx);
void servo_reset(void);

void start_servo_phase(uint8_t phase);

servo_step_t* get_servo_steps(uint8_t phase);
