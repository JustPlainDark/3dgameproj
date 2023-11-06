
#include "simple_logger.h"
#include "gfc_types.h"
#include "gfc_input.h"
#include "agumon.h"


void agumon_update(Entity *self);

void agumon_think(Entity *self);

Entity *agumon_new(Vector3D position)
{
    Entity *ent = NULL;
    
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no agumon for you!");
        return NULL;
    }
    ent->selectedColor = gfc_color(0,0,0,1);
    ent->color = gfc_color(1,1,1,1);
    ent->model = gf3d_model_load("models/kiryu.model");
    ent->think = agumon_think;
    ent->update = agumon_update;
    vector3d_copy(ent->position,position);

    Box b = gfc_box(position.x, position.y, position.z, 1, 1, 2);
    ent->bounds = b;

    return ent;
}

void agumon_update(Entity *self)
{
    if (!self)
    {
        slog("self pointer not provided");
        return;
    }
    //vector3d_add(self->position,self->position,self->velocity);
    //self->rotation.z += 0.01;
}

void agumon_think(Entity *self)
{
    Vector3D forward = {0};
    Vector3D right = {0};
    Vector2D w;
    Entity *other;

    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL);

    SDL_Joystick *joystick;
    joystick = SDL_JoystickOpen(0);

    w = vector2d_from_angle(self->rotation.z);
    forward.x = w.x;
    forward.y = w.y;
    w = vector2d_from_angle(self->rotation.z - GFC_HALF_PI);
    right.x = w.x;
    right.y = w.y;

    other = entity_get_collision(self);

    if(other != NULL && other->type != ENT_P2)
    {
            slog("Collision between players occured");
    }

    if (!self)return;

    if (keys[SDL_SCANCODE_T])
    {
        vector3d_add(self->position,self->position,forward);
    }
    if (keys[SDL_SCANCODE_G])
    {
        vector3d_add(self->position,self->position,-forward);
    }
    if (keys[SDL_SCANCODE_H])
    {
        vector3d_add(self->position,self->position,right);
    }
    if (keys[SDL_SCANCODE_F])
    {
        vector3d_add(self->position,self->position,-right);
    }
    if(self->atkCooldown <= 0)
    {
        if(SDL_JoystickGetButton(joystick, 0) == 1)
        {
                slog("Cross");
                gf3d_model_free(self->model);
                self->model = gf3d_model_load("models/kiryuRP.model");
                self->atkCooldown = 100;
        }
        if(SDL_JoystickGetButton(joystick, 1) == 1)
        {
                slog("Circle");
                gf3d_model_free(self->model);
                self->model = gf3d_model_load("models/kiryuRK.model");
                self->atkCooldown = 100;
        }
        if(SDL_JoystickGetButton(joystick, 2) == 1)
        {
                slog("Triangle");
                gf3d_model_free(self->model);
                self->model = gf3d_model_load("models/kiryuLK.model");
                self->atkCooldown = 100;
        }
        if(SDL_JoystickGetButton(joystick, 3) == 1)
        {
                slog("Square");
                gf3d_model_free(self->model);
                self->model = gf3d_model_load("models/kiryuLP.model");
                self->atkCooldown = 100;
        }
        if(SDL_JoystickGetButton(joystick, 5) == 1)
        {
                slog("R1");
                gf3d_model_free(self->model);
                self->model = gf3d_model_load("models/kiryuForRK.model");
                self->atkCooldown = 100;
        }
    }
    else if(self->atkCooldown == 50)
    {
        gf3d_model_free(self->model);
        self->model = gf3d_model_load("models/kiryu.model");
        self->atkCooldown--;
    }
    else
    {
        self->atkCooldown--;
    }
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
