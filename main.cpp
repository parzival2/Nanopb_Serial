#include "LedBlinkerThread.hpp"
#include "ch.hpp"
#include "chprintf.h"
#include "hal.h"
#include "messages.pb.h"
#include "pb_encode.h"
#include "usbcfg.h"

BaseSequentialStream* chp = (BaseSequentialStream*)(&SDU1);
LedBlinkerThread ledBlinker("LedBlinker");
// Define a buffer
static constexpr uint8_t BUFFER_LENGTH = 128;
uint8_t buffer[BUFFER_LENGTH];

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
	// Send the message every 100 milliseconds
	// Define messages to be written
	Message1 msg1 = Message1_init_zero;
	Message2 msg2 = Message2_init_zero;
	size_t msgLength;
	int32_t number = 0;
	while(true)
	{
		// Write the message
		pb_ostream_t msgStream1 = pb_ostream_from_buffer(buffer, sizeof(buffer));
		// Set the ID
		msg1.id = MessageID::MessageID_Message1ID;
		// Set the data
		msg1.intvalue = number;
		// We will also set the id infront of the message to that we can identify
		// it after receiving
		pb_encode_varint(&msgStream1, static_cast<uint64_t>(msg1.id));
		pb_encode(&msgStream1, Message1_fields, &msg1);
		msgLength = msgStream1.bytes_written;
		streamWrite(chp, buffer, msgLength);
		chThdSleepMilliseconds(100);
		// Send second message
		pb_ostream_t msgStream2 = pb_ostream_from_buffer(buffer, sizeof(buffer));
		// Set the id
		msg2.id = MessageID::MessageID_Message2ID;
		msg2.intvalue = number;
		// Right now the options for nanopb seems to not work properly when
		// nanopb.cmake is used. Ignore it for now.
		pb_encode_varint(&msgStream2, static_cast<uint64_t>(msg2.id));
		pb_encode(&msgStream2, Message2_fields, &msg2);
		msgLength = msgStream2.bytes_written;
		streamWrite(chp, buffer, msgLength);
		chThdSleepMilliseconds(100);
		number += 1;
	}
}
