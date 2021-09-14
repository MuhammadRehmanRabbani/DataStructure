
/********************** Warship repair facility for Tie Fighters and Star Destroyers*****************************/


//including libraries
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <chrono>
#include <time.h>
#include<string>
#include <random>
#include <map>
#include <windows.h>
#define MAX 22

using namespace std;
using namespace std::chrono;


//Declaring of dual stack
typedef struct
{
	int tie;
	int star;
	int max;
	string str[MAX];
}DualStack;

//Initialization of Double Stack
void initialize(DualStack* s)
{
	s->tie = 0;
	s->max = 0;
	s->star = MAX - 1;
	s->str[0] = "TieBase";
	s->str[21] = "StarBase";
}

//Defining push Operation on Tie Stack
void pushTie(DualStack* s, string item)
{
	if (s->star == s->tie + 1)
	{
		s->max++;
		printf("\nSpace is full. Kindly direct towards repair facility in the Dagaba system\n");
		cout << "Vehicle " << item << " has been rejected" << endl;
		return;
	}

	s->tie++;
	s->str[s->tie] = item;
	cout << "Inserted vehicle in TieStack :" << item << endl;
}

//defining push Operation on Star Stack
void pushStar(DualStack* s, string item)
{
	if (s->star == s->tie + 1)
	{
		s->max++;
		printf("\nSpace is full. Kindly direct towards repair facility in the Dagaba system\n");
		cout << "Vehicle " << item << " has been rejected" << endl;
		return;
	}
	s->star--;
	s->str[s->star] = item;
	cout << "Inserted vehicle in StarStack :" << item << endl;
}

//defining pop operation on Tie Stack
int popTie(DualStack* s, string* item)
{
	if (s->tie == -1)
	{
		printf("\nStack Underflow TieStack\n");
		return -1;
	}

	*item = s->str[s->tie--];
	return 0;
}

//defining pop operation on Star Stack
int popStar(DualStack* s, string* item)
{
	if (s->star == MAX - 1)
	{
		printf("\nStack Underflow StarStack\n");
		return -1;
	}

	*item = s->str[s->star++];
	return 0;
}

// method to implemet vehicle maintenance record
void report(string type, string name) {

	// declaring variable for the time required for the vehicle
	int requiredTime = 1;

	double const exp_dist_mean = 1;
	double const exp_dist_lambda = 1 / exp_dist_mean;

	std::random_device rd;

	std::exponential_distribution<> rng(exp_dist_lambda);

	std::mt19937 rnd_gen(rd()); // value of time would be rng(rnd_gen) * 4


	cout << "Vehicle Type: " << type << endl; //printing type of vehicle
	cout << "Vehicle Name: " << name << endl; // printing name of vehicle

	auto start = std::chrono::system_clock::now();
	time_t startTime = std::chrono::system_clock::to_time_t(start);
	cout << "Start Time: " << ctime(&startTime); // printing start time

	// since Sleep takes the amount of time in milliseconds, and 1000 ms = 1 second
	if (type == "Star Destroyer") {
		// star destroyer can take time 2,3,4,5,6 or 7 minutes with equall probability
		requiredTime = rng(rnd_gen) * 4;
		Sleep(requiredTime * 1000 * 60);
	}
	else if (type == "Tie Fighter") {
		// star destroyer can take time 1,2 or 3 minutes with equall probability
		requiredTime = (rand() % 3) + 1;
		Sleep(requiredTime * 1000 * 60);
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedSeconds = end - start;
	time_t endTime = std::chrono::system_clock::to_time_t(end);
	std::cout << "Finish Time " << ctime(&endTime)
		<< "Time to repair: " << elapsedSeconds.count() << "s\n";
	Sleep(2 * 1000);

	cout << "Time consumed for preparation of facility: 2 seconds" << endl;
}

// Main method starts from here
int main()
{
	//declaring variables
	string vName;
	string vehicle;
	int startTime;
	int count;
	int starCount = 0;
	int tieCount = 0;
	int starRepaired = 0;
	int tieRepaired = 0;
	int spaceOccupied = 0;
	const int range_from = 0.0;
	const int range_to = 1.0;
	char i = 'A'; // concatenate alphabet with vehicle name i.e. TieA
	char j = 'A'; // concatenate alphabet with vehicle name i.e. TieB
	double randCount;

	//declaring dual stack
	DualStack stack;

	//initializing the dual stack
	initialize(&stack);

	// seed value for random numbers
	srand(time(0));

	freopen("Time.txt", "w", stdout);

	// creating map object for concatenating two strings i.e. Tie + A = TieA
	std::map<std::string, std::string> variables;

	// generating random numbers between range 0 and 1 
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_real_distribution<> dis(range_from, range_to);

	//Starting timepoint 
	auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
	//Get start time from the system clock and write it to the file
	cout << "Start Time : " << ctime(&timenow) << endl;

	while (true) {
		count = 0;
		// 4 vehicles can come at a time in the station, pushing them in appropriate stack
		while (count < 4) {
			randCount = dis(generator);
			// type of vehicle is determined using srtep function
			if (randCount >= 0 && randCount < 0.75) {
				vehicle = "tie";
				vehicle.push_back(i);
				// if 5 vehicles are rejected, we chould end the program
				if (stack.max == 5) {
					spaceOccupied = 1;
					break;
				}
				pushTie(&stack, vehicle);
				// If we get tieZ, start with tieA 
				if (i == 'Z') {
					i = 'A';
					continue;
				}
				i++;
				tieCount++;
			}
			else if (randCount >= 0.75 && randCount < 1) {
				vehicle = "star";
				vehicle.push_back(j);
				// if 5 vehicles are rejected, we chould end the program
				if (stack.max == 5) {
					spaceOccupied = 1;
					break;
				}
				pushStar(&stack, vehicle);
				// If we get starZ, start with starA
				if (j == 'Z') {
					j = 'A';
					continue;
				}
				j++;
				starCount++;
			}
			count++;
		}// end while

		// if 5 vehicles are rejected, end the program	
		if (spaceOccupied == 1)
			break;

		//if there is start destroyer availabe, recover it first
		if (starCount > 0) {
			if (popStar(&stack, &vName) == 0) {
				cout << "Vehicle poped out of stack: " << vName << endl;
				// calling repair function to print information of vehicle
				report("Star Destroyer", vName);
				starRepaired++;
			}
			starCount--;
			continue;

		}
		//if there is tie fighter available, recover it
		if (tieCount > 0) {
			if (popTie(&stack, &vName) == 0) {
				cout << "Vehicle poped out of stack: " << vName << endl;
				// calling repair function to print information of vehicle
				report("Tie Fighter", vName);
				tieRepaired++;
			}
			tieCount--;
			continue;
		}
	}
	cout << "\n" << "Total Star Destroyers Repaired: " << starRepaired << endl;
	cout << "\n" << "Total Tie Destroyers Repaired: " << tieRepaired << endl;
	return 0;
}

