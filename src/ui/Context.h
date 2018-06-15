#ifndef MYGAME_CONTEXT_H
#define MYGAME_CONTEXT_H

#include <vector>
#include <memory>
#include <theme_properties.h>
#include <SDL2/SDL_log.h>
#include <ui/interfaces/Identity.h>
#include "AChecker.h"
#include "interfaces/IDrawable.h"
#include "AUIO.h"
#include "logic/ALogic.h"

class Context : public IDrawable, public AChecker {
    typedef std::shared_ptr<AUIO> uio_sh_ptr;
    typedef std::vector<uio_sh_ptr> vec_uio_ptr;
    typedef std::unique_ptr<AContextLogic> logic_un_ptr;
public:
    Context() : AChecker() {}
    virtual ~Context() {
        uios_.clear();
    }

    Context& add(AUIO* uio) {
        if(uio) {
            uios_.push_back(uio_sh_ptr(uio));
            uio->attach(&*logic_);
        }
        return *this;
    }

    AUIO* get(const std::string id) {
        for(auto& uio: uios_) {
            if(uio->getID() == id) {
                return &*uio;
            }
        }
        return nullptr;
    }

    void update() {
        static std::vector<Event> events = {};
        if(!EventManager::getInstance().empty()) {
            events.clear();
            EventManager::getInstance().get(events);
            executeEvents(events);
        }
        for(auto& uio: uios_) {
            uio->update();
        }
    }

    Context& remove(const std::string& id) {
        uios_.erase(std::remove_if(uios_.begin(), uios_.end(), [&id, this](auto& uio) {
            if(uio->getID() == id) {
                if(uio.get() == this->selected_uio_) {
                    this->selected_uio_ = nullptr;
                }
            }
            return true;
        }));
        return *this;
    }

    Context& removeAll() {
        uios_.clear();
        selected_uio_ = nullptr;
        return *this;
    }

    void resetLogic(AContextLogic* logic) {
        if(logic_) {
            for(auto& uio: uios_) {
                uio->detach(&*logic_);
            }
        }
        if(logic) {
            for(auto& uio: uios_) {
                uio->attach(logic);
            }
        }
        logic_.reset(logic);
    }

    void draw() override {
        for(auto& uio: uios_) {
            uio->draw();
        }
    }

    void draw(const pt::point& offset) override {
        update();
        for(auto& uio: uios_) {
            uio->draw(offset);
        }
    }

    void check(const EVENT &event, const pt::point &point) {
        CONTEXT_EVENT specEventType;
        AUIO* tmp = getUnder(point);
        if(tmp == nullptr) {
            if(selected_uio_) {
                selected_uio_->setColorScheme(theme::base::all.def);
            }
            selected_uio_ = nullptr;
            getPreviousEvent().clear();
            return;
        }
        if(selected_uio_ == tmp) {
            selected_uio_->setColorScheme(theme::base::all.sel);
            specEventType = getPreviousEvent().add(event);
        }else {
            if(selected_uio_)
                selected_uio_->setColorScheme(theme::base::all.def);
            tmp->setColorScheme(theme::base::all.sel);
            getPreviousEvent().clear();
            selected_uio_ = tmp;
            specEventType = getPreviousEvent().add(event);
        }

        displayEvent(specEventType, point);
    }

    void check(const EVENT &event, const char* key) {
        if(selected_uio_ == nullptr)
            return;
        CONTEXT_EVENT specEventType = getPreviousEvent().add(event);
        displayEvent(specEventType,{}, key);
    }

private:
    AUIO* getUnder(const pt::point& point) {
        for (auto &it: uios_) {
            if (it->under(point))
                return &*it;
        }
        return nullptr;
    }
    void displayEvent(const CONTEXT_EVENT& event, const pt::point& point, const char* key="") {
        switch (event) {
            case CONTEXT_EVENT::CLICK_LEFT_BUTTON:
                selected_uio_->setColorScheme(theme::base::all.clk);
                selected_uio_->clickLeftButton(point);
                break;
            case CONTEXT_EVENT::CLICK_RIGHT_BUTTON:
                selected_uio_->setColorScheme(theme::base::all.clk);
                selected_uio_->clickRightButton(point);
                break;
            case CONTEXT_EVENT::ENTER_KEY:
                selected_uio_->enterKey(key);
                break;
            case CONTEXT_EVENT::MOUSE_MOVE:
                selected_uio_->mouseMove(point);
                break;
            case CONTEXT_EVENT::NONE:break;
        }
    }
    void executeEvents(const std::vector<Event>& events) {
        for(const auto& event: events) {
            switch(event.device) {
                case DEVICE::MOUSE: check(event.event, event.point); break;
                case DEVICE::KEYBOARD: check(event.event, event.key); break;
            }
        }
    }
protected:
    vec_uio_ptr uios_;
    logic_un_ptr logic_ {nullptr};
    AUIO* selected_uio_ = nullptr;
};

class IdentityContext : public Context, public Identity {
public:
    explicit IdentityContext(std::string id) : Context(), Identity(std::move(id)) {}
    virtual ~IdentityContext() = default;
private:
};


#endif //MYGAME_CONTEXT_H
