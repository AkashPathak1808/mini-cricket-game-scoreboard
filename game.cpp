#include "game.h"
using namespace std;

Game::Game() {
	playersPerTeam = 4;
	maxBalls = 6;
	totalPlayers = 11;
	
	players[0] = "Virat";
	players[1] = "Rohit";
	players[2] = "Dhawan";
	players[3] = "Pant";
	players[4] = "Karthik";
	players[5] = "KLRahul";
	players[6] = "Jadeja";
	players[7] = "Hardik";
	players[8] = "Bumrah";
	players[9] = "BKumar";
	players[10] = "Ishant";
	
	isFirstInnings = false;
	teamA.name = "Team-A";
	teamB.name = "Team-B";
	
}

void Game::welcome() {
	cout<<"------------------------------"<<endl<<endl;
	cout<<"=======WELCOME IN CRIC-11======="<<endl<<endl;
	cout<<"------------------------------"<<endl<<endl;
	
	cout<<endl<<endl;
	
	cout<<"------------------------------"<<endl;
	cout<<"=========INSTRUCTION========="<<endl<<endl;
	cout<<"1. Create 2 teams (Team-A and Team-B with 4 players each) from a given pool of 11 players." << endl;
    cout <<"2. Lead the toss and decide the choice of play."<< endl;
    cout <<"3. Each innings will be of 6 balls."<< endl;
    cout<<"------------------------------"<<endl;
    
	cout<<endl;
	
}

void Game::showAllPlayers() {
	cout<<"------------------------------"<<endl;
	cout<<"==========PLAYERS=========="<<endl;
	for(int i=0;i<11;i++){
		cout<<i<<"."<<players[i]<<endl;
	}
	
}

int Game::takeIntegerInput() {
	int n;
	while(!(cin>>n)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<<"Invalid input.Please try again with valid input.....";			
	}
	return n;
}

bool Game::validateSelectedPlayer(int index) {

	int n;
	vector<Player> players;

	players = teamA.players;
	n = players.size();
	for (int i=0; i<n; i++) {
        if (players[i].id == index) {
        	return false;
        }
    }

    players = teamB.players;
    n = players.size();
    for (int i=0; i<n; i++) {
        if (players[i].id == index) {
            return false;
        }
    }

    return true;
}

void Game::selectPlayers() {

	cout<<endl;
	cout<<"------------------------------------------------"<<endl;
	cout<<"|========== Create Team-A and Team-B ==========|"<< endl;
	cout <<"------------------------------------------------"<< endl;

	for (int i = 0; i < playersPerTeam; i++) {

		// Add player to team A
		teamASelection:
			cout << endl << "Select player " << i + 1 << " of Team A - ";
			int playerIndexTeamA = takeIntegerInput();

			if (playerIndexTeamA < 0 || playerIndexTeamA > 10) {
				cout << endl << "Please select from the given players" << endl;
				goto teamASelection;
			}else if(!validateSelectedPlayer(playerIndexTeamA)){
				cout<<endl<<"Player has been already selected.Please selet other player...."<<endl;
				goto teamASelection;
			}else {
				Player teamAPlayer;
				teamAPlayer.id = playerIndexTeamA;
				teamAPlayer.name = players[playerIndexTeamA];
				teamA.players.push_back(teamAPlayer);
			}

		// Add player to team B
		teamBSelection:
			cout << endl << "Select player " << i + 1 << " of Team B - ";
			int playerIndexTeamB = takeIntegerInput();

			if (playerIndexTeamB < 0 || playerIndexTeamB > 10) {
				cout << endl << "Please select from the given players" << endl;
				goto teamBSelection;
			}else if(!validateSelectedPlayer(playerIndexTeamB)){
				cout<<endl<<"Player has been already selected.Please selet other player...."<<endl;
				goto teamBSelection;
			}else {
				Player teamBPlayer;
				teamBPlayer.name = players[playerIndexTeamB];
				teamB.players.push_back(teamBPlayer);
			}
	}
}

void Game::showTeamPlayer() {
	vector<Player> teamAPlayers = teamA.players;
	vector<Player> teamBPlayers = teamB.players;
	
	cout<<endl;
	
	cout<<"------------------------------"<<endl;
	cout<<"====Team-A====\t====Team-B===="<<endl;
	cout<<"------------------------------"<<endl;
	
	for(int i=0; i<playersPerTeam; i++){
		cout<<"["<<i<<"] "<<teamAPlayers[i].name<<"\t"<<"["<<i<<"] "<<teamBPlayers[i].name<<endl;
	}
}

void Game::toss() {
	cout<<endl;
	cout<<"------------------------------"<<endl;
	cout<<"==========Let's Toss=========="<<endl;
	cout<<"------------------------------"<<endl;
	cout<<"Tossing the coin...."<<endl<<endl;
	
	srand(time(NULL));
	int randomValue = rand() % 2;
	
	switch(randomValue) {
		case 0:
			cout<<"Team-A won the toss"<<endl;
			tossChoice(teamA);
			break;
		
		case 1:
			cout<<"Team-B won the toss"<<endl;
			tossChoice(teamB);
			break;
				
	}
}

void Game::tossChoice(Team tossWinnerTeam) {
	cout<<"Enter 1 to bat OR 2 to bowl first...."<<endl;
	cout<<"1. Bat"<<endl<<"2. Bowl"<<endl;
	
	int tossInput = takeIntegerInput();
	
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	
	switch(tossInput) {
		case 1:
			cout<<endl<<tossWinnerTeam.name<<" won the toss and elected to bat first.."<<endl<<endl;
			
			if(tossWinnerTeam.name.compare("Team-A")==0) { 		// if Team-A is the toss winner
			battingTeam = &teamA;
			bowlingTeam = &teamB;
			} 
			else{		// else Team-B is the toss winner
				battingTeam = &teamB;
				bowlingTeam = &teamA;
			}
			
			break;
			
		case 2:
			cout<<endl<<tossWinnerTeam.name<<" won the toss and elected to bowl first.."<<endl<<endl;
			
			if(tossWinnerTeam.name.compare("Team-A")==0) {		// if Team-A is the toss winner
				bowlingTeam = &teamA;
				battingTeam = &teamB;
			}	
			else{		// else Team-B is the toss winner
				bowlingTeam = &teamB;
				battingTeam = &teamA;
			}
			
			break;
			
		default:
			cout<<endl<<"Invalid input. Please try again:"<<endl;
			tossChoice(tossWinnerTeam);
			break;	
	}
}

void Game::startFirstInnings() {
	cout<<"Start First Innings......."<<endl<<endl;
	isFirstInnings = true;
	initializePlayers();
}

void Game::initializePlayers() {
	batsman = &battingTeam->players[0];
	bowler = &bowlingTeam->players[0];
	
	cout<<battingTeam->name<<" "<<batsman->name<<" is batting."<<endl;
	cout<<bowlingTeam->name<<" "<<bowler->name<<" is bowling."<<endl<<endl<<endl;
}

void Game::playInnings() {
	for(int i=0;i<maxBalls;i++){
		cout<<"Press Enter To Bowl.."<<endl;
		getchar();
		cout<<"Bowling..."<<endl;
		
		bat();
		
		if(!validateInningsScore()){
			break;
		}
	}
}

void Game::bat() {
	srand(time(NULL));
	int runsScored = rand() % 7;
	
	batsman->runsScored = batsman->runsScored+runsScored;
	battingTeam->totalRunsScored = battingTeam->totalRunsScored+runsScored;
	batsman->ballsPlayed = batsman->ballsPlayed+1;
	
	bowler->ballsBowled = bowler->ballsBowled+1;
	bowlingTeam->totalBallsBowled = bowlingTeam->totalBallsBowled+1;
	bowler->runsGiven = bowler->runsGiven+runsScored;
	
	if(runsScored!=0){
		cout<<endl<<bowler->name<<" to "<<batsman->name <<" "<<runsScored<<" runs!"<<endl<<endl;
		showGameScoreCard();
	}else{
		cout<<endl<<bowler->name<<" to "<<batsman->name<<" OUT "<<endl<<endl;
		
		battingTeam->wicketLost = battingTeam->wicketLost+1;
		bowler->wicketsTaken = bowler->wicketsTaken+1;
		
		showGameScoreCard();
		
		int nextPlayerIndex = battingTeam->wicketLost;
		batsman = &battingTeam->players[nextPlayerIndex];
	}
}

bool Game::validateInningsScore() {
	if(isFirstInnings) {
		if(battingTeam->wicketLost == playersPerTeam || bowlingTeam->totalBallsBowled == maxBalls) {
			cout<<"\tFIRST INNINGS ENDS"<<endl<<endl;

			cout<<battingTeam->name<<" "<<battingTeam->totalRunsScored<<" - "<<battingTeam->wicketLost<<" ("<< bowlingTeam->totalBallsBowled<<")"<< endl;

			cout<<bowlingTeam->name <<" needs "<<battingTeam->totalRunsScored + 1<<" runs to win the match"<<endl<<endl;
		
			return false;
		} else{
		    
		}
	}
	return true;
}

void Game::showGameScoreCard() {
	cout<<"------------------------------------------------------------"<<endl;
	cout<<battingTeam->name<<" "<<battingTeam->totalRunsScored<<" - "<<battingTeam->wicketLost<<" ("<<bowlingTeam->totalBallsBowled<<") "<<"\t"<<batsman->name<<" "<<batsman->runsScored<<" ("<<batsman->ballsPlayed<<") "<<"\t"<<bowler->name<<" "<<bowler->ballsBowled<<" - "<<bowler->runsGiven<<" - "<<bowler->wicketsTaken<<endl;
		cout<<"------------------------------------------------------------"<<endl<<endl;
}

void Game::startSecondInnings() {
    swap(*battingTeam, *bowlingTeam);    
    cout<<"Start Second Innings.."<<endl<<endl;
    initializePlayers();
    playSecondInnings();
}

void Game::playSecondInnings() {
	for(int i=0;i<maxBalls;i++){
		cout<<"Press Enter To Bowl.."<<endl;
		getchar();
		cout<<"Bowling..."<<endl;
		
		bat();
		
		if(!validateSecondInningsScore()){
			break;
		}
	}
}

bool Game::validateSecondInningsScore() {
    if(battingTeam->totalRunsScored > bowlingTeam->totalRunsScored||battingTeam->wicketLost == playersPerTeam){
       return false;
    }
    return true;
}

void Game::winner() {
    if(battingTeam->totalRunsScored > bowlingTeam->totalRunsScored){
        cout<<battingTeam->name<<" is winner.."<<endl<<endl;
    }else{
        if(battingTeam->totalRunsScored <= bowlingTeam->totalRunsScored){
        cout<<bowlingTeam->name<<" is winner.."<<endl<<endl;;
        }else{
            cout<<"TIE"<<endl<<endl;;
        }
    }
}

void Game::matchSummary() {
    swap(*battingTeam, *bowlingTeam);
    cout<<"-----------------------------"<<endl;
    cout<<"=========MATCH ENDS========="<<endl;
    cout<<"-----------------------------"<<endl<<endl;
    
    vector<Player> teamAPlayers = teamA.players;
	vector<Player> teamBPlayers = teamB.players;
	
	cout<<"\t"<<teamA.name<<" "<<teamA.totalRunsScored<<"-"<<teamA.wicketLost<<"("<<teamA.totalBallsBowled<<")"<<endl;
    cout<<"======================================="<<endl;
    cout<<ends<<"PLAYER"<<"\t\t"<<"BATTING"<<"\t"<<"\t"<<"BOWLING"<<endl;
    cout<<"======================================="<<endl;
    for(int i=0; i<playersPerTeam; i++){
		cout<<"["<<i<<"] "<<teamAPlayers[i].name<<"\t"<<teamAPlayers[i].runsScored<<"("<<teamAPlayers[i].ballsPlayed<<")"<<"\t\t"<<teamAPlayers[i].ballsBowled<<"-"<<teamAPlayers[i].runsGiven<<"-"<<teamAPlayers[i].wicketsTaken<<endl;
        cout<<"---------------------------------------"<<endl;
    }
    cout<<"======================================="<<endl;
    
    cout<<endl<<endl;
    
    cout<<"\t"<<teamB.name<<" "<<teamB.totalRunsScored<<"-"<<teamB.wicketLost<<"("<<teamB.totalBallsBowled<<")"<<endl;
    cout<<"======================================="<<endl;
    cout<<ends<<"PLAYER"<<"\t\t"<<"BATTING"<<"\t\t"<<"BOWLING"<<endl;
    cout<<"======================================="<<endl;
    for(int i=0; i<playersPerTeam; i++){
	    cout<<"["<<i<<"] "<<teamBPlayers[i].name<<"\t"<<teamBPlayers[i].runsScored<<"("<<teamBPlayers[i].ballsPlayed<<")"<<"\t\t"<<teamBPlayers[i].ballsBowled<<"-"<<teamBPlayers[i].runsGiven<<"-"<<teamBPlayers[i].wicketsTaken<<endl;
        cout<<"---------------------------------------"<<endl;
	}
	cout<<"======================================="<<endl;
	
}




