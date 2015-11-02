
struct Tiles
{
	int *tiles;
	int width, height;
};

struct Player
{
	Vec2 position;
	Vec2 velocity;
	Vec2 force;
	Vec2 size;
};

struct Game
{
	Tiles tiles;
	Player players[1];
	int player_count;
};

int get_tile(const Tiles *tiles, int x, int y)
{
	if (x < 0 || y < 0 || x >= tiles->width || y >= tiles->height)
		return 0;

	return tiles->tiles[x + tiles->width * y];
}

void update_input(Game *game)
{
	game->players[0].force = vec2(0.0f, 0.0f);
	game->players[0].force.y = -0.5f;

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		game->players[0].force.x -= 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		game->players[0].force.x += 2.0f;
	}
}

void physics_tick(Game *game, float dt)
{
	for (int i = 0; i < game->player_count; i++) {
		Player *player = game->players + i;
		player->velocity += player->force * dt;
		player->position += player->velocity * dt;

		player->velocity *= 0.99f;
	}

	for (int i = 0; i < game->player_count; i++) {
		Player *player = game->players + i;

		Vec2 half_size = player->size * 0.5f;

		Vec2 min = player->position - half_size;
		Vec2 max = player->position + half_size;
		
		int min_x = (int)min.x;
		int min_y = (int)min.y;
		int max_x = (int)max.x + 1;
		int max_y = (int)max.y + 1;

		Vec2 overlaps[16];
		int overlap_count = 0;

		AABB player_aabb;
		player_aabb.center = player->position;
		player_aabb.half_size = half_size;
		
		for (int x = min_x; x < max_x; x++) {
			for (int y = min_y; y < max_y; y++) {
				if (!get_tile(&game->tiles, x, y))
					continue;

				AABB tile_aabb;
				tile_aabb.center = vec2((float)x + 0.5f, (float)y + 0.5f);
				tile_aabb.half_size = vec2(0.5f, 0.5f);

				if (aabb_to_aabb(&player_aabb, &tile_aabb, overlaps + overlap_count)) {
					if (++overlap_count >= Count(overlaps)) {
						goto break_out_of_2d_loop; // break both
					}
				}
			}
		}
break_out_of_2d_loop:
		
		// TEMP
		for (int i = 0; i < overlap_count; i++) {

			if (fabs(overlaps[i].x) > 0.0f) {
				player->velocity.x = 0.0f;
			} else {
				player->velocity.y = 0.0f;
			}

			player->position -= overlaps[i];
		}
	}
}

void render(Game *game)
{
	Tiles *tiles = &game->tiles;

	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.0f, 0.0f);

	for (int x = 0; x < tiles->width; x++) {
		for (int y = 0; y < tiles->height; y++) {

			if (!get_tile(tiles, x, y))
				continue;

			float fx = (float)x;
			float fy = (float)y;

			glVertex2f(fx, fy);
			glVertex2f(fx + 1.0f, fy);
			glVertex2f(fx + 1.0f, fy + 1.0f);

			glVertex2f(fx + 1.0f, fy + 1.0f);
			glVertex2f(fx, fy + 1.0f);
			glVertex2f(fx, fy);
		}
	}

	glColor3f(0.0f, 0.0f, 1.0f);

	for (int i = 0; i < game->player_count; i++) {
		Player *player = game->players + i;

		float fw = player->size.x;
		float fh = player->size.y;
		float fx = player->position.x - 0.5f * fw;
		float fy = player->position.y - 0.5f * fh;

		glVertex2f(fx, fy);
		glVertex2f(fx + fw, fy);
		glVertex2f(fx + fw, fy + fh);

		glVertex2f(fx + fw, fy + fh);
		glVertex2f(fx, fy + fh);
		glVertex2f(fx, fy);
	}

	glEnd();
}

