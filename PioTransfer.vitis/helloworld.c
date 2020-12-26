/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <xil_io.h>
#include "sleep.h"

int main()
{
	init_platform();

	u32 Status = 0x00;
	u32 Command = 0x00;

	xil_printf("Hello World\n\r");


	Xil_Out32(0x43C00004, 0x01);
	Xil_Out32(0x43C00004, 0x02);
	Xil_Out32(0x43C00004, 0x03);
	Xil_Out32(0x43C00004, 0x04);
	Xil_Out32(0x43C00004, 0x05);
	Xil_Out32(0x43C00004, 0x06);
	Xil_Out32(0x43C00004, 0x07);
	Xil_Out32(0x43C00004, 0x08);

	while (1)
	{

		Status = Xil_In32(0x43C00000);

		xil_printf("Status %x\n\r", Status);

		if (Status == 0x01 || Status == 0x02 || Status == 0x04 || Status == 0x08)
		{
			Command = 0x01;
		}
		else if (Status == 0x03 || Status == 0x5 || Status == 0x06 || Status == 0x9 || Status == 0xA || Status == 0x0C)
		{
			Command = 0x03;
		}
		else if (Status == 0x7 || Status ==  0x0B || Status == 0x0D || Status == 0x0E)
		{
			Command = 0x7;
		}
		else if (Status == 0x0F)
		{
			Command = 0x0F;
		}
		else
		{
			Command = 0x00;
		}

		xil_printf("Command %x\n\r", Command);

		Xil_Out32(0x43C00004, Command);

		usleep(1000000);
	}

	cleanup_platform();
	return 0;
}
