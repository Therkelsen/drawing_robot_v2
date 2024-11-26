#include "matmul.hpp"


/* Layer 1 matrix multiplication */
void l1_mm(float input[n_inputs], const float weights[n_inputs][n_layer1], float output[1][n_layer1]) {
    col: for (int j = 0; j < n_layer1; ++j) {
	#pragma HLS UNROLL
      float sum = 0;

      prod: for (int k = 0; k < n_inputs; ++k){
		#pragma HLS UNROLL
        sum += input[k] * weights[k][j];
      }
      output[0][j] = sum;
    }

  return;
}



/* Layer 2 matrix multiplication */
void l2_mm(float input[1][n_layer1], const float weights[n_layer1][n_layer2], float output[1][n_layer2]) {

    col: for (int j = 0; j < n_layer2; ++j) {
	#pragma HLS UNROLL
      float sum = 0;

      prod: for (int k = 0; k < n_layer1; ++k){
		#pragma HLS UNROLL
        sum += input[0][k] * weights[k][j];
      }
      output[0][j] = sum;
    }


  return;
}



/* Layer 3 matrix multiplication */
void l3_mm(float input[1][n_layer2], const float weights[n_layer2][n_layer3], float output[1][n_layer3]) {

    col: for (int j = 0; j < n_layer3; ++j) {
	#pragma HLS UNROLL
      float sum = 0;

      prod: for (int k = 0; k < n_layer2; ++k){
		#pragma HLS UNROLL
        sum += input[0][k] * weights[k][j];
      }
      output[0][j] = sum;
    }

  return;
}



/* ReLU layer 1 activation function */
void l1_relu(float input[1][n_layer1], float output[1][n_layer1]){
	loop1: for (int i = 0; i < n_layer1; i++){
	#pragma HLS UNROLL
		if (input[0][i] < 0.0)
			output[0][i] = 0.0;
		else
			output[0][i] = input[0][i];
	}

	return;
}



/* ReLU layer 2 activation function */
void l2_relu(float input[1][n_layer2], float output[1][n_layer2]){
	loop1: for (int i = 0; i < n_layer2; i++){
	#pragma HLS UNROLL
		if (input[0][i] < 0.0)
			output[0][i] = 0.0;
		else
			output[0][i] = input[0][i];
	}

	return;
}



/* Softmax layer 3 activation function */
void l3_softmax(float input[1][n_layer3], int &pred){
	int max_idx = -1;
	float max_val = -999.9;
	loop1: for (int i = 0; i < n_layer3; i++){
	#pragma HLS UNROLL
		if (input[0][i] > max_val){
			max_idx = i;
			max_val = input[0][i];
		}
	}
	pred = max_idx;
	return;
}



/* Connect NN Layers */
void nn_inference(float input_img[n_inputs], int& out_r){
	#pragma HLS INTERFACE s_axilite port=return bundle=AXI_CPU
	#pragma HLS INTERFACE s_axilite port=input_img bundle=AXI_CPU
	#pragma HLS INTERFACE s_axilite port=out_r bundle=AXI_CPU

	float temp_output[1][n_layer1] = {1};
	float temp_output2[1][n_layer2] = {1};
	float temp_output3[1][n_layer3] = {1};
	int prediction = -1;

	l1_mm(input_img, weights::layer1_weights, temp_output);
	l1_relu(temp_output, temp_output);
	l2_mm(temp_output, weights::layer2_weights, temp_output2);
	l2_relu(temp_output2, temp_output2);
	l3_mm(temp_output2, weights::layer3_weights, temp_output3);
	l3_softmax(temp_output3, prediction);
	out_r = prediction;
}
