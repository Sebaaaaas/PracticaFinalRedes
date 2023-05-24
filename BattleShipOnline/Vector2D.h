#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <cmath>

class Vector2D
{
private:
	double x; // coordenada x
	double y; // coordenada y
public:
	// constructor por defecto
	Vector2D() : x(0), y(0) {}
	// constructor con par�metros x e y
	Vector2D(double _x, double _y) : x(_x), y(_y) {}

	// double que devuelve la x
	double getX() const { return x; };
	// double que devuelve la y
	double getY() const{ return y; };

	// normalizaci�n de mi vector
	Vector2D& normalizeVector();

	// operador suma
	Vector2D& operator+(const Vector2D& other);
	// operador resta
	Vector2D& operator-(const Vector2D& other);
	// operador multiplicar
	Vector2D& operator*(const Vector2D& other);
	// operador suma adicional
	Vector2D& operator+=(const Vector2D& other);
	// multiplicaci�n escalar
	Vector2D& operator*(const int& other);
	
	// producto escalar de dos vectores
	double scalarProduct(const Vector2D& v1, const Vector2D& v2);
	// vector multiplicaci�n escalar
	Vector2D& scalarMultiplication(const double& scalar);
};

#endif /* VECTOR2D_H_ */