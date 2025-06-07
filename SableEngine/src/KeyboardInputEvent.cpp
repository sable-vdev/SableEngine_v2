#include "KeyboardInputEvent.hpp"
#include "MouseInputEvent.hpp"

KeyboardInputEvent::KeyboardInputEvent() : m_type(EventType::Invalid), m_key(0)
{
}

KeyboardInputEvent::KeyboardInputEvent(const EventType type, const unsigned char key) : m_type(type), m_key(key)
{
}

bool KeyboardInputEvent::IsPressed() const
{
	return m_type == EventType::Pressed;
}

bool KeyboardInputEvent::IsReleased() const
{
	return m_type == EventType::Released;
}

bool KeyboardInputEvent::IsValid() const
{
	return m_type == EventType::Invalid;
}

unsigned char KeyboardInputEvent::GetKeyCode() const
{
	return m_key;
}
