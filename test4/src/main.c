/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/trace.h"
#include <time.h>
#include <unistd.h>
#include "timer.h"
#include "led.h"
#include "stm32f4xx_hal.h"


// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 3 / 4)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(int argc, char* argv[])
{
	 int arr[] = {10, 20, 30, 40, 50}; // Khởi tạo mảng N giá trị nhiệt độ
	 int arr_len = sizeof(arr) / sizeof(arr[0]); // Tính độ dài của mảng số liệu nhiệt độ

// Khai báo tên các chân GPIO được sử dụng để điều khiển đèn LED
#define LED_GPIO_PORT       GPIOD
#define LED_GPIO_PIN        GPIO_PIN_12
	// Khởi tạo HAL
	HAL_Init();

	// Cấu hình clock cho chân GPIO
	__HAL_RCC_GPIOD_CLK_ENABLE();

	// Cấu hình chân GPIO để điều khiển đèn LED
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = LED_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
    // Đọc và xử lý mảng N giá trị
    for (int i=0; i<arr_len; i++)
    {
    	printf("Sensor_temperature: %d Celsius\n",arr[i]);
    	time_t t = time(NULL);
    	struct tm *tm = localtime(&t);
    	printf("Current date and time to get temperature: %s", asctime(tm));
        // Bật đèn LED
    	HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_PIN_SET);
        // Đợi 60 giây
        for (int j=0; j<600000000; j++);
        // Tắt đèn LED
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_PIN_RESET);
        // Đợi 60 giây
        for (int j=0; j<600000000; j++);
    }
    while(1);
    printf("Đang chờ 1 giây...\n");
    sleep(1); // tạm dừng chương trình trong 1 giây
  return 0;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
