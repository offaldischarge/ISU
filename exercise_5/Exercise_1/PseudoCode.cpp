/* Two mutexes with each their own condition variable.
   Car entering does not need to wait for car entering. */
pthread_mutex_t mutexEntry = initialize;
pthread_mutex_t mutexExit = initialize;

pthread_cont_t entry = initialize;
pthread_cont_t exit = initialize;

bool carWaitingToEnter,carWaitingToExit = false;
bool entryGuardOpen, exitGuardOpen = false;

carThread(){
	/* Continuosly go in and out of PLCS */
	while(true){
		/* Entry */
		lock(mutEntry);

		driveUpToEntry();

		carWaitingToEnter = true;
		condSignal(entry);

		while(!entryGuardOpen){		 //mitigate spurios wake ups
			condWait(entry, mutEntry)); //block until park entry is open
		}

		driveCarInPLCS();

		carWaitingToEnter = false;
		condSignal(entry);

		unlock(mutEntry);

		/* Car entered PLCS */

		wait();	// waits for a bit inside the parking

		/* Exit */
		lock(mutExit);

		driveUpToExit();

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

		wait();	//wait a bit outside parking lot before entering again
	}
}


PLCSentryControllerThread(){

	while(true){
		lock(mutEntry);

		while(!carWaitingToEnter){
			condWait(entry, mutEntry); //block until car is no longer waiting
		}

		openEntryDoor();

		entryGuardOpen = true;
		condSignal(entry);

		while(carWaitingToEnter){
			condWait(entry, mutEntry);
		}

		closeEntryDoor();

		entryGuardOpen = false;

		unlock(mutEntry);
	}

}

PLCSexitControllerThread(){

	while(true){
		lock(mutExit);

		while(!carWaitingToExit){
			condWait(exit, mutExit); //block until car is no longer waiting
		}

		openExitDoor();

		exitGuardOpen = true;
		condSignal(exit);

		while(carWaitingToExit){
			condWait(exit, mutExit);
		}

		closeExitDoor();

		exitGuardOpen = false;

		unlock(mutExit);
	}
	
}
