#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 50
#define MAX_SEATS 40
#define MAX_DRIVERS 50
#define MAX_CONDUCTORS 50
#define MAX_TIME_SLOTS 10
#define MAX_ROUTES 20
#define MAX_SCHEDULES_PER_ROUTE 20
#define MAX_NOTIFICATIONS 1000


// Structures
struct time{
    int hour;
    int minute;
};

struct bus {
    char name[50];
    int busIndex;
    int assignedRoute;
    int availableSeats;
    int occupiedSeats;
};

struct driver {
    char name[50];
    int driverIndex;
    int assignedRoute;
    int workHours;
}d[MAX_DRIVERS];

struct conductor {
    char name[50];
    int conductorIndex;
    int assignedRoute;
    int workHours;
};

struct route {
    int routeIndex;
    int numRoute;
    char destination[50];
};

struct notif{
    char recipient[10];
    char message[200];
    struct time timestamp;
}notifications[MAX_NOTIFICATIONS];

struct schedule {
    int numSchedule;
    int numRoute;
    struct time schedules[MAX_SCHEDULES_PER_ROUTE];
    char driverName[50];
    char conductorName[50];
    char busName[50];
};


//changed variable
struct schedule schedules[MAX_SCHEDULES_PER_ROUTE];
int numSchedules;
char driverName[100];
int chosenRoute;
int bookedSeats;


//Global Variables
int addedRoutes=0;
int addedSchedules=0;
int numNotifications = 0;



//Function Declaration

void displayScheduleP(int *p);
void bookSeats();
void sendBookingConfirmation(const char *recipient, const char *busInfo, const char *scheduleInfo);
void addNotification(const char *recipient, const char *message);
void displayNotifications(const char *recipient);
void displayDSchedule(const struct schedule schedules[], int numSchedules, const char *driverName);
void notifyOvertime(int overtimeDIndex);
void notifyAbsence(int absentDIndex, const char *reasonD);
void displayCSchedule(const struct schedule schedules[], int numSchedules, const char *conductorName);
void notifyCOvertime(int overtimeCIndex);
void notifyCAbsence(int absentCIndex, const char *reasonC);
void displayRoutes();
void addRoutes();
void displaySchedules(int *r);
void addSchedule();
void editSchedule();
void displayBuses();
void displayDrivers();
void displayConductors();
void sendScheduleChangeNotification(const char *recipient, const char *role);



//Main Function
int main(){
    int user;
    int choiceD;
    int choiceP;
    int choice;
    int choice1;
    int choice2;
    int choice3;
    int num;
    int absenteeIndex;
    char reason[200];
    int choiceC;
    int numC;
    int absenteeCIndex;
    char reasonC[200];
    int choiceM;

      MainMenu :
      do {
        printf("\tBus Management System\n");
        printf("\t---------------------\n");
        printf("\n\tUser Authentication\n");
        printf("\n\t-------------------\n");
        printf("1. Passenger\n");
        printf("2. Driver\n");
        printf("3. Conductor\n");
        printf("4. Management\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &user);

        switch (user) {

            case 1:
                printf("\n1. Passenger Screen\n");
                printf("2. Notifications\n");
                printf("Choose an option: ");
                scanf("%d", &choiceP);
                    switch(choiceP) {
                        case 1:
                            // Passenger screen function
                            printf("\nDo you want to, \n");
                            printf("1. View Bus Schedule?\n");
                            printf("2. Book a seat?\n");
                            printf("3. Go to main menu?\n");
                            printf("Enter your choice: ");
                            scanf("%d", &choice);

                            if (choice==1){
                                int chosenRoute;
                                printf("\nRoutes\n");
                                displayRoutes();        //Show the route and their destination number
                                printf("Choose the route number:");
                                scanf("%d", &chosenRoute);
                                displaySchedules(&chosenRoute);     //Display the schedule for a particular route.
                            }

                            else if (choice==2) {
                                bookSeats();
                            }
                            else if (choice==3) {
                                printf("Going to main menu...\n");
                                goto MainMenu;
                            }
                            else {
                                printf("Invalid choice. Please select a valid option.\n");
                            }

                            break;

                        case 2:
                            //Show passenger related notifications
                            displayNotifications("passenger");
                            break;

                        default:
                            printf("Invalid choice. Please select a valid option.\n");
                    }
                break;



            case 2:

                printf("1. Driver Screen\n");
                printf("2. Notifications\n");
                printf("Choose an option: ");
                scanf("%d", &choiceD);
                    switch(choiceD) {
                        case 1:

                            // Driver screen function
                            printf("\n1. View Your Schedule\n");
                            printf("2. Mark Attendance\n");
                            printf("3. Go to main menu?\n");
                            printf("Enter your choice: \n");
                            scanf("%d", &choice1);
                            if (choice1==1){
                                    struct schedule s;
                                printf("Enter your name:");
                                gets(s.driverName);
                                displayDSchedule(schedules, numSchedules, driverName);     //Display the schedule of a driver.
                            }

                            else if (choice1==2) {
                                char option;
                                printf("\nMark your attendance\n");
                                printf("Will you come to work today?\n");
                                printf("Type 'Y' for yes or 'N' for no:");
                                scanf(" %c", &option);

                                switch(option) {
                                    case 'Y':
                                        printf("\nAppreciate your commitment.\n");
                                        printf("Can you work overtime today?\n");
                                        printf("Type \'1\' if yes and type \'0\' if no.:");
                                        scanf("%d", &num);
                                        if (num==1){
                                            int otdIndex;
                                            printf("\nWe will notify the management.\n");
                                            printf("\nEnter your driver index number:");
                                            scanf("%02d", otdIndex);
                                            notifyOvertime(otdIndex);
                                        }
                                        else if (num==0){
                                            printf("\nThank you for your response.\n");
                                        }
                                        else
                                            printf("Invalid choice. Please select a valid option.\n");
                                        break;

                                    case 'N':
                                        printf("\nEnter your driver index number:");
                                        scanf("%02d", absenteeIndex);
                                        printf("\nEnter why you won\'t come to work today:\n");
                                        gets(reason);

                                        notifyAbsence(absenteeIndex, reason);
                                        break;

                                    default:
                                        printf("Invalid choice. Please select a valid option.\n");
                                }
                            }

                            else if (choice1==3) {
                                printf("Going to main menu...\n");
                                goto MainMenu;
                            }

                            else {
                                printf("Invalid choice. Please select a valid option.\n");
                            }

                            break;

                        case 2:
                            //Show driver related notifications
                            displayNotifications("driver");
                            break;
                        default:
                            printf("Invalid choice. Please select a valid option.\n");
                    }
                break;



            case 3:
                printf("\n1. Conductor Screen\n");
                printf("2. Notifications\n");
                printf("Choose an option: ");
                scanf("%d", &choiceC);
                switch (choiceC) {
                    case 1:
                        // Conductor screen function
                        printf("\n1. View Your Schedule\n");
                        printf("2. Mark Attendance\n");
                        printf("3. Go to the main menu\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice2);
                        if (choice2 == 1) {
                            struct schedule s;
                            printf("\nEnter your name: ");
                            scanf(" %s", s.conductorName);
                            displayCSchedule(schedules, numSchedules, s.conductorName);
                        } else if (choice2 == 2) {
                            char optionC;
                            int numC, absenteeCIndex;
                            char reasonC[200];

                            printf("\nMark your attendance\n");
                            printf("Will you come to work today? Type 'Y' for yes or 'N' for no: ");
                            scanf(" %c", &optionC);

                            switch (optionC) {
                                case 'Y':
                                    printf("\nAppreciate your commitment.\n");
                                    printf("Can you work overtime today? Type '1' for yes and '0' for no: ");
                                    scanf("%d", &numC);

                                    if (numC == 1) {
                                        int otcIndex;
                                        printf("\nWe will notify the management.\n");
                                        printf("Enter your driver index number: ");
                                        scanf("%d", &otcIndex);
                                        notifyCOvertime(otcIndex);
                                    } else if (numC == 0) {
                                        printf("\nThank you for your response.\n");
                                    } else {
                                        printf("Invalid choice. Please select a valid option.\n");
                                    }
                                    break;

                                case 'N':
                                    printf("\nEnter your conductor index number: ");
                                    scanf("%d", &absenteeCIndex);
                                    printf("\nEnter why you won't come to work today:\n");
                                    scanf(" %199[^\n]", reasonC);  // Use the correct format specifier

                                    notifyCAbsence(absenteeCIndex, reasonC);
                                    break;

                                default:
                                    printf("Invalid choice. Please select a valid option.\n");
                            }
                        } else if (choice2 == 3) {
                            printf("Going to the main menu...\n");
                            goto MainMenu;
                        } else {
                            printf("Invalid choice. Please select a valid option.\n");
                        }
                        break;

                    case 2:
                        // Show conductor-related notifications
                        displayNotifications("conductor");
                        break;

                    default:
                        printf("Invalid choice. Please select a valid option.\n");
                }
                break;




            case 4:
                printf("\n1. Management Screen\n");
                printf("2. Notifications\n");
                printf("Choose an option: ");
                scanf("%d", &choiceM);
                    switch(choiceM) {
                        case 1:
                            // Management screen function
                            printf("\n1. Bus Route Management\n");
                            printf("2. Bus Schedule Management\n");
                            printf("3. View Bus List\n");
                            printf("4. View Drivers List\n");
                            printf("5. View Conductors List\n");
                            printf("6. Go to main menu?\n");
                            printf("Enter your choice: ");
                            scanf("%d", &choice3);
                            if (choice3==1){
                                char select;
                                printf("\na) View Bus Routes\n");
                                printf("b) Add a Bus Route\n");
                                printf("Select an option 'a' or 'b':");
                                scanf(" %c", &select);
                                switch (select){
                                    case 'a':
                                        displayRoutes();
                                        break;
                                    case 'b':
                                        addRoutes();
                                        break;
                                    default:
                                        printf("Invalid choice. Please select a valid option.\n");
                                }
                            }

                            else if (choice3==2) {
                                char select;
                                printf("\na) View Bus Schedule\n");
                                printf("b) Add Time Slot\n");
                                printf("Select an option 'a' or 'b':");
                                scanf(" %c", &select);
                                switch (select){
                                    case 'a':
                                        displaySchedules(&chosenRoute);
                                        break;
                                    case 'b':
                                        addSchedule();
                                        break;
                                    default:
                                        printf("Invalid choice. Please select a valid option.\n");
                                }
                            }

                            else if (choice3==3){
                                printf("Bus List\n");
                                displayBuses();
                            }

                            else if (choice3==4){
                                printf("Drivers List\n");
                                displayDrivers();
                            }

                            else if (choice3==5){
                                printf("Bus List\n");
                                displayConductors();
                            }

                            else if (choice3==6) {
                                printf("Going to main menu...");
                                goto MainMenu;
                            }

                            else {
                                printf("Invalid choice. Please select a valid option.\n");
                            }

                            break;

                        case 2:
                            //Show management related notifications
                            displayNotifications("management");
                            break;
                        default:
                            printf("Invalid choice. Please select a valid option.\n");
                    }
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please select a valid option.\n");
        }

    }
    while (user != 5);

    return 0;
}




//Function Definitions

void displayScheduleP(int *p){
    struct schedule sched[MAX_SCHEDULES_PER_ROUTE]; // Assuming struct schedule is defined

    FILE *schedPD;
    schedPD = fopen("schedule.txt", "r");
    if (schedPD == NULL) {
        printf("\nError opening file for reading.\n");
        return;
    }
    printf("Schedule for Route: %03d\n", *p);
    printf("\n\t|\t Schedule Index \t|\t  Time  \t|\t Bus Name\n");

    for (int y = 0; y < MAX_SCHEDULES_PER_ROUTE; y++) {
        if (fscanf(schedPD, "%02d %03d %02d %02d \n", &sched[y].numSchedule, &sched[y].numRoute, &sched[y].schedules[0].hour, &sched[y].schedules[0].minute,
                                                     sched[y].busName) == 5) {
            if (sched[y].numRoute == *p){
                printf("\n\t|\t----------------\t|\t--------\t|\t--------------------\n");
                printf("\n\t|\t       %02d       \t|\t  %02d:%02d  \t|\t \n", sched[y].numSchedule, sched[y].schedules[0].hour, sched[y].schedules[0].minute, sched[y].busName);
            }
        }
        else {
            break; // Exit the loop if reading fails
        }
    }

    fclose(schedPD);
}

void bookSeats(){
    int i=0;
    char choice;

    while (i < MAX_SEATS) {
        struct bus bookSeat;

        printf("\nEnter route number (e.x.: Route number for bus from Colombo fort to Kandy is 001): ");
        scanf("%03d", &bookSeat.assignedRoute);
        displayScheduleP(&bookSeat.assignedRoute);

        printf("\nEnter the Bus Name you want to book a seat for: ");
        scanf(" %49s", bookSeat.name); // Use %49s to prevent buffer overflow

        sendBookingConfirmation("passenger", bookSeat.assignedRoute, bookSeat.name);

        bookSeat.availableSeats--;
        bookSeat.occupiedSeats++;

        printf("Booking is saved.\n");

        printf("Do you want to book another seat? Enter 'Y' for yes and 'N' for no: ");
        scanf(" %c", &choice);
        if (choice == 'Y') {
            i++;
            bookedSeats++;
        } else if (choice == 'N') {
            printf("Exiting...\n");
            return;
        } else {
            printf("Invalid choice.\n");
        }
    }

    printf("No available seats.\n");
}

void sendBookingConfirmation(const char *recipient, const char *busInfo, const char *scheduleInfo) {
    char message[200];
    sprintf(message, "Booking confirmed for Bus %s, Schedule %s.", busInfo, scheduleInfo);
    addNotification(recipient, message);
}

void displayNotifications(const char *recipient) {
    printf("\nNotifications for %s:\n", recipient);
    for (int i = 0; i < numNotifications; i++) {
        if (strcmp(notifications[i].recipient, recipient) == 0) {
            printf("%d. %s\n", i, notifications[i].message);
        }
    }
}

void addNotification(const char *recipient, const char *message) {
    if (numNotifications < MAX_NOTIFICATIONS) {
        struct notif newNotification;
        strcpy(newNotification.recipient, recipient);
        strcpy(newNotification.message, message);
        notifications[numNotifications] = newNotification;
        numNotifications++;
    } else {
        printf("Maximum number of notifications reached.\n");
    }
}

void displayDrivers(){

        struct driver d1 = {"Gunasena", 0, 10, 6};
        struct driver d2 = {"Jothipala", 1, 9, 8};
        struct driver d3 = {"Punchi Banda", 2, 8, 10};
        struct driver d4 = {"Abeysekara", 3, 7, 4};
        struct driver d5 = {"Ilangarathne", 4, 6, 12};
        struct driver d6 = {"Samarakoon", 5, 5, 11};
        struct driver d7 = {"Wijekoon", 6, 4, 7};
        struct driver d8 = {"Soorasinghe", 7, 3, 5};
        struct driver d9 = {"Weerasinghe", 8, 2, 6};
        struct driver d10 = {"Keerthirathna", 9, 1, 9};

        printf("Driver List\n\n");
        printf("\t|\t Driver Index \t|\t  Assigned Route  \t|\t  Work Hours  \t|\t  Name        \n");
        printf("\t|\t--------------\t|\t------------------\t|\t--------------\t|\t--------------\n");
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", d1.driverIndex, d1.assignedRoute, d1.workHours,d1.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", d2.driverIndex, d2.assignedRoute, d2.workHours,d2.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", d3.driverIndex, d3.assignedRoute, d3.workHours,d3.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", d4.driverIndex, d4.assignedRoute, d4.workHours,d4.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", d5.driverIndex, d5.assignedRoute, d5.workHours,d5.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", d6.driverIndex, d6.assignedRoute, d6.workHours,d6.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", d7.driverIndex, d7.assignedRoute, d7.workHours,d7.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", d8.driverIndex, d9.assignedRoute, d8.workHours,d8.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", d9.driverIndex, d9.assignedRoute, d9.workHours,d9.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", d10.driverIndex, d10.assignedRoute, d10.workHours,d10.name);
}

void displayConductors(){

        struct conductor c1 = {"Jayathilaka", 0, 10, 6};
        struct conductor c2 = {"Appuhami", 1, 9, 8};
        struct conductor c3 = {"Bandara", 2, 8, 10};
        struct conductor c4 = {"Wijewardana", 3, 7, 4};
        struct conductor c5 = {"Kiridena", 4, 6, 12};
        struct conductor c6 = {"Ilangakoon", 5, 5, 11};
        struct conductor c7 = {"Kiribanda", 6, 4, 7};
        struct conductor c8 = {"Sumanasinghe", 7, 3, 5};
        struct conductor c9 = {"Perera", 8, 2, 6};
        struct conductor c10 = {"de Silva", 9, 1, 9};

        printf("Conductor List\n\n");
        printf("\t|\t Conductor Index \t|\t  Assigned Route  \t|\t  Work Hours  \t|\t  Name        \n");
        printf("\t|\t--------------\t|\t------------------\t|\t--------------\t|\t--------------\n");
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", c1.conductorIndex, c1.assignedRoute, c1.workHours, c1.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", c2.conductorIndex, c2.assignedRoute, c2.workHours, c2.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", c3.conductorIndex, c3.assignedRoute, c3.workHours, c3.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", c4.conductorIndex, c4.assignedRoute, c4.workHours, c4.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", c5.conductorIndex, c5.assignedRoute, c5.workHours, c5.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", c6.conductorIndex, c6.assignedRoute, c6.workHours, c6.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", c7.conductorIndex, c7.assignedRoute, c7.workHours, c7.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", c8.conductorIndex, c9.assignedRoute, c8.workHours, c8.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", c9.conductorIndex, c9.assignedRoute, c9.workHours, c9.name);
        printf("\t|\t     %d       \t|\t        %d        \t|\t      %02d      \t|\t  %s\n", c10.conductorIndex, c10.assignedRoute, c10.workHours, c10.name);
}

void displayBuses(){

        struct bus b1 = {"ND 4567", 0, 10};
        struct bus b2 = {"RF 8765", 1, 9};
        struct bus b3 = {"SD 4509", 2, 8};
        struct bus b4 = {"KB 7352", 3, 7};
        struct bus b5 = {"KU 3456", 4, 6};
        struct bus b6 = {"NJ 6876", 5, 5};
        struct bus b7 = {"CD 0709", 6, 4};
        struct bus b8 = {"AX 3467", 7, 3};
        struct bus b9 = {"KL 0356", 8, 2};
        struct bus b10 = {"XR 2489",9, 1};

        printf("Bus List\n\n");
        printf("\t|\t Bus Index    \t|\t  Assigned Route  \t|\t  Name        \n");
        printf("\t|\t--------------\t|\t------------------\t|\t--------------\n");
        printf("\t|\t     %d       \t|\t        %d        \t||\t  %s\n", b1.busIndex, b1.assignedRoute, b1.name);
        printf("\t|\t     %d       \t|\t        %d        \t||\t  %s\n", b2.busIndex, b2.assignedRoute, b2.name);
        printf("\t|\t     %d       \t|\t        %d        \t||\t  %s\n", b3.busIndex, b3.assignedRoute, b3.name);
        printf("\t|\t     %d       \t|\t        %d        \t||\t  %s\n", b4.busIndex, b4.assignedRoute, b4.name);
        printf("\t|\t     %d       \t|\t        %d        \t||\t  %s\n", b5.busIndex, b5.assignedRoute, b5.name);
        printf("\t|\t     %d       \t|\t        %d        \t||\t  %s\n", b6.busIndex, b6.assignedRoute, b6.name);
        printf("\t|\t     %d       \t|\t        %d        \t||\t  %s\n", b7.busIndex, b7.assignedRoute, b7.name);
        printf("\t|\t     %d       \t|\t        %d        \t||\t  %s\n", b8.busIndex, b9.assignedRoute, b8.name);
        printf("\t|\t     %d       \t|\t        %d        \t||\t  %s\n", b9.busIndex, b9.assignedRoute, b9.name);
        printf("\t|\t     %d       \t|\t        %d        \t||\t  %s\n", b10.busIndex, b10.assignedRoute, b10.name);
}

void displayDSchedule(const struct schedule schedules[], int numSchedules, const char *driverName) {
    printf("\nSchedule for Driver: %s\n", driverName);
    printf("| %-4s | %-10s | %-8s | %-10s | %-10s |\n", "ID", "Route", "Driver", "Conductor", "Time");
    printf("|------|------------|----------|------------|------------|\n");

    for (int i = 0; i < numSchedules; i++) {
        if (strcmp(schedules[i].driverName, driverName) == 0) {
            printf("| %-4d | %-10d | %-8s | %-10s | %02d:%02d     |\n", schedules[i].numSchedule, schedules[i].numRoute,
                   schedules[i].driverName, schedules[i].conductorName, schedules[i].schedules[0].hour, schedules[i].schedules[0].minute);
        }
    }
}

void displayCSchedule(const struct schedule schedules[], int numSchedules, const char *conductorName) {
    printf("\nSchedule for Conductor: %s\n", conductorName);
    printf("| %-4s | %-10s | %-8s | %-10s | %-10s |\n", "ID", "Route", "Driver", "Conductor", "Time");
    printf("|------|------------|----------|------------|------------|\n");

    for (int i = 0; i < numSchedules; i++) {
        if (strcmp(schedules[i].conductorName, conductorName) == 0) {
            printf("| %-4d | %-10d | %-8s | %-10s | %02d:%02d     |\n", schedules[i].numSchedule, schedules[i].numRoute,
                   schedules[i].conductorName, schedules[i].conductorName, schedules[i].schedules[0].hour, schedules[i].schedules[0].minute);
        }
    }
}

void notifyAbsence(int absentDIndex, const char *reasonD) {
    char message[200];
    sprintf(message, "Driver with index %02d will be absent today due to: %s", absentDIndex, reasonD);
    addNotification("management", message);
}

void notifyCAbsence(int absentCIndex, const char *reasonC) {
    char message[200];
    sprintf(message, "Conductor with index %02d will be absent today due to: %s", absentCIndex, reasonC);
    addNotification("management", message);
}

void notifyOvertime(int overtimeDIndex) {
    char message[200];
    sprintf(message, "Driver with index %02d will be working overtime today.", overtimeDIndex);
    addNotification("management", message);
}

void notifyCOvertime(int overtimeCIndex) {
    char message[200];
    sprintf(message, "Conductor with index %02d will be working overtime today.", overtimeCIndex);
    addNotification("management", message);
}

void addRoutes(){
    int i=0;
    char choice;

    ADDING: if (i<MAX_ROUTES){
                struct route addRoute[MAX_ROUTES];
                printf("\nEnter route number \n(e.x.: Route number for bus from Colombo fort to Kandy is 001) : ");
                scanf("%03d", &addRoute[i].numRoute);
                printf("\nEnter the destination you want to reach from Badulla :");
                gets(addRoute[i].destination);
                addRoute[i].routeIndex = i;

                FILE *routeA = fopen("route.txt", "w");
                if (routeA == NULL) {
                    printf("Error opening file for writing.\n");
                    return;
                }
                for (int x=0; x<(i+1); x++){
                    fprintf(routeA, "%02d %03d %s \n", addRoute[i].routeIndex, addRoute[i].numRoute, addRoute[i].destination);
                }

                fclose(routeA);
                printf("Route is saved.\n");

                printf("Do you want to add another route? \nEnter 'Y' for yes and 'N' for no.");
                scanf(" %c", &choice);
                 switch (choice)    {
                    case 'Y':
                        i++;
                        addedRoutes++;
                        goto ADDING;
                        break;

                    case 'N':
                        printf("Exiting...");
                        return;

                    default:
                        printf("Invalid choice.");
                                         }
            }
            else {
                printf("Maximum number of routes has reached.");
            }
}

void displayRoutes(){
    struct route routeDisplay[MAX_ROUTES];

    FILE *routeD;
    routeD = fopen("route.txt", "r");
    if (routeD == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    int y=0;
        fscanf(routeD, "%02d %03d %s \n", &routeDisplay[y].routeIndex, &routeDisplay[y].numRoute, &routeDisplay[y].destination);
        printf("\n Route Index \t\t Route Number  \t\t  Destination    \n");
        printf("\n-------------\t\t---------------\t\t-----------------\n");
        while (y<addedRoutes){
            printf("\n     %02d     \t\t     %03d     \t\t  %s  \n", routeDisplay[y].routeIndex, routeDisplay[y].numRoute,
                                                                                            routeDisplay[y].destination);
        }

    fclose(routeD);
}

void addSchedule() {
    int i = 0;
    char choice;

ADD:
    if (i < MAX_SCHEDULES_PER_ROUTE) {
        struct schedule sched[MAX_SCHEDULES_PER_ROUTE];
        printf("\nEnter route number (e.g., Route number for bus from Colombo fort to Kandy is 001): ");
        scanf("%03d", &sched[i].numRoute);
        printf("\nEnter schedule -->\n (Make sure to enter data in 24 hour format -> 18.45)\n hours: ");
        scanf("%02d", &sched[i].schedules[i].hour);
        printf("minutes: ");
        scanf("%02d", &sched[i].schedules[i].minute);

        printf("\nEnter Bus name: ");
        scanf(" %49s", sched[i].busName);
        printf("\nEnter Driver name: ");
        scanf(" %49s", sched[i].driverName);
        printf("\nEnter Conductor name: ");
        scanf(" %49s", sched[i].conductorName);

        sched[i].numSchedule = i;

        FILE *schedA = fopen("schedule.txt", "w");
        if (schedA == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }
        for (int x = 0; x < (i + 1); x++) {
            fprintf(schedA, "%02d %03d %02d %02d %s %s %s \n", sched[i].numSchedule, sched[i].numRoute,
                    sched[i].schedules[i].hour, sched[i].schedules[i].minute, sched[i].busName,
                    sched[i].driverName, sched[i].conductorName);
        }

        fclose(schedA);
        printf("Schedule is saved.\n");

        printf("Do you want to add another Schedule? Enter 'Y' for yes and 'N' for no: ");
        scanf(" %c", &choice);
        switch (choice) {
            case 'Y':
                i++;
                addedSchedules++;
                goto ADD;
                break;

            case 'N':
                printf("Exiting...\n");
                return;

            default:
                printf("Invalid choice.\n");
        }
    } else {
        printf("Maximum number of schedules per route has been reached.\n");
    }
}


void displaySchedules(int *r) {
    struct schedule sched[MAX_SCHEDULES_PER_ROUTE];

    FILE *schedD;
    schedD = fopen("schedule.txt", "r");
    if (schedD == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    int y = 0;
    int numSchedulesFound = 0; // To keep track of the number of schedules found

    while (y < MAX_SCHEDULES_PER_ROUTE && fscanf(schedD, "%02d %03d %02d %02d %49s %49s %49s", &sched[y].numSchedule, &sched[y].numRoute, &sched[y].schedules[0].hour, &sched[y].schedules[0].minute, sched[y].busName, sched[y].driverName, sched[y].conductorName) == 7) {
        if (sched[y].numRoute == *r) {
            if (numSchedulesFound == 0) {
                printf("Schedule for Route: %03d\n\n", sched[y].numRoute);
                printf("\t|\t Schedule Index \t|\t  Time     \t|\t  Bus - Driver - Conductor\n");
                printf("\t|\t----------------\t|\t-----------\t|\t--------------------------\n");
            }

            printf("\t|\t       %02d       \t|\t  %02d:%02d     \t|\t  %s - %s - %s\n", sched[y].numSchedule, sched[y].schedules[0].hour, sched[y].schedules[0].minute, sched[y].busName, sched[y].driverName, sched[y].conductorName);

            numSchedulesFound++;
        }
        y++;
    }

    if (numSchedulesFound == 0) {
        printf("No schedules found for Route: %03d\n\n", *r);
    }

    fclose(schedD);
}



void editSchedule() {
    int scheduleIndex;
    printf("Enter the schedule index you want to edit: ");
    scanf("%d", &scheduleIndex);

    if (scheduleIndex < 0 || scheduleIndex >= addedSchedules) {
        printf("Invalid schedule index.\n");
        return;
    }

    struct schedule *sched = &schedules[scheduleIndex]; // Assuming you have an array of schedules named 'schedules'

    printf("Editing Schedule %d\n", scheduleIndex);
    printf("1. Edit Bus Name\n");
    printf("2. Edit Driver Name\n");
    printf("3. Edit Conductor Name\n");
    printf("4. Go back\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Editing Bus Name
            printf("Enter new Bus Name: ");
            scanf(" %49s", sched->busName);
            printf("Bus Name updated.\n");
            break;
        case 2:
            // Editing Driver Name
            printf("Enter new Driver Name: ");
            scanf(" %49s", sched->driverName);
            printf("Driver Name updated.\n");
            sendScheduleChangeNotification(sched->driverName, "Driver");
            break;
        case 3:
            // Editing Conductor Name
            printf("Enter new Conductor Name: ");
            scanf(" %49s", sched->conductorName);
            printf("Conductor Name updated.\n");
            sendScheduleChangeNotification(sched->conductorName, "Conductor");
            break;
        case 4:
            printf("Going back...\n");
            break;
        default:
            printf("Invalid choice.\n");
    }
}

void sendScheduleChangeNotification(const char *recipient, const char *role) {
    char message[200];
    sprintf(message, "Your schedule as %s has been updated.", role);
    addNotification(recipient, message);
}

