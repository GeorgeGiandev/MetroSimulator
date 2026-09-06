#pragma once
#include <vector>
#include "station.h"
#include "rail.h"
#include <map>
#include <queue>

class Gps
{
public:
	static std::vector<Station*> BFS(Station* start, Station* end, std::vector<Rail*> rails)
	{
		if (start == end) return {};

		std::map<Station*, std::vector<Station*>> adjacency;	// Station - all adjacent stations
		
		for (Rail* r : rails)
		{
			Station* from = r->getFrom();
			Station* to = r->getTo();

			adjacency[from].push_back(to);
			adjacency[to].push_back(from);
		}

			// BFS is using queue
			std::queue<Station*> queue;
			queue.push(start);

			// checking from which station we came
			std::map<Station*, Station*> came_from;
			std::map<Station*, bool> visited;
			
			// BFS algorithm
			visited[start] = true;
			came_from[start] = nullptr; // we start from this node so there is none before
			bool found = false;

			while (!queue.empty()) {
				Station* current = queue.front();
				queue.pop();

				if (current == end) {
					found = true;
					break;
				}

				// for each neighbor of current
				for (Station* neighbor : adjacency[current]) 
				{
					// check if we have been there
					if (!visited[neighbor]) {
						visited[neighbor] = true;
						came_from[neighbor] = current; // we came from current
						queue.push(neighbor);	// we add all neihbors in the queue so to check them after
					}
				}
			}

			// backtracking
			std::vector<Station*> path;
			if (found)
			{
				Station* curr = end;
				while (curr != nullptr)
				{
					path.push_back(curr);
					curr = came_from[curr];
	
				}
				std::reverse(path.begin(), path.end());
			}
			return path;
	}
};