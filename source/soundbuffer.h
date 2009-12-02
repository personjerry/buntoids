#ifndef _SOUNDBUFFER_
#define _SOUNDBUFFER_

#include "al_ext.h"

#include <vector>
#include <string>

class SoundBuffer {
	private:
		ALuint buffer;

	public:
		SoundBuffer(const std::string& url):buffer(0) {
			load(url);
		}

		SoundBuffer():buffer(0) {}

		~SoundBuffer() {
			alDeleteBuffers(1,&buffer);
		}

		void load(const std::string& url);
		ALuint& id();
};

extern std::vector<SoundBuffer*> soundbuffers;

#endif

