#ifndef TESTC_WORLDCONTEXT_H
#define TESTC_WORLDCONTEXT_H

#include <ui/ModernContext.h>
#include <ui/UIO.h>
#include <Draftsman.h>
#include "WorldWrapper.h"

template <class Logic, template <class> class Shape>
class WorldUIO : public ModernContext<Logic>, public UIO<Shape> {
    typedef int T;
    typedef pt::point<T> Point;
    typedef std::unique_ptr<box2d::WorldWrapper> world_ui_ptr;
public:
    explicit WorldUIO(std::string id, const Shape<T>& shape, box2d::WorldProperties& worldProperties)
            : ModernContext<Logic>(),
              UIO<Shape>(std::move(id), shape),
              world_(new box2d::WorldWrapper(worldProperties)) {}
    explicit WorldUIO(std::string id, const Shape<T>& shape)
            : ModernContext<Logic>(),
              UIO<Shape>(std::move(id), shape),
              world_(nullptr) {}

    virtual ~WorldUIO() {
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
        Draftsman::getInstance().draw(UIO<Shape>::shape_, UIO<Shape>::colorScheme_);
    }
    void draw(const Point& offset) override {

    }

    box2d::WorldWrapper* getWorld() {
        return &*world_;
    }

    void resetWorld(box2d::WorldWrapper* world) {
        world_.reset(world);
    }

private:
    world_ui_ptr world_;
};

#endif //TESTC_WORLDCONTEXT_H