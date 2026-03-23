#include <stdlib.h>
#include "Counter.h"
#include "Program.h"

Counter* Counter_New()
{
    Counter* self = (Counter*)malloc(sizeof(Counter));
    memset(self, 0, sizeof(Counter));
    return self;
}

void Counter_Increment(Counter* self)
{
    self->value++;
}

void Counter_Decrement(Counter* self)
{
    if (self->value > 0)
    {
        self->value--;
    }
}

void Counter_Reset(Counter* self)
{
    self->value = 0;
    self->f_ticks = 0;
}

void Counter_Tick(Counter* self)
{
    self->f_ticks++;
}

int Counter_GetValue(Counter* self)
{
    return self->value;
}

int Counter_GetTicks(Counter* self)
{
    return self->f_ticks;
}

bool Counter_IsZero(Counter* self)
{
    return self->value == 0;
}

