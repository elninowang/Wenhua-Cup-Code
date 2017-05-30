#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h>
typedef enum{false,true}bool;
char sHeader[100];		/* Header Key Table */
int nHeaderMax = 0;		/* The Length of Header Table */
char sStream[10000];		/* The Encoded Message */
int iNow = 0;			/* The Now Position of the Encoded Message */
int nStreamMax = 0;		/* The Length of Encode Message */
char sMessage[10000];		/* The Decoded Message */
int iMessage;			/* The Now Position of the Decoded Message */
/********************** Make 3 byte to Binary **********************/
int MakeBinary()
{
	int i;
	int nReturns = 0;	/* The Return Integer of the Function */
	for( i=2;i>=0;i--)
		nReturns+=pow(2,i)*sStream[iNow++];
	if( iNow > nStreamMax )
		return -1;
	return nReturns;
}
/********************** Get the Key's Length ***********************/
int GetBegin(nLen)
{
	if( nLen == 1 )
		return 0;
	return GetBegin(nLen-1)+pow(2,nLen-1)-1;
}
/************ Get the Index of the Map Table by the Key ************/
int MakeIndex(int nLen)
{
	int iBegin = GetBegin(nLen);
	int i,nIndex = 0;
	for( i=nLen-1;i>=0;i--)
		nIndex+=pow(2,i)*sStream[iNow++];
	if( nIndex == pow(2,nLen)-1 )
		return -2;
	if( iNow > nStreamMax )
		return -1;
	return iBegin+nIndex;
}
/******************** Decode the Encoded Message *******************/
int DecodeMessage()
{
	int nLen;			/* The Length of the Key */
	int nState;
	iNow = 0;
	iMessage = 0;
	while( 1 )
	{
		/***** Get the Length of the Key! *******/
		nLen = MakeBinary();
		if( !nLen )
		{
			sMessage[iMessage] = '\0';
			return 1;
		}
		else if( nLen == -1 )
			return 0;
		while( 1 )
		{
			/**** Map The Key to The Header File ******/
			nState = MakeIndex( nLen );
			if( nState == -1 )
				return 0;
			else if( nState == -2 )
				break;
			else if( nState >= nHeaderMax )
			{
				printf("\n !!Error! No this Key in Table !!");
				fclose( stdin );
				freopen( "con", "r", stdin );
				getch();
				exit(-1);
			}
			else
				sMessage[iMessage++] = sHeader[nState];
		}
	}
}
/********************** the Main Funtion  ****************************/
void main(void)
{

	char ch;
	int iTempCharPos = 0;
	char sInput[100];
	bool fIsHeader = true;
	printf("Please input the path of the input file\n");
	scanf( "%s", sInput);
	if( !freopen( sInput, "r", stdin))
	{
		printf("Can't open %s\n", sInput );
		freopen( "con", "r", stdin );
		getch();
		exit(-1);
	}

	iTempCharPos = 0;
	nStreamMax = 0;
	while( ( ch=getchar() )!=EOF )
	{
		if( ch == '\n' )
			if( fIsHeader )
			{
				if( iTempCharPos )
				{
					nHeaderMax = iTempCharPos;
					fIsHeader = false;
					iTempCharPos = 0;
					nStreamMax = 0;
				}
			}
		if( fIsHeader && ch != '\n' )
			sHeader[iTempCharPos++] = ch;

		else
		{
			if( ch != '\n' && ch != '\t' && ch!=' ' )
			{
				if( ch != '0' && ch != '1' )
				{
					printf("The encode message has the letter"
						" which is nether 0 nor 1!\n", sInput );
					fclose( stdin );
					freopen( "con", "r", stdin );
					getch();
					exit(-1);
				}
				sStream[iTempCharPos++] = ch-'0';
			}
			else if( ch == '\n' )
			{
				nStreamMax = iTempCharPos;
				if( DecodeMessage() )
				{
					printf("%s\n",sMessage);
					fIsHeader = true;
					iTempCharPos = 0;
					nStreamMax = 0;
				}
			}
		}
	}
	nStreamMax = iTempCharPos;
	if( DecodeMessage() )
	{
		printf("%s\n",sMessage);
		fIsHeader = true;
		iTempCharPos = 0;
		nStreamMax = 0;
	}
	fclose( stdin );
	freopen("con","r",stdin);
	getch();
}