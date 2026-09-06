#include "level.h"
#include "globalstate.h"
#include "util.h"
#include "point.h"
#include <cstdlib> // for rand
#include <iostream>
#include "box.h"
#include "train.h"
#include "passenger.h"
#include "gps.h"

void Level::init()
{
	// background initiallization
	SETCOLOR(m_brush_background.fill_color, 0.19f, 0.188f, 0.165f);
	m_brush_background.texture = m_state->getFullAssetPath("MetroBackground.png");
	m_brush_background.outline_opacity = 0.0f;

	// text initiallization
	SETCOLOR(m_brush_level_text.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush_level_text.fill_opacity = 0.5f;

	// points

	std::vector<Point> Points_1 =
	{
		{1.5f, 4.0f, "A"},
		{3.0f, 2.5f, "B"},
		{4.5f, 5.5f, "C"},
		{6.0f, 3.5f, "D"},
		{7.5f, 2.0f, "E"},
		{9.0f, 6.0f, "F"},
		{10.5f, 3.0f, "G"},
		{12.0f, 5.0f, "H"},
		{13.5f, 2.5f, "I"},
		{15.0f, 4.0f, "J"}
	};
	std::vector<Point> Points_2 =
	{
		{6.0f, 3.5f, "A"},  
		{9.0f, 3.5f, "B"},  
		{7.5f, 2.5f, "C"},  
		{7.5f, 5.0f, "D"}, 
		{1.5f, 1.5f, "E"},  
		{1.5f, 6.5f, "F"},  
		{13.5f, 1.5f, "G"}, 
		{13.5f, 6.5f, "H"}, 
		{4.0f, 4.0f, "I"},  
		{11.0f, 4.0f, "J"}  
	};
	std::vector<Point> Points_3 =
	{
		{2.0f, 2.0f, "A"},
		{5.0f, 1.5f, "B"},
		{8.0f, 2.0f, "C"},
		{11.0f, 1.5f, "D"},
		{14.0f, 2.0f, "E"},
		{3.5f, 6.0f, "F"},
		{6.5f, 6.5f, "G"},
		{9.5f, 6.0f, "H"},
		{12.5f, 6.5f, "I"},
		{15.0f, 5.5f, "J"}
	};

	// random points
	std::vector<Point> Points;
	unsigned int random = rand() % 10;
	std::cout << random << std::endl;
	if (random < 7)
	{
		Points = Points_1;
	}
	else if (random < 9)
	{
		Points = Points_2;

	}
	else
	{
		Points = Points_3;
	}
	//stations initialliaztion
	for (const auto& p : Points)
	{
		Station* s = new Station(p.name, p.x, p.y, 0.25f);
		s->init();
		stations.push_back(s);
	}

	// Box
	Box* redBox = new Box(15.0f, 7.6f, 0.3f, "red.png");
	boxes.push_back(redBox);

	Box* blueBox = new Box(15.4f, 7.6f, 0.3f, "blue.png");
	boxes.push_back(blueBox);

	redBox->init();
	blueBox->init();
}

void Level::draw()
{
	
	float cw = m_state->getCanvasWidth();
	float ch = m_state->getCanvasHeight();

	float mx = graphics::windowToCanvasX(m_state->getGlobalMouseState().cur_pos_x);
	float my = graphics::windowToCanvasY(m_state->getGlobalMouseState().cur_pos_y);


	// draw background
	graphics::drawRect(cw/ 2.0f, ch/ 2.0f, cw, ch, m_brush_background);

	// draw rails
	for (auto r : rails) 
		r->draw();

	// draw trains
	for (auto t : trains)
		t->draw();

	// draw stations
	for (auto s : stations) 
		s->draw();


	for (auto b : boxes) 
		b->draw();

	// draw lines remaining
	graphics::Brush br;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	std::string red_text = std::to_string(m_red_rails_count) + "/5";
	graphics::drawText(15.0f - 0.2f, 0.3f, 0.25f, red_text, br);
	std::string blue_text = std::to_string(m_blue_rails_count) + "/4";
	graphics::drawText(15.4f, 0.3f, 0.25f, blue_text, br);

	// draw text
	graphics::drawText(14.87f, 7.35f, 0.3f, "Rails", m_brush_level_text);

	// pause
	m_brush_pause.texture = m_state->getFullAssetPath("pause.png");
	m_brush_pause.outline_opacity = 0.0f;
	if (m_state->m_pause && m_state->getInstance()->m_start)
	{
		graphics::drawRect(1.0f, 1.0f, 1.0f, 1.0f, m_brush_pause);
	}



	if (m_start_station != nullptr) {
		graphics::Brush br;
		// color is black
		br.outline_opacity = 1.0f;
		br.fill_opacity = 1.0f;
		graphics::drawLine(m_start_station->getPosX(), m_start_station->getPosY(), mx, my, br);
	}

}

void Level::update(float dt)
{
	if (m_state->m_game_over) { return; }

	for (auto s : stations) 
		s->update(dt);
	

	for (auto b : boxes) 
		b->update(dt);

	for (auto t : trains)
		t->update(dt);


	float mx = graphics::windowToCanvasX(m_state->getGlobalMouseState().cur_pos_x);
	float my = graphics::windowToCanvasY(m_state->getGlobalMouseState().cur_pos_y);

	// choose color from the boxes
	if (m_state->getGlobalMouseState().button_left_pressed) {
		for (auto b : boxes) {
			if (mx > b->getPoint().x - b->getSize() / 2.0f && mx < b->getPoint().x + b->getSize() / 2.0f &&
				my > b->getPoint().y - b->getSize() / 2.0f && my < b->getPoint().y + b->getSize() / 2.0f)
			{
				m_active_color = b->getName();
				std::cout << "The color choosed is: " << m_active_color << std::endl;
				return;
			}
		}
	}

	// dragging stations
	if (m_state->getGlobalMouseState().button_left_pressed) {
		for (auto s : stations) {
			if (s->contains(mx, my)) {
				m_start_station = s;
				std::cout << "The starting drag station is: " << s->getName() << std::endl;
				break;
			}
		}
	}

	
	if (m_state->getGlobalMouseState().button_left_released ) 
	{

		if (m_start_station != nullptr)
		{
			Station* end_station = nullptr;
			for (auto s : stations) {
				if (s->contains(mx, my)) {
					end_station = s;
					std::cout << "The ending drag station is: " << s->getName() << std::endl;
					break;
				}
			}

			if (end_station != nullptr && end_station != m_start_station)
			{
				// just to use one variable for each train
				std::vector<Station*>* current_route = nullptr;
				int* current_counter = nullptr;
				int max_limit = 0;
				Train* current_train = nullptr;

				if (m_active_color == "red.png") 
				{
					current_route = &m_red_rails;
					current_counter = &m_red_rails_count;
					max_limit = 5;
					current_train = m_red_train;
				}
				else 
				{
					current_route = &m_blue_rails;
					current_counter = &m_blue_rails_count;
					max_limit = 4;
					current_train = m_blue_train;
				}

				// checking if the connection is valid
				bool valid_connection = false;
				bool add_to_front = false;
				Station* station_to_add = nullptr;

				if (current_route->empty()) 
				{
					valid_connection = true;	// the rail can be added anywhere
				}
				else 
				{
					// the station must be added in the front or in the back of the route
					Station* first = current_route->front();
					Station* last = current_route->back();
					
					// trying to add to the last station
					if (m_start_station == last) 
					{
						// started dragging from the last station
						valid_connection = true;
						station_to_add = end_station;
					}
					else if (end_station == last) {
						// ended dragging to the last station
						valid_connection = true;
						station_to_add = m_start_station;
					}
					// trying to add to the first station
					else if (m_start_station == first) {
						// started dragging from the first station
						valid_connection = true;
						add_to_front = true;
						station_to_add = end_station;
					}
					else if (end_station == first) {
						// ended dragging to the first station
						valid_connection = true;
						add_to_front = true;
						station_to_add = m_start_station;
					}
				}

				if (valid_connection)
				{
					if (*current_counter < max_limit)
					{
						Rail* newRail = new Rail(m_start_station, end_station, m_active_color);
						newRail->init();
						rails.push_back(newRail);
						std::cout << "Rail added. Color: " << m_active_color << std::endl;

						(*current_counter)++;

						if (current_route->empty()) 
						{
							current_route->push_back(m_start_station);
							current_route->push_back(end_station);
						}
						else 
						{
							if (add_to_front) 
							{
								current_route->insert(current_route->begin(), station_to_add);	// insert the station to index 0 and shift the others.
								// if a station is added to front, every other station's index must increase
								// otherwise the train will float into the air
								if (current_train != nullptr) 
								{
									current_train->shiftStationIndex(1);
								}
							}
							else 
							{
								current_route->push_back(station_to_add);
							}
						}

						if (m_active_color == "blue.png" && m_blue_train == nullptr)
						{
							m_blue_train = new Train(&m_blue_rails);
							m_blue_train->init();
							trains.push_back(m_blue_train);
						}
						else if (m_active_color == "red.png" && m_red_train == nullptr) 
						{
							m_red_train = new Train(&m_red_rails);
							m_red_train->init();
							trains.push_back(m_red_train);
						}
					}
					else
					{
						std::cout << "You reached max rails of color: " << m_active_color << std::endl;
					}
				}
				else
				{
					std::cout << "You must extend the line from its ends." << std::endl;
				}
			}

		}

		m_start_station = nullptr;
	}

	// initiallize and update passengers
	if (m_state->m_pause) return;

	m_passenger_spawn_timer += dt / 1000; 
	
	if (m_passenger_spawn_timer > 5.0f) 
	{
		m_passenger_spawn_timer = 0.0f;


		// random stations 
		int start = rand() % stations.size();
		int end = rand() % stations.size();

		while (start == end) {
			end = rand() % stations.size();
		}

		Station* startS = stations[start];
		Station* endS = stations[end];

		std::vector<Station*> path = Gps::BFS(startS, endS, rails);

		// passengers will occurre only when is a path from startS to endS
		if (!path.empty()) 
		{
			Passenger* p = new Passenger(startS, endS);
			p->init();
			p->setPath(path);
			startS->addPassenger(p);

		}
		
	}
}




Level::Level()
{
}

Level::~Level()
{
	for (auto s : stations)
	{
		delete s;
	}
	stations.clear();

	for (auto b : boxes) 
	{
		delete b;
	}
	boxes.clear();

	for (auto t : trains) {
		delete t;
	}
	trains.clear();

	for (auto r : rails) {
		delete r;
	}
	rails.clear();
}
