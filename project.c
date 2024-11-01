#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

/*MEAN of the Numbers*/
int main() {
    int n, i;
    float num[100], sum = 0.0, mean;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    for(i = 0; i < n; ++i) {
        printf("Enter number %d: ", i + 1);
        scanf("%f", &num[i]);
        sum += num[i];
    }

    mean = sum / n;
    printf("The mean of the given numbers is %.2f", mean);

    return 0;
}

/*Standard Deviation*/
int main() {
    int n, i;
    float num[100], sum = 0.0, mean, vari, s_dev;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    for(i = 0; i < n; ++i) {
        printf("Enter number %d: ", i + 1);
        scanf("%f", &num[i]);
        sum += num[i];
    }

    mean = sum / n;

    for(i = 0; i < n; ++i) {
        vari += pow(num[i] - mean, 2);
    }

    vari /= n;
    s_dev = sqrt(vari);

    printf("The standard deviation of the given numbers is %.2f", s_dev);

    return 0;
}

/*Median*/
int main() {
    int n, i, j, temp;
    float num[100], median;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    for(i = 0; i < n; ++i) {
        printf("Enter number %d: ", i + 1);
        scanf("%f", &num[i]);
    }

    // sorting the array in ascending order
    for(i = 0; i < n; ++i) {
        for(j = i + 1; j < n; ++j) {
            if(num[i] > num[j]) {
                temp = num[i];
                num[i] = num[j];
                num[j] = temp;
            }
        }
    }

    // finding the median
    if(n % 2 == 0) {
        median = (num[(n / 2) - 1] + num[n / 2]) / 2.0;
    } else {
        median = num[n / 2];
    }

    printf("The median of the given numbers is %.2f", median);

    return 0;
}


------------------------------------------------------------------------------------------
/*New Version*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

// Global Variables
double mean, std_dev, median; 

// Mean Function
void* meanFunc(void* param) {
    double* num = (double*) param;
    double sum = 0.0;
    for (int i = 0; i < 8; i++) {
        sum += num[i];
    }
    mean = sum / 8.0;
    pthread_exit(NULL);
}

// Standard Deviation Function
void* std_devFunc(void* param) {
    double* num = (double*) param;
    double sum = 0.0;
    for(int i = 0; i < 8; i++) {
        sum += num[i];
    }
    mean = sum / 8;
    for (int i = 0; i < 8; i++) {
        std_dev += pow(num[i] - mean, 2);
    }
    std_dev = sqrt(std_dev / 8.0);
    pthread_exit(NULL);
}

// Median Function
void* medianFunc(void* param) {
    double *num = (double*) param;
    int temp, i, j;
    // Sorts the array in ascending order
    for(i = 0; i < 8; i++) {
        for(j = i + 1; j < 8; ++j) {
            if(num[i] > num[j]) {
                temp = num[i];
                num[i] = num[j];
                num[j] = temp;
            }
        }
    }
    // Then finds the Median
    if(8 % 2 == 0) {
        median = (num[(8 / 2) - 1] + num[8 / 2]) / 2.0;
    } else {
        median = num[8 / 2];
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 9) {
        printf("How to run the program: ./project num1 num2 num3 num4 num5 num6 num7 num8\n");
        return 1;
    }

    // Parse to a list of doubles
    double num[8];
    for (int i = 0; i < 8; i++) {
        num[i] = atof(argv[i + 1]);
    }

    // Creates three worker threads for the mean, standard deviation, and median 
    // to synchronize all three methods together.
    // Works more efficient
    pthread_t meanFunc_thread, std_devFunc_thread, medianFunc_thread;
    pthread_create(&meanFunc_thread, NULL, meanFunc, (void*) num);
    pthread_create(&std_devFunc_thread, NULL, std_devFunc, (void*) num);
    pthread_create(&medianFunc_thread, NULL, medianFunc, (void*) num);

    // Waits for the threads to finish
    pthread_join(meanFunc_thread, NULL);
    pthread_join(std_devFunc_thread, NULL);
    pthread_join(medianFunc_thread, NULL);

    // Output
    printf("Output \n");
    printf("Mean: %.2f\nStandard Deviation: %.2f\nMedian: %.2f\n", mean, std_dev, median);

    return 0;
}