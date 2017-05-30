#include <stdio.h>
#include <conio.h>
#define		IS_CHAR			-1
#define		NOT_FREE			-1
#define		STACK_SIZE		10
#define		OP_DOUBLE		2
#define		OP_DOUBLE2		3
#define		OP_DOUBLE3		4
#define		OP_SINGLE    	1
#define		NOT_OP			0
#define		OP_FALSE			-1
#define		INPUT_SIZE		100
typedef enum {false,true} bool;

int iStack;						/* it's not only Virtual Memory but also a Stack Top */
char sExpresstion[INPUT_SIZE];	/* Expresstion */
int iExpresstion = 0;		/* the now Position of the Expresstion */

/******************* Clear the Virtual Stack *********************************/
void Clear()
{
	iStack = 0;
}
/*************************** Push Stack **************************************/
void Push()
{
	fprintf( stdout,"ST %d\n", iStack);
	iStack++;
}

/************************* Operation Negate **********************************/
void Negate()
{
	fprintf( stdout,"N\n");
}
/******* Opertion '+','*',and now the Outcome is the Second place ************/
void Double2(char cOperator)
{
	switch( cOperator )
	{
	case '+':
		fprintf( stdout,"A $%d\n", iStack-1);
		break;
	case '*':
		fprintf( stdout,"M $%d\n", iStack-1);
		break;
	}
	iStack--;
}
/******* Opertion '-','/',and now the Outcome is the Second place ************/
void Double3(char cOperator)
{
	Push();
	fprintf( stdout,"L $%d\n",iStack-2);
	switch( cOperator )
	{
	case '-':
		fprintf( stdout,"S $%d\n", iStack-1);
		break;
	case '/':
		fprintf( stdout,"D $%d\n", iStack-1);
		break;
	}
	iStack-=2;
}
/******* Opertion '+','-','*','/',and now the Outcome is the Second place *****/
void Double(char cNext, char cOperator)
{
	switch( cOperator )
	{
	case '+':
		fprintf( stdout,"A %c\n", cNext );
		break;
	case '-':
		fprintf( stdout,"S %c\n", cNext );
		break;
	case '*':
		fprintf( stdout,"M %c\n", cNext );
		break;
	case '/':
		fprintf( stdout,"D %c\n", cNext );
		break;
	}
}

int CheckOperater()
{
	/*if( CheckChar( sExpresstion[iExpresstion]== NOT_OP )*/
	{
		if(  sExpresstion[iExpresstion+1]!= '\0'
			&& iStack >= 0
			&& CheckChar( sExpresstion[iExpresstion+1] ) == OP_SINGLE )
			return OP_SINGLE;
		else if( sExpresstion[iExpresstion+1] != '\0'
			&& iStack > 0
			&&( sExpresstion[iExpresstion+1] == '+'
				|| sExpresstion[iExpresstion+1] == '*') )
			return OP_DOUBLE2;
		else if( sExpresstion[iExpresstion+1] != '\0'
			&& iStack > 0
			&& (sExpresstion[iExpresstion+1] == '-'
				|| sExpresstion[iExpresstion+1] == '/') )
			return OP_DOUBLE3;
		else if( iStack >= 0
			&& sExpresstion[iExpresstion+1]!= '\0'
			&& sExpresstion[iExpresstion+2]!= '\0'
			&& CheckChar( sExpresstion[iExpresstion+2] ) == OP_DOUBLE )
			return OP_DOUBLE;
		else if( sExpresstion[iExpresstion+1] == '\0'
			|| sExpresstion[iExpresstion+2] == '\0' )
			return OP_FALSE;
		else return NOT_OP;
	}
}
/******* Check the Character is Double Operator,Single Operator or Not **************/
int CheckChar(char cNow)
{
	if( cNow == '@' )
		return OP_SINGLE;
	else if( cNow == '+' || cNow == '-' ||
				cNow == '*' || cNow == '/' )
		return OP_DOUBLE;
	else
		return NOT_OP;
}
/*********************** Direct Load Charector to Register **************************/
void LoadChar(char cNow)
{
	fprintf( stdout,"L %c\n",cNow);
}
/******************** Whether the Expresstion Right or Wrong ************************/
bool Check()
{
	int iTempExpresstion = 0;
	int iTempStack = 0;

	while( sExpresstion[iTempExpresstion]!= '\0' )
	{
		if( CheckChar( sExpresstion[iTempExpresstion] ) == NOT_OP )
			iTempStack++;
		else if( CheckChar( sExpresstion[iTempExpresstion] ) == OP_DOUBLE )
			iTempStack--;
		if( iTempStack < 0 )
			return false;
		iTempExpresstion++;
	}
	if( iTempStack != 1 )
		return false;

	return true;
}
/************************** Making Assemble *******************************/
void MakeAssemble()
{
	int nState;
	bool fRight;

	iExpresstion = 0;
	iStack = 0;
	fRight = Check();
	while( fRight )
	{
		if( sExpresstion[iExpresstion] == '\0' )
			break;
		if( CheckChar( sExpresstion[iExpresstion] ) == NOT_OP )
			LoadChar( sExpresstion[iExpresstion] );
		nState = CheckOperater();
		if( nState == NOT_OP )
		{
			Push();
			iExpresstion++;
		}
		if( nState == OP_FALSE )
			break;
		while( nState != NOT_OP )
		{
			nState = CheckOperater();
			if( nState == OP_FALSE )
				break;
			switch( nState )
			{
			case OP_SINGLE:
				Negate();
				iExpresstion+=1;
				break;
			case OP_DOUBLE2:
				Double2( sExpresstion[iExpresstion+1] );
				iExpresstion+=1;
				break;
			case OP_DOUBLE3:
				Double3( sExpresstion[iExpresstion+1] );
				iExpresstion+=1;
				break;
			case OP_DOUBLE:
				iExpresstion++;
				Double( sExpresstion[iExpresstion], sExpresstion[iExpresstion+1] );
				iExpresstion += 1;
				break;
			}
		}
	}
	if( !fRight )
		fprintf( stdout,"Sorry! This Expression is Wrong!");
	fprintf( stdout,"\n");
	iExpresstion = 0;
}
/************************* The Main Function ************************************/
void main(void)
{
	char ch;
	char sInput[50];
	char sOutPut[50];

	printf("Please input the path of InPut file:\n");
	scanf("%s", sInput );
	printf( "Please input the path of Output file:\n");
	scanf("%s", sOutPut);
	if( !freopen( sInput, "r", stdin))
	{
		printf( "Can't open %s\n", sInput );
		freopen( "con", "r", stdin );
		getch();
		exit(-1);
	}

	if( !freopen( sOutPut, "w", stdout))
	{
		printf( "Can't Create %s\n", sOutPut );
		getch();
		exit(-1);
	}
	iExpresstion = 0;
	while( ( ch=getchar() )!=EOF )
	{
		if( ch == '\n' )
		{
			sExpresstion[iExpresstion] = '\0';
			MakeAssemble();
			iExpresstion = 0;
		}
		else if( ch != '\t' && ch != ' ' )
			sExpresstion[iExpresstion++] = ch;
	}
	sExpresstion[iExpresstion] = '\0';
	MakeAssemble();
	fclose( stdin );
	fclose( stdout );

	freopen("con","r",stdin);
}