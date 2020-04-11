#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include <ctype.h>
static int user_count=0;
static int car_count=0;
struct User{
    int userId;
    char *fname[15];
    char *lname[15];
    char *pass[10];
    char *mobile[10];
    int usrroute;
    int startpt;
    int points;
}user[20];

struct UserRef{
    int carId;
    char isReg;
    int isPass;
}userref[20];

struct RouteMap{
    char *route;
    char *stop[10];
}routeMap[10];

struct Car{
    int ownerId;
    int seatCount;
    int passId[10];
    int seatavail;
    int route;
    int stop;
}car[50];

void create_route()
{
    routeMap[0].route = "Route 1";
    routeMap[0].stop[0] = "1. Harsha Hotel";
    routeMap[0].stop[1] = "2.Srinagar Garden";
    routeMap[0].stop[2] = "3.Ramdev Hotel";
    routeMap[0].stop[3] = "4. Channamma Circle";
    routeMap[0].stop[4] = "5. Fish Market";
    routeMap[0].stop[5] = "6. 2nd Gate";
    routeMap[1].route = "Route 2";
    routeMap[1].stop[0] = "1. Guard Room";
    routeMap[1].stop[1] = "2. Mutaga, Nilaji";
    routeMap[1].stop[2] = "3. Kudachi";
    routeMap[1].stop[3] = "4. Gandhi Nagar";
    routeMap[1].stop[4] = "5. Fort Circle";
}


void display_route()
{
    int k;
    for(k=0;k<10;k++)
    {
        if(routeMap[k].route!=NULL)
        {
            printf("%s\n",routeMap[k].route);
        }
        else
        break;
    }
}


void display_stops(int routenum)
{
    int l;
    if(routeMap[routenum-1].route!=NULL)
    {
        for(l=0;l<15;l++)
        {
            if(routeMap[routenum-1].stop[l]!=NULL)
            {
                printf("%s\n",routeMap[routenum-1].stop[l]);
            }
            else
            break;
        }
    }
}

void welcome()
{
    int ch=0;
    char name[20], password[10];
    printf("\nEnter your choice:\n1.Log In:\t2.Sign Up:\n");
    scanf("%d",&ch);
    switch (ch)
    {
        case 1: login();
                printf("\nPress any key to continue");
                getch();
                break;

        case 2: signup();

        default:printf("\nPress any key to continue");
                getch();
                break;
    }
}


void login()
{
    int userid=0,i;
    char *pswd[10];
    int ifvalid=0;
    char ch,pasword[10];
    printf("\nEnter User Id: ");
    scanf("%d",&userid);
    printf("\nEnter Password: ");

    for(i=0;i<8;i++)
    {
        ch = getch();
        if(ch==13)
        break;
         if (ch == 8) /*ASCII value of BACKSPACE*/
      {
         putch('b');
         putch(NULL);
         putch('b');
         i--;
         continue;
      }
        pasword[i] = ch;
        ch = '*' ;
        printf("%c",ch);
    }
    pasword[i]='\0';
    strcpy(&pswd,pasword);

    ifvalid=validate(userid,&pswd);

    if(ifvalid==0)
    {
        clrscr();
        register_user(userid-1);

    }
    else
    {

        login();
    }
}


int validate(int userid,char *pswd)
{
    char *passwd=user[userid-1].pass;



    if(!strcmp(pswd,passwd))
    {

        return 0;
    }
    else
    {
        clrscr();
        printf("\nEnter valid credentials\n");
        return 1;
    }
}


void signup()
{
    char ch,pasword[10];
    int i,temp=0,validfname=0,validlname=0,userId=user_count+1;
    printf("\nEnter your details:\n");
    while(validfname==0)
    {
        printf("\nFirst Name:");
        scanf("%s",&user[user_count].fname);
        validfname=checkString(user[user_count].fname);
    }
    while(validlname==0)
    {
        printf("\Last Name:");
        scanf("%s",&user[user_count].lname);
        validlname=checkString(user[user_count].lname);
    }
    printf("\nPassword:");
    for(i=0;i<8;i++)
    {
        ch = getch();
        if(ch==13)
        break;
         if (ch == 8) /*ASCII value of BACKSPACE*/
      {
         putch('b');
         putch(NULL);
         putch('b');
         i--;
         continue;
      }
        pasword[i] = ch;
        ch = '*' ;
        printf("%c",ch);
    }
    pasword[i]='\0';
    strcpy(user[user_count].pass,pasword);

    while(temp==0)
    {
        printf("\nMobile No: ");
        scanf("%s",&user[user_count].mobile);
        temp=checkDigit(user[user_count].mobile);
    }
    printf("\nRoute details:\n");
    display_route();
    printf("\nSelect Route: ");
    scanf("%d",&user[user_count].usrroute);
    printf("\nStarting points for Route %d :\n",user[user_count].usrroute);
    display_stops(user[user_count].usrroute);
    printf("\nSelect Starting Point:");
    scanf("%d",&user[user_count].startpt);
    user[user_count].userId = userId;
    display_userdetails(user_count);
    printf("Please note your UID and use it for Login\n");
    writeDisk();
    user_count++;
}



int checkString(char *str)
{
    char temp[20];
    int i;
    strcpy(temp,str);
    char *e;
    e=temp;

    for(i=0;temp[i]!='\0';i++)
    {

       if(!((temp[i] >= 97 && temp[i] <= 122) || (temp[i] >= 65 && temp[i] <= 90)))
        {
          printf("Enter only characters");
          return 0;
        }
    }
    return 1;
}


int checkDigit(char *str)
{
    char temp[15];
    int i;
    strcpy(temp,str);
    for(i=0;temp[i]!='\0';i++)
    {

        if(!isdigit(temp[i]))
        {
          printf("Enter a valid mobile number");
          return 0;
        }
    }
    if(i!=10)
    {
        printf("Please enter 10 digits\n");
        return 0;
    }
    return 1;
}

void display_userdetails(int userCnt)
{
    int userId = user[userCnt].userId;
    char *fname=&user[userCnt].fname;
    char *lname=&user[userCnt].lname;
    char *mob=&user[userCnt].mobile;
    char *route=routeMap[(user[userCnt].usrroute)-1].route;
    char *stop=routeMap[(user[userCnt].usrroute)-1].stop[(user[userCnt].startpt)-1];
    printf("\n");
    printf("UserId: %d\n",userId);
    printf("FirstName: %s\n",fname);
    printf("LastName: %s \n",lname);
    printf("MobileNumber: %s \n",mob);
    printf("Route: %s \n",route);
    printf("StartPoint: %s \n",stop);
}


void register_user(int user_id)
{
    //clrscr();
    int ch=0;
    printf("\nEnter your choice:\n1.Owner\t2.Passenger\t3.Check Status\t 4.Update Profile\t5.Exit:\n");
    scanf("%d",&ch);
    switch (ch)
    {
        case 1: register_owner(user_id);
                register_user(user_id);
                break;

        case 2: register_passenger(user_id);
                register_user(user_id);
                break;
        case 3: check_status(user_id);
                printf("Press any key to return");
                getch();
                clrscr();
                register_user(user_id);
                break;
        case 4: update_profile(user_id);
                register_user(user_id);
                break;

        case 5: break;

        default:printf("\nPlease enter valid option");
                register_user(user_id);
                break;
    }
}


void register_owner(int user_id)
{
    if(userref[user_id].isReg==NULL)
    {
        userref[user_id].isPass=0;
        printf("Owner name:%s\n",user[user_id].fname);
        printf("Enter the number of seats available\n");
        scanf("%d",&car[car_count].seatCount);
        car[car_count].ownerId=user_id;
        car[car_count].route=user[user_id].usrroute;
        car[car_count].stop=user[user_id].startpt;
        car[car_count].seatavail=car[car_count].seatCount;
        userref[user_id].carId=car_count++;
        userref[user_id].isReg='y';
        user[user_id].points+=10;

        printf("You have entered %d seats for the route %d and stop %d\n",car[car_count-1].seatCount,car[car_count-1].route,car[car_count-1].stop);
        printf("You have successfully registered\nAdded 10 points to your profile\n");
        printf("Total Points: %d\n",user[user_id].points);
        writeUpdate2Disk();
        printf("\nPress any key to continue\n");
        getch();
    }
    else
    {
        printf("You have already registered \n Press any key to continue\n");
        getch();
    }
}

void register_passenger(int user_id)
{
    if(userref[user_id].isReg==NULL)
    {
        int i=0,j=0;
        userref[user_id].isPass=1;
        int route=user[user_id].usrroute;
        int stop=user[user_id].startpt;
        int ts=stop;
        while(ts>0)
        {
            for(i=0;i<15;i++)
            {
                if(car[i].route!=NULL&&car[i].route==route)
                {
                    if(car[i].stop==ts && car[i].seatavail!=0)
                    {
                        userref[user_id].carId=i;
                        car[i].passId[car[i].seatavail]= user_id;
                        car[i].seatavail--;
                        userref[user_id].isReg = 'Y';
                        user[user_id].points+=5;
                        printf("Seat is alloted ,please note the below details:\n");
                        printf("Owner Name:%s\n",user[car[i].ownerId].fname);
                        printf("Owner Number:%s\n",user[car[i].ownerId].mobile);
                        break;
                    }
                }
            }
            ts--;
        }
        if(userref[user_id].isReg==NULL)
        {
            printf("No Cars available for your route currently,please try again later\n");
        }
        else
        {
            printf("you have successfully registered\nAdded 5 points to your profile\n");
            printf("Total Points: %d\n",user[user_id].points);
            writeUpdate2Disk();
            printf("\nPress any key to continue\n");
        getch();
        }
    }
    else
    {
        printf("You have already registered \n Press any key to continue\n");
        getch();
    }
}



void check_status(int user_id)
{
    int j=0;
    if(userref[user_id].isReg==NULL)
    {
        printf("\nPlease register first\n");
    }
    else
    {
        if(userref[user_id].isPass==1)
        {
            printf("You have registered as Passenger\n");
            printf("Car owner : %s\n",user[car[userref[user_id].carId].ownerId].fname);
            printf("Mobile number : %s\n",user[car[userref[user_id].carId].ownerId].mobile);
        }
        else
        {
            printf("You have registered as Owner\n");
            printf("Passengers registered with you:\n");
            for(j=0;j<=car[userref[user_id].carId].seatCount;j++)
            {
                if(car[userref[user_id].carId].passId[j]!=NULL)
                {
                    printf("Passenger %d details:\n",j);
                    printf("Name : %s\n",user[car[userref[user_id].carId].passId[j]].fname);
                    printf("Mobile number : %s\n",user[car[userref[user_id].carId].passId[j]].mobile);
                }
            }
            printf("Seats Available %d\n",car[userref[user_id].carId].seatavail);
        }
    }
}


void update_profile(int user_id)
{
    int ch=0;
    int temp=0;
    printf("\nEnter your choice:\n1.First Name\t2.Last Name\t3.Mobile number\t 4.Route\t5.Start point\t6.Change Password\t7.Exit:\n");
    scanf("%d",&ch);
    switch(ch){
        case 1 :printf("Enter First Name:\n");
                scanf("%s",&user[user_id].fname);
                display_userdetails(user_id);
                break;
        case 2 :printf("Enter Last Name:\n");
                scanf("%s",&user[user_id].lname);
                display_userdetails(user_id);
                break;
        case 3 :
                while(temp==0)
                {
                    printf("\nEnter Mobile No: ");
                    scanf("%s",&user[user_id].mobile);

                    temp=checkDigit(user[user_id].mobile);
                    }

                display_userdetails(user_id);
                break;
        case 4 :display_route();
                printf("Please select New Route:\n");
                scanf("%d",&user[user_id].usrroute);
                display_userdetails(user_id);

        case 5 :display_stops(user[user_id].usrroute);
                printf("Select the stop");
                scanf("%d",&user[user_id].startpt);
                display_userdetails(user_id);
                break;
        case 6 :change_pass(user_id);
                break;
        case 7 :printf("you have pressed exit\n");
               // update_profile(user_id);
                break;
        default :printf("Please enter valid option");
                break;

    }
    writeUpdate2Disk();
}



void change_pass(int user_id)
{
    char pasword[10],ch;
    int i;
    printf("Enter the new password: ");
    for(i=0;i<8;i++)
    {
        ch = getch();
        if(ch==13)
        break;
        pasword[i] = ch;
        ch = '*' ;
        printf("%c",ch);
    }
    pasword[i]='\0';
    strcpy(user[user_id].pass,pasword);
    printf("Password Changed Successfully");

}

void writeDisk()
{
    int i = 0;
    FILE *file = fopen("userDetails.dat", "ab");
    if(&user[user_count].fname!=NULL)
    {
        fwrite(&user[user_count], sizeof(struct User), 1, file);
    }
    fclose(file);
}

void writeUpdate2Disk()
{
    int i = 0;
    FILE *file = fopen("userDetails.dat", "wb");
    for(i=0;i<user_count;i++)
    {
        if(&user[i].fname!=NULL)
        {
            fwrite(&user[i], sizeof(struct User), 1, file);
        }
    }
    fclose(file);
}


void readDisk()
{
    FILE *infile;
    int i=0;
    infile = fopen ("userDetails.dat","r");
    if (infile == NULL)
    {
      fprintf(stderr, "\nError opening userDetails.dat\n\n");
    }
    else
    {
        while(fread (&user[i], sizeof(struct User), 1, infile))
        {
            if(&user[i].fname!=NULL)
            {
                //display_userdetails(i);
                user_count++;
                i++;
            }
            else
            {
                break;
            }
        }
       // printf("%d\n",user_count);
    }
}



void clrscr()
{
    system("@cls||clear");
}


void main()
{
    create_route();
    readDisk();
    for(;;)
    {
        welcome();
        clrscr();
    }
}
