#include "welch.h"

int main(int argc, char *argv[])
{
	int i,j,chan;
	int rank,size;
	char row[64][4096];
	char out_name[32];

	n_ffts = (x_len-seg_len/2)/(seg_len/2); //number of segments
	nfft = seg_len;
       	overlap = seg_len/2;
	psd_len = nfft/2 ;
	MAX_N = x_len ;


	in_data = (complex_t *)malloc(x_len * sizeof( complex_t ));

        memset (in_data,0.00, x_len * sizeof(complex_t));

	strcpy(out_name,argv[1]);


        strcat(out_name,".out");
        FILE* fout = fopen(out_name,"w");

        if (fout == NULL)
        {
                printf("Cannot create output data file\n");
                return(FALSE);
        }

	FILE* fin = fopen(argv[1], "r");

        if (fin == NULL)
        {
                printf("Cannot find input data file\n");
                 return(FALSE);
        }


	while (fgets(row[i],sizeof(row[i]),fin)!=NULL)
        {
		i++;
	}

	fft_win = (complex_t *)malloc(nfft * sizeof(complex_t));
        memset(fft_win,0.00,nfft*sizeof(complex_t));

        ham_win = (double *)malloc(nfft * sizeof(double));
        memset(ham_win,0.00, nfft * sizeof(double));

        pre_data(fft_win,ham_win); /* prepare data */

        sxx_t = (double *)malloc( nfft * sizeof(double));
        memset (sxx_t,0.00,nfft*sizeof(double));


	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	//printf("rank is %d\n",rank);

		
	for(chan = 0;chan < 64 ;chan ++)
	{
		getdata_from_row(row[chan]);
		for (i = rank ; i < n_ffts; i = i + size)
       		 {
	                startPos = i * (seg_len - overlap)  ;
	                stopPos = startPos + seg_len - 1;

       			 //printf("startPos is %d,stopPos is %d",startPos,stopPos);

		
			add_win(in_data,startPos,stopPos,ham_win); /* window is applied to each segment in every machine */


	                for ( j = 0 ; j < nfft; j++)
	                {
            			         sxx_t[j] = sxx_t[j] + sxx[j] ;
		        //              printf("sxx_t[%d] is %lf\n",j,sxx_t[j]);
		         }
		}// end for rank ;	
		if (rank > 0)
       			 MPI_Send(sxx_t,nfft , MPI_DOUBLE, 0, S_TAG, MPI_COMM_WORLD);
       		else
		{
	                /* 进程0接收sxx*/
//		         double tempTime = MPI_Wtime();

	                for(i = 1; i < size; i ++)
       			 {
	                        MPI_Recv(sxx, nfft, MPI_DOUBLE, i, S_TAG, MPI_COMM_WORLD,&status);
	                        for ( j = 0 ; j < nfft ; j++)
                               		sxx_t[j] = sxx_t[j] + sxx[j] ;
               		}

               		 /* Convert two-sided spectra to one-sided spectra*/
	                for ( i = 1; i < psd_len  ;i++)
	                {
        	               j = nfft - i;
       	                       sxx_t[i] = sxx_t[i] + sxx_t[j];
               		       //printf("sxx_t[%d] is %lf\n",i,sxx_t[i]);
		        }

	                freq = (double *)malloc( psd_len * sizeof(double));
	                norm = fs *  mu * n_ffts ;

	                for ( i=0; i<psd_len; i++)
	                {
	                        sxx[i] = sxx_t[i]/norm;
	                        freq[i] = i *fs /nfft;
	                        if ( sxx[i] ==0.0)
	                                sxx[i] = 1.0e-15;
		                        sxx[i] = 10.0 * log10(sxx[i]);
	                }
				
			for(i=0; i<psd_len ; i++)
        		       fprintf(fout, "%lf,%lf \n", freq[i],sxx[i]);

	
		} //end else

	} //end for  channel

	free(fft_win);
        free(ham_win);
        free(sxx);
        free(sxx_t);
        free(freq);
        free(in_data);

        fclose(fout);
        fclose(fin);
	

        MPI_Finalize();
	
	return 0;
}
