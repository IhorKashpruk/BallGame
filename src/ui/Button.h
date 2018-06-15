#ifndef TESTC_BUTTON_H
#define TESTC_BUTTON_H

#include <ui/interfaces/IText.h>
#include "UIO.h"
#include "Text.h"

template <class Shape = pt::Rectangle>
class Button : public UIO<Shape>, public IText {
public:
    explicit Button(std::string&& id, const Shape& shape, std::string&& text)
            : UIO<Shape>(std::move(id), shape),
            text_(std::move(text), shape.center, shape.angle) {}
    explicit Button(std::string&& id, Shape&& shape, std::string&& text)
            : UIO<Shape>(std::move(id), shape),
            text_(std::move(text), shape.center, shape.angle) {}
    std::string getText()                   override { return text_.getText(); }
    void setText(const std::string& text)   override { text_.reset(text); }
    void setText(std::string&& text)        override { text_.reset(text); }

    void draw() override {
        UIO<Shape>::draw();
        text_.draw();
    }

private:
    Text text_;
};

#endif //TESTC_BUTTON_H
