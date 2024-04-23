#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>

using namespace std;

enum{
    rowNum = 20,
    colNum = 20,
};

class Graph{
    private:
        int arr[rowNum][colNum];
    public:

        void PrintAdjList(){
            cout << "Adjacency List: " << endl;
            for(int i = 0; i < rowNum; i++){
                cout << i + 1 << ": ";
                vector<int> edges = OutEdges(i);

                for(int j = 0; j < edges.size(); j++){
                        cout << edges.at(j) + 1 << ", ";
                }
                cout << endl;
            }
        }

        void PrintGraph(){
            cout << "   ";
            for(int i = 0; i < colNum; i++){
                cout << (i + 1) % 10 << ", ";
            }
            cout << endl;
            for(int i = 0; i < rowNum; i++){
                cout << (i + 1) % 10 << ": ";
                for(int j = 0; j < colNum; j++){
                    cout << arr[i][j] << ", ";
                }
                cout << endl;
            }
        }


        Graph(){
            for(int i = 0; i < rowNum; i++){
                for(int j = 0; j < colNum; j++) {
                    arr[i][j] = 0;
                }
            }
        }

    void AddEdge(int i, int j) {
        arr[i][j] = 1;
    }
    void RemoveEdge(int i, int j){
        arr[i][j] = 0;
    }
    bool hasEdge(int i, int j){
        if(j == -1){
            return false;
        }
        return arr[i][j] == 1;
    }
    vector<int> InEdges(int n) {
        //Columns is n
        vector<int> in;
        for(int i = 0; i < colNum; i++){
            if(arr[i][n] == 1){
                in.push_back(i);
            }
        }
        return in;
    }

    vector<int> OutEdges(int n) {
        //Rows is n
        vector<int> in;
        for(int i = 0; i < rowNum; i++){
            if(arr[n][i] == 1){
                in.push_back(i);
            }
        }
        return in;
    }
};


#endif