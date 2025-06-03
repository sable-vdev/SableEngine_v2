#pragma once

class KeyboardInputEvent
{
public:
	enum EventType
	{
		Pressed,
		Released,
		Invalid
	};

	KeyboardInputEvent();
	KeyboardInputEvent(const EventType type, const unsigned char key);
	bool IsPressed() const;
	bool IsReleased() const;
	bool IsValid() const;
	unsigned char GetKeyCode() const;

private:
	EventType m_type;
	unsigned char m_key;
};

