

#include <tuple>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <random>

using namespace std;

class Solver
{
public:

	int reactiveN;
	int weeks;
	int resourceN;
	int chLimitN;
	std::map<tuple<int, int>, int> costA;
	std::map<tuple<int, int>, int> costB;

	long long bestScore = 0;

	explicit Solver()
	{

	}

	void input_init()
	{
		cin >> weeks >> resourceN >> chLimitN >> reactiveN;
		for( int i = 0; i < resourceN; i++ )
		{
			for( int k = 0; k < 9; k++ )
			{
				int cost_a, cost_b;
				cin >> cost_a >> cost_b;
				costA[{i, k}] = cost_a;
				costB[{i, k}] = cost_b;
			}
		}

	}
	void input_reactive( int iter )
	{
		long long score;
		int let;
		int chVio;
		cin >> score >> chVio >> let;
		for( int i = 0; i < resourceN; i++ )
		{
			for( int j = 0; j < weeks; j++ )
			{

				double cap;
				int letCnt;
				cin >> cap >> letCnt;
			}
		}
		bestScore = max( bestScore, score );
		cerr << "turn " << iter << " Score = " << score << ' ' << ",  chVioN = " << chVio << ' ' << ",  letOpN = " << let << endl;
	}


	void output_()
	{

		for( int i = 0; i < resourceN; i++ )
		{
			string calendar;
			for( int j = 0; j < weeks; j++ )
			{
				calendar.push_back( '9' );
				calendar.push_back( '9' );
			}
			cout << calendar << endl;
		}
	}
};


int main( int argc, char* argv[] )
{
	Solver S;
	S.input_init();

	for( int i = 0; i < S.reactiveN; i++ )
	{
		S.output_();
		S.input_reactive( i );
	}
	cerr << "Best Score = " << S.bestScore << endl;

	return 0;
}


///-------------------------------------------------------///
//　Reactive for offline
///-------------------------------------------------------///
/*
#include "Problem.h"
#include "gen.h"
#include "judge.h"

class Solver
{
public:

	int reactiveN;
	int weeks;
	int resourceN;
	int resCalenderChangeLimitN;
	std::map<tuple<int, int>, int> costA;
	std::map<tuple<int, int>, int> costB;

	Rand r;

	explicit Solver() :r( 0 )
	{}


	void input_reactive()
	{

	}


	vector<string> output_()
	{
		vector<string>calender( resourceN );
		for( int i = 0; i < resourceN; i++ )
			for( int j = 0; j < weeks; j++ )
			{
				calender[i].push_back( '9' );
				calender[i].push_back( '9' );
			}
		return calender;
	}
};

int main( int argc, char* argv[] )
{
	Solver S;
	Judge J;

	J.Input();
	auto pack = J.reactive_init_input();  // Replace with cin/cout when submitting to atcoder. And move the contents of .h to main.cpp.

	S.reactiveN = get<0>( pack );
	S.weeks = get<1>( pack );
	S.resourceN = get<2>( pack );
	S.costA = get<3>( pack );
	S.costB = get<4>( pack );
	S.resCalenderChangeLimitN = get<5>( pack );

	for( int i = 0; i < S.reactiveN; i++ )
	{
		auto output = S.output_(); // Replace with cin/cout when submitting to atcoder
		auto [score, letN, chVioCnt, loadRate, letOpCount] = J.reactive( output ); // Replace with cin/cout when submitting to atcoder
		cerr << "turn " << i << " Score = " << score << ' ' << ",  chVio = " << chVioCnt << ' ' << ",  let = " << letN << endl;

	}



	return 0;
}
*/

///-------------------------------------------------------///



