#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
int main(){
    ifstream dataFile ("data.txt");
    vector<vector<int>> adj;
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
		    adj.resize(x);
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
		   adj.resize(x);
		}
		else{
                   indexSecondName = m[aLine];
		}
	    }
	}
	getline(dataFile,aLine);
	adj[indexFirstName].push_back(indexSecondName);

	//now aLine hods the distance between them
	//TODO i dont know what we are supposed to do with this value
	cout << aLine << endl;
    }


    //theres one extra thing in the map due to the resizing ... ignore it -> wont be used 
    cout << "\n\nCurrent Map" << endl << "------------------------------" << endl;
    for(auto it: m){
	cout << "name: " << it.first << "\tindex->" <<  it.second << endl;
    }

    //current adjaency list ... 8 index is extra -> unimportant
    cout << "\n\nCurrent adjacency list " << endl << "----------------------------" << endl;
    for (int i = 0; i < adj.size(); i++){
        cout << "index " << i << " -> ";
	for (int j = 0; j < adj[i].size(); j++){
	    cout << adj[i][j];
	}
	cout << endl;
    }


    return 0;
}
