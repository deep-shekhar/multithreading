#include<iostream>
#include<fstream>
#include<pthread.h>
#include<string>
#include<sstream>
using namespace std;

int num_threads = 20;
pthread_mutex_t my_mutex;

int a=0,e=0,ii=0,o=0,u=0;

void* vow_count(void* temp){
   ifstream infile;
   string *temp_ss = (string *)temp;
   string temp_s = *temp_ss;
   //delete temp_ss;
   pthread_mutex_lock(&my_mutex);
   cout <<"got file "<<(*temp_ss)<<endl;
   cout <<"processing file " <<(temp_s)<<endl;
   infile.open((temp_s.c_str()));   

   if(!infile){
     cout <<"file "<<temp_s<<" not opened"<<endl;
      pthread_exit(NULL);
   }	

   char vowel;
   while(infile >> noskipws >> vowel){
      switch(vowel){
         case 'a': a++;break; 
         case 'e': e++;break; 
	 case 'i': ii++;break; 
         case 'o': o++;break; 
         case 'u': u++;break; 
         case 'A': a++;break; 
         case 'E': e++;break; 
	 case 'I': ii++;break; 
         case 'O': o++;break; 
         case 'U': u++;break; 
      }
   }
  
   infile.close();
   pthread_mutex_unlock(&my_mutex); 
   pthread_exit(NULL); 
}

int main(int argc,char** argv){
  if(argc <=1 ){
     cout <<"give file names"<<endl;
     return -1;	    
  }
  num_threads = argc-1;
  pthread_t thread[num_threads];
  pthread_mutex_init(&my_mutex,0);
  string filename[argc];
  
  for(int i=1;i<argc;i++){
     filename[i] = argv[i];
     string *temp = &filename[i];
     cout <<(*temp)<<endl;
     if(pthread_create(&thread[i-1],NULL,vow_count,(void*)temp)){
        cout <<"error in creating thread no "<<i<<endl;
        return -1;
     }
  }	  

  for(int i=0;i<num_threads;i++){
     if(pthread_join(thread[i],NULL)){
        cout <<"unable to join threads"<<endl;
        return -1;  
     }
  }  
 
  pthread_mutex_destroy(&my_mutex);

  cout <<"A = "<<a<<endl;
  cout <<"E = "<<e<<endl;
  cout <<"I = "<<ii<<endl;
  cout <<"O = "<<o<<endl;
  cout <<"U = "<<u<<endl;

  return 0;
}
