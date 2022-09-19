#include <math.h>
#include <SDL2/SDL.h>
#include "point.h"
#include "utils.h"

Point4D NewPoint4D(double x, double y, double z, double w){
    Point4D p = {x, y, z, w};
    return p;
}

Point4D RotateXY(Point4D point, double angle){
     Point4D res;

     res.x = point.x * cos(angle) +
             point.y * -sin(angle);
     res.y = point.x * sin(angle) +
             point.y * cos(angle);
     res.z = point.z;
     res.w = point.w;

     return res;
}
Point4D RotateYZ(Point4D point, double angle){
     Point4D res;

     res.x = point.x * 1;
     res.y = point.y * cos(angle) +
             point.z * -sin(angle);
     res.z = point.y * sin(angle) +
             point.z * cos(angle);
     res.w = point.w * 1;

     return res;
}
Point4D RotateXZ(Point4D point, double angle){
     Point4D res;

     res.x = point.x * cos(angle) +
             point.z * -sin(angle);
     res.y = point.y * 1;
     res.z = point.x * sin(angle) +
             point.z * cos(angle);
     res.w = point.w * 1;

     return res;
}
Point4D RotateXW(Point4D point, double angle){
     Point4D res;

     res.x = point.x * cos(angle) +
             point.w * -sin(angle);
     res.y = point.y * 1;
     res.z = point.z * 1;
     res.w = point.x * sin(angle) +
             point.w * cos(angle);

     return res;
}
Point4D RotateYW(Point4D point, double angle){
     Point4D res;

     res.x = point.x * 1;
     res.y = point.y * cos(angle) +
             point.w * -sin(angle);
     res.z = point.z * 1;
     res.w = point.y * sin(angle) + 
             point.w * cos(angle);

     return res;
}
Point4D RotateZW(Point4D point, double angle){
     Point4D res;

     res.x = point.x * 1;
     res.y = point.y * 1;
     res.z = point.z * cos(angle) + 
             point.w * -sin(angle);
     res.w = point.z * sin(angle) + 
             point.w * cos(angle);

     return res;
}

Point4D Rotate(Point4D p, double rotation[6]){
    double x1, y1, z1, x2, y2, z2, rx, ry, rz;
    x1 = p.x;
    y1 = p.y;
    z1 = p.z;
    x2 = rotation[0];
    y2 = rotation[1];
    z2 = rotation[2];

    /* https://en.wikipedia.org/wiki/Rotation_matrix */
    rx = x1 * (cos(x2) * cos(y2)) +
         y1 * (cos(x2) * sin(y2) * sin(z2) - sin(x2)*cos(z2)) +
         z1 * (cos(x2) * sin(y2) * cos(x2) + sin(x2)*sin(z2));
    ry = x1 * (sin(x2) * cos(y2)) +
         y1 * (sin(x2) * sin(y2) * sin(z2) + cos(x2)*cos(z2)) +
         z1 * (sin(x2) * sin(y2) * cos(z2) + cos(x2)*sin(z2));
    // rz = x1 * (-sin(y2)) +
    //      y1 * (sin(x2) * cos(y2)) +
    //      z1 * (cos(x2) * cos(y2));
    rz = x1 * (-sin(y2)) +
         y1 * (cos(y2) * sin(z2)) +
         z1 * (cos(y2) * cos(z2));
        
    return NewPoint4D(rx, ry, rz, p.w);
}

SDL_Point GetProjection(Point4D point, double rotation[6]){
//     printf("br : %f, %f, %f\n", point->position.x, point->position.y, point->position.z);
    Point4D p;
     // p = Rotate(point, rotation);
    p = RotateXY(point, rotation[0]);
    p = RotateYZ(p, rotation[1]);
    p = RotateXZ(p, rotation[2]);
    p = RotateXW(p, rotation[3]);
    p = RotateYW(p, rotation[4]);
    p = RotateZW(p, rotation[5]);
    // printf("ar : %f, %f, %f\n", p->position.x, p->position.y, p->position.z);
    double x, y, Z;
    x = p.x;
    y = p.y;
//     Z = Z0 / (Z0 + z);
    Z = Z0 / (Z0 + p.z + p.w);

     // SDL_Point res = {p.x + p.z/2. + 3*p.w/4., p.y + p.z/2. + 3*p.w/4.};
     SDL_Point res = {x*Z, y*Z};
    return res;
}
