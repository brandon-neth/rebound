/**
 * Bouncing balls at corner.
 *
 * This example tests collision detection methods across box boundaries.
 * There are four particles, one in each corner. To see the ghost boxes in OpenGL
 * press `g` while the simulation is running.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "rebound.h"

extern double coefficient_of_restitution; 
int main(int argc, char* argv[]){
	struct reb_simulation* r = reb_create_simulation();
	// Setup constants
	r->integrator	= REB_INTEGRATOR_LEAPFROG;
	r->gravity	= REB_GRAVITY_BASIC;
	r->collision	= REB_COLLISION_TREE;
    r->collision_resolve = reb_collision_resolve_hardsphere;
	r->dt 		= 1e-3;
	r->boundary	= REB_BOUNDARY_PERIODIC;
	r->usleep	= 1000;			// Slow down integration (for visualization only)
	reb_configure_box(r,3.,1,1,1);
	
	// Initial conditions
	int problem_id = 1;
	if (argc>1){			
		problem_id = atoi(argv[1]);
	}
	struct reb_particle p = {0};

	switch (problem_id){
		case 1: // Multiple instantaneous collisions across boundaries
			r->nghostx = 1; r->nghosty = 1; r->nghostz = 0;
			p.x  = 1; p.y  = 1; p.z  = 0;
			p.m  = 1;
			p.r  = 0.1;
			reb_add(r,p);
			p.x  = -1; p.y  = -1; p.z  = 0;
			p.m  = 1;
			p.r  = 0.1;
			reb_add(r,p);
			p.x  = 1; p.y  = -1; p.z  = 0;
			p.m  = 1;
			p.r  = 0.1;
			reb_add(r,p);
			p.x  = -1; p.y  = 1; p.z  = 0;
			p.m  = 1;
			p.r  = 0.1;
			reb_add(r,p);
			break;
		case 2: // Multiple instantaneous collisions with different sizes
			r->nghostx = 0; r->nghosty = 0; r->nghostz = 0;
			p.x  = 0; p.y  = 0; p.z  = 0;
			p.m  = 1;
			p.r  = 0.5;
			reb_add(r,p);
			p.x  = 1; p.y  = 1; p.z  = 0;
			p.m  = 0.008;
			p.r  = 0.1;
			reb_add(r,p);
			p.x  = -1; p.y  = -1; p.z  = 0;
			p.m  = 0.008;
			p.r  = 0.1;
			reb_add(r,p);
			p.x  = 1; p.y  = -1; p.z  = 0;
			p.m  = 0.008;
			p.r  = 0.3;
			reb_add(r,p);
			p.x  = -1; p.y  = 1; p.z  = 0;
			p.m  = 0.008;
			p.r  = 0.2;
			reb_add(r,p);
			p.x  = 0;  p.y  = 0; p.z  = 1.3;
			p.m  = 0.008;
			p.r  = 0.1;
			reb_add(r,p);
			p.x  = 0;  p.y  = 0; p.z  =-1.3;
			p.m  = 0.008;
			p.r  = 0.05;
			reb_add(r,p);
			break;
	}

	reb_integrate(r,INFINITY);
}

