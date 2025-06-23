/*
 * Process.h
 *
 *  Created on: Aug 10, 2022
 *      Author: CBT
 */

#ifndef SRC_PERIPHERAL_PROCESS_H_
#define SRC_PERIPHERAL_PROCESS_H_

struct data_format {
	unsigned char cyclename;
	unsigned char year, month, day, week;
	unsigned char start_hour, start_minute, start_second;
	unsigned char end_hour, end_minute, end_second;

	float	tempmax[7],pressuremax[7],pressuremin[7];
	unsigned char status;

	unsigned char sterilantNum[10];
	unsigned char Num[10];
	int totalTime[2];

};

extern struct data_format p_data;	//프린트 데이터

extern float PressureData[300];
extern float TemperatureData[300];

extern int HeaterControlMode;

extern unsigned int TotalTime;
extern unsigned int fProcessTime[7];
extern unsigned int CycleTime;
extern unsigned int FullCycleTime;
extern unsigned int EndTime;
extern unsigned int ProcessTime[7];
extern unsigned int StepTime[21];


extern int CycleName;
extern int ProcessNum,StepNum;
extern int testbit;

extern int errorcode;


extern int SelfTestInitFlag;
extern int SelfTestMode,SelfTestProcess;

extern int Select_NORMAL_MODE;
extern int StopFlag;

extern unsigned int DataCounter;
extern unsigned char ProcessFlag, CurrentProcess, CurrentStep, ProcessStep;
extern unsigned int ProcessTime[7];
extern unsigned int StepTime[21];

extern int TestVacuumValue;
extern int TestLeakValue;

extern int HeaterControlMode;

struct Process_data_format {
	unsigned int PartsSetting;
	unsigned int	Time;
};
extern struct Process_data_format	CycleData[7][21];


extern float TestPressure[10], TestTemp[5];
extern int VacuumTestResult[3];
extern int HeaterTestResult[5];
extern int ValveTestResult[4];
extern int TestResult[4];


void loop();

void DeliSecondProcess(void);
void HalfSecondProcess(void);
void OneSecondProcess(void);
void TensecondProcess(void);
void OneMinuteProcess(void);
void Init_Device(void);

void Inithardware();



void StartProcess(void);
void StopProcess(void);
void FactoryTestStop();
void FactoryTestStart();
void ProcessEndTimer(void);


void FactoryTestMode();
void NormalMode();
void VacuumTest();
void HeaterTest();
void ValveTest();
void TotalSelfTest();

void Endtime_Check_Process();
void ErrorCheck();
void ErrorEndProcess();
void DeviceErrorProcess();

void SelfTestModeStart(int mode);
void SelfTestModeStop(int mode);

void GetStartTime();
void GetEndTime();
void GetData();
void InitData();

int calculateElapsedDays(int current_year, int current_month, int current_day, int open_year, int open_month, int open_day);
int check_expiry();

#endif /* SRC_PERIPHERAL_PROCESS_H_ */
