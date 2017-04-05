#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define i_size 1000000
#define f_size 10000000
#define difference 1000000

int compare(int value_1, int value_2, int value_3){
	int max=0;
	if(value_1 > value_2)
		max = value_1;
	else
		max = value_2;
	
	if(value_3 > max)
		max = value_3;
	
	return max;
}

int divide_and_conquer(int array[], int left, int right){
	int i, mid;
	int l_sum=0, r_sum=0;
	int l_m_sum=0, r_m_sum=0;
	int temporay=0;

	if(left==right)
		return array[left];
	
        mid = (left + right) / 2;
        
        l_sum = divide_and_conquer(array, left, mid);
        r_sum = divide_and_conquer(array, mid+1, right);	
	
	for(i=mid; i>=left; i--){
		temporay += array[i];
		if(temporay > l_m_sum)	
			l_m_sum = temporay;
	}
	
	temporay = 0;

	for(i=mid+1; i<=right; i++){
		temporay += array[i];
		if(temporay > r_m_sum)
			r_m_sum = temporay;
	}
	
	return compare(l_sum, r_sum, l_m_sum + r_m_sum);
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
        fprintf(fp_2, "Algorithm 3\n");
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
                        /*fprintf(fp_2, "[");
                        value = linear_time(testArray, length, &interval_l, &interval_h);
                        for(i=interval_l; i<=interval_h; i++){
                                fprintf(fp_2, "%d ", testArray[i]);
                        }
                        fprintf(fp_2, "]\n");*/
			value = divide_and_conquer(testArray, 0, length-1);
                        fprintf(fp_2, "%d\n\n", value);
                        length = 0;
                }
        }
        fclose(fp);
        fclose(fp_2);
}

	
int main(){
	int value, i;
	clock_t timer;
	int *rArray;
	srand(time(NULL));

	printf("---Test correctness of Algorithm 3---\n");
	test_file();
        printf("Please check MSS_Results.txt\n");
	
	printf("\n--------Results of Algorithm 3-------\n");
	for(i=i_size; i<=f_size; i+=difference){	
		rArray = malloc((sizeof(int)*i));//allocated memory location to the array
                randomArray(rArray, i);	
		timer = clock();
		value = divide_and_conquer(rArray, 0, i-1);
		timer = clock() - timer;
		free(rArray);
		printf("Size = %d\nMaximum Sum = %d\nTime = %f seconds\n\n", i, value, (float)timer / (float)CLOCKS_PER_SEC);
	}
	return 0;
}
