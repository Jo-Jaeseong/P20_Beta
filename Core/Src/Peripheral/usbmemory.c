/*
 * usb.c
 *
 *  Created on: Mar 25, 2024
 *      Author: CBT_DEV
 */


/*
 *Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/usbh_msc.c
 * if (status == USBH_NOT_SUPPORTED)를
 * if (status == USBH_NOT_SUPPORTED|| (status == USBH_BUSY))로 수정 필요
 */

/*
 * usb.c
 *
 *  Created on: Mar 25, 2024
 *      Author: CBT_DEV
 */
#include "stdio.h"
#include "main.h"
#include "fatfs.h"
#include "ff.h"
#include "usb_host.h"
#include "peripheral.h"
#include "sensor.h"
#include "hardware.h"


extern char USBHPath[4];   /* USBH logical drive path */
extern FATFS USBHFatFS;    /* File system object for USBH logical drive */
extern FIL USBHFile;       /* File object for USBH */
FRESULT USBret;
int firstcall=1;
char buffer[1024];

extern USBH_HandleTypeDef hUsbHostFS;
extern ApplicationTypeDef Appli_state;

CycleUSBData saveCycleData;


void SaveCycle(){
    char filename[25]; // 파일 이름을 저장할 배열
    char path[50]={};
    FRESULT res;

    sprintf(filename, "%02d-%02d-%02d", p_data.year, p_data.month, p_data.day);
    sprintf(filename + strlen(filename), "_%03d.txt",totalCount);


    //sprintf(filename, "0.txt");
	// USB 메모리가 준비된 상태인지 확인
	if(Appli_state == APPLICATION_READY){
		// USB 메모리를 마운트
		USBret = f_mount(&USBHFatFS, USBHPath, 1);
		if(USBret == FR_OK) {
			sprintf(path, "%02d", p_data.year);
			res = f_mkdir(path);
			if(res == FR_OK || res == FR_EXIST) {
				sprintf(path, "%02d/%02d", p_data.year,p_data.month);
				res = f_mkdir(path);
				if(res == FR_OK || res == FR_EXIST) {
					// 폴더 경로에 파일 이름을 추가하여 전체 경로 생성
					sprintf(path + strlen(path), "/%s", filename);
					// 파일 생성 및 열기
					USBret = f_open(&USBHFile, path, FA_CREATE_ALWAYS | FA_WRITE);
					if(USBret == FR_OK) {
						f_printf(&USBHFile,"SERIAL NO     :  %02d-%02d-%02d-%02d\n",(int)CurrentRFIDData.production_year,(int)CurrentRFIDData.production_month,(int)CurrentRFIDData.production_day, (int)CurrentRFIDData.production_number);
						f_printf(&USBHFile,"Loading Date  :  %2d-%02d-%02d\n",(int)CurrentRFIDData.open_year,(int)CurrentRFIDData.open_month,(int)CurrentRFIDData.open_day);
						f_printf(&USBHFile,"Expiry Date   :  %2d-%02d-%02d\n",(int)CurrentRFIDData.expiry_year,(int)CurrentRFIDData.expiry_month,(int)CurrentRFIDData.expiry_day);
						f_printf(&USBHFile,"Remain H2O2   :  %02d\n",CurrentRFIDData.volume);

						f_printf(&USBHFile,"Selected Cycle:  %d    \n",CycleName);

						f_printf(&USBHFile,"Total Cycle   :  %3d     \n",totalCount);
						f_printf(&USBHFile,"Daily Cycle   :  %3d     \n",dailyCount);
						f_printf(&USBHFile,"Cycle Date    :  %02d-%02d-%02d\n", p_data.year,p_data.month,p_data.day);

						f_printf(&USBHFile,"Start Time    :  %02d:%02d:%02d\n",
								p_data.start_hour,p_data.start_minute,p_data.start_second);
						f_printf(&USBHFile,"End Time      :  %02d:%02d:%02d\n",
									p_data.end_hour,p_data.end_minute,p_data.end_second);

						int tempminute,tempsecond;
						tempminute=(fProcessTime[1]/10)/60;
						tempsecond=(fProcessTime[1]/10)%60;
						f_printf(&USBHFile,"1_Time  :  %02d:%02d      \n",tempminute,tempsecond);
						f_printf(&USBHFile,"1.Temp(Max)     :  %3d   \n",(int)p_data.tempmax[1]);
						f_printf(&USBHFile,"1.Pressure(Max) :  %4d   \n",(int)p_data.pressuremax[1]);
						f_printf(&USBHFile,"1.Pressure(Min) :  %4d   \n",(int)p_data.pressuremin[1]);


						tempminute=(fProcessTime[2]/10)/60;
						tempsecond=(fProcessTime[2]/10)%60;
						f_printf(&USBHFile,"2_Time   :  %02d:%02d      \n",tempminute,tempsecond);
						f_printf(&USBHFile,"2.Temp(Max)     :  %3d   \n",(int)p_data.tempmax[2]);
						f_printf(&USBHFile,"2.Pressure(Max) :  %4d   \n",(int)p_data.pressuremax[2]);
						f_printf(&USBHFile,"2.Pressure(Min) :  %4d   \n",(int)p_data.pressuremin[2]);

						tempminute=(fProcessTime[3]/10)/60;
						tempsecond=(fProcessTime[3]/10)%60;
						f_printf(&USBHFile,"3_Time    :  %02d:%02d      \n",tempminute,tempsecond);
						f_printf(&USBHFile,"3.Temp(Max)     :  %3d   \n",(int)p_data.tempmax[3]);
						f_printf(&USBHFile,"3.Pressure(Max) :  %4d   \n",(int)p_data.pressuremax[3]);
						f_printf(&USBHFile,"3.Pressure(Min) :  %4d   \n",(int)p_data.pressuremin[3]);

						tempminute=(fProcessTime[4]/10)/60;
						tempsecond=(fProcessTime[4]/10)%60;
						f_printf(&USBHFile,"4_Time    :  %02d:%02d      \n",tempminute,tempsecond);
						f_printf(&USBHFile,"4.Temp(Max)     :  %3d   \n",(int)p_data.tempmax[4]);
						f_printf(&USBHFile,"4.Pressure(Max) :  %4d   \n",(int)p_data.pressuremax[4]);
						f_printf(&USBHFile,"4.Pressure(Min) :  %4d   \n",(int)p_data.pressuremin[4]);

						tempminute=(fProcessTime[5]/10)/60;
						tempsecond=(fProcessTime[5]/10)%60;
						f_printf(&USBHFile,"5_Time    :  %02d:%02d      \n",tempminute,tempsecond);
						f_printf(&USBHFile,"5.Temp(Max)     :  %3d   \n",(int)p_data.tempmax[5]);
						f_printf(&USBHFile,"5.Pressure(Max) :  %4d   \n",(int)p_data.pressuremax[5]);
						f_printf(&USBHFile,"5.Pressure(Min) :  %4d   \n",(int)p_data.pressuremin[5]);

						tempminute=(fProcessTime[6]/10)/60;
						tempsecond=(fProcessTime[6]/10)%60;
						f_printf(&USBHFile,"6_Time    :  %02d:%02d      \n",tempminute,tempsecond);
						f_printf(&USBHFile,"6.Temp(Max)     :  %3d   \n",(int)p_data.tempmax[6]);
						f_printf(&USBHFile,"6.Pressure(Max) :  %4d   \n",(int)p_data.pressuremax[6]);
						f_printf(&USBHFile,"6.Pressure(Min) :  %4d   \n",(int)p_data.pressuremin[6]);

						f_printf(&USBHFile,"CARBON FILTER :  %04d     \n",CarbonFilter);
						f_printf(&USBHFile,"HEPA FILTER   :  %04d     \n",HEPAFilter);
						f_printf(&USBHFile,"PLASMA ASSY   :  %04d     \n",PlasmaAssy);

						f_printf(&USBHFile,"Cycle Time    :  %02d:%02d \n",p_data.totalTime[0],p_data.totalTime[1]);
						f_printf(&USBHFile,"Cycle Status  :  %02d      \n",p_data.status);
						f_printf(&USBHFile,"Operator ID   :  %02d      \n",CurrentUser);				// 파일 닫기
					}
				}
				f_close(&USBHFile);
			}
			// USB 메모리 마운트 해제
			f_mount(NULL, USBHPath, 0);
		}
	}
}

void LoadCycleData(int readyear, int readmonth, int readday, int readcount) {
	char filename[30]; // 파일 이름을 저장할 배열
	char line[100]; // 파일로부터 읽은 한 줄을 저장할 배열
    sprintf(filename, "%02d/%02d/%02d-%02d-%02d",readyear, readmonth, readyear, readmonth, readday);
    sprintf(filename + strlen(filename), "_%03d.txt",readcount);
	if(Appli_state == APPLICATION_READY){
		// USB 메모리를 마운트
		USBret = f_mount(&USBHFatFS, USBHPath, 1);
		if(USBret == FR_OK) {
			// 파일 열기
			USBret = f_open(&USBHFile, filename, FA_READ);
			if(USBret == FR_OK) {
				// 데이터 불러오기를 위한 코드
				while(f_gets(line, sizeof(line), &USBHFile)) {
				        if(strncmp(line, "SERIAL NO", 9) == 0) {
				        	sscanf(line, "SERIAL NO : %02d-%02d-%02d-%02d",
				                   &saveCycleData.serialNumber[0],
				                   &saveCycleData.serialNumber[1],
				                   &saveCycleData.serialNumber[2],
				                   &saveCycleData.serialNumber[3]);
				        }
				        else if(strncmp(line, "Loading Date", 12) == 0) {
				            sscanf(line, "Loading Date : %2d-%02d-%02d",
				                   &saveCycleData.loadingDate[0],
				                   &saveCycleData.loadingDate[1],
				                   &saveCycleData.loadingDate[2]);
				        }
				        else if(strncmp(line, "Expiry Date", 11) == 0) {
				            sscanf(line, "Expiry Date : %2d-%02d-%02d",
				                   &saveCycleData.expiryDate[0],
				                   &saveCycleData.expiryDate[1],
				                   &saveCycleData.expiryDate[2]);
				        }
				        else if(strncmp(line, "Remain H2O2", 11) == 0) {
				            sscanf(line, "Remain H2O2 : %d", &saveCycleData.volume);
				        }
				        else if(strncmp(line, "Selected Cycle", 14) == 0) {
							sscanf(line, "Selected Cycle:  %d", &saveCycleData.cycleName);
						}
				        else if(strncmp(line, "Total Cycle", 11) == 0) {
							sscanf(line, "Total Cycle   :  %3d", &saveCycleData.totalCount);
						}
				        else if(strncmp(line, "Daily Cycle", 11) == 0) {
							sscanf(line, "Daily Cycle   :  %3d", &saveCycleData.dailyCount);
						}
				        else if(strncmp(line, "Cycle Date", 10) == 0) {
							sscanf(line, "Cycle Date    :  %02d-%02d-%02d",
									&saveCycleData.date[0],
									&saveCycleData.date[1],
									&saveCycleData.date[2]);
						}
				        else if(strncmp(line, "Start Time", 10) == 0) {
				            sscanf(line, "Start Time    :  %02d:%02d:%02d",
				                   &saveCycleData.startTime[0],
				                   &saveCycleData.startTime[1],
				                   &saveCycleData.startTime[2]);
				        }
				        else if(strncmp(line, "End Time", 8) == 0) {
				            sscanf(line, "End Time      :  %02d:%02d:%02d",
				                   &saveCycleData.endTime[0],
				                   &saveCycleData.endTime[1],
				                   &saveCycleData.endTime[2]);
				        }
				        else if(strncmp(line, "1_Time", 6) == 0) {
				            sscanf(line, "1_Time  :  %02d:%02d",
				                   &saveCycleData.processTime[1][0],
				                   &saveCycleData.processTime[1][1]);
				        }
				        else if(strncmp(line, "1.Temp(Max)", 11) == 0) {
				            sscanf(line, "1.Temp(Max)     :  %3d",&saveCycleData.maxTemperature[1]);

				        }
				        else if(strncmp(line, "1.Pressure(Max)", 15) == 0) {
							sscanf(line, "1.Pressure(Max) :  %4d",&saveCycleData.maxPressure[1]);

						}
				        else if(strncmp(line, "1.Pressure(Min)", 15) == 0) {
							sscanf(line, "1.Pressure(Min) :  %4d",&saveCycleData.minPressure[1]);

						}
				        else if(strncmp(line, "2_Time", 6) == 0) {
				            sscanf(line, "2_Time  :  %02d:%02d",
				                   &saveCycleData.processTime[2][0],
				                   &saveCycleData.processTime[2][1]);
				        }
				        else if(strncmp(line, "2.Temp(Max)", 11) == 0) {
				            sscanf(line, "2.Temp(Max)     :  %3d",&saveCycleData.maxTemperature[2]);

				        }
				        else if(strncmp(line, "2.Pressure(Max)", 15) == 0) {
							sscanf(line, "2.Pressure(Max) :  %4d",&saveCycleData.maxPressure[2]);

						}
				        else if(strncmp(line, "2.Pressure(Min)", 15) == 0) {
							sscanf(line, "2.Pressure(Min) :  %4d",&saveCycleData.minPressure[2]);

						}
				        else if(strncmp(line, "3_Time", 6) == 0) {
				            sscanf(line, "3_Time  :  %02d:%02d",
				                   &saveCycleData.processTime[3][0],
				                   &saveCycleData.processTime[3][1]);
				        }
				        else if(strncmp(line, "3.Temp(Max)", 11) == 0) {
				            sscanf(line, "3.Temp(Max)     :  %3d",&saveCycleData.maxTemperature[3]);

				        }
				        else if(strncmp(line, "3.Pressure(Max)", 15) == 0) {
							sscanf(line, "3.Pressure(Max) :  %4d",&saveCycleData.maxPressure[3]);

						}
				        else if(strncmp(line, "3.Pressure(Min)", 15) == 0) {
							sscanf(line, "3.Pressure(Min) :  %4d",&saveCycleData.minPressure[3]);

						}
				        else if(strncmp(line, "4_Time", 6) == 0) {
				            sscanf(line, "4_Time  :  %02d:%02d",
				                   &saveCycleData.processTime[4][0],
				                   &saveCycleData.processTime[4][1]);
				        }
				        else if(strncmp(line, "4.Temp(Max)", 11) == 0) {
				            sscanf(line, "4.Temp(Max)     :  %3d",&saveCycleData.maxTemperature[4]);

				        }
				        else if(strncmp(line, "4.Pressure(Max)", 15) == 0) {
							sscanf(line, "4.Pressure(Max) :  %4d",&saveCycleData.maxPressure[4]);

						}
				        else if(strncmp(line, "4.Pressure(Min)", 15) == 0) {
							sscanf(line, "4.Pressure(Min) :  %4d",&saveCycleData.minPressure[4]);

						}
				        else if(strncmp(line, "5_Time", 6) == 0) {
				            sscanf(line, "5_Time  :  %02d:%02d",
				                   &saveCycleData.processTime[5][0],
				                   &saveCycleData.processTime[5][1]);
				        }
				        else if(strncmp(line, "5.Temp(Max)", 11) == 0) {
				            sscanf(line, "5.Temp(Max)     :  %3d",&saveCycleData.maxTemperature[5]);

				        }
				        else if(strncmp(line, "5.Pressure(Max)", 15) == 0) {
							sscanf(line, "5.Pressure(Max) :  %4d",&saveCycleData.maxPressure[5]);

						}
				        else if(strncmp(line, "5.Pressure(Min)", 15) == 0) {
							sscanf(line, "5.Pressure(Min) :  %4d",&saveCycleData.minPressure[5]);
						}
				        else if(strncmp(line, "6_Time", 6) == 0) {
				            sscanf(line, "6_Time  :  %02d:%02d",
				                   &saveCycleData.processTime[6][0],
				                   &saveCycleData.processTime[6][1]);
				        }
				        else if(strncmp(line, "6.Temp(Max)", 11) == 0) {
				            sscanf(line, "6.Temp(Max)     :  %3d",&saveCycleData.maxTemperature[6]);
				        }
				        else if(strncmp(line, "6.Pressure(Max)", 15) == 0) {
							sscanf(line, "6.Pressure(Max) :  %4d",&saveCycleData.maxPressure[6]);
						}
				        else if(strncmp(line, "6.Pressure(Min)", 15) == 0) {
							sscanf(line, "6.Pressure(Min) :  %4d",&saveCycleData.minPressure[6]);
						}
				        else if(strncmp(line, "CARBON FILTER", 13) == 0) {
							sscanf(line, "CARBON FILTER :  %04d",&saveCycleData.carbonFilter);
						}
				        else if(strncmp(line, "HEPA FILTER", 11) == 0) {
							sscanf(line, "HEPA FILTER   :  %04d",&saveCycleData.hepaFilter);
						}
				        else if(strncmp(line, "PLASMA ASSY", 11) == 0) {
							sscanf(line, "PLASMA ASSY   :  %04d",&saveCycleData.plasmaAssy);
						}
				        else if(strncmp(line, "Cycle Time", 10) == 0) {
							sscanf(line, "Cycle Time    :  %02d:%02d ",
					                   &saveCycleData.totalTime[0],
					                   &saveCycleData.totalTime[1]);
						}
				        else if(strncmp(line, "Cycle Status", 12) == 0) {
							sscanf(line, "Cycle Status  :  %02d",&saveCycleData.status);
						}
				        else if(strncmp(line, "Operator ID", 11) == 0) {
							sscanf(line, "Operator ID   :  %02d",&saveCycleData.ID);
						}
				    }

				// 파일 닫기
				f_close(&USBHFile);
			}
			// USB 메모리 마운트 해제
			f_mount(NULL, USBHPath, 0);
		}
	}
}


/*
//아래는 Raw 데이터 가공 입력해야함.
for(int i=0;i<270;i++){
	TemperatureData[i+1]*10)/100);
	PressureData[i+1]*10)/100);

}
*/

void SaveCycleSettingData(CycleUSBData* data) {
    char filename[20]; // 파일 이름을 저장할 배열
    sprintf(filename, "Cycle_Setting.txt");
    // USB 메모리가 준비된 상태인지 확인
    if(Appli_state == APPLICATION_READY){
        // USB 메모리를 마운트
        USBret = f_mount(&USBHFatFS, USBHPath, 1);
        if(USBret == FR_OK) {
            // 파일 생성 및 열기
            USBret = f_open(&USBHFile, filename, FA_CREATE_ALWAYS | FA_WRITE);
            if(USBret == FR_OK) {
               // f_printf(&USBHFile,"Date: %d-%d-%d\nProcess Name: %d\n", data->year, data->month, data->day, data->processName);
                // 파일 닫기
                f_close(&USBHFile);
            }
            // USB 메모리 마운트 해제
            f_mount(NULL, USBHPath, 0);
        }
    }
}

void LoadSettingData(CycleUSBData* data) {
    char filename[20]; // 파일 이름을 저장할 배열
    //int file_number = 1; // 파일 번호 (예시로 1을 사용)

	sprintf(filename, "Setting.txt");
    // USB 메모리가 준비된 상태인지 확인
    if(Appli_state == APPLICATION_READY){
        // USB 메모리를 마운트
        USBret = f_mount(&USBHFatFS, USBHPath, 1);
        if(USBret == FR_OK) {
            // 파일 열기
            USBret = f_open(&USBHFile, filename, FA_READ);
            if(USBret == FR_OK) {
                // 데이터 불러오기를 위한 코드
                char buffer[100]; // 파일로부터 읽은 데이터를 저장하기 위한 버퍼
                UINT bytesRead; // 실제로 읽은 바이트 수를 저장
                f_read(&USBHFile, buffer, sizeof(buffer)-1, &bytesRead);
                buffer[bytesRead] = '\0'; // 문자열 종료를 위해 NULL 문자 추가

                // 읽은 데이터를 ProcessData 구조체에 파싱
                sscanf(buffer, "Date: %d-%d-%d\n", &data->date[0], &data->date[1], &data->date[2]);

                // 파일 닫기
                f_close(&USBHFile);
            }
            // USB 메모리 마운트 해제
            f_mount(NULL, USBHPath, 0);
        }
    }
}

void sortNonZeroElementsKeepFirstZero(int arr[], int n) {
    int i, j, temp;

    // 배열의 첫 번째 요소를 제외하고 비-제로 요소를 찾아 정렬합니다.
    // 시작 인덱스를 1로 설정합니다.
    for (i = 1; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            // 두 요소가 비-제로이고 첫 번째 요소가 두 번째 요소보다 클 경우
            if ((arr[i] != 0 && arr[j] != 0) && (arr[i] > arr[j])) {
                // 두 요소의 위치를 바꿉니다.
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // 제로 요소들을 배열의 끝으로 이동시킵니다, 첫 번째 요소는 제외합니다.
    int zeroCount = 0; // 제로 요소의 개수를 세기
    for (i = 1; i < n; i++) { // 첫 번째 요소를 제외하고 시작
        if (arr[i] == 0) {
            zeroCount++;
        } else if (zeroCount > 0) {
            arr[i - zeroCount] = arr[i];
            arr[i] = 0;
        }
    }
}

#define MAX_FILES   100 // 최대 파일 수
#define MAX_FILENAME 20 // 최대 파일 이름 길이
char fileList[MAX_FILES][MAX_FILENAME]; // 파일 이름을 저장할 배열
int fileCount; // 파일 개수
int temptotalcycle[30];

void ReadListData(int year, int month, int day){
    DIR dir; // 디렉토리 객체
    FILINFO fno; // 파일 정보 객체
    FRESULT res; // 결과 저장 변수

    char path[20]={};
    int fileYear, fileMonth, fileDay, fileNum; // 파일에서 추출한 날짜 및 숫자

    fileCount = 0; // 파일 개수
    memset(temptotalcycle,0,sizeof(temptotalcycle));

	if(Appli_state == APPLICATION_READY){
		USBret=f_mount(&USBHFatFS, USBHPath, 1);
		sprintf(path, "%02d/%02d", year, month);
		if (f_opendir(&dir, path) == FR_OK) { // USB 메모리의 루트 디렉토리를 열기
            while (fileCount < MAX_FILES) {
                // 디렉토리 읽기
				res = f_readdir(&dir, &fno);
				if (res != FR_OK || fno.fname[0] == 0) break; // 더 이상 읽을 파일이 없으면 종료
					if (!(fno.fattrib & AM_DIR)) { // 파일인 경우
						// 파일 이름에서 날짜 정보 추출
						if (sscanf(fno.fname, "%02d-%02d-%02d_%03d.txt", &fileYear, &fileMonth, &fileDay, &fileNum) == 4) {
							// 주어진 날짜와 일치하는지 확인
							if (fileYear == year && fileMonth == month && fileDay == day) {
								printf("MATCHED FILE: %s\n", fno.fname);
								strncpy(fileList[fileCount], fno.fname, MAX_FILENAME-1);
								fileList[fileCount][MAX_FILENAME-1] = '\0';
								fileCount++;
								if(fileCount>25){
									fileCount=25;
								}
								temptotalcycle[fileCount]=fileNum;
							}
						}
					}
            	}
			// 디렉토리 닫기
			f_closedir(&dir);
		}
		f_mount(NULL, USBHPath, 0);
	}
    //int n = sizeof(temptotalcycle) / sizeof(temptotalcycle[0]);

    //sortNonZeroElementsKeepFirstZero(temptotalcycle, n);
}

/****************************************************************************************************************/
void SaveSetting(){
    char filename[25]; // 파일 이름을 저장할 배열
    char path[50]="Setting";
    FRESULT res;
    sprintf(filename, "Config.txt");

	// USB 메모리가 준비된 상태인지 확인
	if(Appli_state == APPLICATION_READY){
		// USB 메모리를 마운트
		USBret = f_mount(&USBHFatFS, USBHPath, 1);
		if(USBret == FR_OK) {
			res = f_mkdir(path);
			if(res == FR_OK || res == FR_EXIST) {
				// 폴더 경로에 파일 이름을 추가하여 전체 경로 생성
				sprintf(path + strlen(path), "/%s", filename);
				// 파일 생성 및 열기
				USBret = f_open(&USBHFile, path, FA_CREATE_ALWAYS | FA_WRITE);
				if(USBret == FR_OK) {
					f_printf(&USBHFile,"CleanBioTech Corp\n");
					f_printf(&USBHFile,"Device Config\n\n");

					f_printf(&USBHFile,"Model Name    :  %s\n",flash_MODEL_NAME);
					f_printf(&USBHFile,"Model Number  :  %s\n",flash_SERIAL_NUMBER);
					f_printf(&USBHFile,"Facility Name :  %s\n",flash_FACILITY_NAME);
					f_printf(&USBHFile,"Depart Name   :  %s\n",flash_DEPARTMENT_NAME);
					f_printf(&USBHFile,"S/W Version   :  %s\n",flash_SOFTWARE_VERSION);

					for(int i=0;i<5;i++){
						f_printf(&USBHFile,"ID%d : %s\n",i,flash_ID[i]);
						f_printf(&USBHFile,"PW%d : %s\n",i,flash_PW[i]);
					}

					f_printf(&USBHFile,"USER Count : %d\n",flashuserCount);

					f_printf(&USBHFile,"AlarmCheckFlag[0] : %d\n",AlarmCheckFlag[0]);
					f_printf(&USBHFile,"ErrorCheckFlag[0] : %d\n",ErrorCheckFlag[0]);
					f_printf(&USBHFile,"reservationFlag : %d\n",reservationFlag);
					f_printf(&USBHFile,"autoprintFlag : %d\n",autoprintFlag);
					f_printf(&USBHFile,"printcopy : %d\n",printcopy);
					f_printf(&USBHFile,"printdataFlag : %d\n",printdataFlag);
					f_printf(&USBHFile,"printgraphFlag : %d\n",printgraphFlag);

					f_printf(&USBHFile,"DoorSettingTemp[0] : %d\n",DoorSettingTemp[0]);
					f_printf(&USBHFile,"DoorSettingTemp[1] : %d\n",DoorSettingTemp[1]);
					f_printf(&USBHFile,"DoorSettingTemp[2] : %d\n",DoorSettingTemp[2]);
					f_printf(&USBHFile,"ChamberSettingTemp[0] : %d\n",ChamberSettingTemp[0]);
					f_printf(&USBHFile,"ChamberSettingTemp[1] : %d\n",ChamberSettingTemp[1]);
					f_printf(&USBHFile,"ChamberSettingTemp[2] : %d\n",ChamberSettingTemp[2]);
					f_printf(&USBHFile,"ChamberBackSettingTemp[0] : %d\n",ChamberBackSettingTemp[0]);
					f_printf(&USBHFile,"ChamberBackSettingTemp[1] : %d\n",ChamberBackSettingTemp[1]);
					f_printf(&USBHFile,"ChamberBackSettingTemp[2] : %d\n",ChamberBackSettingTemp[2]);
					f_printf(&USBHFile,"VaporizerSettingTemp[0] : %d\n",VaporizerSettingTemp[0]);
					f_printf(&USBHFile,"VaporizerSettingTemp[1] : %d\n",VaporizerSettingTemp[1]);
					f_printf(&USBHFile,"VaporizerSettingTemp[2] : %d\n",VaporizerSettingTemp[2]);

					f_printf(&USBHFile,"PreesureCondition[0] : %d\n",PreesureCondition[0]);
					f_printf(&USBHFile,"PreesureCondition[1] : %d\n",PreesureCondition[1]);
					f_printf(&USBHFile,"PreesureCondition[2] : %d\n",PreesureCondition[2]);

					f_printf(&USBHFile,"perispeed : %d\n",perispeed);

					f_printf(&USBHFile,"CalibrationTemp[0] : %d\n",CalibrationTemp[0]);
					f_printf(&USBHFile,"CalibrationTemp[1] : %d\n",CalibrationTemp[1]);
					f_printf(&USBHFile,"CalibrationTemp[2] : %d\n",CalibrationTemp[2]);
					f_printf(&USBHFile,"CalibrationTemp[3] : %d\n",CalibrationTemp[3]);
					f_printf(&USBHFile,"CalibrationVacuum : %d\n",CalibrationVacuum);


					f_printf(&USBHFile,"TestVacuumValue : %d\n",TestVacuumValue);
					f_printf(&USBHFile,"TestLeakValue : %d\n",TestLeakValue);
					f_printf(&USBHFile,"TestTempErrorValue : %d\n",TestTempErrorValue);

					f_printf(&USBHFile,"expiry_date2 : %d\n",expiry_date2);
					f_printf(&USBHFile,"DoorOpenPressure : %d\n",DoorOpenPressure);

					f_printf(&USBHFile,"totalCount : %d\n",totalCount);
					f_printf(&USBHFile,"dailyCount : %d\n",dailyCount);
					f_printf(&USBHFile,"beforeday : %d\n",beforeday);

					f_printf(&USBHFile,"RFIDData.production_year : %d\n",CurrentRFIDData.production_year);
					f_printf(&USBHFile,"RFIDData.production_month : %d\n",CurrentRFIDData.production_month);
					f_printf(&USBHFile,"RFIDData.production_day : %d\n",CurrentRFIDData.production_day);
					f_printf(&USBHFile,"RFIDData.production_number : %d\n",CurrentRFIDData.production_number);
					f_printf(&USBHFile,"RFIDData.open_year : %d\n",CurrentRFIDData.open_year);
					f_printf(&USBHFile,"RFIDData.open_month : %d\n",CurrentRFIDData.open_month);
					f_printf(&USBHFile,"RFIDData.open_day : %d\n",CurrentRFIDData.open_day);
					f_printf(&USBHFile,"RFIDData.expiry_year : %d\n",CurrentRFIDData.expiry_year);
					f_printf(&USBHFile,"RFIDData.expiry_month : %d\n",CurrentRFIDData.expiry_month);
					f_printf(&USBHFile,"RFIDData.expiry_day : %d\n",CurrentRFIDData.expiry_day);
					f_printf(&USBHFile,"RFIDData.volume : %d\n",CurrentRFIDData.volume);
					f_printf(&USBHFile,"RFIDData.volumemax : %d\n",CurrentRFIDData.volumemax);

					f_printf(&USBHFile,"CarbonFilterMax : %d\n",CarbonFilterMax);
					f_printf(&USBHFile,"HEPAFilterMax : %d\n",HEPAFilterMax);
					f_printf(&USBHFile,"PlasmaAssyMax : %d\n",PlasmaAssyMax);
					f_printf(&USBHFile,"CarbonFilter : %d\n",CarbonFilter);
					f_printf(&USBHFile,"HEPAFilter : %d\n",HEPAFilter);
					f_printf(&USBHFile,"PlasmaAssy : %d\n",PlasmaAssy);

					f_printf(&USBHFile,"LoginFlag : %d\n",LoginFlag);
					f_printf(&USBHFile,"MonitorFlag : %d\n",MonitorFlag);
				}
				f_close(&USBHFile);
			}
			// USB 메모리 마운트 해제
			f_mount(NULL, USBHPath, 0);
		}
	}
}

void LoadSetting() {
    char filename[25]; // 파일 이름을 저장할 배열
	char line[100]; // 파일로부터 읽은 한 줄을 저장할 배열
	sprintf(filename, "Setting/Config.txt");
	if(Appli_state == APPLICATION_READY){
		// USB 메모리를 마운트
		USBret = f_mount(&USBHFatFS, USBHPath, 1);
		if(USBret == FR_OK) {
			// 파일 열기
			USBret = f_open(&USBHFile, filename, FA_READ);
			if(USBret == FR_OK) {
				// 데이터 불러오기를 위한 코드
				while(f_gets(line, sizeof(line), &USBHFile)) {
					//f_printf(&USBHFile,"Model Name    :  %s\n",flash_MODEL_NAME);
					//f_printf(&USBHFile,"Model Number  :  %s\n",flash_SERIAL_NUMBER);
				        if(strncmp(line, "Model Name", 10) == 0) {
				        	sscanf(line, "Model Name    :  %s",&flash_MODEL_NAME);
				        }
				        else if(strncmp(line, "Model Number", 12) == 0) {
				            sscanf(line, "Model Number  :  %s",&flash_SERIAL_NUMBER);
				        }
				        else if(strncmp(line, "Depart Name", 11) == 0) {
				            sscanf(line, "Depart Name   :  %s",&flash_DEPARTMENT_NAME);
				        }
				        else if(strncmp(line, "S/W Version", 11) == 0) {
				            sscanf(line, "S/W Version   :  %s",&flash_SOFTWARE_VERSION);
				        }
				        else if(strncmp(line, "ID0", 3) == 0) {
				            sscanf(line, "ID0 : %s",&flash_ID[0]);
				        }
				        else if(strncmp(line, "ID1", 3) == 0) {
				            sscanf(line, "ID1 : %s",&flash_ID[1]);
				        }
				        else if(strncmp(line, "ID2", 3) == 0) {
				            sscanf(line, "ID2 : %s",&flash_ID[2]);
				        }
				        else if(strncmp(line, "ID3", 3) == 0) {
				            sscanf(line, "ID3 : %s",&flash_ID[3]);
				        }

				        else if(strncmp(line, "PW0", 3) == 0) {
				            sscanf(line, "PW0 : %s",&flash_PW[0]);
				        }
				        else if(strncmp(line, "PW1", 3) == 0) {
				            sscanf(line, "PW1 : %s",&flash_PW[1]);
				        }
				        else if(strncmp(line, "PW2", 3) == 0) {
				            sscanf(line, "PW2 : %s",&flash_PW[2]);
				        }
				        else if(strncmp(line, "PW3", 3) == 0) {
				            sscanf(line, "PW3 : %s",&flash_PW[3]);
				        }

				        else if(strncmp(line, "USER Count", 10) == 0) {
				            sscanf(line, "USER Count : %d",&flashuserCount);
				        }

				        else if(strncmp(line, "AlarmCheckFlag[0]", 14) == 0) {
				            sscanf(line, "AlarmCheckFlag[0] : %d",&AlarmCheckFlag[0]);
				        }
				        else if(strncmp(line, "ErrorCheckFlag[0]", 14) == 0) {
				            sscanf(line, "ErrorCheckFlag[0] : %d",&ErrorCheckFlag[0]);
				        }
				        else if(strncmp(line, "reservationFlag", 15) == 0) {
				            sscanf(line, "reservationFlag : %d",&reservationFlag);
				        }
				        else if(strncmp(line, "autoprintFlag", 13) == 0) {
				            sscanf(line, "autoprintFlag : %d",&autoprintFlag);
				        }
				        else if(strncmp(line, "printcopy", 9) == 0) {
				            sscanf(line, "printcopy : %d",&printcopy);
				        }
				        else if(strncmp(line, "printdataFlag", 13) == 0) {
				            sscanf(line, "printdataFlag : %d",&printdataFlag);
				        }
				        else if(strncmp(line, "printgraphFlag", 14) == 0) {
				            sscanf(line, "printgraphFlag : %d",&printgraphFlag);
				        }

				        else if(strncmp(line, "DoorSettingTemp[0]", 18) == 0) {
				            sscanf(line, "DoorSettingTemp[0] : %d",&DoorSettingTemp[0]);
				        }
				        else if(strncmp(line, "DoorSettingTemp[1]", 18) == 0) {
				            sscanf(line, "DoorSettingTemp[1] : %d",&DoorSettingTemp[1]);
				        }
				        else if(strncmp(line, "DoorSettingTemp[2]", 18) == 0) {
				            sscanf(line, "DoorSettingTemp[2] : %d",&DoorSettingTemp[2]);
				        }

				        else if(strncmp(line, "ChamberSettingTemp[0]", 21) == 0) {
				            sscanf(line, "ChamberSettingTemp[0] : %d",&ChamberSettingTemp[0]);
				        }
				        else if(strncmp(line, "ChamberSettingTemp[1]", 21) == 0) {
				            sscanf(line, "ChamberSettingTemp[1] : %d",&ChamberSettingTemp[1]);
				        }
				        else if(strncmp(line, "ChamberSettingTemp[2]", 21) == 0) {
				            sscanf(line, "ChamberSettingTemp[2] : %d",&ChamberSettingTemp[2]);
				        }

				        else if(strncmp(line, "ChamberBackSettingTemp[0]", 25) == 0) {
				            sscanf(line, "ChamberBackSettingTemp[0] : %d",&ChamberBackSettingTemp[0]);
				        }
				        else if(strncmp(line, "ChamberBackSettingTemp[1]", 25) == 0) {
				            sscanf(line, "ChamberBackSettingTemp[1] : %d",&ChamberBackSettingTemp[1]);
				        }
				        else if(strncmp(line, "ChamberBackSettingTemp[2]", 25) == 0) {
				            sscanf(line, "ChamberBackSettingTemp[2] : %d",&ChamberBackSettingTemp[2]);
				        }

				        else if(strncmp(line, "VaporizerSettingTemp[0]", 23) == 0) {
				            sscanf(line, "VaporizerSettingTemp[0] : %d",&VaporizerSettingTemp[0]);
				        }
				        else if(strncmp(line, "VaporizerSettingTemp[1]", 23) == 0) {
				            sscanf(line, "VaporizerSettingTemp[1] : %d",&VaporizerSettingTemp[1]);
				        }
				        else if(strncmp(line, "VaporizerSettingTemp[2]", 23) == 0) {
				            sscanf(line, "VaporizerSettingTemp[2] : %d",&VaporizerSettingTemp[2]);
				        }

				        else if(strncmp(line, "PreesureCondition[0]", 20) == 0) {
				            sscanf(line, "PreesureCondition[0] : %d",&PreesureCondition[0]);
				        }
				        else if(strncmp(line, "PreesureCondition[1]", 20) == 0) {
				            sscanf(line, "PreesureCondition[1] : %d",&PreesureCondition[1]);
				        }
				        else if(strncmp(line, "PreesureCondition[2]", 20) == 0) {
				            sscanf(line, "PreesureCondition[2] : %d",&PreesureCondition[2]);
				        }

				        else if(strncmp(line, "CalibrationTemp[0]", 18) == 0) {
				            sscanf(line, "CalibrationTemp[0] : %d",&CalibrationTemp[0]);
				        }
				        else if(strncmp(line, "CalibrationTemp[1]", 18) == 0) {
				            sscanf(line, "CalibrationTemp[1] : %d",&CalibrationTemp[1]);
				        }
				        else if(strncmp(line, "CalibrationTemp[2]", 18) == 0) {
				            sscanf(line, "CalibrationTemp[2] : %d",&CalibrationTemp[2]);
				        }
				        else if(strncmp(line, "CalibrationTemp[3]", 18) == 0) {
				            sscanf(line, "CalibrationTemp[3] : %d",&CalibrationTemp[3]);
				        }
				        else if(strncmp(line, "CalibrationVacuum", 17) == 0) {
				            sscanf(line, "CalibrationVacuum : %d",&CalibrationVacuum);
				        }

				        else if(strncmp(line, "TestVacuumValue", 15) == 0) {
				            sscanf(line, "TestVacuumValue : %d",&TestVacuumValue);
				        }
				        else if(strncmp(line, "TestLeakValue", 13) == 0) {
				            sscanf(line, "TestLeakValue : %d",&TestLeakValue);
				        }
				        else if(strncmp(line, "TestTempErrorValue", 18) == 0) {
				            sscanf(line, "TestTempErrorValue : %d",&TestTempErrorValue);
				        }
				        else if(strncmp(line, "expiry_date2", 17) == 0) {
				            sscanf(line, "expiry_date2 : %d",&expiry_date2);
				        }
				        else if(strncmp(line, "DoorOpenPressure", 16) == 0) {
				            sscanf(line, "DoorOpenPressure : %d",&DoorOpenPressure);
				        }

				        else if(strncmp(line, "totalCount", 10) == 0) {
				            sscanf(line, "totalCount : %d",&totalCount);
				        }
				        else if(strncmp(line, "dailyCount", 10) == 0) {
				            sscanf(line, "dailyCount : %d",&dailyCount);
				        }
				        else if(strncmp(line, "beforeday", 9) == 0) {
				            sscanf(line, "beforeday : %d",&beforeday);
				        }

				        else if(strncmp(line, "RFIDData.production_year", 24) == 0) {
				            sscanf(line, "RFIDData.production_year : %d",&CurrentRFIDData.production_year);
				        }
				        else if(strncmp(line, "RFIDData.production_month", 25) == 0) {
				            sscanf(line, "RFIDData.production_month : %d",&CurrentRFIDData.production_month);
				        }
				        else if(strncmp(line, "RFIDData.production_day", 23) == 0) {
				            sscanf(line, "RFIDData.production_day : %d",&CurrentRFIDData.production_day);
				        }
				        else if(strncmp(line, "RFIDData.production_number", 26) == 0) {
				            sscanf(line, "RFIDData.production_number : %d",&CurrentRFIDData.production_number);
				        }
				        else if(strncmp(line, "RFIDData.open_year", 18) == 0) {
				            sscanf(line, "RFIDData.open_year : %d",&CurrentRFIDData.open_year);
				        }
				        else if(strncmp(line, "RFIDData.open_month", 19) == 0) {
				            sscanf(line, "RFIDData.open_month : %d",&CurrentRFIDData.open_month);
				        }
				        else if(strncmp(line, "RFIDData.open_day", 17) == 0) {
				            sscanf(line, "RFIDData.open_day : %d",&CurrentRFIDData.open_day);
				        }
				        else if(strncmp(line, "RFIDData.expiry_year", 20) == 0) {
				            sscanf(line, "RFIDData.expiry_year : %d",&CurrentRFIDData.expiry_year);
				        }
				        else if(strncmp(line, "RFIDData.expiry_month", 21) == 0) {
				            sscanf(line, "RFIDData.expiry_month : %d",&CurrentRFIDData.expiry_month);
				        }
				        else if(strncmp(line, "RFIDData.expiry_day", 19) == 0) {
				            sscanf(line, "RFIDData.expiry_day : %d",&CurrentRFIDData.expiry_day);
				        }
				        else if(strncmp(line, "RFIDData.volume", 15) == 0) {
				            sscanf(line, "RFIDData.volume : %d",&CurrentRFIDData.volume);
				        }
				        else if(strncmp(line, "RFIDData.volumemax", 18) == 0) {
				            sscanf(line, "RFIDData.volumemax : %d",&CurrentRFIDData.volumemax);
				        }

				        else if(strncmp(line, "CarbonFilterMax", 15) == 0) {
				            sscanf(line, "CarbonFilterMax : %d",&CarbonFilterMax);
				        }
				        else if(strncmp(line, "HEPAFilterMax", 13) == 0) {
				            sscanf(line, "HEPAFilterMax : %d",&HEPAFilterMax);
				        }
				        else if(strncmp(line, "PlasmaAssyMax", 13) == 0) {
				            sscanf(line, "PlasmaAssyMax : %d",&PlasmaAssyMax);
				        }
				        else if(strncmp(line, "CarbonFilter", 12) == 0) {
				            sscanf(line, "CarbonFilter : %d",&CarbonFilter);
				        }
				        else if(strncmp(line, "HEPAFilter", 10) == 0) {
				            sscanf(line, "HEPAFilter : %d",&HEPAFilter);
				        }
				        else if(strncmp(line, "PlasmaAssy", 10) == 0) {
				            sscanf(line, "PlasmaAssy : %d",&PlasmaAssy);
				        }

				        else if(strncmp(line, "LoginFlag", 9) == 0) {
				            sscanf(line, "LoginFlag : %d",&LoginFlag);
				        }
				        else if(strncmp(line, "MonitorFlag", 12) == 0) {
				            sscanf(line, "MonitorFlag : %d",&MonitorFlag);
				        }
				    }

				// 파일 닫기
				f_close(&USBHFile);
			}
			// USB 메모리 마운트 해제
			f_mount(NULL, USBHPath, 0);
		}
	}
}



/****************************************************************************************************************/







void USB_Error_Handler(void)
{
  /* USER CODE BEGIN USB_Error_Handler */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END USB_Error_Handler */
}
