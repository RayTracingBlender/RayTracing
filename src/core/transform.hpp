#pragma once

#include "geometry.hpp"

namespace rt{

#define NOT_ONE(x) ((x) < .999f || (x) > 1.001f)

struct Matrix4x4 {
public:
	Float m[4][4];

	Matrix4x4() {
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
		m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] = m[2][0] = m[2][1] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.f;
	}
	Matrix4x4(Float mat[4][4]);
	Matrix4x4(Float t00, Float t01, Float t02, Float t03,
			  Float t10, Float t11, Float t12, Float t13,
			  Float t20, Float t21, Float t22, Float t23,
			  Float t30, Float t31, Float t32, Float t33);

	friend Matrix4x4 Inverse(const Matrix4x4 &);


	friend Matrix4x4 Transpose(const Matrix4x4 &);

	static Matrix4x4 Mul(const Matrix4x4 &m1, const Matrix4x4 &m2) {
		Matrix4x4 r;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				r.m[i][j] = m1.m[i][0] * m2.m[0][j] +
							m1.m[i][1] * m2.m[1][j] + 
							m1.m[i][2] * m2.m[2][j] + 
							m1.m[i][3] * m2.m[3][j];
		return r;
	}

	

	bool operator == (const Matrix4x4 &m2) const {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (m[i][j] != m2.m[i][j]) return false;
		return true;
	}
	bool operator != (const Matrix4x4 &m2) const {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (m[i][j] != m2.m[i][j]) return true;
		return false;
	}
};

class Transform {
private:
	Matrix4x4 m, mInv;
public:
	Transform(const Float mat4[4][4]) {
		m = Matrix4x4(mat4[0][0], mat4[1][0], mat4[2][0], mat4[3][0],
			mat4[0][1], mat4[1][1], mat4[2][1], mat4[3][1],
			mat4[0][2], mat4[1][2], mat4[2][2], mat4[3][2],
			mat4[0][3], mat4[1][3], mat4[2][3], mat4[3][3]);
		mInv = Inverse(m);
	}

	bool HasScale() const {
		Float a = (*this)(Vector3f(1, 0, 0)).LengthSquared();
		Float b = (*this)(Vector3f(0, 1, 0)).LengthSquared();
		Float c = (*this)(Vector3f(0, 0, 1)).LengthSquared();
		return(NOT_ONE(a) || NOT_ONE(b) || NOT_ONE(c));
	}

	Transform(const Matrix4x4 &m) : m(m), mInv(Inverse(m)) {};
	Transform(const Matrix4x4 &m, const Matrix4x4 &mInv) : m(m), mInv(mInv) {};

	friend Transform Inverse(const Transform &t) { return Transform(t.mInv, t.m); }
	friend Transform Transpose(const Transform &t) { return Transform(Transpose(t.m), Transpose(t.mInv)); }

	
	template <typename T> inline Vector3<T> operator()(const Vector3<T> &v)  const;
	template <typename T> inline Normal3<T> operator()(const Normal3<T> &n)  const;
	template <typename T> inline Point3<T>  operator()(const Point3<T>  &p)  const;
						  inline Ray        operator()(const Ray        &r)  const;
	template <typename T> inline Bounds3<T> operator()(const Bounds3<T> &p)  const;
								 Transform  operator *(const Transform  &t2) const;
								 bool  SwapsHandedness()					 const;

	template <typename T> inline Point3<T> Transform::operator()(const Point3<T> &p, Vector3<T> *pError) const;
};

Transform Translate(const Vector3f &delta);
Transform Scale(Float x, Float y, Float z);
Transform RotateX(Float theta);
Transform RotateY(Float theta);
Transform RotateZ(Float theta);
Transform Rotate(Float theta, const Vector3f &axis);
Transform LookAt(const Point3f &pos, const Point3f &look, const Vector3f &up);

template <typename T> inline Vector3<T> Transform::operator()(const Vector3<T> &v) const {
	T x = v.x, y = v.y, z = v.z;
	return Vector3<T>(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
					  m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z, 
					  m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
}

template <typename T> inline Normal3<T> Transform::operator()(const Normal3<T> &n) const {
	T x = n.x, y = n.y, z = n.z;
	return Normal3<T>(mInv.m[0][0] * x + mInv.m[0][1] * y + mInv.m[0][2] * z,
					  mInv.m[1][0] * x + mInv.m[1][1] * y + mInv.m[1][2] * z,
					  mInv.m[2][0] * x + mInv.m[2][1] * y + mInv.m[2][2] * z);
}

template <typename T> inline Point3<T>  Transform::operator()(const Point3<T>  &p) const {
	T x = p.x, y = p.y, z = p.z;
	T xp = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
	T xp = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
	T xp = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
	T xp = m[3][0] * x + m[3][1] * y + m[3][2] * z + m[3][3];
	if (wp == 1) return Point3<T>(xp, yp, zp);
				 return Point3<T>(xp, yp, zp) / wp;
}

template <typename T> inline Bounds3<T> Transform::operator()(const Bounds3<T> &b) const {
	const Transform &M = *this;
	Bounds3f ret(M(Point3f(b.pMin.x, b.pMin.y, b.pMin.z)));
	ret = Union(ret, M(Point3f(b.pMax.x, b.pMin.y, b.pMin.z)));
	ret = Union(ret, M(Point3f(b.pMin.x, b.pMax.y, b.pMin.z)));
	ret = Union(ret, M(Point3f(b.pMin.x, b.pMin.y, b.pMax.z)));
	ret = Union(ret, M(Point3f(b.pMin.x, b.pMax.y, b.pMax.z)));
	ret = Union(ret, M(Point3f(b.pMax.x, b.pMax.y, b.pMin.z)));
	ret = Union(ret, M(Point3f(b.pMax.x, b.pMin.y, b.pMax.z)));
	ret = Union(ret, M(Point3f(b.pMax.x, b.pMax.y, b.pMax.z)));
	return ret;
}

/**
inline Ray        Transform::operator()(const Ray        &r) const {
	Vector3f oError;
	Point3f o = (*this)(r.o, &oError);
	Vector3f d = (*this)(r.d);
	//TODO Page 233
}


template <typename T>
inline Point3<T> Transform::operator()(const Point3<T> &p,
	Vector3<T> *pError) const {
	T x = p.x, y = p.y, z = p.z;
	// Compute transformed coordinates from point _pt_
	T xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
	T yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
	T zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
	T wp = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];

	// Compute absolute error for transformed point
	T xAbsSum = (std::abs(m.m[0][0] * x) + std::abs(m.m[0][1] * y) +
		std::abs(m.m[0][2] * z) + std::abs(m.m[0][3]));
	T yAbsSum = (std::abs(m.m[1][0] * x) + std::abs(m.m[1][1] * y) +
		std::abs(m.m[1][2] * z) + std::abs(m.m[1][3]));
	T zAbsSum = (std::abs(m.m[2][0] * x) + std::abs(m.m[2][1] * y) +
		std::abs(m.m[2][2] * z) + std::abs(m.m[2][3]));
	*pError = gamma(3) * Vector3<T>(xAbsSum, yAbsSum, zAbsSum);
	CHECK_NE(wp, 0);
	if (wp == 1)
		return Point3<T>(xp, yp, zp);
	else
		return Point3<T>(xp, yp, zp) / wp;
}*/
}
