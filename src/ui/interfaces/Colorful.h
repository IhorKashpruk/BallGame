#ifndef TESTC_COLORFUL_H
#define TESTC_COLORFUL_H

#include <ui/ColorScheme.h>
#include <theme_properties.h>

class Colorful {
public:
    explicit Colorful() = default;
    explicit Colorful(const ColorScheme& colorScheme)
            : colorScheme_(colorScheme) {}
    virtual ~Colorful() = default;

    const ColorScheme& getColorScheme() const { return colorScheme_; }
    void setColorScheme(const ColorScheme& colorScheme) {
        colorScheme_ = colorScheme;
    }

protected:
    ColorScheme colorScheme_ = theme::base::all.def;
};

#endif //TESTC_COLORFUL_H
