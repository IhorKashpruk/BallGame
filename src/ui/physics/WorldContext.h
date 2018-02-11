#ifndef TESTC_WORLDCONTEXT_H
#define TESTC_WORLDCONTEXT_H

#include <ui/ModernContext.h>
#include <ui/UIO.h>
#include <Draftsman.h>
#include "WorldWrapper.h"

template <class Logic, template <class> class Shape>
class WorldContext : public ModernContext<Logic>, public AUIO {
    typedef int T;
    typedef pt::point<T> Point;
    typedef std::unique_ptr<box2d::WorldWrapper> world_ui_ptr;
public:
    explicit WorldContext(std::string id, const Shape<T>& shape, box2d::WorldProperties& worldProperties)
            : ModernContext<Logic>(std::move(id)),
              AUIO(),
              world_(new box2d::WorldWrapper(worldProperties)),
              shape_(shape){}
    explicit WorldContext(std::string id, const Shape<T>& shape)
            : ModernContext<Logic>(std::move(id)),
              AUIO(),
              world_(nullptr),
              shape_(shape){}


    virtual ~WorldContext() {
        ModernContext<Logic>::uios_.clear();
    };

    void update() override {
        if(world_) {
            world_->step();
        }
        ModernContext<Logic>::update();
    }


    void draw() override {
        if (world_) {
            update();
            ModernContext<Logic>::draw();
        }
        Draftsman::getInstance().draw(shape_, colorScheme_);
    }
    void draw(const Point& offset) override {

    }

    void clickLeftButton(const Point& point) override {
        notify(Signal{ModernContext<Logic>::id_, STATE::LEFT_BUTTON_CLICK, point});
    }

    void clickRightButton(const Point& point) override {
        notify(Signal{ModernContext<Logic>::id_, STATE::RIGHT_BUTTON_CLICK, point});
    }

    void enterKey(const char* key) override {
        notify(Signal{ModernContext<Logic>::id_, STATE::ENTER_KEY, key});
    }

    void mouseMove(const Point& point) override {
        notify(Signal{ModernContext<Logic>::id_, STATE::MOUSE_MOVE, point});
    }

    bool under(Point&& point) override {
        return pt::under(shape_, point);
    }

    bool under(const Point& point) override {
        return pt::under(shape_, point);
    }

    Point center() const override {
        return shape_.center;
    }

    float angle() const override {
        return shape_.angle;
    }

    void setColorScheme(const ColorScheme& colorScheme) override {
        colorScheme_ = colorScheme;
    }

    const std::string& id() const override {
        return ModernContext<Logic>::id_;
    }

    box2d::WorldWrapper* getWorld() {
        return &*world_;
    }

    void resetWorld(box2d::WorldWrapper* world) {
        world_.reset(world);
    }

private:
    world_ui_ptr world_;
    Shape<T> shape_;
    ColorScheme colorScheme_ = theme::base::all.def;
};

#endif //TESTC_WORLDCONTEXT_H
