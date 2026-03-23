// Auto-generiert von CS2SX -- nicht manuell bearbeiten
#include <stdlib.h>
#include <string.h>
#include "_forward.h"
#include "Counter.h"
#include "Program.h"

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    BateryApp2App app;
    memset(&app, 0, sizeof(BateryApp2App));
    BateryApp2App_Init(&app);
    SwitchApp_Run((SwitchApp*)&app);

    return 0;
}
