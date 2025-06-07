#pragma once
#include "Logger.hpp"
struct MousePoint
{
	int x, y;
};
class MouseInputEvent
{
public:
	enum EventType
	{
		LPress,
		LRelease,
		RPress,
		RRelease,
		MPress,
		MRelease,
		WheelUp,
		WheelDown,
		Move,
		Raw_Move,
		Invalid
	};
	
	MouseInputEvent();
	MouseInputEvent(EventType type, int x, int y);
	bool IsValid() const;
	EventType GetType() const;
	MousePoint GetMousePosition() const;
	int GetMouseX() const;
	int GetMouseY() const;
private:
	EventType m_type;
	int m_x;
	int m_y;
};