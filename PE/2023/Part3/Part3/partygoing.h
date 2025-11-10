#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std; 

void partyGoing(string filename) {
    ifstream inFile(filename.c_str());
    if (!inFile) {
        cout << "File not found!" << endl;
        return;
    }

    cout << "For the file input of " << '"' << filename << '"' << '.' << endl;
    int A, B, C, D;
    inFile >> A >> B >> C >> D;

    bool** adjMatrix = new bool* [A + 1];

    int* totalFriends = new int[A + 1];

    int* goingFriends = new int[A + 1];

    bool* isGoing = new bool[A + 1];

    int* q = new int[A + 1];
    int qFront = 0;
    int qRear = 0; 

    for (int i = 0; i <= A; i++) {
        adjMatrix[i] = new bool[A + 1];
        totalFriends[i] = 0;
        goingFriends[i] = 0;
        isGoing[i] = false;
        for (int j = 0; j <= A; j++) {
            adjMatrix[i][j] = false;
        }
    }

    for (int k = 0; k < B; k++) {
        int X, Y;
        inFile >> X >> Y;
        if (!adjMatrix[X][Y]) {
            adjMatrix[X][Y] = true;
            adjMatrix[Y][X] = true;
            totalFriends[X]++;
            totalFriends[Y]++;
        }
    }
    inFile.close();

    isGoing[D] = true;  
    q[qRear++] = D;    

    while (qFront != qRear) { 
        int u = q[qFront++]; 

        for (int v = 1; v <= A; v++) {
            if (adjMatrix[u][v]) { 
                goingFriends[v]++; 
                if (isGoing[v]) {
                    continue; 
                }

                if (totalFriends[v] > 0 && (goingFriends[v] * 2 >= totalFriends[v])) {
                    isGoing[v] = true;
                    q[qRear++] = v; 
                }
            }
        }
    }

    if (isGoing[C]) {
        cout << C << " will go for the party" << endl; 
    }
    else {
        cout << C << " will not go for the party" << endl; 
    }

    cout << "Classmate(s) who will go to the party is/are:" << endl; 
    for (int i = 1; i <= A; i++) {
        if (isGoing[i]) {
            cout << i << " ";
        }
    }
    cout << endl;

    for (int i = 0; i <= A; i++) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
    delete[] totalFriends;
    delete[] goingFriends;
    delete[] isGoing;
    delete[] q;
}