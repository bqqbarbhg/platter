
struct Vec2
{
	float x, y;
};

Vec2 vec2(float x, float y)
{
	Vec2 v = { x, y };
	return v;
}

Vec2 operator+(Vec2 a, Vec2 b)
{
	return vec2(a.x + b.x, a.y + b.y);
}
Vec2 &operator+=(Vec2 &a, Vec2 b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}


Vec2 operator-(Vec2 a, Vec2 b)
{
	return vec2(a.x - b.x, a.y - b.y);
}
Vec2 &operator-=(Vec2 &a, Vec2 b)
{
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

Vec2 operator*(Vec2 a, Vec2 b)
{
	return vec2(a.x * b.x, a.y * b.y);
}

Vec2 operator*(Vec2 a, float b)
{
	return vec2(a.x * b, a.y * b);
}
Vec2 &operator*=(Vec2 &a, float b)
{
	a.x *= b;
	a.y *= b;
	return a;
}

