#include<stdio.h>	            //to use the printf function
#include<conio.h>         		//to use the getche function
#include<stdlib.h>         		//to use the rand function

#define GENE_COUNT 10
#define POPULATION 100

typedef struct Chrom{             		// creating the chrom structure
    short int bit[GENE_COUNT];
    int fit;
}chrom;

void evpop(chrom popcurrent[POPULATION]);    	//defining the functions that we will use
int fitness(chrom chrom);
void select(chrom popcurrent[POPULATION]);
void crossover(chrom popnext[POPULATION]);
void mutation(chrom popnext[POPULATION]);

int main(){

}

int fitness(chrom chrom){
  int bit_number = 0;
  int sum = 0;
  while(bit_number < GENE_COUNT){
    sum += (chrom.bit[bit_number]*(2^bit_number));
    bit_number++;
  }
  return(sum);                	//return the value of sum
}