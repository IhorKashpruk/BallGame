#ifndef TESTC_ITEXT_H
#define TESTC_ITEXT_H

class IText {
public:
    virtual void setText(const std::string& text) = 0;
    virtual void setText(std::string&& text) = 0;
    virtual std::string getText() = 0;

};

#endif //TESTC_ITEXT_H
