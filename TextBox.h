#pragma once
#pragma warning(disable:4996)
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class EMessage
{
private:
	string Message;
public:
	void Run();
	void Set_Message(string& s) { Message = s; }
};
	





