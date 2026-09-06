#pragma once
#include <string>

// Abstract class that all objects must 
class GameObject
{
	static int m_next_id;

protected:
	class GlobalState* m_state;		// state of game that obj must know
	std::string m_name;
	int m_id = 0;
	bool m_active = true;
	bool m_hoover = false;


public:
	GameObject(const std::string& name = "");
	virtual void update(float dt) = 0;
	virtual void init() = 0;
	virtual void draw() = 0;
	virtual ~GameObject();
	bool isActive() { return m_active; }
	void setActive(bool a) { m_active = a; }
};