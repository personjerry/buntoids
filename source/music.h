#ifndef _MUSIC_
#define _MUSIC_

#include <AL/al.h>
#include <vorbis/vorbisfile.h>

#include <vector>
#include <string>

class Music {
	private:
		ALuint SBO[3], source;
		OggVorbis_File oggstream;
		vorbis_info* meta;
		FILE* oggfile;
		ALenum format;
		bool active;
		bool stream(ALuint);
		void check();
		std::string errstr(int);

	public:
		Music(const std::string& url):SBO(),source(0),oggstream(),meta(NULL),oggfile(NULL),format(),active() {
			load(url);
		}

		Music():SBO(),source(0),oggstream(),meta(NULL),oggfile(NULL),format(),active() {}
		Music(const Music&):SBO(),source(0),oggstream(),meta(NULL),oggfile(NULL),format(),active() {}

		~Music() {
			alSourceStop(source);

			alSourcei(source,AL_BUFFER,0);

			alDeleteSources(1,&source);
			check();
			alDeleteBuffers(3,SBO);
			check();

			ov_clear(&oggstream);
		}

		Music& operator=(const Music&){
			return *this;
		}

		void load(const std::string&);
		void info();
		void play();

		bool playing();
		bool update();
};

extern std::vector<Music*> musiclist;
extern void newSong(const std::string& song);

#endif

