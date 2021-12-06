#include<vector>
#include "player.h"  //string.h

class Team {
	public:
		
		Team();
		std::string name;
		int totalRunsScored;
		int wicketLost;
		int totalBallsBowled;
		std::vector<Player> players;
	
};
