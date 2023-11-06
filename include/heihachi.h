#ifndef __HEIHACHI_H__
#define __HEIHACHI_H__

#include "entity.h"

/**
 * @brief Create a new heihachi entity
 * @param position where to spawn the aguman at
 * @return NULL on error, or an heihachi entity pointer on success
 */
Entity *heihachi_new(Vector3D position);


#endif
