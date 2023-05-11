#include <stdio.h>
#include <stdint.h>

uint32_t point[2];
int p=173;
uint32_t sum_result[2];

unsigned char roundKey[15][16];
//subByte table
unsigned char sub[16][16] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
    };
  

uint32_t k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe,0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb,0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb,0xbef9a3f7, 0xc67178f2
};

uint32_t constants[]={0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19};

uint32_t result[]={0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19};



//AES 256

  // this function printing the 2d matrix
void print(unsigned char mat[4][4]){
 printf("\n");
  for(int i = 0;i<4;i++){
  for(int j=0;j<4;j++){
  printf("%hhx ",mat[j][i]);
  }

  }
    printf("\n");
}

 //finding the sub Byte from the given table
unsigned char subbytes(unsigned char a){
int t1,t2;
//finding the column
t1 = a&15;
//finding the row
t2 = a>>4;
return sub[t2][t1];
}

//In this function, the 32-bit input is divided into four 8-bit parts, and then each of those 8-bit parts is extracted individually. These 8-bit parts are then concatenated back together in the same order they were originally in
uint32_t subword(uint32_t word){
uint32_t newWord = 0;
unsigned char n1 = word>>24;
n1 = subbytes(n1);
unsigned char n2 = word>>16;
n2 = subbytes(n2);
unsigned char n3 = word>>8;
n3 = subbytes(n3);
unsigned char n4 = word;
n4 = subbytes(n4);

newWord|= n1<<24|n2<<16|n3<<8|n4;
return newWord;
}

//this is key scheduling algorithm generating the 11 round key
 void keySchedulingAES(unsigned char key[32]){
uint32_t  Rconstant[8];
uint32_t  word[60];

//8 constant value 32 bit array
Rconstant[0] = 0x01000000;
Rconstant[1] = 0x02000000;
Rconstant[2] = 0x04000000;
Rconstant[3] = 0x08000000;
Rconstant[4] = 0x10000000;
Rconstant[5] = 0x20000000;
Rconstant[6] = 0x40000000;
Rconstant[7] = 0x80000000;


//first key is same as given key
for(int i=0;i<=7;i++){
word[i] = key[4*i]<<24|key[4*i+1]<<16|key[4*i+2]<<8|key[4*i+3];
}

//creating the other words
for(int i=8;i<=59;i++){
uint32_t w = word[i-1];
if(i%8==0){
w = subword((w<<8) | (w >> 24)) ^ Rconstant[i/8 - 1];
}
else if(i%8==4){
w = subword(w);
}
word[i] = word[i-8]^w;
}
int k = 0;

//now storing the 4 word in the key and making the round key
for(int i=0;i<=56;i+=4){

roundKey[k][0] = word[i]>>24;
roundKey[k][1] = word[i]>>16;
roundKey[k][2] = word[i]>>8;
roundKey[k][3] = word[i];
roundKey[k][4] = word[i+1]>>24;
roundKey[k][5] = word[i+1]>>16;
roundKey[k][6] = word[i+1]>>8;
roundKey[k][7] = word[i+1];
roundKey[k][8] = word[i+2]>>24;
roundKey[k][9] = word[i+2]>>16;
roundKey[k][10] = word[i+2]>>8;
roundKey[k][11] = word[i+2];
roundKey[k][12] = word[i+3]>>24;
roundKey[k][13] = word[i+3]>>16;
roundKey[k][14] = word[i+3]>>8;
roundKey[k][15] = word[i+3];
k++;
}
}

//This function allows for the multiplication of an 8-bit value "x" by the i-th power 
//under modulo x^8+x^4+x^3+x+1
unsigned char polynomial_multiply(unsigned char temp){

unsigned char res=temp<<1;

if(temp>>7==1){
res=res^27;
}

return res;
}

//Mix column function multiplying the matrix
//converting the value of the matrix element to polynomial form
// 4 - x^2
// 5 - x^2 + 1
//for multipication with x^i we made a function polynomial_multiply(x,i)
void MixColumn(unsigned char x[4][4]){
unsigned char mix[4][4];
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
mix[i][j] = x[i][j];
}
}
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
 x[j][i]=polynomial_multiply(mix[j][i]) ^ polynomial_multiply(mix[(j+1)%4][i]) ^ mix[(j+1)%4][i] ^ mix[(j+2)%4][i] ^ mix[(j+3)%4][i];
}
}
}

// inverse_MixColumn function multiplying the inverse matrix
//converting the value of the matrix element to polynomial form
// 165 - x^7+x^5+x^2+1
// 7 - x^2 + x + 1
// 26 - x^4+x^3 + x
// 115 - x^6 + x^4 + x^5 + x + 1
//for multipication with x^i we made a function polynomial_multiply(x,i)
void inverse_MixColumn(unsigned char x[4][4]){
unsigned char mix[4][4];
for(int k=0;k<3;k++){
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
mix[i][j] = x[i][j];
}
}
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
     x[j][i]=polynomial_multiply(mix[j][i]) ^ polynomial_multiply(mix[(j+1)%4][i]) ^ mix[(j+1)%4][i] ^ mix[(j+2)%4][i] ^ mix[(j+3)%4][i];

}
}
}
}
//this shift row function we shifting the row
//first row is same
//second row shifting by 1 circular left
//3rd row shifting by 2 circular left
//4th row shifting by 3 circular left
void shift(unsigned char x[4][4]){
for(int i=0;i<4;i++){
for(int j=0;j<i;j++){
unsigned char t1 = x[i][0];
x[i][0] = x[i][1];
x[i][1] = x[i][2];
x[i][2] = x[i][3];
x[i][3] = t1;
}
}
}

//this inverse shift row function we shifting the row
//first row is same
//second row shifting by 1 circular right
//3rd row shifting by 2 circular right
//4th row shifting by 3 circular right
void inverseshift(unsigned char x[4][4]){
for(int i=0;i<4;i++){
for(int j=0;j<i;j++){
unsigned char t1 = x[i][3];
x[i][3] = x[i][2];
x[i][2] = x[i][1];
x[i][1] = x[i][0];
x[i][0] = t1;
}
}
}

// this is the decryption of sub byte
// 2x+1
// first we xor with 1
// so we need x so we finding multiplicative inverse of 2
// x^7+x^3+x^2
unsigned char inverseSub(unsigned char a){
int i,j;
unsigned char x;
for(int i=0;i<16;i++){
for(int j=0;j<16;j++){
if(sub[i][j]==a){
x = i;
x = (x<<4)|j;


return x;
}
}
}
return 0;
}

// finding the sub byte of 2x+1
// 2x is nothing but multiplying with the x adding 1 is xor 1
//for multiplying x we made a function polynomial_multiply(x,1)
void Subbyte(unsigned char plaintext[4][4]){
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
plaintext[i][j] = subbytes(plaintext[i][j]);
}
}
}

//finding the decryption of subbyte of the matrix
void inverse_Subbyte(unsigned char plaintext[4][4]){
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
plaintext[i][j] = inverseSub(plaintext[i][j]);
}
}
}

//XOR the plaintext with key
void XOR_with_key(unsigned char plaintext[4][4],int round){
int k = 0;
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
plaintext[j][i] ^=  roundKey[round][k];
k++;
}
}
}

//now arranging the all the method for final encryption 
//round 1 to 9 
// XOR with ki
// subbyte
// shift row
// mix column
// for round 10 
// XOR with ki
// subbyte
// shift row
// the last XOR with round key 11
void AES_encryption(unsigned char plaintext[4][4]){
for(int i=0;i<13;i++){

//calling xor function
XOR_with_key(plaintext,i);
//printf("XOR with round Key K%d",i+1);
//print(plaintext);
//calling Subbyte function
Subbyte(plaintext);
//printf("Subbyte");
//print(plaintext);
//calling shift function
shift(plaintext);
//printf("Shift row");
//print(plaintext);
//calling MixColumn function
MixColumn(plaintext);
//printf("Mixcoulmn");
//print(plaintext);
// printf("*********** Round %d ***********",i+1);
// print(plaintext);
}
//calling xor function
XOR_with_key(plaintext,13);
//printf("XOR with round Key K%d",10);
//print(plaintext);

//calling Subbyte function
Subbyte(plaintext);
//printf("Subbyte");
//print(plaintext);
//calling shift function
shift(plaintext);
//printf("Shift row");
//print(plaintext);
XOR_with_key(plaintext,14);
//printf("XOR with round Key K%d",11);
// printf("*********** Round 10 ***********");
// print(plaintext);
}

// now decryption in reverse oder of encryption
void AES_decryption(unsigned char plaintext[4][4]){
//calling xor function
XOR_with_key(plaintext,14);
//calling inverseshift function
inverseshift(plaintext);
//calling inverse_Subbyte function
inverse_Subbyte(plaintext);
//calling xor function
XOR_with_key(plaintext,13);
// printf("*********** Round 10 ***********");
// print(plaintext);
for(int i=12;i>=0;i--){
//calling inverse_MixColumn function
inverse_MixColumn(plaintext);
//calling inverseshift function
inverseshift(plaintext);
//calling inverse_Subbyte function
inverse_Subbyte(plaintext);
//calling xor function
XOR_with_key(plaintext,i);
// printf("*********** Round %d ***********",i+1);
// print(plaintext);
}
}
void XOR_IV(unsigned char plaintext[4][4],unsigned char IV[16]){
    int k = 0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            plaintext[j][i] = plaintext[j][i]^IV[k];
            k++;
        }
    }
}
void CBC_Enc(unsigned char plaintext[4][8]){
    unsigned char plaintext1_128[4][4],plaintext2_128[4][4];
    unsigned char IV[16]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            plaintext1_128[i][j] = plaintext[i][j];
        }
    }
    
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            plaintext2_128[i][j] = plaintext[i][j+4];
        }
    }
    
    XOR_IV(plaintext1_128,IV);
    AES_encryption(plaintext1_128);
    
    int k=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            IV[k] = plaintext1_128[j][i];
            k++;
        }
    }
    XOR_IV(plaintext2_128,IV);
    AES_encryption(plaintext2_128);
    
    for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
plaintext[i][j]=plaintext1_128[i][j];
}
}

for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
plaintext[i][j+4]=plaintext2_128[i][j];
}
}
    
}



//CBC mode 
void CBC_Dec(unsigned char plaintext[4][8]){
     unsigned char cipher1[4][4],cipher2[4][4];
      unsigned char IV[16]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
     for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cipher1[i][j] = plaintext[i][j];
        }
    }
    
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cipher2[i][j] = plaintext[i][j+4];
        }
    }
    int k=0;
    
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            IV[k] = cipher1[j][i];
            k++;
        }
    }
    AES_decryption(cipher2);
    XOR_IV(cipher2,IV);
    
    AES_decryption(cipher1);
    
        for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
plaintext[i][j]=cipher1[i][j];
}
}

for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
plaintext[i][j+4]=cipher2[i][j];
}
}
    
}




void find_x_y(){

for(uint32_t i=0;i<p;i++){
for(uint32_t j=0;j<p;j++){

uint32_t left=(j*j)%p;
uint32_t right=(i*i*i + 23*i + 11)%p;

if(left==right){
point[0]=i;
point[1]=j;
break;
}

}

}
}

uint32_t find_additive_inverse(uint32_t temp){
return (p-temp)%p;
}

uint32_t multiplicative_inverse(uint32_t a, uint32_t b)
{
    uint32_t q = 0;
    uint32_t r = 1;
    uint32_t s1 = 1;
    uint32_t s2 = 0;
    uint32_t s3 = 1;
    uint32_t t1 = 0;
    uint32_t t2 = 1;
    uint32_t t3 = 0;
    while (r > 0)
    {
        q = a / b;
        r = a - q * b;
        s3 = s1 - q * s2;
        t3 = t1 - q * t2;
        if (r > 0)
        {
            a = b;
            b = r;
            s1 = s2;
            s2 = s3;
            t1 = t2;
            t2 = t3;
        }
    }
    return (s2 + p) % p;
}




void add_two_point(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2){

uint32_t slope=0;
if(x1==0 && y1==0){
sum_result[0]=x2;
sum_result[1]=y2;
return;
}

if(x2==0 && y2==0){
sum_result[0]=x1;
sum_result[1]=y1;
return;
}
if((x1==x2) && (y1==find_additive_inverse(y2))){
sum_result[0]=0;
sum_result[1]=0;
return;
}
else if((x1!=x2) || (y1!=y2)){
uint32_t temp1=(y2 + find_additive_inverse(y1)) % p;
uint32_t temp2=(x2 + find_additive_inverse(x1)) % p;
slope=(temp1*multiplicative_inverse(temp2, p)) % p;

}
else{
uint32_t temp1=((3*x1*x1)%p + 23) % p;
uint32_t temp2=multiplicative_inverse((2*y1)%p, p) % p;
slope=(temp1*temp2) % p;
}
uint32_t t1_x=(slope*slope) % p;
uint32_t t2_x=find_additive_inverse((x1 + x2) % p);
sum_result[0]=(t1_x + t2_x) % p;

uint32_t t1_y=(slope*((sum_result[0] + (find_additive_inverse(x1) % p) ) % p)) % p;
sum_result[1]=(y1 + t1_y) % p;
sum_result[1]=find_additive_inverse(sum_result[1]) % p;
 

}


void multiply_point_by_number(int p[2], int n){

sum_result[0]=p[0];
sum_result[1]=p[1];


for(int i=1;i<n;i++){

add_two_point(sum_result[0],sum_result[1],p[0],p[1]);

}


}

uint32_t ROTR_x_by_n(uint32_t x, int n){
return ((x>>n) | (x<<(32-n)));
}

uint32_t SHR_x_by_n(uint32_t x, int n){
return (x>>n);
}

uint32_t CH_x_y_z(uint32_t x, uint32_t y, uint32_t z){
return ((x&y)^((~x)&z));
}

uint32_t MAJ_x_y_z(uint32_t x, uint32_t y, uint32_t z){
return ((x&y)^(x&z)^(y&z));
}

uint32_t summation_0(uint32_t x){
return (ROTR_x_by_n(x,2)^ROTR_x_by_n(x,13)^ROTR_x_by_n(x,22));
}

uint32_t summation_1(uint32_t x){
return (ROTR_x_by_n(x,6)^ROTR_x_by_n(x,11)^ROTR_x_by_n(x,25));
}

//First Small Sigma Function
uint32_t sigma_0(uint32_t x){
return (ROTR_x_by_n(x,7)^ROTR_x_by_n(x,18)^SHR_x_by_n(x,3));
}

//Second Small Sigma Function
uint32_t sigma_1(uint32_t x){
return (ROTR_x_by_n(x,17)^ROTR_x_by_n(x,19)^SHR_x_by_n(x,10));
}

uint64_t findLength(uint32_t temp){

uint64_t count=0;
while(temp>0){
count++;
temp=temp>>1;
}
return count;

}

//Padding Function
void padding_512(uint32_t temp, unsigned char res[64]){

uint64_t length=findLength(temp);


int d=(447 - length) % 512;

int bit_512[512];

int i=511;
for(i=511;i>=448;i--){
bit_512[i]=length&1;
length=length>>1;
}

for(int j=0;j<d;j++){
bit_512[i]=0;
i--;
}

bit_512[i]=1;
i--;

for(;i>=0;i--){
bit_512[i]=temp&1;
temp=temp>>1;
}

int q=0;
for(int k=0;k<512;k++){
q=k/8;
res[q]=(res[q]<<1)|bit_512[k];
}

}


//Implementing SHA for 512 bit.
void SHA_512bit(unsigned char input[64]){



uint32_t words[64];

int j=0;
for(int i=0;i<16;i++){
words[i]=(input[j]<<24) | (input[j+1]<<16) | (input[j+2]<<8) | (input[j+3]);
j=j+4;
}

for(int i=16;i<64;i++){
words[i]=sigma_1(words[i-2]) + words[i-7] + sigma_0(words[i-15]) + words[i-16];
}


uint32_t a,b,c,d,e,f,g,h,t1,t2;

a=result[0];
b=result[1];
c=result[2];
d=result[3];
e=result[4];
f=result[5];
g=result[6];
h=result[7];

for(int i=0;i<64;i++){

t1=h+summation_1(e)+CH_x_y_z(e,f,g)+k[i]+words[i];
t2=summation_0(a)+MAJ_x_y_z(a,b,c);

h=g;
g=f;
f=e;
e=d+t1;
d=c;
c=b;
b=a;
a=t1+t2;
}


result[0]+=a;
result[1]+=b;
result[2]+=c;
result[3]+=d;
result[4]+=e;
result[5]+=f;
result[6]+=g;
result[7]+=h;

}

void SHA_start(uint32_t temp, unsigned char res[32]){

//result={0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19};

result[0]=0x6a09e667;
result[1]=0xbb67ae85;
result[2]=0x3c6ef372;
result[3]=0xa54ff53a;
result[4]=0x510e527f;
result[5]=0x9b05688c;
result[6]=0x1f83d9ab;
result[7]=0x5be0cd19;

unsigned char input[64];

padding_512(temp,input);
SHA_512bit(input);

int k=0;
for(int i=0;i<8;i++){

res[k]=result[i]>>24;
res[k+1]=(result[i]>>16) & 0xff;
res[k+2]=(result[i]>>8) & 0xff;
res[k+3]=(result[i]) & 0xff;

k=k+4;

}



}



int main(){



find_x_y();

printf("Point on Elliptic curve EL alpha: (%d,%d)\n",point[0],point[1]);


printf("Enter Alice’s private key in [1,150] : ");
int alice_private;
scanf("%d",&alice_private);



printf("Enter Alice’s private key in [1,150] : ");
int bob_private;
scanf("%d",&bob_private);

printf("\n");


//Calculating Alice's public key
int alice_public[2];
multiply_point_by_number(point,alice_private);
alice_public[0]=sum_result[0];
alice_public[1]=sum_result[1];

//Calculating Bob's public key
int bob_public[2];
multiply_point_by_number(point,bob_private);
bob_public[0]=sum_result[0];
bob_public[1]=sum_result[1];

//Calculating Shared secret key of Alice
int alice_shared[2];
multiply_point_by_number(bob_public,alice_private);
alice_shared[0]=sum_result[0];
alice_shared[1]=sum_result[1];

//Calculating Shared secret key of Bob
int bob_shared[2];
multiply_point_by_number(alice_public,bob_private);
bob_shared[0]=sum_result[0];
bob_shared[1]=sum_result[1];



printf("Alice's private key : %d\n",alice_private);
printf("Bob's private key : %d\n\n",bob_private);


printf("Alice's Shared Secret key : (%d,%d)\n",alice_shared[0],alice_shared[1]);
printf("Bob's Shared Secret key : (%d,%d)\n\n",bob_shared[0],bob_shared[1]);


int alice_final_key=alice_shared[0], bob_final_key=bob_shared[0];


int flag=findLength(alice_shared[1]);
alice_final_key = (alice_final_key << flag) | alice_shared[1];

flag=findLength(bob_shared[1]);
bob_final_key = (bob_final_key << flag) | bob_shared[1];



//SHA Part
unsigned char SHA_result_alice[32];
SHA_start(alice_final_key,SHA_result_alice);

unsigned char SHA_result_bob[32];
SHA_start(bob_final_key,SHA_result_bob);

printf("Alice's Secret key Ka : \n");

for(int i=0;i<32;i++){
printf("%hhx ",SHA_result_alice[i]);
}

printf("\n\nBob's Secret key Kb : \n");
for(int i=0;i<32;i++){
printf("%hhx ",SHA_result_bob[i]);
}



printf("\n\n*****************************************************************\n");
printf("Alice sending message to Bob\n");
printf("Enter message : ");
unsigned char plaintext[4][8];
for(int i=0;i<8;i++){
for(int j=0;j<4;j++){
scanf("%hhx",&plaintext[j][i]);
}
}
unsigned char plaintext1[4][8];
for(int i=0;i<4;i++){
for(int j=0;j<8;j++){
plaintext1[i][j] = plaintext[i][j];
}
}



printf("\n\n");

// unsigned char roundKeys[15][16];
keySchedulingAES(SHA_result_alice);
// keySchedulingAlgorithm(SHA_result_alice, roundKeys);

 unsigned char aes_result[4][8];
CBC_Enc(plaintext1);

for(int i=0;i<4;i++){
    for(int j=0;j<8;j++){
        aes_result[i][j] = plaintext1[i][j];
    }
}



unsigned char temp1_key_alice[32];
unsigned char temp2_key_alice[32];
for(int i=0;i<32;i++){
temp1_key_alice[i]=SHA_result_alice[i];
temp2_key_alice[i]=SHA_result_alice[i];
}

temp1_key_alice[31]=temp1_key_alice[31]^1;
temp2_key_alice[31]=temp2_key_alice[31]^2;

int q=0;
for(int i=0;i<8;i++){
for(int j=0;j<4;j++){
temp2_key_alice[q]=temp2_key_alice[q]^plaintext[j][i];
}
}

unsigned char padd1[64]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

for(int i=0;i<32;i++){
padd1[i]=temp2_key_alice[i];
}
padd1[32]=padd1[32]^0x80;

padd1[62]=padd1[62]^ 1;


unsigned char temp1_result_alice[32];


result[0]=0x6a09e667;
result[1]=0xbb67ae85;
result[2]=0x3c6ef372;
result[3]=0xa54ff53a;
result[4]=0x510e527f;
result[5]=0x9b05688c;
result[6]=0x1f83d9ab;
result[7]=0x5be0cd19;

SHA_512bit(padd1);

int z=0;
for(int i=0;i<8;i++){

temp1_result_alice[z]=result[i]>>24;
temp1_result_alice[z+1]=(result[i]>>16) & 0xff;
temp1_result_alice[z+2]=(result[i]>>8) & 0xff;
temp1_result_alice[z+3]=(result[i]) & 0xff;

z=z+4;

}

unsigned char t_result[64];

for(int i=0;i<32;i++){
t_result[i]=temp1_key_alice[i];
}


for(int i=0;i<32;i++){
t_result[i+32]=padd1[i];
}


unsigned char MAC_alice[32];

result[0]=0x6a09e667;
result[1]=0xbb67ae85;
result[2]=0x3c6ef372;
result[3]=0xa54ff53a;
result[4]=0x510e527f;
result[5]=0x9b05688c;
result[6]=0x1f83d9ab;
result[7]=0x5be0cd19;

SHA_512bit(t_result);

int k=0;
for(int i=0;i<8;i++){

MAC_alice[k]=result[i]>>24;
MAC_alice[k+1]=(result[i]>>16) & 0xff;
MAC_alice[k+2]=(result[i]>>8) & 0xff;
MAC_alice[k+3]=(result[i]) & 0xff;

k=k+4;

}

printf("Alice Encrypting message\n");
printf("Ciphertext : ");
for(int i=0;i<8;i++){
for(int j=0;j<4;j++){
printf("%hhx ",aes_result[j][i]);
}
}
printf("\n");
printf("MAC (Alice) : ");
for(int i=0;i<32;i++){
printf("%hhx ",MAC_alice[i]);
}




//////////////////////////////////
unsigned char roundKeys_bob[15][16];
keySchedulingAES(SHA_result_bob);


unsigned char dec_aes_result[4][8];
CBC_Dec(aes_result);

for(int i=0;i<4;i++){
    for(int j=0;j<8;j++){
        dec_aes_result[i][j] = aes_result[i][j];
    }
}

unsigned char temp1_key_bob[32];
unsigned char temp2_key_bob[32];
for(int i=0;i<32;i++){
temp1_key_bob[i]=SHA_result_bob[i];
temp2_key_bob[i]=SHA_result_bob[i];
}

temp1_key_bob[31]=temp1_key_bob[31]^1;
temp2_key_bob[31]=temp2_key_bob[31]^2;

q=0;
for(int i=0;i<8;i++){
for(int j=0;j<4;j++){
temp2_key_bob[q]=temp2_key_bob[q]^dec_aes_result[j][i];
}
}

unsigned char padd1_bob[64]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

for(int i=0;i<32;i++){
padd1_bob[i]=temp2_key_bob[i];
}
padd1_bob[32]=padd1_bob[32]^0x80;

padd1_bob[62]=padd1_bob[62]^ 1;


unsigned char temp1_result_bob[32];


result[0]=0x6a09e667;
result[1]=0xbb67ae85;
result[2]=0x3c6ef372;
result[3]=0xa54ff53a;
result[4]=0x510e527f;
result[5]=0x9b05688c;
result[6]=0x1f83d9ab;
result[7]=0x5be0cd19;

SHA_512bit(padd1_bob);

z=0;
for(int i=0;i<8;i++){

temp1_result_bob[z]=result[i]>>24;
temp1_result_bob[z+1]=(result[i]>>16) & 0xff;
temp1_result_bob[z+2]=(result[i]>>8) & 0xff;
temp1_result_bob[z+3]=(result[i]) & 0xff;

z=z+4;

}

unsigned char t_result_bob[64];

for(int i=0;i<32;i++){
t_result_bob[i]=temp1_key_bob[i];
}


for(int i=0;i<32;i++){
t_result_bob[i+32]=padd1_bob[i];
}


unsigned char MAC_bob[32];

result[0]=0x6a09e667;
result[1]=0xbb67ae85;
result[2]=0x3c6ef372;
result[3]=0xa54ff53a;
result[4]=0x510e527f;
result[5]=0x9b05688c;
result[6]=0x1f83d9ab;
result[7]=0x5be0cd19;

SHA_512bit(t_result_bob);

z=0;
for(int i=0;i<8;i++){

MAC_bob[z]=result[i]>>24;
MAC_bob[z+1]=(result[i]>>16) & 0xff;
MAC_bob[z+2]=(result[i]>>8) & 0xff;
MAC_bob[z+3]=(result[i]) & 0xff;

z=z+4;

}

printf("\n\n");
printf("Bob Decrypting message : \n");
printf("Plaintext : ");
for(int i=0;i<8;i++){
for(int j=0;j<4;j++){
printf("%hhx ",dec_aes_result[j][i]);
}
}
printf("\n");
printf("MAC (Bob) : ");
for(int i=0;i<32;i++){
printf("%hhx ",MAC_bob[i]);
}


printf("\n\n");


return 0;



}
