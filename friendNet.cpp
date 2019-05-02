// Hanna Brender and Reid Whitson
// CPSC 450: 01
// FriendNET: Deliverable 3

// Best friend chain algorithm: Dijkstra’s Shortest Path Algorithm
// Killer Features:
//      1. Fake friend feature: Find friends who rate you 4 points less than you rate them
//      2. Rank users from least to most popular

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

void prompt(map<string, int>, map<int, string>, vector<vector<int>>, vector<vector<int>>);
vector<int> dijkstra(int userA, int userB, map<string, int>, map<int, string>, vector<vector<int>>, vector<vector<int>>);

int main(){
    ifstream dataFile ("data.txt");
    
    vector<vector<int>> adjList;
    vector<vector<int>> valuesBetween; // a parallel list to the adjList
    map<string, int> nameToIndex; // map to convert from user's name and their index
    map<int, string> indexToName; // map to convert from user's index to their name
    
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
                    indexToName[x] = aLine;
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
                    indexToName[x] = aLine;
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
    prompt(nameToIndex, indexToName, adjList, valuesBetween);
    
    return 0;
}

void prompt(map<string, int> nameToIndex, map<int, string> indexToName, vector<vector<int>> adjList, vector<vector<int>> valuesBetween) {
    int option;
    cout << "\nWhat do you want to do?\n" <<
    "1) Check if user exists\n" <<
    "2) Check connection between users\n"
    "3) Find fake friends\n"
    "4) Best friend chain\n"
    "5) Rank user popularity\n"
    "6) Quit\n";
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
        prompt(nameToIndex, indexToName, adjList, valuesBetween);
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
            prompt(nameToIndex, indexToName, adjList, valuesBetween);
        } else if (nameToIndex.find(second) == nameToIndex.end()) {
            cout << "Error: " << second << " does not exist\n";
            prompt(nameToIndex, indexToName, adjList, valuesBetween);
        } else {
            // get user index from map
            firstIndex = nameToIndex[first];
            secondIndex = nameToIndex[second];
            
            int length = adjList[firstIndex].size(); // total number of connection for first user
            // go through each of first's connections and check if second is one of their connections
            for (int i = 0; i < length; i++) {
                // second is connected to first
                if (adjList[firstIndex][i] == secondIndex) {
                    // value between first and second
                    int weight = valuesBetween[firstIndex][i];
                    cout << "The connection from " << first << " to " << second << " has weight " << weight << "\n";
                    prompt(nameToIndex, indexToName, adjList, valuesBetween);
                }
            }
            // no connection found
            cout << "No connection between " << first << " and " << second << "\n";
            prompt(nameToIndex, indexToName, adjList, valuesBetween);
        }
    } else if (option == 3) {
        string user_name;
        cout << "What is your name? ";
        cin >> user_name;
        
        // check if user exist
        if (nameToIndex.find(user_name) == nameToIndex.end()) {
            cout << "Error: " << user_name << " does not exist\n";
            prompt(nameToIndex, indexToName, adjList, valuesBetween);
        } else {
            // get user index from map
            int user_index = nameToIndex[user_name];
            
            int count = 0;
            // check if each of user's friends is a fake friend or not
            for (int i = 0; i < adjList[user_index].size(); i++) {
                int friend_index = adjList[user_index][i];
                int user_rating = valuesBetween[user_index][i];
                // check friend's rating of user
                for (int j = 0; j < adjList[friend_index].size(); j++) {
                    if (adjList[friend_index][j] == user_index) {
                        int friend_rating = valuesBetween[friend_index][j];
                        string friend_name = indexToName[friend_index];
                        // display fake friend
                        if ((user_rating - friend_rating) >= 4) {
                            count++;
                            cout << friend_name << " is a fake friend\n";
                        }
                    }
                }
            }
            if (count == 0) {
                cout << "No fake friends\n";
            }
            prompt(nameToIndex, indexToName, adjList, valuesBetween);
        }
    } else if (option == 4) {
        string user_A;
        string user_B;
        int userA;
        int userB;
        
        cout << "User A: ";
        cin >> user_A;
        cout << "User B: ";
        cin >> user_B;
        
        //check if valid users
        if (nameToIndex.find(user_A) == nameToIndex.end()) {
            cout << "Error: " << user_A << " does not exist\n";
        } else if (nameToIndex.find(user_B) == nameToIndex.end()) {
            cout << "Error: " << user_B << " does not exist\n";
        } else {
            userA = nameToIndex[user_A];
            userB = nameToIndex[user_B];
            vector<int> bfList = dijkstra(userA, userB, nameToIndex, indexToName, adjList, valuesBetween);
            // display names of best friend chain
            cout << endl;
            for(int i = bfList.size()-1; i >= 0; i--){
                cout << indexToName[bfList[i]] << endl;
            }
        }
        prompt(nameToIndex, indexToName, adjList, valuesBetween);
    } else if (option == 5) {
        multimap<double, int> avgRatingToIndex; // use multimap so that I can sort on avgRating but also allow for same rating avg
        map<int,int> indexToNumRatings;
        map<int,int> indexToSumRatings;
        int unpopularUser = 0;
        int sumRatings;
        int numRatings;
        double avgRating;
        
        // go through each node in adjacency list and keep track of total number of ratings and
        // sum of ratings for each user
        for (int j = 0; j < adjList.size(); j++) {
            for (int k = 0; k < adjList[j].size(); k++) {
                indexToNumRatings[adjList[j][k]] += 1;
                indexToSumRatings[adjList[j][k]] += valuesBetween[j][k];
            }
        }
        
        // calculate average rating for each user and store in multimap
        for (int i = 0; i < adjList.size(); i++) {
            avgRating = (double)indexToSumRatings[i]/indexToNumRatings[i];
            avgRatingToIndex.insert({avgRating, i});
        }
        
        // display users and their average ratings (from least to most)
        cout << "\nLeast popular to most popular" << endl;
        int count = 1;
        for (auto x: avgRatingToIndex) {
            cout << "   " << count << ". " << indexToName[x.second] << " (Average rating: " << x.first << ")" << endl;
            count++;
        }
        prompt(nameToIndex, indexToName, adjList, valuesBetween);
    } else if (option == 6) {
        cout << "\nGoodbye\n";
        exit(0);
    } else {
        cout << "\nError: Incorrect option\n";
        prompt(nameToIndex, indexToName, adjList, valuesBetween);
    }
}

// Dijkstra's shortest path algorithm (used for best friend chain)
vector<int> dijkstra(int userA, int userB, map<string, int> nameToIndex, map<int, string> indexToName, vector<vector<int>> adjList, vector<vector<int>> valuesBetween) {
    //create list of all nodes
    vector<int> listOfVerts;
    for(auto it: indexToName){
        listOfVerts.push_back(it.first);
    }
    
    //create list of distances
    vector<int> distances;
    for( int i = 0; i < listOfVerts.size(); i++){
        if (listOfVerts[i] == userA) {
            distances.push_back(0);
        } else {
            distances.push_back(999); // "infinity"
        }
    }
    
    //create previous node list
    vector<int> previousVertex;
    for(int i = 0; i < listOfVerts.size(); i++){
        previousVertex.push_back(-1);
    }
    
    //variables for dijkstra's
    vector<int> unvisited = listOfVerts;
    int visit_node = userA;
    int min;
    bool hasBeenVisited = false;
    
    vector<int> visited;
    int calculatedDistance;
    vector<int> shortestPath;

    //find the node with the smallest known distance from the start node
    while (not unvisited.empty()){
        min = 999; // "infinity"
        bool alreadyVisited = false;
        
        //for the current vertex, examine its unvisited neighbors
        for(int i = 0; i < listOfVerts.size(); i++){
            alreadyVisited = false;
            if (distances[i] < min){
                for (int j = 0; j < visited.size(); j++) {
                    if (listOfVerts[i] == visited[j]) {
                        alreadyVisited = true;
                    }
                }
                // no path exists
                if (visit_node == listOfVerts[i] && adjList[visit_node].size() == 0){
                    cout << "\nNo best friend path exists";
                    return shortestPath;
                }
                // update if not already visited
                if (not alreadyVisited) {
                    min = distances[i];
                    visit_node = listOfVerts[i];
                }
            }
        }
        
        //for the current vertex, examine its unvisited neighbors
        for (int i = 0; i < adjList[visit_node].size(); i++){
            hasBeenVisited = false;
            for (int j = 0; j < visited.size(); j++){
                if (adjList[visit_node][i] == visited[j]){
                    hasBeenVisited = true;
                }
            }
            if (not hasBeenVisited){
                //for the current vertex, calculate distance of each neigbor from start vertex
                calculatedDistance = 0;
                calculatedDistance = distances[visit_node] + (10 - valuesBetween[visit_node][i]);
                
                //if the distance of a vertex is less than the known distance, update the shortest disance
                if(distances[adjList[visit_node][i]] > calculatedDistance){
                    distances[adjList[visit_node][i]] = calculatedDistance;
                    previousVertex[adjList[visit_node][i]] = visit_node;
                }
            }
        }
        //add the current vertex to the list of visited nodes and remove from unvisited
        for(int i = 0; i < unvisited.size(); i++){
            if(unvisited[i] == visit_node){
                visited.push_back(unvisited[i]);
                unvisited.erase(unvisited.begin() + i);
            }
        }
    }
    //backtrack through the table to find the friend list
    //push on the first vertex
    shortestPath.push_back(userB);
    
    //loop through until you're at the source
    int u = userB;
    while (u != userA){
        shortestPath.push_back(previousVertex[u]);
        u = previousVertex[u];
    }
    return shortestPath;
}



