/*
 * main.cpp
 *
 *  Created on: Feb 2, 2014
 *      Author: jon
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Line.hpp"

using namespace sf;
RenderWindow app(VideoMode(800, 600, 32), "Line Demo");

int main(void) {
	app.setFramerateLimit(60);

	/* Constructing a line segment from two points */
	LineSegment line1(Vector2f(0.0f, 0.0f), Vector2f(800.0f, 600.0f));

	/* Constructing a line segment from a point, length and angle */
	LineSegment line2(Vector2f(0.0f, 600.0f), -45, 128);

	/* Change color */
	//line2.setColor(Color::Red);

	/* Change length */
	//line2.setLength(512.0f);

	/* Change thickness */
	//line2.setThickness(5.0f);

	/* Center the line's origin at a new position */
	//line2.setPosition(400.0f, 300.0f);

	/* Change the scale at which the line is drawn */
	/* Note that this does not actually change the length of the line */
	//line2.setScale(0.5f);

	/* Change the origin */
	/* i.e. the point at which the line is rotated, moved, etc */
	//line2.setOrigin(line2.getLength() / 2);

	/* orient the line to face a point */
	//line2.pointTo(Vector2f(400.0f, 0.0f));

	Event event;
	while(app.isOpen()) {
		while(app.pollEvent(event)) {
			if(event.type == Event::Closed) {
				app.close();
				break;
			}
		}
		app.clear(Color::Black);
		app.draw(line1);
		app.draw(line2);
		//line2.rotate(1.0f);
		//line2.move(1.6f, 1.2f);
		//line2.scale(1.01f);
		app.display();
	}
}
