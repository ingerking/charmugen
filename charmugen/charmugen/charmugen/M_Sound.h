#pragma once
#include <audiere.h>
using namespace audiere;
class M_Sound
{
private:
	OutputStreamPtr sound;
public:
	M_Sound(AudioDevicePtr aud_dev, char* filename, float volume);
	~M_Sound(void);
	void play(bool repeat);
	void play(bool _reset, bool repeat);
	void stop();
	void reset();
	void stopnreset();
	void setvolume(float volume);
	bool getisplaying();
};

