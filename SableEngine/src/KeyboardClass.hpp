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
	KeyboardInputEvent ReadKey();
	unsigned char ReadChar();
	void OnKeyPressed(const unsigned char key);
	void OnKeyReleased(const unsigned char key);
	void OnChar(const unsigned key);
public:
	bool autoRepeatKeys = false;
	bool autoRepeatChars = false;
private:
	bool m_keyStates[256];
	std::queue<KeyboardInputEvent> m_keyBuffer;
	std::queue<unsigned char> m_charBuffer;
};

