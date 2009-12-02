#include "soundbuffer.h"

#include <vorbis/vorbisfile.h>

#include <iostream>

#define BUFFER_SIZE 32768

std::vector<SoundBuffer*> soundbuffers;

void SoundBuffer::load(const std::string &url) {
	FILE *f=fopen(url.c_str(),"rb");

	if(!f)
		std::cerr<<"could not open "<<url<<std::endl;

	OggVorbis_File oggfile;

	if(ov_open(f,&oggfile,NULL,0)!=0)
		std::cerr<<"error decoding "<<url<<std::endl;

	std::vector<char> Array(BUFFER_SIZE);
	std::vector<char> BufferData;
	long bytes_read;

	do {
		//Set to 0 for little-endian or 1 for big-endian
		static const int endian=0;

		//Read up to a buffer's worth of decoded sound data
		bytes_read=ov_read(&oggfile,&Array[0],int(Array.size()),endian,2,1,NULL);

		if(bytes_read<0) {
			ov_clear(&oggfile);
			std::cerr<<"error decoding "<<url<<std::endl;
		}

		//Append to end of BufferData
		BufferData.insert(BufferData.end(),Array.begin(),Array.begin()+bytes_read);
	} while(bytes_read>0);

	vorbis_info *meta=ov_info(&oggfile,-1);

	//Always use 16-bit samples
	ALenum format=meta->channels==1?AL_FORMAT_MONO16:AL_FORMAT_STEREO16;

	alGenBuffers(1,&buffer);
	alBufferData(buffer,format,&BufferData[0],ALsizei(BufferData.size()),ALsizei(meta->rate));

	ov_clear(&oggfile);
}

ALuint& SoundBuffer::id() {
	return buffer;
}

