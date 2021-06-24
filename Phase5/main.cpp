// #include <iostream>
// #include <vector>
// #include <string>
// #include <sstream>
// #include <algorithm>

#include <bits/stdc++.h>

#define NEEDS_EVALUATOR_IDX 7
#define MAX_SLOTS 5
#define MAX_CUSTOMERS 5
#define MOVING "MOVING"

using namespace std;

typedef int TimeSlot;
typedef vector<TimeSlot> TimeTable;

class Customer
{
private:
	int cid;
public:
	Customer(int _cid)
	{
		cid = _cid;
	}

	int getId() {
		return cid;
	}

	TimeSlot chooseTimeSlot() {
		string response;
		getline(cin, response);
		return stoi(response);
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

	int evaluator_idx = 0;

public:
	System()
	{

	}

	void addCustomer(int cid)
	{
		customer.push_back(new Customer(cid));
	}

	void addEvaluator(int eid)
	{

	}

	void addMovingTeam(int mid)
	{

	}

	
	TimeTable generateTimeslots() {
		TimeTable res(MAX_SLOTS);
		for (int i = 0; i < MAX_SLOTS; ++i)
			res[i] = i;
		random_shuffle(res.begin(), res.end());
		return res;
	}

	string showTable(TimeTable& table) {
		string res = "[";
		bool flag = false;
		for (auto t : table) {
			if (flag)
				res += ", ";
			flag = true;
			res += to_string(t);
		}
		res += "]";
		return res;
	}

	TimeSlot selectTimeSlots(int customer_id)
	{
		auto table = generateTimeslots();
		cout << "Available timeslots for user " << customer_id << ": ";
		cout << showTable(table) << '\n';

		TimeSlot ret = -1;
		for (auto& c : customer)
			if (c->getId() == customer_id)
				ret = c->chooseTimeSlot();

		assert (ret != -1);
		return ret;
	}

	//TODO Query handler
	void handleQuery(string query)
	{
		stringstream ss(query);	
		string query_type;
		ss >> query_type;

		if (query_type == MOVING)
			handleMoving(ss);

	}

	void handleMoving(stringstream& ss) {
		bool has_evaluator;
		int customer_id;
		string address;
		ss >> has_evaluator >> customer_id >> address;

		auto slot = selectTimeSlots(customer_id);
			cout << "boom mf with timeslut " << slot << '\n';
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

void init(System& sys) {
	for (int i = 0; i < MAX_CUSTOMERS; ++i)
		sys.addCustomer(i);
}

int main()
{
	System system;
	init(system);

	string query;
	while (getline(cin, query))
		system.handleQuery(query);
	return 0;
}