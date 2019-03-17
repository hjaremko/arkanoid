#ifndef EVENT_H
#define EVENT_H

struct keyboard
{
    enum class key
    {
        unknown,
        Q
    };
};

struct mouse
{
    enum class button
    {
        unknown,
        button1,
        button3
    };
};

struct key_event
{
    keyboard::key code{ keyboard::key::unknown };
};

struct mouse_button_event
{
    mouse::button button{ mouse::button::unknown };
};

struct mouse_move_event
{
    int y{ -1 };
    int x{ -1 };
};

struct event
{
    enum class type
    {
        unknown,
        key_pressed,
        mouse_pressed,
        mouse_moved
    };

    event() = default;
    virtual ~event() = default;

    type               type{ type::unknown };
    key_event          key;
    mouse_button_event mouse_button;
    mouse_move_event   mouse_move;
};

#endif
