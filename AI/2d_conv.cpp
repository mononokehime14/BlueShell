#include <iostream>

/**
 * W is input width, H is input Height, K is kernel size, P is padding, S is stride
 * Assume data is already padded, for simplicity concern
 * Assume data is 2d array, store in a single array.
*/
float* 2d_convolution(float* data, float* kernel, int W, int H, int K, int P, int S, float bias) {
    int output_width = (W + 2 * P - K) / S + 1;
    int output_height = (H + 2 * P - K) / S + 1;
    float* output = new float(output_height * output_width);
    int output_i = 0, output_j = 0;
    for(int i = 0; i < H + 2 * P - K;i += S) { // at each height
        output_j = 0;
        for(int j = 0;j < W + 2 * P - K;j += S) { // at each width
            output[output_i * output_width + output_j] = element_wise_multiplication(data, kernel 
                i, j, K, W, bias);
            output_j++;
        }
        output_i++;
    }
    return output;
}

/**
 * 这里kernel的值实际上就是weight 如果是正向传播 每一个filter还有一个bias 要补在sum上
*/
float element_wise_multiplication(float* data, float* kernel, int startI, int startJ, int K, int W, float bias) {
    float sum = 0;
    for(int i = 0;i < K;i++) {
        for(int j = 0; j < K;j++) {
            sum += data[(startI + i) * W + (j + startJ)] * kernel[j * K + i];
        }
    }
    return sum + bias;
}

// int main() {
    
// }