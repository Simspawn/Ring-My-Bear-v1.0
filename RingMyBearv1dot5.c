#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct
    {
        char name[20];
    } Player;
    
typedef struct GatedDescription
    {
        int flag;
        const char *gatedDesc;
    } GatedDescription;

typedef struct Stage
    {
        int stageID;
        char stageName[20];
        char description[2000];
        struct Stage *northDest;
        struct Stage *southDest;
        struct Stage *eastDest;
        struct Stage *westDest;
        GatedDescription *gatedDesc1;
        GatedDescription *gatedDesc2;
        GatedDescription *gatedDesc3;
        GatedDescription *gatedDesc4;
        GatedDescription *gatedDesc5;
    } Stage;

typedef struct
    {
        Stage *previousStage;
        Stage *currentStage;
    } State;  

typedef struct
    {
        char buffer[100];
        char raw_input[100];
        char first_word[25];
        char second_word[25];
        char command[25];
    } input;
    
typedef struct
    {
        const char *verb;
        void (*handler)(State *state, input *userinput);
    } Verb;
    
void get_input(char *buffer, size_t size, input *userinput);
void split_input(char *buffer, size_t size, input *userinput);
void set_command(input *userinput);
void execute_command(State *state, input *userinput, Verb *verbs);

void look_func(State *state, input *userinput);
void go_func(State *state, input *userinput);
void dial_FUNC(State *state, input *userinput);

void set_FLAG(uint32_t *bitlocker, uint32_t flag);
void clear_FLAG(uint32_t *bitlocker, uint32_t flag);
bool check_FLAG(uint32_t *bitlocker, uint32_t flag);

int main_loop(void);
void game_TICK(State *state, input *userinput);
void end_SCENE(void);

void init_STAGES(State *state);

Stage CemeteryGate;
void CemeteryGate_FUNC(State *state, input *userinput);

Stage FrontHallow;
void FrontHallow_FUNC(State *state, input *userinput);

Stage NorthHallow;
void NorthHallow_FUNC(State *state, input *userinput);

Stage EastHallow;
void EastHallow_FUNC(State *state, input *userinput);

Stage WestHallow;
void WestHallow_FUNC(State *state, input *userinput);

enum stageID
{
    CEMETERYGATE_ID = 1,
    FRONTHALLOW_ID = 2,
    NORTHHALLOW_ID = 3,
    EASTHALLOW_ID = 4,
    WESTHALLOW_ID = 5
};


input userinput;
bool quit = false;
int turncount =0;
State state;
Verb verbs[] = 
{
    {"look", look_func},
    {"go", go_func},
    {"dial", dial_FUNC},
    {NULL, NULL}
};
 
uint32_t GlobalGates = 0u;
 //eventually just put it in the gd input struct

enum GlobalFlags
{
    PAPER1EXISTS   = (1u << 0),
    PAPER1READ      = (1u << 1),
    PAPER2EXISTS   = (1u << 2),
    PAPER2READ      = (1u << 3),
    PAPER3EXISTS   = (1u << 4),
    PAPER3READ      = (1u << 5), 
    PAPER4EXISTS   = (1u << 6),
    PAPER4READ      = (1u << 7),
    
    FRONTHALLOWVISITED       = (1u << 8),
    NORTHHALLOWVISITED      = (1u << 9),
    EASTHALLOWVISITED        = (1u << 10),
    WESTHALLOWVISITED       = (1u << 11),
        
    SHOWGLOW       = (1u << 12),
    GLOWSEEN         = (1u << 13),
    SHOWGHOST     = (1u << 14),
    GHOSTSEEN      = (1u << 15),
    SHOWBOOTHE =( 1u << 16),
    SHOWEND         = (1u << 17)
    
};
  
 /*
 ====================================================================================
                             int main()                            Eventually the launcher.c
 ====================================================================================
 */
int main()
{
	srand(time(NULL));
	printf ("              Anciano Studios Presenta:\n\n\n\n\n              Ring My Bear\n");
	printf("              A story of love and unforseeable, sometimes tragic consequences.\n\n\n\n\n\n\n\n\n\n");
	main_loop();
	return 0;
}
/*
====================================================================================
*/


/*
====================================================================================
                            int main_loop(void)                            Eventually engine.c
====================================================================================
*/
int main_loop(void)
{
    init_STAGES(&state);                
        
    printf("You'd' left the party early, you just couldn't stand still. You couldn't quite describe it, but you could feel it, \ntugging at the back of your mind... \nSomething was happening. Something was pulling you...\n\nSomeone needed you.\n\n\n\n");
    look_func(&state, &userinput);
    while (quit == false)
	{
        //user input display
        printf("\n->:");
        get_input(userinput.buffer, sizeof(userinput.buffer),  &userinput);
        if (strcmp(userinput.raw_input, "quit") == 0)
        	{
        	    quit = true;
        	    return 0;
        	}
    	split_input(userinput.buffer, sizeof(userinput.buffer), &userinput);
  	  printf("\nYou typed: %s\n\n", userinput.raw_input);
  	  set_command(&userinput);
        execute_command(&state, &userinput, verbs);
        game_TICK(&state, &userinput);
        
 /*
 bool-locked practice
        if (turncount == 4)
        {
            GatedCemeteryGate1.unlocked = true;
        }
        if(GatedCemeteryGate1.unlocked)
        {
            printf("%s", GatedCemeteryDescOne);
        }
        turncount++;
*/            
	} //end of while loop 
	return 0;
} //end of main_loop()
/*
====================================================================================
*/
void get_input(char *buffer, size_t size, input *userinput)
{
    buffer[0] = '\0';
    userinput->first_word[0] = '\0';
    userinput->second_word[0] = '\0';
    userinput->raw_input[0] = '\0'; 
    if (fgets(buffer, size, stdin) != NULL)
        {
            size_t length = strlen(buffer);
            if (length > 0 && buffer[length - 1] == '\n') 
                {
                   buffer[length-1] = '\0';
                } 
                else
                    {
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF)
                            {
                                ;
                            }
                     }
            strncpy(userinput->raw_input, buffer, sizeof(userinput->raw_input));
            userinput->raw_input[(sizeof(userinput->raw_input))-1] = '\0';
            //standardize buffer to lower case
            for (size_t i = 0; buffer[i] != '\0'; ++i)
                {
                    buffer[i] = (char)tolower((unsigned char)buffer[i]);
                }
        }
}
/*
====================================================================================
*/
void split_input(char *buffer, size_t size, input *userinput )
{
    userinput->command[0] = '\0';
    userinput->first_word[0] = '\0';
    userinput->second_word[0] = '\0';
    char *token = strtok(buffer, " \t\r\n");
    if (token)
      {
          strncpy(userinput->first_word, token, sizeof(userinput->first_word) -1);
          userinput->first_word[sizeof(userinput->first_word) -1] = '\0';
      }
    token = strtok(NULL, " \t\r\n");
    if (token)
      {
          strncpy(userinput->second_word, token, sizeof(userinput->second_word) -1);
          userinput->second_word[sizeof(userinput->second_word) -1] = '\0';
          // should we eat the rest of the tokens here to avoid garbage data later? Maybe it gets reset olr destroyed next time strtok is called?
      }
     
}
/*
====================================================================================
*/
void set_command(input *userinput)
{
    struct 
      {
          const char *synonym; 
          const char *dir;
      } dir_syns[] = { {"n", "north"}, {"up",  "north"}, {"s", "south"}, {"down", "south"}, {"e", "east"}, {"right", "east"}, {"w", "west"}, {"left", "west"},
      {"north", "north"}, {"south", "south"}, {"east", "east"}, {"west", "west"},{NULL, NULL}};
      
      for (int i = 0; dir_syns[i].synonym != NULL; i++)
      {
          if (strcmp(userinput->first_word, dir_syns[i].synonym) == 0 || strcmp(userinput->second_word, dir_syns[i].synonym) == 0)
              {
                  strncpy(userinput->command, "go", sizeof(userinput->command) -1);
                  userinput->command[sizeof(userinput->command) - 1] = '\0';
                  strncpy(userinput->first_word, dir_syns[i].dir, sizeof(userinput->first_word) -1);
                  userinput->first_word[sizeof(userinput->first_word) - 1]= '\0';
                  break;
              }
      }                    
    if(strcmp(userinput->first_word, "go")== 0)
      {
          strncpy(userinput->command, "go", sizeof(userinput->command)-1);
          userinput->command[sizeof(userinput->command) -1] = '\0';
          strncpy(userinput->first_word, userinput->second_word, sizeof(userinput->first_word)-1);
          userinput->first_word[sizeof(userinput->first_word) - 1] = '\0';
      }
  
    if(strcmp(userinput->first_word, "look") == 0)
        {
            strncpy(userinput->command , "look", sizeof(userinput->command )-1);
            userinput->command[sizeof(userinput->command)-1] = '\0';
        }       
    if(strcmp(userinput->first_word, "read") == 0)
        {
            strncpy(userinput->command , "look", sizeof(userinput->command )-1);
            strncpy(userinput->first_word, "read", sizeof(userinput->first_word)-1);
            userinput->command[sizeof(userinput->command)-1] = '\0';
            userinput->first_word[sizeof(userinput->first_word)-1] = '\0';
        }

    if(strcmp(userinput->first_word, "dial") == 0)  
    {
        strncpy(userinput->command , "dial", sizeof(userinput->command )-1);
        userinput->command[sizeof(userinput->command)-1] = '\0';
        strncpy(userinput->first_word, userinput->second_word, sizeof(userinput->first_word)-1);
        userinput->first_word[sizeof(userinput->first_word)-1] = '\0';
    }
/*  else 
      {
            userinput->command[0] = '\0';
            userinput->first_word[0] = '0';
            userinput->second_word[0] = '\0';
      }
*/                
}

void execute_command(State *state, input *userinput, Verb *verbs)
{
    bool recognized = false;
    if ((userinput->command[0]) != '\0')
    for (int i = 0; verbs[i].verb != NULL; i++)
        {
            if (strcmp(userinput->command, verbs[i].verb) == 0)
                {
                    verbs[i].handler(state, userinput);
                    recognized = true;
                    break;
                }
        }    
    if (!recognized && strcmp(userinput->raw_input, "quit") != 0)
    {
        printf("\nYou wanna do what?\n\n");
    }
}
/*
====================================================================================
                            verb_func                            Eventually actions.h.c
====================================================================================
*/
// We don't actually use user input here, but the definition demands it and I'll be damned if I make a new one just for one word verbs.
void look_func(State *state, input *userinput)
{
    if(state == NULL || state->currentStage == NULL)
        {
            return;
        }
    GatedDescription *gatedDescs[] =
        {
            state->currentStage->gatedDesc1,
            state->currentStage-> gatedDesc2,
            state->currentStage->gatedDesc3,
            state->currentStage->gatedDesc4,
            state->currentStage->gatedDesc5,
            NULL
        };
    bool read = false;   
    bool somethingwasread = false; 
    if(strcmp(userinput->first_word, "read") == 0)
    {
        read = true;
        
        for(int i = 3; i < 6  && gatedDescs[i] != NULL; i++)
        {
            if(check_FLAG(&GlobalGates, gatedDescs[i]->flag))
            {
                printf("You read the following:\n%s\n\n", gatedDescs[i]->gatedDesc);
                somethingwasread = true; 
            }
        }
        if(!somethingwasread)
        {
            printf("Read what?\n\n");
        }
    }
    if(!read)
    {
    printf("%s\n\n", state->currentStage->stageName);
    printf("%s\n\n", state->currentStage->description);
        for(int i = 0; i < 5 && gatedDescs[i] != NULL; i++)
        {
        if(check_FLAG(&GlobalGates, gatedDescs[i]->flag))
            {
                printf("%s\n\n", gatedDescs[i]->gatedDesc);
            }
        }
    }
}
/*
====================================================================================
*/ 
void go_func(State *state, input *userinput)
{
    typedef enum dir_t
    {
        DIR_NONE,
        DIR_NORTH,
        DIR_SOUTH,
        DIR_EAST,
        DIR_WEST
    } dir_t;
    
    dir_t dir = DIR_NONE;
    bool hasmoved =false;
    if ((userinput->command[0]) != '\0')
    {
        if(strcmp(userinput->first_word, "north") == 0)
        {
            dir = DIR_NORTH;
        }
        else if (strcmp(userinput->first_word, "south") == 0)
        {
            dir = DIR_SOUTH;
        }
        else if (strcmp(userinput->first_word, "east") == 0)
        {
            dir = DIR_EAST;
        }
        else if (strcmp(userinput->first_word, "west") == 0)
        {
            dir = DIR_WEST;
        }
        switch (dir)
        {
            case DIR_NORTH:
                if(state->currentStage->northDest)
                {
                    state->previousStage=state->currentStage;
                    state->currentStage=state->currentStage->northDest;
                    hasmoved = true;
                }
                else printf("You can't go that way\n\n");
            break;
            
            case DIR_SOUTH:
                if(state->currentStage->southDest)
                {
                    state->previousStage=state->currentStage;
                    state->currentStage=state->currentStage->southDest;
                    hasmoved = true;
                }
                else printf("You can't go that way\n\n");
            break;
            
            case DIR_EAST:
                if(state->currentStage->eastDest)
                {
                    state->previousStage=state->currentStage;
                    state->currentStage=state->currentStage->eastDest;
                    hasmoved = true;
                }
                else printf("You can't go that way\n\n");
            break;
            
            case DIR_WEST:
                if(state->currentStage->westDest)
                {
                    state->previousStage=state->currentStage;
                    state->currentStage=state->currentStage->westDest;
                    hasmoved = true;
                }
                else printf("You can't go that way\n\n");
            break;
            
            default:
                printf("Go where?\n\n");
        }
        if (hasmoved == true)
        {
            look_func(state, userinput);
        }
    }
}

void dial_FUNC(State *state, input *userinput)
    {
            if(check_FLAG(&GlobalGates, SHOWBOOTHE))
            {
                if(strcmp(userinput->first_word, "5555557627") == 0 || (strcmp(userinput->first_word, "555-555-7627") == 0))
                {
                    set_FLAG(&GlobalGates, SHOWEND);
                } else printf("Dial what?\n");
            } else printf("Dial on what?\n");
    }
/*
====================================================================================
*/ 

void set_FLAG(uint32_t *bitlocker, uint32_t flag)
{
    *bitlocker |= flag;   
}
void clear_FLAG(uint32_t *bitlocker, uint32_t flag)
{
    *bitlocker &= ~flag;
}
bool check_FLAG(uint32_t *bitlocker, uint32_t flag)
{
    return (*bitlocker &flag);
}

void init_STAGES(State *state) 
{

    
    //intro, the spawn room
    CemeteryGate.stageID = CEMETERYGATE_ID;
    snprintf(CemeteryGate.stageName, sizeof(CemeteryGate.stageName),"Cemetery Gate");
    snprintf(CemeteryGate.description, sizeof(CemeteryGate.description), 
        "You find yourself standing infront of the gates to the old cemetary. The fog drifts slowly by as a crisp nippy \n"
        "breeze breathes down your neck. A wild animal calls out in the woods, one you don't recognize. A chill slithers\n"
        "up your spine.\n"
        "\nThe gate leads North, a sense of need urges you to go in.\n\n");

    CemeteryGate.northDest       =&FrontHallow;
    CemeteryGate.southDest      =NULL;
    CemeteryGate.eastDest        =NULL;
    CemeteryGate.westDest       =NULL;

    
    //North of Cemetary Gate.
    FrontHallow.stageID = FRONTHALLOW_ID;
    snprintf(FrontHallow.stageName, sizeof(FrontHallow.stageName),"Front Hallow");
    snprintf(FrontHallow.description, sizeof(FrontHallow.description), 
    "The cemetary opens up before you, tombstones and crypts hiding behind the mist. Walking paths traverse the \n"
    "grounds, allowing you to walk among the dead without stepping on the grass. The signs insist you stay off the \n"
    "grass, which seems like an especially good idea right now. The somber silence wraps around you, embalming \n"
    "you in the night.\n"
    "There are paths North, South, East, and West.\n\n");
    FrontHallow.northDest       =&NorthHallow;
    FrontHallow.southDest      =&CemeteryGate;
    FrontHallow.eastDest        =&EastHallow;
    FrontHallow.westDest       =&WestHallow;
    static GatedDescription FrontHallowGatedDescs[] =
    {
        { PAPER1EXISTS, 
        "You see a piece of newspaper held down by a rock. The print is faded but you can make out bits and pieces if you read it.\n\n"},
        {SHOWGLOW, 
        "You see a faint glow o the north, drawing your attention back to the North Hallow."},
        {PAPER1EXISTS, 
        "Local mother defends child from wolf attack........ Dubbed a True Momma Bear...... Local Heroine\n\n"},
        {false, NULL}
    };
    FrontHallow.gatedDesc1 = &FrontHallowGatedDescs[0];
    FrontHallow.gatedDesc2 =&FrontHallowGatedDescs[1];
    FrontHallow.gatedDesc3 =NULL;
    FrontHallow.gatedDesc4 = &FrontHallowGatedDescs[2];
    FrontHallow.gatedDesc5 = NULL;   

        
    
    //North of  Front Hallow
    NorthHallow.stageID = NORTHHALLOW_ID;
    snprintf(NorthHallow.stageName, sizeof(NorthHallow.stageName), "North Hallow");
    snprintf(NorthHallow.description, sizeof(NorthHallow.description), 
    "You are in the oldest section of the grounds now. There are less crypts and more tombstones. Simpler tombstones, \n"
    "some cracked, most faded with weather and time. The branches of the trees bend and creak gently in the breeze. \n"
    "The path winds back toward the south.\n\n");
    NorthHallow.northDest       =NULL;
    NorthHallow.southDest      =&FrontHallow;
    NorthHallow.eastDest        =NULL;
    NorthHallow.westDest       =NULL;
    static GatedDescription NorthHallowGatedDescs[] = 
    {
            {PAPER4EXISTS, "There's newspaper clinging to the side of a tombstone. It's been dirty and faded, but you can read The headline.\n\n"},
            {PAPER4EXISTS, "Seating collapse .. local ch.rity event. Massive ..sualties r.p.rted .... young ch..dren incl..ed among ... dead.....\n\n"},
            {SHOWGHOST, 
            "You see a translucent blueish form. Looking closer, it looks exactly like a little boy. The ghostkid is pacing back and forth, \n"
            "his mouth moving, as if speaking. As you focus on the little boy, you can hear what he is saying.\n"
            "\"Can you ring my bear?\"\n"
            "\"I don't feel safe without my bear.\"\n"
            "\"555-555-ROAR, that's 7627.\"\n"
            "\"ling ling ling ling, la ling ling ling ling\"\n"},
            {false, NULL}
    };
    NorthHallow.gatedDesc1 = &NorthHallowGatedDescs[0];
    NorthHallow.gatedDesc2 =&NorthHallowGatedDescs[2];
    NorthHallow.gatedDesc3 =NULL;
    NorthHallow.gatedDesc4 =&NorthHallowGatedDescs[1];
    NorthHallow.gatedDesc5 = NULL; 
    
    //Eastern Room right of spawn room.
    EastHallow.stageID = 4;
    snprintf(EastHallow.stageName, sizeof(EastHallow.stageName),"East Hallow");
    snprintf(EastHallow.description, sizeof(EastHallow.description), 
    "You are in the newest portion of the cemetary. You remember they built new fencing and started mowing this \n"
    "section just a few years ago. There aren't  many grave markers here. One tombstone has a cracked phone \n"
    "on set atop it. It doesn't seem\n to have any charge...\n"
    "There is one exit west.\n\n");
    EastHallow.northDest       =NULL;
    EastHallow.southDest      =NULL;
    EastHallow.eastDest        =NULL;
    EastHallow.westDest       =&FrontHallow;
    static GatedDescription EastHallowGatedDescs[] = 
    {
            {PAPER2EXISTS, "There's newspaper clinging to the side of a tombstone. It's been dirty and faded, but you can read The headline.\n\n"},
            {PAPER2EXISTS, "World Class K-pop sensation to perform charity event at historic venue in honour of local heroine.....\n\n"},
            {SHOWBOOTHE, "You see a payphone that you swear just wasn't there before.\n\n"},
            {false, NULL}
    };
    EastHallow.gatedDesc1 = &EastHallowGatedDescs[0];
    EastHallow.gatedDesc2 =&EastHallowGatedDescs[2];
    EastHallow.gatedDesc3 =NULL;
    EastHallow.gatedDesc4 =&EastHallowGatedDescs[1];
    EastHallow.gatedDesc5 = NULL; 
    
    //Western Room left of spawn room.
    WestHallow.stageID = WESTHALLOW_ID;
    snprintf(WestHallow.stageName, sizeof(WestHallow.stageName), "West Hallow");
    snprintf(WestHallow.description, sizeof(WestHallow.description), 
    "You are in the largest section of the cemetary. There are fewer tombstones here, with far more large crypts \n"
    "containing various town leaders and respected businessmen. The ornamentation feels more like a performance \n"
    "rather than a fitting memorial.\n"
    "There is one exit east.\n\n");
    WestHallow.northDest       =NULL;
    WestHallow.southDest      =NULL;
    WestHallow.eastDest        =&FrontHallow;
    WestHallow.westDest       =NULL;
    static GatedDescription WestHallowGatedDescs[] = 
    {
            {PAPER3EXISTS, "There's newspaper caught in the bushes. It's been wripped and torn, but you can read parts of it.\n\n"},
            {PAPER3EXISTS, "Local real-estate magnate indicted on charges of neglect....\n\n."},
            {false, NULL}
    };
    WestHallow.gatedDesc1 = &WestHallowGatedDescs[0];
    WestHallow.gatedDesc2 =NULL;
    WestHallow.gatedDesc3 =NULL;
    WestHallow.gatedDesc4 =&WestHallowGatedDescs[1];
    WestHallow.gatedDesc5 = NULL;   
            
    state->currentStage = &CemeteryGate;//sets spawn point
    state->previousStage = NULL;
    
}

void FrontHallow_FUNC(State *state, input *userinput)
{
    set_FLAG(&GlobalGates, FRONTHALLOWVISITED);
    if((check_FLAG(&GlobalGates,PAPER1EXISTS)) && (strcmp(userinput->first_word, "read") == 0))
    {
        set_FLAG(&GlobalGates, PAPER1READ);
        set_FLAG(&GlobalGates, PAPER2EXISTS);
    }
    if(check_FLAG(&GlobalGates, SHOWGLOW))
    {
        set_FLAG(&GlobalGates, GLOWSEEN);
    }
        if(check_FLAG(&GlobalGates, GLOWSEEN))    
    {
        set_FLAG(&GlobalGates, SHOWGHOST);
    }
}

void EastHallow_FUNC(State *state, input *userinput)
{
    set_FLAG(&GlobalGates, EASTHALLOWVISITED);
    
    if((check_FLAG(&GlobalGates, PAPER2EXISTS)) && (strcmp(userinput->first_word, "read") == 0))
    {
        set_FLAG(&GlobalGates, PAPER2READ);
        set_FLAG(&GlobalGates, PAPER3EXISTS);        
    }   

}

void WestHallow_FUNC(State *state, input *userinput)
{ 
    set_FLAG(&GlobalGates, WESTHALLOWVISITED);
    
    set_FLAG(&GlobalGates, PAPER1EXISTS);
    if((check_FLAG(&GlobalGates, PAPER3EXISTS)) && (strcmp(userinput->first_word, "read") == 0))
    {
        set_FLAG(&GlobalGates, PAPER3READ);
        set_FLAG(&GlobalGates, PAPER4EXISTS);        
    }   
    
}

void NorthHallow_FUNC(State *state, input *userinput)
{
    set_FLAG(&GlobalGates, NORTHHALLOWVISITED);
    if((check_FLAG(&GlobalGates, PAPER4EXISTS)) && strcmp(userinput->first_word, "read") == 0)
    {
        set_FLAG(&GlobalGates, PAPER4READ);
        set_FLAG(&GlobalGates, SHOWGLOW);
    }
    if(check_FLAG(&GlobalGates, SHOWGHOST))
    {
        set_FLAG(&GlobalGates, GHOSTSEEN);
    }
    if(check_FLAG(&GlobalGates, GHOSTSEEN))
    {
        set_FLAG(&GlobalGates, SHOWBOOTHE);
    }
}

void game_TICK(State *state, input *userinput)
{
    turncount++;
    //Use a switch to know what stage you're in. Case on stageID which has been enumed.
    switch (state->currentStage->stageID)
    {
    case WESTHALLOW_ID:
        {
        WestHallow_FUNC(state, userinput);
        break;
        }
    
    case FRONTHALLOW_ID:
        {
        FrontHallow_FUNC(state, userinput);
        break;
        }
    case EASTHALLOW_ID:
        {
            EastHallow_FUNC(state, userinput);
            break;
        }
    case NORTHHALLOW_ID:
        {
            NorthHallow_FUNC(state, userinput);
            break;
        }
        
    default:
        {
            break;
        }
    }
    char *randEffect[6] = 
    {
        "An eerie scream pierces the night, the hair on the back of your neck stands straight out...\n\n", 
        "You see a flicker of movement in the corner of your eye.\n\n", 
        "You see your mom.\n\n", 
        "You see a hand of a corpse protruding from it's grave, only to sink back down ino the dirt.\n\n", 
        "You see a deer. How cute! Until it suddenly bears fangs at you and uns off into the distance.\n\n",
        "You can just barely hear singing, you think. You hold your breathe, straining to hear... 'ling ling ling ling, la ling ling ling ling.'"
    };
    if(!(check_FLAG(&GlobalGates, SHOWEND)) && rand() % 100 < 20)
    {
        int pickEffect = rand() % 6;
            printf("%s\n\n", randEffect[pickEffect]);        
    }
    if(check_FLAG(&GlobalGates, SHOWEND))
        end_SCENE();
}

void end_SCENE(void)
{
    char *endSCENE = 
    "The broken cell on the tombstone begins to vibrate, then it plays out a ringtone. A song, one you recognize. It's the breakout hit from \n"
    "that Korean girl group Girly Days, 'Ling my Bear, ling ling.' It's the original recording too, not the edit they corrected with years later. \n"
    "The ringing on the cell stops as you get the answering machine message. A bright and happy voices comes across the phone speaker.\n"
    "\"Sorry, we can't get to the phone right now. It's finally the big day, OMG, Yay!! The concert is finally set, Little Tommy could not be more \n" 
    "excited. Leave a message after the beep, BOOOOP\". ::beep::\n\n"
    "A glow begins to form into the shape of a young woman. She regards you for a moment, and bows her head. When she looks up you meet \n"
    "her eyes, which have translucent blue tears streaming from them. She mouths the words \"Thank you.\" and turns to the northwest as \n"
    "another blue glow begins approaching\n\n"
    "The child ghost you saw earlier comes running toward the ghost woman. She throws up her hands in claw form and looks like she's \n"
    "growling. The ghost kid is laughing and smiling brightly. He throws himself into her arms. As they embrace each other they slowly begin to \n"
    "fade. \n\nThe feeling of need inside you eases. You feel released.\n\n\n\n\n\n\n\n\n\n"
    "Thank you for playing Ring My Bear v1.0, an Anciano Studios original.\n"
    "Built on the PreMalloEdi{C}tion Engine v1.5"
    ;
    printf("%s \n You played for %i turns.", endSCENE, turncount);
}
