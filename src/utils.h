#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900
#define FOV 60
#define Z0 (WINDOW_WIDTH/2)/tan((FOV/2) * M_PI / 180.0)

void tick(Uint64 fps);