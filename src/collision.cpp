
struct AABB
{
	Vec2 center;
	Vec2 half_size;
};

bool aabb_to_aabb(const AABB *a, const AABB *b, Vec2 *out_overlap)
{
	Vec2 diff = b->center - a->center;
	Vec2 min_distance = b->half_size + a->half_size;

	Vec2 abs_diff = vec2(fabs(diff.x), fabs(diff.y));
	Vec2 overlap = abs_diff - min_distance;

	if (overlap.x >= 0.0f || overlap.y >= 0.0f)
		return false;

	if (overlap.x < overlap.y) {
		*out_overlap = vec2(0.0f, copysignf(overlap.y, diff.y));
	} else {
		*out_overlap = vec2(copysignf(overlap.x, diff.x), 0.0f);
	}
	return true;
}

