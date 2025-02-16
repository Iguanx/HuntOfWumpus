#include <iostream>
#include <vector>
#include "Graph.h"
#include "Game.h"

using namespace std;


int main() {
    Game main;
    // main.PrintMapAdj(); //Prints the adjacency list of the map
    
    bool gameContinue = true;
    char autoObserve;
    cout << "Would you like to play the game with Auto Observe on? (y or n): ";
    cin >> autoObserve;
    if(toupper(autoObserve) == 'Y'){
        autoObserve = true;
    } else {
        autoObserve = false;
    }
    cout << endl;
    cout << "Welcome to..." << endl;
    cout << " _   _             _            __   _    _                                " << endl;
    cout << "| | | |           | |          / _| | |  | |                               " << endl;
    cout << "| |_| |_   _ _ __ | |_    ___ | |_  | |  | |_   _ _ __ ___  _ __  _   _ ___" << endl;
    cout << "|  _  | | | | '_ \\| __|  / _ \\|  _| | |/\\| | | | | '_ ` _ \\| '_ \\| | | / __|" << endl;
    cout << "| | | | |_| | | | | |_  | (_) | |   \\  /\\  / |_| | | | | | | |_) | |_| \\__ \\ " << endl;
    cout << "\\_| |_/\\__,_|_| |_|\\__|  \\___/|_|    \\/  \\/ \\__,_|_| |_| |_| .__/ \\__,_|___/" << endl;
    cout << "                                                           | |             " << endl;
    cout << "                                                           |_|              " << endl;



    while(gameContinue){
        try{
            char userChoice = 'a';
            if(autoObserve){
                main.displayOutEdges(main.getPlayerRoom() - 1); //Automatically observe every round
            }
            while(toupper(userChoice) != 'M' && toupper(userChoice) != 'S' && toupper(userChoice) != 'O'){
                cout << "Commands: Move ( M ), Shoot ( S ), or Observe ( O )." << endl;
                cout << "You are in room " << main.getPlayerRoom() << endl;
                cout << "What would you like to do: ";
                cin >> userChoice;
            }
            if(toupper(userChoice) == 'M'){
                main.Move();
            } else if(toupper(userChoice) == 'S'){
                main.Shoot();
            } else {
                main.displayOutEdges(main.getPlayerRoom() - 1);
            }

        }
        catch(DeadError &e){
            cerr << e.what() << endl;
            gameContinue = false;
        }
        catch(WinError &e){
            cout << "You shot wumpus!" << endl;
            cerr << e.what() << endl;
            cout << endl;
            gameContinue = false;
        }
    }

    return 0;
}


// g++ -c HuntOfWumpus.cpp
// g++ -o main.exe HuntOfWumpus.o
// ./main.exe