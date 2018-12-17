#include <stdio.h>
#include <stdlib.h>

int concat2(int d1,int d2){
    int len=0;
    int temp=d2;

    while(temp>0){
        temp=temp%10;
        len++;
    }

    while(len>0){
        d1=d1*10;
        len--;
    }

    return d1+d2;
}

int concat3(int d1,int d2,int d3){
    d2=concat2(d2,d3);
    return concat2(d1,d2);
}
int main() {
	//code
	return 0;
	int T;
	printf("Enter T: ");
	scanf("%d",&T);

	int i=0;
	int j=0,k=0,l=0;
	int sum=0,num=0;
	int a[3];
	int d1,d2,d3,x,y,z;
	for(i=0;i<T;i++){
	    sum=0;
	    scanf("%d %d %d",&x,&y,&z);

	    a[0]=4*x;
	    a[1]=5*y;
	    a[2]=6*z;

	    //Case 1:taking individual digits
	    sum=sum+a[0]+a[1]+a[2];

	    //Case2: Taking 2 digits at a time
	    for(j=0;j<3;j++){
	        d1=a[j];

	        for(k=0;k!=j && k<3;k++){
	            d2=a[k];
	            num=concat2(d1,d2);
	            sum=sum+num;
	        }
	    }

	    //Case3: taking 3 at a time
	    for(j=0;j<3;j++){
	        d1=a[j];

	        for(k=0;k!=j && k<3;k++){
	            d2=a[k];

	            for(l=0;l!=k && l!=j && l<3;l++){
	                d3=a[l];
	                num=concat3(d1,d2,d3);
	                sum=sum+num;
	            }
	        }
	    }

	    printf("%d\n",sum%(1000000007));
	}
}

