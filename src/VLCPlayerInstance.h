#include "ofMain.h"
#include <vlc/vlc.h>
#include <memory>

class VLCPlayerInstance {

public:
    VLCPlayerInstance(void);
    ~VLCPlayerInstance(void);


	void init(string t_filename, bool t_fullscreen, bool t_looping);
	void initializeVLC(bool t_fullscreen, bool t_looping);
	bool getIsInitialized();	
	bool isPlaying();
	float getPosition();
	libvlc_time_t getTimeMillis();
	void setTimeMillis(libvlc_time_t ms);
	void play();
	void stop();
	void cleanupVLC();
	
	libvlc_instance_t *libvlc;
	libvlc_media_t *m;
	libvlc_media_player_t *mp;
	libvlc_event_manager_t *eventManager;

    bool isInitialized;
    bool isVLCInitialized;

	string filename;
    int videoWidth, videoHeight;
    float fps;
	libvlc_time_t video_length_ms;

};
