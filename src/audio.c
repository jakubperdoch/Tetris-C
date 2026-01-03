#include "audio.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "constants.h"

Mix_Music* soundtrack = NULL;
Mix_Chunk* gameover_sound = NULL;
Mix_Chunk* line_clear_sound = NULL;

int init_audio()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_LogError(0, "Mixer init failed: %s\n", Mix_GetError());
        return -1;
    }

    soundtrack = Mix_LoadMUS(MUSIC_PATH);
    gameover_sound = Mix_LoadWAV(GAMEOVER_PATH);
    line_clear_sound = Mix_LoadWAV(LINE_CLEAR_SOUND_PATH);


    if (!soundtrack || !gameover_sound || !line_clear_sound)
    {
        SDL_LogError(0, "Audio load failed: %s\n", Mix_GetError());
        return -1;
    }
    return 0;
}

void play_soundtrack()
{
    Mix_PlayMusic(soundtrack, -1);
}

void stop_soundtrack()
{
    printf("Stopping soundtrack\n");
    Mix_HaltMusic();
}

void play_gameover()
{
    Mix_HaltMusic();
    Mix_PlayChannel(-1, gameover_sound, 0);
}

void play_line_clear()
{
    Mix_PlayChannel(-1, line_clear_sound, 0);
}

void cleanup_audio()
{
    Mix_FreeMusic(soundtrack);
    Mix_FreeChunk(gameover_sound);
    Mix_CloseAudio();
}
