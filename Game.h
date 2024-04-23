#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Graph.h"
#include "Exceptions.h"

enum{
    arrowAmount = 3,
};


class Game{
    private:
        int playerRoom;
        int wumpusRoom;
        int batRoom;
        int holeRoom;

        Graph map;

        int arrowPlace[arrowAmount];

        void updateArrows(int curPlace, int endPlace){
            if(endPlace == curPlace){
                for(int i = 0; i < arrowAmount; i++){
                    if(arrowPlace[i] == endPlace){
                        cout << "You picked up an arrow!" << endl;
                    }
                }
            }
            if(playerRoom == curPlace){
                for(int i = 0; i < arrowAmount; i++) {
                    if(arrowPlace[i] == curPlace){
                        arrowPlace[i] = endPlace;
                    }
                }
            } else {
                for(int i = 0; i < arrowAmount; i++){
                    if(arrowPlace[i] == curPlace){
                        arrowPlace[i] = endPlace;
                        return;
                    }
                }
            }
        }
        
        void loseArrow(){
            for(int i = 0; i < arrowAmount; i++) {
                if(arrowPlace[i] == playerRoom){
                    arrowPlace[i] = -1;
                    return;
                }
            }

            throw DeadError();
        }

        void populateMapRandom(){

            for(int i = 0; i < 20; i++){
                int count = rand() % 3 + 2;
                    for(int j = 0; j < count; j++){
                    int randNum = rand() % 20;
                    while(map.hasEdge(i, randNum) || randNum == i){
                        randNum = rand() % 20;
                    }
                map.AddEdge(i, randNum);
                }
            }   
        }

        void populateMap(){
            //Three connections to
            //2-4 connections from
            addEdges(1, 2, 5, 12, 0);
            addEdges(2, 1, 3, 8, 0);
            addEdges(3, 2, 7, 15, 0);
            addEdges(4, 9, 11, 0, 0);
            addEdges(5, 1, 6, 16, 0);
            addEdges(6, 5, 9, 18, 0);
            addEdges(7, 3, 14, 0, 0);
            addEdges(8, 2, 10, 13, 0);
            addEdges(9, 4, 6, 17, 0);
            addEdges(10, 8, 15, 0, 0);
            addEdges(11, 4, 12, 19, 0);
            addEdges(12, 1, 11, 20, 0);
            addEdges(13, 8, 14, 20, 0);
            addEdges(14, 7, 13, 18, 0);
            addEdges(15, 3, 10, 0, 0);
            addEdges(16, 5, 17, 0, 0);
            addEdges(17, 9, 16, 0, 0);
            addEdges(18, 6, 14, 0, 0);
            addEdges(19, 11, 20, 0, 0);
            addEdges(20, 12, 13, 19, 0);
        }

        void shuffleVector(int amount, vector<int>& arr){
                for(int i = 0; i < amount; i++){
                    int rand1 = rand() % amount;
                    int rand2 = rand() % amount;
                    while(rand1 == rand2){
                        rand2 = rand() % amount;
                    }
                    int num1 = arr.at(rand1);
                    arr.at(rand1) = arr.at(rand2);
                    arr.at(rand2) = num1;
                }
        }

        void populateMapRandomPrototype(){
            int amount = rand() % 20 + 60; //between 60 (3 connections) and 79 (4 connections)
            vector<int> arrConnections;
            int spacesFilled = 0; // Current number of connections made
            int curNum = 0; //Start with room 1 ( 0 as the number)
            bool topReached = false; // if it has reached room 20 already marked with this var
            while(spacesFilled < amount){ // While we don't have the connections filled
                int above = rand() % 2 + 2; // Between 2 and 3 connections (incase of duplicates after)
                if(curNum >= 20){
                    topReached = true; // End reached go back to room 1
                    curNum -= 20;
                    above = 1;
                } else if(topReached == true){
                    above = 1;
                }
                for(int i = 0; i < above; i++){
                    arrConnections.push_back(curNum);
                    spacesFilled++;

                    if(spacesFilled >= amount){
                        //Edge case
                        break;
                    }
                }
                curNum++;
            }

            shuffleVector(amount, arrConnections);

            while(arrConnections.size() > 0){
                for(int i = 0; i < 20; i++){
                    int amount = rand() % 2 + 2;
                    for(int j = 0; j < amount; j++){
                        while(map.OutEdges(i).size() > 3){
                            i++;
                        }

                        if(arrConnections.size() <= 0){
                            break;
                        }
                        int num = arrConnections.back();
                        
                        
                        int n = 2;
                        while(map.hasEdge(i, num) || num == i){
                            int hold = arrConnections.at(arrConnections.size() - 1);
                            if((arrConnections.size() - n) > 0){
                                arrConnections.at(arrConnections.size() - 1) = arrConnections.at(arrConnections.size() - n);
                                arrConnections.at(arrConnections.size() - n) = hold;
                            }
                            if(n >= arrConnections.size()){
                                break;
                            }
                            num = arrConnections.back();
                            n++;
                        }

                        map.AddEdge(i, num);

                        if(0 >= arrConnections.size()){
                            break;
                        }
                        arrConnections.pop_back();
                    }
                }
            }
        }
        
        void addEdges(int row, int con1, int con2, int con3, int con4){
            if(con1 != 0){
                map.AddEdge(row - 1, con1 - 1);
            }
            if(con2 != 0){
                map.AddEdge(row - 1, con2 - 1);
            }
            if(con3 != 0){
                map.AddEdge(row - 1, con3 - 1);
            }
            if(con4 != 0){
                map.AddEdge(row - 1, con4 - 1);
            }
        }

        void moveWumpus(){
            cout << "Wumpus has moved..." << endl;
            wumpusRoom = rand() % 20;
            while(wumpusRoom == playerRoom || wumpusRoom == batRoom || wumpusRoom == holeRoom){
                wumpusRoom = rand() % 20;
            }
        }

    public:
        void printArrows(){
            for(int i = 0; i < arrowAmount; i++){
                cout << arrowPlace[i] << ", ";
            }
            cout << endl;
        }
        Game(){
            srand(time(NULL));
            int mapChoice;
            cout << "Would you like to populate the map with 1: Preset Map, or 2: Randomized Map: " << endl;
            cout << "Choice: ";
            cin >> mapChoice;
            if(mapChoice == 2){
                cout << "Populating the map randomly" << endl;
                populateMapRandomPrototype();
            } else {
                cout << "Populating the map with the preset" << endl;
                populateMap();
            }
            playerRoom = rand() % 20; //Between 0 and 19
            wumpusRoom = rand() % 20;
            batRoom = rand() % 20;
            holeRoom = rand() % 20;

            while(wumpusRoom == playerRoom){
                wumpusRoom = rand() % 20;
            }
            while(batRoom == playerRoom || batRoom == wumpusRoom){
                batRoom = rand() % 20;
            }
            while(holeRoom == playerRoom || holeRoom == wumpusRoom || holeRoom == batRoom){
                holeRoom = rand() % 20;
            }

            for(int i = 0; i < arrowAmount; i++){
                arrowPlace[i] = playerRoom;
                //Arrows stay in the same spot as player unless fired
            }
        }

        int getPlayerRoom(){return playerRoom + 1;}

        void PrintMap(){map.PrintGraph();}
        void PrintMapAdj(){map.PrintAdjList();}

        void MoveHelper(int toRoom){
            updateArrows(playerRoom, toRoom);
            playerRoom = toRoom;

            if(playerRoom == wumpusRoom){
                cout << "You ran into wumpus!!!" << endl;
                loseArrow();
                cout << "You lose one arrow" << endl;
                moveWumpus();
            }else if(playerRoom == batRoom){
                cout << "AHHHHH BATS" << endl;
                cout << "Going to a random room nearby..." << endl;
                cout << endl;
                toRoom = rand() % 20;
                while(!map.hasEdge(playerRoom, toRoom)){
                    toRoom = rand() % 20 + 1;
                }
                MoveHelper(toRoom);
            } else if(playerRoom == holeRoom){
                cout << "You fell lol" << endl;
                throw DeadError();
            }
        }

        void Move(){
            //Add cases for collision
            int toRoom;
            cout << "Enter the room to move to: ";
            cin >> toRoom;
            while(!map.hasEdge(playerRoom, toRoom - 1)){
                cout << "Enter the room to move to: ";
                cin >> toRoom;
            }
            cout << endl;

            updateArrows(toRoom - 1, toRoom - 1);

            MoveHelper(toRoom - 1);
        }

        void Shoot(){
            int toShoot = 0;
            while(toShoot < 2 || toShoot > 4){
                cout << "Enter the amount of rooms to shoot through (2-4): ";
                cin >> toShoot;
            }

            int curRoom = 0;
            while(!map.hasEdge(playerRoom, curRoom - 1)){
                cout << "Enter the room to shoot at: ";
                cin >> curRoom;
            }
            cout << "Shot at room: " << curRoom << endl;
            if(curRoom - 1 == wumpusRoom){
                throw WinError();
            }
            Graph roomsPassed;
            for(int i = 0; i < toShoot - 1; i++){
                //Shoots through x rooms
                roomsPassed.AddEdge(playerRoom, curRoom);
                vector<int> edges = map.OutEdges(curRoom);
                curRoom = edges.at(rand() % edges.size());

                while(roomsPassed.hasEdge(playerRoom, curRoom)){
                    curRoom = edges.at(rand() % edges.size());
                }
                cout << "Shot through room: " << curRoom + 1 << endl;

                if(curRoom == wumpusRoom){
                    throw WinError();
                }
            }
            cout << endl;
            cout << "Arrow landed in " << curRoom + 1 << endl;
            if(curRoom == batRoom || curRoom == holeRoom){
                cout << "You're arrow got lost :(" << endl;
                loseArrow();
            }
            for(int i = 0; i < arrowAmount; i++){
                if(arrowPlace[i] != -1 && arrowPlace[i] == playerRoom){
                    arrowPlace[i] = curRoom - 1;
                    break;
                }
            }

            moveWumpus();
        }

        void displayOutEdges(int n){
            vector<int> edges = map.OutEdges(n);
            bool holeNear = false;
            bool wumpusNear = false;
            bool batNear = false;
            //Use booleans so user can't tell which room has what
            
            cout << endl << "Can move to room: ";
            for(int i = 0; i < edges.size() - 1; i++){
                int curRoom = edges.at(i);
                cout << curRoom + 1 << ", ";
                if(curRoom == wumpusRoom){
                    wumpusNear = true;
                } else if(curRoom == batRoom){
                    batNear = true;
                } else if(curRoom == holeRoom){
                    holeNear = true;
                }
            }
            int curRoom = edges.at(edges.size() - 1);
            cout << "or " << curRoom + 1 << endl;
            if(curRoom == wumpusRoom){
                wumpusNear = true;
            } else if(curRoom == batRoom){
                batNear = true;
            } else if(curRoom == holeRoom){
                holeNear = true;
            }

            cout << endl;
            if(wumpusNear){
                cout << "You smell an animal smell" << endl << endl;
            }
            if(batNear){
                cout << "You hear screeching" << endl << endl;
            }
            if(holeNear){
                cout << "You feel a slight breeze" << endl << endl;
            }
        }



};






#endif