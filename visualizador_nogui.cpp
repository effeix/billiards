/*
 * Copyright (c) 2018 Igor Montagner igordsm@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "visualizador_nogui.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"

#include "main.h"

#include <omp.h>
#include <stdio.h>

#include <chrono>
#include <cstdlib>
#include <iostream>


#define MAX_ITER 10

Visualizador::Visualizador(std::vector<Ball> &bodies, int field_width, int field_height, params_t * params) :
    delta_t(params->delta_t),
    field_width(field_width),
    field_height(field_height),
    bodies(bodies) {
    
    gui = params->gui;
    mu = params->mu;
    g = params->g;
    max_iter = params->max_iter;

    iter = 0;
}

void Visualizador::run() {
    long int i = 0;    

    start = Time::now();
    
    while(i < max_iter) {
        do_iteration();
        i++;
    }
    
    elapsed = std::chrono::duration_cast<std::chrono::duration<double>> (Time::now()-start);
    std::cout << elapsed.count() << std::endl;
}

void Visualizador::do_iteration() {
    long int id0, id1;

    /*
    For each ball, compute position in t+1
    */
    double * new_pos_x = new double[bodies.size()];
    double * new_pos_y = new double[bodies.size()];

    #pragma omp parallel for
    for(unsigned int i = 0; i < bodies.size(); i++) {
        new_pos_x[i] = bodies[i].get_next_position(delta_t).first;
        new_pos_y[i] = bodies[i].get_next_position(delta_t).second;
    }

    /*
    If ball is going to collide with the table in t+1,
    compute new velocity vector for the ball and do not
    update position yet. In this case, the computation
    is an inversion of the axis hit by the ball.
    */
    #pragma omp parallel for
    for(unsigned int j = 0; j < bodies.size(); j++) {
        int will_collide_wall = bodies[j].collision_with_wall(
            field_width, field_height, new_pos_x[j], new_pos_y[j]
        );

        switch(will_collide_wall) {
            case 1:
                bodies[j].invert_vx();
                break;
            case 2:
                bodies[j].invert_vy();
                break;
            case 3:
                bodies[j].invert_vx();
                bodies[j].invert_vy();
                break;
            default:
                break;
        }
    }

    /*
    If ball is going to collide with another ball in t+1,
    compute the new velocity vector based on the model
    described in the article tha was submitted along with
    the code. The position of the is going to be update only
    when not colliding in t+1.
    */
    #pragma omp parallel for collapse(2)
    for(unsigned int j = 0; j < bodies.size(); j++) {
        for(unsigned int k = 0; k < bodies.size(); k++) {
            if(j != k) {

                bool will_collide_ball = bodies[j].collision_with_ball(
                    new_pos_x[j], new_pos_y[j], new_pos_x[k], new_pos_y[k], bodies[k].r
                );

                if(will_collide_ball) {
                    if(j > k) {
                        id0 = k;
                        id1 = j;
                    }
                    else {
                        id0 = j;
                        id1 = k;
                    }

                   std::cout
                   << "CHOQUE " << id0 << " " << id1
                   << " " << iter
                   << std::endl;

                    bodies[j].compute_new_velocity_vector(bodies[k]);
                }
                else {
                    bodies[j].update_position(delta_t, new_pos_x[j], new_pos_y[j]);
                }
            }
        }
    }

    #pragma omp parallel for
    for(unsigned int i = 0; i < bodies.size(); i++) {
        bodies[i].update_velocity(delta_t, g, mu);
    }

    if(gui == 0) {
        for(unsigned int l = 0; l < bodies.size(); l++) {
            std::cout
            << "Ball " << bodies[l].id << " " << bodies[l].r << " " << bodies[l].m
            << " " << bodies[l].x << " " << bodies[l].y
            << " " << bodies[l].vx << " " << bodies[l].vy
            << std::endl;
        }
    }

    iter++;
}
