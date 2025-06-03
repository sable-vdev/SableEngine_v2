#include "Input.hpp"

Input::Input()
{
    for (int i = 0; i < 256; i++)
    {
        m_eventType[i] = EventType::None;
    }
}

bool Input::GetButtonDown(unsigned char key) const
{
    return m_eventType[key] == EventType::KeyDown;
}

bool Input::GetButtonUp(unsigned char key) const
{
    return m_eventType[key] == EventType::KeyUp;
}

bool Input::IsKeyBufferEmpty() const
{
    return m_charBuffer.empty();
}

unsigned char Input::GetCharacter()
{
    if (IsKeyBufferEmpty())
    {
        return 0;
    }
    unsigned char key = m_charBuffer.front();
    m_charBuffer.pop();
    return key;
}

void Input::PushCharacter(char key)
{
    m_charBuffer.push(key);
}
