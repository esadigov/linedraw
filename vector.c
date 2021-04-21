#include "vector.h"
Vector V_new(float x, float y)
{
    Vector out = {x, y};
    return out;
}
void V_show(Vector v, char *label)
{
    printf("%s (%.2f, %.2f)\n", label, v.x, v.y);
}
Vector V_diff(Vector v1, Vector v2)
{
    return V_new(v1.x - v2.x, v1.y - v2.y);
}

Vector V_mult(Vector v, float k)
{
    return V_new(v.x * -1, v.y * -1);
}
float V_dotProduct(Vector v1, Vector v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}
float V_magnitude(Vector v)
{
    return sqrt(V_dotProduct(v, v));
}
float V_PtPtDistance(Vector A, Vector P)
{
    return V_magnitude(V_diff(A, P));
}
Vector V_unit(Vector v)
{
    float m = V_magnitude(v);
    return V_new(v.x / m, v.y / m);
}
float V_PtLineDistance(Vector A, Vector B, Vector P)
{
    Vector AP = V_diff(A, P);
    float x = V_dotProduct(V_unit(V_diff(A, B)),AP);
    return sqrt(pow(V_magnitude(AP), 2) - pow(x, 2));
}

bool V_isInRegionI(Vector P, Vector A, Vector B)
{
    return V_dotProduct(V_diff(A, P), V_diff(A, B))<=0;
}
bool V_isInRegionII(Vector P, Vector A, Vector B){
    return (V_dotProduct(V_diff(P,B),V_diff(A,B))>0)&&(V_dotProduct(V_diff(P,A),V_diff(B,A))>0);
}
bool V_isInRegionIII(Vector P, Vector A, Vector B){
    return V_dotProduct(V_diff(P,B),V_diff(A,B))<=0;
}
float V_PtSegmentDistance(Vector P, Vector A, Vector B){
    if(V_isInRegionI(P,A,B)) return V_PtPtDistance(A,P);
    else if(V_isInRegionIII(P,A,B)) return V_PtPtDistance(B,P);
    else return V_PtLineDistance(A,B,P);
}
