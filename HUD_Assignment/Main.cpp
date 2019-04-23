#include "GameManager.h"



int main(int argc, char* args[]) {

	//Creating a game manager as a smart pointer
	auto gm = std::unique_ptr<GameManager>(new GameManager());

	//runs the game manager's onCreate function and obtains a status on whether it was successfully initialised
	bool status = gm->OnCreate();

	//checks if gm was initialised successfully
	if (status) {
		//if it was successful, execute gm's run function
		gm->Run();
	}

	//if not successful, alerts the user and does not start the program
	else if (!status) {
		std::cerr << "Fatal error occured. Cannot start this program" << std::endl;
	}

	//close console
	return 0;
}