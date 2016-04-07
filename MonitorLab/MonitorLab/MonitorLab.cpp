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
	/*// Create the main window 
	sf::RenderWindow window(sf::VideoMode(600, 400, 32), "SFML First Program");

	window.setFramerateLimit(60);

	/* initialize random seed: */
	/*srand(time(NULL));

	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	//create a formatted text string
	sf::Text text;
	text.setFont(font);
	text.setString("Hello World");
	text.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	text.setPosition(20, 40);
	text.setCharacterSize(40);

	/*scrolling background stuff*/
	/*int backgroundScrollSpeed = 1;
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("Assets/background.png");
	sf::Sprite background1;
	background1.setTexture(backgroundTexture);
	background1.setPosition(0, 0);
	background1.scale(3, 2);
	background1.setColor(sf::Color::Cyan);
	sf::Sprite background2;
	background2.setTexture(backgroundTexture);
	background2.setPosition(0, -400);
	background2.scale(3, 2);
	background2.setColor(sf::Color::Cyan);

	Player* player = new Player();

	std::vector<Enemy*> enemies;
	sf::Clock spawnClock;
	spawnClock.restart();

	displayText.setFont(font);
	displayText.setPosition(20, 20);
	displayText.setString("");
	displayText.setColor(sf::Color::Blue);

	//std::thread t1;
	sf::Thread thread(&MonitorFetch);

	sf::Clock messageClock;
	messageClock.restart();

	int score = 0;
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setPosition(SCREENWIDTH - 120, 20);
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setColor(sf::Color::Blue);

	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

			//space = shoot
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Space))
			{
				player->Shoot();
				shootSound.play();
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::F))
			{
				//std::string text; 
				//monitor->Fetch(text);
				//std::cout << text << std::endl;
				//displayText.setString(text);

			}
		}

		if (messageClock.getElapsedTime().asSeconds() > 0.5)
		{
			if (monitor->NewMsgAdded() == true)
				thread.launch();
			else std::cout << "No new messages were found." << std::endl;
			messageClock.restart();
		}

		//prepare frame
		window.clear();

		//scroll the background
		if (background1.getPosition().y < 400)
			background1.setPosition(background1.getPosition().x, background1.getPosition().y + backgroundScrollSpeed);
		else background1.setPosition(0, -395);
		if (background2.getPosition().y < 400)
			background2.setPosition(background2.getPosition().x, background2.getPosition().y + backgroundScrollSpeed);
		else background2.setPosition(0, -395);

		//right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			player->Strafe(1);
		//left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			player->Strafe(2);


		player->Update();
		for (auto it = enemies.begin(); it != enemies.end();)
		{
			if (player->BulletEnemyCollisions(*it))//if a bullet and enemy collide
			{
				delete * it;//delete the pointer
				it = enemies.erase(it);//erase the object(calls the objects destructor)
				hitSound.play();
				monitor->Deposit("Enemy Killed");
				score += 25;
				scoreText.setString("Score: " + std::to_string(score));
			}
			else ++it;
		}

		if (spawnClock.getElapsedTime().asSeconds() > 5)
		{
			Enemy* e = new Enemy();
			enemies.push_back(e);
			spawnClock.restart();
			monitor->Deposit("Enemy Spawned");
		}

		if (score == 100)
		{
			background1.setColor(sf::Color::Red);
			background2.setColor(sf::Color::Red);
		}

		//draw frame items
		window.draw(background1);
		window.draw(background2);

		player->DrawBullets(window);
		window.draw(*player);


		for (int i = 0; i < enemies.size(); i++)
		{
			enemies.at(i)->Update();
			window.draw(*enemies.at(i));
		}

		//std::thread t1(MonitorFetch);

		window.draw(displayText);
		window.draw(scoreText);

		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame*/
	std::string line = "Subject: Re: You have installed boost successfully";
	boost::regex pat("^Subject: (Re: |Aw: )*(.*)"); \
		boost::smatch matches;
	if (boost::regex_match(line, matches, pat))
		std::cout << matches[2] << std::endl;
	system("PAUSE");
	
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

