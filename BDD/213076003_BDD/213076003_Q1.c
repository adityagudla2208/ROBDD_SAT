#include <stdlib.h>
#include <stdio.h>
#include <bdduser.h>

int main (int argc, char* argv[])
{
	bdd_manager bddm = bdd_init();	

	// 4-bit input x
	bdd x3 = bdd_new_var_last(bddm);
	bdd x2 = bdd_new_var_last(bddm);
	bdd x1 = bdd_new_var_last(bddm);
	bdd x0 = bdd_new_var_last(bddm);
	
	// 4-bit input y
	bdd y3 = bdd_new_var_last(bddm);
	bdd y2 = bdd_new_var_last(bddm);
	bdd y1 = bdd_new_var_last(bddm);
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
	bdd sum3 = bdd_new_var_last(bddm);
	bdd sum2 = bdd_new_var_last(bddm);
	bdd sum1 = bdd_new_var_last(bddm);
	bdd sum0 = bdd_new_var_last(bddm);
	bdd cout = bdd_new_var_last(bddm);
	
	printf("NOTE : \n");
	printf("var.8 is sum3\n");
	printf("var.9 is sum2\n");
	printf("var.10 is sum1\n");
	printf("var.11 is sum0\n");
	printf("var.12 is cout\n");
	
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
	
	
	// compute subset A
	bdd a_1 = bdd_xor (bddm, x0,x1);
	bdd a_2 = bdd_xor (bddm, a_1,x2);
	bdd a_3 = bdd_xor (bddm, a_2,x3); //x0 ^ x1 ^ x2 ^ x3
	bdd a_4 = bdd_xor (bddm, y0,y1);
	bdd a_5 = bdd_xor (bddm, a_1,y2);
	bdd a_6 = bdd_xor (bddm, a_2,y3); //y0 ^ y1 ^ y2 ^ y3
	bdd subset_a = bdd_and (bddm, a_1, a_6);

	// Existential quantification
	bdd p = bdd_and(bddm, Xadder, subset_a);
	//bdd_print_bdd(bddm,p,NULL, NULL,NULL, stdout);
	bdd Q[9];
	Q[0] = x0; Q[1] = x1; Q[2] = x2; Q[3] = x3;
	Q[4] = y0; Q[5] = y1; Q[6] = y2; Q[7] = y3; Q[8] = 0;
	int assoc = bdd_new_assoc(bddm,Q,0);
	bdd_assoc(bddm,assoc);

	bdd pq = bdd_exists(bddm,p);
	printf("-------------------------BDD for Question 1-------------------------\n");
	printf("--------------------------------------------------------------------\n\n");
	bdd_print_bdd(bddm,pq,NULL, NULL,NULL, stdout);
	printf("\n\n--------------------------------------------------------------------\n");
	printf("--------------------------------------------------------------------\n");

	return(0);
}

