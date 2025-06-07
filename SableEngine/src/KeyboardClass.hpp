#pragma once
#include <queue>
#include "KeyboardInputEvent.hpp"

class KeyboardClass
{
public:
	KeyboardClass();
	bool IsPressed(unsigned char key);
	bool IsKeyBufferEmpty();
	bool IsCharBufferEmpty();
	void OnKeyDown(const unsigned char key);
	void OnKeyUp(const unsigned char key);
	void OnChar(const unsigned char key);

	unsigned char ReadChar();
	KeyboardInputEvent ReadKey();
private:
	bool m_keyStates[256];
	std::queue<KeyboardInputEvent> m_keyBuffer;
	std::queue<unsigned char> m_charBuffer;
};

