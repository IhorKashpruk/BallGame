#ifndef TESTC_LEVELMANAGER_H
#define TESTC_LEVELMANAGER_H

#include "Factory.h"
#include "ContextManager.h"
#include "JsonReader.h"

namespace level {
    constexpr const char* levels[] {
            "levels/1.json",
            "levels/2.json",
            "levels/3.json",
            "levels/4.json",
            "levels/5.json"
    };

    template<class T, size_t N>
    constexpr size_t size(T (&)[N]) { return N; }

    constexpr const size_t count_of_levels = size(levels);

    class LevelManager {
    NOW_YOU_ARE_SINGLETON(LevelManager)
    public:

        void buildNextLevel() {
            if((int)count_of_levels > (currentLevel_+1)) {
                if(JsonReader::exists(levels[currentLevel_+1])) {
                    WorldUIO<WorldLogic, pt::Rectangle>* worldContext
                            = dynamic_cast<WorldUIO<WorldLogic, pt::Rectangle> *>
                            (ContextManager::getInstance().get("game_context")->get("world_context"));
                    worldContext->removeAll();
                    json j = JsonReader::get(levels[currentLevel_+1]);
                    factory::build(j, *worldContext);
                }
            }
//            currentLevel_++;
        }

    private:
        int currentLevel_ {-1};
    };

}

#endif //TESTC_LEVELMANAGER_H
