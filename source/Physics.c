#include"Physics.h"

bool PointBoxIntersection(Int2 point, BoxCollision2D box)
{
    if(point.x < box.position.x || point.y < box.position.y) 
        return false;

    if(point.x > box.position.x + box.size.x || point.y > box.position.y + box.size.y) 
        return false;

    return true;
}