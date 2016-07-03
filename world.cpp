#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

#define NUM_PLAYERS 64

enum PrisonerResponse : bool {
	Cooperate = true,
	Defect = false
};

enum GameOutcome : int {
	Friends = 0,
	Sabotage = 1,
	Enemies = 2
};

class Player {
public:
	int score;
	string name;
	string type;
	
	Player() { 
		static int existing_player_count = 0;

		score = 0;
		
		ostringstream oss;
		oss << existing_player_count;
		name = oss.str();
		type = "Random";
		
		existing_player_count++;
	}

	PrisonerResponse prisoners_dilemna() {
		return (PrisonerResponse)(rand() % 2);
	}

	void inform_outcome(GameOutcome outcome) {}
};

class Samaritan : public Player {
public:
	Samaritan() {
		type = "Samaritan";
	}

	PrisonerResponse prisoners_dilemna() {
		return Cooperate;
	}
};

class Villain : public Player {
public:
	Villain() {
		type = "Villain";
	}

	PrisonerResponse prisoners_dilemna() {
		return Defect;
	}
};

class Grudger : public Player {
private:
	bool grudged = false;
public:
	Grudger() {
		type = "Grudger";
	}

	PrisonerResponse prisoners_dilemna() {
		if (grudged) return Defect;
		return Cooperate;
	}

	void inform_outcome(GameOutcome outcome) {
		//if the other player acted against us, hold a grudge
		if (outcome != Friends) grudged = true;
	}
};

GameOutcome determine_outcome(bool me_coop, bool you_coop) {
	//if both cooperate, cooperation win
	if (me_coop && you_coop) return Friends;
	//if neither cooperated, enemies
	else if (!me_coop && !you_coop) return Enemies;
	//otherone, one of them defected
	else return Sabotage;
}

void play_game(Player* me, Player* you) {
	//seed game for any players that use rand
	//srand(time(0));

	PrisonerResponse me_coop = me->prisoners_dilemna();
	PrisonerResponse you_coop = you->prisoners_dilemna();
	GameOutcome outcome = determine_outcome(me->prisoners_dilemna(), you->prisoners_dilemna());

	//inform each player of game outcome
	me->inform_outcome(outcome);
	you->inform_outcome(outcome);

	//if players cooperated, both get 3 points
	if (outcome == Friends) {
		//cout << me->name << ", " << you->name << " cooperated." << endl;
		me->score += 3;
		you->score += 3;
	}
	else {
		//if someone defected alone, they get 5 points
		if (outcome == Sabotage && !me_coop) {
			me->score += 5;
		}
		else if (outcome == Sabotage && !you_coop) {
			you->score += 5;
		}
		//if both defected, they only get 1 point
		else {
			me->score++;
			you->score++;
		}
	}
			
}

bool score_sort(pair<string, unsigned> first, pair<string, unsigned> second) {
	if (first.second > second.second) return true;
	return false;
}

void score_display(Player* (&players)[NUM_PLAYERS]) {

	map<string, unsigned> scores;
	for (unsigned i = 0; i < NUM_PLAYERS; i++) {
		Player* player = players[i];
		scores[player->type] += player->score;

		//cout << player->type << " (" << player->name << "): " << player->score << endl;
	}

	cout << "-------Scoreboard---------" << endl;
	//sort scores by score values
	vector<pair<string, unsigned> > pairs(scores.begin(), scores.end());
	sort(pairs.begin(), pairs.end(), &score_sort);
	for (pair<string, unsigned> &pair : pairs) {
		cout << pair.first << ": " << pair.second << endl;
	}
}

void world_play(Player* (&players)[NUM_PLAYERS]) {
	//run a life for every player and add to their cumulative score
	for (unsigned i = 0; i < NUM_PLAYERS - 1; i+= 2) {
		//TODO match players randomly, while only playing one player per turn
		//let this player run a game
		play_game(players[i], players[i+1]);
	}
}

int main(void) {
	srand(time(0));

	Player* players[NUM_PLAYERS];

	unsigned turn = 0;
	//initialize players
	for (unsigned i = 0; i < NUM_PLAYERS; i++) {
		switch (turn) {
			case 0:
				players[i] = new Player();
				break;
			case 1:
				players[i] = new Samaritan();
				break;
			case 2:
				players[i] = new Villain();
				break;
			case 3:
				players[i] = new Grudger();
				break;
			default:
				//reset turns and try again
				turn = 0;
				i--;
				continue;
				break;

		}
		turn++;
	}

	for (unsigned i = 0; i < 10; i++) {
		//run world for a lifetime
		world_play(players);
	}

	//log current scores
	score_display(players);
	
	return 0;
}
