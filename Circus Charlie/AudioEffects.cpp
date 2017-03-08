#include "AudioEffects.h"
#include "Application.h"
#include "ModuleAudio.h"

AudioEffects::AudioEffects(){}

void AudioEffects::LoadFxs(){
	startFx = App->audio->LoadFx("audio/fxs/start.wav");
	jumpFx = App->audio->LoadFx("audio/fxs/jump.wav");
	dieFx = App->audio->LoadFx("audio/fxs/die.wav");
	coinFx= App->audio->LoadFx("audio/fxs/coinAppear.wav");
	catchFx = App->audio->LoadFx("audio/fxs/catchObject.wav");
	pauseFx = App->audio->LoadFx("audio/fxs/pause.wav");
}

void AudioEffects::PlayFX(audioEffects id){
	switch (id){
	case START:
		App->audio->PlayFx(startFx);
		break;
	case JUMP:
		App->audio->PlayFx(jumpFx);
		break;
	case DIE:
		App->audio->PlayFx(dieFx);
		break;
	case COIN:
		App->audio->PlayFx(coinFx);
		break;
	case CATCH:
		App->audio->PlayFx(catchFx);
		break;
	case PAUSE:
		App->audio->PlayFx(pauseFx);
		break;
	}
}