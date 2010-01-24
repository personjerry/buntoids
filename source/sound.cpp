#include "music.h"
#include "sound.h"

#include <iostream>

std::vector<Sound*> soundevents;

ALCdevice *dev;
ALCcontext *ctx;

ALuint uiEffectSlot,uiEffect,uiFilter;

void Sound::bind(ALuint buffer) {
	alSourcei(source,AL_BUFFER,buffer);
}

void Sound::play() {
	alSourcePlay(source);
}

bool Sound::playing() {
	ALint state;
	alGetSourcei(source,AL_SOURCE_STATE,&state);
	return state==AL_PLAYING;
}

void Sound::stop() {
	if(!playing())
		return;

	alSourceStop(source);
}

void Sound::pos(const ALfloat x, const ALfloat y, const ALfloat z) {
	alSource3f(source,AL_POSITION,x,y,z);
}

void Sound::reverb(bool enable) {
	if(enable)
		alSource3i(source,AL_AUXILIARY_SEND_FILTER,uiEffectSlot,0,0);
	else
		alSource3i(source,AL_AUXILIARY_SEND_FILTER,AL_EFFECTSLOT_NULL,0,0);
}

void Sound::lowpass(bool enable) {
	if(enable)
		alSourcei(source,AL_DIRECT_FILTER,uiFilter);
	else
		alSourcei(source,AL_DIRECT_FILTER,AL_FILTER_NULL);
}

bool openal_init() {
	dev=alcOpenDevice(NULL);

	if(!dev)
		return true;

	ctx=alcCreateContext(dev,NULL);

	if(!ctx)
		return true;

	if(!alcMakeContextCurrent(ctx))
		return true;

	sound_init_extensions();
/*
	if(cvars["s_volume"]>100)
		cvars["s_volume"]=100;

	if(cvars["s_on"])
		alListenerf(AL_GAIN,float(cvars["s_volume"])/100);
	else
		alListenerf(AL_GAIN,0.0f);
*/
	alGenAuxiliaryEffectSlots(1,&uiEffectSlot);
	alGenEffects(1,&uiEffect);
	alEffecti(uiEffect,AL_EFFECT_TYPE,AL_EFFECT_REVERB);
	alAuxiliaryEffectSloti(uiEffectSlot,AL_EFFECTSLOT_EFFECT,uiEffect);

	alGenFilters(1,&uiFilter);
	alFilteri(uiFilter,AL_FILTER_TYPE,AL_FILTER_LOWPASS);
	alFilterf(uiFilter,AL_LOWPASS_GAIN,1.0f);
	alFilterf(uiFilter,AL_LOWPASS_GAINHF,0.1f);

	soundbuffers.push_back(new SoundBuffer("data/sfx/00.ogg"));
	soundbuffers.push_back(new SoundBuffer("data/sfx/01.ogg"));

	return false;
}

bool openal_update() {
	if(musiclist.size())
		if(musiclist.back()->playing())
			musiclist.back()->update();

	if(!soundevents.size())
		return true;

	return false;
}

template <typename T> void killarray(T& array) {
	while(array.size()) {
		delete array.back();
		array.pop_back();
	}
}

void openal_kill() {
	if(soundevents.size())
		killarray(soundevents);

	if(soundbuffers.size())
		killarray(soundbuffers);

	if(musiclist.size())
		killarray(musiclist);

	if(uiEffect)
		alDeleteEffects(1,&uiEffect);

	if(uiEffectSlot)
		alDeleteAuxiliaryEffectSlots(1,&uiEffectSlot);

	if(uiFilter)
		alDeleteFilters(1,&uiFilter);

	alcMakeContextCurrent(NULL);
	alcDestroyContext(ctx);
	alcCloseDevice(dev);
}

