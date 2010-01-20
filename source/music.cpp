#include "music.h"

#include <iostream>

#define BUFFER_SIZE 8192*3

std::vector<Music*> musiclist;

void Music::load(const std::string &path) {
	if(!(oggfile=fopen(path.c_str(),"rb")))
		std::cerr<<"could not open ogg file"<<std::endl;

	int result=ov_open(oggfile,&oggstream,NULL,0);

	if(result<0)
		std::cerr<<"could not open ogg stream "<<errstr(result)<<std::endl;

	meta=ov_info(&oggstream,-1);

	format=meta->channels==1?AL_FORMAT_MONO16:AL_FORMAT_STEREO16;

	alGenBuffers(3,SBO);
	check();
	alGenSources(1,&source);
	check();
}

void Music::info() {
	std::cout
	<<"Channels: "	<<meta->channels			<<'\n'
	<<"Rate: "		<<meta->rate				<<'\n'
	<<"Bitrate: "	<<meta->bitrate_nominal		<<std::endl;
}

void Music::play() {
	if(playing())
		return;

	for(int i=0; i<3; ++i) {
		if(!stream(SBO[i]))
			return;
	}

	alSourceQueueBuffers(source,3,SBO);
	alSourcePlay(source);
	active=true;
}

bool Music::playing() {
	return active;
}

bool Music::update() {
	int processed;
	alGetSourcei(source,AL_BUFFERS_PROCESSED,&processed);

	while(processed-- && active) {
		ALuint buffer;
		alSourceUnqueueBuffers(source,1,&buffer);
		check();
		active=stream(buffer);
		alSourceQueueBuffers(source,1,&buffer);
		check();
	}

	ALint state;
	alGetSourcei(source,AL_SOURCE_STATE,&state);

	if(state!=AL_PLAYING)
		alSourcePlay(source);

	return active;
}

bool Music::stream(ALuint buffer) {
	std::vector<char> pcm(BUFFER_SIZE);
	long size=0;

	while(size<BUFFER_SIZE) {
		long result=ov_read(&oggstream,&pcm[size],BUFFER_SIZE-int(size),0,2,1,NULL);
		if(result>0)
			size+=result;
		else if(result<0)
			std::cerr<<errstr(int(result))<<std::endl;
		else
			break;
	}

	alBufferData(buffer,format,&pcm[0],ALsizei(size),ALsizei(meta->rate));
	check();

	if(size==0)
		return false;

	return true;
}

void Music::check() {
	ALenum error=alGetError();
	if(error!=AL_NO_ERROR)
		std::cerr<<alGetString(error)<<std::endl;
}

std::string Music::errstr(int code) {
	switch(code) {
		case OV_EREAD:		return "Read from media";
		case OV_ENOTVORBIS:	return "Not Vorbis data";
		case OV_EVERSION:		return "Vorbis version mismatch";
		case OV_EBADHEADER:	return "Invalid Vorbis header";
		case OV_EFAULT:		return "Internal logic fault (bug or heap/stack corruption)";
		case OV_FALSE:		return "Playback not in progress";
		case OV_HOLE:		return "Interrupion in data (garbage info, loss of sync, or corruption)";
		case OV_EIMPL:		return "Unavailable features attempted to be used";
		case OV_ENOTAUDIO:		return "Not audio data";
		case OV_ENOSEEK:		return "Bitstream not seekable";
		case OV_EINVAL:		return "Invalid argument for libvorbis";
		case OV_EBADPACKET:	return "Invalid packet to synethesis";
		case OV_EBADLINK:		return "Invalid stream or link is corrupt";
		default:			return "Unknown Ogg error";
	}
}

void newSong(const std::string& song)
{
	static std::string old_song = "";
	if(song.size()) {

		if(song!=old_song) {
			if(musiclist.size()) {
				delete musiclist.back();
				musiclist.pop_back();
			}

			musiclist.push_back(new Music("data/sfx/music/"+song));
			musiclist.back()->play();
			old_song=song;
		}
	}
}
