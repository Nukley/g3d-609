/**
 @file Capsule.cpp
  
 @maintainer Morgan McGuire, matrix@graphics3d.com

 @created 2003-02-07
 @edited  2005-08-18

 Copyright 2000-2005, Morgan McGuire.
 All rights reserved.
 */

#include "G3D/Capsule.h"
#include "G3D/BinaryInput.h"
#include "G3D/BinaryOutput.h"
#include "G3D/LineSegment.h"
#include "G3D/Sphere.h"
#include "G3D/CoordinateFrame.h"
#include "G3D/Line.h"
#include "G3D/AABox.h"

namespace G3D {

Capsule::Capsule(class BinaryInput& b) {
	deserialize(b);
}


Capsule::Capsule() {
}


Capsule::Capsule(const Vector3& _p1, const Vector3& _p2, double _r) 
	: p1(_p1), p2(_p2), radius(_r) {
}


void Capsule::serialize(class BinaryOutput& b) const {
	p1.serialize(b);
	p2.serialize(b);
	b.writeFloat64(radius);
}


void Capsule::deserialize(class BinaryInput& b) {
	p1.deserialize(b);
	p2.deserialize(b);
	radius = b.readFloat64();
}


Line Capsule::getAxis() const {
	return Line::fromTwoPoints(p1, p2);
}


Vector3 Capsule::getPoint1() const {
	return p1;
}


Vector3 Capsule::getPoint2() const {
	return p2;
}


float Capsule::getRadius() const {
	return (float)radius;
}


float Capsule::getVolume() const {
	return 
		// Sphere volume
		pow(radius, 3) * G3D_PI * 4 / 3 +

		// Cylinder volume
		pow(radius, 2) * (p1 - p2).magnitude();
}


float Capsule::getSurfaceArea() const {

	return
		// Sphere area
		pow(radius, 2) * 4 * G3D_PI +

		// Cylinder area
		2 * G3D_PI * radius * (p1 - p2).magnitude();
}


void Capsule::getBounds(AABox& out) const {
    Vector3 min = p1.min(p2) - (Vector3(1, 1, 1) * radius);
    Vector3 max = p1.max(p2) + (Vector3(1, 1, 1) * radius);

    out = AABox(min, max);
}

bool Capsule::contains(const Vector3& p) const { 
    return LineSegment::fromTwoPoints(p1, p2).distanceSquared(p) <= square(radius);
}


void Capsule::getRandomSurfacePoint(Vector3& p, Vector3& N) const {
    float h = height();
    float r = getRadius();

    // Create a random point on a standard capsule and then rotate to the global frame.

    // Relative areas
    float capRelArea  = sqrt(r) / 2.0f;
    float sideRelArea = r * h;

    float r1 = random(0, capRelArea * 2 + sideRelArea);

    if (r1 < capRelArea * 2) {

        // Select a point uniformly at random on a sphere
        N = Sphere(Vector3::zero(), 1).randomSurfacePoint();
        p = N * r;
        p.y += sign(p.y) * h / 2.0f;
    } else {
        // Side
        float a = random(0, G3D_TWO_PI);
        N.x = cos(a);
        N.y = 0;
        N.z = sin(a);
        p.x = N.x * r;
        p.z = N.y * r;
        p.y = random(-h / 2.0f, h / 2.0f);
    }

    // Transform to world space
    CoordinateFrame cframe;
    getReferenceFrame(cframe);
    
    p = cframe.pointToWorldSpace(p);
    N = cframe.normalToWorldSpace(N);
}


void Capsule::getReferenceFrame(CoordinateFrame& cframe) const {
    cframe.translation = center();

    Vector3 Y = (p1 - p2).direction();
    Vector3 X = (abs(Y.dot(Vector3::unitX())) > 0.9) ? Vector3::unitY() : Vector3::unitX();
    Vector3 Z = X.cross(Y).direction();
    X = Y.cross(Z);        
    cframe.rotation.setColumn(0, X);
    cframe.rotation.setColumn(1, Y);
    cframe.rotation.setColumn(2, Z);
}


Vector3 Capsule::randomInteriorPoint() const {
    float h = height();
    float r = getRadius();

    // Create a random point in a standard capsule and then rotate to the global frame.

    Vector3 p;

    float hemiVolume = G3D_PI * (r*r*r) * 4 / 6.0;
    float cylVolume = G3D_PI * square(r) * h;
    
    float r1 = random(0, 2.0 * hemiVolume + cylVolume);

    if (r1 < 2.0 * hemiVolume) {

        p = Sphere(Vector3::zero(), r).randomInteriorPoint();

        p.y += sign(p.y) * h / 2.0f;

    } else {

        // Select a point uniformly at random on a disk
        float a = random(0, G3D_TWO_PI);
        float r2 = sqrt(random(0, 1)) * r;

        p = Vector3(cos(a) * r2,
                    random(-h / 2.0f, h / 2.0f),
                    sin(a) * r2);
    }

    // Transform to world space
    CoordinateFrame cframe;
    getReferenceFrame(cframe);
    
    return cframe.pointToWorldSpace(p);
}

} // namespace
