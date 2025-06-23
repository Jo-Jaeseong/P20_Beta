/*
 * sleepmodesystem.h
 *
 *  Created on: Dec 11, 2024
 *      Author: CBT_DEV
 */

#ifndef SRC_PERIPHERAL_SLEEPMODESYSTEM_H_
#define SRC_PERIPHERAL_SLEEPMODESYSTEM_H_

extern int SleepModeFlag;
extern int SleepModeStatus;
extern int ActiveWeekday[7];
extern int ActiveModeTime[2][7];
extern int SleepPageCount;
extern int SleepModeRunning_Flag;

void SleepModeInit();
void SleepModeProcess();
void SleepModeCancel();
int getDayOfWeek(int year, int month, int day);

#endif /* SRC_PERIPHERAL_SLEEPMODESYSTEM_H_ */
