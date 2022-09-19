#include "draw.h"
#include "utils.h"

void DrawFrame(SDL_Renderer* renderer, Point4D* points, int n_points, int* lines[2], int n_lines, double rotation[6]){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Point p1, p2;
    // Point4D temp1, temp2;
    for (int i=0; i<n_lines; i++){
        p1 = GetProjection(points[lines[i][0]], rotation);
        p2 = GetProjection(points[lines[i][1]], rotation);
        // p1.x = WINDOW_WIDTH/2 + temp1.x + temp1.z/2. + 3*temp1.w/4.;
        // p1.y = WINDOW_HEIGHT/2 + temp1.y - temp1.z/2. - 3*temp1.w/4.;
        // p2.x = WINDOW_WIDTH/2 + temp2.x + temp2.z/2. + 3*temp2.w/4.;
        // p2.y = WINDOW_HEIGHT/2 + temp2.y - temp2.z/2. - 3*temp2.w/4.;
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH/2 + p1.x, WINDOW_HEIGHT/2 + p1.y, WINDOW_WIDTH/2 + p2.x, WINDOW_HEIGHT/2 + p2.y);
    }

    // SDL_Point dest= {points[0].x + points[0].z/2. + points[0].w/4., points[0].y - points[0].z/2. - points[0].w/4.}, prev=dest;
    // for (int i=0; i<n_points; i++){
    //     dest.x = points[i].x + points[i].z/2. + points[i].w/4.;
    //     dest.y = points[i].y - points[i].z/2. - points[i].w/4.;
    //     SDL_RenderDrawLine(renderer, dest.x, dest.y, prev.x, prev.y);
    //     prev = dest;
    // }

    SDL_RenderPresent(renderer);
}