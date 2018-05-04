//Triple DES
#include<iostream>
#include<stdlib.h>
using namespace std;
int message[64],keys1[64],keys2[64],keys3[64];

int key_shift_number[] = {-1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};


int lftshift[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int sampledelete[] = {
                         57, 49, 41, 33, 25, 17,
                         1, 58, 50, 42, 34, 26,
                         10, 2, 59, 51, 43, 35,
                         19, 11, 3, 60, 52, 44,
                         63, 55, 47, 39, 31, 23,
                         7, 62, 54, 46, 38, 30,
                         14, 6, 61, 53, 45, 37,
                         21, 13, 5, 28, 20, 12};



int key_permutation[] = {
                         57, 49, 41, 33, 25, 17, 9,
                         1, 58, 50, 42, 34, 26, 18,
                         10, 2, 59, 51, 43, 35, 27,
                         19, 11, 3, 60, 52, 44, 36,
                         63, 55, 47, 39, 31, 23, 15,
                         7, 62, 54, 46, 38, 30, 22,
                         14, 6, 61, 53, 45, 37, 29,
                         21, 13, 5, 28, 20, 12, 4 };

int message_permutation[] = {
                             58, 50, 42, 34, 26, 18, 10, 2,
                             60, 52, 44, 36, 28, 20, 12, 4,
                             62, 54, 46, 38, 30, 22, 14, 6,
                             64, 56, 48, 40, 32, 24, 16, 8,
                             57, 49, 41, 33, 25, 17,  9, 1,
                             59, 51, 43, 35, 27, 19, 11, 3,
                             61, 53, 45, 37, 29, 21, 13, 5,
                             63, 55, 47, 39, 31, 23, 15, 7 };

int sub_key_permutation[] = {
                             14, 17, 11, 24, 1, 5,
                             3, 28, 15, 6, 21, 10,
                             23, 19, 12,  4, 26, 8,
                             16, 7, 27, 20, 13, 2,
                             41, 52, 31, 37, 47, 55,
                             30, 40, 51, 45, 33, 48,
                             44, 49, 39, 56, 34, 53,
                             46, 42, 50, 36, 29, 32 };

int expbox[] =  {
                  32, 1, 2, 3, 4, 5,
                  4, 5, 6, 7, 8, 9,
                  8, 9, 10, 11, 12, 13,
                  12, 13, 14, 15, 16, 17,
                  16, 17, 18, 19, 20, 21,
                  20, 21, 22, 23, 24, 25,
                  24, 25, 26, 27, 28, 29,
                  28, 29, 30, 31, 32, 1 };

int s[8][64] =       {
                      {
                          14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                          0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                          4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                          15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
                      {
                      15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                      3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                      0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                      13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },
                      {
                      10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                      13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                      13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                      1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
                      {
                      7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
                      13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
                      10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
                      3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14 },
                      {
                      2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
                      14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
                      4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
                      11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3 },
                      {
                      12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
                      10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
                      9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
                      4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13 },
                      {
                      4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
                      13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
                      1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
                      6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12 },
                      {
                      13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
                      1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
                      7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
                      2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11 }
                  };

int intermediate_permutation[] = {
                                  16,  7, 20, 21,
                                  29, 12, 28, 17,
                                  1, 15, 23, 26,
                                  5, 18, 31, 10,
                                  2,  8, 24, 14,
                                  32, 27,  3,  9,
                                  19, 13, 30,  6,
                                  22, 11,  4, 25 };

int end_permutation[] = {
                         40,  8, 48, 16, 56, 24, 64, 32,
                         39,  7, 47, 15, 55, 23, 63, 31,
                         38,  6, 46, 14, 54, 22, 62, 30,
                         37,  5, 45, 13, 53, 21, 61, 29,
                         36,  4, 44, 12, 52, 20, 60, 28,
                         35,  3, 43, 11, 51, 19, 59, 27,
                         34,  2, 42, 10, 50, 18, 58, 26,
                         33,  1, 41,  9, 49, 17, 57, 25 };

void initialpermutation(int *msg)
{
    int mcp[64],i;
    for(i=0;i<64;i++)
    {
        mcp[i] = msg[message_permutation[i]-1];
    }
    for(i=0;i<64;i++)
    {
        msg[i] = mcp[i];
    }
}



void endpermutation(int *msg)
{
    int mcp[64],i;
    for(i=0;i<64;i++)
    {
        mcp[i] = msg[end_permutation[i]-1];
    }
    for(i=0;i<64;i++)
    {
        msg[i] = mcp[i];
    }
}



void singleround(int *msg, int *key)
{

    int i,j,left[32],right[32],exp[48],cons[32],offset,numb,col;
    for(i=0;i<32;i++)
    {
        cons[i]=msg[32+i];
    }
    for(i=0;i<32;i++)
    {
        left[i] = msg[i];
    }
    for(j=0;j<48;j++)
    {
        exp[j] = msg[31 + expbox[j]];
    }
    for(i=0;i<48;i++)
    {
        if(exp[i] == key[i])
            exp[i] = 0;
        else
            exp[i] = 1;
    }

    for(i=0;i<8;i++)
    {
        col = 2*exp[0+(i*6)]+exp[5+(i*6)];
        offset = col*16;
        offset += ((8*exp[1+(i*6)])+(4*exp[2+(i*6)])+(2*exp[3+(i*6)])+(1*exp[4+(i*6)]));
        numb = s[i][offset];
        right[(i*4)+0] = numb>7?1:0;
        right[(i*4)+1] = (numb==4||numb==5||numb==6||numb==7||numb==12||numb==13||numb==14||numb==15)?1:0;
        right[(i*4)+2] = (numb==2||numb==3||numb==6||numb==7||numb==10||numb==11||numb==14||numb==15)?1:0;
        right[(i*4)+3] = (numb==1||numb==3||numb==5||numb==7||numb==9||numb==11||numb==13||numb==15)?1:0;
    }

    int intperm[32];
    for(i=0;i<32;i++)
    {
        intperm[i] = right[intermediate_permutation[i]-1];
    }


    for(i=0;i<32;i++)
    {
        if(left[i]==intperm[i])
        {
            right[i] = 0;
        }
        else
        {
            right[i] = 1;
        }
    }
    for(i=0;i<32;i++)
    {
        msg[i]=cons[i];
        msg[i+32]=right[i];

    }

}


void keyperm(int *key,int *newkey)
{
    int i;
    for(i=0;i<56;i++)
    {
        newkey[i] = key[key_permutation[i]];
    }

}


void keyperm2(int *key,int *newkey2)
{
    int i;
    for(i=0;i<48;i++)
    {
        newkey2[i] = key[sub_key_permutation[i]];
    }

}

void keyshift(int *key,int shiftno)
{
    int i,j,a[56];
    for(i=0;i<shiftno;i++)
    {
        for(j=1;j<28;j++)
        {
            a[j-1]=key[j];
        }
        a[j-1]=key[0];
        for(j=29;j<56;j++)
        {
            a[j-1]=key[j];
        }
        a[55]=key[28];
        for(i=0;i<56;i++)
        {
            key[i]=a[i];
        }
    }

}

void swaphalves(int *message)
{
    int i;
    int l[32],r[32];
    for(i=0;i<32;i++)
    {
        l[i]=message[i];
        r[i]=message[32+i];
    }
    for(i=0;i<32;i++)
    {
        message[i]=r[i];
        message[32+i]=l[i];
    }
}

int main()
{
    int i,q,j;
    int msgcpy[64],keycpy1[64],keycpy2[64],keycpy3[64],newkey1[56],newkeye1[48],newkeyes1[16][48],newkey2[56],newkeye2[48],newkeyes2[16][48],newkey3[56],newkeye3[48],newkeyes3[16][48],msg[64];
    cout<<"Enter the 64 bit message \n";
    for(i=0;i<64;i++)
    {
        cin>>message[i];
        msgcpy[i] = message[i];
    }

     cout<<"Enter the 64 bit key k1\n";
     for(i=0;i<64;i++)
    {
        cin>>keys1[i];
        keycpy1[i]=keys1[i];
    }


    cout<<"Enter the 64 bit key k2\n";
     for(i=0;i<64;i++)
    {
        cin>>keys2[i];
        keycpy2[i]=keys2[i];

    }

    cout<<"Enter the 64 bit key k3\n";
     for(i=0;i<64;i++)
    {
        cin>>keys3[i];
        keycpy3[i]=keys3[i];

    }


    cout<<"\n\n\n\nOriginal Message \n";
    for(i=0;i<64;i++)
        cout<<message[i];
    cout<<endl<<endl<<"\n\n\n\n";



    cout<<"Encryption process 1\n";
    initialpermutation(message);
    keyperm(keycpy1,newkey1);
    keyperm(keycpy2,newkey2);
    keyperm(keycpy3,newkey3);
    for(i=0;i<16;i++)
    {
        keyshift(newkey1,key_shift_number[i]);
        keyperm2(newkey1,newkeye1);
        keyshift(newkey2,key_shift_number[i]);
        keyperm2(newkey2,newkeye2);
        keyshift(newkey3,key_shift_number[i]);
        keyperm2(newkey3,newkeye3);
        for(q=0;q<48;q++)
        {
            newkeyes1[i][q]=newkeye1[q];
            newkeyes2[i][q]=newkeye2[q];
            newkeyes3[i][q]=newkeye3[q];
        }
        singleround(message,newkeyes1[i]);
        for(j=0;j<64;j++)
            cout<<message[j];
        cout<<endl;


    }
    swaphalves(message);
    for(j=0;j<64;j++)
            cout<<message[j];
        cout<<endl;
    cout<<endl<<endl<<endl;


    swaphalves(message);
    //Decryption
    cout<<endl;
    cout<<"Decryption Process 2\n";
    swaphalves(message);
    for(j=0;j<64;j++)
        cout<<message[j];
    cout<<endl;
    for(i=0;i<16;i++)
    {


        singleround(message,newkeyes2[15-i]);
        swaphalves(message);
        for(j=0;j<64;j++)
            cout<<message[j];
        cout<<endl;
        swaphalves(message);


    }
    swaphalves(message);
    endpermutation(message);




    cout<<"Encryption process 3\n";

    initialpermutation(message);
    for(i=0;i<16;i++)
    {
        singleround(message,newkeyes3[i]);
        for(j=0;j<64;j++)
            cout<<message[j];
        cout<<endl;


    }
    swaphalves(message);
    for(j=0;j<64;j++)
            cout<<message[j];
        cout<<endl;
    cout<<endl<<endl<<endl;


    swaphalves(message);
    //Decryption
    cout<<endl;
    cout<<"Decryption Process 3\n";
    swaphalves(message);
    for(j=0;j<64;j++)
        cout<<message[j];
    cout<<endl;
    for(i=0;i<16;i++)
    {


        singleround(message,newkeyes3[15-i]);
        swaphalves(message);
        for(j=0;j<64;j++)
            cout<<message[j];
        cout<<endl;
        swaphalves(message);


    }
    swaphalves(message);
    endpermutation(message);


   cout<<"Encryption process 2\n";

    initialpermutation(message);
    for(i=0;i<16;i++)
    {
        singleround(message,newkeyes2[i]);
        for(j=0;j<64;j++)
            cout<<message[j];
        cout<<endl;


    }
    swaphalves(message);
    for(j=0;j<64;j++)
            cout<<message[j];
        cout<<endl;
    cout<<endl<<endl<<endl;




    swaphalves(message);
    //Decryption
    cout<<endl;
    cout<<"Decryption Process 1\n";
    swaphalves(message);
    for(j=0;j<64;j++)
        cout<<message[j];
    cout<<endl;
    for(i=0;i<16;i++)
    {


        singleround(message,newkeyes1[15-i]);
        swaphalves(message);
        for(j=0;j<64;j++)
            cout<<message[j];
        cout<<endl;
        swaphalves(message);


    }
    swaphalves(message);
    endpermutation(message);
    cout<<"Final Message at receiver's end \n";
    for(j=0;j<64;j++)
            cout<<message[j];
        cout<<endl;







    return 0;

}

