#include "Server.h"
#include "../shared/Console.h"
#include "Player.h"

/*

TODO
TODO  Players DCing are still listed as active on server: FIX THIS
TODO
TODO

*/

Server::Server() {
}


Server::~Server() {
}


void Server::start() {
	if (running) {
		Console::log("Attempted to start server that was already running", Console::LogLevel::ERROR);
	}
	running = true;
	incomingThread = std::thread(&Server::handleConnections, this);
}


void Server::stop() {
	running = false;
	listen.close();
	incomingThread.join();
	Console::log("No longer listening for new connections", Console::LogLevel::INFO);
	for (std::shared_ptr<Player> t : players) {
		t->disconnect();
	}
	Console::log("All players kicked", Console::LogLevel::INFO);
}

void Server::handleConnections() {
	listen.listen(port);
	Console::log("Started server", Console::LogLevel::INFO);
	while (running) {
		auto client = std::make_shared<sf::TcpSocket>();
		if (listen.accept(*client) == sf::TcpListener::Done) {
			//Handle max server capacity/nice logins and such here

			//Add client
			Console::log("New client connected", Console::LogLevel::INFO);
			auto player = std::make_shared<Player>();
			//Pass socket to player
			player->socket = client;
			//Start listening
			player->start();
			//Track player in server
			players.push_back(player);
			numPlayers++;
		}
	}
	listen.close();
}
