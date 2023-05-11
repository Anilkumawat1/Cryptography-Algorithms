//Roll no - 202051026
//Name - Anil kumawat

#include <stdio.h>
#include <stdint.h>
//round kay array we will storing 11 round key
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
    
 //mix column matrix
unsigned char M[4][4] = {
    {1,4,4,5},
    {5,1,4,4},
    {4,5,1,4},
    {4,4,5,1}
    };
    
  //mix column inverse matrix
unsigned char inverse_M[4][4] = {
    {165,7,26,115},
    {115,165,7,26},
    {26,115,165,7},
    {7,26,115,165},
    };
    
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

//10 constant value 32 bit array
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

int main(){
 unsigned char plaintext[4][8]={{0x32,0x43,0xf6,0xa8,0x32,0x43,0xf6,0xa8},{0x88,0x5a,0x30,0x8d,0x88,0x5a,0x30,0x8d},{0x31,0x31,0x98,0xa2,0x31,0x31,0x98,0xa2},{0xe0,0x37,0x07,0x34,0xe0,0x37,0x07,0x34}};

  unsigned char key[32]={0x1a, 0x2b, 0x3c, 0x4d, 0x1a, 0x2b, 0x3c, 0x4d, 0x1a, 0x2b, 0x3c, 0x4d,0x1a, 0x2b, 0x3c, 0x4d, 0x1a, 0x2b, 0x3c, 0x4d, 0x1a, 0x2b, 0x3c, 0x4d, 0x1a, 0x2b, 0x3c, 0x4d, 0x1a, 0x2b, 0x3c, 0x4d};

  //taking the input plaintext from ther user
  printf("Enter the plaintext of 256-bit : ");
  for(int i = 0;i<4;i++){
  for(int j=0;j<8;j++){
  scanf("%hhx",&plaintext[j][i]);
  }
  }
  printf("Plaintext of 256-bit : ");
  for(int i = 0;i<4;i++){
  for(int j=0;j<8;j++){
  printf("%hhx ",plaintext[j][i]);
  }
  }
  //printing the plaintext
//   printf("Plaintext : ");
//   print(plaintext);
 
  // taking the input key from ther user
  printf("\nEnter the key of 256-bit : ");
  for(int i = 0;i<32;i++){
 scanf("%hhx",&key[i]);
  }
  //printing the key
  printf("Key : ");
  printf("\n");
  for(int i = 0;i<32;i++){
  printf("%hhx ",key[i]);
  }
//   printf("\n**************************************************");
//   printf("\n");
  
  // calling keySchedulingAES for creating 11 round key
  keySchedulingAES(key);
  
 // printing the round 15 key
  printf("\nRound keys : \n");
  for(int i=0;i<15;i++){
  printf("Round key %d",i+1);
    printf("\n");
  for(int j=0;j<16;j++){
  printf("%hhx " , roundKey[i][j]);
  }
  printf("\n");
  }
   
   
   
    printf("**************************************************\n");
  printf("Encryption : \n");
  
  CBC_Enc(plaintext);
  for(int i = 0;i<8;i++){
  for(int j=0;j<4;j++){
  printf("%hhx ",plaintext[j][i]);
  }
  }
   printf("\n**************************************************\n");
  printf("Decryption : \n");
  CBC_Dec(plaintext);
   for(int i = 0;i<8;i++){
  for(int j=0;j<4;j++){
  printf("%hhx ",plaintext[j][i]);
  }
  }
//   //calling the  AES_encryption for encrypt plaintext
//   AES_encryption(plaintext);
//   printf("\n");
//     printf("**************************************************\n");
//   printf("Final Encryption :");
//   //printing the encrypted plaintext
//   print(plaintext);
  
//     printf("**************************************************\n");
//   printf("Decryption : \n");
 
//   //calling the  AES_decryption for decrypt plaintext
//   AES_decryption(plaintext);
//   //printing the decrypted plaintext
//   printf("**************************************************\n");
//   printf("Final Decryption : ");
//   print(plaintext);
//     printf("**************************************************\n");
 
  
 
   return 0;
}

