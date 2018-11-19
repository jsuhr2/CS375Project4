#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

class Item{
	public:
		double weight;
		double value;
		double ratio;
		Item();
		Item(double w, double v);
		double bestSet;
};

Item::Item(){
}

Item::Item(double w, double v){
	weight = w;
	value = v;
	ratio = v/w;
}

class Node{
	public:
		double profit;
		double weight;
		double bound;
		Node();
};

Node::Node(){
}

class Knapsack{
	public:
		vector<Item> items;
		vector<Node> tree;
		Knapsack();
		void sortByRatio(int, int);
		int partition(int, int);
};

Knapsack::Knapsack(){
}

int max(int x, int y){
	if(x > y)
		return x;
	return y;
}

//*** DYNAMIC PROGRAMMING CODE STARTS HERE ***
int dynamic(Knapsack sack, int numItems, int maxCapacity){
	int tracker = 0;
	int optimal[2][maxCapacity + 1];
	for(int i = 0; i <= numItems; i++){
		for(int j = 0; j <= maxCapacity; j++){
			if(i % 2 == 1){
				if(i == 0 || j == 0)
					optimal[i%2][j] = 0;
				else if(sack.items.at(i - 1).weight <= j)
					optimal[(i%2)][j] = max((sack.items.at(i - 1).value + optimal[(i%2) - 1][j - (int) sack.items.at(i - 1).weight]), optimal[(i%2) - 1][j]);
				else
					optimal[(i%2)][j] = optimal[(i%2) - 1][j];
			} else{
				if(i == 0 || j == 0)
					optimal[i%2][j] = 0;
				else if(sack.items.at(i - 1).weight <= j)
					optimal[(i%2)][j] = max((sack.items.at(i - 1).value + optimal[(i%2) + 1][j - (int) sack.items.at(i - 1).weight]), optimal[(i%2) + 1][j]);
				else
					optimal[(i%2)][j] = optimal[(i%2) + 1][j];
			}
		}
		tracker = i%2;
	}
	return optimal[tracker][maxCapacity];
}

int main(int argc, char** argv){

	if(argc != 4){
		cout << "Incorrect command line arguments" << endl;
		return 0;
	}

//clear output file
	ofstream clear;
	clear.open(argv[2], ofstream::out | ofstream::trunc);
	clear.close();

//open files
	ifstream input(argv[1], ios::in);

	ofstream output;
	output.open(argv[2], ios_base::app);
	while(true){
		const clock_t BEGIN_TIME = clock();
		Knapsack sack;
		int numItems = 0;
		int itemsConsidered = 0;
		int maxCapacity = 0;
//		int capacity = 0;
		int tempWeight = 0;
		int tempValue = 0;
		int maxProfit = 0;
		int decision = atoi(argv[3]);

		input >> numItems;
		input >> maxCapacity;
		if(input.eof())
			break;
		while(itemsConsidered < numItems){
			input >> tempWeight;
			input >> tempValue;
			sack.items.push_back(Item(tempWeight, tempValue));
			itemsConsidered++;
		}
		if(decision == 3){
			maxProfit = dynamic(sack, numItems, maxCapacity);
		}
		output << "Dynamic Programming: " << numItems << " " << maxProfit << " " << ((float(clock() - BEGIN_TIME)/CLOCKS_PER_SEC)) << endl;
	}
	input.close();
	output.close();
	return 0;
}
