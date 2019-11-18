#include "EntryGuard.h"
#include "ExitGuard.h"
#include "Car.h"
#include <osapi/Thread.hpp>

int main(){
	srand(time(0));

	EntryGuard entry;
	ExitGuard exit;
	Car car1(&entry, &exit, 1);
	Car car2(&entry, &exit, 2);

	{
		osapi::Thread car1Thread(&car1);
		osapi::Thread car2Thread(&car2);
		osapi::Thread entryThread(&entry);
		osapi::Thread exitThread(&exit);

		car1Thread.start();
		car2Thread.start();
		entryThread.start();
		exitThread.start();

		car1Thread.join();
		car2Thread.join();
		entryThread.join();
		exitThread.join();
	}

	return 0;
}
