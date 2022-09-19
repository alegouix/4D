typedef struct{
    double x,y,z,w;
} Point4D;

Point4D NewPoint4D(double x, double y, double z, double w);
SDL_Point GetProjection(Point4D point, double rotation[6]);

Point4D RotateXY(Point4D point, double angle);
Point4D RotateYZ(Point4D point, double angle);
Point4D RotateXZ(Point4D point, double angle);
Point4D RotateXW(Point4D point, double angle);
Point4D RotateYW(Point4D point, double angle);
Point4D RotateZW(Point4D point, double angle);
