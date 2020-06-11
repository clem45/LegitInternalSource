#include "../features.hpp"
#define FLOW_OUTGOING	0		
#define FLOW_INCOMING	1
#define MAX_FLOWS		2		// in & out
float GetFOV(const vec3_t& viewAngle, const vec3_t& aimAngle)
{
	vec3_t delta = aimAngle - viewAngle;
	delta.clamp();

	return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}

struct BacktrackRecord
{
	player_t* entity;
	vec3_t head;
	vec3_t origin;
};

struct BacktrackTick
{
	int tickcount;
	std::vector<BacktrackRecord> records;
};

	std::vector<BacktrackTick> ticks;
	player_t* entity;
	vec3_t prevOrig;

	void CBacktracking::RegisterTick(c_usercmd* cmd)
	{
		ticks.insert(ticks.begin(), BacktrackTick{ cmd->tick_count });
		auto& cur = ticks[0];

		while (ticks.size() > (1.0f/interfaces::globals->interval_per_tick) * 0.2f)
			ticks.pop_back();

		for (int i = 1; i < interfaces::globals->max_clients; i++)
		{
			auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

			if (!entity ||
				entity->dormant() ||
				entity->health() <= 0 ||
				entity->team() == csgo::local_player->team() ||
				!entity->is_alive() ||
				entity->has_gun_game_immunity())
				continue;

			cur.records.emplace_back(BacktrackRecord{ entity, entity->get_bone_position(8), entity->origin() });
		}
	}

	void CBacktracking::Begin(c_usercmd* cmd)
	{
		entity = nullptr;

		float serverTime = csgo::local_player->get_tick_base() * interfaces::globals->interval_per_tick;
		auto weapon = csgo::local_player->active_weapon();

		if (cmd->buttons & in_attack && weapon->next_primary_attack() < serverTime + 0.001)
		{
			float fov = 5.f;
			int tickcount = 0;
			bool hasTarget = false;
			vec3_t orig;

			for (auto& tick : ticks)
			{
				for (auto& record : tick.records)
				{
					vec3_t localeyepos = csgo::local_player->get_eye_pos();
					vec3_t angle = math::calculate_angle(localeyepos, record.head);
					float tmpFOV = GetFOV(cmd->viewangles, angle);

					if (tmpFOV < fov)
					{
						fov = tmpFOV;
						tickcount = tick.tickcount;
						hasTarget = true;
						entity = record.entity;
						orig = record.origin;
					}
				}
			}

			if (entity && hasTarget)
			{
				cmd->tick_count = tickcount;
				prevOrig = entity->origin();
				entity->origin() = orig;
			}
		}
	}

	void CBacktracking::End()
	{
		if (entity)
			entity->origin() = prevOrig;

		entity = nullptr;
	}

	c