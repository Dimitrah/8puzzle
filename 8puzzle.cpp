#include "pch.h"
#include <iostream>
#include <cmath>
#include <stack>
#include <set>
#include <vector>
#include <sstream>
#include <string>
#include <chrono>
#include <queue>

#define f(x,n) for(int x=0;x<=n;x++) 

using namespace std;

class State
{
public:
	void print();
	int state[9];
	State Nstate(int i, int j)
	{
		State N;
		f(k, 8) N.state[k] = state[k];
		int t;
		t = N.state[i];
		N.state[i] = N.state[j];
		N.state[j] = t;
		return N;
	}
	string toString() const;
	friend bool operator< (const State& a, const State& o);
	

	int find9();
	bool equal(State k);
	bool goal();

	//Telestes metabasis
	bool goUp(State&n);
	bool goRight(State&n);
	bool goDown(State&n);
	bool goLeft(State&n);

	vector <State> expand();
	State operator= (State o);
};


bool InSet(set<State> closed, State s);

//Depth First Search Algorithm
bool DFS(stack<State> &frontier, set<State> &closed);
//Breadth First Search Algorithm
bool BFS(queue<State>&frontier, set<State>& closed);




int main()
{
	auto start = chrono::steady_clock::now();
	State final, initial;
	f(i, 8)
	{
		final.state[i] = i + 1;
	}
	initial.state[0] = 1;
	initial.state[1] = 2;
	initial.state[2] = 3;
	initial.state[3] = 4;
	initial.state[4] = 6;
	initial.state[5] = 9;
	initial.state[6] = 7;
	initial.state[7] = 5;
	initial.state[8] = 8;

	cout << "We want to reach this state.\n";
	final.print();

	cout << "This is the initial state.\n";
	initial.print();


	//-------DFS-------//
	/*stack<State> frontier;
	set<State> closed;
    frontier.push(initial);
	cout << "The size of agenta is " << frontier.size() << endl;
	if (DFS(frontier, closed) cout << "ok"<<endl;
	else cout << "not ok" << endl;*/
	
	//-------BFS-------//
	queue<State> frontier;
	set<State> closed;
	frontier.push(initial);
	cout << "The size of agenta is " << frontier.size() << endl;
	if (BFS(frontier, closed)) cout << "ok" << endl;
	else cout << "not ok" << endl;
	
	
	
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	

	

	

	
	
	return 0;
}

void State::print()
{
	f(i, 8)
	{
		if ((i + 1) % 3 == 0)
			cout << state[i] << "\n";
		else  cout << state[i] << " ";
	}
	cout << "\n";
}



string State::toString() const
{
	stringstream ot;
	State a = *this;
	for (int i = 0; i <= 8; i++)
		ot << a.state[i];
	return ot.str();
}


int State::find9()
{
	f(i, 8)
	{
		if (state[i] == 9)
			return i;
	}
}

bool State::equal(State k)
{
	f(i, 8)
	{
		if (state[i] != k.state[i])
			return false;
	}
	return true;
}

bool State::goal()
{
	f(i, 8)
	{
		if (state[i] != i + 1)
			return false;
	}
	return true;
}

bool State::goUp(State & n)
{
	n = *this;
	int k=n.find9();
	if (k >= 3)
	{
		n=n.Nstate(k - 3, k);
		return true;
	}
	if(k<3) 
	return false;
}

bool State::goRight(State & n)
{
	n = *this;
	int k = n.find9();
	if (k != 2 && k != 5 && k != 8)
	{
		n = n.Nstate(k, k + 1);
		return true;
	}
	if(k==2||k==5||k==8)
	return false;
}

bool State::goDown(State & n)
{
	n = *this;
	int k = n.find9();
	if (k < 6)
	{
		n = n.Nstate(k, k+3);
		return true;
	}
	if (k >5)
	return false;
}

bool State::goLeft(State & n)
{
	n = *this;
	int k = find9();
	if (k != 0 && k != 3 && k != 6)
	{
		n = n.Nstate(k, k - 1);
		return true;
	}
	if(k==0||k==3||k==6)
	return false;
}

vector<State> State::expand()
{
	vector <State> children;
	State child;

	if (goUp(child))
		children.push_back(child);
	if (goDown(child))
		children.push_back(child);
	if (goLeft(child))
		children.push_back(child);
	if (goRight(child))
		children.push_back(child);

	return children;
}

State State::operator=(State o)
{
	f(i, 8) { state[i] = o.state[i]; }
	return *this;
}

bool operator<(const State & a, const State & o)
{

	return (a.toString() < o.toString());
}

bool InSet(set<State> closed, State s)
{
	if (closed.size() == 0 || (closed.find(s) == closed.end())) return false;
	else return true;
}

bool DFS(stack<State>& frontier, set<State>& closed)
{
	State s;
	if (frontier.empty()) return false;
	s = frontier.top();
	frontier.pop();
	
	if (s.goal())
	{
		cout << "SUCCESS" << endl;
		return true;
	}
	
	if (!InSet(closed,s))
	{
		vector<State> children;
		children = s.expand();
		closed.insert(s);
		for (unsigned int i = 0; i < children.size(); i++)
			frontier.push(children.at(i));

	}
	
	return(DFS(frontier, closed));
}

bool BFS(queue<State>& frontier, set<State>& closed)
{
	State s;
	if (frontier.empty()) return false;
	s = frontier.front();
	frontier.pop();
	if (s.goal())
	{
		cout << "BFS: SUCCESS!" << endl;
		return true;
	}
	if (!InSet(closed, s))
	{
		vector<State> children;
		children = s.expand();
		closed.insert(s);
		for (unsigned int i = 0; i < children.size(); i++)
			frontier.push(children.at(i));
	}
	return BFS(frontier, closed);
}

