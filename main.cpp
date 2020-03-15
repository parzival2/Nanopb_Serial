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

#include "ch.hpp"
#include "hal.h"
#include "usbcfg.h"
#include "chprintf.h"

BaseSequentialStream *chp = (BaseSequentialStream *)(&SDU1);

/* Thread definition */
static THD_WORKING_AREA(changeDirection, 128);
static THD_FUNCTION(dirThread, arg){
	(void)arg;
	/* Set thread name */
	chRegSetThreadName("dirThread");
	/* Thread should not return, so begin a while loop */
	while(TRUE)
	{
        palTogglePad(GPIOA, 5);
		chThdSleepMilliseconds(250);
	}
}


/*
 * Application entry point.
 */
int main(void) {

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
  chThdCreateStatic(changeDirection, sizeof(changeDirection),
                    NORMALPRIO+1, dirThread, NULL);
  while (1) {
     chThdSleepMilliseconds(5);
  }
}