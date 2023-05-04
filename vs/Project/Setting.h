#ifndef SETTING_H
#define SETTING_H

#include <string>

using namespace std;

namespace Engine {
	enum class WindowFlag {
		WINDOWED,
		FULLSCREEN,
		EXCLUSIVE_FULLSCREEN,
		BORDERLESS
	};

	class Setting
	{
	public:
		Setting();
		~Setting();
		string windowTitle;
		int screenWidth, screenHeight, targetFrameRate;
		bool vsync;
		WindowFlag windowFlag;
		float timeScale;
	};
}

#endif

