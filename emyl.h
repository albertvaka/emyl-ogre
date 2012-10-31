#pragma once

//Uncoment this to enable loading audio from an Ogre resource in addition to load from a file
#define EMYL_USE_OGRE

//Uncoment this if you have Boost and want emyl to create a thread to automatically update() the streams for you
//#define EMYL_USE_BOOST

#include <vector>
#include <list>
#include <map>
#include <string>
#include <stdlib.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

#define STREAM_OGG_INIT    (1<<0)
#define STREAM_OGG_LOADED  (1<<1)
#define STREAM_OGG_PLAYING (1<<2)
#define STREAM_OGG_PAUSE   (1<<3)
#define STREAM_OGG_LOOP    (1<<4)

namespace emyl {

class stream
{
public:
	 stream();
	~stream();

	bool   load    (const std::string &_filename);
	bool   load_mem(const std::string &_filename);
	bool   load_ogre(const std::string &_resname);
	bool   load_generic(void *sndfile, ov_callbacks *ptr_callbacks);

	bool   set_source();
	bool   set_source(ALuint _source);
	ALuint get_source() {return m_uiSource;}
	void   free_source();

	void   update();
	void   play();
	void   pause() {m_uiFlags ^= STREAM_OGG_PAUSE;}
	void   stop();
	
	void   seek(double _secs);
	bool   playing();

	void   set_loop(bool _loop);
	void   set_volume(ALfloat _volume);

	char*  get_error() {return m_sLastError;}

	static void updateAll();

private:
	static const int NUM_BUFFERS = 8;
	static const int BUFFER_SIZE = 65536;

#ifdef EMYL_USE_BOOST
	static void updateThread();
#endif

	void set_error(const std::string& _sErr);
	bool bStream(ALuint _buff);
	
	ALenum  m_eformat;
	ALsizei m_ifreq;

	OggVorbis_File   m_ogg;
	ALuint           m_vbuffers[NUM_BUFFERS];
	unsigned int     m_uiFlags;
	ALuint           m_uiSource;

	char*            m_sLastError;
};

class sound
{
public:
	 sound();
	~sound();
	
	bool   load(const std::string& _filename);
#ifdef EMYL_USE_OGRE
	bool   load_ogre(const std::string& _resname);
#endif

	bool   set_buffer(ALuint _buffer);
	ALuint get_buffer() {return m_vbuffer;}

	bool   set_source();
	bool   set_source(ALuint _source);

	ALuint get_source() {return m_uiSource;}

	void   free_source();

	void  play();
	void  pause();
	void  stop();

	void  play_buffer(ALuint _buffer);
	void  play_buffer(ALuint _buffer, int _loop);

	bool  playing();

	void  set_loop(int _loop);
	void  set_volume(ALfloat _volume);

	void set_position  (ALfloat _fX,  ALfloat _fY,  ALfloat _fZ);
	void set_velocity  (ALfloat _fX,  ALfloat _fY,  ALfloat _fZ);
	void set_direction (ALfloat _fX,  ALfloat _fY,  ALfloat _fZ);

	char* get_error() {return m_sLastError;}
private:
	void set_error(const std::string& _sErr);

	ALuint m_vbuffer;
	ALuint m_uiSource;

	char*  m_sLastError;
};

class manager
{
public:

	~manager();

	static manager*  get_instance();
	bool             init();

	void             delete_buffer(const std::string& _filename);
	ALuint           get_buffer(const std::string& _filename);
#ifdef EMYL_USE_OGRE
	ALuint           get_buffer_ogre(const std::string& resName);
#endif

	ALuint           source_reserve();
	void             source_unreserve(ALuint _srcID);

	void             set_volume(ALfloat _volume);
	char*            get_error() {return m_sLastError;}

	void set_position    (ALfloat _fX,  ALfloat _fY,  ALfloat _fZ);
	void set_velocity    (ALfloat _fX,  ALfloat _fY,  ALfloat _fZ);
	void set_orientation (ALfloat _fDX, ALfloat _fDY, ALfloat _fDZ,
	                      ALfloat _fUX, ALfloat _fUY, ALfloat _fUZ);

	void   sleep();
	void unsleep();

private:
	
	//Should not be public because does not use m_mSounds map
	ALuint           get_buffer_generic(void *sndfile, ov_callbacks *ptr_callbacks);

	friend class stream;
	friend class sound;

	static const int NUM_SOURCES = 16;

	void set_error(const std::string& _sErr);

	manager();

	static void delete_instance();
	static manager*               s_pInstance;
	static bool                   s_bInstanced;

	ALCdevice*                    m_alDev;
	ALCcontext*                   m_alContext;

	ALuint                        m_vSources[NUM_SOURCES];
	bool                          m_vSourcesReserved[NUM_SOURCES];
	bool                          m_vSourcesSleeped[NUM_SOURCES];

	std::map<std::string, ALuint> m_mSounds;
	
	char*                         m_sLastError;
};

typedef void(*error_callback)(const std::string &_sErr);
void set_error_callback(error_callback callback);

} //namespace emyl;

