#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
void clrscr()
{
    system("@cls||clear");
    printf("\n SCHOOL BILLING SYSTEM \n\n");
}
typedef struct node
{
    char name[20];
    int admn_no;
    int monthly_fee;
    long to_be_paid;
    struct node *next;
} NODE;
NODE *student_list = NULL;
NODE *search_student(NODE *, int, bool);
NODE *add_student(NODE *first, NODE data, bool print)
{
    clrscr();
    NODE *new_node, *temp = first;
    new_node = (NODE *)malloc(sizeof(NODE));
    strcpy(new_node->name, data.name);
    new_node->admn_no = data.admn_no;
    new_node->monthly_fee = data.monthly_fee;
    new_node->to_be_paid = data.to_be_paid;
    if (search_student(student_list, new_node->admn_no, false) == NULL)
    {
        if (first == NULL)
        {
            new_node->next = NULL;
            first = new_node;
        }
        else
        {
            NODE *prev_Node;
            while (temp != NULL)
            {
                prev_Node = temp;
                temp = temp->next;
            }
            prev_Node->next = new_node;
            new_node->next = NULL;
        }
        if (print)
        {
            clrscr();
            printf("\n Student added successfully!");
        }
    }
    else
    {
        clrscr();
        printf("\nStudent could not be added : The unique admission no. already exists in system !");
    }
    return first;
}
NODE *search_student(NODE *first, int Temp_adminNo, bool print)
{
    NODE *temp = first;
    clrscr();
    while (temp != NULL)
    {
        if (temp->admn_no == Temp_adminNo)
        {
            if (print)
            {
                printf("\n\n !!! Student Found !!! \n Name : %s\n Admission no. :% d\n Monthly Fee: Rs.% d\n Fee Dues: Rs.% ld\n ", temp->name, temp->admn_no, temp->monthly_fee, temp->to_be_paid);
            }
            return temp;
        }
        temp = temp->next;
    }
    if (print == true)
        printf("\n\n !!! Student couldn't be found !!!");
    return NULL;
}
void fee_payment(NODE *first)
{
    clrscr();
    int TempAdminNo;
    char c;
    NODE *temp;
    printf("\n Fee Payment : \n Enter the Addmission no. : ");
    scanf("%d", &TempAdminNo);
    temp = search_student(student_list, TempAdminNo, true);
    while (temp != NULL)
    {
        if (temp->to_be_paid != 0)
        {
            getchar();
            printf("\n Confirm the payment (Y/N) : ");
            scanf("%c", &c);
            if (c == 'Y' || c == 'y')
            {
                temp->to_be_paid = 0;
                printf("\n !! Payment successful for %s :) !!", temp->name);
                break;
            }
            else if (c == 'N' || c == 'n')
            {
                printf("\n !! Payment cancelled :( !!");
                break;
            }
        }
        else
        {
            printf("\n No Fees due ;)");
            break;
        }
    }
}
void update_record(NODE *first)
{
    clrscr();
    NODE *temp = first;
    while (temp != NULL)
    {
        if (temp->to_be_paid != 0)
        {
            temp->to_be_paid = temp->to_be_paid + 0.05 * temp->monthly_fee; // Adding Fine for each month
        }
        else
            temp->to_be_paid = temp->monthly_fee;
        temp = temp->next;
    }
    printf("\n All records updated successfully :)");
}
void display_all_student(NODE *first)
{
    clrscr();
    printf("\n All Records : ");
    NODE *temp = first;
    bool isEmpty = true;
    while (temp != NULL)
    {
        isEmpty = false;
        isEmpty = false;
        printf("\n\n Name : %s\n Admission no. : %d\n Monthly Fee : Rs. %d\n Fee Dues : Rs. %ld\n", temp->name, temp->admn_no, temp->monthly_fee, temp->to_be_paid);

        temp = temp->next;
    }
    if (isEmpty == true)
        printf(" The list is Empty :(");
}
NODE *delete_student(NODE *first, int Temp_adminNo)
{
    clrscr();
    NODE *prev_Node, *temp;
    bool deleted = false;
    temp = first;
    prev_Node = NULL;
    while (temp != NULL)
    {
        if (temp->admn_no == Temp_adminNo)
        {
            if (prev_Node == NULL)
            {
                printf("\n !! Data of %s deleted successfully !!", temp->name);
                first = temp->next;
                free(temp);
            }
            else
            {
                printf("\n !! Data of %s deleted successfully !!", temp->name);
                prev_Node->next = temp->next;
                free(temp);
            }
            deleted = true;
            break;
        }
        prev_Node = temp;
        temp = temp->next;
    }
    if (!deleted)
        printf("\n !!! Data could not be deleted !!!");
    return first;
}
void read_from_file(NODE *first)
{
    FILE *fp;
    NODE data;
    int length;
    fp = fopen("student_details", "r");
    printf("\n Loading Data from File......");
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%d\t", &length);
            fgets(data.name, length + 1, fp);
            fscanf(fp, "\t%d\t%d\t%ld\n", &data.admn_no, &data.monthly_fee, &data.to_be_paid);
            student_list = add_student(student_list, data, false);
        }
    }
    fclose(fp);
    clrscr();
}
void write_to_file(NODE *first)
{
    printf("\n Writing to file ....");
    FILE *fp;
    NODE *temp;
    temp = first;
    fp = fopen("student_details", "w");
    while (temp != NULL)
    {
        fprintf(fp, "%d\t%s\t%d\t%d\t%ld\n", (int)strlen(temp->name), temp->name, temp->admn_no, temp->monthly_fee, temp->to_be_paid);
        temp = temp->next;
    }
    fclose(fp);
    clrscr();
}
int main()
{
    clrscr();
    read_from_file(student_list);
    NODE data;
    int c;
    int Temp_adminNo;
    while (1)
    {
        printf("\n MENU : \n 1 > Add Student Info\n 2 > Search Record\n 3 > Delete Student Info\n 4 > Update All Records Payment Amount\n 5 > Fee Payment\n 6 > Display All Records\n 7 > Reset the File \n 8 > Save and Exit\n\n Choice : ");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            printf("\nEnter Student Info : \n Name : ");
            getchar();
            gets(data.name);
            printf(" Admission No. : ");
            scanf("%d", &data.admn_no);
            printf(" Monthly Fee : ");
            scanf("%d", &data.monthly_fee);
            data.to_be_paid = 0;
            data.next = NULL;
            student_list = add_student(student_list, data, true);
            break;
        case 2:
            printf("\nStudent Search : \n Enter Admission No. of student to search : ");
            scanf("%d", &Temp_adminNo);
            search_student(student_list, Temp_adminNo, true);
            break;
        case 3:
            printf("\nStudent Search : \n Enter Admission No. of student to delete : ");
            scanf("%d", &Temp_adminNo);
            student_list = delete_student(student_list, Temp_adminNo);
            break;
        case 4:
            update_record(student_list);
            break;
        case 5:
            fee_payment(student_list);
            break;
        case 6:
            display_all_student(student_list);
            break;
        case 7:
            printf("\n Existing file deleted <-_->");
            NODE *temp = student_list;
            while (temp != NULL)
            {
                NODE *prev_node = temp;
                temp = temp->next;
                free(prev_node);
            }
            student_list = NULL;
            remove("student_details");
            break;
        case 8:
            write_to_file(student_list);
            exit(0);
            break;
        default:
            printf(" !!! Invalid Input !!!");
        }
    }
}