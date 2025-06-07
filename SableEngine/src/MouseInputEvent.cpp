#include "MouseInputEvent.hpp"

MouseInputEvent::MouseInputEvent() : m_type(EventType::Invalid), m_x(0), m_y(0)
{
}

MouseInputEvent::MouseInputEvent(EventType type, int x, int y) : m_type(type), m_x(x), m_y(y)
{
}

bool MouseInputEvent::IsValid() const
{
	return m_type != EventType::Invalid;
}

MouseInputEvent::EventType MouseInputEvent::GetType() const
{
	return m_type;
}

MousePoint MouseInputEvent::GetMousePosition() const
{
	return MousePoint(GetMouseX(), GetMouseY());
}

int MouseInputEvent::GetMouseX() const
{
	return m_x;
}

int MouseInputEvent::GetMouseY() const
{
	return m_y;
}
