#pragma once
#include <string>
#include <vector>

namespace gl {
	class DeltaTime
	{
	public:
		static float Time() { return m_time; }
		static void AddTimer(std::string name);
		static float GetTimer(std::string name);
		static void SetTimer(std::string name, float time);
		static void StartTimer(std::string name);
		static void StopTimer(std::string name);
		static void RestartTimer(std::string name);
		static void DeleteTimer(std::string name);
		static bool TimerExist(std::string name);
	private:
		static void Update(float time);
	private:
		struct Timer
		{
			std::string name;
			float time;
			bool playing;
		};
		friend class Game;
		static float m_time;
		static std::vector<Timer> m_timers;
	};
}
