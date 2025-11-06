#ifndef C4_ENGINE_ENGINE_H
#define C4_ENGINE_ENGINE_H

#include "./import.h"

typedef struct C4_Engine
{
    void* ctxt;

    void* proc_start;
    void* proc_stop;
    void* proc_input;
    void* proc_output;
    void* proc_tick;
    void* proc_frame;

    paxb8 active;
}
C4_Engine;

typedef paxb8 (C4_Engine_Proc_Start)  (void*, C4_Engine*, Pax_Arena*);
typedef void  (C4_Engine_Proc_Stop)   (void*, C4_Engine*);
typedef paxb8 (C4_Engine_Proc_Input)  (void*, C4_Engine*, Pax_Arena*);
typedef void  (C4_Engine_Proc_Output) (void*, C4_Engine*, Pax_Arena*);
typedef void  (C4_Engine_Proc_Tick)   (void*, C4_Engine*, Pax_Arena*, paxf32);
typedef void  (C4_Engine_Proc_Frame)  (void*, C4_Engine*, Pax_Arena*, paxf32);

paxb8
c4_engine_is_active(C4_Engine* self);

paxb8
c4_engine_play(C4_Engine* self, Pax_Arena* arena, paxiword ticks);

#endif // C4_ENGINE_ENGINE_H
