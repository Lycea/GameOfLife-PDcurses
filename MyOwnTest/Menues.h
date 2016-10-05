#define MAX_MAIN 7 
#define MAX_GOL  6


struct menue
{
    const char *name; //text name of the point
    void (*function)(void);  //pointer to a function which is used
};


typedef struct menue Menue;



extern void first_tests();
extern void game_of_life_menue();
extern void dummy_function();
extern void gol_random();
extern void gol_editor();
extern void gol_options();


Menue options[MAX_MAIN] =
{
    {"1. Intro test",  first_tests},
    {"2.Game Of Life", game_of_life_menue},
    {"3.Ant", dummy_function},
    {"4.--", dummy_function},
    {"5.--", dummy_function},
    {"6.Exit", 0},
    {"Overfiew",0}//shouldn't get there
};


Menue gol[MAX_GOL] =
{
    {"1. Random start state", gol_random},
    {"2. Own start state", gol_editor},
    {"3. Load start pattern", dummy_function},
    {"4. Options", gol_options},
    {"5. Exit",dummy_function},
    {"Game of Life",dummy_function}
};