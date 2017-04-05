#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define i_size 50000
#define f_size 100000
#define difference 5000

int linear_time(int array[], int length, int *interval_l, int *interval_h){
    	int i, cur_h, cur_l;
    	int max = 0;
    	int cur = 0;
    
    	for(i=0; i<length; i++){
        	cur_h = i;
        	if(cur > 0)
            		cur = cur + array[i];   
        	else{
            		cur_l = i;
			cur = array[i];
		}
        	if(cur > max){
            		max = cur;
			*interval_l = cur_l;
        		*interval_h = cur_h;
    		}
	}
	return max;
}

void randomArray(int *a, int n){
        int i, j;
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
	fprintf(fp_2, "Algorithm 4\n");
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
			value = linear_time(testArray, length, &interval_l, &interval_h);
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

int main(){
    	int i, value, interval_l, interval_h;
    	clock_t timer;
    	int *testArray;
	int tArray[] = {31,-41, 59, 26, -53, 58, 97, -93, -23, 84};	
	srand(time(NULL));	
	
	printf("---Test correctness of Algorithm 4---\n");
	test_file();
	printf("Please check MSS_Results.txt\n");

        printf("\n--------Results of Algorithm 4-------\n");	
        for(i=i_size; i<=f_size; i+=difference){        
		testArray = malloc((sizeof(int)*i));				//allocated memory location to the array
                randomArray(testArray, i);
                timer = clock();
                value = linear_time(testArray, i, &interval_l, &interval_h);
		timer = clock() - timer;
		free(testArray);
                printf("Size = %d\nMaximum Sum = %d\nTime = %f seconds\n\n", i, value, (float)timer / (float)CLOCKS_PER_SEC);
        }
	return 0;
}
