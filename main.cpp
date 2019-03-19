//
//  main.cpp
//  Assignment1
//
//  Created by Yashwee Kothari on 2/7/19.
//  Copyright © 2019 Yashwee Kothari. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

bool isCapital(string word){
    bool isUppercase = true;
    for(int i =0; i<word.length(); i++){
        if(!isupper(word[i])){
            isUppercase= false;
        }
    
    }
    
    
    return isUppercase;
}

int main(int argc, const char * argv[]) {
    
    string output;
    
   
    if(argc != 3) {
      cerr << "TWO FILENAMES REQUIRED" <<endl;
      return -1;
   }
   
    ifstream inFile;
    ifstream SecFile;
    inFile.open(argv[1]);
    SecFile.open(argv[2]);
    
    if( inFile.is_open() == false  ) {
        cerr << "BAD FILENAME " << argv[1] << endl;
        return -1;
    }
    
    if( SecFile.is_open() == false  ) {
        cerr << "BAD FILENAME " << argv[2] << endl;
        return -1;
    }
    
    
    //creating map
    map<string,string> mySubMap;
    
    string key, value;
    string line2;
   
   //filling map with key and value pairs
    
    
    while(getline(inFile, line2)){
        if(line2.length() ==0){
        
           continue;
       }
       
       bool isValue = false; 
       bool thirdEntry = false; 
       int firstV =0; 
       string inSentPunct = "";
       bool inWord = false;
       
        
        for(int i =0; i < line2.length(); i++){
           
            if(!isspace(line2[i]) && isValue == false){
               if(isalpha(line2[i])) {
                inWord = true;
                key += inSentPunct;
                key += tolower(line2[i]);
                inSentPunct.clear();
               }
               
                else if(ispunct(line2[i]) && inWord){
                   inSentPunct += line2[i];
                }
                
                  
            }
            
            
            if(isspace(line2[i]) && firstV ==0){
                isValue = true;
                inSentPunct.clear();
                inWord = false;
                continue;
                    
            }
              if(isspace(line2[i]) && firstV !=0) {
                 thirdEntry = true;
                 isValue= false;
                } 
            
            
          
            if(isValue ==true){
                if(isalpha(line2[i])) {
                value += inSentPunct;
                value+=tolower(line2[i]);
                inWord = true;
            
                  inSentPunct.clear();
                   firstV=1;
                }
                
                else if(ispunct(line2[i]) && inWord){
                  inSentPunct += line2[i];
                } 
                
                //to check if there is 3 arguments in the sub line
                
            }
          
        }
       
               
        
     if(thirdEntry==false){
         if (mySubMap.count(key) > 0){ //idk if this does anything to update exisitng words
             mySubMap[key] = value;
         }
         else{
        mySubMap[key] = value;
         }
     }
        key.clear();
        value.clear();
      
    }
    
    
        
    inFile.close(); //close sub file
 
    
    string word = "";
    string line;
    int counter = 0;
   
   
    
   while(getline(SecFile, line)){ 
     
       string punctStore="";
      // bool inWord=false;
       //cout<< line <<endl;
         
       if(line.length() ==0){
           cout<< "\n";
           continue;
       }
       
       for(int i = 0; i< line.length(); i++){
           if(!isspace(line[i])){
               
               if(ispunct(line[i])){
                   ++i; //looking to character after
                   if(ispunct(line[i]) || isspace(line[i])){
                       --i;
                       punctStore += line[i];
                      //going back to orignal character
                   }
                    else{
                        --i;
                        word += line[i];
                    
                    }
                 
               }
               
               else{
           
               word += line[i];
                   
               }
           }
              
           
           if(isspace(line[i])){
               string lowerWord = word;
               for(int w= 0; w<word.length(); w++){  //converting word to lowercase to check 
                   lowerWord[w]= tolower(word[w]);
               }
   
               if(mySubMap.count(lowerWord)){
                             counter++;
                   
                  
                   //Capitilizing letters to match original WORD
                  
                   string newWord = mySubMap[lowerWord];
                  
                  // string printWord ="";
                   if(isupper(word[0])){
                       newWord[0] = toupper(newWord[0]);
                   
                   }
                   
                   
                   
                   
              
                   cout<<newWord;
                   
                   //new stuff ends
                   
                  cout<<punctStore;
                  punctStore.clear();
                
                  
               
               } //end of if
               
               
               else{
               cout<< word;
               cout<<punctStore; 
               punctStore.clear();
                   
               }
               
              cout<< ' ';
               
             word.clear();
             punctStore.clear();
             
           } //end of if 
       
            
              }
       
       
       //PRINTING LAST WORD OF EVERY LINE
       
            string lowerWord = word;
            for(int w= 0; w<word.length(); w++){  //converting word to lowercase to check 
            lowerWord[w]= tolower(word[w]);
              }
  
        if(mySubMap.count(lowerWord)){
           
            //Capitilizing letters to match original WORD
                  
                   string newWord = mySubMap[lowerWord];
                   if(isupper(word[0])){
                       newWord[0] = toupper(newWord[0]);
                   
                   }
            
                 
                   cout<<newWord;
                   
                  
            
            cout<<punctStore;
       
                counter++;
               
               } 
               
               
               else{
               cout<< word;
               cout<<punctStore;   
               } 
        
              
              word.clear();
       
              cout<< endl;
              
                
              }// end of while loop
          
      SecFile.close();  // closing other file 
    
    
          if(counter>0 && mySubMap.size() >1 ){ //why is badsubs mapsize 1 and counter is 45;
                
           cout<<"NUMBER OF CHANGES: " << counter<<endl;
                
            } 
             
  
              return 0;
              }

