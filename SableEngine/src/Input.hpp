#pragma once
#include <queue>

enum EventType
{
	None,
	KeyUp,
	KeyDown
};

class Input
{
public:
	Input();
	bool GetButtonDown(unsigned char key) const;
	bool GetButtonUp(unsigned char key) const;
	bool IsKeyBufferEmpty() const;
	unsigned char GetCharacter();
	void PushCharacter(char key);
public:
	EventType m_eventType[256];
	bool autoRepeatChars = false;
private:
	std::queue<unsigned char> m_charBuffer;
};

