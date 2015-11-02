
int main(void)
{

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    int tiles[4 * 4] = {
        0, 1, 1, 0,
        1, 1, 0, 0,
        0, 1, 1, 1,
        0, 0, 1, 1,
    };

    Game game;
    game.tiles.tiles = tiles;
    game.tiles.width = 4;
    game.tiles.height = 4;

    game.players[0].position = vec2(2.0f, 6.0f);
    game.players[0].velocity = vec2(0.0f, 0.0f);
    game.players[0].size = vec2(0.5f, 0.8f);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0f, 10.0f, 0.0f, 10.0f, -1.0f, 1.0f);

        update_input(&game);

        physics_tick(&game, 0.016f);

        render(&game);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
