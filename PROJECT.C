#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
struct student
{
  int id;
  char name[20];
  char date[15];
  char status;
};
void adddata();
void displaydata();
void searchdata();
void updatedata();
void deletedata();
void main()
{
  int choice;
  clrscr();
  while(1)
  {
    printf("\n======STUDENT ATTENDENCE SYSTEM======\n");
    printf("\n1. Add Record");
    printf("\n2. Display Record");
    printf("\n3. Search Record");
    printf("\n4. Update Record");
    printf("\n5. Delete Record");
    printf("\n6. Exit");
    printf("\nEnter your choice:");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1:
	 adddata();
	 break;
      case 2:
	 displaydata();
	 break;
      case 3:
	 searchdata();
	 break;
      case 4:
	 updatedata();
	 break;
      case 5:
	 deletedata();
	 break;
      case 6:
	 exit(0);
      default:
	 printf("INVALID CHOICE");
    }
     getch();
  }
}
void adddata()
{
   struct student s,temp;
   FILE *fp;
   int found = 0;
   printf("Enter ID :");
   scanf("%d",&s.id);
   printf("Enter Name :");
   scanf("%s",s.name);
   printf("Enter Date (DD-MM-YYYY) :");
   scanf("%s",s.date);
   printf("Enter Status (P/A) :");
   scanf(" %c",&s.status);
   fp=fopen("att.dat","rb");
   if(fp!=NULL)
   {
   while(fread(&temp,sizeof(temp),1,fp))
   {
     if(temp.id==s.id && strcmp(temp.date,s.date)==0)
     {
       found = 1;
       break;
     }
   }
   fclose(fp);
}
if(found==1)
{
  printf("Already Exists\n");
  return;
}
   fp=fopen("att.dat","ab");
   fwrite(&s,sizeof(s),1,fp);
   fclose(fp);
   printf("\n!Record Add Sucessfully\n");
}
 void displaydata()
 {
   struct student s;
   FILE *fp;
   int i,day,current_id;
   char status[31];
   fp=fopen("att.dat","rb");
   if(fp==NULL)
   {
     printf("File can't open");
     exit(0);
   }
     for(i=0;i<31;i++)
     {
       if((i+1)%7==0)
	 status[i]='H';
       else
       status[i]='-';
    }
     printf("\n%-2s %-8s ","ID","Name");
     for(i=1;i<=31;i++)
     printf("%d ",i%10);
     printf("\n----------------------------------------------------------------------------\n");
     if(fread(&s,sizeof(s),1,fp))
     {
	current_id = s.id;
	printf("%-2d %-8s",s.id,s.name);
	do
	 {
	   if(s.id != current_id)
	   {
	     for(i=0;i<31;i++)
	       printf("%c ",status[i]);
	       printf("\n");
	     for(i=0;i<31;i++)
	       status[i]='-';
	       current_id = s.id;
	       printf("%-2d %-8s",s.id,s.name);
	   }
	   day = (s.date[0]-'0')*10 + (s.date[1]-'0');
	   if(day >= 1 && day <=31)
	   {
	     if(day % 7 != 0)
	     status[day-1] =s.status;
	 }
     }
	 while(fread(&s,sizeof(s),1,fp));
	  for(i=0;i<31;i++)
	  printf("%c ",status[i]);
	  printf("\n");
	}

     fclose(fp);
 }
 void searchdata()
 {
   struct student s;
   FILE *fp;
   int id,total=0,present=0,absent=0;
   float per;
   fp=fopen("att.dat","rb");
   if(fp==NULL)
   {
     printf("File can't open");
     exit(0);
   }
    printf("Enter ID to search:");
    scanf("%d",&id);
    printf("\nID\tName\tDate\t\tStatus\n");
    while(fread(&s,sizeof(s),1,fp))
    {
      if(s.id==id)
      {
	printf("%d\t%s\t%s\t%c\n",s.id,s.name,s.date,s.status);
	total++;
	if(s.status == 'P' || s.status == 'p')
	  present++;
	  else
	   absent++;
       }
    }
     fclose(fp);
     if(total==0)
     {
       printf("\nRecord Not Found");
     }
     else
     {
       per = (present * 100.0) / total;
       printf("\nTotal Days = %d",total);
       printf("\nPresent Days = %d",present);
       printf("\nAbsent Dats = %d",absent);
       printf("\nPercentage = %.2f",per);
     }
   }
   void updatedata()

   {
     struct student s;
     FILE *fp,*temp;
     int updateid;
     int found=0;
     fp=fopen("att.dat","rb");
     temp=fopen("temp.dat","wb");
     if(fp==NULL||temp==NULL)
     {
       printf("file can't open");
       exit(0);
     }
     printf("Enter ID Update:");
     scanf("%d",&updateid);
     while(fread(&s,sizeof(s),1,fp))
     {
       if(s.id==updateid)
       {
	 printf("\ncurrent Record:\n");
	 printf("%d\t%s\t%s\t%c\n",s.id,s.name,s.date,s.status);
	 printf("Enter new name:");
	 //getchar();
	// flushall();
	 scanf("%s",s.name);
	 printf("Enter New Date:");
	 scanf("%s",s.date);
	 printf("Enter new Status:");

	 scanf(" %c",&s.status);
	 found = 1;
	} //fseek(fp,-sizeof(s),SEEK_CUR);
	 //fflush(fp);
	 fwrite(&s,sizeof(s),1,temp);
	}
	fclose(fp);
	fclose(temp);
	remove("att.dat");
	rename("temp.dat","att.dat");
	if(found)
	 printf("\nRecord Updated Sucessfully!\n");

	 else
	 {
	   printf("\nRecord Not Found!\n");
	 }
	 fclose(fp);
       }
      void deletedata()
      {
	 struct student s;
	 FILE *fp,*temp;
	 int deleteid;
	 int found=0;
	 fp=fopen("att.dat","rb");
	 if(fp == NULL)
	 {
	   printf("file can't open");
	   exit(0);
	 }
	 temp=fopen("temp.dat","wb");
	 if(temp==NULL)
	 {
	   printf("file can't open");
	   exit(0);
	 }
	 printf("Enter ID to delete:");
	 scanf("%d",&deleteid);
	 while(fread(&s,sizeof(s),1,fp))
	 {
	   if(s.id==deleteid)
	   {
	      found = 1;
	      printf("Record with ID = %d has been deeleted\n",s.id);
	   }
	   else
	   {
	      fwrite(&s,sizeof(s),1,temp);
	   }
       }
       fclose(fp);
       fclose(temp);
       remove("att.dat");
       rename("temp.dat","att.dat");
       if(!found)
       {
	 printf("record not found");
       }

      }
