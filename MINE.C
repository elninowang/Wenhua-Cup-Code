#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define		MAXMINE        10000
#define		MADED				0
#define		ROADTOMINE		1
#define		ROADTOBASE		2
#define		EXPLORING		3
#define		ISWAITING		4
typedef enum{false,true}bool;

typedef struct Robot{
	char nWhere;		         /* Where is the Robot */
	unsigned iTempTime;	/* The Time the Robot Go to Next State */
}Robot,*LPRobot;
typedef struct Base{
	bool fMaking;		/* Whether the Base is Producing Robot */
}Base;
typedef struct Mine{
	bool fExploring;	/* Whether the Mine is been exploring */
	bool fPopping;		/* whether a Robot Go Out the Queue */
	int *aQueue;		/* the Queue Pointer */
	int nBegin;			/* the Beginning Position of the Queue */
	int nEnd;			/* the End Position of the Queue */
	int iPop;			/* the Index of the Robot That will Go ut of the Queue */
}Mine;

LPRobot		lpRobot;	/* the Robot pointor */
Base		base;			/* the Base Item */
Mine		mine;			/* the Mine Item */
unsigned long S,W,C,K,M;		/* the Parameter must be Input */

unsigned long nTime=0;		/* the Time from Begibibg to Now */
unsigned int nMine=0;		/* the Mine which Robots have got */
unsigned int nRobot=0;		/* the Number of the robots Working */
unsigned int nMinTime=0;	/* the Time beteen This State to Next state */

/******************* The Base Begin to Produce Robot ***********/
void MakeRobot()
{
	if( nRobot >= K )
		return;
	(lpRobot+nRobot)->nWhere = MADED;
	(lpRobot+nRobot)->iTempTime = M;
	nRobot++;
}
/******************* Data Structure Functions *******************/
/******************* Push Into the Queue ************************/
void Push(int iRobot)
{
	mine.aQueue[ (mine.nEnd++)%K ] = iRobot;
}
/******************* Pop Out of the Queue ***********************/
int Pop()
{
	return mine.aQueue[ (mine.nBegin++)%K ];
}
/******************* Chech whether the queue is empty ***********/
bool IsQueue()
{
	if( mine.nBegin == mine.nEnd )
		return false;
	else return true;
}
/******************* Get What the Robots will be doing
			in the Next State ***********************/
void NextRobot(int iRobot)
{
	LPRobot lpTemp=lpRobot+iRobot;
	if( !lpTemp->iTempTime )
	{
		switch( lpTemp->nWhere )
		{
		case MADED:
			base.fMaking = 0;
			lpTemp->nWhere = ROADTOMINE;
			lpTemp->iTempTime = S;
			break;
		case ROADTOBASE:
			nMine += C;
			lpTemp->nWhere = ROADTOMINE;
			lpTemp->iTempTime = S;
			break;
		case ROADTOMINE:
			if( !mine.fExploring )
			{
				lpTemp->nWhere = EXPLORING;
				lpTemp->iTempTime = W;
				mine.fExploring = true;
			}
			else
			{
				Push(iRobot);
				lpTemp->nWhere = ISWAITING;
			}
			break;
		case EXPLORING:
			lpTemp->nWhere = ROADTOBASE;
			lpTemp->iTempTime = S;
			if( IsQueue() )
			{
				int iTempRobot=Pop();
				mine.fPopping = true;
				mine.iPop = iTempRobot;
			}
			else
				mine.fExploring = false;
			break;
		default:
			break;
		}
	}
}
/****** Get the Time between this state and the next State. *******/
void CheckMinTime()
{
	int i,j=0;
	while( (lpRobot+j)->nWhere == ISWAITING )
		j++;
	nMinTime = (lpRobot+j)->iTempTime;
	for( i=j+1; i<nRobot; i++ )
		if( (lpRobot+i)->nWhere != ISWAITING && nMinTime > (lpRobot+i)->iTempTime )
			nMinTime = (lpRobot+i)->iTempTime;
}
/******************** Do One Sample ********************************/
void GetMine()
{
	int i;
	LPRobot lpTempRobot;		/* Use to Free System Space */

	base.fMaking = false;
	mine.fExploring = false;
	mine.nBegin = 0;
	mine.nEnd = 0;
	mine.fPopping = false;
	lpRobot = (LPRobot)malloc( K*sizeof(Robot) );
	mine.aQueue = (int*)malloc( K*sizeof(int) );

	nTime=0;
	nMine=0;
	nRobot=0;
	nMinTime=0;

	while( nMine < MAXMINE )
	{
		/***** whether the Base will Produce Robots *****/
		if( base.fMaking == 0 )
		{
			MakeRobot();
			base.fMaking = true;
		}
		CheckMinTime();
		/***** All the Robots go to the next Robots *****/
		for( i=0; i<nRobot; i++)
		{
			if( (lpRobot+i)->nWhere != ISWAITING )
				(lpRobot+i)->iTempTime-=nMinTime;
		}
		/***** Get the new State ************************/
		for( i=0; i<nRobot; i++)
			NextRobot( i );
		/***** Some Robots Pop the Queue ****************/
		if( mine.fPopping == true )
		{
			(lpRobot+mine.iPop)->nWhere = EXPLORING;
			(lpRobot+mine.iPop)->iTempTime = W;
			mine.fPopping =false;
		}
		nTime+=nMinTime;
	}
	printf("%lu\n",nTime);

	free( lpRobot );
	free( mine.aQueue );
}
/******************* The Main Function ***********************************/
void main(void)
{
	int i,n;
	int judge;
	printf("\nPlease Input the Number of The Text Case Which Consists of 5 Integers:\n");
	scanf("%d", &n);
	for( i=0; i<n; i++ )
	{
		printf("%d:  Please Input S W C K M:\n",i+1);
		scanf("%u %u %u %u %u",&S,&W,&C,&K,&M);

		if( C == 0 || K == 0)
		{
			printf( "Input Wrong!\n" );
			continue;
		}

		if (W==0)
		{
			if (K > 10000) K=10000;
			GetMine();
		}
		else if (K>(2*S)/W+2)
		{
			K=(2*S)/W+2;
			if( K > 10000 )
				K = 10000;
			GetMine();
		}
		else if (K > 10000)
		{
			K=10000;
			GetMine();
		}
		else GetMine();
	}
	getch();
}
