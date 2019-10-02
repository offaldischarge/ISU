/* Two mutexes with each their own condition variable.
   Car entering does not need to wait for car entering. */
pthread_mutEntry_t mutEntry = initialize;
pthread_mutEntry_t mutExit = initialize;

pthread_cont_t entry = initialize;
pthread_cont_t exit = initialize;

carThread(){

	/* Continuosly go in and out of PLCS */
	while(true){
		/* Entry */
		driveUpToEntry();

		lock(mutEntry);

		carWaitingToEnter = true;
		condSignal(entry);

		while(!parkEntryOpen){		 //mitigate spurios wake ups
			condWait(entry, mutEntry)); //block until park entry is open
		}

		driveCarInPLCS();
		carWaitingToEnter = false;
		condSignal(entry);

		unlock(mutEntry);

		/* Car entered PLCS */

		wait();						// waits for a bit inside the parking

		/* Exit */
		driveUpToExit();

		lock(mutExit);

		carWaitingToExit = true;
		condSignal(exit);

		while(!parkExitOpen){
			condWait(exit, mutExit);
		}

		driveOutOfPLCS();
		carWaitingToExit = false;
		condSignal(exit);

		unlock(mutExit);

		/* Car exited PLCS */

		wait();						//wait a bit outside parking lot before entering again
	}
}


PLCSentryControllerThread(){
	lock(mutEntry);

	while(!carWaitingToEnter){
		condWait(entry, mutEntry); //block until car is no longer waiting
	}

	openEntryDoor();
	parkEntryOpen = true;
	condSignal(entry);

	while(carWaitingToEnter){
		condWait(entry, mutEntry);
	}

	closeEntryDoor();
	parkEntryOpen = false;

	unlock(mutEntry);
}

PLCSexitControllerThread(){
	lock(mutExit);

	while(!carWaitingToExit){
		condWait(exit, mutExit); //block until car is no longer waiting
	}

	openExitDoor();
	parkExitOpen = true;
	condSignal(exit);

	while(carWaitingToExit){
		condWait(exit, mutExit);
	}

	closeExitDoor();
	parkExitOpen = false;

	unlock(mutExit);
}
