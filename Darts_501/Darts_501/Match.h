/*
 *	This has been declared a struct due to it simply containing data ONLY and having
 *	no functionality.
 *
 *	It contains:
 *		-	Player 1 match results (result_1)
 *		-	Player 2 match results (result_2)
 *		-	A tally of how many times that result has happened, we keep a tally otherwise we would have to print out ALL
 *			results including the match results that have already had an occurence and would also result in a huge vector
 *			of every single match, by keeping a tally there are only 12 possible combinations of match results, namely
 *
 *			7 : 1
 *			7 : 2
 *			7 : 3
 *			7 : 4
 *			7 : 5
 *			7 : 6
 *			1 : 7
 *			2 : 7
 *			3 : 7
 *			4 : 7
 *			5 : 7
 *			6 : 7
 *
 *			In the example below, instead of having to store and then subsequently print ALL result we only store result that are different
 *			and results that have already happened in previous matches we increment a tally on that result. e.g.
 *
 *			INEFFICIENT AND WITHOUT TALLY OPTION.
 *		-	Match[0]	7 : 3
 *		-	Match[1]	7 : 3
 *		-	Match[2]	7 : 4
 *		-	Match[3]	5 : 7
 *
 *			EFFICIENT AND WITH TALLY OPTION.
 *		-	Match[0]	7 : 3		tally = 2
 *		-	Match[1]	7 : 4
 *		-	Match[2]	5 : 7
 *
 *		Hope that makes sense.
 *
 *	Original @author D. Green.
 *
 *	© D. Green. 2020.
 *
 */

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Match
{
	int result_1 = 0;
	int result_2 = 0;
	double tally = 0;
};