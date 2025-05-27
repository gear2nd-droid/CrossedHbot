// CoreXY kinematics stepper pulse time generation
//
// Copyright (C) 2018-2019  Kevin O'Connor <kevin@koconnor.net>
//
// This file may be distributed under the terms of the GNU GPLv3 license.

#include <stdlib.h> // malloc
#include <string.h> // memset
#include "compiler.h" // __visible
#include "itersolve.h" // struct stepper_kinematics
#include "trapq.h" // move_get_coord

static double
crossed_hbot_stepper_a_calc_position(struct stepper_kinematics *sk, struct move *m
                                  , double move_time)
{
    struct coord c = move_get_coord(m, move_time);
    return c.x+c.y-c.z;
}

static double
crossed_hbot_stepper_b_calc_position(struct stepper_kinematics *sk, struct move *m
                                   , double move_time)
{
    struct coord c = move_get_coord(m, move_time);
    return c.x-c.y+c.z;
}

static double
crossed_hbot_stepper_c_calc_position(struct stepper_kinematics *sk, struct move *m
                                   , double move_time)
{
    struct coord c = move_get_coord(m, move_time);
    return -c.x-c.y-c.z;
}

static double
crossed_hbot_stepper_d_calc_position(struct stepper_kinematics *sk, struct move *m
                                   , double move_time)
{
    struct coord c = move_get_coord(m, move_time);
    return -c.x+c.y+c.z;
}

struct stepper_kinematics * __visible
crossed_hbot_stepper_alloc(char type)
{
    struct stepper_kinematics *sk = malloc(sizeof(*sk));
    memset(sk, 0, sizeof(*sk));
    if (type == 'a')
        sk->calc_position_cb = crossed_hbot_stepper_a_calc_position;
    else if (type == 'b')
        sk->calc_position_cb = crossed_hbot_stepper_b_calc_position;
    else if (type == 'c')
        sk->calc_position_cb = crossed_hbot_stepper_c_calc_position;
    else if (type == 'd')
        sk->calc_position_cb = crossed_hbot_stepper_d_calc_position;
    sk->active_flags = AF_X | AF_Y | AF_Z;
    return sk;
}
