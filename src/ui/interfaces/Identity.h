#ifndef TESTC_IDENTITY_H
#define TESTC_IDENTITY_H

#include <string>

class Identity {
public:
    explicit Identity(std::string id) : id_(std::move(id)) {}
    virtual ~Identity() = default;

    std::string getID() const { return id_; }
    void setID(std::string id) { id_ = std::move(id); }

protected:
    std::string id_;
};

#endif //TESTC_IDENTITY_H
