// Unwe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<vector>
#include<array>
#include<map>
#include<fstream>
#include<stack>
#include<list>
using namespace std;

class node { // node class
public:
	node(int nodeNum) {
		this->nodeNum = nodeNum;  // when a new node is created.
	}
	int nodeNum;  // node number
	vector<int> connections;// vector to hold the arcs from the node
	vector<int> weights;  //vector to hold all of the 
	int tw;  //use to set the potentail distance in dijkstras alg 
	int lastNode;

};


void addArc(node* n1, node* n2, int w) {
	

	while (w < 0) {
		cout << " Weight must be above 0 you idiot add type make it posotive  -- ";
		cin >> w;
		
	}
	n1->connections.push_back(n2->nodeNum); // adds the conenction node name to the conenction list
	n1->weights.push_back(w); // adds the weight to the wieghts list
	n2->connections.push_back(n1->nodeNum);
	n2->weights.push_back(w);

}


node* newNode(node* n, int nv) {
	while (nv < 0) {
		cout << "NO NEGATIVES.  enter a postive one - ";
		cin >> nv;

	}
	node* newNode = new node(nv);
	//addToGraph(g, newNode);
	return newNode;
}




void printGraph(vector<node*> myGraph) {
	for (node* i : myGraph) {
		cout << i;
	}
}

void isPath(int v, int w, vector<node*> myGraph) {


	bool isVW = false; // boolean to check if there is a conenction
	for (node* i : myGraph) { // loops through the graph
		if (i->nodeNum == v) {  // if the iteration is the one theyare searching for 
			for (int p : i->connections) {  // then iterates through the list of connections 
				if (p == w) {
					isVW = true;   // makes the boolean true if it finds it. 
					break;    // breaks out the loop as it is found 
				}
			}
			break; // breaks out the loop as it is found 
		}
	}
	//cout << isVW;   
	if (isVW == true) {
		ofstream outputFile;
		outputFile.open("isPathFile.txt");//creates an out put file
		outputFile << v << w << endl;   // Writes the list of nodes into the text file. 

	}
}
// Checks if every ndoe on the graph has connections.
bool isConnected(vector<node*> myGraph) {
	bool connected = true;   // sets a boolean
	for (node* i : myGraph) {   // loops through the vector 
		if (i->connections.size() == 0) {   // checks if the nodes vector holding the connections is empty 
			connected = false;
			cout << "NO" << endl;   // prints out no if any of the nodes have empty connections lists
			return connected;
		}
	}
	cout << "YES" << endl;   // if it is not proved wrong, print out yes.
	return connected;

}

void bfs(int v, vector<node*> myGraph) {
	if (myGraph[0]->nodeNum != 0) {
		cout << "GRAPH NODES MUST BE INTS AND START WITH ZERO TO USE BFS SORRYYYYY";
		return;
	}

	vector<int> visited;
	list<int> que;  // used a list as it is easier than setting up a new data struct to hold a linked lists
	// list already holds data on order.
	int size;
	size = myGraph.size();
	// stores what nodes We have been to
	vector<bool> beenTo(size, false);

	//beenTo[v] = true; //marks the start point as visited
	que.push_back(v); //adds v to the Que

	while (!que.empty()) {
		int u = que.front(); //takes the first item from the Q
		if (!beenTo[u]) {
			visited.emplace_back(u);
			que.pop_front();  // takes of the top of the que, moves everything forwardd
			beenTo[u] = true;
		}

		node* n = myGraph[u]; //finds the node in the graph
		for (int i : n->connections) {   // loops through the connections in the graph
			if (!beenTo[i]) {   // if beenTo is false on that iteration 
				que.push_back(i);  // add it to the stack
			}
		}
	}
	ofstream outputFile;
	outputFile.open("bfs.txt");//creates an out put file

	for (int i : visited) {
		outputFile << i;
	}

}

void dfs(vector<node*> myGraph, int v) {

	if (myGraph[0]->nodeNum != 0) {
		cout << "GRAPH NODES MUST BE INTS AND START WITH ZERO TO USE DFS SORRYYYYY";
		return;
	}
	stack<int> s;  //creates a stack
	vector<int> visited;  //creates a vector to store the sequience in order of visit
  // finds size so nows how big to make beenTo vector
	int size;
	size = myGraph.size();
	// stores what nodes We have been to
	vector<bool> beenTo(size, false);

	s.push(v);  // adds v to stack as start point
	while (!s.empty()) {
		int u = s.top();
		s.pop();
		if (!beenTo[u]) {
			visited.push_back(u);
			beenTo[u] = true;
		}


		node* n = myGraph[u]; //finds the node in the graph
		/*
			This bit here is why you have to start at 0... it kept throwing a runtimes
			error if it was u- what ever the start number was. this error  i think was due to
			the fact that u could be if U could turn negative?
		*/

		for (int i : n->connections) {   // loops through the connections in the graph
			if (beenTo[i] == false) {   // if beenTo is false on that iteration 
				s.push(i);  // add it to the stack
			}
		}
	}
	ofstream outputFile;
	outputFile.open("dfs.txt");//creates an out put file

	for (int i : visited) {
		outputFile << i;
	}
}

void dijk(vector<node*> myGraph, node* s, node* d) {

	for (node* i : myGraph) {
		i->tw = numeric_limits<int>::max(); // sets tw attribute of the node class to the int types max value which is 2147483647
	}
	s->tw = 0; // source node is 0 distance from itself
	int size;
	size = myGraph.size();
	// stores what nodes We have been to
	vector<bool> beenTo(size, false);
	vector<int>visited; //vector to hold the sequences of visited nodes
	node* v; // current node
	v = s; //sets the source node the current node

	int min;
	while (v != d) {  // while we have not reached the destination node
		for (int i = 0; i < v->connections.size(); i++) {  // loops through the adjecent nodes from the current node
			int node = v->connections[i];
			if (v->tw + v->weights[i] < myGraph[node]->tw) {  // if current nodes distance + the weight to the ajecent node is less than the tw of that node
				myGraph[node]->tw = v->tw + v->weights[i];  //  then set the tw to current nodes tw + the edge distance
				myGraph[node]->lastNode = v->nodeNum;  //  stores the current node as the previous node
			}
		}
		beenTo[v->nodeNum] = true;
		min = numeric_limits<int>::max();   // sets a minimun value
		for (int i = 0; i < myGraph.size(); i++) {
			if (!beenTo[i] && myGraph[i]->tw < min) {		// if the node has not been visited yet, and it is less than the min
				v = myGraph[i];    //    sets it to be the new current node
				min = myGraph[i]->tw;   //   sets the min to be that to check the other nodes are not more expensive.
			}
		}
	}
	vector <int> routeTaken;  // creates a vector to store the route taken 
	bool finished = false;
	int distance = d->tw;   // distacne variable 
	while (finished == false) {
		if (d == s) {
			finished = true;
		}
		routeTaken.emplace_back(d->nodeNum);  // adds the previous node to the vector
		d = myGraph[d->lastNode];	// moves to that node

	}
	cout << " The shortest route is ";
	for (int i = routeTaken.size(); i-- > 0;) {
		cout << routeTaken[i] << " ";  // out puts the path taken
	}
	cout << " With the total distance of " << distance;  // outputs the distance.

}
int main()
{
	vector<node*> myGraph;  // creates the array of the graph 
//nodes have to be in order and start at 0 for dfs and bfs to work. soz
	node* n1 = newNode(0, 0);   // creates a new node with the node value of 0, in the position of 0.
	node* n2 = newNode(0, 1);
	node* n3 = newNode(0, 2);	
	node* n4 = newNode(0, 3);
	node* n5 = newNode(0, 4);
	node* n6 = newNode(0, 5);


	// adds the nodes to the vector for the graph
	myGraph.emplace_back(n1);
	myGraph.emplace_back(n2);
	myGraph.emplace_back(n3);
	myGraph.emplace_back(n4);
	myGraph.emplace_back(n5);
	myGraph.emplace_back(n6);

	// Adds the arcs/ connections
	// with node 1 and node 2 qhich you want to conenct **must be node object**-- aswell as the weight int
	addArc(n1, n2, -4); // creates a arc between n1 and n2 with the weighting of 4.
	addArc(n1, n5, 2);
	addArc(n2, n4, 9);
	addArc(n3, n4, 7);
	addArc(n6, n2, 1);

	// Is path funtions- Writes to an output file with the series of intergers. 
	isPath(1, 2, myGraph);
	bool Connected;
	isConnected(myGraph);

	dfs(myGraph, 0);
	bfs(0, myGraph);
	dijk(myGraph, n1, n3);

	
	return 0;
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
