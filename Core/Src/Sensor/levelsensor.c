/*
 * liquidlevel.c
 *
 *  Created on: Nov 10, 2022
 *      Author: CBT
 */
#include "main.h"
#include "levelsensor.h"


#define LevelSensor1_Port	GPIO_IN6_GPIO_Port
#define LevelSensor1_Pin	GPIO_IN6_Pin

#define LevelSensor2_Port	GPIO_IN7_GPIO_Port
#define LevelSensor2_Pin	GPIO_IN7_Pin

static int DebounceLevel(GPIO_TypeDef *port, uint16_t pin, int index)
{
	static int stable_state[2] = {0};
	static int last_state[2] = {0};
	static uint8_t stable_count[2] = {0};
	const uint8_t threshold = 2;
	int value = (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET) ? 1 : 0;

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

int LevelSensor1Check(){
	return DebounceLevel(LevelSensor1_Port, LevelSensor1_Pin, 0);
}

int LevelSensor2Check(){
	return DebounceLevel(LevelSensor2_Port, LevelSensor2_Pin, 1);
}
