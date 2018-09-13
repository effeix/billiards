#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>

#include "ball.h"
#include "geometry.h"

Ball::Ball(long int id, double r, double m, double x, double y, double vx, double vy) :
	id(id), r(r), m(m), x(x), y(y), vx(vx), vy(vy) {}

bool Ball::collision_with_ball(double x, double y, double other_x, double other_y, double other_r) {
	// Minimimum distance for collision between balls 1 and 2 = Radius1 + Radius2
	double d = distance(x, y, other_x, other_y);
	return d <= r + other_r;
}

int Ball::collision_with_wall(double x_max, double y_max, double x, double y)
{
    int which = 0;

    if(x - r <= 0 || x + r >= x_max) {
        which += 1;
    }

    if(y - r <= 0 || y + r >= y_max) {
        which += 2;
    }

	return which;
}

double Ball::velocity()
{
	return std::sqrt(vx*vx + vy*vy);
}

std::pair<double, double> Ball::get_next_position(double delta_t)
{
	return std::make_pair(x + delta_t*vx, y + delta_t*vy);
}

void Ball::update_position(double delta_t, double new_x, double new_y) {
    // Apply equation: p(t+1) = p(t) + Dt*v
    x = new_x;
    y = new_y;
}

void Ball::update_velocity(double delta_t, double g, double mu) {

    // Decompose acceleration vector in X and Y
    double cos = vx / velocity();
    double sin = vy / velocity();
	double acc = g * mu * m;
	double accx = acc * cos;
	double accy = acc * sin;

	// Apply equation: v(t+1) = v(t) + Dt*a
	vx = vx - delta_t * accx;
	vy = vy - delta_t * accy;
}

void Ball::invert_vx() {
    vx *= -1;
}

void Ball::invert_vy() {
    vy *= -1;
}

void Ball::compute_new_velocity_vector(Ball u) {
    // Projection of vector V in vector U
    double proj_v_u = (vx*(u.x - x) + vy*(u.y - y)) / ((u.x - x)*(u.x - x) + (u.y - y)*(u.y - y));

    // Direction of the projection vector
    double coordx = u.x - x;
    double coordy = u.y - y;

    // Projection vector
    double proj_x = coordx * proj_v_u;
    double proj_y = coordy * proj_v_u;

    // Third vector, closing the triangle
    double wx = vx - proj_x;
    double wy = vy - proj_y;

    // Update velocity vector with
    vx = -proj_x + wx;
    vy = -proj_y + wy;
}

void Ball::print() {
    std::cout
    <<"Ball " << id << ":"
    << " R(" << r << ")" << " M(" << m << ")"
    << " Pos(" << x << ", " << y << ")"
    << " Vel(" << vx << ", " << vy << ")"
    << std::endl;
}
