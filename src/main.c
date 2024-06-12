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

    int n_points;// = 16;
    Point4D* points;// = (Point4D*)calloc(n_points, sizeof(Point4D));

    int n_lines;// = 32;
    int **lines;// = (int**)calloc(n_lines, sizeof(int*));

    load_wireframe_model("models/tesseract.wire", &points, &lines, &n_points, &n_lines);

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
        rotation[2] = t/100.;
        rotation[3] = -t/100.;
        rotation[4] = t/300.;
        // rotation[5] = t/300.;

        // printf("start DrawfFrame\n");
        DrawFrame(renderer, points, n_points, lines, n_lines, rotation);
        // printf("end DrawfFrame\n");
        t ++;

        tick(60);
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