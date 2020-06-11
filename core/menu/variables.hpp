#pragma once

namespace variables {
	// misc
	inline bool watermark = true;
	inline bool bhop = false;
	inline bool backtrack = false;
	//visuals
	inline bool showteamesp = false;
	inline bool boxesp = false;
	inline bool nameesp = false;
	inline bool healthesp = false;
	inline bool armoresp = false;
	inline bool glowesp = false;
	inline bool boneesp = false;
	inline bool snaplineesp = false;
	inline bool drawc4 = false;
	inline bool drawbacktrack = false;
	inline bool drawfov = false;
	//aim
	inline bool aimbot = false;
	inline float aimbot_fov = 0.f;
	inline float aimbot_smoothing = 2.f;
	inline bool aimbot_isvisiblecheck = true;

	namespace menu {
		inline bool opened = false;
		inline int x = 140, y = 140;
		inline int w = 600, h = 450;
	}
}