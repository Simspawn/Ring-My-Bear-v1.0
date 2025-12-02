# Ring-My-Bear-v1.0 description + dev-log
First fully playable storyline complete version of Ring My Bear. Content to be added in later versions, maybe.


Dev-log

FBPv1.5 Devlog

/*
Session One: 10/08/2025
Opening CxxDroid for the first time today. Finished an 8 phase lesson yesterday going over what I had so far
in version 1.0 and how to do it more completely and better. Really hoping that getting on here with an actual keyboard and 
mouse will start to reignite the spark of passion I had before [redacted, former boss] quit [redacted, former job]. Literally coding in my sleep, 
coding every waking min I wasn't in the shower. The typing feels natural at least.

@Camp Post Script: 10/09/2025
Had real trouble focusing and remembering/applying what I learned during my first four months. Managed to get a few structs started, 
state, player, stage.  Hopefully as I go, as I spend more time coding and get win after win with reporoducing and producing a 
working IF game/engine, the more the spark reignites. I really want to code and create my games, but it's hard to actually sit down 
and get myself to actually just do it. A second coding session was canceled infavor of more Q&A with jippity. Tomorrow we can code 
a few functions to gain some basic functionality. Maybe that will make it easier to remember and understand how I'm mentally
 mapping how this is all gonna actually execute. 
 */
 
 /*
 Session Two 10/15/2025
 Had breakfast at Waffle House. Still not actually doing the coding like I should. I really need to either finish this damn IF or just go
 back to learning more about programming ffs. 
 
  Did get started on writing a function, but we did still just learn more than we actually coded but we learned specifically about 
  what we were coding.  I think the spark is igniting tho. 
  
  Played some minecraft with Dana then went to Bites for dinner. Got back and hit another session and finished a get_input() that 
  trims new line and if needed flushes stdin to prevent overflow. 
 */
 
 /*
 Session Three: Coding at camp 10/17/2025 3:13PM
 Hopeing to flesh out some io functions. At least enough to achieve some kinda in program functionality so we can begin getting feedback
 and visible progress. 
 
 We made it all the way to getting input echo during a loop where quit closes the program. We removed quit from the echo. 
 */
 
 /* 
 Session Four: Coding at camp 10/18/2025
 We keep forgetting to save and start a new version so the first few days have overlap between them and the iterations 
 aren't clearly defined correctly. This isn't too bad as the changes are small so far, but as we get our coding muscles back into shape and 
 hit longer sessions it's going to be more and more important to remember.
 
 Today we are working on the tokenizer. We are now passing the entire userinput struct to our input functions rather than just the fields
 they may alter. Just incase, and to simplify things. 
 
 Yesterday we solidified our understanding of passing by refernce vs by value, pointers. Pointers will allow our data driven architecture to
 actually live and breathe during the runtime of the program. We still need to move buffer from a global to a userinput field, but that should be simple enough when we get around to it. Will have to change function declarations and calls to fit. 
 
 We have split input into buffer, first_word, and second_word. Make sure to go back and clear all input variables at the start of loops, ie. first_word[0] = '\0' etc etc just to be on the safe side.' Consider using memset in the future. 
 */
 
 /* 
 Session Five and Six: 10/21/2025 10/22/2025
 We coded before work yesterday and today. Made a lot of frusterating progress. Now have stage struct setup with pointers. The system
 is working. Ish. You still gotta lfill out the verb list and ogic out some proper funtions for each. You still gotta validate input into a usable 
command so you can logic what functions to call. You still gotta actually make a few stages at least for testing, llink them, and finish your movement  system. There's still a shit ton to do, but celebrate. It compiles with linked stage struct system in place (sort of). '
 */
 
 /*
 Session Seven: 10/24/2025
 Don't work today, but woke up low energy no focus, napped, woke up more fog less focus... Ate, feel better but it's already 4pm. Anywho, 
 today we're going to get movement locked down by hook or by crook. a center room, intro, and  a room at each direction. func_GO() properyly working dynamically and correctly called in the loop not just hard coded strcmp().
 */
 
 /*Session Eight: 10/24/2025
 Messed up my prompt to Voliance and he really went off the rails hack and slash and tried to meth up my code to get Riing My Bear just 
 working~ Ahh well, that was my fault. Thankfully I caught on in time to not do anything drastic to my engine. We did get in some good 
 changes. We just really need to work on parsing firstWord and secondWord into useable commands, and then an execute_COMMAND()
 to call the appropriate function. 
 */
 
 /*
 Session Nine:  11/4/2025
 I really hate getting stuck and just not doing the coding. We've moved from fun learning to it just being doing the work of coding it out.
 I really gotta buckle down and just do the coding. Right now I need a set_command() and execute_command() so I can remove the hard
 calls and be systemic. 
 
 We did it. We have no hard calls, just reactions to the user input, Get proper reponses to all direction synonyms, go diretions, look, and junk 
 typing says "you wanna do what?" Still get told you can't go that way if you can't go that way, and you get asked "go where" if you don't provide
 a direction or provide a nondirection.Still gotta collapse directions into enums or whatever, and gotta figure out how const guard stages or 
 something or other~'
 */
 
 /*
 Session Ten: 11/7/25
 Really should set movement directions to enums....  God I really don't want to considering it works the way it is.... 
 
 O.K. movement directions to enums conversion and logic rewrite complte. All dirs and dir_syns properly work, no misc or unaligned prints.
 
 Side Note: 11/11/2025
 While working on a blunt Ring My Bear v1.0, I discovered I need to use snprintf(CemetaryGate.description, sizeof(CemetaryGate.description), "stirng literals here" "and here"); instead of strcpy for initing stage description and other fields.'
 */
 
 /*
 Side Note: 11/12/2025
 A lot of things started clicking today after we figured out bools -> bitwise -> gating datasets -> gating functions like with the verb table -> set_command() picking up a lot more logic which we did already know but -> gating shit in game_tick() and a future world_tick(), plus a lot of other stuff too much to get into at one time, plus a fair amount of introspection and reconnection with our motivation, plus some actual work on Ring My Bear, and we really accomplished a lot today.
 */
 
 /*
 Session Eleven 11/17/2025
 We previously got a bool locked desxription to print on turn 4 as an exeripement. Today we are gonna take that skill and work out the flow for Ring My Bear.'
 */
 
 /*
 Session Twelve 11/22/2025
 We missed a couple dev log updates I think, this might actually be session 14 or 15 who knows, it's a devlog session we'll call it that. Anywho, we 
 have successfully implemented bitwise bitlockers and flags, game_TICK(), FrontHallow_FUNC(), and succefully printf'ed a msg only in one specific stage and only after having been to one specific stage, so that's pretty awesome. A lot of this stuff has really been clicking while working on Ring My Bear and when we get back to working on the actual engine we're gonna have some real work to do then.'
 */
 
/*
 Session Thirteen 11/24/2025
 After many many misadventures with ChatGPT and Gemini I have concluded GPT is better with code, or at least better with working with me. I    also now have state driven description fields that show only after setting a bitflag and through the look_func(). We can now set a bitflag trail as the player plays and show the proper new content as they go.
 */
 
 /*
 Session Fourteen 12/01/2025
 I think I had  several micro sessions over the last week where I added a bit here, a piece there, a nut over somewhere and a bolt somewhere else, however, today was big. Today we woke up in mission mode, with the singular goal to stop dicking around and get it done. We also had to try a new source of lions mane, Magic Mind, which had other stuff and prolly less lions mane but man.... Phew..... Jesus I    was already in mission mode when I woke up but when that stuff started hitting~~~ Love of the deer gods... anywho~ We finished the ghost, the phone booth, the dial verb, the end scene, the credits, printfed the turn count~ Ring My Bear v1.0 is officially done. 
 */
