# 🎮 TetriC

Klasická hra Tetris napísaná v C s použitím SDL2 knižníc.

## ✨ Funkcie

- **Klasická Tetris mechanika** — všetkých 7 figúrok (I, O, T, S, Z, J, L) s rotáciami
- **Viacero obrazoviek** — hlavné menu, hra, nastavenia, game over
- **Nastaviteľná obtiažnosť** — Easy / Normal / Hard ovplyvňuje rýchlosť pádu
- **Progresívna obtiažnosť** — hra sa zrýchľuje každých 5 vyčistených riadkov
- **High score systém** — Top 3 skóre ukladané do súboru
- **Zvukové efekty** — hudba na pozadí, zvuk pri vyčistení riadku a game over
- **Náhľad ďalšej figúrky** — vidíš čo príde ďalej

## 🎯 Ovládanie

| Kláves  | Akcia                        |
|---------|------------------------------|
| `←` `→` | Posun figúrky doľava/doprava |
| `↓`     | Zrýchlenie pádu              |
| `Space` | Hard drop (okamžitý pád)     |
| `Z`     | Rotácia doľava               |
| `X`     | Rotácia doprava              |
| `↑` `↓` | Navigácia v menu             |
| `Enter` | Potvrdenie výberu            |
| `Esc`   | Návrat do menu / Ukončenie   |

## 🚀 Inštalácia

### macOS

```bash
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer cmake
git clone https://github.com/jakubperdoch/Tetris-C.git
cd Tetris-C
mkdir build && cd build
cmake ..
make
./tetris
```

### Linux (Ubuntu/Debian)

```bash
sudo apt install build-essential cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
git clone https://github.com/jakubperdoch/Tetris-C.git
cd Tetris-C
mkdir build && cd build
cmake ..
make
./tetris
```

### Windows (MSYS2)

1. Stiahni a nainštaluj [MSYS2](https://www.msys2.org/)
2. Otvor **MSYS2 MINGW64** terminál:

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_mixer
git clone https://github.com/jakubperdoch/Tetris-C.git
cd Tetris-C
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
./tetris.exe
```

## 🛠️ Technológie

| Technológia                                      | Použitie                       |
|--------------------------------------------------|--------------------------------|
| **C11**                                          | Hlavný programovací jazyk      |
| [SDL2](https://www.libsdl.org/)                  | Grafika a window management    |
| [SDL2_ttf](https://wiki.libsdl.org/SDL2_ttf)     | Renderovanie fontov            |
| [SDL2_mixer](https://wiki.libsdl.org/SDL2_mixer) | Audio (hudba + zvukové efekty) |
| **CMake**                                        | Build systém                   |

## 📁 Štruktúra projektu

```
TetriC/
├── src/                    # Zdrojové súbory
│   ├── main.c              # Entry point
│   ├── game.c              # Herná logika, scoreboard
│   ├── board.c             # Herná doska, kolízie, čistenie riadkov
│   ├── shapes.c            # Figúrky a ich renderovanie
│   ├── input.c             # Spracovanie vstupu z klávesnice
│   ├── menu.c              # Hlavné menu a nastavenia
│   ├── render.c            # Renderovanie UI a textov
│   ├── audio.c             # Správa zvukov a hudby
│   └── settings.c          # Načítanie/ukladanie nastavení
├── include/                # Hlavičkové súbory
├── assets/
│   ├── fonts/
│   │   └── tetris_font.ttf
│   └── audio/
│       ├── tetris.mp3
│       ├── gameover.mp3
│       └── line_clear.mp3
├── build/                  # Výstup kompilácie (generované)
├── CMakeLists.txt
└── README.md
```

## 🎲 Herné mechaniky

### Bodovanie

- **100 bodov** za každý vyčistený riadok

### Obtiažnosť

| Úroveň | Počiatočný delay |
|--------|------------------|
| Easy   | 500 ms           |
| Normal | 400 ms           |
| Hard   | 300 ms           |

Hra sa postupne zrýchľuje — každých 5 vyčistených riadkov sa delay zníži o 50 ms (minimum 100 ms).

### Figúrky

| Figúrka | Farba           |
|---------|-----------------|
| I       | 🟦 Svetlo Modrá |
| O       | 🟨 Žltá         |
| T       | 🟪 Fialová      |
| S       | 🟩 Zelená       |
| Z       | 🟥 Červená      |
| J       | 🟦 Modrá        |
| L       | 🟧 Oranžová     |

🐱 https://github.com/jakubperdoch/Tetris-C