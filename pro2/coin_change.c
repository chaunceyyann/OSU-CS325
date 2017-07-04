#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h> 
#include <limits.h>

int changegreedy(int v[], int A, int length, int *coin_array);
int changedp(int v[], int A, int length, int *coin_array);
void test_file(char* input_name);
void output(char* output_name, int testArray[], int A, int length);

struct Coin
{
        int arr[1024];
        int total;
        int length;
};


int main(int argc, char *argv[])
{
	test_file(argv[1]);
	return 0;
}

int changegreedy(int v[], int A, int length, int *coin_array)
{
	int i, j, answer, minimum_count=0;
	
	while(A>0)
	{
		for(i=length-1; i>=0; i--)
			if(v[i]<=A)
			{
				A = A - v[i];
				minimum_count++;
				coin_array[i]++;
				break;
			}
	}				
	return minimum_count;
}

int changedp(int v[], int A, int length, int *coin_array)
{
	int i, j, k, mini_count[A+1];
	int matrix[A+1][length];

	mini_count[0] = 0;
	for(i=1; i<=A; i++)
		mini_count[i] = INT_MAX;

	for(i=0; i<=A; i++)
		for(j=0; j<length; j++)
			matrix[i][j] = 0;
	
	for(i=1; i<=A; i++)
	{	
		for(j=0; j<length; j++)
		{	
			if(v[j] <= i && mini_count[i-v[j]]+1 < mini_count[i])
			{
				for(k=0; k<length; k++)
				{
					matrix[i][k]=0;
					matrix[i][k] += matrix[i-v[j]][k]; 
				}
				mini_count[i] = mini_count[i-v[j]] + 1;
				matrix[i][j] += 1; 
			}
		}
	}
	for(k=0; k<length; k++) 
		coin_array[k] = matrix[A][k];	
	return mini_count[A];
}

void output(char* output_name, int testArray[], int A, int length)
{
	int i, value, count_coin_1[length], count_coin_2[length];
	FILE *fp_2;
	clock_t timer;

	for(i=0; i<length; i++)
	{
		count_coin_1[i] = 0;
		count_coin_2[i] = 0;	
	}

	fp_2 = fopen(output_name, "a");

	fprintf(fp_2, "DP Algorithm\n");
	timer = clock();
	value = changedp(testArray, A, length, count_coin_1);
	timer = clock() - timer;
	fprintf(fp_2, "[");
	for(i=0; i<length-1; i++)
		fprintf(fp_2, "%d, ", count_coin_1[i]);
	fprintf(fp_2, "%d", count_coin_1[i]);
	fprintf(fp_2, "]\n");

	fprintf(fp_2, "%d\n", value);
	//fprintf(fp_2, "Time: %fs", (float)timer / (float)CLOCKS_PER_SEC);

	fprintf(fp_2, "\nGreedy Algorithm\n");
	//call changegreedy function 
	timer = clock();
	value = changegreedy(testArray, A, length, count_coin_2);
	timer = clock() - timer;
	
	fprintf(fp_2, "[");
	for(i=0; i<length-1; i++)
		fprintf(fp_2, "%d, ", count_coin_2[i]);
    fprintf(fp_2, "%d", count_coin_2[i]);        
   	fprintf(fp_2, "]\n");
    fprintf(fp_2, "%d\n", value);	
	//fprintf(fp_2, "Time: %fs\n", (float)timer / (float)CLOCKS_PER_SEC);
	fprintf(fp_2, "---------------------------\n");
		
	fclose(fp_2);

}


void test_file(char* input_name)
{
        int i, j, *testArray = malloc((sizeof(int)*100));
        char *substr;
        char str[1024], c[]=" ", output_name[1024];;
        int number, negative=0, line=0;

	FILE *fp;
	FILE *fp_2;
        if(NULL == (fp = fopen(input_name, "r")))
		{
                printf("Error, this file does not exist\n");
                exit(1);
        }
	strcpy(output_name, input_name);
        strtok(output_name, ".");
        strcat(output_name, "change.txt");
	
	struct Coin Array[1024];//
	int k = 0;
	Array[k].length = 0;
	Array[k].total = 0;
	while(!feof(fp))
	{
                memset(str, 0 , sizeof(str));
                fgets(str, sizeof(str)-1, fp);
		// read data from a txt file
		if(line==0)
		{			
			char *p = strtok(str,c);
                	while(p!=NULL)
					{
                        	substr = malloc((sizeof(char)*1024));
                        	j = 0;
                        	p[strlen(p)-1] = '\0';
                        	for(i=0; i<strlen(p); i++)
							{
                                	if(isdigit(p[i])==1 || p[i]=='-')
									{
                                        	substr[j] = p[i];
                                        	j++;
                                	}
                        	}
                        	p = strtok(NULL, c);
                        	substr[j] = '\0';
                        	number = atoi(substr);
                        	free(substr);
                        	negative = 0;
				Array[k].arr[Array[k].length]= number;//
                                Array[k].length++;//
                	}
			line = 1;
		}
		else
		{
			str[strlen(str)-1] = '\0';
			Array[k].total = atoi(str);//	
			line = 0;
			k += 1;
			Array[k].length = 0;
			Array[k].total = 0; 
		}
	}
	
    fclose(fp);
	for(i=0; i<k; i++)
		output(output_name, Array[i].arr, Array[i].total, Array[i].length);
}
