#ifndef TESTC_SUBJECT_H
#define TESTC_SUBJECT_H

#include <vector>
#include <algorithm>
#include "IObserver.h"

class Subject {
public:
    void attach(IObserver* o) { observers_.push_back(o);}
    void detach(IObserver* o) {
        observers_.erase(
                std::remove(observers_.begin(), observers_.end(), o),
                observers_.end());
    }
    void detachAll() { observers_.clear(); }
    virtual ~Subject() = default;

private:
    std::vector<IObserver*>  observers_{};
protected:
    void notify(Signal&& value) {
        for(auto& it: observers_) {
            it->update(value);
        }
    }
};

#endif //TESTC_SUBJECT_H
