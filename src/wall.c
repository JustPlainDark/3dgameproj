#include "simple_logger.h"
#include "wall.h"


void wall_update(Entity *self);

void wall_think(Entity *self);

Entity *wall_new(Vector3D position)
{
    Entity *ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no wall for you!");
        return NULL;
    }
    ent->selectedColor = gfc_color(0.1,1,0.1,1);
    ent->color = gfc_color(1,1,1,1);
    ent->model = gf3d_model_load("models/wall.model");
    ent->think = wall_think;
    ent->update = wall_update;
    ent->type = ENT_WALL;
    ent->scale = vector3d(2,2,2);
    vector3d_copy(ent->position,position);

    return ent;
}

void wall_update(Entity *self)
{
    if (!self)
    {
        slog("self pointer not provided");
        return;
    }
    //vector3d_add(self->position,self->position,self->velocity);
    //self->rotation.z += 0.01;
}

void wall_think(Entity *self)
{
    if (!self)return;

}

/*eol@eof*/
