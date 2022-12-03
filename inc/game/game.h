// Todo: Refactor Game.
enum XYDir_t {up, down, left, right};

struct Snake {
    enum XYDir_t direction;
    int x;
    int y;
};

struct Snake *init_snake();

void draw_border(int color);
void draw_snake(struct Snake *snake);