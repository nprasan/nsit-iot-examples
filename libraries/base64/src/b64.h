extern const char b64_alphabet[];
int b64_encode(char *output, char *input, int inputLen);
int b64_decode(char *output, char *input, int inputLen);
int b64_enc_len(int inputLen);
int b64_dec_len(char *input, int inputLen);