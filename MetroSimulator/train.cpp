#include "train.h"
#include "util.h"
#include "globalstate.h"
#include "station.h"
#include <iostream>


Train::Train(std::vector<Station*>* route)
	: GameObject("Train"), m_route(route), m_capacity(5)
{

}

Train::~Train()
{
    for (auto p : m_current_passengers)
    {
        delete p;
    }
    m_current_passengers.clear();
}

void Train::init()
{
    m_brush_train.texture = "";
    SETCOLOR(m_brush_train.fill_color, 1.0f, 0.5f, 0.0f);
    SETCOLOR(m_brush_train.outline_color, 0.0f, 0.0f, 0.0f);
    m_brush_train.fill_opacity = 1.0f;
    m_brush_train.outline_opacity = 1.0f;

    SETCOLOR(m_brush_train_debug.fill_color, 0.2f, 1.0f, 0.2f);
    m_brush_train_debug.fill_opacity = 0.8f;

    SETCOLOR(m_brush_train_text.fill_color, 1.0f, 1.0f, 1.0f);
}

void Train::draw()
{
    if (!m_route) return;

    Station* s1 = m_route->at(m_current_station);
    Station* s2 = m_route->at(m_current_station + 1);

    float x1 = s1->getPosX();   // coordinates from starting station
    float y1 = s1->getPosY();
    float x2 = s2->getPosX();   // coordinates from the next station
    float y2 = s2->getPosY();   

    // Using linear interpolation
    float pos_x = x1 + (x2 - x1) * m_progress;
    float pos_y = y1 + (y2 - y1) * m_progress;

    graphics::drawRect(pos_x, pos_y, 0.4f, 0.2f, m_brush_train);

    // to hide the text of current_passangers we have to use collision detection

    bool collision_s1 = checkCollision(pos_x, pos_y, 0.4f, 0.2f, s1->getPosX(), s1->getPosY(), 0.25f, 0.25f);

    bool collision_s2 = false;
    if (s2)
    {
        collision_s2 = checkCollision(pos_x, pos_y, 0.4f, 0.2f, s2->getPosX(), s2->getPosY(), 0.25f, 0.25f);
    }

    if (!collision_s1 && !collision_s2)
    {
        graphics::drawText(pos_x - 0.08f, pos_y + 0.08f, 0.2f, std::to_string(m_current_passengers.size()), m_brush_train_text);
    }

    if (m_state->m_debugging)
    {
        graphics::drawRect(pos_x, pos_y, 0.4f, 0.2f, m_brush_train_debug);
    }
}

void Train::update(float dt)
{
    if (m_state->m_pause) return;
    // if there is only one node (or none) don't start
    if (!m_route || m_route->size() < 2) return;

    // going forward
    if (!m_reverse) 
    {
        m_progress += m_speed * dt / 2.5f;

        if (m_progress >= 1.0f) 
        {
 
            // here we manipulate passengers
            passenger_operations();

            m_progress = 0.0f;
            m_current_station++;

            // if the train is on the last station 
            if (m_current_station >= m_route->size() - 1)
            {
                m_current_station = m_route->size() - 2;
                m_progress = 1.0f;          
                m_reverse = true;
            }
        }   

    }
    // going backwards
    else 
    {
        m_progress -= m_speed * dt / 2.5f;
        if (m_progress <= 0.0f) 
        {
            passenger_operations();

            m_progress = 1.0f;
            m_current_station--;

            // if the train is in the starting station
            if (m_current_station < 0)
            {
                m_current_station = 0;
                m_progress = 0.0f;
                m_reverse = false;
            }
        }
    }
}

void Train::passenger_operations()
{
    Station* current_station_obj = nullptr;

    // if it is going forward then the current_station is the next of m_current_station
    // because we call this function when progress >= 1.0f
    if (!m_reverse)
    {
        if (m_current_station + 1 < m_route->size())
        {
            current_station_obj = m_route->at(m_current_station + 1);
        }
    }
    // otherwise the train going backwards, so the current_station is equal to m_current_station
    else
    {
        current_station_obj = m_route->at(m_current_station);
    }

    if (!current_station_obj) return;

    // finding the next train stop
    Station* next_train_stop = nullptr;
    if (!m_reverse) {
        if (m_current_station + 2 < m_route->size())
            // m_current_stion + 1 is the current so
            next_train_stop = m_route->at(m_current_station + 2);
    }
    else {
        if (m_current_station - 1 >= 0)
            next_train_stop = m_route->at(m_current_station - 1);
    }

    // APOVIVASH
    // we are going from the last passenger to the first to avoid bugs when a passenger delete
    for (int i = m_current_passengers.size() - 1; i >= 0; i--)
    {
        Passenger* p = m_current_passengers[i];

        
        if (p->getNextTarget() == current_station_obj)
        {
            
            m_current_passengers.erase(m_current_passengers.begin() + i);

          
            p->advancePath();

            if (p->hasReachedDestination()) {
                std::cout << "Passenger departed in " << p->getDeparture()->getName() << std::endl;
                delete p; 
            }
            else {
                
                //std::cout << "Passenger transfering in " << current_station_obj->getName() << std::endl;
                current_station_obj->addPassenger(p);

                p->setArrival(current_station_obj); // to draw again if someone chainge trains
            }
        }
    }

    // EPIVIVASH
    std::deque<Passenger*>& waiting_people = current_station_obj->getPeople();
    auto iter = waiting_people.begin();

    while (iter != waiting_people.end())
    {
        if (m_current_passengers.size() >= m_capacity) break;

        Passenger* p = *iter;
        Station* target = p->getNextTarget(); 

        // check if the current train goes there
        bool train_goes_there = false;
        for (auto station : *m_route) {
            if (station == target) {
                train_goes_there = true; 
                break;
            }
        }

        if (train_goes_there) {
            m_current_passengers.push_back(p);
            iter = waiting_people.erase(iter); // boarded
        }
        else {
            iter++; // the other train
        }
    }
}

void Train::shiftStationIndex(int d)
{
    m_current_station += d;
}
