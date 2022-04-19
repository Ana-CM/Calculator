<?php 

class Calculator {

    public $variables = array();

    public function __construct() {
        echo "Calculator is created \n";
        $this->interpret_content();
    }

    public function read_file() {
        $file = fopen("file.txt", "r") or die("Unable to open file!");
        $content = fread($file, filesize("file.txt"));
        fclose($file);

        return $content;
    }

    public function interpret_content() {
        $content = $this->read_file();
        $content = preg_replace('/\s/','', $content);
        $content = explode(";", $content);

        foreach ( $content as $line ) {
            
            if ( strpos( $line, '=' ) ) {
                $line  = explode( '=', $line );
                $value = $this->interpret_line( $line[1] );

                $this->variables[ strtolower( $line[0] ) ] = $value;

            } else {
                $this->print( $line );
            }
        }
    }

    public function interpret_line( $line ) {       
        if ( is_numeric( $line ) ) {
            return $line;
        }

        if ( strpos( $line, '*' )  && strpos( $line, '+' ) ) {
            $value = $this->only_addition( $line );
            return $value;
        }

        if ( strpos( $line, '*' ) ) {
            $value = $this->multiplication( $line );
            return $value;
        }

        $value = $this->addition( $line );
        return $value;
    }

    public function only_addition( $line ) {
        $line     = explode( '+', $line );
        $new_line = '';

        foreach ( $line as $item ) {
            
            if ( strpos( $item, '*' ) ) {
                $value = $this->multiplication( $item );
                $new_line .= $value . '+';
            } else {
                $new_line .= $item . '+';
            }
        }

        $new_line = substr( $new_line, 0, -1 );
        $value = $this->addition( $new_line );

        return $value;
    }

    public function multiplication( $line ) {
        $line = explode( '*', $line );
        $value = 1;

        foreach ( $line as $item ) {
            if( is_numeric( $item ) ) {
                $value *= $item;
            } else {
                $value *= $this->get_variable( $item );
            }
        }

        return $value; 
    }

    public function addition( $line ) {
        $line  = explode( '+', $line );
        $value = 0;

        foreach ( $line as $item ) {
            if ( is_numeric( $item ) ) {
                $value += $item;
            } else {
                $value += $this->get_variable( $item );
            }
        }

        return $value;
    }

    public function print( $value ) {

        if ( empty( $value ) ) {
            return;
        }

        if ( is_numeric( $value ) ) {
            echo $value;
        } else {
            if ( array_key_exists( strtolower( $value ), $this->variables ) ) {
                echo $this->variables[ strtolower( $value ) ];
            } else {
                echo $this->interpret_line( $value );
            }
        }
        echo "\n";
    }

    public function get_variable( $key ) {
        if ( array_key_exists( strtolower( $key ), $this->variables ) ) {
            return $this->variables[ strtolower( $key ) ];
        } else {
            die( "Variable " . $key . " is not defined" );
        }
    }
}

new Calculator();
;?>