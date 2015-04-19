/*
	Algorithmic Programming and Software Design 2014
	Week 4/5 Recursion Lab
	Exercise 4: Solving a maze
	Joshua Tyler 2014
	Based on skeletal code provided.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAZE_ROW_SIZE 25
#define MAZE_COL_SIZE 25

typedef struct coord
{
	int col;
	int row;
 struct	coord *next;
} coord;

void display(char mazeToPrint[MAZE_ROW_SIZE][MAZE_COL_SIZE]);
coord findStart(char mazeToFindStart[MAZE_ROW_SIZE][MAZE_COL_SIZE]);
coord* solve(char mazeToSolve[MAZE_ROW_SIZE][MAZE_COL_SIZE], coord curPos);
char** createArray(int rows, int cols);
void copyMaze(char copyTo[MAZE_ROW_SIZE][MAZE_COL_SIZE], char copyFrom[MAZE_ROW_SIZE][MAZE_COL_SIZE]);
coord adjacentBlanks(char maze[MAZE_ROW_SIZE][MAZE_COL_SIZE], coord curPos);
coord *createLinkedElement(coord *firstElement, coord elementToAdd);
void pointsToMaze(coord *header, char maze[MAZE_ROW_SIZE][MAZE_COL_SIZE]);

int main(void)
{
	//char** maze;
	//maze = createArray(MAZE_ROW_SIZE, MAZE_COL_SIZE);

	char mainMaze[MAZE_ROW_SIZE][MAZE_COL_SIZE];

	/* Read data from file and store in array */
	char inputfile[] = "maze.txt";
	FILE *pfile;
	pfile = fopen(inputfile,"r");
	if(pfile==NULL)
	{
		fprintf(stderr, "ERROR opening file %s for reading\n", inputfile);
		return 1;
	}
	int row, col;
	for(row=0;row<MAZE_ROW_SIZE;row++)
	{
		for(col=0;col<MAZE_COL_SIZE;col++)
		{
			mainMaze[row][col]=(char)fgetc(pfile);
		}
        char endOfLine[3];
		fgets(endOfLine, 3, pfile); /* read end of line character (may vary between OS) */
	}
	fclose(pfile);

	/* Display maze */
	printf("Unsolved Maze:\n");
	display(mainMaze);

	coord start;

	start = findStart(mainMaze);

	coord *points;
	char scrapMaze[MAZE_ROW_SIZE][MAZE_COL_SIZE];

	copyMaze(scrapMaze, mainMaze);

	points = solve(scrapMaze, start);

	pointsToMaze(points, mainMaze);

	//display(scrapMaze);

	printf("Solved Maze:\n");
	display(mainMaze);


	return EXIT_SUCCESS;
}

void display(char mazeToPrint[MAZE_ROW_SIZE][MAZE_COL_SIZE])
{
	int row, col;
	for(row=0;row<MAZE_ROW_SIZE;row++)
	{
		for(col=0;col<MAZE_COL_SIZE;col++)
		{
			printf("%c",mazeToPrint[row][col]);
		}
		printf("\n");
	}
	printf("\n");
}

coord findStart(char mazeToFindStart[MAZE_ROW_SIZE][MAZE_COL_SIZE])
{
	coord start;


	for(start.row = 0; start.row < MAZE_ROW_SIZE; start.row++)
	{
		for(start.col = 0; start.col < MAZE_COL_SIZE; start.col++)
		{
			if( mazeToFindStart[start.row][start.col] == 'I')
				return start;
		}
	}

	puts("Start not found");
	exit(EXIT_FAILURE);
}

coord *solve(char mazeToSolve[MAZE_ROW_SIZE][MAZE_COL_SIZE], coord curPos)
{
	coord *returnList = NULL;
	if(mazeToSolve[curPos.row][curPos.col] == 'O')
	{
		returnList = createLinkedElement(returnList, curPos);
		return returnList;
	}

	mazeToSolve[curPos.row][curPos.col] = 'P';

	//display(mazeToSolve);

	//getchar(); //Pause for input

	coord newPos;

	for(newPos = adjacentBlanks(mazeToSolve, curPos); newPos.row != -1; newPos = adjacentBlanks(mazeToSolve, curPos))
	{
		returnList = solve(mazeToSolve, newPos);

		if(returnList != NULL)
		{
			returnList = createLinkedElement(returnList, curPos);
			return returnList;
		}
	}

	return returnList;
}

char** createArray(int rows, int cols)
{
	char ** returnVal;
	returnVal = (char**) malloc(rows*sizeof(double*));  
	for (int i = 0; i < rows; i++)  
		returnVal[i] = (char*) malloc(cols*sizeof(double));

	return returnVal;
}

void copyMaze(char copyTo[MAZE_ROW_SIZE][MAZE_COL_SIZE], char copyFrom[MAZE_ROW_SIZE][MAZE_COL_SIZE])
{
	int row, col;
	for(row=0;row<MAZE_ROW_SIZE;row++)
	{
		for(col=0;col<MAZE_COL_SIZE;col++)
		{
			copyTo[row][col]=copyFrom[row][col];
		}
	}
	return;
}

coord adjacentBlanks(char maze[MAZE_ROW_SIZE][MAZE_COL_SIZE], coord curPos)
{
	coord newPos;
	newPos.row = -1;
	
	// up
	if( curPos.row < MAZE_ROW_SIZE )
		if ( maze[curPos.row -1][curPos.col] == ' ' || maze[curPos.row -1][curPos.col] == 'O')
		{
			newPos.row = curPos.row -1;
			newPos.col = curPos.col;
			return newPos;
		}

	// left
	if( curPos.col > 0)
		if ( maze[curPos.row][curPos.col -1] == ' ' || maze[curPos.row][curPos.col-1] == 'O')
		{
			newPos.row = curPos.row;
			newPos.col = curPos.col -1;
			return newPos;
		}

	// right
	if( curPos.col < MAZE_COL_SIZE )
		if ( maze[curPos.row][curPos.col +1] == ' ' || maze[curPos.row][curPos.col +1] == 'O')
		{
			newPos.row = curPos.row;
			newPos.col = curPos.col +1;
			return newPos;
		}

	// down
	if( curPos.row > 0 )
		if ( maze[curPos.row +1][curPos.col] == ' ' || maze[curPos.row +1][curPos.col] == 'O')
		{
			newPos.row = curPos.row +1;
			newPos.col = curPos.col;
			return newPos;
		}

	return newPos;
}

// Add to start of list
coord *createLinkedElement(coord *firstElement, coord elementToAdd)
{
	coord *newElement;
	newElement = (coord *)malloc(sizeof(coord));
	if(newElement == NULL)
	{
		puts("Memory error");
		exit(EXIT_FAILURE);
	}

	newElement->col = elementToAdd.col;
	newElement->row = elementToAdd.row;
	newElement->next = firstElement;

	return newElement;
}

void pointsToMaze(coord *header, char maze[MAZE_ROW_SIZE][MAZE_COL_SIZE])
{
	while(header != NULL)
	{
		maze[header->row][header->col] = 'P';

		header = header ->next;
	}

	return;
}