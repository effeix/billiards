#ifndef __MAIN_H__
#define __MAIN_H__

typedef struct _params_t {
	double alpha_wall;
	double alpha_ball;
	double mu;
	double g;
	double delta_t;
	long int h;
	long int w;
	long int n;
	long int max_iter;
	int gui;
} params_t;

#endif/*__MAIN_H__*/
