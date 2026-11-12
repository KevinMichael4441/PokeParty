#pragma once

#include <queue>
#include <string>
#include <iostream>

struct Entry
{
	std::string m_name;
	int m_kills;

	bool operator<(const Entry& t_other) const
	{
		return m_kills < t_other.m_kills;
	}
};


class Leaderboard
{
private:
	std::priority_queue<Entry> m_players;

public:
	void addPlayer(std::string t_name, int t_kills);

	void displayLeaderboard();
};