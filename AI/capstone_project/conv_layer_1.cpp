#include "conv_layer_1.h"

/**
 * 这份代码是CG4002 Capstone Project的时候负责在FPGA板上load我们的CNN模型的队友写的
 * 模型的训练是由我在jupyter notework上实现的 然后把weight直接拷贝了过来 (头文件)
 * 这里仅仅就是给定输入数据 进行神经网络的前向推导
*/
float relu(float inp){
	return (inp>=0)?inp:0;
}

float sigmoid(float inp){
	return 1 / (1 + exp(-inp));
}

void conv_layer_1(hls::stream<floating_point>& input_vector,  hls::stream<floating_point>& output_vector){
#pragma HLS INTERFACE axis port=output_vector register_mode=both register
#pragma HLS INTERFACE axis port=input_vector register_mode=both register
#pragma HLS INTERFACE s_axilite port=return


	floating_point inp;
	float input[40][6];
#pragma HLS ARRAY_PARTITION variable=input dim=2 factor=6 complete


	for(int i=0;i<40;i++){
		for(int j=0;j<6;j++){
			input_vector >> inp;
			input[i][j] = inp.data;
		}
	}

	float conv[38][32];
	for(int filter = 0; filter < 32; filter++){
#pragma HLS UNROLL factor=4
		for(int i = 0; i < 38; i++){
			float x = 0;
			for(int j = 0; j < 3; j++){
				for(int k = 0; k < 6; k++){
					x += input[i + j][k] * weights[j][k][filter];
				}
			}
			x += bias[filter];
			conv[i][filter] = relu(x);
		}
	}

	floating_point out = inp;
	for(int row = 0; row < 38; row++){
		for(int feature = 0; feature < 32; feature++){
			out.data = conv[row][feature];
			out.last = (row == 37 && feature == 31);
			output_vector << out;
		}
	}
}

void dense_layer_0(hls::stream<floating_point>& input_vector,  hls::stream<floating_point>& output_vector){
#pragma HLS INTERFACE axis port=output_vector register_mode=both register
#pragma HLS INTERFACE axis port=input_vector register_mode=both register
#pragma HLS INTERFACE s_axilite port=return

	floating_point inp;
	float input[96];
	for(int i=0;i<96;i++){
		input_vector >> inp;
		input[i] = inp.data;
	}

	float next_layer[64];
	float sum = 0;
	for(int i=0;i<64;i++){
		float val = 0;
		for(int j=0;j<96;j++){
			val += input[j] * weights[j][i];
		}
		val += bias[i];
		next_layer[i] = sigmoid(val);
	}

	floating_point output = inp;
	for(int i = 0; i < 64; i++){
		output.data = next_layer[i];
		output.last = (i == 63);
		output_vector << output;
	}
}

void maxpool_layer_1(hls::stream<floating_point>& input_vector,  hls::stream<floating_point>& output_vector){
#pragma HLS INTERFACE axis port=output_vector register_mode=both register
#pragma HLS INTERFACE axis port=input_vector register_mode=both register
#pragma HLS INTERFACE s_axilite port=return

	floating_point inp;
	float input[38][32];
	for(int i=0;i<38;i++){
		for(int j=0;j<32;j++){
			input_vector >> inp;
			input[i][j] = inp.data;
		}
	}

	float arr[19][32];

	for(int i=0;i<19;i++){
#pragma HLS UNROLL
		for(int j=0;j<32;j++){
			arr[i][j] = max(input[2*i][j], input[2*i + 1][j]);
		}
	}

	floating_point out = inp;
	for(int i=0;i<19;i++){
		for(int j=0;j<32;j++){
			out.data = arr[i][j];
			out.last = (i == 18 && j == 31);
			output_vector << out;
		}
	}

}