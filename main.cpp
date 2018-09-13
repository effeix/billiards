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

#include <iostream>
#include <string>
#include <vector>

#include "ball.h"
#include "main.h"
#include "visualizador.h"


void read_file(std::vector<Ball> &v, params_t * params) {
    std::cin
    >> params->w
    >> params->h
    >> params->n
    >> params->mu
    >> params->alpha_wall
    >> params->alpha_ball;

    long int id;
    double r, m, x, y, vx, vy;

    for(unsigned int i = 0; i < params->n; i++) {
        std::cin >> id >> r >> m >> x >> y >> vx >> vy;

        v.push_back(
            Ball(id, r, m, x, y, vx, vy)
        );
    }
}

void get_env(params_t * params) {
    const char * ENV_delta_t = std::getenv("DELTA_T");
    const char * ENV_gui = std::getenv("GUI");
    const char * ENV_max_iter = std::getenv("MAX_ITER");

    if(ENV_delta_t == NULL) {
        params->delta_t = 0.01;
    }
    else {
        params->delta_t = std::stof(ENV_delta_t);
    }

    if(ENV_max_iter == NULL) {
        params->max_iter = 10;
    }
    else {
        params->max_iter = std::stol(ENV_max_iter);
    }

    params->gui = std::stoi(ENV_gui);
}

int main(int argc, char ** argv) {

    std::vector<Ball> balls;
    params_t * params = new params_t;

    params->g = 9.81;

    read_file(balls, params);
    get_env(params);

    Visualizador v(balls, params->w, params->h, params);

    v.run();

    return 0;
}
