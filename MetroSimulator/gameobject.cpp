#include "gameobject.h"
#include "globalstate.h"

GameObject::GameObject(const std::string & name)
	: m_name(name), m_state(GlobalState::getInstance()), 
	m_id(m_next_id++)
{

}

GameObject::~GameObject()
{
}



int GameObject::m_next_id = 1; // must increase in every instance