/*
 * Line.hpp
 *
 *  Created on: Jan 31, 2014
 *      Author: Jonathan Madden
 */

#ifndef LINE_HPP_
#define LINE_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class LineSegment : public sf::Drawable, sf::Transformable {
public:
	LineSegment(const sf::Vector2f& ptA, const sf::Vector2f& ptB);
	LineSegment(const sf::Vector2f& origin, double angle, double length);

	void setThickness(float thickness);
	void setColor(sf::Color color);
	void setLength(float length);

	//move the line to point to the target, but don't change length
	void pointTo(const sf::Vector2f& target);
	//like pointTo, but stretch the line to the target
	//void setTarget(const sf::Vector2f& target);

	float getLength() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);

	void setRotation(float angle);

	//factorY is ignored
	void setScale(float factorX, float factorY);
	//factors.y is ignored
	void setScale(const sf::Vector2f& factors);
	//we can really only scale the length
	void setScale(float factor);

	void setOrigin(const sf::Vector2f& origin);
	void setOrigin(float origin);

	const sf::Vector2f& getPosition() const;
	const sf::Vector2f getTarget() const;
	float getRotation() const;
	float getScale() const;
	float getOrigin() const;

	void move(float offsetX, float offSetY);
	void move(const sf::Vector2f& offset);

	void rotate(float angle);

	//factorY is ignored
	void scale(float factorX, float factorY);
	//factors.y is ignored
	void scale(const sf::Vector2f& factors);
	//we can really only scale the length
	void scale(float factor);

	const sf::Transform& getTransform();
	const sf::Transform& getInverseTransform();
private:
	sf::RectangleShape _repr;
};

std::ostream& operator<<(std::ostream& out, const LineSegment& ls);

#endif /* LINE_HPP_ */
