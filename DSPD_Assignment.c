/*
DSPD Assignment ...
Group : 1 . BHUMESH BHOYAR		BT16CSE012		20033
		2 . ANIKET MALI			BT16CSE004		20028
*/

#include <windows.h>
#include <stdio.h>
#include <string.h>
#define NAME_LENGTH 50
#define DESIGNATION_LENGTH 50
#define RECORD_CAPACITY 100
#define LEVEL_LENGTH 10
#define SUCCESS 1
#define FAILURE 0
#define UPDATE 2
#define EXIT -1
#define EVENT_LENGTH 10
#define PICK_OUT_LENGTH 15
struct date{
	int day;
	int month;
	int year;
};

struct  Employee_Record{

	char name[NAME_LENGTH];
	int id;
	float salary;
	struct  date DOJ;  // DOJ : Date Of Joining...
	struct date DOB;  // DOB : Date Of Birth...
	char level[LEVEL_LENGTH];
	char designation[DESIGNATION_LENGTH];
	struct date DOR; //date of retirement
	int period;	//number of days from DOJ to DOR
	char event[EVENT_LENGTH];
	char promoted_level[LEVEL_LENGTH];
};

void SetColor(int ForgC);
int insert(struct Employee_Record [] , char name[] , int id , float salary , int DOJ_day , int DOJ_month , int DOJ_year , int DOB_day , int DOB_month , int DOB_year , char level[] , char designation[] , int Number_of_Records );
int delete(struct Employee_Record[] , char name[] , int day , int month , int year , int size );
void getNumEmployees(int , int , int , int);
int isEmpty(int);
int isFull(int);
void getDataSortedonDOB( struct Employee_Record [] , int Number_of_Records );
void getDataSortedonEmployeePeriod(struct Employee_Record [] ,int Number_of_Records);
void getLongestEmployeePeriod(struct Employee_Record [] ,int Number_of_Records);
int UpdateForEvents(struct Employee_Record[] , int Number_of_Records , struct Employee_Record[] , int  Number_of_Records_in_events );
int listUnique(struct Employee_Record [], int size);
int listUnion(struct Employee_Record [] , struct Employee_Record [] , struct Employee_Record [] , int sizeA, int sizeB);
int listIntersection(struct Employee_Record [] , struct Employee_Record [] , struct Employee_Record [] , int sizeA, int sizeB);
int listDifference(struct Employee_Record [] , struct Employee_Record [] , struct Employee_Record [] , int sizeA, int sizeB);
int SymmetricDifference(struct Employee_Record [] , struct Employee_Record [] , struct Employee_Record [] , int sizeA, int sizeB);

int UPPERCASE(char *);
int binarySearch(struct Employee_Record[],char search[],int Number_of_Records_list);
void Display(struct Employee_Record [],int Number_of_Records);
void shift_right_by_one(struct Employee_Record [], int position);
void shift_left_by_one(struct Employee_Record [], int position);
int search_Record(struct Employee_Record [],char name[],int day,int month,int year,int Number_of_Records);
void merge(struct Employee_Record [] , struct Employee_Record [] , struct Employee_Record [] , int size1, int size2);
void mergeSelf(struct Employee_Record [] , struct Employee_Record [] , int l , int m, int n , char Select[]);
void mergeSort(struct Employee_Record [] , struct Employee_Record [] , int low , int high , char Select[]);
void mergeSort_Period(struct Employee_Record Employee[] , struct Employee_Record PeriodSorted[] , int low , int high);
void mergeSelf_Period(struct Employee_Record Employee[] , struct Employee_Record PeriodSorted[] , int low , int middle , int high);
int leapYear(int);
int daysInMonth(int,int);
int validation(char * , int id , float salary ,int DOJ_day , int DOJ_month , int DOJ_year , int DOB_day , int DOB_month , int DOB_year , char level[] , char designation[] );
int EmployeePeriod(int DOJ_day,int DOJ_month,int DOJ_year,int DOR_day,int DOR_month,int DOR_year);
void initialize(struct Employee_Record []);
int Get_Data(struct Employee_Record[]);
int writeIntoFile(struct Employee_Record [] , struct Employee_Record [] , struct Employee_Record [] , struct Employee_Record [] , int Number_of_Records , int Number_of_Records_list1 , int Number_of_Records_list2 , int Number_of_Records_list3 );
int readFromFile(struct Employee_Record [] , struct Employee_Record [] , struct Employee_Record [] , struct Employee_Record [] , int *Number_of_Records , int *Number_of_Records_list1 , int *Number_of_Records_list2 , int *Number_of_Records_list3 );
char PICK_OUT[PICK_OUT_LENGTH] ;

int main(){

    struct Employee_Record Employee[RECORD_CAPACITY];
	struct Employee_Record list1[RECORD_CAPACITY];				 // level 1
	struct Employee_Record list2[RECORD_CAPACITY];				 // level 2
	struct Employee_Record list3[RECORD_CAPACITY];				 // level 3
	struct Employee_Record listA[RECORD_CAPACITY];
	struct Employee_Record listB[RECORD_CAPACITY];
	struct Employee_Record listC[2*RECORD_CAPACITY];
	struct Employee_Record Events[RECORD_CAPACITY];

	int Number_of_Records = 0;
	int Number_of_Records_list1 = 0;
	int Number_of_Records_list2 = 0;
	int Number_of_Records_list3 = 0;

	initialize(Employee);
	initialize(list1);
	initialize(list2);
	initialize(list3);

	int ACTION=0 , sizeA , sizeB , i , sizeC , temp_list , status , returnValue , id , DOJ_day , DOJ_month , DOJ_year , DOB_day , DOB_month , DOB_year ,updated , added ,valid , position , NoOfRecords;
    char name[NAME_LENGTH],level[LEVEL_LENGTH],designation[DESIGNATION_LENGTH];
	float salary;

	status = readFromFile( Employee , list1 , list2 , list3 , &Number_of_Records , &Number_of_Records_list1 , &Number_of_Records_list2 , &Number_of_Records_list3 );
	if(status == 1)
	{
		printf("Succesfully data loaded from file \n");
	}
	else
	{
		printf("Failed to load data from file\n");
	}

    SetColor(10);
	printf("Select the code to perform action on Record :\n");
	printf("\nCODE  ACTION \n\n");
	SetColor(14);
	printf("\t\t\t\t\t-1\tEXIT or STOP \n\t\t\t\t\t1\tInsert or Update Record\n\t\t\t\t\t2\tDelete\n\t\t\t\t\t3\tGet Number Of Employee\n\t\t\t\t\t4\tIs Empty\n\t\t\t\t\t5\tIs Full\n\t\t\t\t\t6\tGet data Sorted on Date of Birth\n\t\t\t\t\t7\tGet data sorted on Employment Period\n\t\t\t\t\t8\tGet Longest Employment Period\n\t\t\t\t\t9\tUpdate for Events\n\t\t\t\t\t10\tUnique List\n\t\t\t\t\t11\tList Union\n\t\t\t\t\t12\tList Intersection\n\t\t\t\t\t13\tList Difference\n\t\t\t\t\t14\tList Symmetric Difference\n\t\t\t\t\t15\tShow Record\n\t\t\t\t\t16\tReset Record \n");

	while(ACTION != EXIT)
	{
        SetColor(10);
		printf("\nEnter Code Again to perform Action : \n");
		SetColor(14);
		scanf("%d",&ACTION);
		switch(ACTION)
		{
			case 1 :
						SetColor(10);
						printf("Enter Number of Records You want to Enter\n");
						scanf("%d",&NoOfRecords);
						if ( NoOfRecords > RECORD_CAPACITY )
						{
							printf("Number of Records is greater than record capacity\n");
						}
						else
						{
							printf("Enter New Records : \n");
							printf("NAME\tID\tSALARY\tDOJ(dd mm yyyy)\tDOB(dd mm yyyy)\tLEVEL\tDESIGNATION\n");
							for( i=0 ; i<NoOfRecords ; i++)
							{
								updated = 0;
								added = 0;

								scanf("%s %d %f %d%d%d %d%d%d %s %s", name , &id , &salary , &DOJ_day , &DOJ_month , &DOJ_year , &DOB_day , &DOB_month , &DOB_year , level , designation );
								UPPERCASE(level);
								UPPERCASE(designation);
								valid = validation(name , id , salary , DOJ_day , DOJ_month , DOJ_year , DOB_day , DOB_month , DOB_year , level , designation);
								if(valid == SUCCESS)
								{
									status = insert(Employee , name , id , salary , DOJ_day , DOJ_month , DOJ_year , DOB_day , DOB_month , DOB_year , level , designation , Number_of_Records );
									if(status == SUCCESS)
									{
										SetColor(13);
										printf("\nSuccesfully Added in the Record.\n");
										SetColor(14);
										Number_of_Records++;	// Record Size increase by 1
										added = SUCCESS;
									}
									else if(status == UPDATE)
									{
										SetColor(13);
										printf("\nRecord Succesfully Updated\n"); // Record Size same will be same as list is update.
										SetColor(14);
										updated = SUCCESS;
									}
									else
									{
										SetColor(12);
										printf("\nFailed.\n");
									}
									if( (added == SUCCESS) || (updated == SUCCESS) )	//update or added in the lists
									{
										if((strcmp(level,"PB-1")) == 0 )
										{
											status = insert(list1 , name , id , salary , DOJ_day , DOJ_month , DOJ_year , DOB_day , DOB_month , DOB_year , level , designation , Number_of_Records_list1 );
											if(status == SUCCESS)
											{
												Number_of_Records_list1++;
												if(updated == SUCCESS)			// if field is updated in main Record and added in 1st list so it means that old field should be there in list2 or list3
												{
													status = delete(list2,name,DOB_day,DOB_month,DOB_year,Number_of_Records_list2);
													Number_of_Records_list2 = Number_of_Records_list2 - status;
													status = delete(list3,name,DOB_day,DOB_month,DOB_year,Number_of_Records_list3);
													Number_of_Records_list3 = Number_of_Records_list3 - status;
												}
											}
										}
										else if((strcmp(level,"PB-2")) == 0 )
										{
											status = insert(list2 , name , id , salary , DOJ_day , DOJ_month , DOJ_year , DOB_day , DOB_month , DOB_year , level , designation , Number_of_Records_list2 );
											if(status == SUCCESS)
											{
												Number_of_Records_list2++;
												if(updated == SUCCESS)			//// if field is updated in main Record and added in 2nd list so it means that old field should be there in list1 or list3
												{
													status = delete(list1,name,DOB_day,DOB_month,DOB_year,Number_of_Records_list1);
													Number_of_Records_list1 = Number_of_Records_list1 - status;
													status = delete(list3,name,DOB_day,DOB_month,DOB_year,Number_of_Records_list3);
													Number_of_Records_list3 = Number_of_Records_list3 - status;
												}
											}
										}
										else if((strcmp(level,"PB-3")) == 0 )
										{
											status = insert(list3 , name , id , salary , DOJ_day , DOJ_month , DOJ_year , DOB_day , DOB_month , DOB_year , level , designation , Number_of_Records_list3 );
											if(status == SUCCESS)
											{
												Number_of_Records_list3++;
												if(updated == SUCCESS)			// if field is updated in main Record and added in 3rd list so it means that old field should be there in list2 or list1
												{
													status = delete(list2,name,DOB_day,DOB_month,DOB_year,Number_of_Records_list2);
													Number_of_Records_list2 = Number_of_Records_list2 - status;
													status = delete(list1,name,DOB_day,DOB_month,DOB_year,Number_of_Records_list1);
													Number_of_Records_list1 = Number_of_Records_list1 - status;
												}
											}
										}
									}
								}
								else
								{
									SetColor(12);
									printf("Please Enter Valid Record \n");
									SetColor(14);
								}
							}
						}
						break;

			case 2 :
						status=0;
						if ( !isEmpty(Number_of_Records) )
						{
							printf("Enter Employee Name and DOB (day month year) \n");
							scanf("%s%d%d%d", name , &DOB_day , &DOB_month , &DOB_year );
							UPPERCASE(name);

							status = delete(list1,name,DOB_day,DOB_month,DOB_year,Number_of_Records_list1);
							Number_of_Records_list1 = Number_of_Records_list1 - status;

							status = delete(list2,name,DOB_day,DOB_month,DOB_year,Number_of_Records_list2);
							Number_of_Records_list2 = Number_of_Records_list2 - status;

							status = delete(list3,name,DOB_day,DOB_month,DOB_year,Number_of_Records_list3);
							Number_of_Records_list3 = Number_of_Records_list3 - status;

							status = delete(Employee,name,DOB_day,DOB_month,DOB_year,Number_of_Records);
							Number_of_Records = Number_of_Records - status;

							if(status)
							{
								SetColor(9);
								printf("\nSUCCESSFULY DELETED...");
							}
							else
							{
								SetColor(9);
								printf("\nFAILED TO DELETE...");
							}
						}
						else
						{
							SetColor(12);
							printf("record is already Empty....\n");
						}
						break;

			case 3 :
						getNumEmployees(Number_of_Records,Number_of_Records_list1,Number_of_Records_list2,Number_of_Records_list3);
						break;

			case 4 :
						SetColor(9);
						status = isEmpty(Number_of_Records);
						if(status)
						{
							printf("Record is Empty\n");
						}
						else
						{
							printf("Record is Not Empty\n");
						}
						break;

			case 5 :
						SetColor(9);
						status = isFull(Number_of_Records);
						if(status)
						{
							printf("Record is Full\n");
						}
						else
						{
							printf("Record is Not Full\n");
						}
						break;

			case 6 :
						for(i=0;i<Number_of_Records;i++)
						{
							listA[i] = Employee[i];
						}
						getDataSortedonDOB(listA , Number_of_Records);
						Display(listA , Number_of_Records);
						break;

			case 7 :
						for(i=0;i<Number_of_Records;i++)
						{
							listA[i] = Employee[i];
						}
						getDataSortedonEmployeePeriod( listA , Number_of_Records );
						Display(listA , Number_of_Records);
						break;

			case 8 :
						printf("Enter List Number 1,2,3 OR 0 for main Record\n");
						scanf("%d",&temp_list);
						if(temp_list == 0)
						{
							getLongestEmployeePeriod( Employee , Number_of_Records );
						}
						else if(temp_list==1)
						{
							getLongestEmployeePeriod( list1 , Number_of_Records_list1 );
						}
						else if(temp_list==2)
						{
							getLongestEmployeePeriod( list2 , Number_of_Records_list2 );
						}
						else if(temp_list==3)
						{
							getLongestEmployeePeriod( list3 , Number_of_Records_list3 );
						}
						else
						{
							printf("Select valid list number \n");
						}
						break;

			case 9 :
					SetColor(10);
					printf("Enter Number of Records ");
					scanf("%d",&NoOfRecords);
					printf("Enter records for events : \n");
					printf("EVENTS :- JOIN PROMOTE RETIRE\nIf event is JOIN or RETIRE , pls add same level in both \n");
					printf("NAME\tID\tSALARY\tDOJ(dd mm yyyy)\tDOB(dd mm yyyy)\tLEVEL\tDESIGNATION\tEVENTS\tPROMOTED_LEVEL\n");
					for( i=0 ; i<NoOfRecords ; i++)
					{
						SetColor(14);
						scanf("%s %d %f %d%d%d %d%d%d %s %s %s %s", Events[i].name , &Events[i].id , &Events[i].salary , &Events[i].DOJ.day , &Events[i].DOJ.month , &Events[i].DOJ.year , &Events[i].DOB.day , &Events[i].DOB.month , &Events[i].DOB.year , Events[i].level , Events[i].designation , Events[i].event , Events[i].promoted_level);
						UPPERCASE(Events[i].designation);
						UPPERCASE(Events[i].level);
						UPPERCASE(Events[i].promoted_level);
						valid = UPPERCASE(Events[i].event);
						if(!valid)
						{
							SetColor(12);
							printf("Please Enter valid Events\n");
						}
					}

					PICK_OUT[0]='\0';
					strcpy( PICK_OUT , "Employee" );
					status = UpdateForEvents(Employee , Number_of_Records , Events , NoOfRecords);
					Number_of_Records = Number_of_Records + status ;

					PICK_OUT[0]='\0';
					strcpy( PICK_OUT , "list1" );
					status = UpdateForEvents(list1 , Number_of_Records_list1 , Events , NoOfRecords);
					Number_of_Records_list1 = Number_of_Records_list1 + status ;

					PICK_OUT[0]='\0';
					strcpy( PICK_OUT , "list2" );
					status = UpdateForEvents(list2 , Number_of_Records_list2 , Events , NoOfRecords);
					Number_of_Records_list2 = Number_of_Records_list2 + status ;

					PICK_OUT[0]='\0';
					strcpy( PICK_OUT , "list3" );
					status = UpdateForEvents(list3 , Number_of_Records_list3 , Events , NoOfRecords);
					Number_of_Records_list3 = Number_of_Records_list3 + status ;

					break;

			case 10:
						sizeA = Get_Data(listA);
						sizeA = listUnique(listA , sizeA);
						Display(listA,sizeA);
						break;

			case 11:
						sizeA = Get_Data(listA);
						sizeB = Get_Data(listB);
						sizeC = listUnion(listA,listB,listC,sizeA,sizeB);
						Display(listC,sizeC);
						break;

			case 12:
						sizeA = Get_Data(listA);
						sizeB = Get_Data(listB);
						sizeC = listIntersection(listA,listB,listC,sizeA,sizeB);
						Display(listC,sizeC);
						break;

			case 13:
						sizeA = Get_Data(listA);
						sizeB = Get_Data(listB);
						sizeC = listDifference(listA,listB,listC,sizeA,sizeB);
						Display(listC,sizeC);
						break;

			case 14:
						sizeA = Get_Data(listA);
						sizeB = Get_Data(listB);
						sizeC = SymmetricDifference(listA,listB,listC,sizeA,sizeB);
						Display(listC,sizeC);
						break;

			case 15:
						SetColor(14);
						printf("\nMain Record :\n");
						Display(Employee,Number_of_Records);
						SetColor(14);
						printf("\nList1\n");
						Display(list1,Number_of_Records_list1);
						SetColor(14);
						printf("\nList2\n");
						Display(list2,Number_of_Records_list2);
						SetColor(14);
						printf("\nList3\n");
						Display(list3,Number_of_Records_list3);
						break;

			case 16:
						Number_of_Records = 0 ;
						Number_of_Records_list1 = 0 ;
						Number_of_Records_list2 = 0 ;
						Number_of_Records_list3 = 0 ;
						status = writeIntoFile( Employee , list1 , list2 , list3 , Number_of_Records , Number_of_Records_list1 , Number_of_Records_list2 , Number_of_Records_list3 );
						if(status == 1)
						{
							printf("Succesfully Reset\n");
						}
						else
						{
							printf("Failed\n");
						}						
						break;			

			case EXIT:
						printf("\nExit...\n");
						status = writeIntoFile( Employee , list1 , list2 , list3 , Number_of_Records , Number_of_Records_list1 , Number_of_Records_list2 , Number_of_Records_list3 );
						if(status == 1)
						{
							printf("Succesfully written into file\n");
						}
						else
						{
							printf("Failed to written into file\n");
						}
						break;

			default :
						SetColor(12);
						printf("\nPlease Enter Valid Code...\n");
						break;
		}
	}
	return 0;
}

void initialize(struct Employee_Record Employee[]){

	int i = 0 ;
	for(i=0 ; i<RECORD_CAPACITY ; i++)
	{
	    Employee[i].level[0] = '\0';
	    Employee[i].designation[0] = '\0';
	   	Employee[i].name[0] = '\0';
		Employee[i].id = 0;
		Employee[i].salary = 0;
		Employee[i].DOJ.day = 0;
		Employee[i].DOJ.month = 0;
		Employee[i].DOJ.year = 0;
		Employee[i].DOB.day = 0;
		Employee[i].DOB.month = 0;
		Employee[i].DOB.year = 0;
		Employee[i].DOR.day = 0;
		Employee[i].DOR.month = 0;
		Employee[i].DOR.year = 0;
		Employee[i].period = 0;
		Employee[i].event[0] = '\0';
		Employee[i].promoted_level[0] = '\0';
	}
}

int insert(struct Employee_Record Employee[] , char name[] , int id , float salary ,int DOJ_day , int DOJ_month , int DOJ_year , int DOB_day , int DOB_month , int DOB_year , char level[] , char designation[] , int Number_of_Records ){

	int j,status,returnValue,position;
	if(Number_of_Records < RECORD_CAPACITY)
	{
		position = search_Record(Employee , name , DOB_day , DOB_month , DOB_year , Number_of_Records);	//search for record

		if(position == -1)	//record not found ....so now we can add the record at correct position
		{
			j = Number_of_Records - 1;
			status = strcmp(Employee[j].name,name);
			while( (j>=0) && (status > 0) )
			{
				shift_right_by_one(Employee,j);
				j--;
				status = strcmp(Employee[j].name,name);
			}
			while((j>=0) && (status==0) && (Employee[j].DOB.year > DOB_year) )
			{
				shift_right_by_one(Employee,j);
				j--;
				status = strcmp(Employee[j].name,name);
			}
			while((j>=0) && (status==0) && (Employee[j].DOB.year == DOB_year) && (Employee[j].DOB.month > DOB_month )  )
			{
				shift_right_by_one(Employee,j);
				j--;
				status = strcmp(Employee[j].name,name);
			}
			while((j>=0) && (status==0) && (Employee[j].DOB.year == DOB_year) && (Employee[j].DOB.month == DOB_month ) && (Employee[j].DOB.day > DOB_day) )
			{
				shift_right_by_one(Employee,j);
				j--;
				status = strcmp(Employee[j].name,name);
			}
			returnValue = SUCCESS;	//record added
		}
		else	//record found so need to update the record...
		{
			j = position - 1;	//so now record will be added at 'position'....
			returnValue = UPDATE;	//update
		}

		Employee[j+1].id = id;
		Employee[j+1].salary = salary;
		Employee[j+1].DOJ.day = DOJ_day;
		Employee[j+1].DOJ.month = DOJ_month;
		Employee[j+1].DOJ.year = DOJ_year;
		Employee[j+1].DOB.day = DOB_day;
		Employee[j+1].DOB.month = DOB_month;
		Employee[j+1].DOB.year = DOB_year;
		//DOR is last date of the month of birth after 60 year of birth for me its 31/05/2058
		Employee[j+1].DOR.day = daysInMonth(DOB_month,DOB_year) ;
		Employee[j+1].DOR.month = DOB_month;
		Employee[j+1].DOR.year = DOB_year + 60;
		Employee[j+1].period = EmployeePeriod( DOJ_day , DOJ_month , DOJ_year , Employee[j+1].DOR.day , DOB_month , Employee[j+1].DOR.year );
		strcpy(Employee[j+1].name,name);
		strcpy(Employee[j+1].level,level);
		strcpy(Employee[j+1].designation,designation);
	}
	else
	{
		returnValue = FAILURE;	//failed to add the record becouse size is full...
	}
	return returnValue;
}

int delete(struct Employee_Record Employee[],char name[],int day,int month,int year,int size){

	int position,returnValue,status;
	position = search_Record(Employee,name,day,month,year,size);
	if(position == -1)
	{
		returnValue = 0;
	}
	else
	{
		while(position < size - 1)
		{
			shift_left_by_one(Employee,position);
			position++;
		}
		returnValue = 1;
	}
	return returnValue;	//return  0 or 1
}

void getNumEmployees(int list , int list1 , int list2 , int list3 ){

	SetColor(9);
	printf("Here is the Information ...\n\n");
	SetColor(10);
	printf("Total Employees in the record = %d \n",list );
	printf("Total Employees in level 1 = %d \n",list1 );
	printf("Total Employees in level 2 = %d \n",list2 );
	printf("Total Employees in level 3 = %d \n",list3 );
}

int isEmpty(int Number_of_Records){

	int returnValue;
	if(Number_of_Records  == 0)
	{
		returnValue = 1;
	}
	else
	{
		returnValue = 0;
	}
	return returnValue;
}

int isFull(int Number_of_Records){

	int returnValue;
	if(Number_of_Records == RECORD_CAPACITY)
	{
		returnValue = 1;
	}
	else
	{
		returnValue = 0;
	}
	return returnValue;
}

void getDataSortedonDOB(struct Employee_Record Employee[] , int Number_of_Records ){	// first sorted on level then DOB

	struct Employee_Record level_DOB_sorted[RECORD_CAPACITY] ;
	char Select[EVENT_LENGTH] = "level";
	int low = 0;
	int high = Number_of_Records - 1 ;
	mergeSort(Employee , level_DOB_sorted , low , high , Select );
}

void getDataSortedonEmployeePeriod(struct Employee_Record Employee[] , int Number_of_Records ){

	struct Employee_Record PeriodSorted[RECORD_CAPACITY];
	int low = 0;
	int high = Number_of_Records - 1;
	mergeSort_Period(Employee , PeriodSorted , low ,high );
}

void getLongestEmployeePeriod(struct Employee_Record Employee[],int Number_of_Records ){

	int position[Number_of_Records] ;	//there may be multiple Record having longest Employee Period ...
	int i , k , size = 0 , longest = 0 ;		// size of position array ...initially zero..

	for(i=0 ; i < Number_of_Records ; i++)
	{
		if(longest < Employee[i].period)
		{
			size = 0;		//	got the new longest period ... so reset the position array
			longest = Employee[i].period ;
			position[size] = i;
			size++;
		}
		else if(longest == Employee[i].period)
		{
			position[size] = i;	// add the positions of anather record having same(longest) period...
			size++;
		}
	}
	printf("\nLongest Period ...\n");
	for(i = 0 ; i < size ; i++)
	{
		k = position[i];
		printf("%s  %d  %f  %d-%d-%d  %d-%d-%d  %s  %s  %d-%d-%d  %d\n", Employee[k].name , Employee[k].id , Employee[k].salary , Employee[k].DOJ.day , Employee[k].DOJ.month , Employee[k].DOJ.year , Employee[k].DOB.day , Employee[k].DOB.month , Employee[k].DOB.year ,Employee[k].level , Employee[k].designation , Employee[k].DOR.day , Employee[k].DOR.month , Employee[k].DOR.year , Employee[k].period );
	}
}

int UpdateForEvents(struct Employee_Record Employee[] ,int Number_of_Records , struct Employee_Record Events[] , int  Number_of_Records_in_events ){


	int i=0 , valid , Total_Records_added = 0 , status ,position;

	for(i=0 ; i < Number_of_Records_in_events ; i++)
	{
		valid = validation( Events[i].name , Events[i].id , Events[i].salary , Events[i].DOJ.day , Events[i].DOJ.month , Events[i].DOJ.year , Events[i].DOB.day , Events[i].DOB.month , Events[i].DOB.year , Events[i].level , Events[i].designation );
		if(valid)
		{
			if( (( strcmp(Events[i].event , "JOIN") ) == 0) || (( strcmp(Events[i].event , "PROMOTE") ) == 0) )	// now we have to use insert function if record is present it will update else will directly add
			{

				position = 0 ;	//	If first promote action takes place and let's position becomes -1(record not found) then it it will not insert the record next time for JOIN event , so we have to make it 0(which is not equal to -1) so it will insert that record

				if((( strcmp(Events[i].event , "PROMOTE") ) == 0))
				{
					if( ( strcmp( PICK_OUT , "Employee" ) ) == 0 )
					{
						position = search_Record(  Employee , Events[i].name , Events[i].DOB.day , Events[i].DOB.month , Events[i].DOB.year , Number_of_Records );	//If event is promote and record is not present in original list , so can,t be promoted ...because it's new record...
					}

					if( (( strcmp(Events[i].level , Events[i].promoted_level ) ) > 0) )
					{
						position = -1 ;	// will not added to any list
						printf("Demote action can't be done as Event is promote\n");
					}
				}

				if( position != -1 )	// if position is -1 it will not add in any list
				{
					if( ( strcmp( PICK_OUT , "Employee" ) ) == 0)	// passed record is original one...
					{
						status = insert(Employee , Events[i].name , Events[i].id , Events[i].salary , Events[i].DOJ.day , Events[i].DOJ.month , Events[i].DOJ.year , Events[i].DOB.day , Events[i].DOB.month , Events[i].DOB.year , Events[i].promoted_level , Events[i].designation , Number_of_Records + Total_Records_added );
						if(status == SUCCESS)
						{
							Total_Records_added++;
						}
					}
					else if(( strcmp( PICK_OUT , "list1" ) ) == 0)	// passed record is of PB-1...so add that records only which have PB-1 level
					{
						if( strcmp( "PB-1" , Events[i].promoted_level ) == 0)
						{
							status = insert(Employee , Events[i].name , Events[i].id , Events[i].salary , Events[i].DOJ.day , Events[i].DOJ.month , Events[i].DOJ.year , Events[i].DOB.day , Events[i].DOB.month , Events[i].DOB.year , Events[i].promoted_level , Events[i].designation , Number_of_Records + Total_Records_added );
							if(status == SUCCESS)
							{
								Total_Records_added++;
							}
						}
						if(( (strcmp(Events[i].event , "PROMOTE")) == 0) && ( strcmp(Events[i].level , "PB-1") == 0) )
						{
							status = delete(Employee , Events[i].name ,  Events[i].DOB.day , Events[i].DOB.month , Events[i].DOB.year , Number_of_Records + Total_Records_added );
							Total_Records_added = Total_Records_added - status ;
						}
					}
					else if(( strcmp( PICK_OUT , "list2" ) ) == 0)	// passed record is of PB-2...so add that records only which have PB-2 level
					{
						if( strcmp( "PB-2" , Events[i].promoted_level ) == 0)
						{
							status = insert(Employee , Events[i].name , Events[i].id , Events[i].salary , Events[i].DOJ.day , Events[i].DOJ.month , Events[i].DOJ.year , Events[i].DOB.day , Events[i].DOB.month , Events[i].DOB.year , Events[i].promoted_level , Events[i].designation , Number_of_Records + Total_Records_added );
							if(status == SUCCESS)
							{
								Total_Records_added++;
							}
						}
						if(( (strcmp(Events[i].event , "PROMOTE")) == 0) && ( strcmp(Events[i].level , "PB-2") == 0) )
						{
							status = delete(Employee , Events[i].name ,  Events[i].DOB.day , Events[i].DOB.month , Events[i].DOB.year , Number_of_Records + Total_Records_added);
							Total_Records_added = Total_Records_added - status ;
						}
					}
					else if(( strcmp( PICK_OUT , "list3" ) ) == 0)  // passed record is of PB-3...so add that records only which have PB-3 level
					{
						if( strcmp( "PB-3" , Events[i].promoted_level ) == 0)
						{
							status = insert(Employee , Events[i].name , Events[i].id , Events[i].salary , Events[i].DOJ.day , Events[i].DOJ.month , Events[i].DOJ.year , Events[i].DOB.day , Events[i].DOB.month , Events[i].DOB.year , Events[i].promoted_level , Events[i].designation , Number_of_Records + Total_Records_added );
							if(status == SUCCESS)
							{
								Total_Records_added++;
							}
						}
					}
				}
				else
				{
					printf("Record is not available , so can't be promoted... \n");
				}
			}
			else if( ( strcmp(Events[i].event , "RETIRE") ) == 0 )
			{
				status = delete(Employee , Events[i].name ,  Events[i].DOB.day , Events[i].DOB.month , Events[i].DOB.year , Number_of_Records + Total_Records_added ) ;
				if(strcmp(PICK_OUT , "Employee")==0)
                {
                    if ( !status )
                    {
                            printf("record is already not present in the list\n");
                    }
                }

				Total_Records_added = Total_Records_added - status ;
			}
		}
	}
	return Total_Records_added ;
}

int listUnique(struct Employee_Record list[] , int size){

	int low,high;
	low = 0;
	high = size - 1;

	int i , position = 0 , status , statusLevel , position_of_higher_level=0 , statusLevel2 ;

	for(i=1 ; i <= size ; i++)
	{
		status = strcmp(list[i-1].name , list[i].name);
		if((status == 0) && (list[i-1].DOB.year == list[i].DOB.year) && (list[i-1].DOB.month == list[i].DOB.month) && (list[i-1].DOB.day == list[i].DOB.day))
		{
			statusLevel = strcmp(list[i-1].level , list[i].level);
			if(statusLevel<0)
			{
				// i having higher level
				statusLevel2 = strcmp(list[position_of_higher_level].level , list[i].level);
				if(statusLevel2<0)
				{
					position_of_higher_level = i;
				}
			}
			else
			{
				// i-1 having higher level
				statusLevel2 = strcmp(list[position_of_higher_level].level , list[i-1].level);
				if(statusLevel2<0)
				{
					position_of_higher_level = i-1;
				}
			}
		}
		else
		{
			list[position] = list[position_of_higher_level];
			position++;
			position_of_higher_level = i;
		}
	}
	return position;
}

int listUnion(struct Employee_Record listA[] , struct Employee_Record listB[] , struct Employee_Record listC[] , int sizeA, int sizeB){

	merge(listA , listB , listC , sizeA , sizeB);
	int sizeC = sizeB + sizeA;
	int i,position = 1 ,status;
	for(i=1 ; i<sizeC ; i++)
	{
		status = strcmp(listC[i-1].name , listC[i].name);
		if((status != 0) || (listC[i-1].DOB.year != listC[i].DOB.year) || (listC[i-1].DOB.month != listC[i].DOB.month) || (listC[i-1].DOB.day != listC[i].DOB.day))
		{
			listC[position] = listC[i];
			position++;
		}
	}
	return position;
}

int listIntersection(struct Employee_Record listA[] , struct Employee_Record listB[] , struct Employee_Record listC[] , int sizeA, int sizeB){

	merge(listA , listB , listC , sizeA , sizeB);
	int sizeC = sizeB + sizeA;
	int i,position = 0 ,status,statusLevel;
	for(i=1 ; i<sizeC ; i++)
	{
		status = strcmp(listC[i-1].name , listC[i].name);
		if((status == 0) && (listC[i-1].DOB.year == listC[i].DOB.year) && (listC[i-1].DOB.month == listC[i].DOB.month) && (listC[i-1].DOB.day == listC[i].DOB.day))
		{
			statusLevel = strcmp(listC[i-1].level , listC[i].level);
			if(statusLevel<0)
			{
					listC[position] = listC[i];
					position++;
			}
			else
			{
				listC[position] = listC[i-1];
				position++;
			}
		}
	}
	return position;
}

int listDifference(struct Employee_Record listA[] , struct Employee_Record listB[] , struct Employee_Record listC[] , int sizeA, int sizeB){

	int i,status;
	for(i=0 ; i<sizeB ; i++)
	{
		status = delete(listA , listB[i].name , listB[i].DOB.day , listB[i].DOB.month , listB[i].DOB.year , sizeA);
		sizeA = sizeA - status;
	}
	for(i=0 ; i<sizeA ; i++)
	{
		listC[i] = listA[i];
	}
	return sizeA;
}

int SymmetricDifference(struct Employee_Record listA[] , struct Employee_Record listB[] , struct Employee_Record listC[] , int sizeA, int sizeB){

	int i , sizeC , frequency=1 , position = 0 ;

	merge(listA , listB , listC , sizeA , sizeB);
	sizeC = sizeA + sizeB ;
	for(i=0 ; i < sizeC  ; i++)
	{
		if(  (strcmp( listC[i].name , listC[i+1].name ) ==0 ) && (listC[i].DOB.year == listC[i+1].DOB.year)  && (listC[i].DOB.month == listC[i+1].DOB.month)  && (listC[i].DOB.day == listC[i+1].DOB.day) )
		{
			frequency++;
		}
		else
		{
			if(frequency==1)
			{
				listC[position] = listC[i];
				position++;
			}
			frequency = 1;
		}
	}
	sizeC = position ;
	return sizeC;
}

void Display(struct Employee_Record Employee[],int Number_of_Records){

    int i;
    SetColor(9);
    printf("\n\n\tNAME\tID\tSALARY\tDOJ(DD-MM-YYYY)\tDOB(DD-MM-YYYY)\tLEVEL\tDESIGNATION\tDOR(DD-MM-YYYY)\tPERIOD\t\t\t\t\n");
    SetColor(10);
	for (i = 0; i < Number_of_Records; ++i)
	{
		printf("\t%s\t%d\t%.2f\t%d-%d-%d\t%d-%d-%d\t%s\t%s\t%d-%d-%d\t%d\t\n", Employee[i].name , Employee[i].id , Employee[i].salary , Employee[i].DOJ.day , Employee[i].DOJ.month , Employee[i].DOJ.year , Employee[i].DOB.day , Employee[i].DOB.month , Employee[i].DOB.year ,Employee[i].level , Employee[i].designation , Employee[i].DOR.day , Employee[i].DOR.month , Employee[i].DOR.year , Employee[i].period );
	}
}

int search_Record(struct Employee_Record Employee[],char name[],int day,int month,int year,int Number_of_Records){

	int position,returnValue=-1,temp_position,status,found=0;
	position = binarySearch(Employee,name,Number_of_Records); // binary search for given name
	if(position==-1)
	{
		returnValue=-1;
	}
	else	// found name ....now search for DOB
	{
		temp_position = position;
		status = strcmp(Employee[temp_position].name,name);
		while((status == 0) && (found == 0))		//search in right side
		{
			if((Employee[temp_position].DOB.day == day) && ( Employee[temp_position].DOB.month == month ) && ( Employee[temp_position].DOB.year == year ))//record found on right side
			{
				returnValue = temp_position ;	//record found in right side
				found = 1;
			}
			temp_position++;
			status = strcmp(Employee[temp_position].name,name);
		}

		temp_position = position-1 ;
		status = strcmp(Employee[temp_position].name,name);		// search in left side...
		while((status == 0) && (found == 0 ))
		{
			if((Employee[temp_position].DOB.day == day) && ( Employee[temp_position].DOB.month == month ) && ( Employee[temp_position].DOB.year == year ))//record found on left side
			{
				returnValue = temp_position;	// record found
				found = 1;
			}
			temp_position--;
			status = strcmp(Employee[temp_position].name,name);
		}
	}
	return returnValue;
}

int binarySearch(struct Employee_Record list[],char search[],int Number_of_Records_list){

	int f,l,m;
	f=0;
	l=Number_of_Records_list - 1;
	int x,returnValue,found=0;
	while((f<=l) && (found==0))
	{
		m = (f+l)/2;
		x=strcmp(list[m].name , search);
		if(x==0)
		{
			returnValue = m;
			found=1;
		}
		else if( x < 0)
		{
			f=m+1;
		}
		else
		{
			l=m-1;
		}
	}
	if(found==0)
	{
		returnValue = -1;
	}
	return returnValue;
}

void shift_right_by_one(struct Employee_Record Employee[], int j){

	Employee[j+1].id = Employee[j].id;
	Employee[j+1].salary = Employee[j].salary;
	Employee[j+1].DOJ.day = Employee[j].DOJ.day;
	Employee[j+1].DOJ.month = Employee[j].DOJ.month;
	Employee[j+1].DOJ.year = Employee[j].DOJ.year;
	Employee[j+1].DOB.day = Employee[j].DOB.day;
	Employee[j+1].DOB.month = Employee[j].DOB.month;
	Employee[j+1].DOB.year = Employee[j].DOB.year;
	Employee[j+1].DOR.day = Employee[j].DOR.day;
	Employee[j+1].DOR.month = Employee[j].DOR.month;
	Employee[j+1].DOR.year = Employee[j].DOR.year;
	Employee[j+1].period = Employee[j].period;
	strcpy(Employee[j+1].name,Employee[j].name);
	strcpy(Employee[j+1].level,Employee[j].level);
	strcpy(Employee[j+1].designation,Employee[j].designation);
}

void shift_left_by_one(struct Employee_Record Employee[],int j){

	Employee[j].id = Employee[j+1].id;
	Employee[j].salary = Employee[j+1].salary;
	Employee[j].DOJ.day = Employee[j+1].DOJ.day;
	Employee[j].DOJ.month = Employee[j+1].DOJ.month;
	Employee[j].DOJ.year = Employee[j+1].DOJ.year;
	Employee[j].DOB.day = Employee[j+1].DOB.day;
	Employee[j].DOB.month = Employee[j+1].DOB.month;
	Employee[j].DOB.year = Employee[j+1].DOB.year;
	Employee[j].DOR.day = Employee[j+1].DOR.day;
	Employee[j].DOR.month = Employee[j+1].DOR.month;
	Employee[j].DOR.year = Employee[j+1].DOR.year;
	Employee[j].period = Employee[j+1].period;
	strcpy(Employee[j].name,Employee[j+1].name);
	strcpy(Employee[j].level,Employee[j+1].level);
	strcpy(Employee[j].designation,Employee[j+1].designation);
}

int leapYear(int year){	//return 1 if leap else 0...

	int returnValue ;
	if(year % 4 == 0)
	{
		if(year % 400)
		{
			returnValue = 1 ; // leap
		}
		else if( year % 100)
		{
			returnValue = 0 ; // not leap
		}
		else
		{
			returnValue = 1 ;
		}
	}
	else
	{
		returnValue = 0;	// not leap
	}
	return returnValue ;
}

int daysInMonth(int month,int year){

	int returnValue ;
	if((month == 1) || (month == 3) || (month == 5) ||(month == 7) ||(month == 8) || (month == 10) || (month == 12) )
	{
		returnValue = 31 ;
	}
	else if((month == 4) || (month == 6) || (month == 9) || (month == 11) )
	{
		returnValue = 30 ;
	}
	else	// february month
	{
		returnValue = 28 + leapYear(year);	//return 1 if leap else 0
	}
	return returnValue;
}

int EmployeePeriod(int DOJ_day,int DOJ_month,int DOJ_year,int DOR_day,int DOR_month,int DOR_year){

	long int TotalDays_DOJ = 0 , TotalDays_DOR = 0 ;
	int month = 1 ;

	TotalDays_DOJ += 365*(DOJ_year-1) + ((DOJ_year-1)/4 - (DOJ_year-1)/100 + (DOJ_year-1)/400);
	while(month < DOJ_month)
	{
		TotalDays_DOJ += daysInMonth(month , DOJ_year);
		month++;
	}
	TotalDays_DOJ += DOJ_day;

	month = 1 ;
	TotalDays_DOR += 365*(DOR_year-1) + ((DOR_year-1)/4 - (DOR_year-1)/100 + (DOR_year-1)/400);
	while(month < DOR_month)
	{
		TotalDays_DOR += daysInMonth(month , DOR_year);
		month++;
	}
	TotalDays_DOR += DOR_day;

	return  (TotalDays_DOR - TotalDays_DOJ);
}

int validation(char *name , int id , float salary ,int DOJ_day , int DOJ_month , int DOJ_year , int DOB_day , int DOB_month , int DOB_year , char level[] , char designation[] ){

	UPPERCASE(level);
	SetColor(12);
    int i=0,returnValue=1;

    while((name[i] != '\0') && (returnValue == 1))
    {
        if( 'a' <= name[i]  && name[i] <= 'z' )
        {
            name[i] = name[i] - 'a' + 'A' ;
        }
        else if('A' > name[i] || name[i] > 'Z' )
        {
            returnValue = 0;
        }
        i++;
    }
    if(returnValue == 0)
    {
    	printf("Please Enter Valid Name \n");
    }
    else
    {
	    if( DOB_year > DOJ_year  )
	    {
	    	returnValue = 0;
	    }
	    else if ( (DOB_year == DOJ_year) && (DOB_month > DOJ_month) )
	    {
	    	returnValue = 0;
	    }
	    else if ((DOB_year == DOJ_year) && (DOB_month == DOJ_month) && (DOB_day > DOJ_day) )
	    {
	    	returnValue = 0;
	    }
	    if( DOJ_year > (DOB_year + 60) )
	    {
	    	returnValue = 0 ;
	    }
	    else if ( ( DOJ_year == (DOB_year + 60 ) ) && ( DOJ_month > DOB_month ))
	    {
	    	returnValue = 0 ;
	    }

	    if(returnValue == 0)
	    {
	    	printf("Please Enter valid dates \n");
	    }
	    else
	    {

	    	if( (strcmp(level,"PB-1") != 0) && (strcmp(level,"PB-2") != 0) && (strcmp(level,"PB-3") != 0))	// level not matches with PB-1 and PB-2 and PB-3
	    	{
	    		returnValue = 0;
	    	}

	    	if(returnValue == 0)
	    	{
	    		printf("Please Enter Valid level\n");
	    	}
	    }
	}

    return returnValue;
}

void mergeSort(struct Employee_Record list[] , struct Employee_Record TempList[] , int low , int high , char Select[]){

	int middle;
	if(low < high)
	{
		middle = (low + high)/2;
		mergeSort(list , TempList , low , middle , Select);
		mergeSort(list , TempList , middle+1 , high , Select);
		mergeSelf(list , TempList , low , middle , high , Select);
	}
}

void mergeSelf(struct Employee_Record list[] , struct Employee_Record TempList[] , int low , int middle, int high , char Select[]){

	int i,j,k,status;
	i = low;
	j = middle + 1;
	k= low;

	while( i<=middle && j<=high)
	{

		if( (strcmp(Select , "name")) == 0)
		{
			status = strcmp(list[i].name , list[j].name);
		}
		else if( (strcmp(Select , "level")) == 0)
		{
			status = strcmp(list[i].level , list[j].level);
		}

		if(status < 0)
		{
			TempList[k++] = list[i++];
		}
		else if(status > 0)
		{
			TempList[k++] = list[j++];
		}
		else	// status == 0
		{
			if(list[i].DOB.year < list[j].DOB.year)
			{
				TempList[k++] = list[i++];
			}
			else if (list[i].DOB.year > list[j].DOB.year)
			{
				TempList[k++] = list[j++];
			}
			else
			{
				if(list[i].DOB.month < list[j].DOB.month)
				{
					TempList[k++] = list[i++];
				}
				else if (list[i].DOB.month > list[j].DOB.month)
				{
					TempList[k++] = list[j++];
				}
				else
				{
					if(list[i].DOB.day < list[j].DOB.day)
					{
						TempList[k++] = list[i++];
					}
					else if (list[i].DOB.day > list[j].DOB.day)
					{
						TempList[k++] = list[j++];
					}
					else
					{
						TempList[k++] = list[i++];
						TempList[k++] = list[j++];
					}
				}
			}
		}
	}
	while(i <= middle)
	{
		TempList[k++] = list[i++];
	}
	while(j <= high)
	{
		TempList[k++] = list[j++];
	}

	i=low;

	while(i<=high)
	{
		list[i] = TempList[i];
		i++;
	}
}

void merge(struct Employee_Record list1[] , struct Employee_Record list2[] , struct Employee_Record list3[] , int size1, int size2){

	int i=0,j=0,k=0,status;
	while( i<size1 && j<size2)
	{
		status = strcmp(list1[i].name , list2[j].name);
		if(status < 0)
		{
			list3[k++] = list1[i++];
		}
		else if(status > 0)
		{
			list3[k++] = list2[j++];
		}
		else	// status == 0
		{
			if(list1[i].DOB.year < list2[j].DOB.year)
			{
				list3[k++] = list1[i++];
			}
			else if (list1[i].DOB.year > list2[j].DOB.year)
			{
				list3[k++] = list2[j++];
			}
			else
			{
				if(list1[i].DOB.month < list2[j].DOB.month)
				{
					list3[k++] = list1[i++];
				}
				else if (list1[i].DOB.month > list2[j].DOB.month)
				{
					list3[k++] = list2[j++];
				}
				else
				{
					if(list1[i].DOB.day < list2[j].DOB.day)
					{
						list3[k++] = list1[i++];
					}
					else if (list1[i].DOB.day > list2[j].DOB.day)
					{
						list3[k++] = list2[j++];
					}
					else
					{
						list3[k++] = list1[i++];
						list3[k++] = list2[j++];
					}
				}
			}
		}
	}
	if(i < size1)
	{
		while(i < size1)
		{
			list3[k++] = list1[i++];
		}
	}
	else
	{
		while(j < size2)
		{
			list3[k++] = list2[j++];
		}
	}
}

void mergeSort_Period(struct Employee_Record Employee[] ,struct Employee_Record PeriodSorted[] , int low , int high){

	int middle;
	if(low < high)
	{
		middle = (low + high )/2 ;
		mergeSort_Period(Employee , PeriodSorted , low , middle);
		mergeSort_Period(Employee , PeriodSorted , middle + 1 , high);
		mergeSelf_Period(Employee , PeriodSorted , low , middle , high);
	}
}

void mergeSelf_Period(struct Employee_Record Employee[] ,struct Employee_Record PeriodSorted[] , int low , int middle , int high){

	int i,j,k,status;
	i = low;
	j = middle + 1;
	k = low;

	while( i<=middle && j<=high)
	{
		status = strcmp(Employee[i].level , Employee[j].level);
		if(status < 0)
		{
			PeriodSorted[k++] = Employee[i++];
		}
		else if(status > 0)
		{
			PeriodSorted[k++] = Employee[j++];
		}
		else	// status == 0
		{
			if(Employee[i].period < Employee[j].period)
			{
				PeriodSorted[k++] = Employee[i++];
			}
			else 	// list is unique...
			{
				PeriodSorted[k++] = Employee[j++];
			}
		}
	}
	while(i <= middle)
	{
		PeriodSorted[k++] = Employee[i++];
	}
	while(j <= high)
	{
		PeriodSorted[k++] = Employee[j++];
	}
	i = low;
	while(i <= high)
	{
		Employee[i] = PeriodSorted[i] ;
		i++;
	}
}

int UPPERCASE(char *name){

	int i=0 , returnValue = 1 ;
	while((name[i] != '\0') && (returnValue == 1))
    {
        if( 'a' <= name[i]  && name[i] <= 'z' )
        {
            name[i] = name[i] - 'a' + 'A' ;
        }
        else if('A' > name[i] || name[i] > 'Z' )
        {
            returnValue = 0;
        }
        i++;
    }
    return returnValue ;
}

int Get_Data(struct Employee_Record list[]){

	SetColor(9);
	int size , i , id , status , DOJ_day , DOJ_month , DOJ_year , DOB_day , DOB_month , DOB_year , valid , low , high;
    char name[NAME_LENGTH],level[LEVEL_LENGTH],designation[DESIGNATION_LENGTH];
	float salary;
	printf("Number Of Records you wants to Enter : \n");
	scanf("%d",&size);
	printf("NAME  ID  SALARY  DOJ(dd mm yyyy)  DOB(dd mm yyyy)  level  designation\n");
	SetColor(10);
	for( i = 0 ; i < size ; i++ )
	{
		SetColor(14);
		scanf("%s %d %f %d%d%d %d%d%d %s %s", name , &id , &salary , &DOJ_day , &DOJ_month , &DOJ_year , &DOB_day , &DOB_month , &DOB_year , level , designation );
		UPPERCASE(level);
		UPPERCASE(designation);
		valid = validation(name , id , salary , DOJ_day , DOJ_month , DOJ_year , DOB_day , DOB_month , DOB_year , level , designation);
		if(valid == SUCCESS)
		{
			list[i].id = id;
			list[i].salary = salary;
			list[i].DOJ.day = DOJ_day;
			list[i].DOJ.month = DOJ_month;
			list[i].DOJ.year = DOJ_year;
			list[i].DOB.day = DOB_day;
			list[i].DOB.month = DOB_month;
			list[i].DOB.year = DOB_year;
			list[i].DOR.day = daysInMonth(DOB_month,DOB_year) ;
			list[i].DOR.month = DOB_month;
			list[i].DOR.year = DOB_year + 60;
			list[i].period = EmployeePeriod( DOJ_day , DOJ_month , DOJ_year , list[i].DOR.day , DOB_month , list[i].DOR.year );
			strcpy(list[i].name,name);
			strcpy(list[i].level,level);
			strcpy(list[i].designation,designation);
		}
	}

	struct Employee_Record temp[RECORD_CAPACITY];
	low = 0;
	high = size - 1 ;
	char Select[EVENT_LENGTH] = "name";			//sort on name and then DOB...
	mergeSort( list , temp , low , high , Select);

	return size;
}

void SetColor(int ForgC)
{
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

int writeIntoFile(struct Employee_Record Employee[] , struct Employee_Record list1[] , struct Employee_Record list2[] , struct Employee_Record list3[] , int Number_of_Records , int Number_of_Records_list1 , int Number_of_Records_list2 , int Number_of_Records_list3 ){
	
	FILE *fp;
	fp = fopen("data.txt" , "w");
	if(fp == NULL )
	{
		printf("FILE NOT OPEN...\n");
		return 0;
	}
	int i;
	SetColor(10);
	fprintf(fp,"%d\n%d\n%d\n%d\n", Number_of_Records , Number_of_Records_list1 , Number_of_Records_list2 , Number_of_Records_list3 );
	for( i=0 ; i<Number_of_Records ; i++)
	{
		fprintf(fp,"\t%s\t%d\t%.2f\t%d %d %d\t%d %d %d\t%s\t%s\t%d %d %d\t%d\t\n", Employee[i].name , Employee[i].id , Employee[i].salary , Employee[i].DOJ.day , Employee[i].DOJ.month , Employee[i].DOJ.year , Employee[i].DOB.day , Employee[i].DOB.month , Employee[i].DOB.year ,Employee[i].level , Employee[i].designation , Employee[i].DOR.day , Employee[i].DOR.month , Employee[i].DOR.year , Employee[i].period );
	}
	for(i=0 ; i<Number_of_Records_list1 ; i++)
	{
		fprintf(fp,"\t%s\t%d\t%.2f\t%d %d %d\t%d %d %d\t%s\t%s\t%d %d %d\t%d\t\n", list1[i].name , list1[i].id , list1[i].salary , list1[i].DOJ.day , list1[i].DOJ.month , list1[i].DOJ.year , list1[i].DOB.day , list1[i].DOB.month , list1[i].DOB.year ,list1[i].level , list1[i].designation , list1[i].DOR.day , list1[i].DOR.month , list1[i].DOR.year , list1[i].period );
	}
	for(i=0 ; i<Number_of_Records_list2 ; i++)
	{
		fprintf(fp,"\t%s\t%d\t%.2f\t%d %d %d\t%d %d %d\t%s\t%s\t%d %d %d\t%d\t\n", list2[i].name , list2[i].id , list2[i].salary , list2[i].DOJ.day , list2[i].DOJ.month , list2[i].DOJ.year , list2[i].DOB.day , list2[i].DOB.month , list2[i].DOB.year ,list2[i].level , list2[i].designation , list2[i].DOR.day , list2[i].DOR.month , list2[i].DOR.year , list2[i].period );		
	}
	for(i=0 ; i<Number_of_Records_list3 ; i++)
	{
		fprintf(fp,"\t%s\t%d\t%.2f\t%d %d %d\t%d %d %d\t%s\t%s\t%d %d %d\t%d\t\n", list3[i].name , list3[i].id , list3[i].salary , list3[i].DOJ.day , list3[i].DOJ.month , list3[i].DOJ.year , list3[i].DOB.day , list3[i].DOB.month , list3[i].DOB.year ,list3[i].level , list3[i].designation , list3[i].DOR.day , list3[i].DOR.month , list3[i].DOR.year , list3[i].period );
	}
	fflush ( stdin ) ;
	fclose(fp);
	return 1;
}

int readFromFile(struct Employee_Record Employee[] , struct Employee_Record list1[] , struct Employee_Record list2[] , struct Employee_Record list3[] , int *Number_of_Records , int *Number_of_Records_list1 , int *Number_of_Records_list2 , int *Number_of_Records_list3 ){

	FILE *fp;
	fp = fopen("data.txt" , "r");
	if(fp == NULL )
	{
		printf("FILE NOT OPEN...\n");
		return 0;
	}
	int i;
	int n,n1,n2,n3;
	fscanf(fp,"%d %d %d %d", &n , &n1 , &n2 , &n3 );
	*Number_of_Records = n ;
	*Number_of_Records_list1 = n1 ;
	*Number_of_Records_list2 = n2 ;
	*Number_of_Records_list3 = n3 ;

	for( i=0 ; i < *Number_of_Records ; i++)
	{
		fscanf(fp,"%s %d %f %d%d%d %d%d%d %s %s %d%d%d %d ", Employee[i].name , &Employee[i].id , &Employee[i].salary , &Employee[i].DOJ.day , &Employee[i].DOJ.month , &Employee[i].DOJ.year , &Employee[i].DOB.day , &Employee[i].DOB.month , &Employee[i].DOB.year , Employee[i].level , Employee[i].designation , &Employee[i].DOR.day , &Employee[i].DOR.month , &Employee[i].DOR.year , &Employee[i].period );
	}
	for(i=0 ; i < *Number_of_Records_list1 ; i++)
	{
		fscanf(fp,"%s %d %f %d%d%d %d%d%d %s %s %d%d%d %d ", list1[i].name , &list1[i].id , &list1[i].salary , &list1[i].DOJ.day , &list1[i].DOJ.month , &list1[i].DOJ.year , &list1[i].DOB.day , &list1[i].DOB.month , &list1[i].DOB.year , list1[i].level , list1[i].designation , &list1[i].DOR.day , &list1[i].DOR.month , &list1[i].DOR.year , &list1[i].period );
	}
	for(i=0 ; i < *Number_of_Records_list2 ; i++)
	{
		fscanf(fp,"%s %d %f %d%d%d %d%d%d %s %s %d%d%d %d ", list2[i].name , &list2[i].id , &list2[i].salary , &list2[i].DOJ.day , &list2[i].DOJ.month , &list2[i].DOJ.year , &list2[i].DOB.day , &list2[i].DOB.month , &list2[i].DOB.year , list2[i].level , list2[i].designation , &list2[i].DOR.day , &list2[i].DOR.month , &list2[i].DOR.year , &list2[i].period );		
	}
	for(i=0 ; i < *Number_of_Records_list3 ; i++)
	{
		fscanf(fp,"%s %d %f %d%d%d %d%d%d %s %s %d%d%d %d ", list3[i].name , &list3[i].id , &list3[i].salary , &list3[i].DOJ.day , &list3[i].DOJ.month , &list3[i].DOJ.year , &list3[i].DOB.day , &list3[i].DOB.month , &list3[i].DOB.year , list3[i].level , list3[i].designation , &list3[i].DOR.day , &list3[i].DOR.month , &list3[i].DOR.year , &list3[i].period );
	}
	fflush ( stdin ) ;
	fclose(fp);
	return 1;
}
