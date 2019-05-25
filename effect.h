#ifndef EFFECT_H
#define EFFECT_H
#include "rpgobj.h"

class FireEffect: public RPGObj{
public:
    FireEffect(objstate _state){initObj(Effect, _state, " ");}
};

#endif // EFFECT_H
