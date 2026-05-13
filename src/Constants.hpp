#pragma once

namespace GameConstants {
    constexpr unsigned int WINDOW_WIDTH = 800;
    constexpr unsigned int WINDOW_HEIGHT = 600;
    constexpr unsigned int FONT_SIZE = 24;
    constexpr unsigned int SNAKE_INITIAL_LENGTH = 3;
    constexpr float CELL_SIZE = 20.f;
    constexpr int GRID_WIDTH = static_cast<int>(WINDOW_WIDTH / CELL_SIZE);
    constexpr int GRID_HEIGHT = static_cast<int>(WINDOW_HEIGHT / CELL_SIZE);

    constexpr float BASE_STEP_INTERVAL = 0.15f;
    constexpr float MIN_STEP_INTERVAL = 0.06f;
    constexpr float STEP_INTERVAL_DECREASE = 0.01f;
    constexpr int APPLES_PER_SPEED_LEVEL = 5;
}
