#include <stdio.h>

#define ARRAY_SIZE 10

float mpu6050[ARRAY_SIZE] = {0.0, 11.68, 18.95, 23.56, 25.72, 25.38, 22.65, 18.01, 10.14, -0.26};
float bno55[ARRAY_SIZE]   = {0.0, 9.49, 16.36, 21.2, 23.16, 22.8, 19.5, 14.85, 6.79, -2.69};

// func to calculate weighted average based on accuracy
float weightedAverage(float val1, float val2, float acc1, float acc2);

// func to apply Kalman Filter
float kalmanFilter(float measurement, float prevEstimate, float processNoise);

int main() {
    float output_fair[ARRAY_SIZE];
    float output_good[ARRAY_SIZE];
    float output_hero[ARRAY_SIZE];
    float output_legend[ARRAY_SIZE];

    float imuAccuracy = 0.79; // 79%
    float bnoAccuracy = 0.92; // 92%
    float processNoise = 0.2; 

    for (int i = 0; i < ARRAY_SIZE; i++) {
        // Fair: Used averaging sensor without regard accuracy of each sensor and generated reasonable output
        output_fair[i] = (mpu6050[i] + bno55[i]) / 2.0;

        // Good: Used averaging sensor with taking into consideration the accuracy of each sensor and generate reasonable output
        output_good[i] = weightedAverage(mpu6050[i], bno55[i], imuAccuracy, bnoAccuracy);

        // Hero: Used dynamic filter such as Kalman filter and generated reasonable output
		// i tried the equation but it gave me zero and idk why and i think that legend depends on it
        if (i == 0) {
            output_hero[i] = (mpu6050[i] + bno55[i]) / 2.0;
        } else {
            output_hero[i] = kalmanFilter((mpu6050[i] + bno55[i]) / 2.0, output_hero[i - 1], processNoise);
        }

        /*Legend: Used dynamic filter such as Kalman filter and taking into 
		consideration the physics of projectile to infer new information 
		and fuse all this information and generate reasonable output.*/
    }

    printf("Fair output:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%.2f ", output_fair[i]);
    }

    printf("\n\nGood output:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%.2f ", output_good[i]);
    }

    printf("\n\nHero output:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%.2f ", output_hero[i]);
    }

    return 0;
}

float weightedAverage(float val1, float val2, float acc1, float acc2) {
    return (acc1 * val1 + acc2 * val2) / (acc1 + acc2);
}

float kalmanFilter(float measurement, float prevEstimate, float processNoise) {
    float prediction = prevEstimate; 
    float kalmanGain = prevEstimate / (prevEstimate + processNoise);
    float estimate = prediction + kalmanGain * (measurement - prediction);
    return estimate;
}