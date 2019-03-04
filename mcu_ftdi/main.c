/*
 * Copyright (C) 2018 Fundación Inria Chile
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     riot_apps
 * @{
 *
 * @file
 * @brief       Mcu ftdi test aplication
 *
 * @author      Francisco Molina <francisco.molina@inria.cl>
 *
 * @}
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "board.h"
#include "periph/uart.h"
// #include "uart_stdio.h"

#define SHELL_BUFSIZE       (128U)
#define UART_BUFSIZE        (128U)

#define PRINTER_PRIO        (THREAD_PRIORITY_MAIN - 1)
#define PRINTER_TYPE        (0xabcd)

#ifndef UART_STDIO_DEV
#define UART_STDIO_DEV      (UART_UNDEF)
#endif


static void rx_cb_1(void *arg, uint8_t data)
{
    (void) arg;
    uart_write(UART_DEV(1), &data, 1);
}

static void rx_cb_2(void *arg, uint8_t data)
{
    (void) arg;
    uart_write(UART_DEV(0), &data, 1);
}

int main(void)
{
    printf("Uart FTDI runing on UART_DEV 0 & 1 \n \n");

    if(UART_NUMOF<2){
    	printf("This Board doesn't have enough uart devices \n");
        return -1;
    }

    uart_init(UART_DEV(0), 115200, rx_cb_1, (void *) 0);
    uart_init(UART_DEV(1), 115200, rx_cb_2, (void *) 1);

    while(1){}

    return 0;
}
