#include "LaserBeam.h"
#include "Helper.h"
#include <memory>
#include "SolarSystem.h"

LaserBeam::LaserBeam() {
	type = 0;
}


LaserBeam::~LaserBeam() {
}

void LaserBeam::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	std::shared_ptr<EntityCore> ori = system->getEntity(origin);
	sf::Vector2f size = target.getView().getSize();
	//Put the end of the laser far enough away that it is off screen
	sf::Vector2f end = ori->getPosition() + direction * (size.x + size.y);
	sf::Vector2f delta = end - ori->getPosition();
	float length = sqrtf(delta.x * delta.x + delta.y * delta.y);
	float ang = toDegrees(atan2f(delta.y, delta.x));
	sf::RectangleShape line(sf::Vector2f(length, 20));
	line.rotate(ang);
	line.setFillColor(sf::Color(255, 0, 0, TTL * 255));
	states.transform *= getTransform();
	target.draw(line, states);
}