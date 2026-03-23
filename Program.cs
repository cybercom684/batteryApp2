using System.Collections.Generic;
using System.Text;

public class BateryApp2App : SwitchApp
{
    private int _currentScreen;

    private Label _titleLabel;
    private Label _batteryLabel;
    private Label _batteryStatusLabel;
    private ProgressBar _batteryBar;
    private Label _frameLabel;
    private Label _uptimeLabel;
    private Label _screenHintLabel;

    private Label _scoresTitleLabel;
    private Label _scoresListLabel;
    private Label _scoresSumLabel;
    private Label _scoresHighLabel;
    private Label _nameScoresLabel;
    private Button _addScoreButton;
    private Button _resetScoresButton;

    private Label _namesTitleLabel;
    private Label _namesListLabel;
    private Label _namesCountLabel;
    private Button _addNameButton;

    private Label _navLabel;

    private List<int> _scores;
    private List<string> _names;
    private Dictionary<string, int> _nameScores;
    private Counter _frameCounter;
    private Counter _uptimeSeconds;
    private int _framesSinceSecond;
    private int _nameIndex;

    private static string[] _namePool;
    private static int _namePool_count;

    public override void OnInit()
    {
        LibNX.Services.Psm.psmInitialize();

        _scores = new List<int>();
        _names = new List<string>();
        _nameScores = new Dictionary<string, int>();
        _frameCounter = new Counter();
        _uptimeSeconds = new Counter();
        _currentScreen = 0;
        _framesSinceSecond = 0;
        _nameIndex = 0;

        _namePool = new string[6];
        _namePool_count = 6;
        _namePool[0] = "Alice";
        _namePool[1] = "Bob";
        _namePool[2] = "Charlie";
        _namePool[3] = "Diana";
        _namePool[4] = "Eve";
        _namePool[5] = "Frank";

        _scores.Add(142);
        _scores.Add(89);
        _scores.Add(256);
        _scores.Add(73);
        _scores.Add(310);

        _names.Add("Alice");
        _names.Add("Bob");

        // Dictionary befüllen
        _nameScores.Add("Alice", 142);
        _nameScores.Add("Bob", 89);
        _nameScores.Add("Charlie", 256);

        // System Screen
        _titleLabel = new Label("=== CS2SX Dashboard ===");
        _titleLabel.X = 5;
        _titleLabel.Y = 1;

        _batteryLabel = new Label("Battery: --%");
        _batteryLabel.X = 5;
        _batteryLabel.Y = 3;

        _batteryBar = new ProgressBar(30);
        _batteryBar.X = 5;
        _batteryBar.Y = 4;

        _batteryStatusLabel = new Label("Status: --");
        _batteryStatusLabel.X = 5;
        _batteryStatusLabel.Y = 5;

        _frameLabel = new Label("Frames: 0");
        _frameLabel.X = 5;
        _frameLabel.Y = 7;

        _uptimeLabel = new Label("Uptime: 0s");
        _uptimeLabel.X = 5;
        _uptimeLabel.Y = 8;

        _screenHintLabel = new Label("L/R = Switch Screen");
        _screenHintLabel.X = 5;
        _screenHintLabel.Y = 27;

        Form.Add(_titleLabel);
        Form.Add(_batteryLabel);
        Form.Add(_batteryBar);
        Form.Add(_batteryStatusLabel);
        Form.Add(_frameLabel);
        Form.Add(_uptimeLabel);
        Form.Add(_screenHintLabel);

        // Scores Screen
        _scoresTitleLabel = new Label("=== Highscores ===");
        _scoresTitleLabel.X = 5;
        _scoresTitleLabel.Y = 1;
        _scoresTitleLabel.Visible = false;

        _scoresListLabel = new Label("...");
        _scoresListLabel.X = 5;
        _scoresListLabel.Y = 3;
        _scoresListLabel.Visible = false;

        _scoresSumLabel = new Label("Sum: 0");
        _scoresSumLabel.X = 5;
        _scoresSumLabel.Y = 14;
        _scoresSumLabel.Visible = false;

        _scoresHighLabel = new Label("Best: 0");
        _scoresHighLabel.X = 5;
        _scoresHighLabel.Y = 15;
        _scoresHighLabel.Visible = false;

        _nameScoresLabel = new Label("NameScores: --");
        _nameScoresLabel.X = 5;
        _nameScoresLabel.Y = 17;
        _nameScoresLabel.Visible = false;

        _addScoreButton = new Button("[X] Add Random Score");
        _addScoreButton.X = 5;
        _addScoreButton.Y = 20;
        _addScoreButton.Visible = false;
        _addScoreButton.OnClick = OnAddScore;

        _resetScoresButton = new Button("[Y] Reset Scores");
        _resetScoresButton.X = 5;
        _resetScoresButton.Y = 22;
        _resetScoresButton.Visible = false;
        _resetScoresButton.OnClick = OnResetScores;

        Form.Add(_scoresTitleLabel);
        Form.Add(_scoresListLabel);
        Form.Add(_scoresSumLabel);
        Form.Add(_scoresHighLabel);
        Form.Add(_nameScoresLabel);
        Form.Add(_addScoreButton);
        Form.Add(_resetScoresButton);

        // Names Screen
        _namesTitleLabel = new Label("=== Players ===");
        _namesTitleLabel.X = 5;
        _namesTitleLabel.Y = 1;
        _namesTitleLabel.Visible = false;

        _namesListLabel = new Label("...");
        _namesListLabel.X = 5;
        _namesListLabel.Y = 3;
        _namesListLabel.Visible = false;

        _namesCountLabel = new Label("Count: 0");
        _namesCountLabel.X = 5;
        _namesCountLabel.Y = 18;
        _namesCountLabel.Visible = false;

        _addNameButton = new Button("[X] Add Player");
        _addNameButton.X = 5;
        _addNameButton.Y = 20;
        _addNameButton.Visible = false;
        _addNameButton.OnClick = OnAddName;

        Form.Add(_namesTitleLabel);
        Form.Add(_namesListLabel);
        Form.Add(_namesCountLabel);
        Form.Add(_addNameButton);

        _navLabel = new Label("[L] Prev  [R] Next  [+] Exit");
        _navLabel.X = 5;
        _navLabel.Y = 28;
        Form.Add(_navLabel);

        RefreshScores();
        RefreshNames();
    }

    public override void OnFrame()
    {
        _frameCounter.Increment();
        _framesSinceSecond++;

        if (_framesSinceSecond >= 60)
        {
            _uptimeSeconds.Increment();
            _framesSinceSecond = 0;
        }

        if (Input.IsDown(NpadButton.R))
        {
            _currentScreen = _currentScreen + 1;
            if (_currentScreen > 2)
                _currentScreen = 0;
            SwitchScreen();
        }

        if (Input.IsDown(NpadButton.L))
        {
            _currentScreen = _currentScreen - 1;
            if (_currentScreen < 0)
                _currentScreen = 2;
            SwitchScreen();
        }

        if (Input.IsDown(NpadButton.X))
        {
            if (_currentScreen == 1)
                OnAddScore();
            if (_currentScreen == 2)
                OnAddName();
        }

        if (Input.IsDown(NpadButton.Y))
        {
            if (_currentScreen == 1)
                OnResetScores();
        }

        if (_currentScreen == 0)
        {
            uint battery = 0;
            LibNX.Services.Psm.psmGetBatteryChargePercentage(ref battery);
            _batteryLabel.Text = $"Battery: {battery}%";
            _batteryBar.value = (int)battery;

            if (battery > 60)
                _batteryStatusLabel.Text = "Status: Good";
            else if (battery > 20)
                _batteryStatusLabel.Text = "Status: Low";
            else
                _batteryStatusLabel.Text = "Status: CRITICAL!";

            _frameLabel.Text = $"Frames: {_frameCounter.GetValue()}";
            _uptimeLabel.Text = $"Uptime: {_uptimeSeconds.GetValue()}s";
        }
    }

    public override void OnExit()
    {
        LibNX.Services.Psm.psmExit();
    }

    public void SwitchScreen()
    {
        _titleLabel.Visible = false;
        _batteryLabel.Visible = false;
        _batteryBar.Visible = false;
        _batteryStatusLabel.Visible = false;
        _frameLabel.Visible = false;
        _uptimeLabel.Visible = false;
        _screenHintLabel.Visible = false;

        _scoresTitleLabel.Visible = false;
        _scoresListLabel.Visible = false;
        _scoresSumLabel.Visible = false;
        _scoresHighLabel.Visible = false;
        _nameScoresLabel.Visible = false;
        _addScoreButton.Visible = false;
        _resetScoresButton.Visible = false;

        _namesTitleLabel.Visible = false;
        _namesListLabel.Visible = false;
        _namesCountLabel.Visible = false;
        _addNameButton.Visible = false;

        if (_currentScreen == 0)
        {
            _titleLabel.Visible = true;
            _batteryLabel.Visible = true;
            _batteryBar.Visible = true;
            _batteryStatusLabel.Visible = true;
            _frameLabel.Visible = true;
            _uptimeLabel.Visible = true;
            _screenHintLabel.Visible = true;
        }

        if (_currentScreen == 1)
        {
            _scoresTitleLabel.Visible = true;
            _scoresListLabel.Visible = true;
            _scoresSumLabel.Visible = true;
            _scoresHighLabel.Visible = true;
            _nameScoresLabel.Visible = true;
            _addScoreButton.Visible = true;
            _resetScoresButton.Visible = true;
            RefreshScores();
        }

        if (_currentScreen == 2)
        {
            _namesTitleLabel.Visible = true;
            _namesListLabel.Visible = true;
            _namesCountLabel.Visible = true;
            _addNameButton.Visible = true;
            RefreshNames();
        }
    }

    public void OnAddScore()
    {
        int next = (_scores.Count * 37 + 13) % 200 + 10;
        _scores.Add(next);
        RefreshScores();
    }

    public void OnResetScores()
    {
        _scores.Clear();
        _scores.Add(100);
        _scores.Add(200);
        _scores.Add(50);
        RefreshScores();
    }

    public void RefreshScores()
    {
        int sum = 0;
        int best = 0;
        var sb = new StringBuilder(512);

        foreach (int score in _scores)
        {
            sum = sum + score;
            if (score > best)
                best = score;
            sb.Append(score);
            sb.Append("\n");
        }

        // _nameScores ausgeben
        var nsSb = new StringBuilder(256);
        nsSb.AppendLine("--- Name Scores ---");
        if (_nameScores.ContainsKey("Alice"))
            nsSb.AppendLine("Alice: ?");
        if (_nameScores.ContainsKey("Bob"))
            nsSb.AppendLine("Bob: ?");
        if (_nameScores.ContainsKey("Charlie"))
            nsSb.AppendLine("Charlie: ?");

        _scoresListLabel.Text = sb.ToString();
        _scoresSumLabel.Text = $"Sum: {sum}  Best: {best}";
        _scoresHighLabel.Text = $"Count: {_scores.Count}";
        _nameScoresLabel.Text = nsSb.ToString();
    }

    public void OnAddName()
    {
        _names.Add(_namePool[_nameIndex]);
        _nameIndex = _nameIndex + 1;
        if (_nameIndex >= _namePool_count)
            _nameIndex = 0;
        RefreshNames();
    }

    public void RefreshNames()
    {
        var sb = new StringBuilder(256);
        foreach (var name in _names)
            sb.AppendLine(name);
        _namesListLabel.Text = sb.ToString();
        _namesCountLabel.Text = $"Players: {_names.Count}";
    }
}