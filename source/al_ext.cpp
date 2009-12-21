#include "al_ext.h"

#include <iostream>

PFNALEFFECTI					alEffecti;
PFNALFILTERI					alFilteri;
PFNALFILTERF					alFilterf;
PFNALGENFILTERS					alGenFilters;
PFNALGENEFFECTS					alGenEffects;
PFNALDELETEEFFECTS				alDeleteEffects;
PFNALDELETEFILTERS				alDeleteFilters;
PFNALAUXILIARYEFFECTSLOTI		alAuxiliaryEffectSloti;
PFNALGENAUXILIARYEFFECTSLOTS	alGenAuxiliaryEffectSlots;
PFNALDELETEAUXILIARYEFFECTSLOTS	alDeleteAuxiliaryEffectSlots;

template <typename TO, typename FROM> TO nasty_cast(FROM f) {
	union {
		FROM f; TO t;
	} u; u.f=f;
	return u.t;
}

void sound_init_extensions() {
	alFilteri						=	nasty_cast<PFNALFILTERI>					(alGetProcAddress("alFilteri"));
	alFilterf						=	nasty_cast<PFNALFILTERF>					(alGetProcAddress("alFilterf"));
	alEffecti						=	nasty_cast<PFNALEFFECTI>					(alGetProcAddress("alEffecti"));
	alGenEffects					=	nasty_cast<PFNALGENEFFECTS>					(alGetProcAddress("alGenEffects"));
	alGenFilters					=	nasty_cast<PFNALGENFILTERS>					(alGetProcAddress("alGenFilters"));
	alDeleteFilters					=	nasty_cast<PFNALDELETEFILTERS>				(alGetProcAddress("alDeleteFilters"));
	alDeleteEffects					=	nasty_cast<PFNALDELETEEFFECTS>				(alGetProcAddress("alDeleteEffects"));
	alAuxiliaryEffectSloti			=	nasty_cast<PFNALAUXILIARYEFFECTSLOTI>		(alGetProcAddress("alAuxiliaryEffectSloti"));
	alGenAuxiliaryEffectSlots		=	nasty_cast<PFNALGENAUXILIARYEFFECTSLOTS>	(alGetProcAddress("alGenAuxiliaryEffectSlots"));
	alDeleteAuxiliaryEffectSlots	=	nasty_cast<PFNALDELETEEFFECTS>				(alGetProcAddress("alDeleteAuxiliaryEffectSlots"));

	if(	!alEffecti || !alFilteri || !alFilterf || !alGenFilters || !alGenEffects || !alDeleteEffects || !alDeleteFilters ||
		!alAuxiliaryEffectSloti || !alGenAuxiliaryEffectSlots || !alDeleteAuxiliaryEffectSlots)
		std::cerr<<"one or more OpenAL functions failed to load"<<std::endl;
}

