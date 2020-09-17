#include "test.h"

test::piece::piece(int pos_x, int pos_y, vector<vector<char>> p)
{
    piece::char_piece = p;
    piece::len_x = (int) p[0].size()/2; 
    piece::len_y = (int) p.size()/2;
          
}

int test::piece::get_len_x() { return piece::len_x; }

int test::piece::get_len_y() { return piece::len_y; }

int test::piece::get_pos_x() { return piece::pos_x; }

int test::piece::get_pos_y() { return piece::pos_y; }

void test::piece::set_pos_x(int new_pos) { piece::pos_x = new_pos; }

void test::piece::set_pos_y(int new_pos) { piece::pos_y = new_pos; }

test::test(vector<vector<char>> new_base, vector<test::piece*> pl) 
{ 
    base = new_base; 
    piece_list = pl;
}

test::test(int n_dim, int m_dim)
{
    this -> n_dim = n_dim;
    this -> m_dim = m_dim;
    vector<vector<char>> aux(n_dim, vector<char>(m_dim));
    base = aux;
    generate_input_base();
}

int test::get_n_dim() { return base.size(); }

int test::get_m_dim() { return base[0].size(); }

vector<test::piece*> test::get_piece_list() { return piece_list; } 

vector<vector<char>> test::get_base() { return base; }

void test::set_base(vector<vector<char>> i) { base = i; } 

void test::generate_input_base()
{    
    for (int i = 0; i < n_dim; i++)
    {        
        for (int j = 0; j < m_dim; j++)
        {
            base[i][j] = empty;      
        }
    }    
}

void test::add_piece(int pos_x, int pos_y, vector<vector<char>> p)
{
    piece* new_piece = new piece(pos_x, pos_y, p);    
    piece_list.insert(piece_list.end(), new_piece);
    insert_piece(pos_x, pos_y, new_piece);      
}

void test::move_piece() 
{
    int rand_piece, piece_pos_x, piece_pos_y;    
    do
    {        
        srand(time(NULL));
        rand_piece = rand() % piece_list.size();
        piece_pos_x = rand() % (get_n_dim() - piece_list[rand_piece] -> get_len_y());
        piece_pos_y = rand() % (get_m_dim() - piece_list[rand_piece] -> get_len_x());
        usleep(1000);                 
    } 
    while (!test_insert(piece_pos_x, piece_pos_y, piece_list[rand_piece]));     
    remove_piece(piece_list[rand_piece]);       
    insert_piece(piece_pos_x, piece_pos_y, piece_list[rand_piece]);        
}

void test::remove_piece(piece* p) 
{           
    change_values(p -> get_pos_x(), p -> get_pos_y(), p, empty);        
}

void test::insert_piece(int pos_x, int pos_y, piece* p)
{  
    change_values(pos_x, pos_y, p, full);
    p -> set_pos_x(pos_x);
    p -> set_pos_y(pos_y);
    piece_cost += ((p -> get_len_x() * 2 
                        + p -> get_len_y() * 2)) * cost_x;            
}

void test::change_values(int pos_x, int pos_y, piece* p, char value)
{        
    for (int i = 0; i <= p -> get_len_x(); i++)
    {                           
        base[pos_x][pos_y+i] = value;
        base[pos_x][pos_y-i] = value;
        for (int j = 1; j <= p -> get_len_y(); j++)
        {            
            base[pos_x + j][pos_y + i] = value;
            base[pos_x + j][pos_y - i] = value;
            base[pos_x - j][pos_y + i] = value;
            base[pos_x - j][pos_y - i] = value;    
        }            
    }     
}

bool test::test_insert(int pos_x, int pos_y, test::piece* p)
{
    bool res = false;
    if (pos_y - p->get_len_x() >= 0 && pos_x - p->get_len_y() >= 0)
    {
        for (int i = 0; i <= p -> get_len_x(); i++)
        {
            res = base[pos_x][pos_y+i] == empty;
            res &= base[pos_x][pos_y-i] == empty;
            for (int j = 1; j <= p -> get_len_y(); j++)
            {            
                res &= base[pos_x + j][pos_y + i] == empty;
                res &= base[pos_x + j][pos_y - i] == empty;
                res &= base[pos_x - j][pos_y + i] == empty;
                res &= base[pos_x - j][pos_y - i] == empty;    
            }
        }    
    }
    return res;   
}

double test::get_cost()
{    
    double final_cost = 0.0f;    
    vector<int> used_area = get_used_area();    
    final_cost = (used_area[0] * used_area[1]) * cost_o;
    return final_cost - piece_cost;
}

vector<int> test::get_used_area()
{
    int max_x, max_y, aux_y, aux_x;
    for (int i = 0; i < piece_list.size(); i++)
    {
        aux_y = piece_list[i] -> get_pos_x() 
                    + piece_list[i] -> get_len_x();
        aux_x = piece_list[i] -> get_pos_y() 
                    + piece_list[i] -> get_len_y();
        if (aux_x > max_x) max_x = aux_x;
        if (aux_y > max_y) max_y = aux_y;
    }
    vector<int> res = {max_x, max_y};
    return res;
}

void test::print_base()
{
    cout << "\n";    
    cout << "   ";
    for (int i = 0; i < base[0].size(); i++)
    {
        cout << setw(3) << i;
    }
    cout << "\n";

    for (int i = 0; i < base.size(); i++)
    {
        cout << setw(3) << i;
        for (int j = 0; j < base[i].size(); j++)
        {
            cout << setw(3) << base[i][j];                              
        }                 
        cout << "\n";
    }
    cout << "\n";     
}