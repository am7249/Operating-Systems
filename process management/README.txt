Name: Abdullah Mobeen
NYU ID: am7249
Assignment: 2
Professor: Oliver Marin

Q1) I have attached the picture of the family tree produced from the code provided in the doc directory. In my understanding, there are 6 child process altogether -- 3 immediate children, 1 grandchild for 2 out of 3 children, and 1 grandchild for 1 out of 3 children. 

Modified code ~ 

	int main (int arg, char * argv [])

	{

		int i, j, p;
		for (i = 0; i <3; i ++)

			if ((p = fork ()) == 0){
				printf( "i =% d \ n", i)
				j = 0;
				while ((j < i) && ((p = fork ()) == 0))
					j ++;
				if (p != 0)
				{
					wait(0);
					exit(1);
				}
				if (p == 0)
					printf ( "j =% d \ n", j);
				exit(j);

			}/ * if * /
		wait(0);
		return (0);

	}

Q2) The code for this problem exists in file decoder.c in src directory. My logic was simple -- for each value of a, compute the sum of the first row, and use that sum to compute other missing entries. I use an array of length n (n=children) to accomodate each child process. It's compilation rule in the makefile exists in all2 and runstack2. Also, in the output, I also output the value of a for which we get a magic square. 

Q3) The code for this problem exists in files converters.c and multi_converter.c in src directory. The logic was simple -- given the input currency and the input amount in the command line, convert it to Euro, and then convert that amount in Euro to all currencies available in the header file converters.h. I use an array of length n (n = children) to accomodate each child process. 

=======================================================================

Files in src:
	1) converters.c - solution for Q3
	2) multi_converter.c - solution for Q3
	3) decoder.c - solution for Q2

Files in include:
	1) converters.h - solution for Q3

Makefil.ini - provides compilation rules for both Q2 (all2 and runstack2)and Q3 (all and runstack). There are some warnings when I run the makefile, but it's only for unused variables. It compiles fine. 
