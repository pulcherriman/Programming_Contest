#pragma once

#include <cmath>
#include "Problem.h"


class Judge : public ProblemVar
{
private:
	long long score = 0;

public:

	int N;
	explicit Judge()
	{}

	int GetWeek( int time )
	{
		return ( time - 4 * HOUR - 1 ) / WEEK;
	}

	// éëåπièTj Ç…Ç®ÇØÇÈâ“ì≠éûä‘ÇÃëçòaÇãÅÇﬂÇÈ
	// Calculate the total working time of resource i week j
	map<pair<int, int>, int> GetResourceTotalTime( std::vector<vector<pair<int, int>>> calendar )
	{
		map<pair<int, int>, int> t;
		for( int res = 0; auto & i:calendar )
		{
			for( auto& j : i )
			{
				t[{res, GetWeek( j.first )}] += j.second - j.first;
			}
			res++;
		}
		return t;
	}


	auto sequenceForward( vector<vector<pair<int, int>>> icalendar, vector<string> strCalendar ) // return {Number of let operations, Number of calendar change constraint violations, resource/week working ratio, resource/week Number of let operations}
	{

		std::vector<int>t3( resourceN, 0 );
		std::vector<int>ridx( resourceN, 0 );
		int END = week * 3600 * 24 * 7;

		map<pair<int, int>, int> base = GetResourceTotalTime( icalendar );
		map<pair<int, int>, int> used;
		map<pair<int, int>, int> let_cnt;


		int changeLimitViolationCnt = 0;
		for( int i = 0; i < resourceN; i++ )
		{
			assert( strCalendar[i].size() == week * 2 );
			int cntCh = 0;
			for( int j = 0; j < week * 2 - 2; j++ )
			{
				if( strCalendar[i][j] != strCalendar[i][j + 2] )
					cntCh++;
			}
			changeLimitViolationCnt += std::max( 0, cntCh - resCalendarChangeLimitN );
		}

		for( int i = 0; i < resourceN; i++ )
			for( int j = 0; j < week; j++ )
			{
				used[{i, j}] = 0;
				let_cnt[{i, j}] = 0;
			}

		auto Assign = [this, END, &t3, &ridx, &used, &let_cnt, &icalendar] ( Operation& op )
		{
			// [( startTime, endTime ), ... ]
			std::vector<pair<int, int>> lstAssigned( 1, pair<int, int>( -1, 0 ) );
			int lstAssignedTotalTime = 1;

			std::vector<std::vector<pair<int, int>>> assignedList( this->itemList[op.itemNo].itemProcN, std::vector<pair<int, int>>() );

			for( int i = 0; i < this->itemList[op.itemNo].itemProcN; i++ )
			{
				const int res = this->itemList[op.itemNo].proc[i];
				const int prod = op.prodTime[i];
				int remainProd = prod;
				int& tidx = ridx[res];

				for( auto [startTime, endTime] : lstAssigned )
				{
					const int curProd = ( long long int ) ( endTime - startTime ) * prod / lstAssignedTotalTime;
					int remainCurProd = curProd;
					remainProd -= curProd;

					int est = std::max( startTime, t3[res] );
					while( icalendar[res][tidx].second <= est ) tidx++;
					est = std::max( est, icalendar[res][tidx].first );

					// Ç∆ÇËÇ†Ç¶Ç∏ëOãlÇﬂÇÇ∑ÇÈ ... First, front justification
					// å„ãlÇﬂÇÃèÍçáÇÕÅCëOãlÇﬂÇ∑ÇÈÇ∆Ç´ÇÃç≈å„ÇÃèIÇÌÇËéûä‘Ç©ÇÁäJénéûä‘ÇíTÇ∑ÅB ... In the case of back justification, the start time is searched from the last end time when front justified.
					while( remainCurProd )
					{
						int curStartTime, curEndTime;

						if( endTime - est >= remainCurProd )
						{
							curEndTime = endTime;
							curStartTime = curEndTime - remainCurProd;
						}
						else
						{
							curStartTime = est;
							curEndTime = curStartTime + remainCurProd;
						}

						if( curEndTime >= icalendar[res][tidx].second )
						{
							curEndTime = icalendar[res][tidx].second;
							tidx++;
							est = icalendar[res][tidx].first;
						}

						t3[res] = curEndTime;
						remainCurProd -= curEndTime - curStartTime;
						assignedList[i].push_back( make_pair( curStartTime, curEndTime ) );
					}
				}

				while( remainProd )
				{
					int est = t3[res];
					int curStartTime = est, curEndTime = est + remainProd;
					if( curEndTime >= icalendar[res][tidx].second )
					{
						curEndTime = icalendar[res][tidx].second;
						tidx++;
					}

					t3[res] = curEndTime;
					remainProd -= curEndTime - curStartTime;
					assignedList[i].push_back( make_pair( curStartTime, curEndTime ) );
				}

				// èIÇÌÇËéûä‘Ç©ÇÁãtéZÇ∑ÇÈ ... calculate backwards from the end time
				int endTime = assignedList[i].back().second;
				int bidx = tidx;
				remainProd = prod;
				assignedList[i].clear();

				while( remainProd )
				{
					while( icalendar[res][bidx].first >= endTime ) bidx--;
					int curStartTime = icalendar[res][bidx].first;
					int curEndTime = std::min( icalendar[res][bidx].second, endTime );

					if( curEndTime - curStartTime > remainProd ) curStartTime = curEndTime - remainProd;
					bidx--;

					remainProd -= curEndTime - curStartTime;
					assignedList[i].push_back( make_pair( curStartTime, curEndTime ) );
				}

				std::reverse( assignedList[i].begin(), assignedList[i].end() );
				for( auto [startTime, endTime] : assignedList[i] )
				{
					int curWeek = GetWeek( startTime );
					if( curWeek < week ) used[make_pair( res, curWeek )] += endTime - startTime;
				}

				lstAssigned = assignedList[i];
				lstAssignedTotalTime = prod;
			}

			bool let = lstAssigned.back().second > op.let;

			if( let ) // î[ä˙íxÇÍçÏã∆ÇÃèàóùéûä‘Çä‹ÇﬁèTÇÉ`ÉFÉbÉN ... Check week including processing time for let operation
			{
				set<pair<int, int>> se;
				for( int i = 0; const vector<pair<int, int>>&vec : assignedList )
				{
					int res = this->itemList[op.itemNo].proc[i];

					for( auto [startTime, endTime] : vec )
					{
						int curWeek = GetWeek( startTime );
						if( curWeek < week ) se.insert( make_pair( res, curWeek ) );
					}

					i++;
				}

				for( pair<int, int> p : se ) let_cnt[p]++;
			}
			//cerr << prev_t3 << ' ' << op.let << endl;
			return let;
		};
		int let = 0;
		for( int i = 0; i < operationN; i++ )
		{
			bool letFlag = Assign( opList[i] );
			let += letFlag == true ? 1 : 0;
		}

		//assert( used.size() == base.size() );
		map<pair<int, int>, double>loadRate;
		for( auto& e : used )
		{
			if( e.first.second == week ) continue;
			loadRate[e.first] = static_cast<double>( e.second ) / (double)max( 1, base[e.first] );
		}
		return make_tuple( let, changeLimitViolationCnt, loadRate, let_cnt );
	}


	auto Score()
	{
		return score;
	}
	auto reactive_init_input()
	{
		return make_tuple( reactiveN, week, resourceN, costTypeA, costTypeB, resCalendarChangeLimitN );
	}

	auto reactive( vector<string> input )
	{
		assert( input.size() == resourceN );
		assert( input[0].size() == week * 2 );
		for( auto& e : input )
			assert( input[0].size() == e.size() );

		std::vector<vector<pair<int, int>>> calendar( resourceN );
		long long cost = 0;

		for( int i = 0; i < resourceN; i++ )
		{
			for( int j = 0; j < week; j++ )
			{
				int calendarTypeA = input[i][j * 2] - '1';
				int calendarTypeB = input[i][j * 2 + 1] - '1';
				Calendar.addCalendar( calendar[i], j, calendarTypeA, calendarTypeB );

				cost += costTypeA[{i, calendarTypeA}] + costTypeB[{i, calendarTypeB}];
			}
		}

		for( int j = 0; j < resourceN; j++ )
		{
			calendar[j].push_back( { 1e9,2e9 } );
		}

		auto [let, chLimVioCnt, loadRate, letOpCount] = sequenceForward( calendar, input );
		long long curScore = ( let + chLimVioCnt ) == 0 ? round( ( 10.0 - log10( static_cast<double>( cost / week ) ) ) * 1e9 ) : 0;
		score = max( score, curScore );
		return make_tuple( curScore, let, chLimVioCnt, loadRate, letOpCount );

	}

};



