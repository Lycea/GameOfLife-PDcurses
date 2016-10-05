#define _AFXDLL

#include "curses.h"
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "patterns.h"
#include "Menues.h"


#define MAX_ROWS      60//60
#define MAX_COLUMN    200//200

#define LAST_ROW      (MAX_ROWS-1)
#define LAST_COLLUMN  (MAX_COLUMN-1)


struct options
{
   const char * name;
   unsigned int value ;
};

struct field
{
    int _old;
    int _new;
};


typedef struct options Options;

int *pre_def[]=
{
    *glider,
    *glider_gun,
    *lwss,
    *mwss,
    *blinker_ship
};


Options c_pre_def[] =
{
    {"<     Glider   >",303}, 
    {"<  Glider Gun  >",936},
    {"<      LWWS    >",405},
    {"<      MWSS    >",506},
    {"< blinker_ship >",1731},
    {"<     none     >",0}
};


/*option types definition*/
Options o_gol[9] =
{
    {"                   ", -1},
    {"1.Speed:    <     >",  0},
    {"                   ", -1},
    {"2.Density:  <     >", 50},
    {"                   ", -1},
    {"3.Color:    <     >",  3},
    {"                   ", -1},
    {"Exit", -1},
    {"Options", -1}
};


void first_tests();
void game_of_life_menue();
void dummy_function();
void draw_menue(int opt,Menue *names_,int max);
void gol_random();
void gol_editor();


const char *controls[] = { "Use up + down arrows to navigate\n and enter to select", 
                           "Exit with ESC else click to move",
                           "Change the options with a click"};

    field board[MAX_ROWS][MAX_COLUMN];


void dummy_function()
{
    init_pair(2,COLOR_RED,COLOR_BLACK);

    attron(COLOR_PAIR(2));
    mvprintw(LINES/2,COLS/2,"Not available right now");
    attroff(COLOR_PAIR(2));
    getch();
    clear();
}

void do_init()
{
    initscr();			/* Start curses mode 		  */
    start_color();      /*init colors*/
    keypad(stdscr,true);/*inits the keys linke arrow keys for input*/
    mousemask(ALL_MOUSE_EVENTS, NULL);
    mouse_set(ALL_MOUSE_EVENTS);
    init_pair(1,COLOR_BLUE,COLOR_GREEN);/*init first color pair*/
    init_pair(3,COLOR_BLACK,COLOR_RED);
    curs_set(0); //set the curser invisible)
    noecho(); //set no echo for userinput
}

WINDOW* load_sub_win(WINDOW *win,int col_pair)
{
    win = subwin(stdscr, 10,MAX_COLUMN,MAX_ROWS,0); //create a new window

    box(win,0,0); // make border
    wbkgd(win,COLOR_PAIR(col_pair));

    wrefresh(win);

    return win;
}

void gol_options()
{
    bool b_no_end = true;
    int mkey;
    clear();
    draw_menue(-1,(Menue*)o_gol,9);
    draw_menue(7,(Menue*)o_gol,9);

    mvprintw(2,15,"%i",o_gol[1].value);
    mvprintw(4,15,"%i",o_gol[3].value);
    mvprintw(6,15,"%i",o_gol[5].value);
    refresh();

    do
    {
        mkey = getch();
        if(mkey == KEY_MOUSE)
        {
            int button ;
            request_mouse_pos();
            if (BUTTON_CHANGED(1))
                button = 1;

            if ((BUTTON_STATUS(button) &
                BUTTON_ACTION_MASK) == BUTTON_CLICKED)
            {
                switch(MOUSE_Y_POS)
                {
                case 2:
                    if(MOUSE_X_POS == 13)
                    {
                        o_gol[MOUSE_Y_POS-1].value--;
                        if(o_gol[MOUSE_Y_POS-1].value ==-1)
                        {
                            o_gol[MOUSE_Y_POS-1].value = 0;
                        }
                        mvprintw(MOUSE_Y_POS,15,"%i",o_gol[MOUSE_Y_POS-1].value);
                    }
                    else if( MOUSE_X_POS == 19)
                    {
                        o_gol[MOUSE_Y_POS-1].value++;
                        mvprintw(MOUSE_Y_POS,15,"%i",o_gol[MOUSE_Y_POS-1].value);
                    }
                    break;

                case 4:
                    if(MOUSE_X_POS == 13)
                    {
                        o_gol[MOUSE_Y_POS-1].value--;
                        if(o_gol[MOUSE_Y_POS-1].value ==-1)
                        {
                            o_gol[MOUSE_Y_POS-1].value = 0;
                        }
                        mvprintw(MOUSE_Y_POS,15,"%i",o_gol[MOUSE_Y_POS-1].value);
                    }
                    else if( MOUSE_X_POS == 19)
                    {
                        o_gol[MOUSE_Y_POS-1].value++;
                        mvprintw(MOUSE_Y_POS,15,"%i",o_gol[MOUSE_Y_POS-1].value);
                    }
                    break;

                case 6:
                    if(MOUSE_X_POS == 13)
                    {
                        o_gol[MOUSE_Y_POS-1].value--;
                        if(o_gol[MOUSE_Y_POS-1].value ==-1)
                        {
                            o_gol[MOUSE_Y_POS-1].value = 0;
                        }
                        mvprintw(MOUSE_Y_POS,15,"%i",o_gol[MOUSE_Y_POS-1].value);
                    }
                    else if( MOUSE_X_POS == 19)
                    {
                        o_gol[MOUSE_Y_POS-1].value++;
                        mvprintw(MOUSE_Y_POS,15,"%i",o_gol[MOUSE_Y_POS-1].value);
                    }

                case 8:
                    if(MOUSE_X_POS >= 0 && MOUSE_X_POS <4)
                    {
                        b_no_end = false;
                    }
                    default:;
                }
            }
            //printw( "Position: Y: %d X: %d", MOUSE_Y_POS, MOUSE_X_POS);
        }
    }
    while(b_no_end);
    clear();
}

void save_state()
{

}

void first_tests()
{
    char test[20];
    sprintf(test,"test!\nxyz");

    attrset(A_BOLD);
	printw(test);	/* Print the testtext		  */
    attroff(A_BOLD);

    attron(COLOR_PAIR(1));
        mvprintw(5,5,"Hi again");
	    refresh();			/* Print it on to the real screen */
	    getch();			/* Wait for user input */
    attroff(COLOR_PAIR(1));

    printw(test);
    mvprintw(0,0,"Hi again");
    refresh();			/* Print it on to the real screen */
    getch();

    int column_ = COLS, rows_ = LINES;
    resize_term(MAX_ROWS,MAX_COLUMN);
    
    getch();
    resize_term(rows_,column_);
    
    attrset(COLOR_PAIR(3)|A_BLINK);
    mvprintw(20,10," ");
    attrset(A_NORMAL);

    mouse_set(ALL_MOUSE_EVENTS);
    //PDC_save_key_modifiers(TRUE);
    //PDC_return_key_modifiers(TRUE);

    raw();
    timeout( 0);
    getch();

    while(true)
    {
        int key = getch();

        if(key == KEY_MOUSE)
        {
            int button ;
            request_mouse_pos();
            if (BUTTON_CHANGED(1))
                button = 1;
            else if (BUTTON_CHANGED(2))
                button = 2;
            else if (BUTTON_CHANGED(3))
                button = 3;

            move( 4, 18);
            clrtoeol();
            printw( "Button %d: ", button);

            if (MOUSE_MOVED)
            {
                addstr( "moved: ");
                attrset(COLOR_PAIR(3)|A_BLINK);
                mvprintw(MOUSE_Y_POS,MOUSE_X_POS," ");
                attrset(A_NORMAL);
            }
            else if (MOUSE_WHEEL_UP)
                addstr("wheel up: ");
            else if (MOUSE_WHEEL_DOWN)
                addstr("wheel dn: ");
            else if ((BUTTON_STATUS(button) &
                BUTTON_ACTION_MASK) == BUTTON_PRESSED)
            {
                addstr("pressed: ");
                attrset(COLOR_PAIR(3)|A_BLINK);
                mvprintw(MOUSE_Y_POS,MOUSE_X_POS," ");
                attrset(A_NORMAL);
            }
            else if ((BUTTON_STATUS(button) &
                BUTTON_ACTION_MASK) == BUTTON_CLICKED)
                addstr( "clicked: ");
                attrset(COLOR_PAIR(3)|A_BLINK);
                mvprintw(MOUSE_Y_POS,MOUSE_X_POS," ");
                attrset(A_NORMAL);

            //printw( "Position: Y: %d X: %d", MOUSE_Y_POS, MOUSE_X_POS);
            
        }
        else if(key == 27)
        {
            break;
        }
    }
    clear();
}

void gol_make_board()
{
    srand(time(NULL));
    int num[3];

    clear();
    /*set alive dead start */
    attrset(COLOR_PAIR(3)|A_BLINK);
    for(int lines = 0; lines < MAX_ROWS;lines++)
    {
        for(int columns = 0; columns <MAX_COLUMN;columns++)
        {

#ifdef default_way
            /*decide if 0 or 1*/
            for(int i = 0; i<3; i++)
            {
                num[i] = rand() % 2000+1;
            }

            /*show or not show it*/
            if((num[0]+num[1]+num[2])%2 )
            {
                board[lines][columns]._old = 0;
                mvprintw(lines,columns," ");
                //OutputDebugString(L"0");
            }
            else
            {
                board[lines][columns]._old = 1;
                //OutputDebugString(L"1");
            }
#else
            num[0] = rand() % 100;
            if(num[0] < o_gol[3].value)
            {
                board[lines][columns]._old = 0;
                mvprintw(lines,columns," ");
            }
            else
            {
                board[lines][columns]._old = 1;
            }
#endif
            
        }
    }
    attrset(A_NORMAL);
    refresh();
}

int calc_next(int row, int col)
{
    int n; // number of neighbours
#ifndef default_way
    /*normal row not at the borders*/
    if( col != 0 && col != LAST_COLLUMN && row != 0 && row!= LAST_ROW)
    {
        n = board[row+1][col]._old +     //under the cell
            board[row+1][col+1]._old +   //right diagonal below the cell
            board[row+1][col-1]._old +   //left diagonal below the cell
            board[row-1][col]._old +     //above the cell
            board[row-1][col+1]._old +   //right diagonal above the cell
            board[row-1][col-1]._old +   //left diagonal above the cell
            board[row][col+1]._old +     //right side of the cell
            board[row][col-1]._old;      //left side of the cell
    }
    /*it is a border place*/
    else
    {
        /*it is in the first row*/
        if(row == 0)
        {
            /*not left or right corner*/
            if(col!=0 || col!= LAST_COLLUMN)
            {
                n = board[row+1][col]._old +
                board[row+1][col+1]._old +
                board[row+1][col-1]._old +
                board[LAST_ROW][col]._old +
                board[LAST_ROW][col+1]._old +
                board[LAST_ROW][col-1]._old +
                board[row][col+1]._old +
                board[row][col-1]._old;
            }
            // top left corner //fi
            else if(col == 0)
            {
                n = board[1][0]._old +                 //under the cell
                    board[1][1]._old +                 //right diagonal below the cell
                    board[1][LAST_COLLUMN]._old +      //left diagonal  below the cell 
                    board[LAST_ROW][0]._old +          //above the cell
                    board[LAST_ROW][1]._old +          //right diagonal above the cell
                    board[LAST_ROW][LAST_COLLUMN]._old +   //left diagonal above the cell
                    board[row][col+1]._old +     //right side of the cell
                    board[row][LAST_COLLUMN]._old;      //left side of the cell
            }
            // top right corner
            else if(col == LAST_COLLUMN)
            {
                n = board[1][LAST_COLLUMN]._old +     //under the cell
                    board[1][0]._old +           //right diagonal below the cell
                    board[1][LAST_COLLUMN-1]._old +       //left diagonal below the cell
                    board[LAST_ROW][LAST_COLLUMN]._old +            //above the cell
                    board[LAST_ROW][0]._old +              //right diagonal above the cell
                    board[LAST_ROW][LAST_COLLUMN-1]._old +          //left diagonal above the cell
                    board[0][0]._old +             //right side of the cell
                    board[0][LAST_COLLUMN -1]._old;          //left side of the cell
            }
        }
        /*it is in the last row*/
        else if(row == LAST_ROW)
        {
            //not at a corner
            if(col!=0 || col!= LAST_COLLUMN)
            {
                n = board[0][col]._old +     //under the cell
                board[0][col+1]._old +       //right diagonal below the cell
                board[0][col-1]._old +       //left diagonal below the cell
                board[row-1][col]._old +     //above the cell
                board[row-1][col+1]._old +   //right diagonal underabove the cell
                board[row-1][col-1]._old +   //left diagonal above the cell
                board[row][col+1]._old +     //right side of the cell
                board[row][col-1]._old;      //left side of the cell
            }
            //bottom left corner
            else if(col == 0)
            {
                n = board[0][0]._old +     //under the cell
                board[0][col+1]._old +       //right diagonal below the cell
                board[0][LAST_COLLUMN]._old +         //left diagonal below the cell
                board[row-1][col]._old +     //above the cell
                board[row-1][col+1]._old +   //right diagonal above the cell
                board[row-1][LAST_COLLUMN]._old +     //left diagonal above the cell
                board[row][col+1]._old +     //right side of the cell
                board[row][LAST_COLLUMN]._old;        //left side of the cell
            }
            //bottom right corner*/
            else if(col == LAST_COLLUMN)
            {
                n = board[0][col]._old +     //under the cell
                board[0][col+1]._old +       //right diagonal below the cell
                board[0][col-1]._old +       //left diagonal below the cell
                board[row-1][col]._old +     //above the cell
                board[row-1][0]._old +       //right diagonal above the cell
                board[row-1][col-1]._old +   //left diagonal above the cell
                board[row][0]._old +         //right side of the cell
                board[row][col-1]._old;      //left side of the cell
            }
        }
        /*is left side*/
        else if(col == 0)
        {
            n = board[row+1][col]._old +     //under the cell
            board[row+1][col+1]._old +   //right diagonal below the cell
            board[row+1][LAST_COLLUMN]._old +   //left diagonal below the cell
            board[row-1][col]._old +     //above the cell
            board[row-1][col+1]._old +   //right diagonal underabove the cell
            board[row-1][LAST_COLLUMN]._old +   //left diagonal above the cell
            board[row][col+1]._old +     //right side of the cell
            board[row][LAST_COLLUMN]._old;      //left side of the cell
        }
        /*is right side*/
        else if(col == LAST_COLLUMN)
        {
            n = board[row+1][col]._old +     //under the cell
            board[row+1][0]._old +   //right diagonal below the cell
            board[row+1][col-1]._old +   //left diagonal below the cell
            board[row-1][col]._old +     //above the cell
            board[row-1][0]._old +   //right diagonal above the cell
            board[row-1][col-1]._old +   //left diagonal above the cell
            board[row][0]._old +     //right side of the cell
            board[row][col-1]._old;      //left side of the cell
        }
    }
#else
n	= 
		board[(row - 1 + COLS) % COLS][col]._old		+
		board[(row - 1 + COLS) % COLS][(col - 1 + LINES) % LINES]._old 	+
		board[(row - 1 + COLS) % COLS][(col + 1) % LINES]._old 	+
        board[(row + 1) % COLS][col]._old		+
		board[(row + 1) % COLS][(col - 1 + LINES) % LINES]._old 	+
		board[(row + 1) % COLS][(col + 1) % LINES]._old 	+
		board[row][(col - 1 + LINES) % LINES]._old		+
		board[row][(col + 1) % LINES]._old;
#endif

    return n;
}

void load_state_win()
{

}

void gol_start()
{
    int prev_pop = 0,
        prevprev_pop = 0,
        x3_gen = 0,
        x4_gen = 0;

    bool b_run = true;
    int key;
    int nbr = 0;
    int i_pop = 0,
        i_gen = 0;

    WINDOW *gui;
    clear();
    gui = load_sub_win(gui,0);

    timeout(o_gol[1].value);
    while(getch() != KEY_F(1))
    {
        
        /*check cells for dead or alive*/
        for(int rows = 0; rows < MAX_ROWS; rows ++)
        {
            for(int _cols = 0; _cols < MAX_COLUMN; _cols++)
            {
                nbr = calc_next(rows,_cols);
                /*check alive or dead*/
                if(board[rows][_cols]._old)
                {
                    if(nbr < 2 || nbr > 3)
                    {
                        board[rows][_cols]._new = 0;
                    }
                    else
                    {
                        board[rows][_cols]._new = 1;
                    }
                }
                else
                {
                    if(nbr == 3)
                    {
                        board[rows][_cols]._new = 1;
                    }
                    else
                    {
                        board[rows][_cols]._new = 0;
                    }
                }
            }
        }


        i_pop = 0;
        /*actualise the board*/
        for(int i = 0; i< MAX_ROWS; i++)
        {
            for(int j = 0; j< MAX_COLUMN; j++)
            {
                board[i][j]._old=board[i][j]._new;
                if(board[i][j]._new == 1)
                {
                    attron(COLOR_PAIR(o_gol[5].value)|A_BLINK);
                     mvprintw(i,j," ");
                    attroff(COLOR_PAIR(o_gol[5].value)|A_BLINK);
                    i_pop++;
                }
                else
                {
                    mvprintw(i,j," ");
                }
            }
        }

        i_gen++;

        
        /*print array to file*/
        //FILE *fp;

        /*fp = fopen("test.txt","a+");

        fprintf(fp,"\n\n");
        for(int i = 0; i < MAX_ROWS; i++)
        {
            for(int j = 0; j < MAX_COLUMN; j++)
            {
                if(board[i][j]._new == 1)
                {
                    fprintf(fp,"0");
                }
                else
                {
                    fprintf(fp,".");
                }
            }
            fprintf(fp,"\n");
        }

        fclose(fp);*/
        /*gui = load_sub_win(gui,0);*/

        mvwprintw(gui, 5,5,"Population:        %d",i_pop);
        mvwprintw(gui, 7,5,"Actual generation: %d",i_gen);

        if((i_pop == prev_pop  &&  i_pop== prevprev_pop && x3_gen == i_pop)||(i_pop == prevprev_pop && i_pop == x4_gen))
        {
            mvwprintw(gui, 3,5,"Dead");
        }
        else
        {
            mvwprintw(gui, 3,5,"    ");
        }
        refresh();
        x4_gen = x3_gen;
        x3_gen = prevprev_pop;
        prevprev_pop = prev_pop;
        prev_pop = i_pop;
        i_pop = 0;
        wrefresh(gui);
    }
}

void gol_start_steps()
{
    int val;

    val = o_gol[1].value;
    o_gol[1].value = -1;
    gol_start();
    o_gol[1].value = val;

}

void init_array()
{
    for(int i= 0; i<= LAST_ROW; i++)
    {
        for(int j = 0; j<= LAST_COLLUMN;j++)
        {
            board[i][j]._old = 0;
        }
    }
}

void gol_loaded()
{
    
}

void draw_bg()
{
    bool b = true;
    for(int i = 0; i<= LAST_ROW;i++)
    {
        b = i%2;
        for(int j = 0; j<= LAST_COLLUMN; j++)
        {
            if(b)
            {
                attrset(A_REVERSE);
                mvprintw(i,j," ");
                attrset(A_NORMAL);
                b=false;
            }
            else
            {
                mvprintw(i,j," ");
                b=true;
            }
        }
    }
    refresh();
}

void gol_editor()
{
    WINDOW *w_gui;
    bool editing = true;
    int key;
    int column_ = COLS, rows_ = LINES;

    clear();
    resize_term(MAX_ROWS+10,MAX_COLUMN);
    //draw_bg();

    w_gui = load_sub_win(w_gui,0);
    
    mvwprintw(w_gui,4,40,"save state");
    mvwprintw(w_gui,4,60,"start run");
    mvwprintw(w_gui,6,60,"start run step");
    mvwprintw(w_gui,4,80,"restart map");
    wrefresh(w_gui);
    raw();
    mouse_set(ALL_MOUSE_EVENTS);

    init_array();
    draw_bg();

    timeout(0);
    while(editing)
    {
        
        key = getch();

        if( key == KEY_MOUSE && key != ERR)
        {
            request_mouse_pos();

            if(MOUSE_Y_POS < MAX_ROWS&& MOUSE_Y_POS  != -1)
            {
                int button ;
                
                if (BUTTON_CHANGED(1))
                    button = 1;
                else if (BUTTON_CHANGED(2))
                    button = 2;
                else if (BUTTON_CHANGED(3))
                    button = 3;


                if (MOUSE_MOVED)
                {
                    attrset(COLOR_PAIR(3)|A_BLINK);
                    mvprintw(MOUSE_Y_POS,MOUSE_X_POS," ");
                    attrset(A_NORMAL);
                    board[MOUSE_Y_POS][MOUSE_X_POS]._old = 1;
                }
                else if ((BUTTON_STATUS(button) &
                    BUTTON_ACTION_MASK) == BUTTON_PRESSED)
                {
                    attrset(COLOR_PAIR(3)|A_BLINK);
                    mvprintw(MOUSE_Y_POS,MOUSE_X_POS," ");
                    attrset(A_NORMAL);
                    board[MOUSE_Y_POS][MOUSE_X_POS]._old = 1;
                }
                else if ((BUTTON_STATUS(button) &
                    BUTTON_ACTION_MASK) == BUTTON_CLICKED)
                {
                    attrset(COLOR_PAIR(3)|A_BLINK);
                    mvprintw(MOUSE_Y_POS,MOUSE_X_POS," ");
                    attrset(A_NORMAL);
                    board[MOUSE_Y_POS][MOUSE_X_POS]._old = 1;
                }
            }
            else
            {
                ungetch(key);
                key = wgetch(w_gui);
                flushinp() ;
                if(key == KEY_MOUSE)
                {
                     request_mouse_pos();
                     int y = MOUSE_Y_POS;
                     int x = MOUSE_X_POS;

                     int button ;
                
                    if (BUTTON_CHANGED(1))
                    {
                        button = 1;
                        if ((BUTTON_STATUS(button) &
                            BUTTON_ACTION_MASK) == BUTTON_CLICKED)
                        {
                            if(MOUSE_Y_POS - MAX_ROWS == 4)
                            {
                                if(MOUSE_X_POS >=40 && MOUSE_X_POS <=50)
                                {
                                    
                                }
                                else if(MOUSE_X_POS >=MAX_ROWS && MOUSE_X_POS <70)
                                {
                                    gol_start();
                                    editing = false;
                                    clear();
                                    resize_term(rows_,column_);
                                }
                                else if(MOUSE_X_POS >=80 && MOUSE_X_POS <=90)
                                {
                                    init_array();
                                    clear();
                                    w_gui = load_sub_win(w_gui,0);
                                        mvwprintw(w_gui,4,40,"save state");
                                        mvwprintw(w_gui,4,60,"start run");
                                        mvwprintw(w_gui,6,60,"start run step");
                                        mvwprintw(w_gui,4,80,"restart map");
                                        wrefresh(w_gui);
                                    draw_bg();
                                }
                            }
                            else if(MOUSE_Y_POS - MAX_ROWS == 6)
                            {
                                if(MOUSE_X_POS >=MAX_ROWS && MOUSE_X_POS <=74)
                                {
                                    
                                    gol_start_steps();
                                    editing = false;
                                    clear();
                                    resize_term(rows_,column_);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void gol_random()
{
    int column_ = COLS, rows_ = LINES;
    int key;
    bool do_random = true;

    resize_term(MAX_ROWS +10,MAX_COLUMN);

    do
    {
        gol_make_board();

        bool b = true;
        while(b)
        {
            key = getch();

            switch(key)
            {
                case 'r':
                    b = false;
                    break;

                case 'a':
                    b = false;
                    do_random = false;
                    break;

                case 's':
                    b = false;
                    do_random = false;
                    break;
            }
        }
    }
    while(do_random);

    if(key =='a')
    {
        gol_start();
    }
    else
    {
        gol_start_steps();
    }
    
    clear();
    resize_term(rows_,column_);
}

void game_of_life_menue()
{
    int key;
    int option = 0;
    draw_menue(-1,gol,MAX_GOL);
    bool b_end = false;

    while(1)
    {
        key = getch();

        switch(key)
        {
            case KEY_UP:
                if(option != 0)
                {
                    option--;
                    draw_menue(option,gol,MAX_GOL);
                }
                break;

            case KEY_DOWN:
                if(option != 4)
                {
                    option++;
                    draw_menue(option,gol,MAX_GOL);
                }
                break;

            case KEY_ENTER:
            case 10:
            case 13:
                if(option != 4)
                {
                    gol[option].function();
                    draw_menue(-1,gol,MAX_GOL);
                    draw_menue(option,gol,MAX_GOL);
                }
                else
                {
                    b_end = true;
                }
                break;

            default:;
        }
        if(b_end)
        {
            clear();
            break;
        }
    }
}

void draw_menue(int opt,Menue *names_,int max)
{
    static int old_opt;
    //First drawing
    if(opt == -1)
    {
        attrset(A_NORMAL);
        attrset(A_BOLD);
        mvprintw(0,0,names_[max-1].name);
        attroff(A_BOLD);

        attrset(A_REVERSE);
        mvprintw(1,1,names_[0].name);
        attroff(A_REVERSE);

        for(int i = 2; i< max;i++)
        {
            mvprintw(i,1,names_[i-1].name);
        }
        old_opt = 0;
    }
    else
    {
        if(opt > -1)
        {
            /*overdraw old one*/
            attrset(A_NORMAL);
            mvprintw(old_opt+1,1,names_[old_opt].name);
            attrset(A_NORMAL);

            attrset(A_REVERSE);
            /*overdraw new one*/
            mvprintw(opt+1,1,names_[opt].name);
            attrset(A_NORMAL);

            old_opt = opt;
        }
    }
}

int main(int argc, char *argv[])
{
    int key_;
    unsigned int option_ = 0;
    bool b_end = false;

    /*do the initialisastion stuff*/
    do_init();
    /*draw the menue first time*/
    draw_menue(-1,options,MAX_MAIN);

    while(true)
    {
        key_ = getch();
        switch(key_)
        {
            case KEY_UP:
                if(option_ != 0)
                {
                    option_ --;
                    draw_menue(option_,options,MAX_MAIN);
                    refresh();
                }
                break;

            case KEY_DOWN:
                if(option_ != 5)
                {
                    option_ ++;
                    draw_menue(option_,options,MAX_MAIN);
                    refresh();
                }
                break;

            case KEY_ENTER:
            case 10:
            case 13:
                clear();
                if(option_ !=5)
                {
                    options[option_].function();
                    draw_menue(-1,options,MAX_MAIN);
                    draw_menue(option_,options,MAX_MAIN);
                }
                else
                {
                    endwin();
                    b_end = true;
                }
                break;

        }
        if(b_end)
        {
            break;
        }

    }
	endwin();			/* End curses mode		  */
    return 0;
}