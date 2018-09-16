#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
    public:
        Entity() {}
        virtual ~Entity() {}
        virtual void draw() const = 0;
        virtual void destroy() const = 0;

        enum class ColorPair
        {
            Red = 1,
            Green,
            Yellow,
            Blue,
            Magenta,
            Cyan,
            White
        };

        void setPosition( const int t_y, const int t_x )
        {
            m_y = t_y;
            m_x = t_x;
        }

        void setColorPair( const ColorPair t_color )
        {
            m_color = static_cast<int>( t_color );
        }

        void setAttribiutes( const int t_attributes )
        {
            m_attributes = t_attributes;
        }

    protected:
        int m_y{ 0 };
        int m_x{ 0 };
        int m_color{ 0 };
        int m_attributes{ 0 };
};

#endif //ENTITY_H
