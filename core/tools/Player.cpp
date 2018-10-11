#include "..\e2dtool.h"


std::map<size_t, e2d::Music*> e2d::Player::musics_;

e2d::Player::Player()
	: volume_(1.f)
{
}

e2d::Player::~Player()
{
}

bool e2d::Player::Load(const String & file_path)
{
	if (file_path.IsEmpty())
		return false;

	Music * music = new (std::nothrow) Music();

	if (music)
	{
		if (music->Load(file_path))
		{
			music->SetVolume(volume_);
			musics_.insert(std::make_pair(file_path.GetHash(), music));
			return true;
		}
		else
		{
			delete music;
		}
	}
	return false;
}

bool e2d::Player::Play(const String & file_path, int loop_count)
{
	if (file_path.IsEmpty())
		return false;

	if (Load(file_path))
	{
		auto music = musics_[file_path.GetHash()];
		if (music->Play(loop_count))
		{
			return true;
		}
	}
	return false;
}

void e2d::Player::Pause(const String & file_path)
{
	if (file_path.IsEmpty())
		return;

	size_t hash = file_path.GetHash();
	if (musics_.end() != musics_.find(hash))
		musics_[hash]->Pause();
}

void e2d::Player::Resume(const String & file_path)
{
	if (file_path.IsEmpty())
		return;

	size_t hash = file_path.GetHash();
	if (musics_.end() != musics_.find(hash))
		musics_[hash]->Play();
}

void e2d::Player::Stop(const String & file_path)
{
	if (file_path.IsEmpty())
		return;

	size_t hash = file_path.GetHash();
	if (musics_.end() != musics_.find(hash))
		musics_[hash]->Stop();
}

bool e2d::Player::IsPlaying(const String & file_path)
{
	if (file_path.IsEmpty())
		return false;

	size_t hash = file_path.GetHash();
	if (musics_.end() != musics_.find(hash))
		return musics_[hash]->IsPlaying();
	return false;
}

bool e2d::Player::Load(const Resource& res)
{
	if (musics_.end() != musics_.find(res.id))
		return true;

	Music * music = new (std::nothrow) Music();

	if (music)
	{
		if (music->Load(res))
		{
			music->SetVolume(volume_);
			musics_.insert(std::make_pair(res.id, music));
			return true;
		}
		else
		{
			delete music;
		}
	}
	return false;
}

bool e2d::Player::Play(const Resource& res, int loop_count)
{
	if (Load(res))
	{
		auto music = musics_[res.id];
		if (music->Play(loop_count))
		{
			return true;
		}
	}
	return false;
}

void e2d::Player::Pause(const Resource& res)
{
	if (musics_.end() != musics_.find(res.id))
		musics_[res.id]->Pause();
}

void e2d::Player::Resume(const Resource& res)
{
	if (musics_.end() != musics_.find(res.id))
		musics_[res.id]->Play();
}

void e2d::Player::Stop(const Resource& res)
{
	if (musics_.end() != musics_.find(res.id))
		musics_[res.id]->Stop();
}

bool e2d::Player::IsPlaying(const Resource& res)
{
	if (musics_.end() != musics_.find(res.id))
		return musics_[res.id]->IsPlaying();
	return false;
}

float e2d::Player::GetVolume()
{
	return volume_;
}

void e2d::Player::SetVolume(float volume)
{
	volume_ = std::min(std::max(volume, 0.f), 1.f);
	for (const auto& pair : musics_)
	{
		pair.second->SetVolume(volume_);
	}
}

void e2d::Player::PauseAll()
{
	for (const auto& pair : musics_)
	{
		pair.second->Pause();
	}
}

void e2d::Player::ResumeAll()
{
	for (const auto& pair : musics_)
	{
		pair.second->Play();
	}
}

void e2d::Player::StopAll()
{
	for (const auto& pair : musics_)
	{
		pair.second->Stop();
	}
}

void e2d::Player::ClearCache()
{
	if (musics_.empty())
		return;

	for (const auto& pair : musics_)
	{
		delete pair.second;
	}
	musics_.clear();
}
