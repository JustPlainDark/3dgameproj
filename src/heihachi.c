
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
    ent->state = ES_stand;
    ent->health = 100;

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
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL);

    //SDL_Joystick *joystick;
    //joystick = SDL_JoystickOpen(0);
    if(self->atkCooldown <= 0)
    {
        if (keys[SDL_SCANCODE_N])
        {
            gf3d_model_free(self->model);
            self->model = gf3d_model_load("models/heihachiRP.model");
            self->atkCooldown = 100;
        }
        if (keys[SDL_SCANCODE_J])
        {
            gf3d_model_free(self->model);
            self->model = gf3d_model_load("models/heihachiLP.model");
            self->atkCooldown = 100;
        }
        if (keys[SDL_SCANCODE_I])
        {
            gf3d_model_free(self->model);
            self->model = gf3d_model_load("models/heihachiLK.model");
            self->atkCooldown = 100;
        }
        if (keys[SDL_SCANCODE_O])
        {
            gf3d_model_free(self->model);
            self->model = gf3d_model_load("models/heihachiRK.model");
            self->atkCooldown = 100;
        }
        if (keys[SDL_SCANCODE_P])
        {
            gf3d_model_free(self->model);
            self->model = gf3d_model_load("models/heihachiBackLP.model");
            self->atkCooldown = 100;
        }
    }
    else if(self->atkCooldown == 50)
    {
        gf3d_model_free(self->model);
        self->model = gf3d_model_load("models/heihachi.model");
        self->atkCooldown--;
    }
    else
    {
        self->atkCooldown--;
    }

    /*
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
    */

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
