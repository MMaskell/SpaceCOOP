#include "GraphicalConsole.h"

const unsigned int GraphicalConsole::fontSize = 14;
const float GraphicalConsole::borderX = 10.0f;
const float GraphicalConsole::borderY = 10.0f;
const float GraphicalConsole::lineGap = 8.0f;

sf::Font GraphicalConsole::font;

GraphicalConsole::GraphicalConsole() {
}


GraphicalConsole::~GraphicalConsole() {
}

void GraphicalConsole::log(std::string msg, LogLevel level) {
	struct Message m;
	m.msg = msg;
	m.level = level;
	std::lock_guard<std::mutex> guard(lock);
	logs.push_back(m);
}

void GraphicalConsole::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	auto view = target.getView();
	target.setView(consoleView);
	sf::Vector2u size = target.getSize();
	//Draw backing
	sf::RectangleShape background(sf::Vector2f(size.x, size.y));
	background.setFillColor(sf::Color(0, 0, 0, 127));
	target.draw(background, states);
	float inputHeight = borderY + fontSize;
	float inputTop = size.y - inputHeight - lineGap;
	//Draw text
	float lineStartPos = inputTop - (fontSize + lineGap);
	int lineIndex = logs.size() - viewOffset - 1;
	//TODO: Line wrapping
	lock.lock();
	while (lineStartPos > 0.0 && lineIndex >= 0) {
		sf::Text line(logs[lineIndex].msg, font, fontSize);
		switch (logs[lineIndex].level) {
			case LogLevel::INFO:
				line.setOutlineColor(sf::Color::White);
				line.setFillColor(sf::Color::White);
				break;
			case LogLevel::WARNING:
				line.setOutlineColor(sf::Color::Yellow);
				line.setFillColor(sf::Color::Yellow);
				break;
			case LogLevel::ERROR:
				line.setOutlineColor(sf::Color::Red);
				line.setFillColor(sf::Color::Red);
				break;
		}
		line.setPosition(borderX, lineStartPos);
		target.draw(line, states);
		//Update positioning
		lineStartPos -= fontSize + lineGap;
		lineIndex--;
	}
	lock.unlock();
	//Draw input box
	//float h = fontSize + lineGap * 2;
	sf::RectangleShape input(sf::Vector2f(size.x, inputHeight));
	input.setFillColor(sf::Color(0, 0, 0, 127));
	input.setPosition(0.0f, inputTop);
	target.draw(input, states);
	//Draw current input
	sf::Text inputText(command, font, fontSize);
	inputText.setOutlineColor(sf::Color::Green);
	inputText.setFillColor(sf::Color::Green);
	inputText.setPosition(borderX, inputTop);
	target.draw(inputText, states);

	//Reset view
	target.setView(view);
}

void GraphicalConsole::loadFont(std::string fontName) {
	font.loadFromFile(fontName);
}

void GraphicalConsole::resize(unsigned int width, unsigned int height) {
	consoleView = sf::View(sf::FloatRect(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height)));
}