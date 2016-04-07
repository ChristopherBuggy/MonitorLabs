// MonitorLab.cpp : Defines the entry point for the console application.
//Header
////////////////////////////////////////////////////////////////////////
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include <boost/regex.hpp>
#include <iostream>
#include <string>
#include <mutex>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <thread>

using namespace std;

Monitor* monitor = new Monitor();
sf::Text displayText;

void MonitorFetch()
{
	//while (true)
	//{
	std::string text;
	monitor->Fetch(text);
	std::cout << text << std::endl;
	displayText.setString(text);
	//}
}

int main()
{
	BoundedBuffer buffer(200);

	std::thread c1(consumer, 0, std::ref(buffer));
	std::thread c2(consumer, 1, std::ref(buffer));
	std::thread c3(consumer, 2, std::ref(buffer));
	std::thread p1(producer, 0, std::ref(buffer));
	std::thread p2(producer, 1, std::ref(buffer));

	c1.join();
	c2.join();
	c3.join();
	p1.join();
	p2.join();

	return 0;

	/*std::string line = "Subject: Re: You have installed boost successfully";
	boost::regex pat("^Subject: (Re: |Aw: )*(.*)"); \
		boost::smatch matches;
	if (boost::regex_match(line, matches, pat))
		std::cout << matches[2] << std::endl;
	system("PAUSE");
	*/
	//sf::Thread thread(&MonitorFetch);

	//return EXIT_SUCCESS;

}


struct BoundedBuffer {
	int* buffer;
	int capacity;

	int front;
	int rear;
	int count;

	std::mutex lock;

	std::condition_variable not_full;
	std::condition_variable not_empty;

	BoundedBuffer(int capacity) : capacity(capacity), front(0), rear(0), count(0) {
		buffer = new int[capacity];
	}

	~BoundedBuffer() {
		delete[] buffer;
	}

	void deposit(int data) {
		std::unique_lock<std::mutex> l(lock);

		not_full.wait(l, [this]() {return count != capacity; });

		buffer[rear] = data;
		rear = (rear + 1) % capacity;
		++count;

		not_empty.notify_one();
	}

	int fetch() {
		std::unique_lock<std::mutex> l(lock);

		not_empty.wait(l, [this]() {return count != 0; });

		int result = buffer[front];
		front = (front + 1) % capacity;
		--count;

		not_full.notify_one();

		return result;
	}
};

void consumer(int id, BoundedBuffer& buffer) {
	for (int i = 0; i < 50; ++i) {
		int value = buffer.fetch();
		std::cout << "Consumer " << id << " fetched " << value << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
}

void producer(int id, BoundedBuffer& buffer) {
	for (int i = 0; i < 75; ++i) {
		buffer.deposit(i);
		std::cout << "Produced " << id << " produced " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

