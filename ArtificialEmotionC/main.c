//
//  main.c
//  ArtificialEmotionC
//
//  Created by Zane Lassiter on April 29th, 2015
//
//  LAST EDITED:                September 25th, 2015
//

//System Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>
#include <limits.h>
#include <termios.h>

//Personal headers
#include "emotion.h"
#include "user.h"
/* Included in Header:

 EMOTION Type

 STATE Type

 Companion Struct and underlying functions

 EMOTION Mod functions

 TODO: Add STATE Mod functions

*/

#define MAX_SIZE 1028
#define MAX_RESPONSE_SIZE 64
#define nOne 2
#define nTwo 1
//MAIN FUNCTION BEGIN
int main(int argc, const char * argv[]) {
    //Prep for Time command
    time_t rawtime;
    time (&rawtime);

    struct tm *info;
    info = localtime (&rawtime);
    
    //Number of arguements in Emotion Triggers array, KEEP UP TO DATE WITH ARRAY
    //int nOne = 2;
    //const char *queries[nOne] = {"Time", "Test"};

    //TODO: Add query banks for all emotion triggers and actual functionality to emotions
    //All Trigger banks need to be a uniform length to prevent seg faults
    //int nTwo = 1;
    const char *emotionTriggersJoy      [nOne] = {"Happy"};
    const char *emotionTriggersSad      [nOne] = {"Sad"};
    const char *emotionTriggersMad      [nOne] = {"Mad"};
    const char *emotionTriggersScared   [nOne] = {"Scared"};
    const char *emotionTriggersPeace    [nOne] = {"Peaceful"};
    const char *emotionTriggerPowerful  [nOne] = {"Powerful"};
    
    char *response = malloc(MAX_RESPONSE_SIZE);
    char username[64];
    char password[64];
    char firstChoice[8];
    int  breakOut = 0;
    
    /*
     Reads input for Username value
     
     Password input is hidden
     */
    struct termios oflags, nflags;
    printf("Would you like to log in? y/n: ");
    while (breakOut == 0) {
        scanf("%s", firstChoice);
        
        switch (firstChoice[0]) {
            case 'Y': {
                breakOut = 1;
            }
            case 'y': {
                
                //Doesnt hide user input for username
                printf("Enter your username here: ");
                scanf("%63s", username);
                getchar();
        
                //Password input
                tcgetattr(fileno(stdin), &oflags);
                nflags = oflags;
                nflags.c_lflag &= ~ECHO;
                nflags.c_lflag |= ECHONL;
                
                if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
                    perror("tcsetattr");
                    return EXIT_FAILURE;
                }
                
                printf("Enter Password: ");
                
                fgets(password, sizeof(password), stdin);
                if ((strlen(password) > 0) && (password[strlen(password) - 1] == '\n')) {
                    password [strlen(password) - 1] = '\0';
                }
                
                if (tcsetattr(fileno(stdin), TCSANOW, &oflags)) {
                    perror("tcsetattr");
                    return EXIT_FAILURE;
                }
                breakOut = 1;
                break;
            }
            case 'N': {
                
            }
            case 'n': {
                printf("Logging out...");
                exit(1);
            }
            default: {
                printf("\nInvalid input\n"
                       "Would you like to log in? y/n ");
                break;
            }
        }
    }
    breakOut = 0;
    
    EMOTION testEmotion = { //The grossly oversimplified version of STATE (Now TRUE_EMOTION
                           //, because STATE wasn't cmplex enough; EMOTION
        0.0, //Sad
        0.0, //Joy
        0.0, //Power
        0.0, //Peace
        0.0, //Mad
        0.0, //Scare
    };
    
    TRUE_EMOTION testTrueEmotion = { //Remember how small and simple EMOTION was? Yeah. 6 to 72 emotions
                                    //Fun Fact: Mac users can triple tap a term to look for its definition
                                   //Just not in Xcode, because Apple is no fun
        //Sad Block L1
        0.0, //Bashful
        0.0, //Stupid
        0.0, //Miserable
        0.0, //Inadequate
        0.0, //Inferior
        0.0, //Apathetic
        //...L2
        0.0, //Guilty
        0.0, //Ashamed
        0.0, //Depressed
        0.0, //Lonely
        0.0, //Bored
        0.0, //Sleepy
        
        //Joy Block L1
        0.0, //Daring
        0.0, //Fascinating
        0.0, //Stimulating
        0.0, //Amused
        0.0, //Extravagant
        0.0, //Delightful
        //...L2
        0.0, //Excited
        0.0, //Sexy
        0.0, //Energetic
        0.0, //Playful
        0.0, //Creative
        0.0, //Aware
        
        //Power Block L1
        0.0, //Confident
        0.0, //Intelligent
        0.0, //Worthwhile
        0.0, //Valuable
        0.0, //Satisfied
        0.0, //Cheerful
        //...L2
        0.0, //Faithful
        0.0, //Important
        0.0, //Hopeful
        0.0, //Appreciated
        0.0, //Respected
        0.0, //Proud

        //Peace Block L1
        0.0, //Pensive
        0.0, //Relaxed
        0.0, //Responsive
        0.0, //Serene
        0.0, //Sentimental
        0.0, //Thankful
        //...L2
        0.0, //Content
        0.0, //Thoughtful
        0.0, //Intimate
        0.0, //Loving
        0.0, //Trusting
        0.0, //Nurturing

        //Mad Block L1
        0.0, //Skeptical
        0.0, //Irratated
        0.0, //Furious
        0.0, //Frustrated
        0.0, //Selfish
        0.0, //Jealous
        //...L2
        0.0, //Critical
        0.0, //Hateful
        0.0, //Rage
        0.0, //Angry
        0.0, //Hostile
        0.0, //Hurt

        //Scared Block L1
        0.0, //Bewildered
        0.0, //Discouraged
        0.0, //Insignificant
        0.0, //Weak
        0.0, //Foolish
        0.0, //Embarrassed
        //...L2
        0.0, //Rejected
        0.0, //Confused
        0.0, //Helpful
        0.0, //Submissive
        0.0, //Insecure
        0.0, //Anxious

    };
    
    RESPONSES testResponses = {
        0, //response
        0, //Time (query)
        0, //Fibo (query)
        0, //joy
        0, //mad
        0, //sad
        0, //scare
        0, //peace
        0, //power
        0, //Debug command
    };
    //Create a database of established users, have structs created for each or one via a wildcard
    struct User *past = establishUsers("Sichais", "password");
    
    //New struct to be compared to User past
    struct User *user = createUser(username, password);
    struct Companion *assist = wakeUp("\0", testEmotion, testTrueEmotion, testResponses);
    
    int logBool = logIn(user, past);
    
    if (logBool == 0) {
        printf("Invalid credentials, exitting program");
        exit(1);
    }
    
    printf("Loading...\n");
    sleep(1);
    printf("Welcome %s"
           "\n\n"
           "Please enter the name of your assistant: ", user -> username);
    
    fgets(assist -> name, MAX_RESPONSE_SIZE, stdin);
    if ((strlen(assist -> name) > 0) && (assist -> name[strlen(assist -> name) - 1])) {
        assist -> name[strlen(assist -> name) -1] = '\0';
    }
    //Sorta redundant, but just in case I need something like it
    switch (assist -> name[0]) {
        case '\n': {
            printf("You didn't enter anything, ");
        }
        default: {
            break;
        }
    }
    printf("Hello my name is %s\n", assist -> name);

    printf("Please enter a command, Or say 'Log out' to exit\n");
    int responseEnd1 = strcasecmp("Log Out", response);
    while (responseEnd1 != 0) {
        printf(">");
        
        fgets(response, MAX_RESPONSE_SIZE, stdin);
        if ((strlen(response) > 0) && (response[strlen(response) - 1] == '\n')) {
            response [strlen(response) - 1] = '\0';
        }

        assist -> allResponses.responseBool = checkQuery(assist, response, assist);

        checkJoy    (*emotionTriggersJoy,     nTwo, response, assist);
        checkSad    (*emotionTriggersSad,     nTwo, response, assist);
        checkMad    (*emotionTriggersMad,     nTwo, response, assist);
        checkScared (*emotionTriggersScared,  nTwo, response, assist);
        checkPower  (*emotionTriggerPowerful, nTwo, response, assist);
        checkPeace  (*emotionTriggersPeace,   nTwo, response, assist);
        
        if (assist -> allResponses.joyBool          == 1) {
            raiseJoy(assist);
        } else if (assist -> allResponses.madBool   == 1) {
            raiseMad(assist);
        } else if (assist -> allResponses.sadBool   == 1) {
            raiseSad(assist);
        } else if (assist -> allResponses.scareBool == 1) {
            raiseScared(assist);
        } else if (assist -> allResponses.powerBool == 1) {
            raisePower(assist);
        } else if (assist -> allResponses.peaceBool == 1) {
            raisePeace(assist);
        }

        if (assist -> allResponses.timeBool == 1) {
            printf("The current time is: %s", asctime(info));
            assist -> allResponses.timeBool = 0;
        }
        if (assist -> allResponses.fiboBool == 1) {
            int i = 0;
            int fiboLimit = 0;
            printf("Alright, how far do you want the sequence to go: ");
            scanf("%d", &fiboLimit);
            for (i = 0; i < fiboLimit; i++) {
                printf("%d \n", fibonacci(i));
            }
            assist -> allResponses.fiboBool = 0;
        }
        //Find a way to cut this down
        if (assist -> allResponses.debugBool == 1) { //72 emotions + 1 line for each for readability
            printf("Debug code entered: \n"         //and needing to reference those same 72 emotions
                   "Bashful:          %f\n"        //really makes the line count skyrocket
                   "Stupid:           %f\n"
                   "Miserable:        %f\n"
                   "Inadequate:       %f\n"
                   "Inferior:         %f\n"
                   "Apathetic:        %f\n"
                   "Guilty:           %f\n"
                   "Ashamed:          %f\n"
                   "Depressed:        %f\n"
                   "Lonely:           %f\n"
                   "Bored:            %f\n"
                   "Sleepy:           %f\n"
                   "Daring:           %f\n"
                   "Fascinating:      %f\n"
                   "Stimulating:      %f\n"
                   "Amused:           %f\n"
                   "Extravagant:      %f\n"
                   "Delightful:       %f\n"
                   "Excited:          %f\n"
                   "Sexy:             %f\n"
                   "Energetic:        %f\n"
                   "Playful:          %f\n"
                   "Creative:         %f\n"
                   "Aware:            %f\n"
                   "Confident:        %f\n"
                   "Intelligent:      %f\n"
                   "Worthwhile:       %f\n"
                   "Valuable:         %f\n"
                   "Satisfied:        %f\n"
                   "Cheerful:         %f\n"
                   "Faithful:         %f\n"
                   "Important:        %f\n"
                   "Hopeful:          %f\n"
                   "Appreciated:      %f\n"
                   "Respected:        %f\n"
                   "Proud:            %f\n"
                   "Pensive:          %f\n"
                   "Relaxed:          %f\n"
                   "Responsive:       %f\n"
                   "Serene:           %f\n"
                   "Sentimental:      %f\n"
                   "Thankful:         %f\n"
                   "Content:          %f\n"
                   "Thoughtful:       %f\n"
                   "Intimate:         %f\n"
                   "Loving:           %f\n"
                   "Trusting:         %f\n"
                   "Nurturing:        %f\n"
                   "Skeptical:        %f\n"
                   "Irratated:        %f\n"
                   "Furious:          %f\n"
                   "Frustrated:       %f\n"
                   "Selfish:          %f\n"
                   "Jealous:          %f\n"
                   "Critical:         %f\n"
                   "Hateful:          %f\n"
                   "Rage:             %f\n"
                   "Angry:            %f\n"
                   "Hostile:          %f\n"
                   "Hurt:             %f\n"
                   "Bewildered:       %f\n"
                   "Discouraged:      %f\n"
                   "Insignificant:    %f\n"
                   "Weak:             %f\n"
                   "Foolish:          %f\n"
                   "Embarrassed:      %f\n"
                   "Rejected:         %f\n"
                   "Confused:         %f\n"
                   "Helpful:          %f\n"
                   "Submissive:       %f\n"
                   "Insecure:         %f\n"
                   "Anxious:          %f\n",
                       assist -> currentTrueEmotion.bashful,
                       assist -> currentTrueEmotion.stupid,
                       assist -> currentTrueEmotion.miserable,
                       assist -> currentTrueEmotion.inadequate,
                       assist -> currentTrueEmotion.inferior,
                       assist -> currentTrueEmotion.apathetic,
                       assist -> currentTrueEmotion.guilty,
                       assist -> currentTrueEmotion.ashamed,
                       assist -> currentTrueEmotion.depressed,
                       assist -> currentTrueEmotion.lonely,
                       assist -> currentTrueEmotion.bored,
                       assist -> currentTrueEmotion.sleepy,
                       assist -> currentTrueEmotion.daring,
                       assist -> currentTrueEmotion.fascinating,
                       assist -> currentTrueEmotion.stimulating,
                       assist -> currentTrueEmotion.amused,
                       assist -> currentTrueEmotion.extravagant,
                       assist -> currentTrueEmotion.delightful,
                       assist -> currentTrueEmotion.excited,
                       assist -> currentTrueEmotion.sexy,
                       assist -> currentTrueEmotion.energetic,
                       assist -> currentTrueEmotion.playful,
                       assist -> currentTrueEmotion.creative,
                       assist -> currentTrueEmotion.aware,
                       assist -> currentTrueEmotion.confident,
                       assist -> currentTrueEmotion.intelligent,
                       assist -> currentTrueEmotion.worthwhile,
                       assist -> currentTrueEmotion.valuable,
                       assist -> currentTrueEmotion.satisfied,
                       assist -> currentTrueEmotion.cheerful,
                       assist -> currentTrueEmotion.faithful,
                       assist -> currentTrueEmotion.important,
                       assist -> currentTrueEmotion.hopeful,
                       assist -> currentTrueEmotion.appreciated,
                       assist -> currentTrueEmotion.respected,
                       assist -> currentTrueEmotion.proud,
                       assist -> currentTrueEmotion.pensive,
                       assist -> currentTrueEmotion.relaxed,
                       assist -> currentTrueEmotion.responsive,
                       assist -> currentTrueEmotion.serene,
                       assist -> currentTrueEmotion.sentimental,
                       assist -> currentTrueEmotion.thankful,
                       assist -> currentTrueEmotion.content,
                       assist -> currentTrueEmotion.thoughtful,
                       assist -> currentTrueEmotion.intimate,
                       assist -> currentTrueEmotion.loving,
                       assist -> currentTrueEmotion.trusting,
                       assist -> currentTrueEmotion.nurturing,
                       assist -> currentTrueEmotion.skeptical,
                       assist -> currentTrueEmotion.irratated,
                       assist -> currentTrueEmotion.furious,
                       assist -> currentTrueEmotion.frustrated,
                       assist -> currentTrueEmotion.selfish,
                       assist -> currentTrueEmotion.jealous,
                       assist -> currentTrueEmotion.critical,
                       assist -> currentTrueEmotion.hateful,
                       assist -> currentTrueEmotion.rage,
                       assist -> currentTrueEmotion.angry,
                       assist -> currentTrueEmotion.hostile,
                       assist -> currentTrueEmotion.hurt,
                       assist -> currentTrueEmotion.bewildered,
                       assist -> currentTrueEmotion.discouraged,
                       assist -> currentTrueEmotion.insignificant,
                       assist -> currentTrueEmotion.weak,
                       assist -> currentTrueEmotion.foolish,
                       assist -> currentTrueEmotion.embarrassed,
                       assist -> currentTrueEmotion.rejected,
                       assist -> currentTrueEmotion.confused,
                       assist -> currentTrueEmotion.helpful,
                       assist -> currentTrueEmotion.submissive,
                       assist -> currentTrueEmotion.insecure,
                       assist -> currentTrueEmotion.anxious);
        }
        responseEnd1 = strcasecmp("Log Out", response);
        //TODO Add emotional state dependant regex
    }
    printf("Shutting down...");
    //Frees up memory assist was using
    shutDown(assist);
    
    return 0;
}
//MAIN FUNCTION END
