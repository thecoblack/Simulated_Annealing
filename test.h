#ifndef TEST_H
#define TEST_H

#include <stdlib.h>
#include <cstdio>
#include <vector>
#include <time.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <unistd.h>

#define cost_x 1
#define cost_o 2
#define empty  '-'
#define full   'x'

using namespace std;

class test
{
    private:   

        struct piece
        {
            private:
                vector<vector<char>> char_piece;
                double piece_cost;                
                int len_x, len_y;
                int pos_x, pos_y;

            public:
                piece(int pos_x, int pos_y, vector<vector<char>> p);
                int get_len_x();
                int get_len_y();
                int get_pos_x();
                int get_pos_y();
                void set_pos_x(int new_pos);
                void set_pos_y(int net_pos);
        };

        int n_dim, m_dim;
        double piece_cost = 0.0f;        
        vector<vector<char>> base;        
        vector<test::piece*> piece_list;               

        // Test piece can be used
        bool test_dimension(char** piece);

        // Return false, if can't be inserted
        bool test_insert(int pos_x, int pos_y, piece* p);       

        void change_values(int pos_x, int pos_y, piece* p, char value);

        vector<int> get_used_area();               

    public:     

        vector<vector<char>> square3x3 = {{'x','x','x'}, 
                                          {'x','x','x'}, 
                                          {'x','x','x'}};

        vector<vector<char>> square1x1 = {{'x'}}; 
        
        vector<vector<char>> line3x1 = {{'x','x','x'}};
        
        vector<vector<char>> line1x3 = {{'x'},
                                        {'x'},
                                        {'x'}};       

        test(vector<vector<char>> base, vector<test::piece*> pl);

        // Inicialize the base
        test(int n_dim, int m_dim);

        // Generate a matrix of doubles for testing 
        // the simulated annealing
        void generate_input_base();

        void add_piece(int pos_x, int pos_y, vector<vector<char>> p);               

        void insert_piece(int pos_x, int pos_y, piece* p);        

        void remove_piece(piece* p);

        void move_piece();

        double get_cost();

        int get_n_dim();

        int get_m_dim();

        vector<test::piece*> get_piece_list();

        vector<vector<char>> get_base();

        void set_base(vector<vector<char>> i);

        void print_base();
};

#endif

