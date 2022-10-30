#pragma once
#include "common.hpp
#include "gta/enums.hpp"
#include "gta/player.hpp"

/* 
---DOCUMENTATION---

this is my own take on a glorified player list. for a D3D UI, and because of that: 
we have multiple variables that will be updated in a seperate thread so it doesn't fuck with the D3D thread

NOTE: DO NOT ADD/REMOVE ON PLAYER JOIN/LEAVES, IF YOU'RE USING BBV1 UI IT WILL CRASH IF YOU DON'T NULLPTR CHECK THE RETURN VALUES, DO THAT SHIT BEFORE!

everthing else is self-explanatory. if you can't figure it out then it sucks to suck eh?
*/

namespace big {
	class player {
	public:
		player() = default;

		player(CNetGamePlayer* net_game_player, std::uint64_t rid) : m_net_game_player(net_game_player), m_rid(rid) {};

		// use threads to update this stuff accordingly
    CNetGamePlayer* m_net_game_player;
		std::uint64_t m_rid;
    
    // misc, not needed. use threads to update this stuff accordingly
		bool script_host = false;

    // an example variable to try out per-player looping
		bool frozen = false;
	};

	class players {
	public:
		void add(CNetGamePlayer* net_game_player)
		{
			players_map.insert({ net_game_player->player_info->m_rockstar_id, player(net_game_player, net_game_player->player_info->m_rockstar_id) });
		}

		void add_multiple(std::vector<CNetGamePlayer*> players)
		{
			for (auto the_player : players)
				players_map.insert({ the_player->player_info->m_rockstar_id, player(the_player, the_player->player_info->m_rockstar_id) });
		}

		void remove(std::uint64_t rid)
		{
			players_map.erase(rid);
		}

		void remove_multiple(std::vector<std::uint64_t> rids)
		{
			for (auto rid : rids)
				players_map.erase(rid);
		}

		void set_selected(std::uint64_t rid)
		{
			m_selected_player = rid;
		}

		player* get_selected()
		{
			for (auto& [key, val] : players_map)
				if (val.m_net_game_player != nullptr)
					if (val.m_net_game_player->player_info != nullptr)
						if (val.m_rid != 0)
							if (val.m_rid == m_selected_player)
								return &val;

			return nullptr;
		}

		player* get_by_rid(std::uint64_t rid)
		{
			for (auto& [key, val] : players_map)
				if (val.m_net_game_player != nullptr)
					if (val.m_net_game_player->player_info != nullptr)
						if (val.m_rid != 0)
							if (val.m_rid == rid)
								return &val;

			return nullptr;
		}

	public:
		std::map<uint64_t, player> players_map;
		std::uint64_t m_selected_player;
	};

	inline players g_players;
}
