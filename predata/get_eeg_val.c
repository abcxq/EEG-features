#include <stdio.h>
#include <math.h>
#include <string.h>

	 
int main(int argc,char **argv)
{

	int i,j,trial,number;
	long x_len,count = 0;
	char row[256];
	char string[16];
	char out_name[32];
	FILE *fin,*fout;
	//complex_t *in_data[8];
	double in_data[256];
	int  chan_flag = 1;
	if( argc < 2)
	{
		printf("Usage:readfile filename\n");
		return -1;
	}

	fin = fopen(argv[1], "r");
	
	strcpy(out_name,argv[1]);
	

	strcat(out_name,".val");
	fout = fopen(out_name,"w");

	if (fin == NULL)
	{
        	printf("Cannot find input data file\n");
       		 return -2 ;
	}



//	fseek(fin,0,SEEK_SET); 

/*	for(i=0;i<8;i++)
	{
		in_data[i] = (complex_t *)malloc(x_len * sizeof( complex_t ));
		memset (in_data[i],0.00, x_len * sizeof(complex_t));
	} */


	i = 0;
	fgets(row,sizeof(row),fin); //skip the first  four 
	fgets(row,sizeof(row),fin); 
	fgets(row,sizeof(row),fin); 
	fgets(row,sizeof(row),fin); 

	while (fgets(row,sizeof(row),fin)!=NULL)
	{
		if(chan_flag)
		{
			chan_flag = 0;
			continue;
		}	
        	sscanf(row, "%d %s %d %lf",&trial,string,&number,&in_data[i]); 

		i = i + 1;
		if ( i == 256 )
		{
			//write_to_file(in_data);
			for(j = 0;j<255;j++)
	                {
                        	fprintf(fout,"%lf,",in_data[j]);
	                }
                       	fprintf(fout,"%lf\n",in_data[255]);
			i = 0 ;
			chan_flag = 1;
			continue;
		}
        }
/*
	for(i = 0;i<x_len; i++)
	{
		for(j = 0;j<8;j++)
		{
			printf("%lf\t",in_data[j][i].r);
		}
		printf("\n");
	}

*/

        fclose(fin);
        fclose(fout);

	return 0;
}
