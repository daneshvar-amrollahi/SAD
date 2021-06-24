#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

//#include <bits/stdc++.h>

#include <unistd.h>

#define NEEDS_EVALUATOR_IDX 7
#define MAX_SLOTS 5
#define MAX_CUSTOMERS 5
#define MOVING "MOVING"
#define MAX_EVALUATOR 20
#define MAX_TEAM 20
#define MAX_SUPERVISOR 20
#define PRICE 2
#define WAIT_FOR_RESPONSE() sleep(4)


using namespace std;

int current_time = 0;

typedef int TimeSlot;
typedef vector<TimeSlot> TimeTable;


class Payment
{
private:
	string link;
public:
	Payment(string _link)
	{
		link = _link;
	}

	int payRequest(int cost)
	{
		cout << "Enter credit card id: " << endl;
		string line;
		getline(cin, line);
		cout << "PAYMENT: Payment successful" << endl; 
		return ++current_time;
	}
};


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

	void pay(double cost, string link)
	{
		Payment payment = Payment(link);
		cout << "CUSTOMER "  << cid << ": Paying at " << link << " ..." << endl;


		int date = payment.payRequest(cost);
		cout << "CUSTOMER " << cid << ": Payment Done. Date: " << date << endl;
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

	int status(TimeSlot date , string address , int cost){
		//LOG
		int remaining = rand() % 11;
		int remaining_cost = (remaining * cost) / 100;

		return remaining_cost;
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

	int getId()
	{
		return eid;
	}

	void evaluate(TimeSlot date, string addresss)
	{
		cout << "EVALUATOR " << eid << ": Evaluation Done. Date: " << date << " Address: " << addresss << endl;
		return;
	}
};

class MovingTeam
{
private:
	int tid;
	MovingSupervisor* supervisor;
public:
	MovingTeam(int _tid , MovingSupervisor* _supervisor)
	{
		tid = _tid;
		supervisor = _supervisor;
	}
	int getId(){
		return tid;
	}
	int schedule(TimeSlot date , string address , int cost){
		int remaining_cost = supervisor->status(date , address , cost);
		return remaining_cost;
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
		evaluator.push_back(new Evaluator(eid));
	}

	void addMovingTeam(int tid)
	{
		int mid = rand() % MAX_SUPERVISOR;
		moving_team.push_back(new MovingTeam(tid , new MovingSupervisor(mid)));
	}

	
	TimeTable generateTimeslots() {
		TimeTable res(MAX_SLOTS);
		for (int i = 0; i < MAX_SLOTS; ++i)
			res[i] = i + current_time;
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
		double good_capacity;
		ss >> has_evaluator >> customer_id >> address >> good_capacity;

		auto slot = selectTimeSlots(customer_id);

		current_time++;

		if (has_evaluator)
		{
			int evaluator = rand() % MAX_EVALUATOR;
			evaluate(evaluator, slot, address);
		}

		current_time++;

		double cost = good_capacity * PRICE;

		pay(cost, customer_id);

		current_time++;

		schedule(slot , address , cost);

	}

	void evaluate(int eid, TimeSlot slot, string address){
		
		for (auto &e: evaluator)
			if (e->getId() == eid)
				e->evaluate(slot, address);
	}

	void pay(double cost, int cid){

		string link = "https://paypay.com/?cid=" + to_string(cid);

		for (auto &c: customer)
			if (c->getId() == cid)
				c->pay(cost, link);

	}

	// moving team_id
	void schedule(TimeSlot date , string address , int cost){
		int tid = rand() % MAX_TEAM;	
		//LOG
		for (auto &t: moving_team)
			if (t->getId() == tid){
				int remaining_cost = t->schedule(date , address , cost);
				cout << "SYSTEM Additional charge for customer : " << remaining_cost << endl;
			}
	}

};


void init(System& sys) {
	for (int i = 0; i < MAX_CUSTOMERS; ++i)
		sys.addCustomer(i);

	for (int i = 0 ; i < MAX_EVALUATOR ; i++)
		sys.addEvaluator(i);

	for (int i = 0 ; i < MAX_TEAM ; i++)
		sys.addMovingTeam(i);
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