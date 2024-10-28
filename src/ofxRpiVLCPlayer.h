#pragma once

#include <memory>
#include "VLCPlayerInstance.h"

class ofxRpiVLCPlayer
{
    shared_ptr<VLCPlayerInstance> vlcPlayerInstance;
    ofTexture dummyTexture;
	ofImage dummyImage;
public:
    ofxRpiVLCPlayer(void);
    ~ofxRpiVLCPlayer(void);
    
    void setup(bool t_fullscreen, bool t_looping);
    bool loadMovie(string name);
    void closeMovie();
    void update();
    
    long getTimeMillis();
    
    ofTexture &getTextureReference();
	ofImage &getThumbnailImage();
    //void draw(float x, float y, float w, float h);
    //void draw(float x, float y);
    void play();
    void stop();
    
    bool fullscreen;
    bool looping;
};

