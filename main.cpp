#include "ch.hpp"
#include "hal.h"
#include "LedBlinkerThread.hpp"
#include "chprintf.h"
#include "usbcfg.h"


BaseSequentialStream* chp = (BaseSequentialStream*)(&SDU1);
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

	while(true)
	{
		chprintf(chp, "Hello from bluepill\n");
		chThdSleepMilliseconds(100);
	}
}
