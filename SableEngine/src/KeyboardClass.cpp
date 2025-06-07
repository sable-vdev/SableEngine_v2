#include "KeyboardClass.hpp"

KeyboardClass::KeyboardClass()
{
	for (auto i = 0; i < 256; i++)
	{
		m_keyStates[i] = false;
	}
}

bool KeyboardClass::IsPressed(unsigned char key)
{
	return m_keyStates[key];
}

bool KeyboardClass::IsKeyBufferEmpty()
{
	return m_keyBuffer.empty();
}

bool KeyboardClass::IsCharBufferEmpty()
{
	return m_charBuffer.empty();
}

KeyboardInputEvent KeyboardClass::ReadKey()
{
	if (IsKeyBufferEmpty())
	{
		return KeyboardInputEvent();
	}

	KeyboardInputEvent event = m_keyBuffer.front(); //get first keyboard event in queue
	m_keyBuffer.pop();
	return event;
}

unsigned char KeyboardClass::ReadChar()
{
	if (IsCharBufferEmpty())
	{
		return 0;
	}

	unsigned char e = m_charBuffer.front();
	m_charBuffer.pop();
	return e;
}

void KeyboardClass::OnKeyDown(const unsigned char key)
{
	m_keyStates[key] = true;
	m_keyBuffer.push(KeyboardInputEvent(KeyboardInputEvent::EventType::Pressed, key));

}

void KeyboardClass::OnKeyUp(const unsigned char key)
{
	m_keyStates[key] = false;
	m_keyBuffer.push(KeyboardInputEvent(KeyboardInputEvent::EventType::Released, key));
}

void KeyboardClass::OnChar(const unsigned char key)
{
	m_charBuffer.push(key);
}
