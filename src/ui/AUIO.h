#ifndef TESTC_USERINTERFACEOBJECT_H
#define TESTC_USERINTERFACEOBJECT_H

#include <ui/interfaces/Identity.h>
#include <ui/interfaces/Colorful.h>
#include "ui/interfaces/IDrawable.h"
#include "ui/interfaces/IResponsible.h"
#include "logic/Subject.h"
#include "ui/interfaces/IDimensional.h"

class AUIO : public IDrawable,
             public IResponsible,
             public IDimensional,
             public Subject,
             public Identity,
             public Colorful {
public:
    explicit AUIO(std::string id)
            : IDrawable(),
              IResponsible(),
              IDimensional(),
              Subject(),
              Identity(std::move(id)),
              Colorful() {}
    virtual ~AUIO() = default;
    virtual void update() {}
};

#endif //TESTC_USERINTERFACEOBJECT_H
