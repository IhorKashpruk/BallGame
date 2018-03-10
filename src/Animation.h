#ifndef TESTC_ANIMATION_H
#define TESTC_ANIMATION_H

#include <SDL2/SDL_timer.h>

class IAnimation {
public:
    virtual ~IAnimation() = default;
    virtual void animate() = 0;
protected:
    virtual void drawAnimation() = 0;
    virtual void updateAnimation() = 0;
};

class Animation : public IAnimation {
public:
    explicit Animation(Uint32 steep) :
            IAnimation(),
            last_time_(SDL_GetTicks()),
            steep_(steep) {}
    virtual ~Animation() = default;
    void animate() override {
        if((last_time_ + steep_) < SDL_GetTicks()) {
            last_time_ = SDL_GetTicks();
            updateAnimation();
        }
        drawAnimation();
    }
protected:
    Uint32 last_time_;
    Uint32 steep_;
};

class TemporaryAnimation : public Animation {
public:
    TemporaryAnimation(Uint32 steep, Uint32 life_time)
            : Animation(steep),
              life_time_(life_time) {}
    virtual ~TemporaryAnimation() = default;
    void animate() override {
        if((SDL_GetTicks() - last_time_) > life_time_) {
            doneAnimation();
            return;
        }
        Animation::animate();
    }
protected:
    virtual void doneAnimation() = 0;
private:
    Uint32 life_time_;
};

// Animation for AUIO
template <class Shape, int width, bool from_center>
class LinearAnimation : public Animation {
public:
    explicit LinearAnimation(Uint32 steep) : Animation(steep) {}
};

template <int width, bool from_center>
class LinearAnimation<pt::Circle<int>, width, from_center> : public Animation {
public:
    LinearAnimation<pt::Circle<int>, width, from_center>(Uint32 steep) : Animation(steep) {}
    void animateShape(pt::Circle<int>& circle, const ColorScheme& colorScheme) {
        // Save previous radius
        int tmp_radius = circle.radius;
        // Change radius
        circle.radius = radius_ + (from_center ? 0 : circle.radius);
        // Draw circle
        Draftsman::getInstance().draw(circle, colorScheme);
        // Restore radius
        circle.radius = tmp_radius;
    }

    void updateAnimation() override {
        static int n = 0;
        if(radius_ == width) {
            if(n <= 2) {
                n++; return;
            } else {
                n = 0;
            }
        }
        radius_ = radius_ >= width ? 0 : radius_ + 1;
    }
private:
    static int radius_ ;
};

template <int width, bool from_center>
int LinearAnimation<pt::Circle<int>, width, from_center>::radius_ {0};

template <int width, bool from_center>
class LinearAnimation<pt::Rectangle<int>, width, from_center> : public Animation {
public:
    LinearAnimation<pt::Rectangle<int>, width, from_center>(Uint32 steep) : Animation(steep) {}
    void animateShape(pt::Rectangle<int>& rectangle, const ColorScheme& colorScheme) {
        // Save previous size
        pt::size<int> tmp_size = rectangle.size_;
        // Change size
        rectangle.size_ = from_center ? size_ : (size_ + rectangle.size_);
        // Draw circle
        Draftsman::getInstance().draw(rectangle, colorScheme);
        // Restore radius
        rectangle.size_ = tmp_size;
    }
    void updateAnimation() override {
        static int n = 0;
        if(size_.w == width) {
            if(n <= 2) {
                n++; return;
            } else {
                n = 0;
            }
        }
        size_.w = size_.w >= width ? 0 : size_.w + 1;
        size_.h = size_.h >= width ? 0 : size_.h + 1;
    }
private:
    static pt::size<int> size_;
};

template <int width, bool from_center>
pt::size<int> LinearAnimation<pt::Rectangle<int>, width, from_center>::size_ = {0,0};

#endif //TESTC_ANIMATION_H
