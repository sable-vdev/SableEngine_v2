#include "MouseClass.hpp"

void MouseClass::OnLeftPressed(int x, int y)
{
	m_leftIsDown = true;
	m_x = x;
	m_y = y;
	m_mouseEventBuffer.push(MouseInputEvent(MouseInputEvent::EventType::LPress, x, y));
}

void MouseClass::OnLeftReleased(int x, int y)
{
	m_leftIsDown = false;
	m_x = x;
	m_y = y;
	m_mouseEventBuffer.push(MouseInputEvent(MouseInputEvent::EventType::LRelease, x, y));
}

void MouseClass::OnRightPressed(int x, int y)
{
	m_rightIsDown = true;
	m_x = x;
	m_y = y;
	m_mouseEventBuffer.push(MouseInputEvent(MouseInputEvent::EventType::RPress, x, y));
}

void MouseClass::OnRightReleased(int x, int y)
{
	m_rightIsDown = false;
	m_x = x;
	m_y = y;
	m_mouseEventBuffer.push(MouseInputEvent(MouseInputEvent::EventType::RRelease, x, y));
}

void MouseClass::OnMiddlePressed(int x, int y)
{
	m_middleIsDown = true;
	m_x = x;
	m_y = y;
	m_mouseEventBuffer.push(MouseInputEvent(MouseInputEvent::EventType::MPress, x, y));
}

void MouseClass::OnMiddleReleased(int x, int y)
{
	m_middleIsDown = false;
	m_x = x;
	m_y = y;
	m_mouseEventBuffer.push(MouseInputEvent(MouseInputEvent::EventType::MRelease, x, y));
}

void MouseClass::OnWheelUp(int x, int y)
{
	m_x = x;
	m_y = y;
	m_mouseEventBuffer.push(MouseInputEvent(MouseInputEvent::EventType::WheelUp, x, y));
}

void MouseClass::OnWheelDown(int x, int y)
{
	m_x = x;
	m_y = y;
	m_mouseEventBuffer.push(MouseInputEvent(MouseInputEvent::EventType::WheelDown, x, y));
}

void MouseClass::OnMouseMove(int x, int y)
{
	m_x = x;
	m_y = y;
	m_mouseEventBuffer.push(MouseInputEvent(MouseInputEvent::EventType::Move, x, y));
}

void MouseClass::OnMouseRawMove(int x, int y)
{
	m_mouseEventBuffer.push(MouseInputEvent(MouseInputEvent::EventType::Raw_Move, x, y));
}

bool MouseClass::IsLeftDown() const
{
	return m_leftIsDown;
}

bool MouseClass::IsMiddleDown() const
{
	return m_rightIsDown;
}

bool MouseClass::IsRightDown() const
{
	return m_middleIsDown;
}

bool MouseClass::IsEventBufferEmpty()
{
	return m_mouseEventBuffer.empty();
}

MouseInputEvent MouseClass::ReadEvent()
{
	if (!IsEventBufferEmpty()) return MouseInputEvent();

	MouseInputEvent event = m_mouseEventBuffer.front();
	m_mouseEventBuffer.pop();
	return event;
}

MousePoint MouseClass::GetMousePosition() const
{
	return { m_x, m_y };
}
