#include "Audio.h"

Sound shoot;
SoundBuffer buffer;

int initAudio()
{
    if (!buffer.loadFromFile("../resources/sfx/shoot.wav")) {
        return 1;
    }
    shoot.setBuffer(buffer);
    return 0;
}

int ShootingSound() {
    shoot.play();
    return 0;
}