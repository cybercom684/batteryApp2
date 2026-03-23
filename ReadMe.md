# batteryApp2

> Nintendo Switch Homebrew Demo — geschrieben in C# mit [CS2SX](https://github.com/cybercom684/CS2SX)

Eine vollständig interaktive Switch-Homebrew-App als Demonstration des CS2SX-Transpilers. Echten C#-Code schreiben, fertige `.nro`-Datei erhalten.

---

## Features

- **3-Screen-Navigation** — wechseln mit L / R
- **Live-Batterieanzeige** — echte Daten über libnx PSM Service
- **`List<int>` + `foreach`** — dynamische Score-Liste mit Summe und Bestwert
- **`List<string>`** — Spieler-Namensverwaltung
- **`Dictionary<string, int>`** — Name-zu-Score-Zuordnung mit `ContainsKey`
- **`StringBuilder`** — effizienter mehrzeiliger Label-Textaufbau
- **Buttons mit `OnClick`** — interaktive UI mit Fokus-Navigation
- **`Visible`-Property** — dynamisches Ein- und Ausblenden von Controls
- **String-Interpolation** — `$"Batterie: {battery}%"` → `snprintf` in C

---

## Steuerung

| Taste | Aktion |
|-------|--------|
| `L` / `R` | Zwischen Screens wechseln |
| `X` | Score hinzufügen (Screen 1) / Spieler hinzufügen (Screen 2) |
| `Y` | Scores zurücksetzen (Screen 1) |
| `A` | Fokussierten Button bestätigen |
| `↑` / `↓` | Zwischen Buttons navigieren |
| `+` | App beenden |

---

## Build

### Voraussetzungen

- [devkitPro](https://devkitpro.org/wiki/Getting_Started) mit devkitA64 und libnx
- Umgebungsvariable `DEVKITPRO` gesetzt
- [.NET 8 SDK](https://dotnet.microsoft.com/download)
- CS2SX installiert:

```bash
dotnet tool install -g cs2sx
```

### Build-Befehl

```bash
cs2sx build batteryApp2
```

Ausgabe: `batteryApp2.nro`

### Installation auf der Switch

`batteryApp2.nro` in den Ordner `/switch/` auf der SD-Karte kopieren und über das Homebrew-Menü starten.

---

## Projektstruktur

```
batteryApp2/
├── LibNX/...           ← LibNX-Header und -Bibliotheken (devkitPro) für Intelisense
├── Program.cs          ← Haupt-App (C#-Quellcode)
├── Counter.cs          ← Hilfsklasse für Zähler
├── batteryApp2.csproj
├── cs2sx.json          ← CS2SX Konfiguration
└── cs2sx_out/          ← Automatisch generierter C-Code
    ├── Program.c
    ├── Program.h
    ├── _forward.h
    ├── switchforms.h
    ├── switchapp.h
    └── main.c
```

---

## Code-Beispiele

### Dictionary

```csharp
private Dictionary<string, int> _nameScores;

_nameScores = new Dictionary<string, int>();
_nameScores.Add("Alice", 142);
_nameScores.Add("Bob", 89);

if (_nameScores.ContainsKey("Alice"))
    sb.AppendLine("Alice: gefunden");
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

### Generierter C-Code

CS2SX transpiliert den C#-Code automatisch zu gültigem C:

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

## Über CS2SX

CS2SX transpiliert C#-Quellcode zu C und kompiliert ihn mit devkitPros `aarch64-none-elf-gcc` zu Nintendo Switch `.nro`-Homebrew-Dateien.

Unterstützte C#-Features: `List<T>`, `Dictionary<K,V>`, `StringBuilder`, `foreach`, String-Interpolation, `ref`/`out`-Parameter, direkte libnx-Aufrufe und mehr.

---

*Erstellt mit [CS2SX](https://github.com/cybercom684/CS2SX)*