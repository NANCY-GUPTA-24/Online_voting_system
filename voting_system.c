#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CANDIDATES 10
#define MAX_VOTERS 100
#define MAX_NAME_LENGTH 50
#define MAX_VOTER_ID_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
typedef struct
 {
    char name[MAX_NAME_LENGTH];
    int votes;
    char symbol;
    // Symbol associated with the candidate
}
 Candidate;
typedef struct
{
    char voter_id[MAX_VOTER_ID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    int has_voted;
}
Voter;
Candidate candidates[MAX_CANDIDATES];
Voter voters[MAX_VOTERS];
int candidate_count = 0;
int voter_count = 0;
char symbols[10] = {'!', '@', '#', '$', '%', '^', '&', '*', '~', '+'};
int symbolTaken[10] = {0};
// Track which symbols are taken
void printBorder()
{


    printf("\t\n\t");
}

void showWelcomeMessage()
{
    printBorder();
    printf("====================================================================\n\t");
    printf("========================= ===========================================\n\t");
    printf("*                                                                                                                                                *\n\t");
    printf("*                                                                                                                                                *\n\t");
    printf("*                                                                                                                                                *\n\t");
    printf("*                          ONLINE VOTING SYSTEM                                                                         *\n\t");
    printf("*                                                                                                                                              *\n\t");
   printf("*                      WELCOME TO THE VOTING SYSTEM                                                         *\n\t");

    printf("*                     Please select an option to begin               *\n\t");

    printf("*                                                                    *\n\t");
    printf("*                                                                    *\n\t");
    printf("*                                                                    *\n\t");
   printf("====================================================================\n\t");
     printf("====================================================================\n\t");


    printBorder();
}


//admin login
void admin_login()
{
    const char *admin_username = "sdf";

    const char *admin_password = "project";

    char username[20], password[20];

    printf("Admin Login\n");

    //enter the username
    printf("Username: ");

    scanf("%s", username);


    printf("Password: ");

    scanf("%s", password);

    if (strcmp(username, admin_username) != 0 || strcmp(password, admin_password) != 0)
        {

        printf("\n\033[0;31m INVALID CREDENTIAL !!\033[0m\n");
        exit(1);
    }


    printf("\033[0;32m Login successful!!\033[0m\n");
}

void add_candidate()
{

    if (candidate_count >= MAX_CANDIDATES)
        {

        printf("Cannot add more candidates.\n");

        return;
    }
    int symbol_choice;

    printf("\033[0;34m Available Symbols:\033[0m \n");

    for (int i = 0; i < 10; i++)
        {
        if (!symbolTaken[i])
        {

            printf("%d. %c\n", i + 1, symbols[i]);
        }
    }

    printf("Select a symbol for the new candidate (1-10): ");


    scanf("%d", &symbol_choice);

    if (symbol_choice < 1 || symbol_choice > 10 || symbolTaken[symbol_choice - 1])
        {

        printf("Invalid or taken symbol. Please select a different symbol.\n");
        return;
    }

    symbolTaken[symbol_choice - 1] = 1;

     // Mark the symbol as taken

    printf("Enter candidate name: ");
    scanf("%s", candidates[candidate_count].name);

    candidates[candidate_count].symbol = symbols[symbol_choice - 1];

    candidates[candidate_count].votes = 0;

    candidate_count++;

    printf("Candidate added successfully!\n");
}

void remove_candidate()
 {

    char name[MAX_NAME_LENGTH];

    printf("Enter candidate name to remove: ");

    scanf("%s", name);


    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
            {
            symbolTaken[candidates[i].symbol - '!' ] = 0;
            // Free the symbol
            for (int j = i; j < candidate_count - 1; j++)
             {
                candidates[j] = candidates[j + 1];
            }
            candidate_count--;
            printf("Candidate removed successfully!\n");
            return;       }    }
  printf("\033[0;31m Candidate not found!\n \033[0m\n");
}


void view_results()

 {   printf("Voting Results:\n");

    for (int i = 0; i < candidate_count; i++)
        {

        printf("Candidate: %s, Symbol: %c, Votes: %d\n", candidates[i].name, candidates[i].symbol, candidates[i].votes);
    }
}
void register_voter()
{
    if (voter_count >= MAX_VOTERS)
        {
        printf("Cannot register more voters.\n");
        return;
    }

    printf("Enter voter ID: ");
    scanf("%s", voters[voter_count].voter_id);

    //password
    printf("Enter password: ");
    scanf("%s", voters[voter_count].password);

    voters[voter_count].has_voted = 0;

    voter_count++;

    printf("Voter registered successfully!\n");
}

int voter_results()

{

    int maxVotes = 0;

    int winnerIndex = -1;

    int winnerFrequency = 0;

    for (int i = 0; i < 5; i++)
        {

        if (candidates[i].votes > maxVotes)
        {
            maxVotes = candidates[i].votes;
            winnerIndex = i;
        }
    }

    for (int i = 0; i < 5; i++)

    {
        if (candidates[i].votes == maxVotes)
        {
            winnerFrequency++;
        }
    }
    printf("\n-----RESULT-----\n");
    //for the result of election

    if (winnerFrequency > 1)
        {

        printf("No candidate has majority votes\n");
    }
     else if (winnerIndex != -1)
    {

        printf("The winner is: %s\nCandidate Symbol: %c\nwith %d votes!\n", candidates[winnerIndex].name, candidates[winnerIndex].symbol, maxVotes);
    } else
    {
        printf("No winner\n");
        //all have same votes
    }
}

int voter_login()
 {
    char voter_id[MAX_VOTER_ID_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("Voter Login\n");

    printf("Voter ID: ");
    scanf("%s", voter_id);

    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < voter_count; i++)
        {
        if (strcmp(voters[i].voter_id, voter_id) == 0 && strcmp(voters[i].password, password) == 0)
        {
            if (voters[i].has_voted)
             {
                printf("You have already voted.\n");
                return -1;
                 // Voter has already voted
            }
            return i;
            // Return voter index
        }
    }

    printf("Invalid credentials!\n");
    return -1;
}

void cast_vote(int voter_index) {
    printf("Candidates:\n");


    for (int i = 0; i < candidate_count; i++)
        {
        printf("%d. %s (Symbol: %c)\n", i + 1, candidates[i].name, candidates[i].symbol);
    }

    int choice;


    printf("Select candidate number to vote: ");
    scanf("%d", &choice);


    if (choice < 1 || choice > candidate_count)
        {

        printf("Invalid choice!\n");
        return;
    }

    candidates[choice - 1].votes++;

    voters[voter_index].has_voted = 1;

    printf("Vote cast successfully for %s!\n", candidates[choice - 1].name);
}

void display_admin_menu() {
    printf("\nAdmin Menu :\n");


    printf("1. Add Candidate\n");

    //admin to add the new candidate


    printf("2. Remove Candidate\n");

    //remove the candidate


    printf("3. View Results\n");
    //result of the voting system
  printf("4. Register Voter\n");
    //to register the voters


    printf("5. Exit\n");
    //exit


    printf("Select an option: ");
}

//voter menu
void display_voter_menu()
{

    printf("\nVoter Menu:\n");

    printf("1. Cast Vote\n");

    printf("2. View Results\n");

    printf("3. Exit\n");

    printf("Select an option: ");
}

void display_candidate_details()
{
    printf("NAME: YOGI ADITYA NATH\n");
    printf(" \n");


    printf("AGE:52 YEARS\n");
    printf("\n");


    printf("PARTY : BJP\n");
    printf("\n");


    printf("EXPERIENCE:26 years\n");
    printf("\n");
   printf("MOTTO- To provide jobs to youth and decrease unemployment\n");
    printf("To make UP a crime free state\n");
    printf("To promote UP tourism\n");

    printf("NET WORTH : 1.5 CRORE\n");

    printf("\n");
    printf("\n");

    printf("--------------------------------------------------------------------\n");

    printf("\n");

    printf("NAME OF CANDIDATE : Nitish Kumar\n");
    printf(" \n");


    printf("AGE:73 years\n");
    printf("\n");

    printf("PARTY :Coalition government\n");
    printf("\n");


    printf("Experience:28 years\n");
    printf("\n");


    printf("Promises - To provide government jobs to youth\n");

    printf("To provide 24*7 running tap water\n");

    printf("\n");
    printf("To supply 24*7 electricity in every village\n");

    printf("\n");

    printf("NET WORTH: 1.64 CRORE \n");
    printf("\n");

    printf("--------------------------------------------------------------------\n");
    printf("\n");

    printf("NAME OF CANDIDATE : Uddhav Balasaheb Thackeray.\n");
    printf(" \n");


    printf("AGE:64 YEARS\n");
    printf("\n");


    printf("PARTY :Shiv Sena (Founded by his father, Bal Thackeray).\n");
    printf("\n");


    printf("POSITION: Former Chief Minister of Maharashtra (2019–2022).\n");
    printf("\n");


    printf("LEADERSHIP : Took over as Shiv Sena leader after the death of his father, Bal Thackeray, \n");

    printf("\n");


    printf("Political Stance: Known for his pro-Hindu ideology, regionalism, and focus on the welfare of Maharashtra.\n");
    printf("\n");



    printf("NET WORTH:143 CRORE\n");
    printf("\n");



    printf("NO. OF INCOME SOURCES: \n");
    printf("\n");




    printf("--------------------------------------------------------------------\n");
    printf("\n");



    printf("NAME OF CANDIDATE : Ashok Gehlot.\n");
    printf(" \n");



    printf("AGE:75 YEARS\n");
    printf("\n");
    printf("PARTY : Indian National Congress (INC).\n");
    printf("\n");


    printf("CURRENT POSITION: Chief Minister of Rajasthan (third term, since December 2018).\n");
    printf("\n");
   printf(" He has consistently championed policies aimed at the welfare of marginalized communities, including farmers, women, Dalits, and backward classes.\n");
  printf(" His government has focused on social justice, healthcare, education, and rural development.\n");
    printf("\n");


    printf("CIVIL CASES:\n");
    printf("\n");



    printf("NET WORTH: 12 CRORE\n");
    printf("\n");
  printf("NO. OF INCOME SOURCES: \n");

     printf("--------------------------------------------------------------------\n");
    printf("\n");
    return ;


 printf("NAME OF CANDIDATE : Shri nayab Singh saini\n");
    printf(" \n");
    printf("AGE:54 YEARS\n");
    printf("\n");
    printf("PARTY : Bharti janta party\n");
    printf("\n");


    printf("CURRENT POSITION: Chief Minister .\n");
    printf("\n");
  printf(" Saini is a notable BJP leader from Other Backward Classes (OBC) in Haryana.\n");
    printf(" His government has focused on social justice, healthcare, education, and rural development.\n");
   printf("\n");
   printf("CIVIL CASES: not really\n");
    printf("\n");
    printf("NET WORTH: 5.6CRORE\n");
    printf("\n");
   printf("--------------------------------------------------------------------\n");
    printf("\n");
    return ;

}



int main() {

    int option, voter_index;


    // Show the welcome page with start option

    showWelcomeMessage();

    printf("1. Start\n");

    printf("Select an option to begin: ");

    scanf("%d", &option);

    if (option != 1)
        {

        printf("Invalid option! Exiting.\n");
        exit(1);
    }


    // Main program loop for user options

    while (1)

        {
 printf("\n\033[0;35mWelcome to Voting System\033[0m\n\n");
        printf("1. Admin Login\n");
        printf("2. Voter Login\n");
        printf("3.Candidate details\n");
        printf("4. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);

        switch (option)
        {

            case 1:
                admin_login();
                while (1) {

                    display_admin_menu();
                    scanf("%d", &option);


                    switch (option)
                    {
                        case 1:
                            add_candidate();
                            break;


                        case 2:
                            remove_candidate();
                            break;
                        case 3:
                            view_results();
                            break;
                        case 4:
                            register_voter();
                            break;


                        case 5:
                            break;



                            // Exit admin menu
                        default:
                            printf("Invalid option!\n");
                    }

                    if (option == 5)

                        {
                        break;
                        // Exit admin login
                    }
                }

                break;

            case 2:
                voter_index = voter_login();


                if (voter_index != -1) {

                    while (1)



                        {
                        display_voter_menu();
                        scanf("%d", &option);



                        switch (option)
                         {
                            case 1:
    cast_vote(voter_index);
                                break;


                            case 2:
                                voter_results();
                                break;
                                case 3:
                                break;

                            // Exit voter menu
                            default:

                                printf("Invalid option!\n");
                        }

                        if (option == 3) {
                            break;
                              // Exit voter login
                        }

                 }

                break;


            case 3:
            isplay_candidate_details();



            case 4:
                exit(0);
         default:
                printf("Invalid option!\n");

        }

    }
    return 0;
}
}
