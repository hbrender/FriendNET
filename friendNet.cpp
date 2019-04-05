#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void prompt(map<string, int>, vector<vector<int>>, vector<vector<int>>);

int main(){
    ifstream dataFile ("data.txt");
    
    vector<vector<int>> adjList;
    vector<vector<int>> valuesBetween; // a parallel list to the adjList
    map<string, int> nameToIndex; // map to convert from user's name and their index
    
    string aLine;
    
    //variable to keep track of values in the map
    int x = 0;
    int indexFirstName;
    int indexSecondName;
    
    while (not dataFile.eof()) {
        for (int i = 0; i < 2; i++){
            getline(dataFile, aLine, ' ');
            
            if(i == 0){
                //this is the first name in the line of the file
                if(nameToIndex.find(aLine) == nameToIndex.end()){
                    //it isnt in the map yet
                    nameToIndex[aLine] = x;
                    indexFirstName = x;
                    x++;
                    adjList.resize(x);
                    valuesBetween.resize(x);
                } else{
                    //found the name in the list
                    indexFirstName = nameToIndex[aLine];
                }
            } else{
                //this is the second name in the line of the file
                if(nameToIndex.find(aLine) == nameToIndex.end()){
                    //it isnt in the map yet
                    nameToIndex[aLine] = x;
                    indexSecondName = x;
                    x++;
                    adjList.resize(x);
                    valuesBetween.resize(x);
                } else{
                    indexSecondName = nameToIndex[aLine];
                }
            }
        }
        int intVal;
        //read it into an int value
        dataFile >> intVal;
        //eat up the newline
        getline(dataFile,aLine);
        
        //add value to adjacency list
        adjList[indexFirstName].push_back(indexSecondName);
        
        //now intVal holds the distance between them
        valuesBetween[indexFirstName].push_back(intVal);
    }
    
    
    // Names to index
    cout << "\n\nCurrent Map" << endl << "------------------------------" << endl;
    for(auto it: nameToIndex){
        cout << "name: " << it.first << "\tindex->" <<  it.second << endl;
    }
    
    //current adjListaency list
    cout << "\n\nCurrent adjListacency list " << endl << "----------------------------" << endl;
    for (int i = 0; i < adjList.size(); i++){
        cout << "index " << i << " -> ";
        for (int j = 0; j < adjList[i].size(); j++){
            cout << adjList[i][j] << " ";
        }
        cout << endl;
    }
    
    //current distance values -> parallel to aboce
    cout << "\n\nCurrent values between the individuals" << endl << "-------------------------" << endl;
    for (int i = 0; i < valuesBetween.size(); i++){
        cout << "index " << i << " -> ";
        for (int j = 0; j < valuesBetween[i].size(); j++){
            cout << valuesBetween[i][j] << " " ;
        }
        cout << endl;
    }
    prompt(nameToIndex, adjList, valuesBetween);
    
    return 0;
}

void prompt(map<string, int> nameToIndex, vector<vector<int>> adjList, vector<vector<int>> valuesBetween) {
    int option;
    cout << "\nWhat do you want to do?\n" <<
            "1) Check if user exists\n" <<
            "2) Check connection between users\n"
            "3) Quit\n";
    cin >> option;
    
    if (option == 1) {
        string user;
        cout << "What user? ";
        cin >> user;
        
        if (nameToIndex.find(user) != nameToIndex.end()) {
            cout << user << " does exist\n";
        } else {
            cout << user << " does not exist\n";
        }
        prompt(nameToIndex, adjList, valuesBetween);
    } else if (option == 2) {
        string users;
        cout << "What users (seperated by spaces)? ";
        cin.ignore();
        getline(cin, users);
        
        // split the string of two user names
        string name;
        string first;
        string second;
        for (auto n: users) {
            if (n == ' ') {
                first = name;
                name = "";
            } else {
                name = name + n;
            }
        }
        second = name;
        
        int firstIndex;
        int secondIndex;
        // check if users exist
        if (nameToIndex.find(first) == nameToIndex.end()) {
            cout << "Error: " << first << " does not exist\n";
            prompt(nameToIndex, adjList, valuesBetween);
        } else if (nameToIndex.find(second) == nameToIndex.end()) {
            cout << "Error: " << second << " does not exist\n";
            prompt(nameToIndex, adjList, valuesBetween);
        } else {
            // get user index from map
            firstIndex = nameToIndex[first];
            secondIndex = nameToIndex[second];
            
            int length = adjList[firstIndex].size(); // total number of connection for first user
            // go through each of first's connections and second is one of their connections
            for (int i = 0; i < length; i++) {
                // second is connected to first
                if (adjList[firstIndex][i] == secondIndex) {
                    // value between first and second
                    int weight = valuesBetween[firstIndex][i];
                    cout << "The connection from " << first << " to " << second << " has weight " << weight << "\n";
                    prompt(nameToIndex, adjList, valuesBetween);
                }
            }
            // no connection found
            cout << "No connection between " << first << " and " << second << "\n";
            prompt(nameToIndex, adjList, valuesBetween);
        }
    } else if (option == 3) {
        exit(0);
    } else {
        cout << "\nError: Incorrect option\n";
        prompt(nameToIndex, adjList, valuesBetween);
    }
}
