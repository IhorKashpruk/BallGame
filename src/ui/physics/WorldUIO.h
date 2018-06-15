#ifndef TESTC_WORLDCONTEXT_H
#define TESTC_WORLDCONTEXT_H

#include <ui/ModernContext.h>
#include <ui/UIO.h>
#include <Draftsman.h>
#include <theme_properties.h>
#include <ui/logic/Camera.h>
#include "WorldWrapper.h"
#include "ContactListener.h"

template <class Logic, class Shape>
class WorldUIO : public ModernContext<Logic>, public UIO<Shape> {
    typedef std::unique_ptr<box2d::WorldWrapper> world_ui_ptr;
    typedef std::unique_ptr<RectangleCamera> camera_ptr;
public:
    explicit WorldUIO(std::string id, const Shape& shape, box2d::WorldWrapper::properties& prop)
            : ModernContext<Logic>(),
              UIO<Shape>(std::move(id), shape),
              world_(new box2d::WorldWrapper(prop)) {
        camera_.reset(new RectangleCamera(pt::Rectangle({}, 0, {100,100}), shape.center));
    }
    explicit WorldUIO(std::string id, const Shape& shape)
            : ModernContext<Logic>(),
              UIO<Shape>(std::move(id), shape),
              world_(nullptr) {
        camera_.reset(new RectangleCamera(pt::Rectangle({}, 0, {100,100}), shape.center));
    }

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
            SDL_Log("offset: %d", camera_->getOffset().x);
            ModernContext<Logic>::draw(camera_->getOffset());
        }
        Draftsman::getInstance().draw(UIO<Shape>::shape_, UIO<Shape>::colorScheme_);
        if(UIO<Shape>::colorScheme_ == theme::base::all.clk) {
            UIO<Shape>::colorScheme_ = theme::base::all.sel;
        }
    }
    void draw(const pt::point& offset) override {
        if (world_) {
            ModernContext<Logic>::draw(offset);
        }
        Draftsman::getInstance().draw(UIO<Shape>::shape_, UIO<Shape>::colorScheme_);
        if(UIO<Shape>::colorScheme_ == theme::base::all.clk) {
            UIO<Shape>::colorScheme_ = theme::base::all.sel;
        }
    }

    box2d::WorldWrapper* getWorld() {
        return &*world_;
    }

    void resetWorld(box2d::WorldWrapper* world) {
        world_.reset(world);
        world_->getWorld()->SetContactListener(new box2d::ContactListener());
    }

    RectangleCamera* getCamera() {
        return camera_.get();
    }

private:
    world_ui_ptr world_;
    camera_ptr camera_;
};

#endif //TESTC_WORLDCONTEXT_H
