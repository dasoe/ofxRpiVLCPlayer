#include "ofxRpiVLCPlayer.h"

//using shared_ptr;

ofxRpiVLCPlayer::ofxRpiVLCPlayer(void)
{
}

ofxRpiVLCPlayer::~ofxRpiVLCPlayer(void)
{
    //closeMovie();
}

void ofxRpiVLCPlayer::setup(bool t_fullscreen, bool t_looping) {
    fullscreen = t_fullscreen;
    looping = t_looping;
}

bool ofxRpiVLCPlayer::loadMovie(string movieName) {
    closeMovie();
    vlcPlayerInstance = make_shared<VLCPlayerInstance>();
    
    vlcPlayerInstance->init(movieName, fullscreen, looping);
    bool result = vlcPlayerInstance->getIsInitialized();
    if (!result) vlcPlayerInstance.reset();

    return result;
}

void ofxRpiVLCPlayer::closeMovie() {
    if (vlcPlayerInstance) {
        vlcPlayerInstance->stop();
        vlcPlayerInstance.reset();
    }
}

void ofxRpiVLCPlayer::update() {
    //if (vlcPlayerInstance) {
    //    vlcPlayerInstance->updateTexture();
    //}
} 

//ofTexture &ofxRpiVLCPlayer::getTextureReference() {
    //if (vlcPlayerInstance) {
        //return vlcPlayerInstance->getTexture();
    //} else {
        //return dummyTexture;
    //}
//}

//void ofxRpiVLCPlayer::draw(float x, float y, float w, float h) {
    //if (vlcPlayerInstance) {
        //vlcPlayerInstance->getTexture().draw(x, y, 0, w, h);
    //}
//}

//void ofxRpiVLCPlayer::draw(float x, float y) {
    //if (vlcPlayerInstance) {
        //vlcPlayerInstance->getTexture().draw(x, y);
    //}
//}

void ofxRpiVLCPlayer::play() {
    if (vlcPlayerInstance) {
        vlcPlayerInstance->play();
    }
}

void ofxRpiVLCPlayer::stop() {
    if (vlcPlayerInstance) {
        vlcPlayerInstance->stop();
    }
}

long ofxRpiVLCPlayer::getTimeMillis() {
    return (long) vlcPlayerInstance->getTimeMillis();
}
