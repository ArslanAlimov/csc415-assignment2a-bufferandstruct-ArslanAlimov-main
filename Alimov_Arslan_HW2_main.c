/**************************************************************
* Class:  CSC-415-02 Fall 2021
* Name: Arslan Alimov
* Student ID: 916612104
* GitHub UserID: ArslanAlimov
* Project: Assignment 2 – Stucture in Memory and Buffering
*
* File: Alimov_Arslan_HW2_main.c
*
* Description:
	This assignment our main function receives arguments 
	this arguments contain our First name Last name and 		
    some message. Then those arguments fill out our 	
    personal information after which we write it into our 		
    buffer till we get empty line
*
**************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assignment2.h"
int main(int counter,char* arguments[])
//function main takes properties of counter and arguments size of 3 stored in an array we have 3 arguments FirstName LastName Message
{
  
    int iterator=0;
    int myId= 916612104;
    //creating variables iteration value iterator++
     
	const char *nextString;
    //create an empty string 
	
    char *myBuffer= (char *)malloc(sizeof(char) * BLOCK_SIZE);
    //creating a buffer with a Block_Size from assignment2 header file
    
	personalInfo *aboutMe=(personalInfo*)malloc(sizeof(personalInfo));
    /*
    need to allocate memory for our object
    personal info=
    {
        firstName=""{string}
        lastName= ""{string}
        studentID=""{int}
        gradelevel {FRESHMAN, SOPHMORE, JUNIOR, SENIOR, GRAD, INSTRUCTOR} level,(enum=SENIOR)
        languages=, // See #defines for the bitmap values (from Headers)
        message[100], (Message from cmd line)
    });
    */
	
    if(aboutMe==NULL)
     {
         puts("Error memory Allocation|Personal Info");
         exit(1);
     }
     if(myBuffer==NULL)
     {
         puts("Error Memmory Allocation|Buffer");
         exit(1);
     }
        
	aboutMe->firstName=arguments[1];
        aboutMe->lastName=arguments[2];
        aboutMe->studentID=myId;
        aboutMe->level=SENIOR;
        /*
        RUNOPTIONS=$(FIRSTNAME) $(LASTNAME)             message
                     ^Arguments[1] ^ Arguments[2]        ^Arguments[3]
        Assigning values to our aboutMe (object of personal info) that we created in line 29
        we assign our firstname from our cmdline it will be first argument in our cmdline
        our last name would be in second cmdline argument
        I created an int variable so I would'nt need to type it each time in line 23
        level = Senior which is 3 enum (starting from 0)
        */
        
	aboutMe->languages =KNOWLEDGE_OF_MIPS_ASSEMBLER|KNOWLEDGE_OF_PHP|KNOWLEDGE_OF_C_SHARP|KNOWLEDGE_OF_JAVA|KNOWLEDGE_OF_JAVASCRIPT;
    //adding languages from header file they are stored in bit values
        
	strcpy(aboutMe->message,arguments[3]);
	
    //we copy our message that is stored in argument3 and fill it out into our data struct that is called aboutMe
	// ^for this part we can also use memcpy(aboutMe->message,arguments[3],100);  if it is something that teacher wants we give destination where we need to copy the message, second parameter is something that we want to copy
	// and the third parameter is how much memory we need to give it. where I give 100 because message has [100] 
	
        writePersonalInfo(aboutMe);
        // we call a function writePersonal info and pass our aboutMe information in order for it to fill it all out


        nextString=getNext();
        //store our get Next string into our nextString variable
        //printf("\nFIRST STRING: %s\n",nextString);
        // line above was used for debugging purpose

        while (nextString!=NULL)
        {

            //create while loop to check if there is any more strings from getNext() it will work till we hit NULL 

            for(int i = 0; nextString[i]!='\0'; i++)
            {
                /*creating for loop strings always end with \0 in C therewore we are using \0 
                    it checks our string length for character \0 at the end
                */
              
               myBuffer[iterator++]=nextString[i];
               //fillout our buffer with next string
                //printf("\nNEXT STRING :%s\n",nextString);
                //code above for debugging purpose

                if(iterator==BLOCK_SIZE)
                {
                    
                    //if iterator which was 0 equals to block size which is 256 (buffer size)
					//printf("FULL BUFFER: %s\n",myBuffer);
                    //code above is debugging
                    
                    commitBlock(myBuffer);
                    //calling commit block which flushes out our buffer
                    
                    memset(myBuffer,0,BLOCK_SIZE);
                    //we set memory of mybuffer to 0 , of size 256 
		            //same as free(myBuffer); and myBuffer= (char*)calloc(256, sizeof(char));
                    //memset(void *str , int,size)
                    
                    iterator=0;
                    //we set our iterator value back to 0
                }
            }
           
            nextString=getNext();
            // getting next string
			//printf("BUFFER: %s\n",myBuffer);
           //printf("NEXT STRING: %s \n ",nextString);
        }
		
        //printf("\n BUFFER AFTER : %s  \t NEXT STRING %s \n",myBuffer,nextString);
        if(iterator!=0)
        {
            //if iterator not equals to 0 then we flush again it is for a save purpose 
            commitBlock(myBuffer);
        }
       
	//free(nextString);
        // nextString=NULL;

        free(myBuffer);
	myBuffer=NULL;

        free(aboutMe);
	aboutMe=NULL;
	
        //freeing Everything
        /*
        Setting to null to avoid dangling pointers 
        */
		checkIt();
        //calling function check it to check if everything is correct
        return 0;
        //return something so code runs 
}

/*
MAIN COMMENTS / My Thoughts and Logic doing this assignment
To simply describe the logic of this file - I am creating commandline that is taking two parameters list of arguments and counter to count them.
I then create all my variables (because the code looks cleaner that way.
I decided to allocate memory using malloc instead of just creating an array of size 256 buffer[256] ,because it is proper way of creating buffer. As well as it creates buffer based on the real size of your variable/object.
I then  check for buffers if they are NULL so if they don't have anything inside them(they didn't get allocated) I write something that will state the error and exit the code with int 1.
I then start to fillout my aboutme object which is basically struct from personalInfo , I found out that if I just do aboutme->message = arguments[3] , it does not really copy whole message
so I had to use strcpy which copied all of my messages. Then I call a function writeperseonalInfo passing my about me information as a parameter (this is what the assignment is asking for).
I decided to create a constant char which stores my nextline. It is a way for me to controll my nextlines because if I were to call getNext(); each time it would be new line each time
but this way I actually store nextline somewhere.
I use whole loop which basically checks for NULL value in the nextline if its empty , this is used for our cmd line to continue working otherwise it would stop.
inside while loop I used for loop which checks for the last character inside our next string in C our last character in string is always \0 <- we went over that in class.
I then fillout my buffer and use my iterator which is 0 and do +1 inside the loop while our nextline does not get to \0 empty character. I use different counters , because one will be controlled iterator
and another one is not controlled which is i ,we use i in order to get all lines.
I then use if statement to check if buffer size equals to 256  , I flush out my buffer  set memory of my buffer back to 0 and the size of buffer 256.
and I set my iterator for buffer to 0.
I used nextstring = getNext(); because that way our cmd line not going to look for input from us and will continue working untill it gets to NULL.
I check for my iterator if it does not equal to 0 then I call commitblock again to flush out my memory this is more like for safety of my buffer.
I set my pointers to NULL and I free them to not have any dangling pointers e.t.c.
Lastly I call checkit() to make sure everything is properly allocated and works.
return 0 as a sucessful run 
*/
