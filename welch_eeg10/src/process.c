#include "welch.h"
void getdata_from_row(char data[])
{
        int i;
        char *token;

        for(i = 0;i< 256;i++)
        {
                token = strsep(&data,",");
                in_data[i].r = atof(token);
        	in_data[i].i = 0.00;
        }
}


void pre_data(complex_t z[],double win[])
{
	int i;
	double fl;
	
	mu = 0.00;


	 /* 初始化数组z，用于进行傅立叶变换 */
        for(i = 0; i < nfft ; i ++)
        {
                z[i].r = cos(i*2*PI/seg_len);

                z[i].i = sin(i*2*PI/seg_len);
        }

        /*  init window funtion arry */
        fl = seg_len - 1.0;
        for(i = 0;i < seg_len;i++)
        {
               win[i] = 0.54-0.46*cos(2*PI*i/fl); //Hamming window
//               win[i] = 0.54-0.5*cos(2*PI*i/fl); //Hann window
//		 win[i] = 1;			   //Rectangular window
		mu = mu + win[i] * win[i] ;
        }



}


void add_win(complex_t *x,int start,int stop,double *window) /* window is applied to each segment of x */
{
	int i,j;
	complex_t *xx;

	i = 0;



	xx =(complex_t *)malloc(nfft *sizeof(complex_t));
	memset(xx,0.00,nfft * sizeof(complex_t));

	for ( j = start;j < stop+1 ;j++,i++)
	{
		xx[i].r = x[j].r * window[i];
		xx[i].i = 0;

	}
	
/*	for (; i < variableNum ; i++ )
	{
		secdata_add0[i].r = 0;
		secdata_add0[i].i = 0;
	}

	for(i=0; i<variableNum ; i++)  
        {        
              fprintf(fout, "r is %lf,i is %lf \n", secdata_add0[i].r,secdata_add0[i].i);
        } */
		
	s = (complex_t *)malloc(nfft * sizeof(complex_t));
	memset (s,0.00, nfft * sizeof(complex_t));

    /* 对加窗后的数据sec_data作FFT，输出序列为s，每个进程仅负责计算出序列中 */
    /* 位置为startPos 到 stopPos的元素 */
	evaluate(xx, 0, nfft - 1, fft_win, s, 0, nfft - 1, nfft); /*cal fft */


         /* cal the power of every segment */
         sxx = (double *)malloc( nfft * sizeof(double));
	 memset (sxx,0.00,nfft*sizeof(double));

        for ( i = 0; i < nfft  ;i++)
        {
    /*           j = nfft - i;
               sxx[i] = sxx[i] + s[i].r * s[i].r + s[i].i * s[i].i;
               sxx[i] = sxx[i] + s[j].r * s[j].r + s[j].i * s[j].i; */
               sxx[i] = s[i].r * s[i].r + s[i].i * s[i].i;
	//	printf("sxx[%d] is %lf\n",i,sxx[i]);
        }

/*        sxx[0] += s[0].r*s[0].r*2.0;
        sxx[0] += s[0].i*s[0].i*2.0; */


	free(s);
	free(xx);

}


/*
 * Function:    readFromFile
 * Description:	从dataIn.txt读取数据
 */
/*BOOL readFromFile()
{
	int i;
	long count = 0;
	char row[32];
	FILE* fin = fopen("xqqse.txt", "r");

	if (fin == NULL)
	{
        	printf("Cannot find input data file\n");
       		 return(FALSE);
	}

	while (fgets(row,32,fin)!=NULL)
		count++;

	printf("The number of that file is %ld\n",count);
	printf("Please input the number you want welch\n");
	scanf(" %d",&x_len);

	printf("Enter the length of every segment  (0 quits)\n ");
        scanf("%d",&seg_len); 

        if (seg_len == 0)
		return 0;

		
	printf("Please input the frequency (0 quits) ");
	scanf(" %d",&fs);

        if (fs == 0)
		return 0;

	MAX_N = x_len ;


	fseek(fin,0,SEEK_SET);

	in_data = (complex_t *)malloc(x_len * sizeof( complex_t ));

	memset (in_data,0.00, x_len * sizeof(complex_t));

    for(i = 0; i < x_len; i ++)
    {
        fscanf(fin, "%lf", &in_data[i].r);
        in_data[i].i = 0.00;
    }

    fclose(fin);
    return(TRUE);
}

*/
/*
 * Function:    sendOrigData
 * Description: 把原始数据发送给其它进程
 * Parameters:  size为集群中进程的数目
 */
void sendOrigData(int size)
{
    int i;
    for(i = 1; i < size; i ++)
    {
        MPI_Send(&x_len, 1, MPI_INT, i, V_TAG, MPI_COMM_WORLD);
        MPI_Send(&seg_len, 1, MPI_INT, i, V_TAG, MPI_COMM_WORLD);
        MPI_Send(&fs, 1, MPI_INT, i, V_TAG, MPI_COMM_WORLD);
        MPI_Send(in_data, x_len * 2 , MPI_DOUBLE, i, P_TAG, MPI_COMM_WORLD);
    }
}


/*
 * Function:    recvOrigData
 * Description:	接受原始数据
 */
void recvOrigData()
{
	MPI_Recv(&x_len, 1, MPI_INT, 0, V_TAG, MPI_COMM_WORLD, &status);
	MPI_Recv(&seg_len, 1, MPI_INT, 0, V_TAG, MPI_COMM_WORLD, &status);
	MPI_Recv(&fs, 1, MPI_INT, 0, V_TAG, MPI_COMM_WORLD, &status);

	in_data = (complex_t *)malloc(x_len * sizeof( complex_t ));
	memset (in_data,0.00, x_len * sizeof(complex_t));
	MPI_Recv(in_data, x_len * 2 , MPI_DOUBLE, 0, P_TAG, MPI_COMM_WORLD, &status);

	n_ffts = (x_len-seg_len/2)/(seg_len/2);
        nfft = seg_len;
        overlap = seg_len/2;
	psd_len = nfft/2;
	MAX_N = x_len ;
	
}


