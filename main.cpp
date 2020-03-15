/*
	ChibiOS - Copyright (C) 2006..2016 Nicolas Reinecke
	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#include "LedBlinkerThread.hpp"
#include "ch.hpp"
#include "chprintf.h"
#include "hal.h"
#include "usbcfg.h"
#include "PidParam.pb.h"
#include "pb_encode.h"
#define BUFFER_LENGTH 128

BaseSequentialStream* chp = (BaseSequentialStream*)(&SDU1);
uint8_t buffer[BUFFER_LENGTH];

LedBlinkerThread ledBlinker("LedBlinker");

/*
 * Application entry point.
 */
int main(void)
{
	/*
	 * System initializations.
	 * - HAL initialization, this also initializes the configured device drivers
	 *   and performs the board-specific initializations.
	 * - Kernel initialization, the main() function becomes a thread and the
	 *   RTOS is active.
	 */
	halInit();
	chibios_rt::System::init();

	// Initialize Serial-USB driver
	sduObjectInit(&SDU1);
	sduStart(&SDU1, &serusbcfg);

	/*
	 * Activates the USB driver and then the USB bus pull-up on D+.
	 * Note, a delay is inserted in order to not have to disconnect the cable
	 * after a reset.
	 */
	usbDisconnectBus(serusbcfg.usbp);
	chThdSleepMilliseconds(1500);
	usbStart(serusbcfg.usbp, &usbcfg);
	usbConnectBus(serusbcfg.usbp);

  PidParam pbPidParam = PidParam_init_zero;
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  pbPidParam.p = 0.;
  pbPidParam.i = 0.;
  pbPidParam.d = 0.;
  bool status = pb_encode(&stream, PidParam_fields, &pbPidParam);
  size_t messageLength = stream.bytes_written;
  streamWrite(chp, buffer, messageLength);

	ledBlinker.start(NORMALPRIO + 10);
  float number = 0.;
	while(1)
	{
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    pbPidParam.p = number;
    pbPidParam.i = number;
    pbPidParam.d = number;
    status = pb_encode(&stream, PidParam_fields, &pbPidParam);
    messageLength = stream.bytes_written;
    streamWrite(chp, buffer, messageLength);
    // chprintf(chp, "Number of bytes written : %d\n", messageLength);
    number += 1.;
		chThdSleepMilliseconds(5);
	}
}