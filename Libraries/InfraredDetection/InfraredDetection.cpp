#include "InfraredDetection.h";
#include "Arduino.h";
InfraredDetection::InfraredDetection(int ilength,int[] iports){
	port=&iports;
	length=ilength;

}
bool InfraredDetection::getBall(){
	int	r;
	int min=0;
	int minVal=1023;
	for(int i=0;i<length-3;i++){
		r=analogRead(ports[i]);
		if(r<1020){
			return true;
		}
	}
	return false;
}
int InfraredDetection::getClosestDirection(){
	int min=0;
	int r;
	for(int i=0;i<length-3;i++){
		r=analogRead(ports)[i];
		if(r<1000)
		{
			if(r<minVal){
				minVa=r;
				min=i;
				if(min>=(length-3/2))
					min=i+3;
			}
		}
	}
	return min;
}
int InfraredDirection::getDirection()
{
	int result=-1;
	int count=0;
	int r;
	for(int i=0;i<length-3;i++){
		r=analogRead(ports)[i];
		if(r<1000)
		{
			count++;
		}
	}
	if(count>0){
		int index=0;
		int detected[count];
		for(int i=0;i<length-3;i++){
			r=analogRead(ports)[i];
			if(r<1000)
			{
				detected[index]=i;
				if(min>=(length-3/2))
					detected[index]=i+3;
				index++;
			}
		}
		int compare=detected[0];
		bool adjacent=true;
		for(int i=1;i<count && adjacent==true;i++){
			if(compare+1!=detected[i]){
				adjacent=false;
			}
			compare=detected[i];
		}
		if(adjacent){
			result=detected[(count/2)-1];
		}
		else{
			int sum=0;
			for(int i=0;i<count;i++){
				if(min<(length-3/2)){
					sum+=detected[i];
				}
				else{
					sum+=detected[i]-(length-3);
				}
			}
			if(sum<0){
				result=sum/count+(length-3);
			}
			if(sum>0)
			{
				result=sum/count+(length-3);
			}
			else
			{
				result=sum/count;
			}
		}
		} 
	}
	return result;
}
