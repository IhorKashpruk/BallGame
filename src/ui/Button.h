#ifndef TESTC_BUTTON_H
#define TESTC_BUTTON_H

#include "UIO.h"
#include "Text.h"

class IButton {
public:
    virtual void setText(const std::string& text) = 0;
    virtual void setText(std::string&& text) = 0;
    virtual std::string getText() = 0;

};

template <template <class> class Shape = pt::Rectangle>
class Button : public UIO<Shape>, public IButton {
    typedef int T;
public:
    explicit Button(std::string&& id, const Shape<T>& shape, std::string&& text)
            : UIO<Shape>(std::move(id), shape),
            text_(std::move(text), shape.center, shape.angle) {}
    explicit Button(std::string&& id, Shape<T>&& shape, std::string&& text)
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
