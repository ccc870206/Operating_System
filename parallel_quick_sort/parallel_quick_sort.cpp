#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <vector>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <cstring>
#include <fstream>
#include <algorithm> 



using namespace std;


pthread_t T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15; 
vector<int> t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15;
sem_t s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15;
sem_t ST,MT;
ofstream out1;


void SetArray(vector<int> list,vector<int>& arr1,vector<int>& arr2)
{
    //cout << "begin\n";
    int n = list.size();
    if ( n == 0) return;
    if ( n == 1) 
    {
        arr1.push_back(list[0]);
        return;
    }
    if ( n == 2) 
    {
        if(list[0]<list[1])
        {
            arr1.push_back(list[0]);
            arr2.push_back(list[1]);
        }
        else
        {
            arr1.push_back(list[0]);
            arr2.push_back(list[1]);
        }
        return;
    }

    int random = rand()%n;

    int pivot = list[random];

    for(int i = n-1;i >= 0;i--)
    {
        if(list[i]<pivot)
            arr1.push_back(list[i]);
        else
            arr2.push_back(list[i]);
    }
    //cout << "end\n";
}

void BubbleSort(vector<int>& arr)
{
    int n = arr.size();
    for(int i = 0;i < n;i++)
        for(int j = i;j < n;j++)
            if(arr[i]>arr[j])
                swap(arr[i],arr[j]);
}


void *MotherThread(void* data)
{


    SetArray(t1,t2,t3);
    
    sem_post(&s2);
    sem_post(&s3);

    sem_wait(&MT);
    sem_wait(&MT);
    sem_wait(&MT);
    sem_wait(&MT);
    sem_wait(&MT);
    sem_wait(&MT);
    sem_wait(&MT);
    sem_wait(&MT);
  
    int i;
 
    for(i = 0;i< t8.size();i++)
    out1 << t8[i] << " ";
    for(i = 0;i< t9.size();i++)
        out1 << t9[i] << " ";
    for(i = 0;i< t10.size();i++)
        out1 << t10[i] << " ";
    for(i = 0;i< t11.size();i++)
        out1 << t11[i] << " ";
    for(i = 0;i< t12.size();i++)
        out1 << t12[i] << " ";
    for(i = 0;i< t13.size();i++)
        out1 << t13[i] << " ";
    for(i = 0;i< t14.size();i++)
        out1 << t14[i] << " ";
    for(i = 0;i< t15.size();i++)
        out1 << t15[i] << " ";
    sem_post(&s1);
    pthread_exit(data);

}

void *TwoThread(void* data)
{
    sem_wait(&s2);
    
    SetArray(t2,t4,t5);

    sem_post(&s4);
    sem_post(&s5);
    
    pthread_exit(data);
}

void *ThreeThread(void* data)
{
    sem_wait(&s3);
    
    SetArray(t3,t6,t7);
   
    sem_post(&s6);
    sem_post(&s7);
    
    pthread_exit(data);
}


void *FourThread(void* data)
{
    sem_wait(&s4);
    
    SetArray(t4,t8,t9);

    sem_post(&s8);
    sem_post(&s9);
    
    pthread_exit(data);
}

void *FiveThread(void* data)
{
    sem_wait(&s5);

    SetArray(t5,t10,t11);
   
    sem_post(&s10);
    sem_post(&s11);
    
    pthread_exit(data);
}

void *SixThread(void* data)
{
    sem_wait(&s6);

    SetArray(t6,t12,t13);
  
    sem_post(&s12);
    sem_post(&s13);
  
    pthread_exit(data);
}

void *SevenThread(void* data)
{
    sem_wait(&s7);

    SetArray(t7,t14,t15);
   
    sem_post(&s14);
    sem_post(&s15);
   
    pthread_exit(data);
}

void *EightThread(void* data)
{
    sem_wait(&s8);
  
    BubbleSort(t8);
   
    sem_post(&MT);
    pthread_exit(data);
}

void *NineThread(void* data)
{
    sem_wait(&s9);
   
    BubbleSort(t9);
   
    sem_post(&MT);
    pthread_exit(data);
}

void *TenThread(void* data)
{
    sem_wait(&s10);
   
    BubbleSort(t10);
  
    sem_post(&MT);
    pthread_exit(data);
}

void *ElevenThread(void* data)
{
    sem_wait(&s11);
   
    BubbleSort(t11);
  
    sem_post(&MT);
    pthread_exit(data);
}

void *TwelveThread(void* data)
{
    sem_wait(&s12);
   
    BubbleSort(t12);
  
    sem_post(&MT);
    pthread_exit(data);
}

void *ThirteenThread(void* data)
{
    sem_wait(&s13);
  
    BubbleSort(t13);
   
    sem_post(&MT);
    pthread_exit(data);
}

void *FourteenThread(void* data)
{
    sem_wait(&s14);
    
    BubbleSort(t14);
  
    sem_post(&MT);
    pthread_exit(data);
}

void *FifteenThread(void* data)
{
    sem_wait(&s15);
  
    BubbleSort(t15);
  
    sem_post(&MT);
    pthread_exit(data);
}

void *SingleThread(void* data)
{
    ofstream out2;
    out2.open("output2.txt");
    t2.clear();
    t3.clear();
    t4.clear();
    t5.clear();
    t6.clear();
    t7.clear();
    t8.clear();
    t9.clear();
    t10.clear();
    t11.clear();
    t12.clear();
    t13.clear();
    t14.clear();
    t15.clear();
    SetArray(t1,t2,t3);
    SetArray(t2,t4,t5);
    SetArray(t3,t6,t7);
    SetArray(t4,t8,t9);
    SetArray(t5,t10,t11);
    SetArray(t6,t12,t13);
    SetArray(t7,t14,t15);
    BubbleSort(t8);
    BubbleSort(t9);
    BubbleSort(t10);
    BubbleSort(t11);
    BubbleSort(t12);
    BubbleSort(t13);
    BubbleSort(t14);
    BubbleSort(t15);
    int i;
    for(i = 0;i < t14.size();i++)
        t7[i] = t14[i];
    for(i;i < t7.size();i++)
        t7[i] = t15[i-t14.size()];
    
    for(i = 0;i < t12.size();i++)
        t6[i] = t12[i];
    for(i;i < t6.size();i++)
        t6[i] = t13[i-t12.size()];

    for(i = 0;i < t10.size();i++)
        t5[i] = t10[i];
    for(i;i < t5.size();i++)
        t5[i] = t11[i-t10.size()];

    for(i = 0;i < t8.size();i++)
        t4[i] = t8[i];
    for(i;i < t4.size();i++)
        t4[i] = t9[i-t8.size()];
    
    for(i = 0;i < t6.size();i++)
        t3[i] = t6[i];
    for(i;i < t3.size();i++)
        t3[i] = t7[i-t6.size()];

    for(i = 0;i < t4.size();i++)
        t2[i] = t4[i];
    for(i;i < t2.size();i++)
        t2[i] = t5[i-t4.size()];

    for(i = 0;i < t2.size();i++)
        t1[i] = t2[i];
    for(i;i < t1.size();i++)
        t1[i] = t3[i-t2.size()] ;
    for(i = 0;i < t1.size();i++)
        out2 << t1[i] << " ";


    sem_post(&ST);
    pthread_exit(data);
}




int main()

{   
    struct timeval start,end;
    char name[100];
    srand (time(NULL));

    ifstream in;
 

    cout << "Input the file name: ";
    
    cin >> name;

    in.open(name);
    out1.open("output1.txt");
    

    int get; 


    while(in >> get)
    {
        t1.push_back(get);
    }

    /////////////////MUTI THREAD///////////////////////////////////
    gettimeofday(&start,0);
    sem_init(&s1,0,0);
    sem_init(&s2,0,0);
    sem_init(&s3,0,0);
    sem_init(&s4,0,0);
    sem_init(&s5,0,0);
    sem_init(&s6,0,0);
    sem_init(&s7,0,0);
    sem_init(&s8,0,0);
    sem_init(&s9,0,0);
    sem_init(&s10,0,0);
    sem_init(&s11,0,0);
    sem_init(&s12,0,0);
    sem_init(&s13,0,0);
    sem_init(&s14,0,0);
    sem_init(&s15,0,0);

    sem_init(&MT,0,0);

    char* message;
    
    
    pthread_create(&T1,NULL,MotherThread,(void*) message);
    pthread_create(&T2,NULL,TwoThread,(void*) message);
    pthread_create(&T3,NULL,ThreeThread,(void*) message);
    pthread_create(&T4,NULL,FourThread,(void*) message);
    pthread_create(&T5,NULL,FiveThread,(void*) message);
    pthread_create(&T6,NULL,SixThread,(void*) message);
    pthread_create(&T7,NULL,SevenThread,(void*) message);
    pthread_create(&T8,NULL,EightThread,(void*) message);
    pthread_create(&T9,NULL,NineThread,(void*) message);
    pthread_create(&T10,NULL,TenThread,(void*) message);
    pthread_create(&T11,NULL,ElevenThread,(void*) message);
    pthread_create(&T12,NULL,TwelveThread,(void*) message);
    pthread_create(&T13,NULL,ThirteenThread,(void*) message);
    pthread_create(&T14,NULL,FourteenThread,(void*) message);
    pthread_create(&T15,NULL,FifteenThread,(void*) message);
    
    sem_wait(&s1);

    gettimeofday(&end,0);


	int sec = end.tv_sec - start.tv_sec;
    int usec = end.tv_usec - start.tv_usec;

   printf("Elapsed time of MT sorting: %f sec\n", sec+(usec/1000000.0));

    ///////////////SINGLE THREAD///////////////////////
    gettimeofday(&start,0);
    sem_init(&ST,0,0);
    pthread_create(&T1,NULL,SingleThread,(void*) message);
    sem_wait(&ST);
    gettimeofday(&end,0);
    
    sec = end.tv_sec - start.tv_sec;
    usec = end.tv_usec - start.tv_usec;
    
    printf("Elapsed time of ST sorting: %f sec\n", sec+(usec/1000000.0));

    return 0;
}