#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define i_size 100
#define f_size 1000
#define difference 100
int Max_Subarray(int a[], int n, int *interval_l, int *interval_h);//for calculate max subarray
void randomArray(int *a, int n);//for random fill array
void test_file();

int main(){
	//test result for the first array in the test document
	printf("---Test correctness of Algorithm 1---\n");
	test_file();
        printf("Please check MSS_Results.txt\n");

	int j;
	int *testArray, interval_l, interval_h, value;
	clock_t timer;

	printf("\n--------Results of Algorithm 1-------\n");
	for(j = i_size; j <= f_size; j = j + difference){
		testArray = malloc((sizeof(int)*j));//allocated memory location to the array
		randomArray(testArray, j);
		timer = clock();
		value = Max_Subarray(testArray, j, &interval_l, &interval_h);
		timer = clock() - timer;
		free(testArray);
		printf("Size = %d\nMaximum Sum = %d\nTime = %f seconds\n\n", j, value, (float)timer / (float)CLOCKS_PER_SEC);
	}
	return 0;
}

int Max_Subarray(int a[], int n, int *interval_l, int *interval_h){
	int i, j, k, sum, maxSum;
	j = 0;
	k = 0;
	maxSum = 0;

	for(i = 0; i < n; i++){
 		for(j = i; j < n; j++){
    			sum = 0;
     			for(k = i; k <= j; k++){
      				sum += a[k];
      				if(sum > maxSum){
      					maxSum = sum;
	 				*interval_l = i;
					*interval_h = k;
				}
			}
   		} 
  	}
  	return maxSum;
}

void randomArray(int *a, int n){
	int i, j;
	srand(time(NULL));
	for(i = 0; i < n; i++){
		j = rand() % 200;
		j = j - 100;
		a[i] = j;
	}
}

void test_file(){
        int i, j, *testArray = malloc((sizeof(int)*100));
        char *substr;
        char str[1024], c[]=" ";
        int number, value, length, interval_l, interval_h;
        int negative=0;

        FILE *fp;
        FILE *fp_2;
        if(NULL == (fp = fopen("MSS_Problems.txt", "r"))){
                printf("error\n");
                exit(1);
        }

        fp_2 = fopen("MSS_Results.txt", "a");
        fprintf(fp_2, "Algorithm 1\n");
        while(!feof(fp)){
                memset(str, 0 , sizeof(str));
                fgets(str, sizeof(str)-1, fp);
                char *p = strtok(str,c);
                while(p!=NULL){
                        substr = malloc((sizeof(char)*100));
                        j = 0;
                        p[strlen(p)-1] = '\0';
                        for(i=0; i<strlen(p); i++){
                                if(isdigit(p[i])==1 || p[i]=='-'){
                                        substr[j] = p[i];
                                        j++;
                                }
                        }
                        p = strtok(NULL, c);
                        substr[j] = '\0';
                        number = atoi(substr);
                        free(substr);
                        testArray[length] = number;
                        length++;
                        negative = 0;
                }
                if(length > 0){
                        fprintf(fp_2, "[");
                        for(i=0; i<length; i++){
                                fprintf(fp_2, "%d ", testArray[i]);
                        }
                   	fprintf(fp_2, "]\n");
                        value = Max_Subarray(testArray, length, &interval_l, &interval_h);
                        fprintf(fp_2, "[");
			             for(i=interval_l; i<=interval_h; i++){
                                fprintf(fp_2, "%d ", testArray[i]);
                        }
                        fprintf(fp_2, "]\n");
                        fprintf(fp_2, "%d\n\n", value);
                        length = 0;
                }
        }
        fclose(fp);
        fclose(fp_2);
}

