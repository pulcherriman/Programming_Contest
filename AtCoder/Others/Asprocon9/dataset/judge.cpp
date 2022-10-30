#include <fstream>
#include <cassert>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "judge.h"
#define ASPROCON9_USE_RUNNER 

#ifdef _MSC_VER
#define ASPROCON9_USE_RUNNER
#endif

#ifdef ASPROCON9_USE_RUNNER

int reactive_start( std::string )
{
	return 0;
}

void reactive_end()
{}

void reactive_write( string buf )
{
	cout << buf << flush;
}

string reactive_read()
{
	string s;
	getline( std::cin, s );
	return s;
}

#else

#include "reactive.h"

#endif // ASPROCON9_USE_RUNNER


Judge create_judge( char* inputFileName = nullptr )
{
	Judge J;
	if( inputFileName != nullptr )
	{
		ifstream s( inputFileName );
		if( !s )
		{
			cerr << "cannot open input file " << inputFileName << endl;
			exit( 1 );
		}
		J.Input( s );
	}
	else
	{
		J.Input( cin );
	}

	return J;
}

ostringstream vis_out;

void PrintErrorMessage( const string& msg )
{
	cerr << "!!! Invalid Output !!! " << endl;
	cerr << "Error: " << msg << endl;
}

long long main_2( Judge& J )
{
	long long bestScore = 0;

	{
		stringstream ss;
		ss << J.week << ' ' << J.resourceN << ' ' << J.resCalendarChangeLimitN << ' ' << J.reactiveN << endl;
		vis_out << J.resourceN << ' ' << J.week << ' ' << J.reactiveN << '\n';
		for( auto& e : J.costTypeA )
		{
			ss << e.second << ' ' << J.costTypeB[e.first] << endl;
		}
		reactive_write( ss.str() );
	}

	auto CheckInput = [&J] ( const vector<string>& input ) -> bool
	{
		for( const string& s : input )
		{
			if( s.size() != static_cast<size_t>( J.week ) * 2 )
			{
				PrintErrorMessage( "The length of calendar pattern must be " + to_string( J.week * 2 ) );
				return false;
			}

			for( char c : s )
			{
				if( !( '1' <= c && c <= '9' ) )
				{
					PrintErrorMessage( "The Calendar pattern must be in the range 1~9" );
					return false;
				}
			}
		}

		return true;
	};

	for( int k = 0; k < J.reactiveN; k++ )
	{
		vector<string> input; // �Q���҂̏o�͎󂯎�� ... Receive output
		for( int j = 0; j < J.resourceN; j++ )
		{
			string s = reactive_read();
			if( !s.empty() && s.back() == '\n' )
			{
				s.pop_back();
			}
			vis_out << s << '\n';

			input.emplace_back( s );
		}

		if( !CheckInput( input ) )
		{
			return -1;
		}

		// �o�͂���J�����_�̐��� ... Generate calendar from output
		vector<vector<pair<int, int>>>calendar( J.resourceN );
		long long cost = 0;
		for( int i = 0; i < J.resourceN; i++ )
		{
			for( int j = 0; j < J.week; j++ )
			{
				int calendarTypeA = input[i][j * 2] - '1';
				int calendarTypeB = input[i][j * 2 + 1] - '1';
				Calendar.addCalendar( calendar[i], j, calendarTypeA, calendarTypeB );

				cost += J.costTypeA[{i, calendarTypeA}] + J.costTypeB[{i, calendarTypeB}];
			}
		}

		for( int j = 0; j < J.resourceN; j++ )
		{
			calendar[j].push_back( { 1'000'000'000, 2'000'000'000 } );
		}

		// ����t�� ... assignation
		auto [let, chLimVioCnt, loadRate, letOpCount] = J.sequenceForward( calendar, input );

		{ // ���� ... input
			long long score = ( let + chLimVioCnt ) == 0 ? round( ( 10.0 - log10( static_cast<double>( cost / J.week ) ) ) * 1e9 ) : 0;
			bestScore = max( bestScore, score );
			stringstream ss;
			ss << score << ' ' << chLimVioCnt << ' ' << let << endl;
			for( auto& e : loadRate )
			{
				ss << to_string( e.second ).substr( 0, 5 ) << ' ' << to_string( letOpCount[e.first] ).substr( 0, 5 ) << endl;
			}
			reactive_write( ss.str() );
		}

	}
	return bestScore;
}


#ifdef ASPROCON9_USE_RUNNER

int main( int argc, char** argv )
{
	if( argc <= 1 )
	{
		cerr << "usage: " << argv[0] << " input-file [output-file]\n";
		return 0;
	}

	Judge J = create_judge( argv[1] );

	reactive_start( argv[1] );
	long long result = main_2( J );
	reactive_end();

	if( argc > 2 )
	{
		if( ofstream f( argv[2] ); f )
		{
			f << result << '\n' << vis_out.str();
		}
		else
		{
			cerr << "cannot open output file: " << argv[2] << endl;
		}
	}

	long long score = max( result, 0LL );
	cerr << "Score = " << score << endl;
	return 0;
}

#else

int main( int argc, char** argv )
{
	if( argc <= 1 )
	{
		cerr << "usage: " << argv[0] << " <command>\n";
		return 0;
	}

	Judge J = create_judge();

	reactive_start( argv[1] );
	long long result = main_2( J );
	reactive_end();
	cout << result << '\n' << vis_out.str();

	long long score = max( result, 0LL );
	cerr << "Score = " << score << endl;
	return 0;
}

#endif // ASPROCON9_USE_RUNNER
