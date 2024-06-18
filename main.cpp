/****************************
 * Yatzhee!
 * System: VSCode on MacIOS
 * Author: Nuha Abougoash
 * ***************************/
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <iomanip>
#include <ctime>
#include <vector>

using namespace std;

class Dice {
	private:
		int value;
        bool keep;
	public:

		//Randomly assigns a value between from 1 to 6 to the dice.
		void roll();
		int reveal() {return value;}
        void diceToKeep() {
			keep = true; //if user selected to keep the dice, set true
		};
        void diceNotToKeep() {
    		keep = false; //if user selected to NOT keep the dice, set false
		};    
        bool getKeep() {
    		return keep;
		};        
		//The autograder will set the values directly instead of calling roll() to avoid randomness!
		void setValue(int value) {this->value = value;}

};

void Dice::roll() {
    value = (rand() % 6) + 1; //randomly rolls dice from 1-6
}
//#################################################################################################

const int HAND_SIZE = 5;

class Hand {
	public:
		//Display the value of the five dice
		void show();	
		void play();

		Dice* getDice(int diceNum) {
            return &arrayDice[diceNum]; //this finds the position of arraydice and points to the address 
        };
		
		//selection is the string of dice numbers that the player wants to keep.
		void setSelection(string selection);	

		Hand();	 //the dice that was not chosen will be kept in the hand of the player
	
	private:
        Dice arrayDice[HAND_SIZE]; //creates array for dice
};

void Hand::show(){
	for ( int i = 0; i < HAND_SIZE; i++) {
		cout << arrayDice[i].reveal(); //reveal the value of the dice
	}
	cout << endl;
}

void Hand::play(){
	for (int i = 0; i < HAND_SIZE; i++) {
		if (arrayDice[i].getKeep() == false) {
			arrayDice[i].roll();
		} //if user decides not to keep the dice then it will go back to rolling the dice
	}
}

void Hand::setSelection(string selection) { 
	for (int i = 0; i < selection.size(); i++) {
		int selectedDice = selection[i] - '0' - 1; //selected die is the index of die the player chose to keep
		if (selectedDice >= HAND_SIZE) {
			continue;
		}
		arrayDice[selectedDice].diceToKeep(); //set array to keep the same number at the corresponding index for when player rolls again
	}
}

Hand::Hand() {
	for ( int i=0; i < HAND_SIZE; i++) {
		arrayDice[i].diceNotToKeep(); //set array at index i to dice not kept
	}
}
//######################################################################

//List of rows in the board
const int ONES = 0;
const int TWOS = 1;
const int THREES = 2;
const int FOURS = 3;
const int FIVES = 4;
const int SIXES = 5;
const int THREE_OF_KIND = 6;
const int FOUR_OF_KIND = 7;
const int FULL_HOUSE = 8;
const int SMALL_STRAIGHT = 9;
const int LARGE_STRAIGHT = 10;
const int CHANCE = 11;
const int YAHTZEE = 12;

const int BOARD_SIZE=13; 

class Game {
	public:
		// function to calculate the number of dice in each row
		int upper_board(Hand* hand, int row) {
			int score = 0;
			for (int i = 0; i < HAND_SIZE; i++) { 
				int diceNum = hand->getDice(i)->reveal();
				if (diceNum == row){ 
					score += row; 
				}
			}
			return score;
		}; 

		//calcScore returns a score of a hand (5 dice) for given row in the board. 
		int calcScore(Hand* hand, int row);

		//Display the board 
		void show() {
			//Print the board and set specificied width to create appropriate amount of whitespace
			//Call scoreBoard to print the appropriate score
            cout << " 1. Ones:" << setw(19) << scoreBoard(ONES) << endl;
            cout << " 2. Twos:" << setw(19) << scoreBoard(TWOS) << endl;
            cout << " 3. Three:" << setw(18) << scoreBoard(THREES) << endl;
            cout << " 4. Fours:" << setw(18) << scoreBoard(FOURS) << endl;
            cout << " 5. Fives:" << setw(18) << scoreBoard(FIVES) << endl;
            cout << " 6. Sixes:" << setw(18) << scoreBoard(SIXES) << endl;
			cout << "    Sum:" << setw(20) << getUpperScore() << endl;
        	cout << "    Bonus:" << setw(18) << getBonusScore() << endl;
            cout << " 7. Three of a kind:" << setw(8) << scoreBoard(THREE_OF_KIND) << endl;
            cout << " 8. Four of a kind:" << setw(9) << scoreBoard(FOUR_OF_KIND) << endl;
            cout << " 9. Full house:" << setw(13) << scoreBoard(FULL_HOUSE) << endl;
            cout << "10. Small stright:" << setw(10) << scoreBoard(SMALL_STRAIGHT) << endl;
            cout << "11. Large Straight:" << setw(9) << scoreBoard(LARGE_STRAIGHT) << endl;
            cout << "12. Chance:" << setw(17) << scoreBoard(CHANCE) << endl;
            cout << "13. Yatzhee:" << setw(16) << scoreBoard(YAHTZEE) << endl;
            cout << "Total: " << setw(21) << getTotalScore() << endl;
        }; 

		//Changes the board display from '-' to appropriate score
		string scoreBoard(int row) {
			if (arrayBoard[row] == -1) {
				return "-";
			}
			else {
				return to_string(arrayBoard[row]); //change to string
			}
    	};
		
		//Check isPlayed and isFinished functions
		Game() {
			for (int i = 0; i < BOARD_SIZE; i++) {
				arrayBoard[i] = -1;
			}
		};

		//Returns the score of the upper part of the board
		int getUpperScore() {
			int upperTotal = 0;
			for (int i = 0; i < 6; i++) {
				if( arrayBoard[i] != -1){
					upperTotal += arrayBoard[i];
				}
			}
			return upperTotal;
		}; 
		
		//Returns the score of the lower part of the board
		int getLowerScore() {
			int lowerTotal = 0;
			for (int i = 6; i < BOARD_SIZE; i++) {
				if (arrayBoard[i] != -1) {
					lowerTotal += arrayBoard[i];
				}
			}
			return lowerTotal;
		}; 
	
		//Returns the bonus points
		int getBonusScore() {
			//if player score more than 63 in their upper board
			if(getUpperScore( )>= 63) {
				return 35; //player gains 35 points
			}
			return 0;
		}; 

		//Returns the total score
		int getTotalScore() {
			//add uppper and lower and bonus
			int total = getUpperScore()+getLowerScore()+getBonusScore();
			return total;
		}; 

		//Play a hand based on the selected row
		void play(Hand* hand, int row) {
			arrayBoard[row] = calcScore(hand, row);
		}; 
        
		//Check to see if a row has been played or not (returns true if a row has been played)
		bool isPlayed(int row) {
			if (arrayBoard[row]!= -1) {
				return true;
			}
			return false;	
		};
		
		//Check to see if all rows haven been played or not (returns true if all rows have been played)
		bool isFinished() {
        for (int row = 0; row < BOARD_SIZE; row++) {
            if (!isPlayed(row)) {
                return false; //return false if isPlayed fucntion is also false
            }
        }
        return true;
    };

	private:
		int arrayBoard[BOARD_SIZE]; //creates an array that is the sixe of the board  
};

int Game::calcScore(Hand*hand, int row) {
	int counterArray[6]{0,0,0,0,0,0}; //initalize an empty array

	//Calculate first six rows
	//The upper board function is called to calculate the score for the first six rows
	if (row == ONES) {
		return upper_board(hand, 1); 
	}
	if (row == TWOS) {
		return upper_board(hand, 2); 
	}
	if (row == THREES) {
		return upper_board(hand, 3); 
	}
	if (row == FOURS) {
		return upper_board(hand, 4);
	}
	if (row == FIVES) {
		return upper_board(hand, 5); 
	}
	if (row == SIXES) {
		return upper_board(hand, 6); 
	}

	//this for loop increments the array by one each time there is a number at the corresponding index
	for (int i = 0; i < HAND_SIZE; i++) {
		int diceNum = hand->getDice(i)->reveal(); //diceNum variable grabs the dice number in users hand
		if (diceNum == 1) {
			counterArray[0] += 1; 
		}
		if (diceNum == 2) { 
			counterArray[1] += 1; 
		}
		if (diceNum == 3) { 
			counterArray[2] += 1;
		}
		if (diceNum == 4) { 
			counterArray[3] += 1;
		}
		if (diceNum == 5) {
			counterArray[4] += 1; 
		}
		if (diceNum == 6) {
			counterArray[5] += 1;
		}
	}
	
	//Calculate THREE_OF_KIND
	if (row == THREE_OF_KIND) {
		int sum = 0; //initialize sum
		for (int i = 0; i < 6; i++) {
			//if there is three of the same dice
			if (counterArray[i] >= 3) {
				for (int j = 0; j < HAND_SIZE; j++) {
					int diceNum = hand->getDice(j)->reveal();
					sum += diceNum; //sum of all the dice rolled 
				}
			}
		}
		return sum; //returns the score
	}
	
	//Calculate THREE_OF_KIND
	if (row == FOUR_OF_KIND) {
		int sum = 0; //initialize sum
		for (int i = 0; i < 6; i++) {
			//if there is four of the same dice
			if (counterArray[i] >= 4) {
				for (int j = 0; j < HAND_SIZE; j++) {
					int diceNum = hand->getDice(j)->reveal();
					sum += diceNum; //sum of all the dice rolled
				}
			}
		}
		return sum; //returns the score
	}

	//Calculate FULL_HOUSE
	if (row == FULL_HOUSE) {
		int sum1 = 0, sum2 = 0;
		int first = hand->getDice(0)->reveal();
		int second;

		//this loop will set second equal to the dice number if first is not
		for (int i = 0; i < HAND_SIZE; i++) {
			if (first != hand->getDice(i)->reveal()) { 
				second = hand->getDice(i)->reveal(); 
			}
		}
		
		for (int i = 0; i < HAND_SIZE; i++) {
			//if first is equal to dice number then increment the first sum
			if (first == hand->getDice(i)->reveal()) {
				sum1++; 
			}
			//if second is equal to dice number then increment the second sum
			else if (second == hand->getDice(i)->reveal()) {
				sum2++; 
			}
		}

		//if both sums add up to 5, then we know we have a three of kind and two of kind
		if (sum1 + sum2 == 5) { 
			return 25; //player gains 25 points
		}
		return 0;
	}

	//Calculate SMALL_STRAIGHT
	if (row == SMALL_STRAIGHT) {
		//If player rolls 3 sequential dice 1,2,3 or 2,3,4 or 3,4,5
		if (counterArray[0] >= 1) { 
			if ((counterArray[1] >= 1) && (counterArray[2] >= 1) && (counterArray[3] >= 1)) { 
				return 30; //player gains 30 points
			}
		}
		else if (counterArray[1] >= 1) { 
			if ((counterArray[2] >= 1) && (counterArray[3] >= 1) && (counterArray[4] >= 1)) { 
				return 30; //player gains 30 points
			}
		}
		else if (counterArray[2] >= 1) {
			if ((counterArray[3] >= 1) && (counterArray[4] >= 1) && (counterArray[5] >= 1)) { 
				return 30; //player gains 30 points
			}
		}
	}

	//Calculate LARGE_STRAIGHT
	if (row == LARGE_STRAIGHT) {
		//If player rolls four sequential dice 1,2,3,4 or 2,3,4,5
		if (counterArray[0] == 1) { 
			if ((counterArray[1] == 1) && (counterArray[2] == 1) && (counterArray[3]==1) && (counterArray[4] == 1)) {
				return 40; //player gains 40 points
			}
		}
		if (counterArray[1] == 1) {  
			if ((counterArray[2] == 1) && (counterArray[3] == 1) && (counterArray[4] == 1) && (counterArray[5] == 1)) { 
				return 40; //player gains 40 points
			}
		}
		return 0;
	}

	//Calculate CHANCE
	if (row == CHANCE) {
		int sum = 0;
		for (int i = 0; i < HAND_SIZE; i++) { 
			int diceNum = hand->getDice(i)->reveal();
			sum +=  diceNum; //add the sum of all the dice rolled
		}
		return sum; 
	}

	//Calculate YAHTZEE
	if (row == YAHTZEE) {
		for (int i = 0; i < 6; i++){
			//If five of the same dice are rolled
			if (counterArray[i] >= 5) {
				return 50; //the player gains 50 points
			}
		}
	}
}
//#######################################################################################

//The run function is the main loop of youther program
void run() {
	int row; //declare row variable
    Hand* hand = new Hand(); //call hand class
    Game* game= new Game(); //call game class
    game->show(); //display the board
    while (!game->isFinished()) { // as long as game is not finished
        
		hand->play(); // call play from Hand class, if the user does not want to keep dice then it will go back to rolling the dice again
        for (int i = 0; i < 2; i++) { //for loop to roll 3 times
            hand->show(); //reveals the value of the dice
            game->calcScore(hand,row);
            cout << "Keep Dice (s to stop rolling): ";
            string dicesKept; //declare string for dicesKepts
            cin >> dicesKept;
            hand->setSelection(dicesKept);
            hand->play();
        }
		
        hand->show(); //reveals the value of the dice
        cout << "Keep Dice (s to stop rolling): ";
        string dicesKept;
        cin >> dicesKept;
        hand->setSelection(dicesKept);
        game->show(); 
        hand->play(); //roll the dice the user does not want to keep
        hand->show();
	}
}
//#######################################################################################

void test_case() {
	Game game;
	Hand* hand = new Hand();

	hand->getDice(0)->setValue(1);
	hand->getDice(1)->setValue(2);
	hand->getDice(2)->setValue(3);
	hand->getDice(3)->setValue(4);
	hand->getDice(4)->setValue(5);
	
	bool check1 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 40) {
		check1 = false;
	}
	if (check1) {
		cout << "check 1 passed\n"; 
	}

	hand->getDice(0)->setValue(2);
	hand->getDice(1)->setValue(6);
	hand->getDice(2)->setValue(4);
	hand->getDice(3)->setValue(3);
	hand->getDice(4)->setValue(5);
	
	bool check2 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 40) {
		check2 = false;
	}

	if (check2) {
		cout << "check 2 passed\n"; 
	}

	hand->getDice(0)->setValue(3);
	hand->getDice(1)->setValue(2);
	hand->getDice(2)->setValue(5);
	hand->getDice(3)->setValue(6);
	hand->getDice(4)->setValue(3);

	bool check3 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 0) {
		check3 = false;
	}

	if (check3) {
		cout << "check 3 passed\n"; 
	}

	hand->getDice(0)->setValue(1);
	hand->getDice(1)->setValue(2);
	hand->getDice(2)->setValue(3);
	hand->getDice(3)->setValue(4);
	hand->getDice(4)->setValue(6);

	bool check4 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 0) {
		check4 = false;
	}

	if (check4) {
		cout << "check 4 passed\n"; 
	}


}


int main() {
	
	srand(time(0));
	run();
	//test_case();
	return 0;
}