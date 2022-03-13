#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ERROR -1
#define maxArraySize 256

// III IIO IOI IOO OII OIO OOI OOO
//Translated 3 digits given using the code given into either a 1 or a 0.
int translation(int firstDGT, int secondDGT, int thirdDGT, int binary[]){
	if(firstDGT == 1){
		if(secondDGT == 1){
			if(thirdDGT==1){
				return binary[0];
			}else
				return binary[1];
		}else{
			if(thirdDGT==1){
				return binary[2];
			}else
				return binary[3];
		}
	}else{
		if(secondDGT == 1){
			if(thirdDGT==1)
				return binary[4];
			else
				return binary[5];
		}else{
			if(thirdDGT==1){
				return binary[6];
			}else
				return binary[7];
		}
	}
}

//Gets a starting line given a length and a array to save it to.
void getStartingLine(int line[], int length){
	for(int i=0;i<length;i++){
		line[i]=0;
	}
	line[length/2]=1;
}

void getRandomStartingLine(int line[], int length){
	for(int i=0;i<length;i++){
		line[i]=rand() % 2;
	}
}

//Gets the length of the first line of a file given
int getFileSize(char filename[]){
	FILE *file;
    file = fopen(filename, "r");
    if (file != NULL)
    {
    	char line[maxArraySize];
    	fgets(line, maxArraySize, file);
    	fclose(file);
    	return(strlen(line)-1);
    }
    else{
    	return(ERROR);
    }
}

//Gets the first line of a file and saves it to an array given
void getStartingLineFile(int startingLine[], char filename[], int fileLength){
	FILE *file;
    file = fopen(filename, "r");
    if (file != NULL){
    	char line[fileLength];
    	int iterator = 0;
    	for(int iterator = 0; iterator < fileLength; iterator++){
      		line[iterator] = (char)fgetc(file);
      		startingLine[iterator] = line[iterator] - '0';
    	}
    }
    fclose(file);
}

// length of the array, rule array, array to use rule on, iterator = 0, how many iterations you wish to run the method
void generate(int length,int array[],int fileArray[],int iterator,int iterations) {

	FILE *file;
	file = fopen("generateToFile", "a");
	iterator++;
	int nextGeneration[length];
	int left, middle, right = 0;

	for (int n=0; n < length; n++){
		if(fileArray[n]==0){
			printf("□ ");
		}
		else{
			printf("■ ");
		}
		//send to file
		fprintf(file, "%d", fileArray[n]);
	}
	//if i = 0 or i = fileArray.length-1; left = fileArray[fileArray.length-1], right = filleArray[0] 
	for(int i = 0; i < length; i++){
		if(i == 0 )
		{
			left = fileArray[length-1];
		}
		else{
		left = fileArray[i-1]; 
		}
		middle = fileArray[i];

		if(i == length-1)
		{
			right = fileArray[0];
		}
		else{ 
		right = fileArray[i+1];
		}
		nextGeneration[i] = translation(left, middle, right, array);
	}
	printf("\n");
	//copy array into current value 
	

	fprintf(file, "\n");

		fclose(file);
	if(iterator < iterations)
	{
		generate(length, array, nextGeneration, iterator, iterations);
	}
}

//Set all values in a 2D array to be 0
void initialise2DArray(int length, int width, int array[][width]){
	for(int i=0; i<length; i++){
		for(int counter=0;counter<width;counter++){
			array[i][counter]=0;
		}
	}
}

//Set all values in a 2D array to be 0 or 1 randomly
void initialiseRandom2DArray(int length, int width, int array[][width]){
	for(int i=0; i<length; i++){
		for(int counter=0;counter<width;counter++){
			array[i][counter]=rand() % 2;
			printf("%d",array[i][counter]);
		}
	}
}

//Set character in a array
void setCharacter(int width, int set, int array[]){
	array[width]=set;
}

//display a 2D array
void display2DArray(int length, int width, int array[][width]){
	for(int i=0; i<length; i++){
		for(int counter=0;counter<width;counter++){
			if(array[i][counter]==1){
				printf("■ ");
			}
			else{
				printf("□ ");
			}
			// printf("%d ", array[i][counter]);
		}
		printf("\n");
	}
}

//Count the number of surrounding squares that are 1 to a given square in a 2D array
int countSurroundingOnes(int length, int width, int counterY, int counterX, int array[][width]){
	//Check if the y counter needs to loop around at the start 
	int minusY;
	if(counterY==0){
		//if it needs to loop set the minusY variable to the opposite side of the array
		minusY=length-1;
	}
	else {
		//else just set minus y to one less than were Y is
		minusY = counterY-1;
	}

	//Do the same but see if Y needs to wrap at the end of the array
	int plusY;
	if(counterY==length-1){
		plusY=0;
	}
	else {
		plusY = counterY+1;
	}

	//Do this again but for X's instead of Y's
	int minusX;
	if(counterX==0){
		minusX=width-1;
	}
	else {
		minusX = counterX-1;
	}

	int plusX;
	if(counterX==width-1){
		plusX=0;
	}
	else {
		plusX = counterX+1;
	}

	//Initialise counter of the surrounding squares
	int totalSurroundingSquares =0;

	//Add 1 if it matches any of the surrounding squares.
	if(array[minusY][minusX]==1){
		totalSurroundingSquares++;
	}
	if(array[minusY][counterX]==1){
		totalSurroundingSquares++;
	}
	if(array[minusY][plusX]==1){
		totalSurroundingSquares++;
	}
	if(array[counterY][minusX]==1){
		totalSurroundingSquares++;
	}
	if(array[counterY][plusX]==1){
		totalSurroundingSquares++;
	}
	if(array[plusY][minusX]==1){
		totalSurroundingSquares++;
	}
	if(array[plusY][counterX]==1){
		totalSurroundingSquares++;
	}
	if(array[plusY][plusX]==1){
		totalSurroundingSquares++;
	}
	// }
	//return the number
	return(totalSurroundingSquares);
}

//Run the game of life for one cycle - saving the output to the original array
void cycleArray(int length, int width, int array[][width]){
	int tempInt = 0;
	int tempArray[length][width];

	for(int i=0; i<length; i++){
		for(int counter=0;counter<width;counter++){
			tempInt = countSurroundingOnes(length,width,i,counter,array);
			if(array[i][counter] == 0){
				if(tempInt==3){
					tempArray[i][counter]=1;
				}
				else{
					tempArray[i][counter]=0;
				}
			}
			else if(array[i][counter] == 1){
				if(tempInt <2){
					tempArray[i][counter]=0;
				}
				else if(tempInt>3){
					tempArray[i][counter]=0;
				}
				else{
					tempArray[i][counter]=1;
				}
			}
		}
	}

	for(int i=0; i<length; i++){
		for(int counter=0;counter<width;counter++){
			array[i][counter]=tempArray[i][counter];
		}
	}
}

//Delays the program for the number of seconds given
void delay(int number_of_seconds){ 
    clock_t start_time = time(NULL); 
    while (time(NULL) < start_time + number_of_seconds); 
} 

//Runs game of life and displays each iteration
void displayGOL(int length, int width, int array[][width], int iterations){
	printf("\n");
	display2DArray(length,width,array);
	for(int i =0; i< iterations; i++){
		printf("\n");
		delay(1);
		cycleArray(length,width,array);
		display2DArray(length,width,array);
	}
}

//Changes the direction the ant in Langstons ant is moving
int changeDirection(int number, int direction){
	if(direction == 1){
		number--;
	}
	else{
		number++;
	}
	if(number<0){
		number=3;
	}
	if(number>3){
		number=0;
	}
	return number;
}

//Runs a cellular automata given a filename, a rule and the number of times it's wanted to run
void startingLineFile(char fileName[], int ruleArray[], int iterations){
	//get file size
	int fileSize = getFileSize(fileName);
	//make sure it returned well and if so initialise array of the length given
	if(fileSize != ERROR){
		int startingLine[fileSize];
		//Save line to array
		getStartingLineFile(startingLine, fileName, fileSize);
		//Just for printing
		generate(fileSize, ruleArray, startingLine, 0, iterations);
	}
	else{
		printf("File doesn't exist. Please create a file called %s with an arra of 1's and 0's in it", fileName);
	}
	printf("\n");
}

//Runs a cellular automata given a rule, the number of times it's wanted to run
void startingLineNoFile(int ruleArray[], int iterations, int width, int random){
	int startingLine[width];
	if(random == 0){
		getStartingLine(startingLine,width);
	}
	else{
		getRandomStartingLine(startingLine,width);
	}
	generate(width, ruleArray, startingLine, 0, iterations);
	printf("\n");
}

//Testing for modular automata stuff
void ruleStuff(){
	int iterations = 40;
	printf("\nTranslating 101 using rule 30");
	int array[8] = {0,0,0,1,1,1,1,0};

	printf("\nUsing File:\n");
	startingLineFile("starter.txt", array, iterations);
	printf("\nUsing Random Line:\n");
	startingLineNoFile(array, iterations, 103, 1);	
	printf("\nUsing Single Dot:\n");
	startingLineNoFile(array, iterations, 103, 0);	
}

//Converts an integer to binary and saves it in the array "binary"
void binaryConverter(int translate, int binary[]){
	int divider=128;
	for(int i = 0; i<8; i++){
		if(translate>=divider){
			binary[i]=1;
			translate = translate-divider;
		}
		else{
			binary[i]=0;
		}
	divider = divider/2;
	}
}

//The menu for the celluar automata.
void automataMenu(){
	int rule[8];
	int iterates, width, tempInt;
	int loop = 1;
	while(loop==1){
		loop=0;
		printf("\nWhat rule would you like to use? Please insert an integer\n");
		scanf("%d",&tempInt);
		if(tempInt>255||tempInt<0){
			printf("\nThis number isn't able to be translated into 8 bit binary\n");
			loop=1;
		}
	}
	binaryConverter(tempInt, rule);
	printf("\nHow many times do you want to iterate through the rule?\n");
	scanf("%d", &iterates);
	printf("\nWhat sort of starting line do you want?\n1: A one in the middle\n2: Random starting line\n3: Line read in from file\n");
	scanf("%d",&tempInt);
	if(tempInt==1||tempInt==2){
		printf("\nWhat would you like the width of the line to be?\n");
		scanf("%d",&width);
		if(tempInt==1){
			startingLineNoFile(rule, iterates, width, 0);	
		}else{
			startingLineNoFile(rule, iterates, width, 1);	
		}
	}
	else{
		char filename[256];
		printf("\nPlease insert the name of the file you would like to read from\n");
		scanf("%s",filename);
		startingLineFile(filename,rule,iterates);
	}
}

//Runs game of life
void gameOfLife(){
	int gridNo;
	int iterations;
	int length;
	int width;

	printf("What game of life grid would you like to display?\n\t1: Glider\n\t2: Pulsar\n\t3: Random\n\t4: Custom\n");
	scanf("%d", &gridNo);
	printf("How many iterations would you like to display?\n");
	scanf("%d", &iterations);

	//glider
	if(gridNo==1){
		length = 15;
		width = 15;
		int TwoDArray[length][width];
		initialise2DArray(length,width,TwoDArray);
		//One glider
		setCharacter(10,1,TwoDArray[10]);
		setCharacter(10,1,TwoDArray[11]);
		setCharacter(10,1,TwoDArray[12]);
		setCharacter(9,1,TwoDArray[12]);
		setCharacter(8,1,TwoDArray[11]);
		//Second glider
		setCharacter(3,1,TwoDArray[3]);
		setCharacter(3,1,TwoDArray[4]);
		setCharacter(3,1,TwoDArray[5]);
		setCharacter(2,1,TwoDArray[5]);
		setCharacter(1,1,TwoDArray[4]);
		displayGOL(length, width, TwoDArray, iterations);
	}
	//Pulsar
	else if(gridNo==2){
		length = 17;
		width = 17;
		int TwoDArray[length][width];
		initialise2DArray(length,width,TwoDArray);
		//inside
		//top left
		setCharacter(7,1,TwoDArray[6]);
		setCharacter(7,1,TwoDArray[5]);
		setCharacter(7,1,TwoDArray[4]);
		setCharacter(6,1,TwoDArray[7]);
		setCharacter(4,1,TwoDArray[7]);
		setCharacter(5,1,TwoDArray[7]);
		//top right
		setCharacter(9,1,TwoDArray[6]);
		setCharacter(9,1,TwoDArray[4]);
		setCharacter(9,1,TwoDArray[5]);
		setCharacter(6,1,TwoDArray[9]);
		setCharacter(4,1,TwoDArray[9]);
		setCharacter(5,1,TwoDArray[9]);
		//Bottom left
		setCharacter(7,1,TwoDArray[12]);
		setCharacter(7,1,TwoDArray[11]);
		setCharacter(7,1,TwoDArray[10]);
		setCharacter(12,1,TwoDArray[7]);
		setCharacter(10,1,TwoDArray[7]);
		setCharacter(11,1,TwoDArray[7]);
		//bottom right
		setCharacter(9,1,TwoDArray[12]);
		setCharacter(9,1,TwoDArray[10]);
		setCharacter(9,1,TwoDArray[11]);
		setCharacter(12,1,TwoDArray[9]);
		setCharacter(10,1,TwoDArray[9]);
		setCharacter(11,1,TwoDArray[9]);
		//outside
		//top left
		setCharacter(2,1,TwoDArray[6]);
		setCharacter(2,1,TwoDArray[5]);
		setCharacter(2,1,TwoDArray[4]);
		setCharacter(6,1,TwoDArray[2]);
		setCharacter(4,1,TwoDArray[2]);
		setCharacter(5,1,TwoDArray[2]);
		//top right
		setCharacter(14,1,TwoDArray[6]);
		setCharacter(14,1,TwoDArray[4]);
		setCharacter(14,1,TwoDArray[5]);
		setCharacter(6,1,TwoDArray[14]);
		setCharacter(4,1,TwoDArray[14]);
		setCharacter(5,1,TwoDArray[14]);
		//Bottom left
		setCharacter(2,1,TwoDArray[12]);
		setCharacter(2,1,TwoDArray[11]);
		setCharacter(2,1,TwoDArray[10]);
		setCharacter(12,1,TwoDArray[2]);
		setCharacter(10,1,TwoDArray[2]);
		setCharacter(11,1,TwoDArray[2]);
		//bottom right
		setCharacter(14,1,TwoDArray[12]);
		setCharacter(14,1,TwoDArray[10]);
		setCharacter(14,1,TwoDArray[11]);
		setCharacter(12,1,TwoDArray[14]);
		setCharacter(10,1,TwoDArray[14]);
		setCharacter(11,1,TwoDArray[14]);
		displayGOL(length, width, TwoDArray, iterations);
	}
	//Random
	else if(gridNo==3){
		length = 53;
		width = 100;
		int TwoDArray[length][width];
		initialiseRandom2DArray(length,width,TwoDArray);
		displayGOL(length, width, TwoDArray, iterations);
	}
	//My own stuff
	else if(gridNo==4){
		length = 20;
		width = 30;
		int TwoDArray[length][width];
		initialise2DArray(length,width,TwoDArray);
		setCharacter(width-1,1,TwoDArray[length-1]);
		setCharacter(width-1,1,TwoDArray[0]);
		setCharacter(0,1,TwoDArray[length-1]);
		setCharacter(0,1,TwoDArray[0]);
		setCharacter(0,1,TwoDArray[1]);
		setCharacter(1,1,TwoDArray[1]);
		setCharacter(2,1,TwoDArray[2]);
		//Glider
		setCharacter(10,1,TwoDArray[10]);
		setCharacter(10,1,TwoDArray[11]);
		setCharacter(10,1,TwoDArray[12]);
		setCharacter(9,1,TwoDArray[12]);
		setCharacter(8,1,TwoDArray[11]);
		//Rotating stick
		setCharacter(13,1,TwoDArray[7]);
		setCharacter(13,1,TwoDArray[8]);
		setCharacter(13,1,TwoDArray[9]);
		displayGOL(length, width, TwoDArray, iterations);
	}
	else{
		return;
	}
}

//Runs langtons ant
void langtonsAnt(){
	/*
	  o
	3   1
	  2
	*/
	int iterations;
	int length;
	int width;
	int direction = 1;
	
	printf("What width do you want it to be?\n");
	scanf("%d",&width);
	printf("What length do you want it to be?\n");
	scanf("%d",&length);
	printf("How many iterations would you like to display? (A large number such as 100,000 is better)\n");
	scanf("%d", &iterations);

	int antLength = length/2;
	int antWidth = width/2;
	int twoDArray[length][width];

	initialise2DArray(length,width,twoDArray);

	for(int i=0; i < iterations; i++){
		printf("\n");
		display2DArray(length,width,twoDArray);

		//Change direction then flip current square.
		if(twoDArray[antLength][antWidth]==0){
			direction = changeDirection(direction,0);
			twoDArray[antLength][antWidth]=1;

		}
		else{
			direction = changeDirection(direction,1);
			twoDArray[antLength][antWidth]=0;
		}
		
		if(direction==0){
			antLength++;
		}
		else if(direction==1){
			antWidth++;
		}
		else if(direction==2){
			antLength--;
		}
		else if(direction==3){
			antWidth--;
		}

		if(antWidth<0){
			antWidth=width-1;
		}
		else if(antWidth>(width-1)){
			antWidth=0;
		}
		if(antLength<0){
			antLength=length-1;
		}
		else if(antLength>(length-1)){
			antLength=0;
		}
	}
}

//CHOW MEIN!
int main(){
	int collector;

	printf("1: Langstons Ant\n2: Game of Life\n3: Cellular Automata\n");
	scanf("%d", &collector);
	if (collector==1){
		langtonsAnt();
	}
	else if(collector==2){
		gameOfLife();
	}
	else if(collector==3){
		automataMenu();
	}
}