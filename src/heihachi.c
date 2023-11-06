
#include "simple_logger.h"
#include "heihachi.h"


void heihachi_update(Entity *self);

void heihachi_think(Entity *self);

Entity *heihachi_new(Vector3D position)
{
    Entity *ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no heihachi for you!");
        return NULL;
    }
    ent->selectedColor = gfc_color(0,0,0,1);
    ent->color = gfc_color(1,1,1,1);
    ent->model = gf3d_model_load("models/heihachi.model");
    ent->think = heihachi_think;
    ent->update = heihachi_update;
    vector3d_copy(ent->position,position);
    ent->type = ENT_P2;

    Box b = gfc_box(position.x, position.y, position.z, 1, 1, 2);
    ent->bounds = b;

    return ent;
}

void heihachi_update(Entity *self)
{
    if (!self)
    {
        slog("self pointer not provided");
        return;
    }
    //vector3d_add(self->position,self->position,self->velocity);
    //self->rotation.z += 0.01;
}

void heihachi_think(Entity *self)
{
    if (!self)return;
    switch(self->state)
    {
        case ES_stand:
            //stand
            break;
        case ES_stBlock:
            // stand block
            break;
        case ES_ch:
            // crouch
            break;
        case ES_chBlock:
            // crouch block
            break;
        case ES_attack:
            //attack frame
            break;
        case ES_knockd:
            //knocked down
            break;
    }
}

/*eol@eof*/
