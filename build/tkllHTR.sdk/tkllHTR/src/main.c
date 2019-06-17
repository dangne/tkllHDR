#include <stdlib.h>
#include "xil_printf.h"
#include "xuartps.h"
#include "xparameters.h"
#include "sleep.h"

#define BUFFER_SIZE 	5

XUartPs Uart; // Instance of the UART Device

static u8 SendBuffer[BUFFER_SIZE];	// Buffer for Transmitting Data
static u8 RecvBuffer[BUFFER_SIZE];	// Buffer for Receiving Data

int main(){
	// Lookup configuration for the UART
	XUartPs_Config* Config = XUartPs_LookupConfig(XPAR_XUARTPS_0_DEVICE_ID);

	// Initialize UART with the above configuration
	XUartPs_CfgInitialize(&Uart, Config, Config->BaseAddress);

	// Set receive timeout to detect an idle connection
	XUartPs_SetRecvTimeout(&Uart, 8);

	// Initialize send and receive buffer
	memset(SendBuffer, 65, BUFFER_SIZE);	// 65 is 'A' in ASCII
	memset(RecvBuffer, 0, BUFFER_SIZE);

	// Send data to UART
	XUartPs_Send(&Uart, SendBuffer, BUFFER_SIZE);

	while(1){
		// Wait until there is incoming data
		while (!XUartPs_IsReceiveData(XPAR_XUARTPS_0_BASEADDR));

		// Short delay to ensure the UART receive properly
		usleep(500);

		// Receive data from UART
		XUartPs_Recv(&Uart, RecvBuffer, BUFFER_SIZE);

		// Send received data again to check if it is read correctly
		XUartPs_Send(&Uart, RecvBuffer, BUFFER_SIZE);
		memset(RecvBuffer, 0, BUFFER_SIZE);
	}
	return 0;
}
