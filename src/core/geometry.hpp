#pragma once
#include "utility.hpp"

/**
	
	Vectors
	
*/

namespace rt{

template <typename T> class Vector2 {
public:
	T x, y;
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

template <typename T> class Vector3 {
public:
	T x, y, z;

	bool HasNaNs() const {
		return std::isnan(x) || std::isnan(y) || std::isnan(z);
	}

	Vector3() { x = y = z = 0; }
	Vector3(T x, T y, T z) : x(x), y(y), z(z) {
		assert(!HasNaNs());
	}

	T operator[](int i) const {
		assert(i >= 0 && i <= 2);
		if (i == 0) return x;
		if (i == 1) return y;
					return z;
	}

	T operator[](int i) {
		assert(i >= 0 && i <= 2);
		if (i == 0) return x;
		if (i == 1) return y;
					return z;
	}

	Vector3<T> operator+(const Vector3<T> &v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3<T> &operator+=(const Vector3<T> &v) const {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3<T> operator-(const Vector3<T> &v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3<T> &operator-=(const Vector3<T> &v) const {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector3<T> operator*(T s) const {
		return Vector3(x * s, y * s, z * s);
	}

	Vector3<T> &operator*=(T s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	
	Vector3<T> operator/(T f) const {
		assert(f != 0);
		float inv = (float)1 / f;
		return Vector3(x * inv, y * inv, z * inv);
	}

	Vector3<T> &operator/=(T f) {
		assert(f != 0);
		float inv = (float)1 / f;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}

	Vector3<T> operator -() const { return Vector3<T>(-x, -y, -z); }

	float LengthSquared() const { return x * x + y * y + z * z; }	
	float Length() const { return std::sqrt(LengthSquared()); }

	
};

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;

template <typename T> Vector3<T> Abs(const Vector3<T> &v) {
	return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

template <typename T> Vector3<T> Dot(const Vector3<T> &v1, const Vector3<T> &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T> Vector3<T> AbsDot(const Vector3<T> &v1, const Vector3<T> &v2) {
	return std::abs(Dot(v1, v2));
}

template <typename T> Vector3<T> Cross(const Vector3<T> &v1, const Vector3<T> &v2) {

	double v1x = v1.x;
	double v2x = v2.x;

	double v1y = v1.y;
	double v2y = v2.y;

	double v1z = v1.z;
	double v2z = v2.z;

	return Vector3<T>((v1y * v2z) - (v1z * v2y),
					  (v1z * v2x) - (v1x * v2z),
					  (v1x * v2y) - (v1y * v2x));
}

template <typename T> Vector3<T> Normalize(const Vector3<T> &v) { return v / v.Length(); }

template <typename T> T MinComponent(const Vector3<T> &v) { return std::min(v.x, std::min(v.y, v.z)); }
template <typename T> T MaxComponent(const Vector3<T> &v) { return std::max(v.x, std::max(v.y, v.z)); }

template <typename T> Vector3<T> Min(const Vector3<T> &v1, const Vector3<T> &v2) {
	return Vector3<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y), std::min(v1.z, v2.z));
}
template <typename T> Vector3<T> Max(const Vector3<T> &v1, const Vector3<T> &v2) {
	return Vector3<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z));
}

template <typename T> int MaxDimension(const Vector3<T> &v) { return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2); }

template <typename T> Vector3<T> Max(const Vector3<T> &v1, int x, int y, int z) {
	return Vector3<T>(v[x], v[y], v[z]);
}

//Why?
template <typename T> inline Vector3<T> operator*(T s, const Vector3<T> &v) { return s * v; };

template <typename T> inline void CoordinateSystem(const Vector3<T> &v1, const Vector3<T> &v2, const Vector3<T> &v3) {
	if (std::abs(v1.x) > std::abs(v1.y))
		*v2 = Vector3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
	else
		*v2 = Vector3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
	*v3 = Cross(v1, *v2);
}








/**

Points

*/






template <typename T> class Point3 {
public:
	T x, y, z;

	bool HasNaNs() const {
		return std::isnan(x) || std::isnan(y) || std::isnan(z);
	}

	Point3() { x = y = z = 0; }
	Point3(T x, T y, T z) : x(x), y(y), z(z) {
		assert(!HasNaNs());
	}

	template <typename U> explicit Point3(const Point3<U> &p) : x((T)p.x), y((T)p.y), z((T)p.z) {
		assert(!HasNaNs());
	}

	template <typename U> explicit operator Vector3<U>() const {
		return Vector3<U>(x, y, z);
	}

	Point3<T> operator+(const Vector3<T> &v) const{
		return Point3<T>(x + v.x, y + v.y, z + v.z);
	}

	Point3<T> &operator+=(const Vector3<T> &v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Point3<T> operator-(const Vector3<T> &v) const {
		return Point3<T>(x - v.x, y - v.y, z - v.z);
	}

	Vector3<T> operator-(const Point3<T> &p) const {
		return Vector3<T>(x - p.x, y - p.y, z - p.z);
	}

	Point3<T> &operator-=(const Vector3<T> &v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
};
typedef Point3<float> Point3f;
typedef Point3<int> Point3i;


template <typename T> class Point2 {
public:
	T x, y;

	bool HasNaNs() const {
		return std::isnan(x) || std::isnan(y);
	}

	explicit Point2(const Point3<T> &p) : x(p.x), y(p.y){
		assert(!HasNaNs());
	}
};
typedef Point2<float> Point2f;
typedef Point2<int> Point2i;

template <typename T> inline float Distance(const Point3<T> &p1, const Point3<T> &p2) {
	return (p1 - p2).Length();
}

template <typename T> inline float DistanceSquared(const Point3<T> &p1, const Point3<T> &p2) {
	return (p1 - p2).LengthSquared();
}

template <typename T> Point3<T> Lerp(float t, const Point3<T> &p1, const Point3<T> &p2) {
	return (1 - t) * p0 + t * p1;
}

template <typename T> Point3<T> Min(const Point3<T> &p1, const Point3<T> &p2) {
	return Vector3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z));
}
template <typename T> Point3<T> Max(const Point3<T> &p1, const Point3<T> &p2) {
	return Vector3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z));
}

template <typename T> Point3<T> Floor(const Point3<T> &p) {
	return Point3<T>(std::floor(p.x), std::floor(p.y), std::floor(p.z));
}
template <typename T> Point3<T> Ceil(const Point3<T> &p) {
	return Point3<T>(std::ceil(p.x), std::ceil(p.y), std::ceil(p.z));
}
template <typename T> Point3<T> Abs(const Point3<T> &p) {
	return Point3<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
}

template <typename T> Point3<T> Permute(const Point3<T> &p, int x, int y, int z) {
	return Point3<T>(p[x], p[y], p[z]);
}






/**


	Normals


*/
template <typename T> class Normal3 {
public:
	T x, y, z;

	bool HasNaNs() const {
		return std::isnan(x) || std::isnan(y) || std::isnan(z);
	}

	Normal3() { x = y = z = 0; }
	Normal3(T x, T y, T z) : x(x), y(y), z(z) {
		assert(!HasNaNs());
	}
	explicit Normal3(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {
		assert(!v.HasNaNs());
	}

	T operator[](int i) const {
		assert(i >= 0 && i <= 2);
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}

	T operator[](int i) {
		assert(i >= 0 && i <= 2);
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}

	Normal3<T> operator+(const Normal3<T> &n) const {
		return Normal3(x + n.x, y + n.y, z + n.z);
	}

	Normal3<T> &operator+=(const Normal3<T> &n) const {
		x += n.x;
		y += n.y;
		z += n.z;
		return *this;
	}

	Normal3<T> operator-(const Normal3<T> &n) const {
		return Normal3(x - n.x, y - n.y, z - n.z);
	}

	Normal3<T> &operator-=(const Normal3<T> &n) const {
		x -= n.x;
		y -= n.y;
		z -= n.z;
		return *this;
	}

	Normal3<T> operator*(T s) const {
		return Normal3(x * s, y * s, z * s);
	}

	Normal3<T> &operator*=(T s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Normal3<T> operator/(T f) const {
		assert(f != 0);
		float inv = (float)1 / f;
		return Normal3(x * inv, y * inv, z * inv);
	}

	Normal3<T> &operator/=(T f) {
		assert(f != 0);
		float inv = (float)1 / f;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}

	Normal3<T> operator -() const { return Normal3<T>(-x, -y, -z); }

	float LengthSquared() const { return x * x + y * y + z * z; }
	float Length() const { return std::sqrt(LengthSquared()); }
};



typedef Normal3<float> Normal3f;

template <typename T> Normal3<T> Dot(const Normal3<T> &n1, const Normal3<T> &n2) {
	return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

template <typename T> Normal3<T> Dot(const Normal3<T> &n1, const Vector3<T> &v2) {
	return n1.x * v2.x + n1.y * v2.y + n1.z * v2.z;
}

template <typename T> Normal3<T> Dot(const Vector3<T> &v1, const Normal3<T> &n2) {
	return v1.x * n2.x + v1.y * n2.y + v1.z * n2.z;
}

template <typename T> Normal3<T> AbsDot(const Normal3<T> &n1, const Normal3<T> &n2) {
	return std::abs(Dot(n1, n2));
}

template <typename T> Normal3<T> AbsDot(const Normal3<T> &n1, const Vector3<T> &v2) {
	return std::abs(Dot(n1, v2));
}

template <typename T> Normal3<T> AbsDot(const Vector3<T> &v1, const Normal3<T> &n2) {
	return std::abs(Dot(v1, n2));
}

template <typename T> Normal3<T> Abs(const Normal3<T> &n) {
	return Vector3<T>(std::abs(n.x), std::abs(n.y), std::abs(n.z));
}

template <typename T> Normal3<T> Normalize(const Normal3<T> &n) { return n / n.Length(); }

template <typename T> T MinComponent(const Normal3<T> &n) { return std::min(n.x, std::min(n.y, n.z)); }
template <typename T> T MaxComponent(const Normal3<T> &n) { return std::max(n.x, std::max(n.y, n.z)); }

template <typename T> Normal3<T> Min(const Normal3<T> &n1, const Normal3<T> n2) {
	return Vector3<T>(std::min(n1.x, n2.x), std::min(n1.y, n2.y), std::min(n1.z, n2.z));
}
template <typename T> Normal3<T> Max(const Normal3<T> &n1, const Normal3<T> &n2) {
	return Vector3<T>(std::max(n1.x, n2.x), std::max(n1.y, n2.y), std::max(n1.z, n2.z));
}

template <typename T> int MaxDimension(const Normal3<T> &n) { return (n.x > n.y) ? ((n.x > n.z) ? 0 : 2) : ((n.y > n.z) ? 1 : 2); }

template <typename T> Normal3<T> Max(const Normal3<T> &n, int x, int y, int z) {
	return Vector3<T>(n[x], n[y], n[z]);
}

template <typename T> inline Normal3<T> Faceforward(const Normal3<T> &n, const Vector3<T> &v) {
	return (Dot(n, v) < 0.f) ? -n : n;
}

//template <typename T> inline Vector3<T>::Vector3(const Normal3<T> &n) : x(n.x), y(n.y), z(n.z) { assert(n.HasNaNs()); }





/**

	Rays

*/


class Ray {
public:
	Point3f o;
	Vector3f d;
	mutable float tMax;
	float time;
	//const Medium *medium;

	Ray() : tMax(INFINITY), time(0.f) /**, medium(nullptr)*/{};
	Ray(const Point3f &o, const Vector3f &d, float tMax = INFINITY, float time = 0.f /**, const *medium = nullptr*/) : o(o), d(d), tMax(tMax), time(time) /**, medium(medium)*/ {}

	Point3f operator()(float t) const { return o + d * t; };


};

class RayDifferntial : public Ray {
public:
	bool hasDifferntials;
	Point3f rxOrigin, ryOrigin;
	Vector3f rxDirection, ryDirection;

	RayDifferntial() { hasDifferntials = false; }
	RayDifferntial(const Point3f &o, const Vector3f &d, float tMax = INFINITY, float time = 0.f /**, const *medium = nullptr*/) : Ray(o, d, tMax, time /**, medium*/) { hasDifferntials = false; }
	RayDifferntial(const Ray &ray) : Ray(ray) {
		hasDifferntials = false;
	}

	void ScaleDifferentials(float s) {
		rxOrigin    = o + (rxOrigin - o)    * s;
		ryOrigin    = o + (ryOrigin - o)    * s;
		rxDirection = d + (rxDirection - d) * s;
		ryDirection = d + (ryDirection - d) * s;
	}
};








/**

	Bounding Boxes

*/

template <typename T> class Bounds2 {
public:
};

typedef Bounds2<float> Bounds2f;
typedef Bounds2<int>   Bounds2i;

template <typename T> class Bounds3 {
public:
	Point3<T> pMin, pMax;

	Bounds3() {
		T minNum = std::numeric_limits<T>::lowest();
		T maxNum = std::numeric_limits<T>::max();

		pMin = Point3<T>(maxNum, maxNum, maxNum);
		pMax = Point3<T>(minNum, minNum, minNum);
	}
	Bounds3(const Point3<T> &p) : pMin(p), pMax(p) {}
	Bounds3(const Point3<T> &p1, const Point3<T> &p2) : pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)), pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z)) {}


	const Point3<T> &operator[](int i) const {
		if (i == 0)
			return pMin;
		else
			return pMax;
	}
	Point3<T> &operator[](int i) {
		if (i == 0)
			return pMin;
		else
			return pMax;
	}

	Point3<T> corner(int corner) const {
		return Point3<T>((*this)[(corner & 1)].x,
			             (*this)[(corner & 2) ? 1 : 0].y,
			             (*this)[(corner & 4) ? 1 : 0].z);
	}

	Vector3<T> Diagonal() const { return pMax - pMin;  };

	T SurfaceArea() const {
		Vector3<T> d = Diagonal();
		return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
	}

	T Volume() const {
		Vector3<T> d = Diagonal();
		return d.x * d.y * d.z;
	}

	int MaxiumumExtent() const {
		Vector3<T> d = Diagonal();
		if (d.x > d.y && d.x > d.z)
			return 0;
		else if (d.y > d.z)
			return 1;
		return 2;
	}

	Point3<T> Lerp(const Point3f &t) {
		return Point3<T>(::Lerp(t.x, pMin.x, pMax.x),
						 ::Lerp(t.y, pMin.y, pMax.y),
						 ::Lerp(t.z, pMin.z, pMax.z));
	}

	Vector3<T> Offset(const Point3<T> &p) const {
		Vector3<T> o = p - pMin;
		if (pMax.x > pMin.x) o.x /= pMax.x - pMin.x;
		if (pMax.y > pMin.y) o.y /= pMax.y - pMin.y;
		if (pMax.z > pMin.z) o.z /= pMax.z - pMin.z;
		return o;
	}

	void BoundingSphere(Point3<T> *center, float *radius) const {
		*center = (pMin + pMax) / 2;
		*radius = Inside(*center, *this) ? Distance(*center, pMax) : 0;
	}
};

typedef Bounds3<float> Bounds3f;
typedef Bounds3<int>   Bounds3i;

template <typename T> Bounds3<T> Union(const Bounds3<T> &b, const Point3<T> &p) {
	return Bounds3<T>(Point3<T>(std::min(b.pMin.x, p.x), std::min(b.pMin.y, p.y), std::min(b.pMin.z, p.z)),
		              Point3<T>(std::max(b.pMax.x, p.x), std::max(b.pMax.y, p.y), std::max(b.pMax.z, p.z)));
}

template <typename T> Bounds3<T> Union(const Bounds3<T> &b1, const Bounds3<T> &b2) {
	return Bounds3<T>(Point3<T>(std::min(b1.pMin.x, b2.pMin.x), std::min(b1.pMin.y, b2.pMin.y), std::min(b1.pMin.z, b2.pMin.z)),
		              Point3<T>(std::max(b1.pMax.x, b2.pMax.x), std::max(b1.pMax.y, b2.pMax.y), std::max(b1.pMax.z, b2.pMax.z)));
}

template <typename T> Bounds3<T> Intersect(const Bounds3<T> &b1, const Bounds3<T> &b2) {
	return Bounds3<T>(Point3<T>(std::max(b1.pMin.x, b2.pMin.x), std::max(b1.pMin.y, b2.pMin.y), std::max(b1.pMin.z, b2.pMin.z)),
					  Point3<T>(std::min(b1.pMax.x, b2.pMax.x), std::min(b1.pMax.y, b2.pMax.y), std::min(b1.pMax.z, b2.pMax.z)));
}

template <typename T> bool Overlaps(const Bounds3<T> &b1, const Bounds3<T> &b2) {
	bool x = (b1.pMax.x >= b2.pMin.x) && (b1.pMin.x <= b2.pMax.x);
	bool y = (b1.pMax.y >= b2.pMin.y) && (b1.pMin.y <= b2.pMax.y);
	bool z = (b1.pMax.z >= b2.pMin.z) && (b1.pMin.z <= b2.pMax.z);
	return (x && y && z);
}

template <typename T> bool Inside(const Point3<T> &p, const Bounds3<T> &b) {
	return (p.x >= b.pMin.x && p.x <= b.pMax.x &&
			p.y >= b.pMin.y && p.y <= b.pMax.y &&
			p.z >= b.pMin.z && p.z <= b.pMax.z);
}

template <typename T> bool InsideExclusive(const Point3<T> &p, const Bounds3<T> &b) {
	return (p.x >= b.pMin.x && p.x < b.pMax.x &&
			p.y >= b.pMin.y && p.y < b.pMax.y &&
			p.z >= b.pMin.z && p.z < b.pMax.z);
}

template <typename T, typename U> inline Bounds3<T> Expand(const Bounds3<T> &b, U delta) {
	return Bounds3<T>(b.pMin - Vector3<T>(delta, delta, delta),
		b.pMax + Vector3<T>(delta, delta, delta));
}




}

