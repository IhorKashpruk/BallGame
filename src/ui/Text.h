#ifndef TESTC_TEXT_H
#define TESTC_TEXT_H

#include <Draftsman.h>
#include <ui/interfaces/IDrawable.h>
#include <string>
#include <theme_properties.h>

class Text : public IDrawable {
    typedef int T;
    typedef pt::point<T> Point;
public:
    explicit Text(std::string text, const Point& point, const float angle)
            : IDrawable(), center_(point), angle_(angle) {
        reset(std::move(text));
    }
    ~Text() override {
        if(texture_)
            SDL_DestroyTexture(texture_);
    }

    std::string& getText() { return text_; }

    void draw() override {
        Draftsman::getInstance().draw(texture_, rect_, angle_);
    }

    void draw(const Point &offset) override {

    }

    void reset(std::string text) {
        text_ = std::move(text);
        if(texture_)
            SDL_DestroyTexture(texture_);
        texture_ = nullptr;
        SDL_Surface* surface;
        surface = TTF_RenderText_Blended(
                Draftsman::getInstance().getFont(),
                text_.c_str(),
                theme::base::text
        );

        texture_ = SDL_CreateTextureFromSurface(Draftsman::getInstance().getRenderer(), surface);
        SDL_FreeSurface(surface);

        int w, h;
        TTF_SizeText(Draftsman::getInstance().getFont(), text_.c_str(), &w, &h);
        rect_.x = center_.x - w/2;
        rect_.y = center_.y - h/2;
        rect_.w = w;
        rect_.h = h;
    }

private:
    SDL_Texture* texture_ = nullptr;
    std::string text_;
    SDL_Rect rect_;
    Point center_;
    float angle_;
};

#endif //TESTC_TEXT_H
