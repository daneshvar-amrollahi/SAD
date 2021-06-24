#include <iostream>
#include <vector>
#include <stringstream>

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

	void addCustomer(int cid)
	{

	}

	void addEvaluator(int eid)
	{

	}

	void addMovingTeam(int mid)
	{

	}

	void selectTimeSlots(int customer_id)
	{
		//random time slots
		//customer ba folan id az beine in entekhab kon
	}

	//TODO Query handler

	void handleQuery(string query)
	{
		stringstream ss(query);	
		string query_type;	
		bool has_evaluator;
		int customer_id;

		ss >> query_type >> has_evaluator >> customer_id;
	}

	void evaluate(int eid){
		// be yaroo begoo evaluate kon
	}

	void pay(double cost , int cid){

	}

	// moving team_id
	void schedule(int mid , string date , string addresss){

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