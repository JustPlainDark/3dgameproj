#ifndef __POTEMKIN_H__
#define __POTEMKIN_H__

#include "entity.h"

/**
 * @brief Create a new potemkin entity
 * @param position where to spawn the aguman at
 * @return NULL on error, or an potemkin entity pointer on success
 */
Entity *potemkin_new(Vector3D position);


#endif
