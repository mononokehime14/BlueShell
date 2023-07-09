void 2d_maxpooling(float* input, float* output, int Win, int Hin, int Wout, int Hout) {
    int width_batch = (Win + Wout - 1) / Wout;
    int height_batch = (Hin + Hout - 1) / Hout;
    for(int i = 0;i < Hout;i++) {
        for(int j = 0;j < Wout;j++) {
            int width_offset = j * width_batch;
            int height_offset = i * height_batch;
            float sum = 0;
            for(int k = height_offset;k < Hin;k++) {
                for(int l = width_offset;l < Win;l++) {
                    sum += input[k * Win + l];
                }
            }
            output[i * Wout + j] = sum;
        }
    }
}