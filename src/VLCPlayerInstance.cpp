#include "VLCPlayerInstance.h"

VLCPlayerInstance::VLCPlayerInstance(void) {
    cout << "VLCPlayerInstance constructor" << endl;
}

VLCPlayerInstance::~VLCPlayerInstance(void)
{
    cout << "VLCPlayerInstance destructor" << endl;
	cleanupVLC();
}

void VLCPlayerInstance::init(string t_filename, bool t_fullscreen, bool t_looping) {
	
	cout << "rum";
	
	filename = ofToDataPath("", true) + "/" + t_filename;
	
	
    initializeVLC(t_fullscreen, t_looping);
    
    if (!isVLCInitialized) return;
	libvlc_media_player_play(mp);
}


void VLCPlayerInstance::initializeVLC(bool t_fullscreen, bool t_looping) {
	cout << "init libvlc" << endl;
	char const *vlc_argv[] = {
		"--avcodec-hw=none",
		"--plugin-path=../../../data/",
		"--no-osd"
	};

	int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);
	libvlc = libvlc_new(vlc_argc, vlc_argv);
	cout << "libvlc: " << libvlc << " | Version: " << libvlc_get_version() << endl;
	//libvlc = libvlc_new(0, NULL);
	if (!libvlc) {
		const char *error = libvlc_errmsg();
		cout << error << endl;
		return;
	}
        
    libvlc_audio_output_t *aout = libvlc_audio_output_list_get(libvlc);
    while(aout) {
        cout << aout->psz_name << endl;
        cout << aout->psz_description << endl;
        aout = aout->p_next;
    }
    
	m = libvlc_media_new_path(libvlc, filename.c_str());
    mp = libvlc_media_player_new_from_media(m);
	libvlc_video_set_mouse_input(mp,false);
	libvlc_video_set_key_input(mp,false);
	libvlc_audio_output_set(mp, "waveout");

    libvlc_media_parse(m);
        
    // WHY NOT WORKING?= configure looping
	//libvlc_media_add_option(m, "--loop");
    
    videoWidth = libvlc_video_get_width(mp);
    videoHeight = libvlc_video_get_height(mp);
    video_length_ms = libvlc_media_get_duration(m);
    cout << "Video: " << video_length_ms << " s" << endl;

	cout << "Video: (" << videoWidth << "px | " << videoHeight << "px)" << endl;
	
    libvlc_video_set_format(mp, "RGBA", videoWidth, videoHeight, videoWidth * 4);
	

	
	libvlc_set_fullscreen(mp, t_fullscreen );
	
    isVLCInitialized = true;
    
}

bool VLCPlayerInstance::isPlaying() {
    return libvlc_media_player_is_playing(mp);
}

bool VLCPlayerInstance::getIsInitialized() {
    return isInitialized;
}

float VLCPlayerInstance::getPosition() {
	return libvlc_media_player_get_position(mp);
}

libvlc_time_t VLCPlayerInstance::getTimeMillis(){
	return libvlc_media_player_get_time(mp);
}

void VLCPlayerInstance::setTimeMillis(libvlc_time_t ms){
	libvlc_media_player_set_time(mp, ms);
}

void VLCPlayerInstance::play() {
    libvlc_media_player_play(mp);
}


void VLCPlayerInstance::stop() {
    libvlc_media_player_stop(mp);
}

void VLCPlayerInstance::cleanupVLC() {
    libvlc_media_player_stop(mp);
    libvlc_media_player_release(mp);
    libvlc_media_release(m);
    libvlc_release(libvlc);
}

