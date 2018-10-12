#ifndef EVENT_H
#define EVENT_H

struct Keyboard
{
    enum class Key
    {
        Unknown,
        Q
    };
};

struct Mouse
{
    enum class Button
    {
        Unknown,
        Button1,
        Button3
    };
};

struct KeyEvent
{
    Keyboard::Key code{ Keyboard::Key::Unknown };
};

struct MouseButtonEvent
{
    Mouse::Button button{ Mouse::Button::Unknown };
};

struct MouseMoveEvent
{
    int y{ -1 };
    int x{ -1 };
};

struct Event
{
    enum class Type
    {
        Unknown,
        KeyPressed,
        MouseButtonPressed,
        MouseMoved
    };

    Event() {}
    virtual ~Event() {}

    Type             type{ Type::Unknown };
    KeyEvent         key;
    MouseButtonEvent mouseButton;
    MouseMoveEvent   mouseMove;
};

#endif
