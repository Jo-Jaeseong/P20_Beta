/*
 * alarm.h
 *
 *  Created on: 2023. 3. 29.
 *      Author: CBT
 */

#ifndef SRC_PERIPHERAL_ALARM_H_
#define SRC_PERIPHERAL_ALARM_H_


extern unsigned char devicealarm[15];
extern unsigned char devicePreAlarm[5];
extern unsigned char deviceerror[15];

extern unsigned char AlarmCheckFlag[15];
extern unsigned char ErrorCheckFlag[15];

int Alarm_Check();
int PreAlarm_Check();
void DisplayAlarmCheck();

#endif /* SRC_PERIPHERAL_ALARM_H_ */
