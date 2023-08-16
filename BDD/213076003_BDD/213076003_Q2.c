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
	
	
	// compute subset B
	bdd b_1 = bdd_xor (bddm, cout,s3);
	bdd b_2 = bdd_xor (bddm, b_1,s2);
	bdd b_3 = bdd_xor (bddm, b_2,s1);
	bdd subset_b = bdd_xor (bddm, b_3,s0);

	// Existential quantification
	bdd p = bdd_and(bddm, Xadder, subset_b);
	//bdd_print_bdd(bddm,p,NULL, NULL,NULL, stdout);
	bdd Q[6];
	Q[0] = sum0; Q[1] = sum1; Q[2] = sum2; Q[3] = sum3; Q[4] = cout; Q[5] = 0;
	int assoc = bdd_new_assoc(bddm,Q,0);
	bdd_assoc(bddm,assoc);
	
	printf("NOTE : \n");
	printf("var.0 is x3\n");
	printf("var.1 is x2\n");
	printf("var.2 is x1\n");
	printf("var.3 is x0\n");
	printf("var.4 is y3\n");
	printf("var.5 is y2\n");
	printf("var.6 is y1\n");
	printf("var.7 is y0\n");

	bdd pq = bdd_exists(bddm,p);
	printf("-------------------------BDD for Question 2-------------------------\n");
	printf("--------------------------------------------------------------------\n\n");
	bdd_print_bdd(bddm,pq,NULL, NULL,NULL, stdout);
	printf("\n\n--------------------------------------------------------------------\n");
	printf("--------------------------------------------------------------------\n");

	return(0);
}

