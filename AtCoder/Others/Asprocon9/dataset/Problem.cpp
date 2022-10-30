#include <fstream>
#include <cassert>
#include <set>
#include "Problem.h"


void ProblemVar::Output()
{
	assert( generated == true );
	{  
		string OUTPUT = to_string( inputNo );
		while( OUTPUT.size() < 4 ) OUTPUT = '0' + OUTPUT;
		OUTPUT = input_outputfile_name + OUTPUT;
		OUTPUT += ".txt";
		ofstream out( OUTPUT );

		out << week << '\n';
		out << resCalendarChangeLimitN << '\n';
		out << reactiveN << '\n';
		out << itemN << '\n';
		for( auto& e : itemList )
		{
			out << e.itemNo << "	" << e.itemProcN << '\n';
			out << e.prodTimeRange.first << "	" << e.prodTimeRange.second << '\n';
			for( auto& e2 : e.proc )
			{
				out << e2 << "	";
			}
			out << "\n";
		}

		out << resourceN << '\n';
		for( auto& e : resourceList )
		{
			out << e.resNo << '\n';
			out << e.procNo << "	" << e.resDemand << "	" << e.workerN << "	" << e.costPerHour << "	" << e.costPerHourNight << '\n';
			out << e.costRatio << "	" << e.calendar0CostRatio << "	" << e.calendar1CostRatio << "\n";
			for( auto& e2 : e.calendarTypeXRatio )
			{
				out << e2 << "	";
			}
			out << "\n";
		}

		out << operationN << '\n';
		for( auto& e : opList )
		{
			out << e.opNo << "	" << e.itemNo << "	" << e.let << '\n';
			for( auto& e2 : e.prodTime )
			{
				out << e2 << "	";
			}
			out << "\n";
		}

		std::set<pair<int, int>>used;

		out << costTypeA.size() << '\n';
		for( auto& e : costTypeA )
		{
			out << e.second << "	" << costTypeB[e.first] << '\n';
		}


		out << procN << '\n';
		for( int i = 0; i < procN; i++ )
		{
			out << procDemand[i] << '\n';
		}

		for( int i = 0; i < resourceN; i++ )
		{
			out << calendar[i].size() << '\n';

			for( auto& e : calendar[i] )
				out << e.first << "	" << e.second << '\n';

			for( auto& e : originalCalendar )
				out << e << '\n';
		}
		out << addCostHoliday << '\n';
		out.close();
	}
}

void ProblemVar::Input( istream &in )
{
	//dump( "input start" );
	assert( generated == false );
	{
		in >> week;
		in >> resCalendarChangeLimitN;
		in >> reactiveN;
		in >> itemN;
		for( int i = 0; i < itemN; i++ )
		{
			Item e;
			in >> e.itemNo >> e.itemProcN;
			e.proc.resize( e.itemProcN );
			in >> e.prodTimeRange.first >> e.prodTimeRange.second;
			for( int j = 0; j < e.itemProcN; j++ )
			{
				in >> e.proc[j];
			}
			itemList.push_back( e );
		}

		in >> resourceN;
		for( int i = 0; i < resourceN; i++ )
		{
			Resource e;
			e.calendarTypeXRatio.resize( CalendarTypeN );
			in >> e.resNo;
			in >> e.procNo >> e.resDemand >> e.workerN >> e.costPerHour >> e.costPerHourNight;
			in >> e.costRatio >> e.calendar0CostRatio >> e.calendar1CostRatio;
			for( int j = 0; j < CalendarTypeN; j++ )
			{
				in >> e.calendarTypeXRatio[j];
			}
			resourceList.emplace_back( e );
		}

		in >> operationN;
		for( int i = 0; i < operationN; i++ )
		{
			Operation e;
			in >> e.opNo >> e.itemNo >> e.let;
			int procN = itemList[e.itemNo].itemProcN;
			e.prodTime.resize( procN );
			for( int j = 0; j < procN; j++ )
			{
				in >> e.prodTime[j];
			}
			opList.push_back( e );
		}


		int sz;
		in >> sz;
		for( int e = 0; e < sz; e++ )
		{
			int i = e / CalendarTypeN, k = e % CalendarTypeN, costA, costB;
			in >> costA >> costB;
			costTypeA[{i, k}] = costA;
			costTypeB[{i, k}] = costB;
		}

		in >> procN;
		procDemand.resize( procN );
		for( int i = 0; i < procN; i++ )
		{
			in >> procDemand[i];
		}


		calendar.resize( resourceN );
		originalCalendar.resize( resourceN );

		for( int i = 0; i < resourceN; i++ )
		{
			int sz;
			in >> sz;
			calendar[i].resize( sz );
			for( auto& e : calendar[i] )
				in >> e.first >> e.second;

			for( auto& e : originalCalendar )
				in >> e;
		}
		in >> addCostHoliday;
	}
	generated = true;
}
