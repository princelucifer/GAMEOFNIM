// Game of Nim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <stdlib.h>

#define MAX_PEGS 20
#define MAX_DISCS 10

using namespace std;

// Function prototypes

int read_n_pegs(void);
/* This function will prompt the user to input the number of peg and it will be atmost 20
   It has a return type of int which will be the number of pegs. */

void read_n_discs(int*, int, int*);
/*
	This function will prompt the user to input the number
	of discs in each peg (<= 10 discs in each peg)
	It has an arguments of integer pointer which will point to the array of pegs
	containing the number of discs in each peg and int which is the number of Pegs
*/

void display_pegs(int* pegArray, int size, int totalPegs);
// This function is used to display the pegs in the required manner

float calculate_statistics(float numberOfDiscs, float totalNumber);
// This function calculated the percentage of disc in each peg

void display_discs(int pegNumber, int numberOfDiscs, int totalDiscs);
// This function used to display the number of disc alongside with statistics

int isEmpty(int*);
// Function implemented to check for the emptiness 
void player_move(int*, int, int*, int*);
// Function to ask the player for move command

void display_winner(int* curPlayer);

int main(int argc, char** argv) {
	//Varaible Declaration
	int N;
	N = read_n_pegs(); // Calling the read peg function to know the number of pegs and storing it in N
	int *pegs = (int *) malloc(sizeof(N)*N);
	int totalPegs = 0;
	int cur_player = 0;  // cur_player is 0 means Player 1 and 1 means Player 2


	read_n_discs(pegs, N, &totalPegs); // Calling the read disc function to update the pegs array
	display_pegs(pegs, N, totalPegs);
	while (!isEmpty(&totalPegs)) {
		player_move(&cur_player, N, &totalPegs, pegs);
	}
	return 0;
}

int read_n_pegs()
{
	int temp = 0;
	while (temp > MAX_PEGS or temp < 1) { // This will prompt user untill he enters the correct number
		cout << "\nEnter the number of PEGS (1-20): ";
		cin >> temp;
		if (temp > MAX_PEGS or temp < 1) {
			cout << "[-]Please enter the correct number";
		}
	}
	return temp; // Returning the number of pegs
}

void read_n_discs(int* pegs, int size, int* totalPegs)
{

	for (int i = 0; i < size; i++)
	{
		int t = -1;
		while (t > MAX_DISCS or t < 0) {
			cout << "\nEnter the number of Discs in Peg(0-10): " << i + 1 << ": ";
			cin >> t;
			*totalPegs += t;
			if (t > MAX_DISCS or t < 0) {
				cout << "[-]Please enter the correct number";
			}
		}
		pegs[i] = t;
	}
}

float calculate_statistics(float numberOfDiscs, float totalNumber) {
	return ((float)(numberOfDiscs / totalNumber) * 100); // it will return the percentage of disc
}

void display_discs(int pegNumber, int numberOfDiscs, int totalDiscs) {
	cout << "\nPeg" << setw(2) << pegNumber << ": ";
	for (int i = 0; i < numberOfDiscs; i++)
	{
		cout << "%";
	}
	cout << setw(11 - numberOfDiscs);
	cout << "(" << calculate_statistics((float)numberOfDiscs, (float)totalDiscs) << "%)";
}

void display_pegs(int* pegArray, int size, int totalDiscs) {
	for (int i = 0; i < size; i++)
	{
		display_discs(i + 1, pegArray[i], totalDiscs);
	}

}

int isEmpty(int* totalPegs)
{
	if (*totalPegs <= 0) return 1;
	else return 0;
}

void player_move(int* curPlayer, int N, int* totalPegs, int* pegs)
{
	cout << "\n\nPlayer" << *curPlayer + 1 << " Moves\n";
	int mp, md;
	cout << "\nFrom which peg to move: ";
	cin >> mp;
	if (mp < 1 or mp > N) {
		cout << "\nInvalid Choice. Lets try again";
		return;
	}
	cout << "No. of Disc to move: ";
	cin >> md;
	if (md < 0 or md > pegs[mp-1]) {
		cout << "\nInvalid Choice. Lets try again";
		return;
	}


	pegs[mp - 1] = pegs[mp - 1] - md;
	*totalPegs -= md;
	if (isEmpty(totalPegs)) { // If there is no disc player wins 
		display_winner(curPlayer);
		exit(0);
	}
	else {
		int t = *totalPegs; // Else game will continue and the player will change
		display_pegs(pegs, N, t);
		*curPlayer = !(*curPlayer);
	}
}

void display_winner(int* curPlayer)
{
	cout << "\n\n[+]Congratulation Player" << *curPlayer + 1 << " You have won the game.\n";
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
