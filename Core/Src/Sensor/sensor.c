/*
 * sensor.c
 *
 *  Created on: Mar 19, 2024
 *      Author: CBT_DEV
 */

#include "main.h"

#include "doorsensor.h"
#include "levelsensor.h"
#include "temperature.h"
#include "valvesensor.h"
#include "vacuum_sensor2.h"

#include "sensor.h"

#define Limit1_Port		GPIO_IN1_GPIO_Port
#define Limit1_Pin		GPIO_IN1_Pin

#define Limit2_Port		GPIO_IN2_GPIO_Port
#define Limit2_Pin		GPIO_IN2_Pin

#define Limit3_Port		GPIO_IN3_GPIO_Port
#define Limit3_Pin		GPIO_IN3_Pin

#define Limit4_Port		GPIO_IN4_GPIO_Port
#define Limit4_Pin		GPIO_IN4_Pin


static int DebounceInput(GPIO_TypeDef *port, uint16_t pin, int active_low, int index)
{
	static int stable_state[4] = {0};
	static int last_state[4] = {0};
	static uint8_t stable_count[4] = {0};
	const uint8_t threshold = 2;
	int raw = (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET) ? 1 : 0;
	int value = active_low ? !raw : raw;

	if (value == last_state[index]) {
		if (stable_count[index] < threshold) {
			stable_count[index]++;
		}
	} else {
		stable_count[index] = 0;
		last_state[index] = value;
	}

	if (stable_count[index] >= threshold) {
		stable_state[index] = value;
	}

	return stable_state[index];
}

int Limit1(){
	return DebounceInput(Limit1_Port, Limit1_Pin, 1, 0);
}

int Limit2(){
	return DebounceInput(Limit2_Port, Limit2_Pin, 1, 1);
}

int Limit3(){
	return DebounceInput(Limit3_Port, Limit3_Pin, 1, 2);
}

int Limit4(){
	return DebounceInput(Limit4_Port, Limit4_Pin, 1, 3);
}
