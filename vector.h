#ifndef BLAH
#define BLAH
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
struct vector
{
    float x, y;
};
typedef struct vector Vector;

Vector V_new(float x, float y);
void V_show(Vector v, char *label);
Vector V_diff(Vector v1, Vector v2);
Vector V_mult(Vector v, float k);
float V_dotProduct(Vector v1, Vector v2);
float V_magnitude(Vector v);
float V_PtPtDistance(Vector A, Vector P);
Vector V_unit(Vector v);
float V_PtLineDistance(Vector A, Vector B, Vector P);
bool V_isInRegionII(Vector P, Vector A, Vector B);
bool V_isInRegionIII(Vector P, Vector A, Vector B);
float V_PtSegmentDistance(Vector P, Vector A, Vector B);
#endif
