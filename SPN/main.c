#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//this is the round key function it return the 16bit key
uint16_t round_key(uint32_t key , int round){
 int position = 4 * round - 3;
 uint32_t new_key = key;
 new_key = new_key << position - 1;
 new_key = new_key >> 16;
 uint16_t final_key = new_key;
 return final_key;
}
// this is the substitution function it substitut the 4 bit according to the given arrray
uint16_t substitution(uint16_t text){
 int sub_box[16] = {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7};
 uint16_t newciphertext = 0;
  
 for(int j=0;j<4;j++){
   newciphertext = newciphertext | sub_box[text%16] << 4*j;
   text = text/16;
  }
  return newciphertext;
}
// this is the reverse substitution function it substitut the 4 bit according to the given array (bijective array)
uint16_t rev_substitution(uint16_t text){
 int rev_sub_box[16] = {14,3,4,8,1,12,10,15,7,13,9,6,11,2,0,5};
 uint16_t newciphertext = 0;
  
 for(int j=0;j<4;j++){
   newciphertext = newciphertext | rev_sub_box[text%16] << 4*j;
   text = text/16;
  }
  return newciphertext;
}
// this is the permutaion function it permute the 16 bit(every bit)
uint16_t permutation(uint16_t text){
 int per_box[16] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};
 uint16_t newciphertext = 0;
  for(int j=0;j<=15;j++){
    int temp = (text >> (15-per_box[j]));
    temp = temp%2;
    newciphertext = newciphertext |  temp << (15-j);
  
  }
  return newciphertext;
}

// Encryption function call function according given image of encryption
uint16_t Encryption(uint16_t plaintext,uint32_t key){
 uint16_t ciphertext = plaintext;
 
 //For round 1
 printf("Round 1\n");
 uint16_t nKey = round_key(key,1);
 ciphertext = ciphertext ^ nKey;
 printf("Key : %04x\n",nKey);
 printf("Ciphertext u1 : %04x\n",ciphertext);
 ciphertext = substitution(ciphertext);
 printf("Ciphertext v1 : %04x\n",ciphertext);
 ciphertext = permutation(ciphertext);
 printf("Ciphertext w1 : %04x\n",ciphertext);
 
 //For round 2
 printf("Round 2\n");
 nKey = round_key(key,2);
 ciphertext = ciphertext ^ nKey;
 printf("Key : %04x\n",nKey);
 printf("Ciphertext u2 : %04x\n",ciphertext);
 ciphertext = substitution(ciphertext);
 printf("Ciphertext v2 : %04x\n",ciphertext);
 ciphertext = permutation(ciphertext);
 printf("Ciphertext w2 : %04x\n",ciphertext);
 
 //For round 3
 printf("Round 3\n");
 nKey = round_key(key,3);
 ciphertext = ciphertext ^ nKey;
 printf("Key : %04x\n",nKey);
 printf("Ciphertext u3 : %04x\n",ciphertext);
 ciphertext = substitution(ciphertext);
 printf("Ciphertext v3 : %04x\n",ciphertext);
 ciphertext = permutation(ciphertext);
 printf("Ciphertext w3 : %04x\n",ciphertext);
 
 //For round 4
 printf("Round 4\n");
 nKey = round_key(key,4);
 ciphertext = ciphertext ^ nKey;
 printf("Key : %04x\n",nKey);
 printf("Ciphertext u4 : %04x\n",ciphertext);
 ciphertext = substitution(ciphertext);
 printf("Ciphertext v4 : %04x\n",ciphertext);
 
 //For round 5
 printf("Round 5\n");
 nKey = round_key(key,5);
 ciphertext = ciphertext ^ nKey;
 printf("Key : %04x\n",nKey);
 printf("Ciphertext y : %04x\n",ciphertext);
 
 
 return ciphertext;
}
//Decryption 
uint16_t Decryption(uint16_t chiphertext, uint32_t key){
 
 uint16_t plaintext = chiphertext;
 //for round 1
 uint16_t nKey = round_key(key,5);
 plaintext = plaintext ^ nKey;
 printf("Round 1\n");
 printf("Key : %04x\n",nKey);
 printf("Plaintext : %04x\n",plaintext);
 
 //for round 2
 plaintext = rev_substitution(plaintext);
 nKey = round_key(key,4);
 plaintext = plaintext ^ nKey;
 printf("Round 2\n");
 printf("Key : %04x\n",nKey);
 printf("Plaintext : %04x\n",plaintext);
 
 //for round 3
 plaintext = permutation(plaintext);
 plaintext = rev_substitution(plaintext);
 nKey = round_key(key,3);
 plaintext = plaintext ^ nKey;
 printf("Round 3\n");
 printf("Key : %04x\n",nKey);
 printf("Plaintext : %04x\n",plaintext);
 
 //for round 4
 plaintext = permutation(plaintext);
 plaintext = rev_substitution(plaintext);
 nKey = round_key(key,2);
 plaintext = plaintext ^ nKey;
 printf("Round 4\n");
 printf("Key : %04x\n",nKey);
 printf("Plaintext : %04x\n",plaintext);
 
 //for round 4
 plaintext = permutation(plaintext);
 plaintext = rev_substitution(plaintext);
 nKey = round_key(key,1);
 plaintext = plaintext ^ nKey;
 printf("Round 5\n");
 printf("Key : %04x\n",nKey);
 printf("Plaintext : %04x\n",plaintext);

 printf("---------------------------------------------------------\n");
 return plaintext;
}

int main(){

 uint16_t plaintext,ciphertext;
 uint32_t key;
 
 printf("Enter the plaintext (hexa decimal 16 bit) : ");
 scanf("%hx", &plaintext);
 
 printf("Enter the secret key (hexa decimal 32 bit) : ");
 scanf("%x" , &key);
 
 printf("---------------------------------------------------------\n");
 printf("Encryption process : \n");
 //call Encryption function 
 ciphertext = Encryption(plaintext,key);
 printf("---------------------------------------------------------\n");
 printf("Final encryption : %04x\n",ciphertext);
 printf("---------------------------------------------------------\n");
 printf("Decryption process : \n");
 //call Decryption function
 printf("Final decryption : %04x\n",Decryption(ciphertext,key));
 printf("---------------------------------------------------------\n");
return 0;
}
