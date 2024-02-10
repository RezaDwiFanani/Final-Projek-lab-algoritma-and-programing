#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_STUDENTS 100 
//the max of student the program can manage = 100 (constant)
#define MAX_NAME_LENGTH 50




typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char courseLevel[15];
    int quiz;
    int assignment;
    int exam;
    int score;
    char grade;
} Student;

//function prototype (declarations)
void menuDisplay();
void read(Student students[], int *studentCount);
void write(Student students[], int studentCount);
void displayData();



//function involved in entry
void entry(Student students[], int *studentCount);
void validateCourseLevel(char *courseLevel);
void validateScore(int *score);
void deleteData(Student students[], int *studentCount);
void edit(Student students[], int studentCount);



//function involved in sorting
void sortBy(Student students[], int numStudents, int ascending, int (*compare)(const void *, const void *));
void quicksort(Student students[], int low, int high, int (*compare)(const void *, const void *));
int partition(Student students[], int low, int high, int (*compare)(const void *, const void *));
int compareByID(const void *a, const void *b);
int compareByBestGrade(const void *a, const void *b);
int compareByModeGrade(const void *a, const void *b);
int compareByName(const void *a, const void *b);



//function involved in searching
void displayResults(Student students[], int indices[], int count);
int searchFinalGrade(Student students[], int studentCount, char searchKey, int indices[], int maxIndices);
int searchName(Student students[], int studentCount, const char *searchKey, int indices[], int maxIndices);
int searchID(Student students[], int studentCount, int searchKey, int indices[], int maxIndices);


int main() {
	system("COLOR 6F");
    Student students[MAX_STUDENTS];
    int studentCount = 0;

    //Load existing data from the file so that the program can manage them 
	read(students, &studentCount);

    int choice;
    //Option variable for the sub-menu
	int entryOpt, sortOption, sortOrder, searchOpt, keyID, indices[MAX_STUDENTS];
	//Searchkey
	char keyName[MAX_NAME_LENGTH], keyGrade;
	// Determine comparison function based on user choice
    int (*compareFunction)(const void *, const void *);
    
      do {
		menuDisplay();
        printf("\t\t\t\t\t   Your choice: ");
        scanf("%d", &choice);
        printf("\n\n\n-------------------------------------------------------------------------------------------\n");
        system("cls");
    

        switch (choice) {
            case 1:
            	//This is the option that allows user to input new student datas
				
				do{
					//Display entry sub-menu:
					printf("\nEntry Sub-Menu:\n");
        			printf("1. Add New Student\n");
        			printf("2. Edit Student Data\n");
        			printf("3. Delete Student\n");
        			printf("4. Back to Main Menu\n");
        			printf("Enter your option: ");
        			scanf("%d", &entryOpt);  
					
					switch (entryOpt) {
            			case 1:
							entry(students, &studentCount);
                			break;
            			case 2:
                			edit(students, studentCount);
                			break;
            			case 3:
                			deleteData(students, &studentCount);
                			break;
            			case 4: // Back to the main menu
                			break;
            			default:
                			printf("Invalid input. Please enter a valid option.\n");
        			}
				} while (entryOpt != 4);	          					
                
				break;
                
            case 2: 
				// This is the option that prompts the program to sort the data
    			
    			do{
					// Display sorting sub-menu
    				printf("\nPlease choose your preferred sorting method:\n");
    				printf("1. Sort datas by Student ID\n");
   					printf("2. Sort datas by Best Grade\n");
    				printf("3. Sort datas by Mode Grade\n");
    				printf("4. Sort datas by Name\n");
    				printf("5. Exit to main menu\n");
    				printf("Enter your sorting option: ");
    				scanf("%d", &sortOption);

					//Sorting sub-menu selection branch
    				switch (sortOption) {
        				case 1:
            				compareFunction = compareByID;
            				break;
        				case 2:
            				compareFunction = compareByBestGrade;
            				break;
        				case 3:
            				compareFunction = compareByModeGrade;
       		     			break;
            			case 4:
            				compareFunction = compareByName;
        				case 5:
        					break;
						default:
            				printf("Invalid sorting option. Returning to main menu.\n");
            				break;
                	}
                	
					if (sortOption == 2 || sortOption == 3 || sortOption == 4) {
        			// For 'best grade' and 'mode grade', always sort in descending order
        			sortBy(students, studentCount, 1, compareFunction);
   					} else {
	        		// For other cases, prompt the user for the order
			        printf("Please select the sorting order:\n");
        			printf("1. Ascending\n");
        			printf("2. Descending\n");
        			printf("Enter your choice: ");
        			scanf("%d", &sortOrder);
        		
	        		//Perform the sorting
    	    		sortBy(students, studentCount, sortOrder, compareFunction);   
					write(students, studentCount);    //save the progress of data processing        
					}
            	} while (sortOption >= 1 && sortOption <= 4);	
				break;
				
            case 3:
                // This is the option that allows user to search a certain student or
                //a group of students.
                
                do{
                	// Display search menu
    				printf("\nPlease Choose your Searching Way:\n");
    				printf("1. Search by Student ID\n");
    				printf("2. Search by Name\n");
    				printf("3. Search by Final Grade\n");
    				printf("4. Back to Main Menu\n");
    				scanf("%d", &searchOpt);
				                
	                // Perform search based on user choice
    				switch (searchOpt) {
        				case 1: {
            				printf("Enter the Student ID to search: ");
            				scanf("%d", &keyID);
            				int idSearchResult = searchID(students, studentCount, keyID, indices, MAX_STUDENTS);
            				break;
        				}
        			
						case 2: {
    	        			printf("Enter the Name to search: ");
        	    			scanf("%s", keyName);
            				int nameSearchResult = searchName(students, studentCount, keyName, indices, MAX_STUDENTS);
            				break;
        				}
        
						case 3: {
    	        			printf("Enter the Final Grade to search: ");
        	    			scanf(" %c", &keyGrade);
            					int gradeSearchResult = searchFinalGrade(students, studentCount, keyGrade, indices, MAX_STUDENTS);
            				break;
        				}
        			
	        			case 4: {
    	    				//Back to Main Menu
							break;
						}
						
						default:
            				printf("Invalid choice. Choose between number 1 to number 4.\n");
            				break;
    				}
				} while (searchOpt >= 1 && searchOpt <= 3);
				break;
				
            case 4:
                // Exit the Program (Bubhyee)
                write(students, studentCount);
                printf("Your Data has been Updated. Now Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        	}
    	} while (choice != 4);
	
	return 0;
}



void read(Student students[], int *studentCount) {
    FILE *fpoint = fopen("DataSiswa.txt", "r");

    if (fpoint == NULL) {
        printf("File not found. Starting with an empty dataset.\n");
        return;
    }

    while (fscanf(fpoint, "%d %s %s %d %d %d %d %c",
                  &students[*studentCount].id,
                  students[*studentCount].name,
                  students[*studentCount].courseLevel,
                  &students[*studentCount].quiz,
                  &students[*studentCount].assignment,
                  &students[*studentCount].exam,
                  &students[*studentCount].score,
                  &students[*studentCount].grade) == 8) {
        (*studentCount)++;
        if (*studentCount == MAX_STUDENTS) {
            break;  //to Avoid exceeding array size
        }
    }

    fclose(fpoint);
}



void displayData() {
    FILE *file = fopen("DataSiswa.txt", "r");

    // Memeriksa apakah file berhasil dibuka
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    // Membaca dan menampilkan data dari file
    int nim;
    char nama[50];
    char tipe[50];
    float nq, nt, nu, nak;
    char grade;

    printf("NIM\tNama\t\t\tNilai Quiz\tNilai Tugas\tNilai Ujian\tNilai Akhir Kursus\tGrade\n");

    while (fscanf(file, "%d %s %s %f %f %f %f %c", &nim, nama, tipe, &nq, &nt, &nu, &nak, &grade) == 8) {
        printf("%d\t%s\t\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\t\t\t%c\n", nim, nama, nq, nt, nu, nak, grade);
    }

    // Menutup file setelah selesai membaca
    fclose(file);
}



// Function to write data to a file, for saving purposes
void write(Student students[], int studentCount) {
    FILE *fpoint = fopen("DataSiswa.txt", "w");

    if (fpoint == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        fprintf(fpoint, "%d %s %s %d %d %d %d %c\n",
                students[i].id,
                students[i].name,
                students[i].courseLevel,
                students[i].quiz,
                students[i].assignment,
                students[i].exam,
                students[i].score,
                students[i].grade);
    }

    fclose(fpoint);
}



//Below is the main menu contain, stored in menuDisplay function
void menuDisplay(){
	printf("==================================================================================================================\n");
    printf("\n\n\t\t\t\t\tWELCOME TO ENGLISH SCORE CALCULATION MANAGEMENT");
	printf("\n\t\tThis is made to suffice our final project assignment in Algorithm and Programming Study Course");
	printf("\n\n\n==================================================================================================================\n");
	printf("\n\n\t\t\t\t\t    HERE IS A LIST OF WHAT WE CAN DO FOR YOU: \n");
    printf("\n\n\t\t\t\t    1. Entry");
    printf("\n\t\t\t\t\t     2. Sort\n");
    printf("\t\t\t\t\t\t   3. Search\n");
    printf("\t\t\t\t\t\t\t   4. Exit\n");
    printf("\t\t\t\t\t\t\t\t   \n");
    printf("\n\n\n==================================================================================================================\n");
	return;
}



//Validation Function so that the system will not accept any level other than Beginner, Intermediate, or Advanced
void validateCourseLevel(char *courseLevel) {
    while (strcmp(courseLevel, "Beginner") != 0 &&
           strcmp(courseLevel, "Intermediate") != 0 &&
           strcmp(courseLevel, "Advanced") != 0) {
        printf("The course level just now is invalid, please retry: ");
        scanf("%s", courseLevel);
    }
    return;
}

//Validation Function so that the score range stays from 0 to 100.
void validateScore(int *score) {
    while (*score < 0 || *score > 100) {
        printf("The score just now is invalid, please retry: ");
        scanf("%d", score);
    }
    return;
}

// Function to add a new student entry
void entry(Student students[], int *studentCount) {
    displayData();
	int Additional;
    
    printf("Enter the number of students to add: ");
    scanf("%d", &Additional);

    if (*studentCount + Additional > MAX_STUDENTS) {
        printf("Adding %d students would exceed the maximum limit.\n", Additional);
        return;
    }

    FILE *fpoint = fopen("DataSiswa.txt", "a");
    if (fpoint == NULL) {
        printf("Error opening file for appending.\n");
        return;
    }

    for (int i = 0; i < Additional; i++) {
        printf("Enter Student ID for student %d: ", i + 1);
        scanf("%d", &students[*studentCount + i].id);
		
        printf("Enter Student Name for student %d: ", i + 1);
        scanf("%s", students[*studentCount + i].name);

        printf("Enter Course Level for student %d (Beginner, Intermediate, Advanced): ", i + 1);
        scanf("%s", students[*studentCount + i].courseLevel);
		validateCourseLevel(students[*studentCount + i].courseLevel);
		
        printf("Enter Quiz Score for student %d (0-100): ", i + 1);
        scanf("%d", &students[*studentCount + i].quiz);
		validateScore(&students[*studentCount + i].quiz);
		 
        printf("Enter Assignment Score for student %d (0-100): ", i + 1);
        scanf("%d", &students[*studentCount + i].assignment);
		validateScore(&students[*studentCount + i].assignment);
		
        printf("Enter Exam Score for student %d (0-100): ", i + 1);
        scanf("%d", &students[*studentCount + i].exam);
		validateScore(&students[*studentCount + i].exam);
		
        // Calculate final score and determine final grade
        students[*studentCount + i].score = ((30 * students[*studentCount + i].quiz) +
            (30 * students[*studentCount + i].assignment) +
    		(40 * students[*studentCount + i].exam))/ 100;

        if (students[*studentCount + i].score >= 85)
            students[*studentCount + i].grade = 'A';
        else if (students[*studentCount + i].score >= 70)
            students[*studentCount + i].grade = 'B';
        else if (students[*studentCount + i].score >= 60)
            students[*studentCount + i].grade = 'C';
        else if (students[*studentCount + i].score >= 50)
            students[*studentCount + i].grade = 'D';
        else
            students[*studentCount + i].grade = 'E';

        // Write to file
        fprintf(fpoint, "%d %s %s %d %d %d %d %c\n",
                students[*studentCount + i].id,
                students[*studentCount + i].name,
                students[*studentCount + i].courseLevel,
                students[*studentCount + i].quiz,
                students[*studentCount + i].assignment,
                students[*studentCount + i].exam,
                students[*studentCount + i].score,
                students[*studentCount + i].grade);
    }

    fclose(fpoint);
    printf("%d students' data entered and saved to file successfully.\n", Additional);
    int empty = MAX_STUDENTS - (*studentCount + Additional);
    if (empty < 100){
    	printf("There are now %d students enrolled in this course. There are %d empty seats left to fill out!\n",
           *studentCount + Additional, empty);
	} else printf("Yay!! Our program now has reached the maximum capacity!");
    (*studentCount) += Additional;
    return;
}

void edit(Student students[], int studentCount) {
    int num, i, j;
    printf("How many student data would you like to edit?\n");
    printf("Answer: ");
    scanf("%d", &num);
    int editID[num];
    
    //Prompt user to input the students IDs
    for (i = 0; i < num; i++){
    	printf("Enter the Student ID to edit: ");
    	scanf("%d", &editID[i]);
	}

    // Find the index of the student with the given ID & Display the pre-edited data
    printf("Current Data:\n");
	for (j = 0; j < num; j++){
    	int index = (students, studentCount, editID[j], NULL, 0);
		
    	if (index != -1) {
        	// Display the current data for confirmation
			printf("Name %d        : %s", j+1, students[index].name);
			printf("ID %d          : %d", j+1, students[index].id);
			printf("Level %d       : %s", j+1, students[index].courseLevel);
			printf("Assignment %d  : %d", j+1, students[index].assignment);
			printf("Quiz %d		   : %d", j+1, students[index].quiz);
			printf("Exam %d		   : %d", j+1, students[index].exam);
			printf("Final Score %d : %d", j+1, students[index].score);
			printf("Final Grade    : %c", j+1, students[index].grade);
    	} else {
        	printf("Student with ID %d not found.\n", editID[j]);
    	}
	}
		
    for (j = 0; j < num; j++){
		int index = (students, studentCount, editID[j], NULL, 0);
		
		if (index != -1){
			// Prompt for new data
	    	printf("\nEnter new data:\n");
			printf("Enter Student Name     : ");
        		scanf("%s", students[index].name);
		    printf("Enter Student ID       : ");
    			scanf("%d", &students[index].id);
        	printf("Enter Student Level    : ");
				scanf("%s", students[index].courseLevel);
				validateCourseLevel(students[index].courseLevel);
			printf("Enter Assignment Score : ");
				scanf("%d", &students[index].assignment);
				validateScore(&students[index].assignment);
			printf("Enter Quiz Score       : ");
				scanf("%d", &students[index].quiz);
				validateScore(&students[index].quiz);
			printf("Enter Exam Score       : ");
				scanf("%d", &students[index].exam);
				validateScore(&students[index].exam);
		}
	}   	
    
	printf("Data updated successfully.\n");
	
	return;
}

void deleteData(Student students[], int *studentCount) {
    int Dnum, i, j;
    
    //prompt the user to input the amount of data to be deleted
    printf("How many data would you like to remove?\n");
    printf("Answer : ");
    	scanf("%d", &Dnum);
    int deleteID[Dnum];
	
		printf("Enter the Student ID to delete: ");
		for (i = 0; i < Dnum; i++){
    		scanf("%d", &deleteID[i]);
		}

    printf("Data to be deleted:\n");
	for (j = 0; j < Dnum; j++){
    	int index = searchID(students, *studentCount, deleteID[j], NULL, 0);
		
    	if (index != -1) {
        	// Display the current data for confirmation
			printf("Name %d        : %s", j+1, students[index].name);
			printf("ID %d          : %d", j+1, students[index].id);
			printf("Level %d       : %s", j+1, students[index].courseLevel);
			printf("Assignment %d  : %d", j+1, students[index].assignment);
			printf("Quiz %d		   : %d", j+1, students[index].quiz);
			printf("Exam %d		   : %d", j+1, students[index].exam);
			printf("Final Score %d : %d", j+1, students[index].score);
			printf("Final Grade    : %c", j+1, students[index].grade);
    	} else {
        	printf("Student with ID %d not found.\n", deleteID[j]);
    	}
	}
	
    char confirm;
	printf("\nAre you sure you want to delete these data? (Y/N): ");
    scanf(" %c", &confirm);

		for (j = 0; j < Dnum; j++){
			int index = searchID(students, *studentCount, deleteID[j], NULL, 0);
    		if (index != -1) {   
				if (confirm == 'y' || confirm == 'Y') {
            		// Shift remaining elements to overwrite the deleted one
            		for (i = index; i < *studentCount - 1; i++) {
                		students[i] = students[i + 1];
            		} 
            			// Decrement the number of students
            		(*studentCount)--;
            		printf("Data deleted successfully.\n");
        		} else if (confirm == 'N' || confirm == 'n'){
            		printf("Deletion canceled.\n");
        		} else printf("Your input is invalid");
    		} else {
        	printf("Student with ID %d not found.\n", deleteID);
    		}
		}
	return;
}



void quicksort(Student students[], int low, int high, int (*compare)(const void *, const void *)) {
    if (low < high) {
        int pivotIndex = partition(students, low, high, compare);

        quicksort(students, low, pivotIndex - 1, compare);
        quicksort(students, pivotIndex + 1, high, compare);
    }
    
    return;
}

int partition(Student students[], int low, int high, int (*compare)(const void *, const void *)) {
    Student pivot = students[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (compare(&students[j], &pivot) < 0) {
            i++;
            // Swap students[i] and students[j]
            Student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
        }
    }

    // Swap students[i + 1] and students[high]
    Student temp = students[i + 1];
    students[i + 1] = students[high];
    students[high] = temp;

    return i + 1;
}

int compareByID(const void *a, const void *b) {
	
    return ((Student *)a)->id - ((Student *)b)->id;
}

int compareByBestGrade(const void *a, const void *b) {
    int scoreA = ((Student *)a)->score;
    int scoreB = ((Student *)b)->score;

    return scoreB - scoreA;  // Sort in descending order
}

int compareByModeGrade(const void *a, const void *b) {
	
    return ((Student *)a)->grade - ((Student *)b)->grade;
}   

int compareByName(const void *a, const void *b) {
	
    return strcmp(((Student *)a)->name, ((Student *)b)->name);
}

void sortBy(Student students[], int studentCount, int ascending, int (*compare)(const void *, const void *)) {
    // Perform quicksort
    quicksort(students, 0, studentCount - 1, compare);

    // Display sorted data
    printf("\nSorted Data:\n");
    printf("Comparison Type | Student ID | Student Name\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%-16s| %-10d| %s\n", ascending ? "Ascending" : "Descending", students[i].id, students[i].name);
    }
    
    return;
}



void displaySearch(Student students[], int indices[], int count) {
    if (count == 0) {
        printf("No matching data found.\n");
    } else {
        printf("Matching data found:\n");
        for (int i = 0; i < count; i++) {
            printf("ID: %d, Name: %s, Grade: %c\n",
                   students[indices[i]].id, students[indices[i]].name, students[indices[i]].grade);
        }
        printf("Total matching data: %d\n", count);
    }
    
    return;
}

int searchFinalGrade(Student students[], int studentCount, char searchKey, int indices[], int maxIndices) {
    int count = 0;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].grade == searchKey) {
            if (count < maxIndices) {
                indices[count++] = i; // Store the index of the occurrence
            }
        }
    }

    displaySearch(students, indices, count);

    return count; // Return the number of occurrences
}

int searchName(Student students[], int studentCount, const char *searchKey, int indices[], int maxIndices) {
    int count = 0;

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, searchKey) == 0) {
            if (count < maxIndices) {
                indices[count++] = i; // Store the index of the occurrence
            }
        }
    }

    displaySearch(students, indices, count);

    return count; // Return the number of occurrences
}

int searchID(Student students[], int studentCount, int searchKey, int indices[], int maxIndices) {
    int count = 0;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchKey) {
            if (count < maxIndices) {
                indices[count++] = i; // Store the index of the occurrence
            }
        }
    }

    displaySearch(students, indices, count);

    return count; // Return the number of occurrences
}
