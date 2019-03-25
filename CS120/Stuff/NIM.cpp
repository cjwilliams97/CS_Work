/*     The Game of NIM
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
srand(time(NULL));
int num_objects = 23;
int current_player = 1;
int move;
cout << "Welcome to the Game of NIM!" << endl;
cout << "Take turns against the computer removing 1-3 objects per play. The player to remove the last object loses!" << endl;
cout << "Enter the number of objects to start with: ";
cin >> num_objects;
while ( num_objects < 0 ) {
cout << "Invalid number of objects. Please enter a number greater than 0: ";
cin >> num_objects;
}

cin >> num_objects;
do {
if ( current_player == 1 ) {
cout << "Player 1 enter your move (1-3): ";
cin >> move;
while ( move < 1 || move > 3 || move > num_objects ) {
cout << "Illegal move. /nEnter a new move: ";
cin >> move;
}
}
else {
do {
if ( num_objects == 2 ) {
move = 1; }
else {
move = 1 + rand () % 3;
}
}
while ( move < 1 || move > 3 || move > num_objects );
cout << "Computer removed " << move << endl;
}
num_objects = num_objects - move;
cout << num_objects << " objects remaining. \n";
current_player = ( current_player + 1 ) % 2;
}
while ( num_objects > 0 );
cout << "Player " << current_player << " wins!\n";
cin.ignore();
cout << "\nPress enter to quit.\n";
cin.ignore();
return 0;
}
