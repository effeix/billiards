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

#ifndef VISUALIZADOR_H
#define VISUALIZADOR_H

#include "main.h"
#include "SDL2/SDL.h"
#include "body.h"
#include <vector>

/**
 * Visualizador simplificado para a disciplina de Super Computação do INSPER - 2018/2.
 *
 * Este Visualizador recebe um vector de corpos circulares com massa, raio, posição e
 * velocidade, as dimensões do campo de simulação e o passo da simulação. A cada frame
 * da simulação a função `do_iteration` é executada. Coloque o código da sua simulação
 * neste método. Você pode escolher criar uma subclasse ou simplesmente escrever seu
 * código neste método. Criar uma subclasse tem a vantagem de poder criar visualizadores
 * para os diferentes modelos de física.
 *
 */
 #include "ball.h"
#include <chrono>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::high_resolution_clock VerboseTimer;

class Visualizador
{
public:
    long iter, verbose_iter;
    double delta_t;
    int gui;
    double mu;
    double g;
    double counter;
    long int max_iter;
    Time::time_point vt_start, vt_end, start, end;
    std::chrono::duration<double> elapsed;

    Visualizador(std::vector<Ball> &bodies, int field_width, int field_height, params_t * params);

    void do_iteration();
    void run();

private:
    int field_width, field_height;
    std::vector<Ball> &bodies;
};

#endif // VISUALIZADOR_H
