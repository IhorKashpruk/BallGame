#ifndef TESTC_USERINTERFACEOBJECT_H
#define TESTC_USERINTERFACEOBJECT_H

#include "interfaces/IDrawable.h"
#include "interfaces/IResponsible.h"
#include "logic/Subject.h"
#include "interfaces/IDimensional.h"
#include "ColorScheme.h"

class AUIO : public IDrawable,
             public IResponsible,
             public IDimensional,
             public Subject {
public:
    explicit AUIO()
            : IDrawable(),
              IResponsible(),
              IDimensional(),
              Subject() {}
    virtual ~AUIO() = default;
    virtual const std::string& id() const = 0;
    virtual void setColorScheme(const ColorScheme& colorScheme) = 0;
    virtual void update() {}

};

#endif //TESTC_USERINTERFACEOBJECT_H
