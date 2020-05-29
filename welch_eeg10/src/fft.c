#include "welch.h"


void comp_add(complex_t* result, const complex_t* c1, const complex_t* c2)
{
    result->r = c1->r + c2->r;
    result->i = c1->i + c2->i;
}


void comp_multiply(complex_t* result, const complex_t* c1, const complex_t* c2)
{
    result->r = c1->r * c2->r - c1->i * c2->i;
    result->i = c1->r * c2->i + c2->r * c1->i;
}


/*
 * Function:    shuffle
 * Description: 移动f中从beginPos到endPos位置的元素，使之按位置奇偶
 *              重新排列。举例说明:假设数组f，beginPos=2, endPos=5
 *              则shuffle函数的运行结果为f[2..5]重新排列，排列后各个
 *              位置对应的原f的元素为: f[2],f[4],f[3],f[5]
 * Parameters:  f为被操作数组首地址
 *              beginPos, endPos为操作的下标范围
 */
void shuffle(complex_t* f, int beginPos, int endPos)
{
    int i;
    complex_t temp[MAX_N];

    for(i = beginPos; i <= endPos; i ++)
    {
        temp[i] = f[i];
    }

    int j = beginPos;
    for(i = beginPos; i <= endPos; i +=2)
    {
        f[j] = temp[i];
        j++;
    }
    for(i = beginPos +1; i <= endPos; i += 2)
    {
        f[j] = temp[i];
        j++;
    }
}


/*
 * Function:		evaluate
 * Description:	对复数序列f进行FFT或者IFFT(由x决定)，结果序列为y，
 * 			产生leftPos 到 rightPos之间的结果元素
 * Parameters:	f : 原始序列数组首地址
 * 			beginPos : 原始序列在数组f中的第一个下标
 * 			endPos : 原始序列在数组f中的最后一个下标
 * 			x : 存放单位根的数组，其元素为w,w^2,w^3...
 * 			y : 输出序列
 * 			leftPos : 所负责计算输出的y的片断的起始下标
 * 			rightPos : 所负责计算输出的y的片断的终止下标
* 			totalLength : y的长度
 */
void evaluate(complex_t* f, int beginPos, int endPos, const complex_t* x, complex_t* y, int leftPos, int rightPos, int totalLength)
{
	int i;
	if ((beginPos > endPos)||(leftPos > rightPos))
	{
		printf("Error in use Polynomial!\n");
		exit(-1);
	}
	else
		if(beginPos == endPos)
		{			
			for(i = leftPos; i <= rightPos; i ++)
			{
				y[i] = f[beginPos];
			}
		}		
		else 
			if(beginPos + 1 == endPos)
			{
				for(i = leftPos; i <= rightPos; i ++)
				{
					complex_t temp;
					//comp_multiply(&temp, &f[endPos], &x[i]);
					comp_multiply(&temp, &x[i],&f[endPos]);
					comp_add(&y[i], &f[beginPos], &temp);
					//printf(" y[%d] is  %f + %fi \n",i,y[i].r,y[i].i);
				}				
			}	
			else
			{
				complex_t tempX[MAX_N],tempY1[MAX_N], tempY2[MAX_N];
				int midPos = (beginPos + endPos)/2;

				shuffle(f, beginPos, endPos);

				for(i = leftPos; i <= rightPos; i ++)
				{		
					comp_multiply(&tempX[i], &x[i], &x[i]);
				}							

				evaluate(f, beginPos, midPos, tempX, tempY1, leftPos, rightPos, totalLength);
				evaluate(f, midPos+1, endPos, tempX, tempY2, leftPos, rightPos, totalLength);

				for(i = leftPos; i <= rightPos; i ++)
				{
					complex_t temp;
					comp_multiply(&temp, &tempY2[i],&x[i]);
					comp_add(&y[i], &tempY1[i], &temp);
				}			
			}	
}


/*
 * Function:    print
 * Description: 打印数组元素的实部
 * Parameters:  f为待打印数组的首地址
 *              fLength为数组的长度
 */
void print(const complex_t* f, int fLength)
{
    BOOL isPrint = FALSE;
    int i;

    /* f[0] */
    if (abs(f[0].r) > EPS)
    {
        printf("%f", f[0].r);
        isPrint = TRUE;
    }

    for(i = 1; i < fLength; i ++)
    {
        if (f[i].r > EPS)
        {
            if (isPrint)
                printf(" + ");
            else
                isPrint = TRUE;
            printf("%ft^%d", f[i].r, i);
        }
        else if (f[i].r < - EPS)
        {
            if(isPrint)
                printf(" - ");
            else
                isPrint = TRUE;
            printf("%ft^%d", -f[i].r, i);
        }
    }
    if (isPrint == FALSE)
        printf("0");
    printf("\n");
}


/*
 * Function:    myprint
 * Description: 完整打印复数数组元素，包括实部和虚部
 * Parameters:  f为待打印数组的首地址
 *              fLength为数组的长度
 */
void myprint(const complex_t* f, int fLength)
{
    int i;
    for(i=0;i<fLength;i++)
    {
        printf("%f+%fi , ", f[i].r, f[i].i);
    }
    printf("\n");
}


/*
 * Function:   addTransTime
 * Description:累计发送数据所耗费的时间
 * Parameters: toAdd为累加的时间
 */
void addTransTime(double toAdd)
{
    transTime += toAdd;
}

