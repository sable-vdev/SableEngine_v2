#pragma once
#include <queue>
#include "MouseInputEvent.hpp"

class MouseClass
{
public:
	void OnLeftPressed(int x, int y);
	void OnLeftReleased(int x, int y);
	void OnRightPressed(int x, int y);
	void OnRightReleased(int x, int y);
	void OnMiddlePressed(int x, int y);
	void OnMiddleReleased(int x, int y);
	void OnWheelUp(int x, int y);
	void OnWheelDown(int x, int y);
	void OnMouseMove(int x, int y);
	void OnMouseRawMove(int x, int y);
	bool IsLeftDown() const;
	bool IsMiddleDown() const;
	bool IsRightDown() const;
	bool IsEventBufferEmpty();
	MouseInputEvent ReadEvent();
	MousePoint GetMousePosition() const;
private:
	std::queue<MouseInputEvent> m_mouseEventBuffer;
	bool m_leftIsDown = false;
	bool m_rightIsDown = false;
	bool m_middleIsDown = false;
	int m_x, m_y;
};

