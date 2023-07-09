#include <iostream>

/**
 * i1   o1
 * i2   o2
 * i3   o3
 * i4
 * 
 * o1 = i1 * w11 + i2 * w21 + i3 * w31 + i4 * w41
*/
void dense_layer_forward(float* input, float* output, float* weights, int Win, int Wout) {
    for(int i = 0;i < Win;i++) {
        float sum = 0;
        for(int j = 0;j < Wout;j++) {
            sum += input[i] * weights[i * Win + j];
        }
        output[j] = sum;
    }
}