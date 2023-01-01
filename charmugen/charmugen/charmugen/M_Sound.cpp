#include "M_Sound.h"


M_Sound::M_Sound(AudioDevicePtr aud_dev, char* filename, float volume)
{
	sound=NULL;

	sound=OpenSound(aud_dev, filename, false);
	sound->setVolume(volume);
}


M_Sound::~M_Sound(void)
{
	stop();
	reset();
}

void M_Sound::play(bool repeat){
	if(!sound->isPlaying()){
		sound->setRepeat(repeat);
		sound->play();
	}
}

void M_Sound::play(bool _reset, bool repeat){
	if(_reset){
		if(sound->isPlaying()){
			sound->stop();
			sound->reset();
		}
		sound->setRepeat(repeat);
		sound->play();
	}
	else{
		if(!sound->isPlaying()){
			sound->setRepeat(repeat);
			sound->play();
		}
	}
}

void M_Sound::stop(){
	sound->stop();
}

void M_Sound::reset(){
	sound->reset();
}

void M_Sound::stopnreset(){
	if(sound->isPlaying()){
		sound->stop();
	}
	sound->reset();
}

void M_Sound::setvolume(float volume){
	sound->setVolume(volume);
}

bool M_Sound::getisplaying(){
	return sound->isPlaying();
}