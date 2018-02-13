#ifndef TESTC_LABLE_H
#define TESTC_LABLE_H

#include <ui/interfaces/IText.h>
#include "UIO.h"
#include "Text.h"

template <template <class> class Shape = pt::Rectangle>
class Label : public UIO<Shape>, public IText {
    typedef int T;
public:
    explicit Label(std::string&& id, const Shape<T>& shape, std::string&& text)
            : UIO<Shape>(std::move(id), shape),
              text_(std::move(text), shape.center, shape.angle) {}
    explicit Label(std::string&& id, Shape<T>&& shape, std::string&& text)
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

#endif //TESTC_LABLE_H
