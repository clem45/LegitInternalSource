#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../menu/variables.hpp"

namespace misc {
	namespace movement {
		void bunny_hop(c_usercmd* cmd);
	};
}

namespace visuals {
	void boxesp();
	void nameesp();
	void healthesp();
	void armoresp();
	void glowesp();
	void boneesp();
	void snaplineesp();
	void drawc4();
	void drawfov();
}

namespace CBacktracking
{
	void RegisterTick(c_usercmd* cmd);
	void Begin(c_usercmd* cmd);
	void End();
	void Draw();
}

namespace legitbot
{
	player_t* GetBestTarget(c_usercmd* cmd);
	void AimBot(c_usercmd* cmd);
}