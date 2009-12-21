#ifndef _AL_EXT_
#define _AL_EXT_

#include <AL/alut.h>

#define AL_FILTER_NULL				0x0000
#define AL_EFFECT_REVERB			0x0001
#define AL_EFFECT_TYPE				0x8001
#define AL_EFFECTSLOT_EFFECT		0x0001
#define AL_EFFECTSLOT_NULL			0x0000
#define AL_DIRECT_FILTER			0x20005
#define AL_AUXILIARY_SEND_FILTER	0x20006
#define	AL_FILTER_LOWPASS			0x0001
#define AL_LOWPASS_GAIN				0x0001
#define AL_LOWPASS_GAINHF			0x0002
#define AL_FILTER_TYPE				0x8001

typedef void(*PFNALFILTERI)						(ALuint, ALenum, ALint);
typedef void(*PFNALFILTERF)						(ALuint, ALenum, ALfloat);
typedef void(*PFNALEFFECTI)						(ALuint, ALenum, ALint);
typedef void(*PFNALGENFILTERS)					(ALsizei, ALuint*);
typedef void(*PFNALGENEFFECTS)					(ALsizei, ALuint*);
typedef void(*PFNALDELETEFILTERS)				(ALsizei, ALuint*);
typedef void(*PFNALDELETEEFFECTS)				(ALsizei, ALuint*);
typedef void(*PFNALAUXILIARYEFFECTSLOTI)		(ALuint, ALenum, ALint);
typedef void(*PFNALGENAUXILIARYEFFECTSLOTS)		(ALsizei, ALuint*);
typedef void(*PFNALDELETEAUXILIARYEFFECTSLOTS)	(ALsizei, ALuint*);

extern PFNALEFFECTI						alEffecti;
extern PFNALFILTERI						alFilteri;
extern PFNALFILTERF						alFilterf;
extern PFNALGENFILTERS					alGenFilters;
extern PFNALGENEFFECTS					alGenEffects;
extern PFNALDELETEEFFECTS				alDeleteEffects;
extern PFNALDELETEFILTERS				alDeleteFilters;
extern PFNALAUXILIARYEFFECTSLOTI		alAuxiliaryEffectSloti;
extern PFNALGENAUXILIARYEFFECTSLOTS		alGenAuxiliaryEffectSlots;
extern PFNALDELETEAUXILIARYEFFECTSLOTS	alDeleteAuxiliaryEffectSlots;

void sound_init_extensions();

#endif

