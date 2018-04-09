#pragma once
#include "../shared/SolarSystem.h"
#include "../shared/entities/EntityCore.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include <mutex>
#include "Player.h"

using std::unordered_map;
using std::shared_ptr;
using std::vector;
using std::mutex;

class Server;

class ServerSolarSystem :
	public SolarSystem {
public:
	ServerSolarSystem();
	~ServerSolarSystem();
	//Pass in info about star?
	void generateSystem(Server* server);

	void addEntity(shared_ptr<EntityCore> entity);
	shared_ptr<EntityCore> getEntity(UUID id);
	void removeEntity(UUID id);

	void addPlayer(shared_ptr<Player> player);
	void removePlayer(shared_ptr<Player> player);

	void update(double dt);

	std::default_random_engine generator;

	unordered_map<UUID, shared_ptr<EntityCore>> entities;
	vector<shared_ptr<Player>> players;
	mutex entityLock;
	mutex playerLock;
};

