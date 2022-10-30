#pragma once

#include "Problem.h"


constexpr int INF = 2'000'000'000;


class Generator : public ProblemVar
{
public:


	// 文字列をスペース区切りで分割 ... seperate string with a whitespace character 
	vector<string> split( string S )
	{
		vector<string> ret;
		string temp;
		for( char c : S )
		{
			if( c == ' ' )
			{
				if( !temp.empty() ) ret.push_back( temp );
				temp.clear();
			}
			else
			{
				temp += c;
			}
		}
		ret.push_back( temp );
		return ret;
	}



	void Generate( int inputIndex, string INPUT, string outputfile_name )
	{

		inputNo = inputIndex;
		input_INPUT = INPUT;
		input_outputfile_name = outputfile_name;

		unsigned long long seed = 0;

		// 入力によるパラメータ変更 ... process input parameter
		vector<string> argv = split( INPUT );
		int argc = argv.size();

		for( int i = 0; i < argc - 1; i += 2 )
		{
			string temp = argv[i];

			if( temp == "-week" )
			{
				week = stoi( argv[i + 1] );
			}
			else if( temp == "-resourceN" )
			{
				resourceN = stoi( argv[i + 1] );
			}
			else if( temp == "-itemN" )
			{
				itemN = stoi( argv[i + 1] );
			}
			else if( temp == "-changeLimit" )
			{
				resCalendarChangeLimitN = stoi( argv[i + 1] );
			}
			else if( temp == "-seed" )
			{
				seed = stoull( argv[i + 1] );
			}
			else
			{
				cerr << "unknown option: " << argv[i] << '\n';
				exit( 0 );
			}
		}

		Rand r( seed );

		int CTN = CalendarTypeN;

		reactiveN = param.reactiveN[seed % 3];
		itemN = r.randint( param.itemMin, param.itemMax + 1 );
		resourceN = r.randint( param.resMin, param.resMax + 1 );
		week = r.randint( param.weeksMin, param.weeksMax + 1 );
		resCalendarChangeLimitN = r.randint( param.changeLimitMin, param.changeLimitMax );

		if( seed <= 2 )
		{
			itemN = param.itemMin;
			resourceN = param.resMin;
			week = param.weeksMin;
			resCalendarChangeLimitN = param.changeLimitMin;
		}


		// 入力の生成 ... generate input data
		{ // 資源・工程の生成 ... generate resource and process

			procN = r.randint( param.procNMin, resourceN + 1 );
			procResSet.resize( procN, set<int>() );
			procDemand.resize( procN, 0.0 );
			resDemandMutationRatio.resize( resourceN, 1.0 );


			auto proc = r.divide( resourceN - 1, procN - 1 ); // (proc[i-1],proc[i] ]  as same process
			proc.emplace_back( resourceN + 1 );

			std::vector<int> procBaseCalendarType( procN ); // Base calendar for process i
			for( int i = 0; i < procN; i++ )
			{
				procBaseCalendarType[i] = r.randint( 2, 7 );
			}

			calendar.resize( resourceN );
			originalCalendar.resize( resourceN );

			for( int i = 0, idx = 0; i < resourceN; i++ )
			{
				resDemandMutationRatio[i] = r.uniform( param.resInitCalendarMutationRatioMin, param.resInitCalendarMutationRatioMax );
				procResSet[idx].insert( i );

				Resource res;
				res.resNo = i;
				res.workerN = 1 + abs( r.normal( param.workerNSigma ) ); // 資源の稼働に必要な作業員数 ... Number of workers required to operate resources
				res.costPerHour = param.baseCostPerHour + abs( r.normal( param.costPerHourSigma ) ); // 作業員の時給 ... worker's hourly rate
				res.costPerHourNight = res.costPerHour + abs( r.normal( param.costPerHourNightSigma ) ); // 作業員の夜勤の時給 ... night shift rate
				res.resDemand += 1;
				res.costRatio = r.uniform( param.costExpMin, param.costExpMax );
				res.calendar1CostRatio = r.uniform( param.calendar1CostRatioMin, param.calendar1CostRatioMax );
				res.calendar0CostRatio = r.uniform( res.calendar1CostRatio );
				res.procNo = idx;

				res.calendarTypeXRatio.resize( CTN );
				for( int j = 0; j < CTN; j++ )
				{
					res.calendarTypeXRatio[j] = r.uniform(); // カレンダの変化確率 ... Calendar changed probability
				}

				for( int j = 0; j < week; j++ )
				{
					int calType = procBaseCalendarType[res.procNo];
					if( resDemandMutationRatio[i] > r.uniform() ) // 確率でカレンダをランダムに変更 ... Change calendar randomly with probability
					{
						auto x = r.weighted_unique_seq( res.calendarTypeXRatio, 1 );
						calType = x[0];
					}
					procDemand[idx] += 1.0 * Calendar.Time[calType]; // 稼働時間に比例して工程の需要を決める ... Determine process demand in proportion to calendar
					originalCalendar[i] += calType + '0';
					originalCalendar[i] += calType + '0';
					Calendar.addCalendar( calendar[i], j, calType, calType ); // 資源jの週iのカレンダを追加する ... 
				}

				calendar[i].push_back( { 1e9,INF } );
				resourceList.emplace_back( res );

				if( proc[idx] <= i ) idx++;
			}

			while( 1 )
			{
				long long maxCost = 0;
				for( int i = 0; i < resourceN; i++ )
				{
					for( int k = 2; k < CalendarTypeN; k++ )
					{
						// 稼働時間 * 作業員数 * 時給 * 稼働時間にかかる倍率 を稼働パターンの費用とする
						// working time * Number of workers * Hourly wage * Multiplication factor for working time  is used as calendar pattern cost
						int wN = resourceList[i].workerN;
						int cPH = resourceList[i].costPerHour;
						int cPHN = resourceList[i].costPerHourNight;
						double cR = resourceList[i].costRatio;
						costTypeA[{i, k}] = ( Calendar.totalTimeA[k] * wN * cPH
											  + Calendar.totalTimeB[k] * wN * cPHN ) * pow( cR, Calendar.totalTime[k] );
						costTypeB[{i, k}] = costTypeA[{i, k}] * addCostHoliday;
					}
					maxCost += costTypeA[{i, CalendarTypeN-1}];
					maxCost += costTypeB[{i, CalendarTypeN-1}];
				}

				if( maxCost >= param.maxCost ) // if maxCost exceeded 10^10 change parameters
				{
					for( auto& res : resourceList )
					{
						res.workerN = 1 + abs( r.normal( param.workerNSigma ) );
						res.costPerHour = param.baseCostPerHour + abs( r.normal( param.costPerHourSigma ) );
						res.costPerHourNight = res.costPerHour + abs( r.normal( param.costPerHourNightSigma ) );
						res.costRatio = r.uniform( param.costExpMin, param.costExpMax );
						res.calendar1CostRatio = r.uniform( param.calendar1CostRatioMin, param.calendar1CostRatioMax );
						res.calendar0CostRatio = r.uniform( res.calendar1CostRatio );
					}
				}
				else
					break;
			}


			for( int i = 0; i < resourceN; i++ )
			{
				costTypeA[{i, 0}] = costTypeA[{i, 2}] * resourceList[i].calendar0CostRatio;
				costTypeB[{i, 0}] = costTypeB[{i, 2}] * resourceList[i].calendar0CostRatio;
				costTypeA[{i, 1}] = costTypeA[{i, 2}] * resourceList[i].calendar1CostRatio;
				costTypeB[{i, 1}] = costTypeB[{i, 2}] * resourceList[i].calendar1CostRatio;
			}
		}

		{ // 品目の生成 ... generate item
			vector<double>resDemand( resourceN );
			for( int i = 0; i < resourceN; i++ )
				resDemand[i] = resourceList[i].resDemand;

			int procRate = log2( r.randint( 2, max( 3, 1 << ( resourceN / 5 ) ) ) ); // 数値が大きいほど工程の長さは短く設定されやすくなる
			int prodTime = std::max( param.prodTimeBase, static_cast<int>( abs( r.normal( param.prodTimeBase, r.uniform( param.prodTimeSigmaMin, param.prodTimeSigmaMax ) ) ) ) );

			//int prodTimeMax = r.randint( param.prodTimeMin + 1, param.prodTimeMax );

			for( int i = 0; i < itemN; i++ )
			{
				Item it;
				it.itemNo = i;
				it.itemProcN = r.randint( param.itemProcNMin, max( param.itemProcNMin + 1, procN / procRate ) ); // 工程数
				auto v = r.weighted_unique_seq( procDemand, it.itemProcN ); // どの工程を通るか需要に従い決める
				for( auto& e : v )
				{
					auto res = r.weighted_unique_seq( resDemand, 1, &procResSet[e] ); // 工程のどの資源を通るか決める
					it.proc.emplace_back( res[0] );
				}
				it.prodTimeRange = std::make_pair( prodTime * param.prodTimeVarMin, prodTime * param.prodTimeVarMax ); // 製造時間の幅を設定
				sort( it.proc.begin(), it.proc.end() ); // 工程順序を昇順に整える
				itemList.emplace_back( it );

			}
		}


		// 作業の生成 ... generate operation．

		operationN = 0;

		std::vector<int>t3( resourceN, 0 ); // 資源ごと, 直前の作業の製造終了時刻 ... For each resource, production end time of the immediately preceding operation
		std::vector<int>ridx( resourceN, 0 );
		int END = week * WEEK - DAY;

		// ENDを超えない限り作業を追加する ... Add operation as long as it does not exceed END
		// 作業は左詰めで割り付ける ... Assign operations left aligned


		auto CheckCapacity = [this, &t3, &ridx, END] ( Operation& op, bool assignFlag = false )
		{
			int totalSkip = 0;

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

				const int oriRidx = ridx[res];
				const int oriT3 = t3[res];

				for( auto [startTime, endTime] : lstAssigned )
				{
					const int curProd = ( long long int ) ( endTime - startTime ) * prod / lstAssignedTotalTime;
					int remainCurProd = curProd;
					remainProd -= curProd;

					int est = std::max( startTime, t3[res] );
					while( this->calendar[res][tidx].second <= est ) tidx++;
					est = std::max( est, this->calendar[res][tidx].first );

					// とりあえず前詰めをする。
					// 後詰めの場合は前詰めするときの最後の終わり時間から開始時間を探します。
					while( remainCurProd )
					{
						int curStartTime, curEndTime;
						// ESSEE
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

						if( curEndTime >= this->calendar[res][tidx].second )
						{
							curEndTime = this->calendar[res][tidx].second;
							tidx++;
							est = this->calendar[res][tidx].first;
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
					if( curEndTime >= this->calendar[res][tidx].second )
					{
						curEndTime = this->calendar[res][tidx].second;
						tidx++;
					}

					t3[res] = curEndTime;
					remainProd -= curEndTime - curStartTime;
					assignedList[i].push_back( make_pair( curStartTime, curEndTime ) );
				}

				// 終わり時間から逆算する ... calculate backwards from the end time
				int endTime = assignedList[i].back().second;
				int bidx = tidx;
				remainProd = prod;
				assignedList[i].clear();

				while( remainProd )
				{
					while( this->calendar[res][bidx].first >= endTime ) bidx--;
					int curStartTime = this->calendar[res][bidx].first;
					int curEndTime = std::min( this->calendar[res][bidx].second, endTime );

					if( curEndTime - curStartTime > remainProd ) curStartTime = curEndTime - remainProd;
					bidx--;

					remainProd -= curEndTime - curStartTime;
					assignedList[i].push_back( make_pair( curStartTime, curEndTime ) );
				}

				std::reverse( assignedList[i].begin(), assignedList[i].end() );

				// calculate totalSkip
				int curRidx = oriRidx;
				int curT3 = oriT3;
				while( curT3 < assignedList[i].front().first )
				{
					int st = std::max( curT3, this->calendar[res][curRidx].first );
					int ed = std::min( assignedList[i].front().first, this->calendar[res][curRidx].second );
					totalSkip += ed - st;

					curRidx++;
					curT3 = ed;
				}

				lstAssigned = assignedList[i];
				lstAssignedTotalTime = prod;

				if( !assignFlag )
				{
					t3[res] = oriT3;
					ridx[res] = oriRidx;
				}
				else
				{
					op.let = lstAssigned.back().second;
				}
			}

			return make_tuple( totalSkip, lstAssigned.back().second <= END ); // 
		};

		while( 1 )
		{
			int i = r.randint( itemN );

			Operation tmp;
			pair<int, Operation> MIN = { INF,tmp };
			for( int k = 0; k < 1; k++ )
			{
				Operation op;
				op.itemNo = i;
				op.opNo = operationN;
				op.prodTime.resize( itemList[i].itemProcN );

				for( int j = 0; j < itemList[i].itemProcN; j++ )
					op.prodTime[j] = r.randint( itemList[i].prodTimeRange );

				auto [totalSkip, flag] = CheckCapacity( op );
				if( flag == false )
					continue;

				if( MIN.first > totalSkip )
					MIN = make_pair( totalSkip, op );
			}

			if( MIN.first == INF )
				break;

			Operation op = MIN.second;
			CheckCapacity( op, true );
			operationN++;
			opList.emplace_back( op );

		}

		generated = true;

	}


};

