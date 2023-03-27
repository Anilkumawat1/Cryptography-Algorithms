#include <stdio.h>
#include <string.h>

void adjustPlaintext(char* plaintext, int length)
{
   char temp[100];
   int newLength = 0;
   for(int i=0;i<length;i++){
       
    //   two characters are same than we need to add 'x'
       if(i+1<length&&plaintext[i]==plaintext[i+1]){
          temp[newLength++] = plaintext[i];
          temp[newLength++] = 'x';
       }
       else{
           temp[newLength++] = plaintext[i];
       }
   }
//   checking that our new plaintext is odd length or even length if odd than add x
   if(newLength%2!=0)
   temp[newLength++] = 'x';
   
//   now copy the temp into the plaintext
   strncpy(plaintext,temp,newLength);
   
   plaintext[newLength] = '\0';
}


void generateKeyMatrix(char* key, char keyMatrix[5][5]) {
    
   int visited[26];
//   initilize the visited with 0 
   for(int i=0;i<26;i++){
       visited[i] = 0;
   }

   int i = 0;
   int j = 0;
   int len = strlen(key);
   for(int k=0;k<len;k++){
    //   checking that we visited already or not
       if(visited[key[k]-'a']==0){
           visited[key[k]-'a'] = 1;
           keyMatrix[i][j] = key[k];
           j++;
       }
       if(j>=5){
           i++;
           j=0;
       }
   }
   
//   this loop for remaining characters
   for(char k='a';k<='z';k++){
       if(k=='j')
       continue;
        //   checking that we visited already or not
       if(visited[k-'a']==0){
           visited[k-'a'] = 1;
           keyMatrix[i][j] = k;
           j++;
       }
       if(j>=5){
           i++;
           j=0;
       }
   }
   
//   printing the keyMatrix
  for(int i1=0;i1<5;i1++){
       for(int j1=0;j1<5;j1++){
           printf("%c ",keyMatrix[i1][j1]);
       }
       printf("\n");
   }
}


void removeJ(char *key){
    int len = strlen(key);
    for(int i=0;i<len;i++){
        if(key[i]=='j'){
            key[i] = 'i';
        }
    }
}


void search(int arr[4],char a,char b,char keyMatrix[5][5]){
    int i =0;
    int j = 0;
    // searching the a and b in the keyMatrix
    for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (keyMatrix[i][j] == a) {
				arr[0] = i;
				arr[1] = j;
			}
			else if (keyMatrix[i][j] == b) {
				arr[2] = i;
				arr[3] = j;
			}
		}
	}
}


int mod(int num){
    // if num = -3 than we need to add 5 than we can tak mod
    if(num<0)
     num = num+5;
     return num%5;
}


int GCD(int a, int b){
    // using GCD we check that a is invertible or not if GCD(a, 26) = 1 than it is invertible
    if(a==0)
    return b;
    return GCD(b%a,a);
}


int multiplicative_inverse(int a, int m){
    // GCD(x,m) = ax + bm with this equation 
    int m0 = m;
    int y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a>1) {
        int q = a / m;
        int t = m;
        m = a % m, 
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}


void encryptPlayfairCipher(char* plaintext,char* ciphertext,char keyMatrix[5][5]){
    int arr[4];
    int length = strlen(plaintext);
    for (int i=0;i<length;i+=2) {
        // searching the char in the keyMatrix
		search(arr,plaintext[i],plaintext[i+1],keyMatrix);
		
// 		if the letters appear on the same raw of your table then replace them with the letter to their
// immediate right respectively
		if (arr[0] == arr[2]) {
			ciphertext[i] = keyMatrix[arr[0]][(arr[1]+1)%5];
			ciphertext[i+1] = keyMatrix[arr[0]][(arr[3]+1)%5];
		}
// 		if the letters appear on the same column of your table then replace them with the letter to their
// immediate below respectively.
		else if (arr[1] == arr[3]) {
			ciphertext[i] = keyMatrix[(arr[0]+1)%5][arr[1]];
			ciphertext[i+1] = keyMatrix[(arr[2]+1)%5][arr[1]];
		}
// 		if the letters are not in the same row or column then replace them with the letters on the same
// row respectively but at the other pair or corners of the rectangle defined by the original pair. The
// order is important the firt letter of the encrypted pair is the one that lies on the same row as the
// first letter of the plaintext pair
		else {
		ciphertext[i] = keyMatrix[arr[0]][arr[3]];
			ciphertext[i+1] = keyMatrix[arr[2]][arr[1]];
		}
	}
    ciphertext[length] = '\0';
}


void encryptAffine(char* plaintext, int a, int b, char* ciphertext) {
    // checking that a is invertible or not
    if(GCD(a,26)==1){
        int length = strlen(plaintext);
        for(int i=0;i<length;i++){
            // Enc(x,k) = (ax+b)mod26 = ciphertext
            ciphertext[i] = ((plaintext[i]-'a')*a + b)%26+'a';
        }
    }
}


void decryptAffine(char* decryptMess, int a, int b, char* ciphertext) {
     // checking that a is invertible or not
    if(GCD(a,26)==1){
        int length = strlen(decryptMess);
        // (a a-1) = 1
        //so finding the a inverse using multiplicative_inverse function
        int inverse = multiplicative_inverse(a,26);
        for(int i=0;i<length;i++){
            // Dec(c,k) = ((c+26-b)(a−1))mod26
            decryptMess[i] = (((ciphertext[i]-'a')+26-b)*inverse)%26+'a';
        }
    }
}

void encryptShift(char* plaintext, int shift, char* ciphertext) {
    int length = strlen(plaintext);
    for(int i=0;i<length;i++){
        // shifting the letter by given shift value
        ciphertext[i] = (plaintext[i]-'a'+shift)%26 + 'a';
    }
}

void decryptShift(char* decryptMess, int shift, char* ciphertext) {
    int length = strlen(ciphertext);
    for(int i=0;i<length;i++){
        decryptMess[i] = (ciphertext[i]-'a'+26-shift)%26 + 'a';
    }
}

void decryptPlayfairCipher(char* decryptMess,char* ciphertext,char keyMatrix[5][5]){
    // same as encrypt 
    int arr[4];
    int length = strlen(ciphertext);
    for (int i=0;i<length;i+=2) {
         // searching the char in the keyMatrix
		search(arr,ciphertext[i],ciphertext[i+1],keyMatrix);
		
		// if the letters appear on the same raw of your table then replace them with the letter to their
// immediate right respectively
		if (arr[0] == arr[2]) {
			decryptMess[i] = keyMatrix[arr[0]][mod(arr[1]-1)];
			decryptMess[i+1] = keyMatrix[arr[0]][mod(arr[3]-1)];
		}
		
		// if the letters appear on the same column of your table then replace them with the letter to their
// immediate below respectively.
		else if (arr[1] == arr[3]) {
			decryptMess[i] = keyMatrix[mod(arr[0]-1)][arr[1]];
			decryptMess[i+1] = keyMatrix[mod(arr[2]-1)][arr[1]];
		}
// 		taking corners of the rectangle
		else {
		decryptMess[i] = keyMatrix[arr[0]][arr[3]];
		decryptMess[i+1] = keyMatrix[arr[2]][arr[1]];
		}
	}
}

int main()
{  
   char plaintext[100];
   char keyMatrix[5][5];
   char key[100];
   char ciphertext[100];
   char decryptMess[100];
   
//   taking the message
   printf("Enter the plain text(small letter) : ");
   scanf("%s",plaintext);
   
//   removing j and adjust the size of message and adding x if repetition of any characters 
   int length = strlen(plaintext);
   removeJ(plaintext);
   adjustPlaintext(plaintext,length);
   printf("After adjusting the plaintext : %s\n",plaintext);
   
//   taking the key of encryption
   printf("Enter the key : ");
   scanf("%s",key);
   removeJ(key);
   printf("After adjusting the key : %s\n",key);
   
//   generating the key matrix
   printf("5x5 key matrix : \n");
   generateKeyMatrix(key,keyMatrix);
   
   printf("\n");
   
//   now encrypt the plaintext using Playfair
   encryptPlayfairCipher(plaintext,ciphertext,keyMatrix);
   printf("Playfair ciper (after encryption) C1 : %s\n",ciphertext);
   
//   now encrypt the C1 cipher using Affine cipher
   encryptAffine(ciphertext,11,15,ciphertext);
   printf("Affine ciper (after encryption) C2 : %s\n",ciphertext);
   
//   now encrypt the C2 cipher using Shift cipher
   encryptShift(ciphertext,5,ciphertext);
   printf("Shift ciper (after encryption) C3 : %s\n",ciphertext);
   
   printf("\n");
   
//   now decrypt the C3 cipher using Shift cipher
   decryptShift(decryptMess,5,ciphertext);
   printf("Shift ciper (after decryption) p3 : %s\n",decryptMess);
   
//   now decrypt the P3 cipher using Affine cipher
   decryptAffine(decryptMess,11,15,decryptMess);
   printf("Affine ciper (after decryption) p2 : %s\n",decryptMess);
   
//   now decrypt the plaintext using Playfair
   decryptPlayfairCipher(decryptMess,decryptMess,keyMatrix);
   printf("Playfair ciper (after decryption) p1 : %s\n\n",decryptMess);
   
   printf("Final decrypted message : %s\n",decryptMess);
   return 0;
}

