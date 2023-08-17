#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define NO_OBJECT_ERROR 1
//#define NO_ACCOUNT_WANTED 20
#define MAX_ACCOUNTS_IN_BANKING_SYSTEM 20
#define MAX_ACCOUNT_OWNER_NAME_LENGTH 40

/* Exit codes:
1 - NO_OBJECT_ERROR
20 - Didn't want a bank account.
*/

/*
OOP Principles Gleaned from Washington article: http://staff.washington.edu/gmobus/Academics/TCES202/Moodle/OO-ProgrammingInC.html
Program Methods inspired by: http://www.cprogrammingnotes.com/question/banking-system.html
*/

/* Account Abstract Data Type (ADT). Has a numeric balance, numeric ID, and string of
owner's name. */
struct Account {
	float accountBalance;
	int accountId;
	char ownerFullName[MAX_ACCOUNT_OWNER_NAME_LENGTH];
};

void createCustomerAccounts(struct Account[], int);
void displayAllAccounts(struct Account[], int);
int searchForAccount(struct Account[], int, int);
void depositInAccount(struct Account[], int, int, float);
void withdrawFromAccount(struct Account[], int, int, float);

int main() {
	struct Account accountArray[MAX_ACCOUNTS_IN_BANKING_SYSTEM];
    int num_accounts, menuChoice, accountId, index;
	float amount;

    printf("Banking System\n\n");
    printf("How many customer account records do you want to create? 20 is the maximum.\n");
    scanf("%d", &num_accounts);
	createCustomerAccounts(accountArray, num_accounts);
    do
    {

        printf("\nBanking System Menu - What would you like to do?\n");
        printf("1 - Display all records.\n");
        printf("2 - Search for a record.\n");
        printf("3 - Deposit amount.\n");
        printf("4 - Withdraw amount.\n");
        printf("0 - Exit.\n");
        printf("\nPress # of Preferred Action: \n");
        scanf("%d", &menuChoice);
        switch (menuChoice)
        {
            case 1:
                displayAllAccounts(accountArray, num_accounts);
                break;
            case 2:
                printf("Enter account ID to search : ");
                scanf("%d", &accountId);
                index = searchForAccount(accountArray, num_accounts, accountId);
                if (index ==  - 1)
                {
                    printf("Record not found : ");
                }
                else {
                    printf("Account ID: %d\nName: %s\nBalance: %.2f\n",
                        accountArray[index].accountId, accountArray[index].ownerFullName,
                        accountArray[index].accountBalance);
                }
                break;
            case 3:
                printf("Enter account ID: ");
                scanf("%d", &accountId);
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);
                depositInAccount(accountArray, num_accounts, accountId, amount);
                break;
            case 4:
                printf("Enter account ID: ");
                scanf("%d", &accountId);
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                withdrawFromAccount(accountArray, num_accounts, accountId, amount);
        }
    }
    while (menuChoice != 0);

    return 0;
	
}

void createCustomerAccounts(struct Account accountList[MAX_ACCOUNTS_IN_BANKING_SYSTEM], int accountCount)
{
	//iterator gets initialized to zero. While it's less than accountCount, add to it.
    int iterator;
    for (iterator = 0; iterator < accountCount; iterator++)
    {
		char c;
		//Record # is 1, then 2, then 3...
        printf("\nEnter data for Record #%d", iterator + 1);
        printf("\nEnter Legal Name: ");
		//1st account in the list (with index 0) is given the account ID supplied by user.
        //scanf bad
		//scanf("%10[0-9a-zA-Z ]", accountList[iterator].ownerFullName);
		//scanf("%s", accountList[iterator].ownerFullName);
		//fgets(placeholder, 30, stdin);
		//fflush(stdin) isn't fully supported on all platforms, so let's use a while loop to get rid
		//of anything in stdin per https://c-faq.com/stdio/stdinflush2.html .
		while((c = getchar()) != '\n' && c != EOF)
		/* discard */ ;
		fgets(accountList[iterator].ownerFullName, 20, stdin);
		//getline(&accountList[iterator].ownerFullName, 45, stdin);
		//fprintf(stderr, "my %s has %d chars\n", "string format", 30);
		printf("%s\n", accountList[iterator].ownerFullName);
		//fprintf(stderr, "my %s has %d chars\n", "string format", 30);
		//stdin is then flushed.
        fflush(stdout);
        printf("Enter starting balance: \n");
		scanf("%f", &accountList[iterator].accountBalance);
		
        //gets(list[iterator].ownerFullName);
        accountList[iterator].accountId = iterator;
		printf("\nAccount ID: %d", iterator);
    } 
}

void displayAllAccounts(struct Account accountList[MAX_ACCOUNTS_IN_BANKING_SYSTEM], int s)
{
    int i;

    printf("\n\nAccount Number\t\tAccount Owner\t\tBalance\n");
    for (i = 0; i < s; i++)
    {
        printf("%d\t\t\t%s\t\t\t%.2f\n", accountList[i].accountId, accountList[i].ownerFullName,
            accountList[i].accountBalance);
    } 
}

int searchForAccount(struct Account accountList[MAX_ACCOUNTS_IN_BANKING_SYSTEM], int s, int allegedAccountId)
{
    int i;

    for (i = 0; i < s; i++)
    {
        if (accountList[i].accountId == allegedAccountId)
        {
            return i;
        } 
    }
    return  - 1;
}

void depositInAccount(struct Account accountList[], int s, int number, float amountToDeposit)
{
    int i = searchForAccount(accountList, s, number);
    if (i ==  - 1)
    {
        printf("Record not found");
    } 
    else
    {
        accountList[i].accountBalance += amountToDeposit;
    }
}

void withdrawFromAccount(struct Account accountList[], int s, int number, float amountToWithdraw)
{
    //int placeholder;
	int i = searchForAccount(accountList, s, number);
    if (i ==  - 1)
    {
        printf("Record not found\n");
    } 
    else if (accountList[i].accountBalance < amountToWithdraw)
    {
        printf("Insufficient balance\n");
		//scanf("%d", placeholder);
    }
    else
    {
        accountList[i].accountBalance -= amountToWithdraw;
    }
}
