#ifndef CS2SX_PROGRAM_H
#define CS2SX_PROGRAM_H

#pragma once
#include "_forward.h"

struct BateryApp2App
{
    SwitchApp base;
    int f_currentScreen;
    Label* f_titleLabel;
    Label* f_batteryLabel;
    Label* f_batteryStatusLabel;
    ProgressBar* f_batteryBar;
    Label* f_frameLabel;
    Label* f_uptimeLabel;
    Label* f_screenHintLabel;
    Label* f_scoresTitleLabel;
    Label* f_scoresListLabel;
    Label* f_scoresSumLabel;
    Label* f_scoresHighLabel;
    Label* f_nameScoresLabel;
    Button* f_addScoreButton;
    Button* f_resetScoresButton;
    Label* f_namesTitleLabel;
    Label* f_namesListLabel;
    Label* f_namesCountLabel;
    Button* f_addNameButton;
    Label* f_navLabel;
    List_int* f_scores;
    List_char* f_names;
    Dict_str_int* f_nameScores;
    Counter* f_frameCounter;
    Counter* f_uptimeSeconds;
    int f_framesSinceSecond;
    int f_nameIndex;
    const char** f_namePool;
    int f_namePool_count;
};

void BateryApp2App_Init(BateryApp2App* self);
void BateryApp2App_OnInit(BateryApp2App* self);
void BateryApp2App_OnFrame(BateryApp2App* self);
void BateryApp2App_OnExit(BateryApp2App* self);
void BateryApp2App_SwitchScreen(BateryApp2App* self);
void BateryApp2App_OnAddScore(BateryApp2App* self);
void BateryApp2App_OnResetScores(BateryApp2App* self);
void BateryApp2App_RefreshScores(BateryApp2App* self);
void BateryApp2App_OnAddName(BateryApp2App* self);
void BateryApp2App_RefreshNames(BateryApp2App* self);



#endif
