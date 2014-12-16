#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include "../tools/Universal.h"

class Audio : Universal {

	public:
		Mix_Music* theme_song;
		Mix_Music* theme_song_loop;
		Mix_Music* pirate_song;
		Mix_Music* current_song;

		void initiate();
		void update();

		/**
		plays specified music
		**/
		void play_music(Mix_Music* music, int loops);

		/**
		free memory from all audio created
		**/
		void free_audio();
};

#endif