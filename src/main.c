// SPDX-License-Identifier: MIT
// Copyright 2024 Algovoid

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    pin_t pin_A;
    pin_t pin_B;
    pin_t pin_C;
    pin_t pin_D;

    pin_t pin_E;
    pin_t pin_F;

    pin_t pin_G;
    pin_t pin_H;
    pin_t pin_I;

    pin_t pin_J;
    pin_t pin_K;

    pin_t pin_Y;

} chip_state_t;

uint8_t subGate1;
uint8_t subGate2;
uint8_t subGate3;
uint8_t subGate4;

static void set_logic(chip_state_t *chip) {
  subGate1 = ( pin_read(chip->pin_A) & pin_read(chip->pin_B) & pin_read(chip->pin_C) & pin_read(chip->pin_D) ) ;

  subGate2 = ( pin_read(chip->pin_E) & pin_read(chip->pin_F) );

  subGate3 = ( pin_read(chip->pin_G) & pin_read(chip->pin_H) & pin_read(chip->pin_I) ) ;

  subGate4 = (pin_read(chip->pin_J) & pin_read(chip->pin_K) );

  pin_write(chip->pin_Y, !( subGate1 | subGate2 | subGate3 | subGate4 ) );

}


static void chip_pin_change(void *user_data, pin_t pin, uint32_t value) {
  chip_state_t *chip = (chip_state_t*)user_data;
  set_logic(chip);
  // uncomment to see gates and output states
  /*
  printf("Gate 1 :  %d\n" , subGate1);
  printf("Gate 2 :  %d\n" , subGate2);
  printf("Gate 3 :  %d\n" , subGate3);
  printf("Gate 4 :  %d\n" , subGate4);
  printf("Output State Y :  %u\n" , pin_read(chip->pin_Y)); */
}


void chip_init() {
  printf("Initialize sn54s51 chip!\n");
  chip_state_t *chip = malloc(sizeof(chip_state_t));

  chip->pin_A = pin_init("A", INPUT);
  chip->pin_B = pin_init("B", INPUT);
  chip->pin_C = pin_init("C", INPUT);
  chip->pin_D = pin_init("D", INPUT);

  chip->pin_E = pin_init("E", INPUT);
  chip->pin_F = pin_init("F", INPUT);

  chip->pin_G = pin_init("G", INPUT);
  chip->pin_H = pin_init("H", INPUT);
  chip->pin_I = pin_init("I", INPUT);

  chip->pin_J = pin_init("J", INPUT);
  chip->pin_K = pin_init("K", INPUT);


  chip->pin_Y = pin_init("Y", OUTPUT);

  pin_write(chip->pin_A, LOW);
  pin_write(chip->pin_B, LOW);
  pin_write(chip->pin_C, LOW);
  pin_write(chip->pin_D, LOW);

  pin_write(chip->pin_E, LOW);
  pin_write(chip->pin_F, LOW);

  pin_write(chip->pin_G, LOW);
  pin_write(chip->pin_H, LOW);
  pin_write(chip->pin_I, LOW);

  pin_write(chip->pin_J, LOW);
  pin_write(chip->pin_K, LOW);

  const pin_watch_config_t config = {
    .edge = BOTH,
    .pin_change = chip_pin_change,
    .user_data = chip,
  };

  pin_watch(chip->pin_A, &config);
  pin_watch(chip->pin_B, &config);

  pin_watch(chip->pin_C, &config);
  pin_watch(chip->pin_D, &config);

  pin_watch(chip->pin_E, &config);
  pin_watch(chip->pin_F, &config);

  pin_watch(chip->pin_G, &config);
  pin_watch(chip->pin_H, &config);

  pin_watch(chip->pin_I, &config);

  pin_watch(chip->pin_J, &config);
  pin_watch(chip->pin_K, &config);

  set_logic(chip);
}