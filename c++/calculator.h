#ifndef CALCULATOR
#define CALCULATOR

#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

class Calculator
{
    public:
        Calculator();
        ~Calculator();
        string read_file();
        void interpret_content();
        int interpret_line( string line );
        int only_addition( string line );
        int multiplication( string line );
        int addition ( string line );
        void print_result( string key );
        bool is_number( const string& line );

    private:
        map<string, int> variables;
        int get_variable_value( string key );
};

#endif