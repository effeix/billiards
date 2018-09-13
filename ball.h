#ifndef __BALL_H__
#define __BALL_H__

class Ball {
public:
    long int id;
	double r;   // m
	double m;   // kg
	double x;   // m/s
	double y;   // m/s
	double vx;  // m
	double vy;  // m

	Ball(long int id, double r, double m, double x, double y, double vx, double vy);
	bool collision_with_ball(double x, double y, double other_x, double other_y, double r);
	int collision_with_wall(double x_max, double y_max, double x, double y);
	void invert_vx();
	void invert_vy();
	void compute_new_velocity_vector(Ball b);
	double velocity();
	void update_position(double delta_t, double new_x, double new_y);
	void update_velocity(double delta_t, double g, double mu);
	std::pair<double, double> get_next_position(double delta_t);
	void print();
};

#endif/*__BALL_H__*/
