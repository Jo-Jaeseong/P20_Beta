/*
 * lcd.c
 *
 *  Created on: Oct 25, 2022
 *      Author: CBT
 */
#include"main.h"
#include"sensor.h"
#include <string.h>
#include <stdlib.h>

/*
#define RS485DE_Port	USART6_DE_GPIO_Port
#define RS485DE_Pin		USART6_DE_Pin
*/

extern UART_HandleTypeDef huart6;

unsigned char   TX_vacuum[8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A};	// 요청
//unsigned char   TX_vacuum[8] = {0x01, 0x03, 0x00, 0x01, 0x00, 0x01, 0xD5, 0xCA};
//unsigned char   TX_vacuum[8] = {0x01, 0x03, 0x00, 0x0A, 0x00, 0x02, 0xE4, 0x09};	//Mpa 요청
//세팅
//01 06 00 09 00 06 D9 CA Pa
//01 06 00 09 00 03 19 C9 Kpa
//01 06 00 09 00 00 59 C8 Mpa
//01 06 00 09 00 01 98 08 Bar
//unsigned char   TX_vacuum1[8] = {0x01, 0x06, 0x00, 0x09, 0x00, 0x06, 0xD9, 0xCA};	//pa
unsigned char   TX_vacuum1[8] = {0x01, 0x06, 0x00, 0x09, 0x00, 0x03, 0x19, 0xC9};	//Kpa
//unsigned char   TX_vacuum1[8] = {0x01, 0x06, 0x00, 0x09, 0x00, 0x00, 0x59, 0xC8};	//Mpa
//unsigned char   TX_vacuum1[8] = {0x01, 0x06, 0x00, 0x09, 0x00, 0x01, 0x98, 0x08};	//Bar
unsigned char	RX_vacuum[20]={};
int testpress=0;
static int last_valid_testpress = 0;

static uint16_t Modbus_CRC16(const uint8_t *buffer, uint16_t length)
{
	uint16_t crc = 0xFFFF;

	for (uint16_t i = 0; i < length; i++) {
		crc ^= buffer[i];
		for (uint8_t j = 0; j < 8; j++) {
			if (crc & 0x0001) {
				crc = (crc >> 1) ^ 0xA001;
			} else {
				crc >>= 1;
			}
		}
	}
	return crc;
}

//int Pressure=760;
float Pressure=760;
int CalibrationVacuum;
int DoorOpenPressure=0;
int PreesureCondition[3];



void Read_Vacuumsensor(){
	HAL_StatusTypeDef rx_status;
	uint16_t rx_crc;
	uint16_t calc_crc;

	RS485_TX_ENABLE();
	HAL_UART_Transmit(&huart6, TX_vacuum, 8, 10);
	//HAL_Delay(10);
	RS485_TX_DISABLE();

	memset(RX_vacuum, 0, 7);
	rx_status = HAL_UART_Receive(&huart6, RX_vacuum, 7, 20);
	if (rx_status != HAL_OK) {
		return;
	}

	calc_crc = Modbus_CRC16(RX_vacuum, 5);
	rx_crc = (uint16_t)RX_vacuum[5] | ((uint16_t)RX_vacuum[6] << 8);
	if (calc_crc != rx_crc || RX_vacuum[0] != TX_vacuum[0] || RX_vacuum[1] != 0x03 || RX_vacuum[2] != 0x02) {
		return;
	}

	testpress=(RX_vacuum[3]<<8)|(RX_vacuum[4]);
	last_valid_testpress = testpress;
	if (last_valid_testpress > 0) {
		testpress = last_valid_testpress;
	}

	//---------------------------------

	//절대값 센서

	if(testpress==0){
		testpress=10000;
	}
	Pressure=testpress*760/10132.5-10+CalibrationVacuum;


	//---------------------------------
/*
	//상대값 센서
	if(testpress==0){
		Pressure=760;
	}
	else{
		Pressure=(testpress-55536)*0.075-10+CalibrationVacuum;
	}
	if(Pressure>=760){
		Pressure=760;
	}
*/
	//---------------------------------
}


void Init_Vacuumsensor(){
/*
	RS485_TX_ENABLE();
	HAL_UART_Transmit(&huart6, TX_vacuum1, 8, 10);
	RS485_TX_DISABLE();
	HAL_UART_Receive_IT(&huart6, RX_vacuum, 8);
*/
}


void RS485_TX_ENABLE(){
	HAL_GPIO_WritePin(RS485DE_GPIO_Port, RS485DE_Pin, GPIO_PIN_SET);
}

void RS485_TX_DISABLE(){
	HAL_GPIO_WritePin(RS485DE_GPIO_Port, RS485DE_Pin, GPIO_PIN_RESET);
}
