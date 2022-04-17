#include<stdio.h>	            //to use the printf function
#include<conio.h>         		//to use the getche function
#include<stdlib.h>         		//to use the rand function
#include<time.h>                //to use the time function

#define GENE_COUNT 10
#define POPULATION 100
#define ITER 100
#define STATIC_POP_FILE "population.txt"

typedef struct Chrom{             		// creating the chrom structure
    short int bit[GENE_COUNT];
    int fit;
    double prob;
}chrom;

void init_pop(chrom popcurrent[POPULATION]);    	//defining the functions that we will use
int fitness(chrom chrom);
void select(chrom popcurrent[POPULATION], chrom selected[POPULATION]);
void crossover(chrom popnext[POPULATION]);
void mutation(chrom popnext[POPULATION]);
void sort(chrom popcurrent[POPULATION]);

int main(){

}

chrom convert_str_2_chrom(char* chrom_str){         //Accepts a string of 1s & 0s to the length of GENE_COUNT.
    chrom chromo;                                   //Will return the corresponding chromosome.
    for(int i=0;chrom_str[i];i++){
        if(i>=GENE_COUNT || (chrom_str[i]!='0' && chrom_str[i]!='1')){
            printf("Error!\nInvalid string as a chromosome.\n");
            exit(EXIT_FAILURE);
        }
        chromo.bit[i] = chrom_str[i] - '0';
    }
    return chromo;
}

void init_pop(chrom popcurrent[POPULATION]){        //Read Initial population from a static file. STATIC_POP_FILE
    FILE *population;

    population = fopen(STATIC_POP_FILE,"rt");

    if(population == NULL){
        printf("Error!\nCouldn't open population file.\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<POPULATION;i++){
        char chrom_str[GENE_COUNT + 2];
        fscanf(population,"%s",chrom_str);
        chrom_str[GENE_COUNT] = 0;
        popcurrent[i] = convert_str_2_chrom(chrom_str);
    }
    long long int total_fitness = 0;
    for(int i=0;i<POPULATION;i++){
        popcurrent[i].fit = fitness(popcurrent[i]);
        total_fitness += popcurrent[i].fit;
    }
    for(int i=0;i<POPULATION;i++){
        popcurrent[i].prob = (double)popcurrent[i].fit/total_fitness;
    }

}

int fitness(chrom chrom){
    int bit_number = 0;
    int sum = 0;
    while(bit_number < GENE_COUNT){
        sum += (chrom.bit[bit_number]*(2^bit_number));
        bit_number++;
    }
    sum = sum%101;
    return(sum);                	//return the value of sum
}

void select(chrom popcurrent[POPULATION], chrom selected[POPULATION]){      //perfom selection on the curr pop considering prob.
    sort(popcurrent);
    for(int j=0;j<POPULATION;j++){
        srand((unsigned)time(NULL));
        double random = rand()/RAND_MAX;
        double cumulative_prob = 0;
        for(int i=0;i<POPULATION;i++){
            cumulative_prob += popcurrent[i].prob;
            if(random<cumulative_prob){
                selected[j] = popcurrent[i];
                break;
            }
        }
    }
}

void sort(chrom popcurrent[POPULATION]){        //sort pop by their prob
    chrom temp;
    for(int i=0 ; i<POPULATION ; i++){
        for(int j=0; j<POPULATION ; j++){
            if(popcurrent[j].fit>popcurrent[j+1].fit){
            temp=popcurrent[j+1];
            popcurrent[j+1]=popcurrent[j];
            popcurrent[j]=temp;
            }
        }
    }
}

void crossover(chrom selected[POPULATION]){ // crossover function takes a pointer to array of chromes
    int random;
    random=rand();
    chrom temp_child;
    random=((random%(GENE_COUNT-1))+1); //random cross over for first child (child of first selected chrom and the last one)
    for(int i=0;i<random;i++){
        temp_child.bit[i] = selected[0].bit[i];
    }
    for(int i=random;i<GENE_COUNT-1;i++){
        temp_child.bit[i] = selected[POPULATION-1].bit[i];
    }
    for(int chrom_counter = 0 ; chrom_counter<POPULATION ; chrom_counter++){
        random=rand();
        random=((random%(GENE_COUNT-1))+1);
        for(int i=random;i<GENE_COUNT;i++){
            selected[chrom_counter].bit[i] = selected[chrom_counter+1].bit[i];
        }    
    }
    selected[POPULATION-1] = temp_child; //the last selected chrom now becomes the new child
}                  
