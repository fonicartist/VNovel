#define EVENT_H
#ifdef  EVENT_H

#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

class Event {
private:
	int number;
	std::string speaker, text;



public:
	Event();
	~Event();

};

#endif