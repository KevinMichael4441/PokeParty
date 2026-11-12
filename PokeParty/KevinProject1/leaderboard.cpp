#include "leaderboard.h"


void Leaderboard::addPlayer(std::string t_name, int t_kills)
{
	m_players.push({ t_name, t_kills });
}

void Leaderboard::displayLeaderboard()
{
	while (!m_players.empty())
	{
		std::cout << m_players.top().m_name << " - " << m_players.top().m_kills << "\n";
		m_players.pop();
	}
}