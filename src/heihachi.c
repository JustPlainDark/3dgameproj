
#include "simple_logger.h"
#include "gfc_types.h"
#include "gfc_input.h"
#include "heihachi.h"


void heihachi_update(Entity *self);

void heihachi_think(Entity *self);

Vector3D lastP;

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
    vector3d_copy(lastP,ent->position);
    //ent->type = ENT_P2;
    //ent->state = ES_stand;
    ent->health = 100;

    Box b = gfc_box(position.x, position.y, position.z, 3, 3, 10);
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
    vector3d_copy(self->bounds, self->position);
    //vector3d_add(self->position,self->position,self->velocity);
    //self->rotation.z += 0.01;
}

void heihachi_think(Entity *self)
{
    Vector3D forward = {0};
    Vector3D right = {0};
    Vector2D w;
    Entity *other;

    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL);

    w = vector2d_from_angle(self->rotation.z);
    forward.x = w.x;
    forward.y = w.y;
    w = vector2d_from_angle(self->rotation.z - GFC_HALF_PI);
    right.x = w.x;
    right.y = w.y;

    other = entity_get_collision(self);

    if(self->type == ENT_P1)
    {
        SDL_Joystick *joystick;
        joystick = SDL_JoystickOpen(0);

        if(self->state == ES_stand)
        {
            if (keys[SDL_SCANCODE_T] || SDL_JoystickGetAxis(joystick, 1) < -32700 || SDL_JoystickGetHat(joystick, 0) == 1)
            {
                vector3d_add(self->position,self->position,forward);
            }
            if (keys[SDL_SCANCODE_G] || SDL_JoystickGetAxis(joystick, 1) > 32700 || SDL_JoystickGetHat(joystick, 0) == 4)
            {
                vector3d_add(self->position,self->position,-forward);
            }
            if (keys[SDL_SCANCODE_H] || SDL_JoystickGetAxis(joystick, 0) > 32700 || SDL_JoystickGetHat(joystick, 0) == 2)
            {
                vector3d_add(self->position,self->position,right);
            }
            if (keys[SDL_SCANCODE_F] || SDL_JoystickGetAxis(joystick, 0) < -32700 || SDL_JoystickGetHat(joystick, 0) == 8)
            {
                vector3d_add(self->position,self->position,-right);
            }

            if(self->position.x >= 12)
            {
                    self->position.x = 11;
                    slog("go back x is 12");
            }
            if(self->position.y >= 12)
            {
                    self->position.y = 11;
                    slog("go back y is 12");
            }
            if(self->position.x <= -12)
            {
                    self->position.x = -11;
                    slog("go back x is -12");
            }
            if(self->position.y <= -12)
            {
                    self->position.y = -11;
                    slog("go back y is -12");
            }
        }



        if(self->atkCooldown <= 0)
        {
            if(SDL_JoystickGetButton(joystick, 0) == 1)
            {
                    slog("Cross");
                    gf3d_model_free(self->model);
                    self->model = gf3d_model_load("models/heihachiRP.model");
                    self->state = ES_attack;
                    self->atkCooldown = 400;
                    if(other != NULL && other->type == ENT_P2 && self->state == ES_attack)
                    {
                            slog("Right Punch");
                            if(other->health < 50)
                            {
                                other->health -= other->health;
                            }
                            else other->health -= 40;
                    }
            }
            if(SDL_JoystickGetButton(joystick, 1) == 1)
            {
                    slog("Circle");
                    gf3d_model_free(self->model);
                    self->model = gf3d_model_load("models/heihachiRK.model");
                    self->state = ES_attack;
                    self->atkCooldown = 600;
                    if(other != NULL && other->type == ENT_P2 && self->state == ES_attack)
                    {
                            slog("Right Kick");
                            if(other->health < 50)
                            {
                                other->health -= other->health;
                            }
                            else other->health -= 50;
                    }
            }
            if(SDL_JoystickGetHat(joystick, 0) == 4 && SDL_JoystickGetButton(joystick, 2) == 1)
            {
                slog("Down + Triangle");
                    gf3d_model_free(self->model);
                    self->model = gf3d_model_load("models/heihachiDownLK.model");
                    self->state = ES_attack;
                    self->atkCooldown = 200;
                    if(other != NULL && other->type == ENT_P2 && self->state == ES_attack)
                    {
                            slog("Down Left Kick");
                            if(other->health < 15)
                            {
                                other->health -= other->health;
                            }
                            else other->health -= 15;
                    }
            }
            else if(SDL_JoystickGetButton(joystick, 2) == 1)
            {
                    slog("Triangle");
                    gf3d_model_free(self->model);
                    self->model = gf3d_model_load("models/heihachiLK.model");
                    self->state = ES_attack;
                    self->atkCooldown = 200;
                    if(other != NULL && other->type == ENT_P2 && self->state == ES_attack)
                    {
                            slog("Left Kick");
                            if(other->health < 15)
                            {
                                other->health -= other->health;
                            }
                            else other->health -= 15;
                    }
            }
            if(SDL_JoystickGetHat(joystick, 0) == 8 && SDL_JoystickGetButton(joystick, 3) == 1)
            {
                    slog("Left+Square");
                    gf3d_model_free(self->model);
                    self->model = gf3d_model_load("models/heihachiBackLP.model");
                    self->state = ES_attack;
                    self->atkCooldown = 100;
                    if(other != NULL && other->type == ENT_P2 && self->state == ES_attack)
                    {
                            slog("Left Punch");
                            if(other->health < 10)
                            {
                                other->health -= other->health;
                            }
                            else other->health -= 10;
                    }
            }
            else if(SDL_JoystickGetButton(joystick, 3) == 1)
            {
                    slog("Square");
                    gf3d_model_free(self->model);
                    self->model = gf3d_model_load("models/heihachiLP.model");
                    self->state = ES_attack;
                    self->atkCooldown = 100;
                    if(other != NULL && other->type == ENT_P2 && self->state == ES_attack)
                    {
                            slog("Left Punch");
                            if(other->health < 10)
                            {
                                other->health -= other->health;
                            }
                            else other->health -= 10;
                    }
            }
            if(SDL_JoystickGetHat(joystick, 0) == 8 && SDL_JoystickGetButton(joystick, 5) == 1)
            {
                slog("R1+Left");
                gf3d_model_free(self->model);
                self->model = gf3d_model_load("models/heihachiSweep.model");
                self->state = ES_attack;
                self->atkCooldown = 500;
                if(other != NULL && other->type == ENT_P2 && self->state == ES_attack)
                {
                        slog("Hammer Fall");
                        /*if(self->atkCooldown == 250)
                        {
                            gf3d_model_free(self->model);
                            self->model = gf3d_model_load("models/heihachiBusterRise.model");
                        }*/
                        if(other->health < 75)
                        {
                            other->health -= other->health;
                        }
                        else other->health -= 75;
                }
            }
            else if(SDL_JoystickGetHat(joystick, 0) == 2 && SDL_JoystickGetButton(joystick, 5) == 1)
            {
                slog("R1+Right");
                gf3d_model_free(self->model);
                self->model = gf3d_model_load("models/heihachiHeadbutt.model");
                self->state = ES_attack;
                self->atkCooldown = 500;
                if(other != NULL && other->type == ENT_P2 && self->state == ES_attack)
                {
                        slog("Garuda Impact");
                        /*if(self->atkCooldown == 250)
                        {
                            gf3d_model_free(self->model);
                            self->model = gf3d_model_load("models/heihachiBusterRise.model");
                        }*/
                        if(other->health < 75)
                        {
                            other->health -= other->health;
                        }
                        else other->health -= 75;
                }
            }
            else if(SDL_JoystickGetHat(joystick, 0) == 4 && SDL_JoystickGetButton(joystick, 5) == 1)
            {
                slog("R1+Down");
                gf3d_model_free(self->model);
                self->model = gf3d_model_load("models/heihachiUpper.model");
                self->state = ES_attack;
                self->atkCooldown = 500;
                if(other != NULL && other->type == ENT_P2 && self->state == ES_attack)
                {
                        slog("Heat Tackle");
                        /*if(self->atkCooldown == 250)
                        {
                            gf3d_model_free(self->model);
                            self->model = gf3d_model_load("models/heihachiBusterRise.model");
                        }*/
                        if(other->health < 75)
                        {
                            other->health -= other->health;
                        }
                        else other->health -= 75;
                }
            }
            else if(SDL_JoystickGetButton(joystick, 5) == 1)
            {
                    slog("R1");
                    gf3d_model_free(self->model);
                    self->model = gf3d_model_load("models/heihachiEWGF.model");
                    self->state = ES_attack;
                    self->atkCooldown = 100;
                    if(other != NULL && other->type == ENT_P2 && self->state == ES_attack)
                    {
                            slog("Forward Right Kick");
                            if(other->health < 50)
                            {
                                other->health -= other->health;
                            }
                    }
            }
        }
        else if(self->atkCooldown == 75)
        {
            gf3d_model_free(self->model);
            self->model = gf3d_model_load("models/heihachi.model");
            self->state = ES_attack;
            self->atkCooldown--;
        }
        else
        {
            self->atkCooldown--;
            self->state = ES_stand;
        }
    }

    if(self->health <= 0)
    {
        entity_free(self);
    }

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
