#ifndef _SOUND_
#define _SOUND_

#include "soundbuffer.h"
#include "al_ext.h"

class Sound {
	private:
		ALuint source;

	public:
		Sound(SoundBuffer* buffer):source(0) {
			alGenSources(1,&source);
			bind(buffer->id());
		}

		Sound():source(0) {
			alGenSources(1,&source);
		}

		~Sound() {
			alDeleteSources(1,&source);
		}

		void play();
		bool playing();
		void stop();
		void bind(ALuint);
		void pos(const ALfloat,const ALfloat,const ALfloat);
		void reverb(bool);
		void lowpass(bool);
};

extern std::vector<Sound*> soundevents;

bool openal_init();
bool openal_update();
void openal_kill();

#endif

