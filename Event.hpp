#ifndef EVENT_H
#define EVENT_H

class Event
{
    public:
        enum class Button
        {
            Mouse1,
            Mouse3,
            Q,
            Other
        };

        enum class Type
        {
            Mouse,
            Key,
            Other
        };

        Event()
        {

        }

        Event( Event::Button t_button, int t_y, int t_x ) : m_button( t_button ), m_y( t_y ), m_x( t_x )
        {
            m_type = Type::Mouse;
        }

        Event( Event::Button t_button ) : m_button( t_button )
        {
            m_type = Type::Key;
        }

        virtual ~Event() {}

        Event::Type type()
        {
            return m_type;
        }

        Event::Button pressed()
        {
            return m_button;
        }

        int getMousePosX()
        {
            return m_x;
        }

        int getMousePosY()
        {
            return m_y;
        }

    protected:
        Button m_button{ Button::Other };
        Type m_type{ Type::Other };
        int  m_y{ -1 };
        int  m_x{ -1 };
};

#endif
