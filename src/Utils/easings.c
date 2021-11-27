#include <Utils/easings.h>

double easeInBack(float x)
{
    return 2.70158 * x * x * x - 1.70158 * x * x;
}
