#ifndef C4_ENGINE_ENGINE_C
#define C4_ENGINE_ENGINE_C

#include "./engine.h"

paxb8
c4_engine_start(C4_Engine* self, Pax_Arena* arena)
{
    C4_Engine_Proc_Start* proc =
        pax_as(C4_Engine_Proc_Start*, self->proc_start);

    self->active = 0;

    if (self->proc_start != 0)
        self->active = proc(self->ctxt, self, arena);

    return self->active;
}

void
c4_engine_stop(C4_Engine* self)
{
    C4_Engine_Proc_Stop* proc =
        pax_as(C4_Engine_Proc_Stop*, self->proc_stop);

    if (self->proc_stop != 0) proc(self->ctxt, self);
}

paxb8
c4_engine_input(C4_Engine* self, Pax_Arena* arena)
{
    C4_Engine_Proc_Input* proc =
        pax_as(C4_Engine_Proc_Input*, self->proc_input);

    self->active = 0;

    if (self->proc_input != 0)
        self->active = proc(self->ctxt, self, arena);

    return self->active;
}

void
c4_engine_output(C4_Engine* self, Pax_Arena* arena)
{
    C4_Engine_Proc_Output* proc =
        pax_as(C4_Engine_Proc_Output*, self->proc_output);

    if (self->proc_output != 0) proc(self->ctxt, self, arena);
}

void
c4_engine_tick(C4_Engine* self, Pax_Arena* arena, paxf32 slice)
{
    C4_Engine_Proc_Tick* proc =
        pax_as(C4_Engine_Proc_Tick*, self->proc_tick);

    if (self->proc_tick != 0) proc(self->ctxt, self, arena, slice);
}

void
c4_engine_frame(C4_Engine* self, Pax_Arena* arena, paxf32 slice)
{
    C4_Engine_Proc_Frame* proc =
        pax_as(C4_Engine_Proc_Frame*, self->proc_frame);

    if (self->proc_frame != 0) proc(self->ctxt, self, arena, slice);
}

paxb8
c4_engine_is_active(C4_Engine* self)
{
    return self->active != 0 ? 1 : 0;
}

paxb8
c4_engine_play(C4_Engine* self, Pax_Arena* arena, paxiword ticks)
{
    Pax_Clock clock = pax_clock_create(arena);

    paxf32 slice = 1.0 / pax_as(paxf32, ticks);
    paxf32 time  = 0;

    if (c4_engine_start(self, arena) == 0)
        return 0;

    while (c4_engine_is_active(self) != 0) {
        time += pax_clock_elapsed(clock);

        if (c4_engine_input(self, arena) == 0)
            break;

        c4_engine_frame(self, arena, slice);

        for (; time >= slice; time -= slice)
            c4_engine_tick(self, arena, slice);

        c4_engine_output(self, arena);
    }

    c4_engine_stop(self);

    return 1;
}

#endif // C4_ENGINE_ENGINE_C
