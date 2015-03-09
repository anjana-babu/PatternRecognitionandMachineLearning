#include <stdio.h>
#include <stdlib.h>

/* Using Linde Buzo Gray Algorithm - Mahalanobis Distance */
int main(int argc, char *argv[])
{

  double x[1000];
  char class[1000];
  double mean = 0.0, mean1 = 0.0, mean2 = 0.0, mean1_prev = 0.0, mean2_prev = 0.0;
  double variance = 0.0, variance1 = 0.0, variance2 = 0.0, variance1_prev = 0.0, variance2_prev = 0.0;
  int i=0;
  FILE *fp;
  char s[20];
  int np, count_class1, count_class2;

  /*
   * Training data
   */
  fp = fopen("trainData.txt","rb");
  if (fp == NULL)
  {
     perror("Failed to open file \"myfile\"");
     return EXIT_FAILURE;
  }

  /* Reading all the values from a file */
  while(!feof(fp))
  {
     fscanf(fp,"%lf",&x[i]);
     i++;
  }
  np = i;
  fclose(fp);

  /* Calculating mean for all the points */
  for(i = 0;i < np;i++)
  {
     mean += x[i];
  }
  mean /= np;

  /* Calculating variance for all the points */
  for(i = 0;i < np;i++)
  {
     variance += (x[i]-mean) * (x[i]-mean);
  }
  variance /= np;

  //printf("\n Mean= %lf, Variance= %lf",mean,variance);

  mean1 = mean - 100*sqrt(variance);
  mean2 = mean + 100*sqrt(variance);

printf("\n Initial mean 1 : %lf ",mean1);
printf("\n Initial mean 2 : %lf ",mean2);


for(i = 0;i < np;i++)
     {
        if((sqrt((x[i]-mean1)*(x[i]-mean1)))<(sqrt((x[i]-mean2)*(x[i]-mean2))))
        {
           class[i] = 1;
        }
        else
        {
           class[i] = 2;
        }
     }

for(i = 0;i < np;i++)
     {
        if(class[i] == 1)
        {
           variance1 += (x[i]-mean1) * (x[i]-mean1);
           count_class1++;
        }
        else
        {
           variance2 += (x[i]-mean2) * (x[i]-mean2);
           count_class2++;
        }
     }
     variance1 /= count_class1;
     variance2 /= count_class2;


  do
  {
     for(i = 0;i < np;i++)
     {
        if((sqrt((x[i]-mean1)*(x[i]-mean1)/variance1))<(sqrt((x[i]-mean2)*(x[i]-mean2)/variance2)))
        {
           class[i] = 1;
        }
        else
        {
           class[i] = 2;
        }
     }

     /* Computing mean for 2 classes */
     mean1_prev = mean1;
     mean2_prev = mean2;

     count_class1 = 0;
     count_class2 = 0;
     mean1 = 0;
     mean2 = 0;

     for(i = 0;i < np;i++)
     {
        if(class[i] == 1)
        {
           mean1 += x[i];
           count_class1++;
        }
        else
        {
           mean2 += x[i];
           count_class2++;
        }
     }
     mean1 /= count_class1;
     mean2 /= count_class2;

     /* Computing variance for 2 classes */
     variance1_prev = variance1;
     variance2_prev = variance2;
     count_class1 = 0;
     count_class2 = 0;
     variance1 = 0;
     variance2 = 0;

     for(i = 0;i < np;i++)
     {
        if(class[i] == 1)
        {
           variance1 += (x[i]-mean1) * (x[i]-mean1);
           count_class1++;
        }
        else
        {
           variance2 += (x[i]-mean2) * (x[i]-mean2);
           count_class2++;
        }
     }
     variance1 /= count_class1;
     variance2 /= count_class2;
     printf("\n mean1 = %lf, mean2 = %lf, mean1_prev = %lf, mean2_prev = %lf, class1=%d, class2 = %d ",mean1,mean2,mean1_prev,mean2_prev,count_class1,count_class2);
  }while(mean1!=mean1_prev && mean2!=mean2_prev);

  printf("\n Mean of class 1 = %lf",mean1);
  printf("\n Variance of class 1 = %lf", variance1);
  printf("\n Mean of class 2 = %lf",mean2);
  printf("\n Variance of class 2 = %lf", variance2);

  /*
   * Testing data
   */

  fp = fopen("testData.txt","rb");
  if (fp == NULL)
  {
     perror("Failed to open file \"myfile\"");
     return EXIT_FAILURE;
  }

  /* Reading all the values from a file */
  i = 0;
  while(!feof(fp))
  {
     fscanf(fp,"%lf",&x[i]);
     i++;
  }
  np = i;
  fclose(fp);

  count_class1 = 0;
  count_class2 = 0;
  for(i = 0;i < (np - 100) ;i++)
  {
     if((sqrt((x[i]-mean1)*(x[i]-mean1)/variance1))<(sqrt((x[i]-mean2)*(x[i]-mean2)/variance2)))
     {
        class[i] = 1;
        count_class1++;
     }
     else
     {
        class[i] = 2;
        count_class2++;
     }
  }
  printf("\n Testing first 100 points.. ");
  printf("\n Class 1 : %d, Class 2 : %d", count_class1, count_class2);

   count_class1 = 0;
  count_class2 = 0;
  for(i = (np - 100);i < np ;i++)
  {
     if((sqrt((x[i]-mean1)*(x[i]-mean1)/variance1))<(sqrt((x[i]-mean2)*(x[i]-mean2)/variance2)))
     {
        class[i] = 1;
        count_class1++;
     }
     else
     {
        class[i] = 2;
        count_class2++;
     }
  }
  printf("\n Testing next 100 points..");
  printf("\n Class 1 : %d, Class 2 : %d", count_class1, count_class2);

  system("PAUSE");
  return 0;
}
