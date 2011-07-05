#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"

char *colors[] = { 
    "black"  ,
    "red"    ,
    "green"  ,
    "yellow" ,
    "blue"   ,
    "magenta",
    "cyan"   ,
    "white"  
};

void list_colors( void ) {
    unsigned int bg, fg, bd;
    
    for( bg = 0; bg < 8; bg++ ) {
        for( bd=0; bd <= 1; bd++ ) {
            printf( "%s:\n", colors[bg] );
            for( fg = 0; fg < 8; fg++ ) {
                printf( " \e[%dm\e[%s%dm %s%s \e[0m", 
                    bg+40, bd?"1;":"", fg+30, bd?"lt":"  ", colors[fg] );
                fflush(stdout);
            }
            printf( "\n" );
        }
    }
    return;
}

void usage( void ) {
    printf( "%sc%so%sl%so%sr%s v%0.2f - copyright (c) 2001 "
            "Moshe Jacobson <moshe@runslinux.net>\n", FG_LTRED, FG_LTYELLOW, 
            FG_LTGREEN, FG_LTBLUE, FG_LTMAGENTA, NOCOLOR, VERSION );
    printf( "This program is free software released under the GPL. "
            "See COPYING for info.\n\n" );
    printf( "Usage:\n\n   %scolor%s [lt]%sfgcolor%s [%sbgcolor%s]\n", 
            FG_BD, NOCOLOR, FG_UL, NOCOLOR, FG_UL, NOCOLOR );
    printf( "   %scolor%s [ bd | ul | off ] %s\n   color%s --list\n\n", 
            FG_BD, NOCOLOR, FG_BD, NOCOLOR );

    printf( "   %sfgcolor%s and %sbgcolor%s are one of:\n", 
            FG_UL, NOCOLOR, FG_UL, NOCOLOR ); 
    printf( "      %sred %sgreen %syellow %sblue %smagenta %scyan %swhite%s.\n",
            FG_LTRED, FG_LTGREEN, FG_LTYELLOW, FG_LTBLUE, FG_LTMAGENTA, 
            FG_LTCYAN, FG_LTWHITE, NOCOLOR );
    printf( "   Preceed the foreground color with %slt%s to use a light "
            "color.\n", FG_BD, NOCOLOR );
    printf( "   %scolor ul%s and %scolor bd%s turn on %sunderline%s and "
            "%sbold%s, respectively.\n", FG_BD, NOCOLOR, FG_BD, NOCOLOR,
            FG_UL, NOCOLOR, FG_BD, NOCOLOR );
    printf( "   %scolor off%s turns off any coloring and resets "
            "to default colors.\n", FG_BD, NOCOLOR );
    printf( "   %scolor --list%s shows all the possible color combinations "
            "visually.\n\n", FG_BD, NOCOLOR );

    printf( "Example:\n\n" );

    printf( "   This program can be used from shellscripts as a "
            "convenience to allow for\n"
            "   ansi colored text output. Simply invoke it with command "
            "substitution. For\n"
            "   example, in a POSIX compliant shell such as bash or ksh, "
            "you would do:\n\n"
            "      echo \"$(color ltyellow blue)Hi there!$(color off)\"\n\n"
            "   to see %sHi there!%s\n\n", FG_LTYELLOW BG_BLUE, NOCOLOR );
    return;
}

void fgcolor( char *clr ) {
    unsigned int i;

    if( !strcmp(clr,"off") ) {
        printf( NOCOLOR );
        return;
    } else if( !strcmp(clr,"bd") ) {
        printf( FG_BD );
        return;
    } else if( !strcmp(clr,"ul") ) {
        printf( FG_UL );
        return;
    }
    
    else if( !strncmp(clr,"lt",2) ) {
        printf( "\033[1m" );
        clr+=2;
    } else {
        printf( "\033[0m" );
    }

    for( i=0; i<8; i++ ) {
        if( !strcmp(clr,colors[i]) ) {
            printf( "\033[%dm", 30+i );
            break;
        }
    }
    return;
}
    
void bgcolor( char *clr ) {
    unsigned int i;

    for( i=0; i<8; i++ ) {
        if( !strcmp(clr,colors[i]) ) {
            printf( "\033[%dm", 40+i );
            break;
        }
    }
    return;
}

int main( int argc, char *argv[] ) {

    if( argc == 1 ) {
        usage();
        return EXIT_SUCCESS;
    }
    
    if( !strcmp(argv[1], "--list") ) {
        list_colors();
        return EXIT_SUCCESS;
    }

    fgcolor( argv[1] );
    if( argv[2] ) bgcolor( argv[2] );
    
    
    return EXIT_SUCCESS;
}

