#include "entity.hpp"

void entity::set_position( int y, int x )
{
    position_ = point( y, x );
}

void entity::set_position( const point& position )
{
    position_ = position;
}

void entity::set_color( color_pair color )
{
    color_ = static_cast<int>( color );
}

void entity::set_attributes( chtype attributes )
{
    attributes_ = attributes;
}

auto entity::get_position() const -> point
{
    return position_;
}

auto entity::gety() const -> int
{
    return position_.y;
}

auto entity::getx() const -> int
{
    return position_.x;
}

void entity::sety( const int y )
{
    position_.y = y;
}

void entity::setx( const int x )
{
    position_.x = x;
}

void entity::set_width( int width )
{
    width_ = width;
}

void entity::set_height( int height )
{
    height_ = height;
}

auto entity::width() const -> int
{
    return width_;
}

auto entity::height() const -> int
{
    return height_;
}

auto entity::is_destroyable() const -> bool
{
    return true;
}

auto entity::can_collide() const -> bool
{
    return true;
}

auto entity::get_color() const -> int
{
    return color_;
}

auto entity::get_attributes() const -> chtype
{
    return attributes_;
}
