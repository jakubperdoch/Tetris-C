#define TITLE "TetriC"

#define SCREEN_WIDTH  900
#define SCREEN_HEIGHT 800
#define SCREEN_OFFSET_X (SCREEN_WIDTH - BOARD_WIDTH * CELL_SIZE) / 2
#define SCREEN_OFFSET_Y ((SCREEN_HEIGHT - BOARD_HEIGHT * CELL_SIZE) / 1.2)

#define BOARD_WIDTH  10
#define BOARD_HEIGHT 20
#define CELL_SIZE    30

#define FALL_DELAY 300
#define FALL_SPEED_MULTIPLIER 1.1

#define FONT_PRIMARY_PATH "assets/fonts/tetris_font.ttf"
#define FONT_PRIMARY_SIZE 20
#define FONT_SECONDARY_SIZE 10

#define MUSIC_PATH "assets/audio/tetris.mp3"
#define GAMEOVER_PATH "assets/audio/gameover.mp3"
#define LINE_CLEAR_SOUND_PATH "assets/audio/line_clear.mp3"


