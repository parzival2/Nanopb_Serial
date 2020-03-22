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
#include <stdlib.h>
#include "LedBlinkerThread.hpp"
#include "ch.hpp"
#include "chprintf.h"
#include "hal.h"
#include "pb_encode.h"
#include "usbcfg.h"
#include "messages.pb.h"
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

	ledBlinker.start(NORMALPRIO + 10);
	// Define the message
	Message1 message1 = Message1_init_zero;
	Message2 message2 = Message2_init_zero;
	Message3 message3 = Message3_init_zero;
	size_t msgLength;
	while(1)
	{
		// chprintf(chp, "Number of bytes written : %d\n", messageLength);
		// First write the fist message
		pb_ostream_t stream1 = pb_ostream_from_buffer(buffer, sizeof(buffer));
		message1.intvalue = rand() % 100;
		message1.messageid = Message1_messageid_tag;
		pb_encode_varint(&stream1, message1.messageid);
		bool status = pb_encode(&stream1, Message1_fields, &message1);
		msgLength = stream1.bytes_written;
		streamWrite(chp, buffer, msgLength); 
		chThdSleepMilliseconds(100);
		// Send second message
		pb_ostream_t stream2 = pb_ostream_from_buffer(buffer, sizeof(buffer));
		message2.intvalue = rand() % 100;
		message2.messageid = Message2_messageid_tag;
		pb_encode(&stream2, Message2_fields, &message2);
		msgLength = stream2.bytes_written;
		streamWrite(chp, buffer, msgLength);
		chThdSleepMilliseconds(100);
	}
}