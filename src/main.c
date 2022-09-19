#include "engine.h"


SDL_Window* screen = NULL;
SDL_Renderer* renderer = NULL;

int init(){
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        return -1;
    }

    screen = SDL_CreateWindow("4D",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (screen == NULL){
        return -1;
    }

    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        return -1;
    }


    return 0;

}

void Quit(){
    SDL_Quit();
}

int mainloop(SDL_Window* screen, SDL_Renderer* renderer){
    int running=1;
    SDL_Event event;

    int n_points = 16;
    Point4D* points = (Point4D*)calloc(n_points, sizeof(Point4D));
    points[0] = NewPoint4D(100, 100, 100, 100);
    points[1] = NewPoint4D(100, 100, -100, 100);
    points[2] = NewPoint4D(100, -100, 100, 100);
    points[3] = NewPoint4D(-100, 100, 100, 100);
    points[4] = NewPoint4D(+100, -100, -100, 100);
    points[5] = NewPoint4D(-100, 100, -100, 100);
    points[6] = NewPoint4D(-100, -100, 100, 100);
    points[7] = NewPoint4D(-100, -100, -100, 100);
    points[8] = NewPoint4D(100, 100, 100, -100);
    points[9] = NewPoint4D(100, 100, -100, -100);
    points[10] = NewPoint4D(100, -100, 100, -100);
    points[11] = NewPoint4D(-100, 100, 100, -100);
    points[12] = NewPoint4D(100, -100, -100, -100);
    points[13] = NewPoint4D(-100, 100, -100, -100);
    points[14] = NewPoint4D(-100, -100, 100, -100);
    points[15] = NewPoint4D(-100, -100, -100, -100);

    int n_lines = 32;
    int **lines = (int**)calloc(n_lines, sizeof(int*));
    for (int i=0; i<n_lines; i++){
        lines[i] = (int*) calloc(2, sizeof(int));
    }

    lines[0][0] = 0;
    lines[0][1] = 1;
    lines[1][0] = 0;
    lines[1][1] = 2;
    lines[2][0] = 0;
    lines[2][1] = 3;
    lines[3][0] = 1;
    lines[3][1] = 4;
    lines[4][0] = 1;
    lines[4][1] = 5;
    lines[5][0] = 2;
    lines[5][1] = 6;
    lines[6][0] = 2;
    lines[6][1] = 4;
    lines[7][0] = 3;
    lines[7][1] = 5;
    lines[8][0] = 3;
    lines[8][1] = 6;
    lines[9][0] = 4;
    lines[9][1] = 7;
    lines[10][0] = 5;
    lines[10][1] = 7;
    lines[11][0] = 6;
    lines[11][1] = 7;
    lines[12][0] = 8;
    lines[12][1] = 9;
    lines[13][0] = 8;
    lines[13][1] = 10;
    lines[14][0] = 8;
    lines[14][1] = 11;
    lines[15][0] = 9;
    lines[15][1] = 12;
    lines[16][0] = 9;
    lines[16][1] = 13;
    lines[17][0] = 10;
    lines[17][1] = 14;
    lines[18][0] = 10;
    lines[18][1] = 12;
    lines[19][0] = 11;
    lines[19][1] = 13;
    lines[20][0] = 11;
    lines[20][1] = 14;
    lines[21][0] = 12;
    lines[21][1] = 15;
    lines[22][0] = 13;
    lines[22][1] = 15;
    lines[23][0] = 14;
    lines[23][1] = 15;
    lines[24][0] = 0;
    lines[24][1] = 8;
    lines[25][0] = 1;
    lines[25][1] = 9;
    lines[26][0] = 2;
    lines[26][1] = 10;
    lines[27][0] = 3;
    lines[27][1] = 11;
    lines[28][0] = 4;
    lines[28][1] = 12;
    lines[29][0] = 5;
    lines[29][1] = 13;
    lines[30][0] = 6;
    lines[30][1] = 14;
    lines[31][0] = 7;
    lines[31][1] = 15;



    double rotation[6];
    int t = 0;
    while (running){
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            running = 0;
                            break;
                    }
            }
        }

        // for (int i=0; i<n_points; i++){
        //     points[i].x += cos(t/(100.+(double)(i+100)))*1;
        // }

        // rotation[0] = t/300.;
        // rotation[1] = t/100.;
        rotation[2] = t/300.;
        rotation[3] = -t/300.;
        // rotation[4] = t/100.;
        // rotation[5] = t/100.;

        // printf("start DrawfFrame\n");
        DrawFrame(renderer, points, n_points, lines, n_lines, rotation);
        // printf("end DrawfFrame\n");
        t ++;
    }

    // printf("esto finito pepito\n");
    return 0;
}

int main(){
    printf("initializing SDL...");
    if (init()){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
        return -1;
    }
    printf("done\n");

    printf("start\n");
    mainloop(screen, renderer);

    Quit();
    return 0;
}