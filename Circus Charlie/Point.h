#pragma once

template <class type_a>
class Point{
public:	
	type_a x, y;

	Point(){}
	Point(type_a x, type_a y) : x(x), y(y){};

	//Operators
	Point operator +(const Point &p) const{
		p2Vector2 r;

		r.x = x + p.x;
		r.y = y + p.y;
	}

	Point operator -(const Point &p) const{
		p2Vector2 r;

		r.x = x - p.x;
		r.y = y - p.y;
	}

	const Point& operator +=(const Point &p){
		x += p.x;
		y += p.y;
	}

	const Point& operator -=(const Point &p){
		x -= p.x;
		y -= p.y;
	}

	bool operator ==(const Point& p) const{
		return (x == p.x && y == p.y);
	}

	bool operator !=(const Point& p) const{
		return (x != p.x || y != p.y);
	}

	// Utils ------------------------------------------------
	bool IsZero() const{
		return (x == 0 && y == 0);
	}

	Point& SetToZero(){
		x = y = 0;
		return(*this);
	}

	Point& Negate(){
		x = -x;
		y = -y;

		return(*this);
	}

	type_a Distance(const Point& p) const{
		type_a fx = p.x - x;
		type_a fy = p.y - y;

		return sqrt((fx*fx) + (fy*fy));
	}
};

typedef Point<int> iPoint;
typedef Point<float> fPoint;