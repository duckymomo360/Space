#pragma once
#include <cmath>

struct Vector2 {
	float x, y;

	Vector2() : x(0.0f), y(0.0f) {};

	Vector2(float x, float y) : x(x), y(y) {};
	
	Vector2 operator+(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(const Vector2& other) const {
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator*(float scalar) const {
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 RotateAround(const Vector2& origin, float angle) {
		float s = std::sin(angle);
		float c = std::cos(angle);

		float dx = x - origin.x;
		float dy = y - origin.y;

		float qx = origin.x + c * dx - s * dy;
		float qy = origin.y + s * dx + c * dy;

		return Vector2(qx, qy);
	}

	static Vector2 FromAngle(float angle) {
		float qx = std::sin(angle);
		float qy = std::cos(angle);
		return Vector2(qx, qy);
	}

    static const Vector2 Zero;
    static const Vector2 One;
    static const Vector2 Up;
    static const Vector2 Down;
    static const Vector2 Left;
    static const Vector2 Right;
};
