#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
int main(){
    ifstream dataFile ("data.txt");
    vector<vector<int>> adjList;
    vector<vector<int>> valuesBetween; //a parallel list to the adjList 
    map<string, int> m;


    string aLine;

    //variable to keep track of values in the map
    int x = 0;
    int indexFirstName;
    int indexSecondName;


    while (not dataFile.eof())
    {
	for (int i = 0; i < 2; i++){
            getline(dataFile, aLine, ' ');
	    
	    if( i == 0){
		//this is the first name in the line of the file
		if(m.find(aLine) == m.end()){
                    //it isnt in the map yet
		    m[aLine] = x;
		    indexFirstName = x;
		    x++;
		    adjList.resize(x);
                    valuesBetween.resize(x); 
		}
		else{
		    //found the name in the list
		    indexFirstName = m[aLine];
		}
	    }
	    else{
		//this is the second name in the line of the file
		if(m.find(aLine) == m.end()){
                   //it isnt in the map yet
		   m[aLine] = x;
		   indexSecondName = x;
		   x++; 
		   adjList.resize(x);
		   valuesBetween.resize(x);
		}
		else{
                   indexSecondName = m[aLine];
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
    //TODO resize the map so it doesnt hold the last value because it has a newline
    //or something.... i think it reads in the last newline and then adds it to the map before 
    //being done
	
    //resize vectors by one so that the last value isnt all crazy
    adjList.resize(adjList.size()-1);
    valuesBetween.resize(valuesBetween.size()-1);


    //theres one extra thing in the map due to the resizing ... ignore it -> wont be used 
    cout << "\n\nCurrent Map" << endl << "------------------------------" << endl;
    for(auto it: m){
	cout << "name: " << it.first << "\tindex->" <<  it.second << endl;
    }

    //current adjListaency list ... 8 index is extra -> unimportan
    cout << "\n\nCurrent adjListacency list " << endl << "----------------------------" << endl;
    for (int i = 0; i < adjList.size(); i++){
        cout << "index " << i << " -> ";
	for (int j = 0; j < adjList[i].size(); j++){
	    cout << adjList[i][j];
	}
	cout << endl;
    }

    //current distance values -> parallel to aboce
    cout << "\n\nCurrent values between the individuals" << endl << "-------------------------" << endl;
    for (int i = 0; i < valuesBetween.size(); i++){
        cout << "index " << i << " -> ";
	for (int j = 0; j < valuesBetween[i].size(); j++){
	    cout << valuesBetween[i][j];
	}
	cout << endl;
    }


    return 0;
}
