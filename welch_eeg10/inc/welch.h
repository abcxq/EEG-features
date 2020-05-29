#ifndef WELCH_H
#define	WELCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mpi.h"

#define PI    3.1415926535897932
#define EPS   10E-8
#define V_TAG 99
#define P_TAG 100
#define Q_TAG 101
#define R_TAG 102
#define S_TAG 103
#define S_TAG2 104

typedef enum {FALSE, TRUE}
BOOL;

typedef struct
{
    double r;
    double i;
} complex_t;

int psd_len,overlap,n_ffts,nfft,MAX_N;
//int seg_len,fs,psd_len,overlap,n_ffts,nfft,MAX_N;
static int seg_len=64,fs=256,x_len=256;
//long int x_len,total_len;
int startPos,stopPos;
static double transTime = 0.00, totalTime = 0.00, beginTime;
double norm,mu;
double *sxx,*sxx_t,*ssx_reduce[8]; /* store power */
double *freq; /* store frequency */
double *ham_win;
complex_t *fft_win,*in_data,*s,*total_in_data[8];
MPI_Status status;


void pre_data(complex_t z[],double win[]);
void add_win(complex_t x[],int start,int stop,double window[]); /* window is applied to each segment of x */
void comp_add(complex_t* result, const complex_t* c1, const complex_t* c2);
void comp_multiply(complex_t* result, const complex_t* c1, const complex_t* c2);

void shuffle(complex_t* f, int beginPos, int endPos);
void evaluate(complex_t* f, int beginPos, int endPos, const complex_t* x,\
		 complex_t* y, int leftPos, int rightPos, int totalLength);

void print(const complex_t* f, int fLength);
void myprint(const complex_t* f, int fLength);
void addTransTime(double toAdd);
void getdata_from_row(char data[]);
/*BOOL readFromFile(char *filename);
void sendOrigData(int size);
void sendchanneldata(int size,int num);
void recvOrigData();
void master_reduce(int size);
BOOL output2file(char *filename);*/

#endif	/* WELCH_H */

