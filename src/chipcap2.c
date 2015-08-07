/*
 * chipcap2 - Simple program just read out himidity/temperature
 *
 * Copyright (C) 2015 Sittisak Sakamornlertsakul <sittisaks@hotmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License v2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
  char rxBuffer[5];  // receive buffer
  char txBuffer[5];  // transmit buffer
  int chipcap2Address = 0x28; 
  int opResult = 0;   // keep operation result
  int sign = 1;     // Temperature sign

  // Create a file descriptor for the I2C bus
  int i2cHandle = open("/dev/i2c-0", O_RDWR);
  if(i2cHandle < 0) {
	printf("Error open /dev/i2c-0!!!");
	exit(1);
  }

  // Tell the I2C bus the address of the device 
  // we are going to talk to.
  opResult = ioctl(i2cHandle, I2C_SLAVE, chipcap2Address);

  // Clear our buffers
  memset(rxBuffer, 0, sizeof(rxBuffer));
  memset(txBuffer, 0, sizeof(txBuffer));

  txBuffer[0] = 0x00; // This is just a dummy data for MR(Measurement Request).
  opResult = write(i2cHandle, txBuffer, 1);
  // Read back the humidity and temperture, 4 bytes of data
  if (opResult != 1) printf("No ACK bit!\n");
  int ready = 0;
  do {
    opResult = read(i2cHandle, rxBuffer, 4);
    ready = ((rxBuffer[0] & 0xc0) == 0) ? 1 : 0;
  } while(!ready);
  // Status = data0:bit 7-6
  // Humidity = data0:bit 5-0 and data1:bit 7-0
  // Temperature = data2:bit 7-0 and data3:bit 7-2
  // sign = ((rxBuffer[0] & 0x80)!= 0) ? -1 : 1;
//  int i;
//  for(i=0; i< 4; i++)
//     printf("%2x ", rxBuffer[i] & 0xff);
//  printf("\n");
  int humid_i = ((rxBuffer[0] & 0x3f) << 8) + (rxBuffer[1] & 0xff);
  int temp_i = (((rxBuffer[2] & 0xff) << 8) + (rxBuffer[3] & 0xfc)) >> 2;
  double humid_d = (humid_i/16384.0) * 100.0;
  double temp_d = ((temp_i/16384.0) * 165.0) - 40.0; 
//  printf("Status = %d\n", (rxBuffer[0] & 0xc0) >> 6);
//  printf("Humidity = %x %3.2f\n", humid_i, humid_d);
  printf("%3.2f", temp_d);
  
  close(i2cHandle);
}
