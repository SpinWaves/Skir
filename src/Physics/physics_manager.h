#ifndef __PHYSICS_MANAGER__
#define __PHYSICS_MANAGER__

typedef struct
{
    int x;
    int y;
    int w;
    int h;
} BoxCollider;

BoxCollider* newBoxCollider(int x, int y, int w, int h);
void freeBoxCollider(BoxCollider* boxCollider);

#endif // __PHYSICS_MANAGER__
