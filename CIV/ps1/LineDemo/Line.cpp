/*
 * Line.cpp
 *
 *  Created on: Jan 31, 2014
 *      Author: jon
 */

#include <iostream>
#include <cmath>
#include "Line.hpp"

using namespace sf;

LineSegment::LineSegment(const Vector2f& ptA, const Vector2f& ptB) {
	double dX = ptB.x - ptA.x,
			dY = ptB.y - ptA.y;
	double length = sqrt(dX * dX + dY * dY);
	_repr = RectangleShape(Vector2f(length, 0));
	_repr.setPosition(ptA);
	float angle = atan2(dY, dX) * 180;
	angle /= M_PI;
	_repr.setRotation(angle);
	_repr.setOutlineThickness(1.0f);
	_repr.setOutlineColor(Color::Blue);
}

LineSegment::LineSegment(const Vector2f& origin, double angle, double length)
	: _repr(Vector2f(length, 0))
{
	_repr.setPosition(origin);
	_repr.setRotation(angle);
	_repr.setOutlineThickness(1.0f);
	_repr.setOutlineColor(Color::Blue);
}

void LineSegment::setThickness(float thickness) {
	_repr.setOutlineThickness(thickness);
}

void LineSegment::setColor(Color color) {
	_repr.setOutlineColor(color);
}

void LineSegment::setLength(float length) {
	_repr.setSize(Vector2f(length, 0.0f));
}

void LineSegment::pointTo(const Vector2f& target) {
	double dX = _repr.getPosition().x - target.x,
			dY = _repr.getPosition().y - target.y;
	float angle = ((atan2(dY, dX) * 180) / M_PI) - 180;
	_repr.setRotation(angle);
}

/*
void LineSegment::setTarget(const Vector2f& target) {
	double dX = _repr.getPosition().x - target.x,
			dY = _repr.getPosition().y - target.y;
	double length = sqrt(dX * dX + dY * dY);
	double angle = ((atan2(dY, dX) * 180) / M_PI) - 180;
	_repr.setRotation(angle);
	_repr.setSize(Vector2f(length, 0));
}
*/

float LineSegment::getLength() const {
	return _repr.getSize().x;
}

void LineSegment::draw(RenderTarget& target, RenderStates states) const {
	target.draw(_repr);
}

void LineSegment::setPosition(float x, float y) {
	_repr.setPosition(x, y);
}

void LineSegment::setPosition(const Vector2f& position) {
	_repr.setPosition(position);
}

void LineSegment::setRotation(float angle) {
	_repr.setRotation(angle);
}

void LineSegment::setScale(float factorX, float factorY) {
	_repr.setScale(factorX, 1.0f);
}

void LineSegment::setScale(const Vector2f& factors) {
	_repr.setScale(factors.x, 1.0f);
}

void LineSegment::setScale(float factor) {
	_repr.setScale(factor, 1.0f);
}

void LineSegment::setOrigin(const Vector2f& origin) {
	_repr.setOrigin(origin.x, 0);
}

void LineSegment::setOrigin(float origin) {
	_repr.setOrigin(origin, 0);
}

const Vector2f& LineSegment::getPosition() const {
	return _repr.getPosition();
}

const Vector2f LineSegment::getTarget() const {
	return _repr.getPosition() + Vector2f(getLength(), 0.0f);
}

float LineSegment::getRotation() const{
	return _repr.getRotation();
}

float LineSegment::getScale() const {
	return _repr.getScale().x;
}

float LineSegment::getOrigin() const {
	return _repr.getOrigin().x;
}

void LineSegment::move(float offsetX, float offsetY) {
	_repr.move(offsetX, offsetY);
}

void LineSegment::move(const Vector2f& offset) {
	_repr.move(offset);
}

void LineSegment::rotate(float angle) {
	_repr.rotate(angle);
}

void LineSegment::scale(float factorX, float factorY) {
	_repr.scale(factorX, 1.0f);
}

void LineSegment::scale(const Vector2f& factors) {
	_repr.scale(factors.x, 1.0f);
}

void LineSegment::scale(float factor) {
	_repr.scale(factor, 1.0f);
}

const Transform& LineSegment::getTransform() {
	return _repr.getTransform();
}

const Transform& LineSegment::getInverseTransform() {
	return _repr.getInverseTransform();
}

std::ostream& operator<<(std::ostream& out, const LineSegment& ls) {
	out << "LineSegment :: (" << ls.getPosition().x << ", " << ls.getPosition().y
			<< ") -> (" << ls.getTarget().x << ", " << ls.getTarget().y
	    << "), length: " << ls.getLength()
		<< ", angle: " << ls.getRotation();
	return out;
}
