#ifndef MONITOR_H
#define MONITOR_H

class Monitor
{
private:
	std::string buf[100];
	int front;//index of first full slot
	int rear;//index of first empty slot. rear = (front+count) % n
	int count;//number of full slots
	bool not_full;//signalled when count < n
	bool not_empty;//signalled when count > n

	bool newMessage;
public:
	Monitor();
	~Monitor();
	void Deposit(std::string data);
	void Fetch(std::string &result);

	bool Empty();
	bool NewMsgAdded();
};

#endif
