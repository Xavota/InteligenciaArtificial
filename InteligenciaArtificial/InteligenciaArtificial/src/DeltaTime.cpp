#include "DeltaTime.h"

namespace gl {
float DeltaTime::m_time = 0;
std::vector<DeltaTime::Timer> DeltaTime::m_timers;

void DeltaTime::AddTimer(std::string name)
{
	m_timers.push_back(Timer{name, 0, true});
}
float DeltaTime::GetTimer(std::string name)
{
	for (Timer& t : m_timers)
	{
		if (t.name == name)
		{
			return t.time;
		}
	}
	return 0;
}
void DeltaTime::SetTimer(std::string name, float time)
{
	for (Timer& t : m_timers)
	{
		if (t.name == name)
		{
			t.time = time;
		}
	}
}
void DeltaTime::StartTimer(std::string name)
{
	for (Timer& t : m_timers)
	{
		if (t.name == name)
		{
			t.playing = true;
		}
	}
}
void DeltaTime::StopTimer(std::string name)
{
	for (Timer& t : m_timers)
	{
		if (t.name == name)
		{
			t.playing = false;
		}
	}
}
void DeltaTime::RestartTimer(std::string name)
{
	for (Timer& t : m_timers)
	{
		if (t.name == name)
		{
			t.time = 0;
		}
	}
}
void DeltaTime::DeleteTimer(std::string name)
{
	for (int i = 0; i < m_timers.size(); i++)
	{
		if (m_timers[i].name == name)
		{
			m_timers.erase(m_timers.begin() + i);
		}
	}
}
bool DeltaTime::TimerExist(std::string name)
{
	for (Timer& t : m_timers)
	{
		if (t.name == name)
		{
			return true;
		}
	}
	return false;
}
void DeltaTime::Update(float time)
{
	m_time = time;
	for (Timer& t : m_timers)
	{
		if (t.playing)
		{
			t.time += time;
		}
	}
}
}