// generator

#include "Problem.h"
#include "gen.h"

int main( int argc, char* argv[] )
{
	string outputfile_name = "";
	if( argc >= 2 ) outputfile_name = argv[1];
	string INPUT;
	for( int i = 0; getline( cin, INPUT ); i++ )
	{
		Generator G;
		G.Generate( i, INPUT, outputfile_name );
		G.Output();

	}
}
