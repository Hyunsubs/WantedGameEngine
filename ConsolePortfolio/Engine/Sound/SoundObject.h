#pragma once

#include "PreCompiledHeader/PreCompiledHeader.h"

class ENGINE_API SoundObject
{
private:
	FMOD::Sound* m_Sound;	// Sound ����
	std::list<FMOD::Channel*> m_listChannel; // Sound�� ����ǰ� �ִ� ä�� ����Ʈ

public:
    // _iRoopCount : 0 (���ѹݺ�),  _fVolume : 0 ~ 1(Volume), _bOverlap : �Ҹ� ��ø ���ɿ���
    void LoadSound(std::string _path);
    int Play(int _iRoopCount, float _fVolume, bool _bOverlap);
    void RemoveChannel(FMOD::Channel* _pTargetChannel);
    void Stop();

    // 0 ~ 1
    void SetVolume(float _f, int _iChannelIdx);
    ~SoundObject();

};