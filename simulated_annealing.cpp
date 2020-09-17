#include "simulated_annealing.h"

simulated_annealing::
simulated_annealing(double starting_t, double final_t,
                        double t_k, int n_iter)
{
    current_temp = starting_t;
    final_temp = final_t;
    temp_k = t_k;
    num_iter = n_iter;
    k = 0;    
}

void simulated_annealing::set_input(test* i) 
{
    input = new F(i);    
}

void simulated_annealing::calculate_solution()
{    
    input -> get_conf() -> print_base();    
    while(current_temp >= final_temp)
    {
        for (int m = 0; m < num_iter; m++)
        {            
            F* new_sol = generate_solution();                       
            if (test_solution(new_sol)) 
            {
                input = new_sol;
                print();                   
            }                  
        }         
        current_temp *= temp_k;
        k++;
    }       
}

simulated_annealing::F* simulated_annealing::generate_solution()
{      
    test* new_test = new test(input -> get_conf() -> get_base(), 
                                input -> get_conf() -> get_piece_list());           
    new_test -> move_piece();    
    return new F(new_test); 
}

bool simulated_annealing::test_solution(simulated_annealing::F* new_sol)
{
    double current_cost = input-> get_cost(), new_cost = input -> get_cost();
    double sub_cost = new_cost - current_cost;
    double rand_num = rand() % 2;    
    
    if (sub_cost <= 0) return true; 
    else 
    {
        double p = exp(-sub_cost/current_temp);
        if (rand_num < p) return true;
        return false;
    }
}

void simulated_annealing::print()
{
    system("clear");
    cout << "Current cost: " << input -> get_cost() << "  Current temp: " << current_temp << "\n";
    input -> get_conf() -> print_base();
}