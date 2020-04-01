#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <string.h>

namespace AprilCrackme
{
	char buf[9];

	void Process()
	{
		printf("Enter key...\n");

		std::cin >> buf;

		/*
		*	Solve, to find out first 5 characters.
		*
		*	buf[0] = a, buf[1] = b, buf[2] = c, buf[3] = d, buf[4] = e.
		*
		*	3 * (a + e) + 2 * c - b - d = 347
		*	3 * (d + 2 * a) - 2 * (b + 2 * e) - c = 104
		*	e + b - c + a + 2 * (b - c) + 7 * d = 450
		*	b + 2 * a + 3 * (d + c) - 7 * e = 87
		*	e + a + c + d + b = 270
		*
		*	Simplify first equation:
		*	3 * a + 3 * e + 2 * c - b - d = 347
		*	In order:
		*	3a - b + 2c - d + 3e = 347
		*
		*	Simplify second equation:
		*	3 * d + 6 * a - 2 * b - 4 * e - c = 104
		*	In order:
		*	6a - 2b - c + 3d - 4e = 104
		*
		*	Simplify third equation:
		*	e + b - c + a + 2 * b - 2 * c + 7 * d = 450
		*	In order:
		*	a + 3b - 3c + 7d + e = 450
		*
		*	Simplify fourth equation:
		*	b + 2 * a + 3 * d + 3 * c - 7 * e = 87
		*	In order:
		*	2a + b + 3c + 3d - 7e = 87
		*
		*	Simplify fifth equation:
		*	e + a + c + d + b = 270
		*	In order:
		*	a + b + c + d + e = 270
		*
		*	Thank you, WolframAlpha!
		*	Solution is: a = 57, b = 53, c = 55, d = 49, e = 56
		*	Characters are: a = '9', b = 5', c = '7', d = '1', e = '8'
		*	Final string is - 95718xxxx.
		*/

		int check_first = 3 * (buf[0] + buf[4]) + 2 * buf[2] - buf[1] - buf[3];	//	0x15B 347
		int check_second = 3 * (buf[3] + 2 * buf[0]) - 2 * (buf[1] + 2 * buf[4]) - buf[2];	//	0x68 104
		int check_third = buf[4] + buf[1] - buf[2] + buf[0] + 2 * (buf[1] - buf[2]) + 7 * buf[3];	//	0x1C2 450
		int check_fourth = buf[1] + 2 * buf[0] + 3 * (buf[3] + buf[2]) - 7 * buf[4];	//	0x57 87
		int check_fifth = buf[4] + buf[0] + buf[2] + buf[3] + buf[1];	//	0x10E 270

		printf("%x %x %x %x %x\n", check_first, check_second, check_third, check_fourth, check_fifth);

		/*
		 *	7th character is xor'ed with 0x6F (111) and result should be 0x5F (95).
		 *	So, xor known characters to find out what's needed!
		 *	0x5F ^ 0x6F = 0x30 (48).
		 *	7th character code is 48 - '0' (digit zero).
		 *	Final string is - 95718x0xx.
		*/

		int check_sixth = buf[6] ^ 0x6F;	//	0x5F 95

		printf("%x\n", check_sixth);

		/*
		 *	7th and 8th characters should be same, so they're both '0'.
		 *	Final string is - 95718x00x.
		*/

		bool check_seventh = buf[6] == buf[7];
		printf("%x %s %x\n", buf[6], (check_seventh ? "==" : "!="), buf[7]);

		/*
		 *	When subtracting 6th character from 9th character, result should be 3.
		 *	When adding 6th to 9th character, result should be 235.
		 *
		 *	x - y = 3
		 *	x + y = 235
		 *
		 *	x = 3 + y
		 *	3 + y + y = 235
		 *	3 + 2y = 235
		 *	2y = 235 - 3
		 *	2y = 232
		 *	y = 232 / 2
		 *	y = 116
		 *	x = 116 + 3
		 *	x = 119
		 *
		 *	So, 9th character code is 119 'w', and 6th character code is 116 't'.
		 *	Final string is - 95718t00w.
		*/

		int check_eighth = buf[8] - buf[5];	//	3
		int check_ninth = buf[5] + buf[8];	//	0xEB 235

		printf("%i %x\n", check_eighth, check_ninth);

		/*
		 *	Result string is: 95718t00w.
		*/

		if (check_first == 0x15b &&
			check_second == 0x68 &&
			check_third == 0x1c2 &&
			check_fourth == 0x57 &&
			check_fifth == 0x10e &&
			check_sixth == 0x5f &&
			check_seventh &&
			check_eighth == 0x3 &&
			check_ninth == 0xeb)
			printf("Cracked!\n");
		else
			printf("Wrong key!\n");

		int retchar = getchar();

		/*
		 *	Crackme 'what_is_my_password' by:
		 *		br0ken - https://crackmes.one/crackme/5ab77f5333c5d40ad448c103
		 *
		 *	Resources used:
		 *		1. http://www.asciitable.com/ - ASCII table;
		 *		2. https://www.wolframalpha.com - WolframAlpha;
		 *		3. IDA Pro 7.0.
		*/
	}
}

int main()
{
  AprilCrackme::Process();
}
