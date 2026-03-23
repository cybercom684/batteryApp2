#include <stdlib.h>
#include "Counter.h"
#include "Program.h"

void BateryApp2App_Init(BateryApp2App* self)
{
    ((SwitchApp*)self)->OnInit = (void(*)(SwitchApp*))BateryApp2App_OnInit;
    ((SwitchApp*)self)->OnFrame = (void(*)(SwitchApp*))BateryApp2App_OnFrame;
    ((SwitchApp*)self)->OnExit = (void(*)(SwitchApp*))BateryApp2App_OnExit;
}

void BateryApp2App_OnInit(BateryApp2App* self)
{
    psmInitialize();
    self->f_scores = List_int_New();
    self->f_names = List_char_New();
    self->f_nameScores = Dict_str_int_New();
    self->f_frameCounter = Counter_New();
    self->f_uptimeSeconds = Counter_New();
    self->f_currentScreen = 0;
    self->f_framesSinceSecond = 0;
    self->f_nameIndex = 0;
    self->f_namePool = (const char**)malloc(6 * sizeof(const char*));
    self->f_namePool_count = 6;
    self->f_namePool[0] = "Alice";
    self->f_namePool[1] = "Bob";
    self->f_namePool[2] = "Charlie";
    self->f_namePool[3] = "Diana";
    self->f_namePool[4] = "Eve";
    self->f_namePool[5] = "Frank";
    List_int_Add(self->f_scores, 142);
    List_int_Add(self->f_scores, 89);
    List_int_Add(self->f_scores, 256);
    List_int_Add(self->f_scores, 73);
    List_int_Add(self->f_scores, 310);
    List_char_Add(self->f_names, "Alice");
    List_char_Add(self->f_names, "Bob");
    Dict_str_int_Add(self->f_nameScores, "Alice", 142);
    Dict_str_int_Add(self->f_nameScores, "Bob", 89);
    Dict_str_int_Add(self->f_nameScores, "Charlie", 256);
    self->f_titleLabel = Label_New("=== CS2SX Dashboard ===");
    self->f_titleLabel->base.x = 5;
    self->f_titleLabel->base.y = 1;
    self->f_batteryLabel = Label_New("Battery: --%");
    self->f_batteryLabel->base.x = 5;
    self->f_batteryLabel->base.y = 3;
    self->f_batteryBar = ProgressBar_New(30);
    self->f_batteryBar->base.x = 5;
    self->f_batteryBar->base.y = 4;
    self->f_batteryStatusLabel = Label_New("Status: --");
    self->f_batteryStatusLabel->base.x = 5;
    self->f_batteryStatusLabel->base.y = 5;
    self->f_frameLabel = Label_New("Frames: 0");
    self->f_frameLabel->base.x = 5;
    self->f_frameLabel->base.y = 7;
    self->f_uptimeLabel = Label_New("Uptime: 0s");
    self->f_uptimeLabel->base.x = 5;
    self->f_uptimeLabel->base.y = 8;
    self->f_screenHintLabel = Label_New("L/R = Switch Screen");
    self->f_screenHintLabel->base.x = 5;
    self->f_screenHintLabel->base.y = 27;
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_titleLabel);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_batteryLabel);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_batteryBar);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_batteryStatusLabel);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_frameLabel);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_uptimeLabel);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_screenHintLabel);
    self->f_scoresTitleLabel = Label_New("=== Highscores ===");
    self->f_scoresTitleLabel->base.x = 5;
    self->f_scoresTitleLabel->base.y = 1;
    self->f_scoresTitleLabel->base.visible = 0;
    self->f_scoresListLabel = Label_New("...");
    self->f_scoresListLabel->base.x = 5;
    self->f_scoresListLabel->base.y = 3;
    self->f_scoresListLabel->base.visible = 0;
    self->f_scoresSumLabel = Label_New("Sum: 0");
    self->f_scoresSumLabel->base.x = 5;
    self->f_scoresSumLabel->base.y = 14;
    self->f_scoresSumLabel->base.visible = 0;
    self->f_scoresHighLabel = Label_New("Best: 0");
    self->f_scoresHighLabel->base.x = 5;
    self->f_scoresHighLabel->base.y = 15;
    self->f_scoresHighLabel->base.visible = 0;
    self->f_nameScoresLabel = Label_New("NameScores: --");
    self->f_nameScoresLabel->base.x = 5;
    self->f_nameScoresLabel->base.y = 17;
    self->f_nameScoresLabel->base.visible = 0;
    self->f_addScoreButton = Button_New("[X] Add Random Score");
    self->f_addScoreButton->base.x = 5;
    self->f_addScoreButton->base.y = 20;
    self->f_addScoreButton->base.visible = 0;
    self->f_addScoreButton->OnClick = (void(*)(void*))BateryApp2App_OnAddScore;
    self->f_resetScoresButton = Button_New("[Y] Reset Scores");
    self->f_resetScoresButton->base.x = 5;
    self->f_resetScoresButton->base.y = 22;
    self->f_resetScoresButton->base.visible = 0;
    self->f_resetScoresButton->OnClick = (void(*)(void*))BateryApp2App_OnResetScores;
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_scoresTitleLabel);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_scoresListLabel);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_scoresSumLabel);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_scoresHighLabel);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_nameScoresLabel);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_addScoreButton);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_resetScoresButton);
    self->f_namesTitleLabel = Label_New("=== Players ===");
    self->f_namesTitleLabel->base.x = 5;
    self->f_namesTitleLabel->base.y = 1;
    self->f_namesTitleLabel->base.visible = 0;
    self->f_namesListLabel = Label_New("...");
    self->f_namesListLabel->base.x = 5;
    self->f_namesListLabel->base.y = 3;
    self->f_namesListLabel->base.visible = 0;
    self->f_namesCountLabel = Label_New("Count: 0");
    self->f_namesCountLabel->base.x = 5;
    self->f_namesCountLabel->base.y = 18;
    self->f_namesCountLabel->base.visible = 0;
    self->f_addNameButton = Button_New("[X] Add Player");
    self->f_addNameButton->base.x = 5;
    self->f_addNameButton->base.y = 20;
    self->f_addNameButton->base.visible = 0;
    self->f_addNameButton->OnClick = (void(*)(void*))BateryApp2App_OnAddName;
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_namesTitleLabel);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_namesListLabel);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_namesCountLabel);
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_addNameButton);
    self->f_navLabel = Label_New("[L] Prev  [R] Next  [+] Exit");
    self->f_navLabel->base.x = 5;
    self->f_navLabel->base.y = 28;
    SwitchApp_Add((SwitchApp*)self, (Control*)self->f_navLabel);
    BateryApp2App_RefreshScores(self);
    BateryApp2App_RefreshNames(self);
}

void BateryApp2App_OnFrame(BateryApp2App* self)
{
    Counter_Increment(self->f_frameCounter);
    self->f_framesSinceSecond++;
    if (self->f_framesSinceSecond >= 60)
    {
        Counter_Increment(self->f_uptimeSeconds);
        self->f_framesSinceSecond = 0;
    }
    if ((((SwitchApp*)self)->kDown & HidNpadButton_R))
    {
        self->f_currentScreen = self->f_currentScreen + 1;
        if (self->f_currentScreen > 2)
        {
            self->f_currentScreen = 0;
        }
        BateryApp2App_SwitchScreen(self);
    }
    if ((((SwitchApp*)self)->kDown & HidNpadButton_L))
    {
        self->f_currentScreen = self->f_currentScreen - 1;
        if (self->f_currentScreen < 0)
        {
            self->f_currentScreen = 2;
        }
        BateryApp2App_SwitchScreen(self);
    }
    if ((((SwitchApp*)self)->kDown & HidNpadButton_X))
    {
        if (self->f_currentScreen == 1)
        {
            BateryApp2App_OnAddScore(self);
        }
        if (self->f_currentScreen == 2)
        {
            BateryApp2App_OnAddName(self);
        }
    }
    if ((((SwitchApp*)self)->kDown & HidNpadButton_Y))
    {
        if (self->f_currentScreen == 1)
        {
            BateryApp2App_OnResetScores(self);
        }
    }
    if (self->f_currentScreen == 0)
    {
        unsigned int battery = 0;
        psmGetBatteryChargePercentage(&battery);
        snprintf(_cs2sx_strbuf, sizeof(_cs2sx_strbuf), "Battery: %u%%", battery);
    Label_SetText(self->f_batteryLabel, _cs2sx_strbuf);
        self->f_batteryBar->value = (int)battery;
        if (battery > 60)
        {
            Label_SetText(self->f_batteryStatusLabel, "Status: Good");
        }
        else if (battery > 20)
        {
            Label_SetText(self->f_batteryStatusLabel, "Status: Low");
        }
        else
        {
            Label_SetText(self->f_batteryStatusLabel, "Status: CRITICAL!");
        }
        snprintf(_cs2sx_strbuf, sizeof(_cs2sx_strbuf), "Frames: %d", Counter_GetValue(self->f_frameCounter));
    Label_SetText(self->f_frameLabel, _cs2sx_strbuf);
        snprintf(_cs2sx_strbuf, sizeof(_cs2sx_strbuf), "Uptime: %ds", Counter_GetValue(self->f_uptimeSeconds));
    Label_SetText(self->f_uptimeLabel, _cs2sx_strbuf);
    }
}

void BateryApp2App_OnExit(BateryApp2App* self)
{
    psmExit();
}

void BateryApp2App_SwitchScreen(BateryApp2App* self)
{
    self->f_titleLabel->base.visible = 0;
    self->f_batteryLabel->base.visible = 0;
    self->f_batteryBar->base.visible = 0;
    self->f_batteryStatusLabel->base.visible = 0;
    self->f_frameLabel->base.visible = 0;
    self->f_uptimeLabel->base.visible = 0;
    self->f_screenHintLabel->base.visible = 0;
    self->f_scoresTitleLabel->base.visible = 0;
    self->f_scoresListLabel->base.visible = 0;
    self->f_scoresSumLabel->base.visible = 0;
    self->f_scoresHighLabel->base.visible = 0;
    self->f_nameScoresLabel->base.visible = 0;
    self->f_addScoreButton->base.visible = 0;
    self->f_resetScoresButton->base.visible = 0;
    self->f_namesTitleLabel->base.visible = 0;
    self->f_namesListLabel->base.visible = 0;
    self->f_namesCountLabel->base.visible = 0;
    self->f_addNameButton->base.visible = 0;
    if (self->f_currentScreen == 0)
    {
        self->f_titleLabel->base.visible = 1;
        self->f_batteryLabel->base.visible = 1;
        self->f_batteryBar->base.visible = 1;
        self->f_batteryStatusLabel->base.visible = 1;
        self->f_frameLabel->base.visible = 1;
        self->f_uptimeLabel->base.visible = 1;
        self->f_screenHintLabel->base.visible = 1;
    }
    if (self->f_currentScreen == 1)
    {
        self->f_scoresTitleLabel->base.visible = 1;
        self->f_scoresListLabel->base.visible = 1;
        self->f_scoresSumLabel->base.visible = 1;
        self->f_scoresHighLabel->base.visible = 1;
        self->f_nameScoresLabel->base.visible = 1;
        self->f_addScoreButton->base.visible = 1;
        self->f_resetScoresButton->base.visible = 1;
        BateryApp2App_RefreshScores(self);
    }
    if (self->f_currentScreen == 2)
    {
        self->f_namesTitleLabel->base.visible = 1;
        self->f_namesListLabel->base.visible = 1;
        self->f_namesCountLabel->base.visible = 1;
        self->f_addNameButton->base.visible = 1;
        BateryApp2App_RefreshNames(self);
    }
}

void BateryApp2App_OnAddScore(BateryApp2App* self)
{
    int next = (self->f_scores->count * 37 + 13) % 200 + 10;
    List_int_Add(self->f_scores, next);
    BateryApp2App_RefreshScores(self);
}

void BateryApp2App_OnResetScores(BateryApp2App* self)
{
    List_int_Clear(self->f_scores);
    List_int_Add(self->f_scores, 100);
    List_int_Add(self->f_scores, 200);
    List_int_Add(self->f_scores, 50);
    BateryApp2App_RefreshScores(self);
}

void BateryApp2App_RefreshScores(BateryApp2App* self)
{
    int sum = 0;
    int best = 0;
    StringBuilder* sb = StringBuilder_New(512);
    for (int _i_score = 0; _i_score < (int)(self->f_scores->count); _i_score++)
    {
        int score = self->f_scores->data[_i_score];
        sum = sum + score;
        if (score > best)
        {
            best = score;
        }
        StringBuilder_AppendInt(sb, score);
        StringBuilder_AppendStr(sb, "\n");
    }
    StringBuilder* nsSb = StringBuilder_New(256);
    StringBuilder_AppendLine(nsSb, "--- Name Scores ---");
    if (Dict_str_int_ContainsKey(self->f_nameScores, "Alice"))
    {
        StringBuilder_AppendLine(nsSb, "Alice: ?");
    }
    if (Dict_str_int_ContainsKey(self->f_nameScores, "Bob"))
    {
        StringBuilder_AppendLine(nsSb, "Bob: ?");
    }
    if (Dict_str_int_ContainsKey(self->f_nameScores, "Charlie"))
    {
        StringBuilder_AppendLine(nsSb, "Charlie: ?");
    }
    Label_SetText(self->f_scoresListLabel, StringBuilder_ToString(sb));
    snprintf(_cs2sx_strbuf, sizeof(_cs2sx_strbuf), "Sum: %d  Best: %d", sum, best);
    Label_SetText(self->f_scoresSumLabel, _cs2sx_strbuf);
    snprintf(_cs2sx_strbuf, sizeof(_cs2sx_strbuf), "Count: %d", self->f_scores->count);
    Label_SetText(self->f_scoresHighLabel, _cs2sx_strbuf);
    Label_SetText(self->f_nameScoresLabel, StringBuilder_ToString(nsSb));
}

void BateryApp2App_OnAddName(BateryApp2App* self)
{
    List_char_Add(self->f_names, self->f_namePool[self->f_nameIndex]);
    self->f_nameIndex = self->f_nameIndex + 1;
    if (self->f_nameIndex >= self->f_namePool_count)
    {
        self->f_nameIndex = 0;
    }
    BateryApp2App_RefreshNames(self);
}

void BateryApp2App_RefreshNames(BateryApp2App* self)
{
    StringBuilder* sb = StringBuilder_New(256);
    for (int _i_name = 0; _i_name < (int)(self->f_names->count); _i_name++)
    {
        const char* name = self->f_names->data[_i_name];
        StringBuilder_AppendLine(sb, name);
    }
    Label_SetText(self->f_namesListLabel, StringBuilder_ToString(sb));
    snprintf(_cs2sx_strbuf, sizeof(_cs2sx_strbuf), "Players: %d", self->f_names->count);
    Label_SetText(self->f_namesCountLabel, _cs2sx_strbuf);
}

