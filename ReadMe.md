# batteryApp2

> Nintendo Switch Homebrew Demo — written in C# with [CS2SX](https://github.com/johannesh/cs2sx)

A fully interactive Switch homebrew app demonstrating the CS2SX transpiler. Write real C# code, get a working `.nro` file.

---

## Screenshots

| System Screen | Scores Screen | Names Screen |
|---|---|---|
| Live battery % + ProgressBar | Dynamic score list with sum | Player list with Dictionary |

---

## Features

- **3-Screen navigation** — switch with L / R
- **Live battery display** — real data via libnx PSM service
- **`List<int>` + `foreach`** — dynamic score list with sum and best calculation
- **`List<string>`** — player name management
- **`Dictionary<string, int>`** — name-to-score mapping with `ContainsKey`
- **`StringBuilder`** — efficient multi-line label output
- **Buttons with `OnClick`** — interactive UI with focus navigation
- **`Visible` property** — dynamic show/hide of all controls
- **String interpolation** — `$"Battery: {battery}%"` → `snprintf` in C

---

## Controls

| Button | Action |
|--------|--------|
| `L` / `R` | Switch between screens |
| `X` | Add score (Screen 1) / Add player (Screen 2) |
| `Y` | Reset scores (Screen 1) |
| `A` | Confirm focused button |
| `↑` / `↓` | Navigate between buttons |
| `+` | Exit app |

---

## Build

### Requirements

- [devkitPro](https://devkitpro.org/wiki/Getting_Started) with devkitA64 + libnx
- `DEVKITPRO` environment variable set
- [.NET 8 SDK](https://dotnet.microsoft.com/download)
- CS2SX installed:

```bash
dotnet tool install -g cs2sx
```

### Build command

```bash
cs2sx build batteryApp2
```

Output: `batteryApp2.nro`

### Install on Switch

Copy `batteryApp2.nro` to `/switch/` on your SD card and launch via the Homebrew Menu.

---

## Project structure

```
batteryApp2/
├── Program.cs          ← Main app (C# source)
├── Counter.cs          ← Helper class
├── batteryApp2.csproj
├── cs2sx.json          ← CS2SX config
└── cs2sx_out/          ← Auto-generated C code
    ├── Program.c
    ├── Program.h
    ├── _forward.h
    ├── switchforms.h
    ├── switchapp.h
    └── main.c
```

---

## Code examples

### Dictionary

```csharp
private Dictionary<string, int> _nameScores;

_nameScores = new Dictionary<string, int>();
_nameScores.Add("Alice", 142);
_nameScores.Add("Bob", 89);

if (_nameScores.ContainsKey("Alice"))
    sb.AppendLine("Alice: found");
```

### StringBuilder

```csharp
var sb = new StringBuilder(512);

foreach (int score in _scores)
{
    sb.Append(score);
    sb.Append("\n");
}

_scoresListLabel.Text = sb.ToString();
```

### What CS2SX generates

```c
StringBuilder* sb = StringBuilder_New(512);

for (int _i_score = 0; _i_score < (int)(self->f_scores->count); _i_score++)
{
    int score = self->f_scores->data[_i_score];
    StringBuilder_AppendInt(sb, score);
    StringBuilder_AppendStr(sb, "\n");
}

Label_SetText(self->f_scoresListLabel, StringBuilder_ToString(sb));
```

---

## cs2sx.json

```json
{
    "name":      "batteryApp2",
    "author":    "CS2SX",
    "version":   "1.0.2",
    "mainClass": "BateryApp2App"
}
```

---

## About CS2SX

CS2SX transpiles C# source code to C and compiles it with devkitPro's `aarch64-none-elf-gcc` to produce Nintendo Switch `.nro` homebrew files.

Supported C# features: `List<T>`, `Dictionary<K,V>`, `StringBuilder`, `foreach`, string interpolation, `ref`/`out` parameters, libnx direct calls, and more.

---

*Built with [CS2SX](https://github.com/johannesh/cs2sx)*