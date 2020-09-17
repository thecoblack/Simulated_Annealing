#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include "test.h"
#include <math.h> 
#include <vector>
#include <unistd.h>

class simulated_annealing
{                   
    public:
        struct F
        {
            private:
                double cost;
                test*  conf;
            public:
                F(test* c)
                {
                    conf = c;
                    cost = c -> get_cost();                    
                }
                double get_cost() { return cost; }
                test*  get_conf() { return conf; }                               
        };

        simulated_annealing(double starting_temp, double final_temp,
                                double temp_k, int num_iter);

        void set_input(test* i);        

        void calculate_solution();

        F* generate_solution();

        bool test_solution(F* new_sol);

        void print(); 

     private:
        double current_temp, final_temp, temp_k;
        F* input = NULL;
        int num_iter, k;                
};

#endif