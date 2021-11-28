#include <Physics/physics_manager.h>
#include <Kernel/Memory/memory.h>

BoxCollider* newBoxCollider(int x, int y, int w, int h)
{
    BoxCollider* box = custom_malloc(sizeof(BoxCollider));
    box->x = x;
    box->y = y;
    box->w = w;
    box->h = h;
    return box;
}
inline void freeBoxCollider(BoxCollider* boxCollider)
{
    custom_free(boxCollider);
}
