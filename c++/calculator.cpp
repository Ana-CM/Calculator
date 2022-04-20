#include <iostream>
#include <vector> 
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "calculator.h"
using namespace std;

Calculator::Calculator() {
    cout << "Calculator constructor" << endl;
}

string Calculator::read_file() {

    ifstream file_stream{ "file.txt" };

    if ( file_stream.fail() ) {
        cout << "Error opening file" << endl;
        return "";
    }

    ostringstream str_stream{} ;
    file_stream >> str_stream.rdbuf();

    if (file_stream.fail() && !file_stream.eof()){
        cout << "Error reading file" << endl;
        return "";
    }

    return str_stream.str();
}

void Calculator::interpret_content() {    

    string content = read_file();
    string delimiter = ";";

    content.erase( std::remove_if( content.begin(), content.end(), ::isspace ), content.end() );

    size_t position = 0;
    string line;

    while ( ( position = content.find( delimiter ) ) != string::npos ) {
        line = content.substr( 0, position );
       
        if ( line.find( '=' ) != string::npos ) {
            string key     = line.substr( 0, line.find( '=' ) );
            int value      = interpret_line( line.substr( line.find( '=' ) + 1 ) );
            variables[key] = value;

        } else {
            print_result( line );
        }

        content.erase(0, position + delimiter.length() );
    }
}

int Calculator::interpret_line( string line ) {       

    int value = 0;

    if ( is_number( line ) ) {
        value = stoi( line );
    } else if ( ( line.find( '*' ) != string::npos ) && ( line.find( '+' ) != string::npos ) ) {
        value = only_addition( line );
    } else if ( ( line.find( '*' ) != string::npos ) && ( line.find( '+' ) == string::npos ) ) {
        value = multiplication( line );
    } else {
        value = addition( line );
    }

    return value;
}

int Calculator::only_addition( string line ) {
    int value = 0;
    string new_line, aux_line, delimiter = "+";
    size_t position = 0;

    line = line + delimiter;

    while ( ( position = line.find( delimiter ) ) != string::npos ) {

        aux_line = line.substr( 0, position );
        
        if ( aux_line.find( '*' ) != string::npos ) {
            value = multiplication( aux_line );
            new_line = new_line + to_string( value ) + delimiter;
        } else {
            new_line = new_line + aux_line + delimiter;
        }

        line.erase(0, position + delimiter.length() );
    }

    new_line = new_line.substr ( 0, new_line.length() - 1 );

    value = addition( new_line );

    return value;
}

int Calculator::multiplication( string line ) {
    int value = 1;
    string aux_line, delimiter = "*";
    size_t position = 0;

    line = line + delimiter;

    while ( ( position = line.find( delimiter ) ) != string::npos ) {

        aux_line = line.substr( 0, position );
        
        if ( is_number( aux_line ) ) {
            value = value * stoi( aux_line );
        } else {
           value = value * get_variable_value( aux_line );
        }

        line.erase(0, position + delimiter.length() );
    }

    return value;
}

int Calculator::addition( string line ) {
    int value = 0;
    string aux_line, delimiter = "+";
    size_t position = 0;

    line = line + delimiter;

    while ( ( position = line.find( delimiter ) ) != string::npos ) {

        aux_line = line.substr( 0, position );
        
        if ( is_number( aux_line ) ) {
            value = value + stoi( aux_line );
        } else {
           value = value + get_variable_value( aux_line );
        }

        line.erase(0, position + delimiter.length() );
    }

    return value;
}

void Calculator::print_result( string key ) {

    if ( is_number( key ) ) {
        cout << key << endl;
    } else {
        if ( variables.find( key ) != variables.end() ) {
            cout << key << " = " << variables[key] << endl;
        } else {
            cout << interpret_line( key ) << endl;
        }
    }
}

int Calculator::get_variable_value( string key ) {
    
    if ( variables.find( key ) != variables.end() ) {
        return variables[key];
    } else {
        cout << "Variable not found" << endl;
        return 0;
    }
}

bool Calculator::is_number( const string& line ) {
    for ( char const &c : line ) {
        if (std::isdigit(c) == 0) return false;
    }

    return true;
}
