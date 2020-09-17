#include "simulated_annealing.h"
#include "test.h"


int main() 
{         
    simulated_annealing* x = new simulated_annealing(10000.0, 10.0, 0.0001, 10);
    test* t = new test(11, 16); //square 11x16
    t -> add_piece(2, 3, t -> line1x3);
    t -> add_piece(8, 3, t -> square3x3);
    t -> add_piece(3, 7, t -> line3x1);
    x -> set_input(t);    
    x -> calculate_solution(); 
}