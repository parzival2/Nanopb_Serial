#include "ch.hpp"
#include "hal.h"

class LedBlinkerThread : public chibios_rt::BaseStaticThread<256>
{
  public:
	LedBlinkerThread(const char* threadName)
		: chibios_rt::BaseStaticThread<256>()
		, mThreadName(threadName)
	{
	}

  protected:
	void main(void) override
	{
		this->setName(mThreadName);

		while(TRUE)
		{
			palTogglePad(GPIOC, GPIOC_LED);
			chThdSleepMilliseconds(200);
		}
	}

  private:
	const char* mThreadName;
};
