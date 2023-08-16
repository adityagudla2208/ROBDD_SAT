#include <stdlib.h>
#include <stdio.h>
#include <bdduser.h>

int main (int argc, char* argv[])
{
	bdd_manager bddm = bdd_init();	

	// 4-bit input x & y
	bdd x3 = bdd_new_var_last(bddm);
	bdd y3 = bdd_new_var_last(bddm);
	bdd x2 = bdd_new_var_last(bddm);
	bdd y2 = bdd_new_var_last(bddm);
	bdd x1 = bdd_new_var_last(bddm);
	bdd y1 = bdd_new_var_last(bddm);
	bdd x0 = bdd_new_var_last(bddm);
	bdd y0 = bdd_new_var_last(bddm);	

	// compute s0 & c0
	bdd s0 = bdd_xor (bddm, x0, y0); //x0 ^ y0
	bdd c0 = bdd_and (bddm, x0, y0); //x0 & y0
		
	// compute s1 & c1
	bdd s1_1 = bdd_xor (bddm, x1, y1); //x1 ^ y1
	bdd s1 = bdd_xor (bddm, s1_1, c0); //x1 ^ y1 ^ c0
	bdd c1_1 = bdd_and (bddm, x1, y1); //x1 & y1
	bdd c1_2 = bdd_and (bddm, x1, c0); //x1 & c0
	bdd c1_3 = bdd_and (bddm, y1, c0); //y1 & c0
	bdd c1_4 = bdd_or (bddm, c1_1, c1_2); //(x1 & y1) | (x1 & c0)
	bdd c1 = bdd_or (bddm, c1_3, c1_4); //(x1 & y1) | (x1 & c0) | (y1 & c0)
		
	// compute s2 & c2
	bdd s2_1 = bdd_xor (bddm, x2, y2); //x2 ^ y2
	bdd s2 = bdd_xor (bddm, s2_1, c1); //x2 ^ y2 ^ c1
	bdd c2_1 = bdd_and (bddm, x2, y2); //x2 & y2
	bdd c2_2 = bdd_and (bddm, x2, c1); //x2 & c1
	bdd c2_3 = bdd_and (bddm, y2, c1); //y2 & c1
	bdd c2_4 = bdd_or (bddm, c2_1, c2_2); //(x2 & y2) | (x2 & c1)
	bdd c2 = bdd_or (bddm, c2_3, c2_4); //(x2 & y2) | (x2 & c1) | (y2 & c1)
	
	// compute s3 & c3
	bdd s3_1 = bdd_xor (bddm, x3, y3); //x3 ^ y3
	bdd s3 = bdd_xor (bddm, s3_1, c2); //x3 ^ y3 ^ c2
	bdd c3_1 = bdd_and (bddm, x3, y3); //x3 & y3
	bdd c3_2 = bdd_and (bddm, x3, c2); //x3 & c2
	bdd c3_3 = bdd_and (bddm, y3, c2); //y3 & c2
	bdd c3_4 = bdd_or (bddm, c3_1, c3_2); //(x3 & y3) | (x3 & c2)
	bdd c3 = bdd_or (bddm, c3_3, c3_4); //(x3 & y3) | (x3 & c2) | (y3 & c2)
	
	// compute characteristic function of 4 bit adder
	bdd cout = bdd_new_var_last(bddm);
	bdd sum3 = bdd_new_var_last(bddm);
	bdd sum2 = bdd_new_var_last(bddm);
	bdd sum1 = bdd_new_var_last(bddm);
	bdd sum0 = bdd_new_var_last(bddm);
	
	bdd char1 = bdd_xor(bddm, sum3, s3);
	bdd char2 = bdd_not(bddm, char1); //
	bdd char3 = bdd_xor(bddm, sum2, s2);
	bdd char4 = bdd_not(bddm, char3); //
	bdd char5 = bdd_xor(bddm, sum1, s1);
	bdd char6 = bdd_not(bddm, char5); //
	bdd char7 = bdd_xor(bddm, sum0, s0);
	bdd char8 = bdd_not(bddm, char7); //
	bdd char9 = bdd_xor(bddm, cout, c3);
	bdd char10 = bdd_not(bddm, char9); //
	bdd char11 = bdd_and(bddm, char2, char4);
	bdd char12 = bdd_and(bddm, char11, char6);
	bdd char13 = bdd_and(bddm, char12, char8);
	
	//CHARACTERISTIC FUNCTION
	bdd Xadder = bdd_and(bddm, char13, char10);
	
	
	//compute subset A : inputs are prime numbers
	bdd a_1 = bdd_not (bddm, x3);
	bdd a_2 = bdd_and (bddm, a_1,x0);
	bdd a_3 = bdd_not (bddm, x2);
	bdd a_4 = bdd_and (bddm, a_3, a_1);
	bdd a_5 = bdd_and (bddm, a_4, x1);
	bdd a_6 = bdd_not (bddm, x1);
	bdd a_7 = bdd_and (bddm, x2, a_6);
	bdd a_8 = bdd_and (bddm, a_7, x0);
	bdd a_9 = bdd_and (bddm, x1, x0);
	bdd a_10 = bdd_and (bddm, a_9, a_3);
	
	bdd a_11 = bdd_or (bddm, a_2, a_5);
	bdd a_12 = bdd_or (bddm, a_11, a_8);
	bdd a_13 = bdd_or (bddm, a_12, a_10);
	
	bdd b_1 = bdd_not (bddm, y3);
	bdd b_2 = bdd_and (bddm, b_1,y0);
	bdd b_3 = bdd_not (bddm, y2);
	bdd b_4 = bdd_and (bddm, b_3, b_1);
	bdd b_5 = bdd_and (bddm, b_4, y1);
	bdd b_6 = bdd_not (bddm, y1);
	bdd b_7 = bdd_and (bddm, y2, b_6);
	bdd b_8 = bdd_and (bddm, b_7, y0);
	bdd b_9 = bdd_and (bddm, y1, y0);
	bdd b_10 = bdd_and (bddm, b_9, b_3);

	bdd b_11 = bdd_or (bddm, b_2, b_5);
	bdd b_12 = bdd_or (bddm, b_11, b_8);
	bdd b_13 = bdd_or (bddm, b_12, b_10);
	
	bdd subset_a = bdd_and (bddm, a_13, b_13);

	// Existential quantification
	bdd p = bdd_and(bddm, Xadder, subset_a);
	//bdd_print_bdd(bddm,p,NULL, NULL,NULL, stdout);
	bdd Q[9];
	Q[0] = x0; Q[1] = x1; Q[2] = x2; Q[3] = x3;
	Q[4] = y0; Q[5] = y1; Q[6] = y2; Q[7] = y3; Q[8] = 0;
	int assoc = bdd_new_assoc(bddm,Q,0);
	bdd_assoc(bddm,assoc);
	
	printf("NOTE : \n");
	printf("var.8 is cout\n");
	printf("var.9 is sum3\n");
	printf("var.10 is sum2\n");
	printf("var.11 is sum1\n");
	printf("var.12 is sum0\n");

	bdd pq = bdd_exists(bddm,p);
	printf("-------------Image of subset A (inputs are prime numbers)-------------\n");
	printf("-----------------------------BDD name: pq-----------------------------\n\n");
	bdd_print_bdd(bddm,pq,NULL, NULL,NULL, stdout);
	printf("\n\n----------------------------------------------------------------------\n");
	printf("----------------------------------------------------------------------\n");
	
	//all even output numbers when two inputs are prime numbers
	bdd e_1 = bdd_not(bddm, sum0);
	bdd e = bdd_and(bddm, e_1, pq);
	printf("----Subset of subset A(even outputs when inputs are prime numbers)----\n");
	printf("-----------------------------BDD name : e-----------------------------\n\n");
	bdd_print_bdd(bddm,e,NULL, NULL,NULL, stdout);
	printf("\n\n----------------------------------------------------------------------\n");
	printf("----------------------------------------------------------------------\n");
	
	//bdd of all possible nonzero even output numbers
	bdd i1 = bdd_not (bddm, sum0);
	bdd i2 = bdd_or (bddm, sum3, sum2);
	bdd i3 = bdd_or (bddm, i2, sum1);
	bdd i4 = bdd_or (bddm, i3, cout);
	bdd i = bdd_and (bddm, i1, i4);
	printf("---------------All possible nonzero even output numbers---------------\n");
	printf("-----------------------------BDD name : i-----------------------------\n\n");
	bdd_print_bdd(bddm,i,NULL, NULL,NULL, stdout);
	printf("\n\n----------------------------------------------------------------------\n");
	printf("----------------------------------------------------------------------\n");
	
	//To prove: e is a subset of i
	//we need to show that : ~i.e = 0 OR ~e+i = 1
	bdd p1 = bdd_not (bddm, i);
	bdd p2 = bdd_and (bddm, p1, e);
	printf("\nTo prove: Every even 4-bit number can be expressed as a sum of two prime numbers\n");
	printf("We need to prove: bdd 'e' is a subset of bdd 'i' i.e. ~e+i = 1 OR ~i.e = 0\n");
	printf("--------------------------Proof 1 : ~i.e = 0--------------------------\n");
	printf("----------------------------------------------------------------------\n\n");
	bdd_print_bdd(bddm,p2,NULL, NULL,NULL, stdout);
	printf("Result is a zero BDD hence ~i.e = 0");
	printf("\n\n----------------------------------------------------------------------\n");
	printf("----------------------------------------------------------------------\n");
	
	bdd p3 = bdd_not (bddm, e);
	bdd p4 = bdd_or (bddm, p3, i);
	printf("--------------------------Proof 2 : ~e+i = 1--------------------------\n");
	printf("----------------------------------------------------------------------\n\n");
	bdd_print_bdd(bddm,p4,NULL, NULL,NULL, stdout);
	printf("Result is a one BDD hence ~e+i = 1");
	printf("\n\n----------------------------------------------------------------------\n");
	printf("----------------------------------------------------------------------\n");
	
	printf("Hence the property is proved\n");

	return(0);
}

