#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int bayes_classifier(double x, double mean1, double mean2, double mean3, double variance1, double variance2, double variance3);

int main(int argc, char *argv[])
{
  FILE *fp;
  int no_train=0,no_test=0,i=0;
  double training[1500];
  double test[1500];
  double class[500];
  int count_class1=0,count_class2=0,count_class3=0;
  int np, no_classes;
  double mean1=0.0,mean2=0.0,mean3=0.0,variance1=0.0,variance2=0.0,variance3=0.0;
  
  /* Dataset 1: 1-dimensional artificial data of 3 classes 
   * Total data points: 1500
   * First 500 from class 1
   * Next 500 from class 2
   * Last 500 from class 3
   * 75% of data points from each class is used as training data
   * 25% of data points from each class is used as test data
   */
  fp = fopen("dsI_group2.txt","rb");
  if (fp == NULL)
  {
     perror("Failed to open file \"myfile\"");
     return EXIT_FAILURE;
  }

  /* Reading all the values from a file */
  while(!feof(fp))
  {
     /* Test points */
     if((i>=375&&i<500)||(i>=875&&i<1000)||(i>=1375&&i<1500))
     {
         fscanf(fp,"%lf",&test[no_test++]);
     }
     /* Training points */
     else
     {
         fscanf(fp,"%lf",&training[no_train++]);
     }
     
     i++;
  }
  /* Closing the file */
  fclose(fp);
  
  /* Estimated Mean for class 1 */
  for(i=0;i<375;i++)
  {
      mean1+=training[i];
  }
  mean1=mean1/375;
  
  /* Estimated Mean for class 2 */
  for(;i<750;i++)
  {
       mean2+=training[i];
  }
  mean2=mean2/375;
  
  /* Estimated Mean for class 3 */
  for(;i<1125;i++)
  {
       mean3+=training[i];
  }
  mean3=mean3/375;
  
  /* Estimated Variance for class 1 */
  for(i=0;i<375;i++)
  {
      variance1+=((training[i]-mean1)*(training[i]-mean1));
  }
  variance1=variance1/375;
  
  /* Estimated Variance for class 2 */
  for(;i<750;i++)
  {
      variance2+=((training[i]-mean2)*(training[i]-mean2));
  }
  variance2=variance2/375;
  
  /* Estimated Variance for class 3 */
  for(;i<1125;i++)
  {
      variance3+=((training[i]-mean3)*(training[i]-mean3));
  }
  variance3=variance3/375;
  
  /* Displaying estimated means */
  printf("\n Mean 1 = %lf\t Variance 1 = %lf",mean1,variance1);
  printf("\n Mean 2 = %lf\t Variance 2 = %lf",mean2,variance2);
  printf("\n Mean 3 = %lf\t Variance 3 = %lf",mean3,variance3);
  
  /* Chi square test */

  /* Training data using Bayes classifier */
  for(i=0;i<375;i++)
  {
      class[i]=bayes_classifier(test[i],mean1,mean2,mean3,variance1,variance2,variance3);
      if(class[i]==1)
      {
          count_class1++;
      }
      else if(class[i]==2)
      {
          count_class2++;
      }
      else if(class[i]==3)
      {
          count_class3++;
      }
  }
  
  /* Classification */
  printf("\n No of points classified as class 1 = %d ",count_class1);
  printf("\n No of points classified as class 2 = %d ",count_class2);
  printf("\n No of points classified as class 3 = %d ",count_class3);
    
  system("PAUSE");	
  return 0;
}


int bayes_classifier(double x, double mean1, double mean2, double mean3, double variance1, double variance2, double variance3)
{
    double gauss_pdf1,gauss_pdf2,gauss_pdf3;
    
    gauss_pdf1=1/sqrt(2*3.14*variance1)*pow(2.303,-0.5*(x-mean1)*(x-mean1)/variance1);
    gauss_pdf2=1/sqrt(2*3.14*variance2)*pow(2.303,-0.5*(x-mean2)*(x-mean2)/variance2);
    gauss_pdf3=1/sqrt(2*3.14*variance3)*pow(2.303,-0.5*(x-mean3)*(x-mean3)/variance3);
    
    if((gauss_pdf1>gauss_pdf2)&&(gauss_pdf1>gauss_pdf3))
    {
         return 1;
    }
    else if((gauss_pdf2>gauss_pdf1)&&(gauss_pdf2>gauss_pdf3))
    {
         return 2;
    }
    else if((gauss_pdf3>gauss_pdf2)&&(gauss_pdf3>gauss_pdf1))
    {
         return 3;
    }
    return 0;
}
