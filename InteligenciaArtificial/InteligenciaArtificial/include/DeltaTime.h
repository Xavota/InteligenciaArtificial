#pragma once
#include <string>
#include <vector>

namespace gl {
	/**
	  * @brief		Keeps track of the global time and can create, update and destroy timers 
	  *             accesible in any part of the document
	*/
	class DeltaTime
	{
	public:
		/**
		  * @brief		Returns the time between the last update and this
		  * @bug	    No know Bugs
		*/
		static float Time() { return m_time; }

		/**
		  * @brief		Adds a timer with a name
		  * @param      name: the name to identify the timer
		  * @bug	    No know Bugs
		*/
		static void AddTimer(std::string name);
		/**
		  * @brief		Returns the value of a timer
		  * @param      name: the name to identify the timer
		  * @bug	    No know Bugs
		*/
		static float GetTimer(std::string name);
		/**
		  * @brief		Sets the value of a timer
		  * @param      name: the name to identify the timer
		  * @param      time: the new time
		  * @bug	    No know Bugs
		*/
		static void SetTimer(std::string name, float time);
		/**
		  * @brief		Set a timer to start adding time
		  * @param      name: the name to identify the timer
		  * @bug	    No know Bugs
		*/
		static void StartTimer(std::string name);
		/**
		  * @brief		Stop a timer from addingtime
		  * @param      name: the name to identify the timer
		  * @bug	    No know Bugs
		*/
		static void StopTimer(std::string name);
		/**
		  * @brief		Returns a timer's value to 0
		  * @param      name: the name to identify the timer
		  * @bug	    No know Bugs
		*/
		static void RestartTimer(std::string name);
		/**
		  * @brief		Deletes a timer
		  * @param      name: the name to identify the timer
		  * @bug	    No know Bugs
		*/
		static void DeleteTimer(std::string name);
		/**
		  * @brief		Returns true if the timers asked already exist
		  * @param      name: the name to identify the timer
		  * @bug	    No know Bugs
		*/
		static bool TimerExist(std::string name);

	private:
		/**
		  * @brief		Updates the world time along with all the timers
		  * @param      time: time passed since the last update
		  * @bug	    No know Bugs
		*/
		static void Update(float time);

	private:
		/**
		  * @brief		Data for the stores timers
		*/
		struct Timer
		{
			std::string name;
			float time;
			bool playing;
		};
		friend class Game;
		friend class Game_FP;
		static float m_time;
		static std::vector<Timer> m_timers;
	};
}
