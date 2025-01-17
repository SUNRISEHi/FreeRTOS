/* message modify test*/

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Local includes. */
#include "console.h" // posix 환경에서 console을 사용하기 위한 헤더파일. printf 대신 사용

// Simulation of the CPU hardware sleeping mode
// Idle task hook, 지우면 안됨

//Task handle 이름 선언
TaskHandle_t task3;

void vApplicationIdleHook( void )
{
    usleep( 15000 );
}

// Task 1 정의
void vTask1( void *pvParameters )
{
	const char *pcTaskName = "zzzzzzz\r\n";

	for( ;; )
	{
		console_print( pcTaskName );
        vTaskDelay( 1000 );
	}
}
// Task 2 정의
void vTask2( void *pvParameters )
{
	const char *pcTaskName = "알람! 알람! 알람!\r\n";

	for( ;; )
	{
		console_print( pcTaskName );
        vTaskDelay( 5000 );
		vTaskResume(task3);
	}
}
// Task 3 정의
void vTask3(void *pvParameters)
{
	const char*pcTaskName = "5분만...\r\n";
	for(;;)
	{
		console_print( pcTaskName );
		vTaskSuspend(task3);
	}
}


int main( void )
{

    console_init(); 

	xTaskCreate( vTask1, "Task 1", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( vTask2, "Task 2", configMINIMAL_STACK_SIZE, NULL, 3, NULL );
    xTaskCreate( vTask3, "Task 3", configMINIMAL_STACK_SIZE, NULL, 2, &task3 );

	vTaskStartScheduler();
	for( ;; );
}