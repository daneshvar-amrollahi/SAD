#include <iostream>
#include <vector>


#define NEEDS_EVALUATOR_IDX 7

class Customer
{
private:
	int cid;
public:
	Customer(int _cid)
	{
		cid = _cid;
	}
};


class MovingSupervisor
{
private:
	int mid;
public:
	MovingSupervisor(int _mid)
	{
		mid = _mid;
	}

};

class Evaluator
{
private:
	int eid;
public:
	Evaluator(int _eid)
	{
		eid = _eid;
	}

};

class MovingTeam
{
private:
	MovingSupervisor* supervisor;
public:
	MovingTeam(MovingSupervisor* _supervisor)
	{
		supervisor = _supervisor;
	}
};


class System
{
private:
	vector <Customer*> customer;
	vector <Evaluator*> evaluator;
	vector <MovingTeam*> moving_team;
public:
	System()
	{

	}

	void addCustomer()
	{

	}

	void addEvaluator()
	{

	}

	void addMovingTeam()
	{

	}

	void selectTimeSlots()
	{

	}

	void handleMovingRequest(string query)
	{
		cout << "SYSTEM: received query: " << query << endl;
		bool needs_evaluator = stoi(query[NEEDS_EVALUATOR_IDX]);
		
		int id;
	}

};


class Payment
{
private:
	string link;
public:
	Payment(string _link)
	{
		link = _link;
	}

};



int main()
{
	System system;
	while (1)
	{
		string query;
		cin >> query;
		system.handleMovingRequest(query);
	}
	return 0;
}