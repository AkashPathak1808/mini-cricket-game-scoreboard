#include "game.h"
using namespace std;

int main() {
	Game game;
	game.welcome();
	
	cout << "\nPress Enter to continue";
	getchar();

    game.showAllPlayers();
    
    cout << "\nPress Enter to continue";
	getchar();
	
	game.selectPlayers();
	
	game.showTeamPlayer();
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	cout<<"\n Press Enter to toss....";
	getchar();
	game.toss();
	
	cout << "\nPress Enter to START FIRST INNING...";
	getchar();
	game.startFirstInnings(); 
	
	game.playInnings();
	
	cout << "\nPress Enter to START SECOND INNING...";
	getchar();
	game.startSecondInnings();
	
    game.winner();
    
    cout << "\nPress Enter to Match Summary...";
	getchar();
    game.matchSummary();
	
		   
    return 0;
    
}
