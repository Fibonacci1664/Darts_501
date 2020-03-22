/*
 *	This has been declared a struct due to it simply containing data ONLY and having
 *	no functionality.
 *
 *	It contains:
 *		-	A finish total
 *		-	3 darts each being an array themselves of 2 elements which are there to contain:
 *				-	The number to aim for.	1 - 20.
 *				-	The type to aim for.	s, d, t, i, o.		(Single, double, treble, inner bull, outer bull.)
 *
 *	Original @author D. Green.
 *
 *	© D. Green. 2020.
 *
 */

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Finishes
{
	int m_finishTotal;
	int m_dart_1[2];
	int m_dart_2[2];
	int m_dart_3[2];
};