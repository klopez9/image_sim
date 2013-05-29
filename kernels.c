/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "derp",              /* Team name */

    "Ben Malecki",     /* First member full name */
    "bmaleck1@binghamton.edu",  /* First member email address */

    "Kevin Lopez",                   /* Second member full name (leave blank if none) */
    "klopez9@binghamton.edu"                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
/*char rotate_descr[] = "rotate: Current working version!!!!!!!!!!!";
void rotate(int dim, pixel *src, pixel *dst) 
{
	if(dim >256){
		rotate_new(dim,scrc,dst);
	} else {
		naive_rotate(dim,src,dst);
	}
}
*/
typedef struct {
	int dim;
	int rowB;
	int rowE;
	pixel *src;
	pixel *dst;
	//declare things here
} threadInfo;

void threadFunc(void * arg) {
	threadInfo x =*(threadInfo *) arg;
	int i,j;
	for(j = x.rowB;j< (x.rowE);j++) { //increments through 1/4 of the rows of the source file
		for (i = 0;i< (x.dim);i++) { 
			x.dst[RIDX(x.dim-1-j,i,x.dim)] = x.src[RIDX(i,j,x.dim)];

			//wierd loop unrolling actually slows down everything signifigantly

			/*x.dst[RIDX(x.dim-1-j,(i+1),x.dim)] = x.src[RIDX((i+1),j,x.dim)];
			x.dst[RIDX(x.dim-1-j,(i+2),x.dim)] = x.src[RIDX((i+2),j,x.dim)];
			x.dst[RIDX(x.dim-1-j,(i+3),x.dim)] = x.src[RIDX((i+3),j,x.dim)];
			x.dst[RIDX(x.dim-1-j,(i+4),x.dim)] = x.src[RIDX((i+4),j,x.dim)];
			x.dst[RIDX(x.dim-1-j,(i+5),x.dim)] = x.src[RIDX((i+5),j,x.dim)];
			x.dst[RIDX(x.dim-1-j,(i+6),x.dim)] = x.src[RIDX((i+6),j,x.dim)];
			x.dst[RIDX(x.dim-1-j,(i+7),x.dim)] = x.src[RIDX((i+7),j,x.dim)];*/
			/*x.dst[RIDX(x.dim-1-(j+1),i,x.dim)] = x.src[RIDX(i,(j+1),x.dim)];
			x.dst[RIDX(x.dim-1-(j+2),i,x.dim)] = x.src[RIDX(i,(j+2),x.dim)];
			x.dst[RIDX(x.dim-1-(j+3),i,x.dim)] = x.src[RIDX(i,(j+3),x.dim)];
			x.dst[RIDX(x.dim-1-(j+4),i,x.dim)] = x.src[RIDX(i,(j+4),x.dim)];
			x.dst[RIDX(x.dim-1-(j+5),i,x.dim)] = x.src[RIDX(i,(j+5),x.dim)];
			x.dst[RIDX(x.dim-1-(j+6),i,x.dim)] = x.src[RIDX(i,(j+6),x.dim)];
			x.dst[RIDX(x.dim-1-(j+7),i,x.dim)] = x.src[RIDX(i,(j+7),x.dim)];
			*/
		}
	}
}
void noThreadFunc(int dim, pixel *src, pixel *dst) {
	int i, j;
	for (j = 0; j < dim; j++) {
		for (i = 0; i < dim; i++) {
	    		dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];

			//looop unrolling removed because it slows everything down

			/*dst[RIDX(dim-1-j,(i+1),dim)] = src[RIDX((i+1),j,dim)];
			dst[RIDX(dim-1-j,(i+2),dim)] = src[RIDX((i+2),j,dim)];
			dst[RIDX(dim-1-j,(i+3),dim)] = src[RIDX((i+3),j,dim)];
			dst[RIDX(dim-1-j,(i+4),dim)] = src[RIDX((i+4),j,dim)];
			dst[RIDX(dim-1-j,(i+5),dim)] = src[RIDX((i+5),j,dim)];
			dst[RIDX(dim-1-j,(i+6),dim)] = src[RIDX((i+6),j,dim)];
			dst[RIDX(dim-1-j,(i+7),dim)] = src[RIDX((i+7),j,dim)];*/
			/*dst[RIDX(dim-1-(j+1),i,dim)] = src[RIDX(i,(j+1),dim)];
			dst[RIDX(dim-1-(j+2),i,dim)] = src[RIDX(i,(j+2),dim)];
			dst[RIDX(dim-1-(j+3),i,dim)] = src[RIDX(i,(j+3),dim)];
			dst[RIDX(dim-1-(j+4),i,dim)] = src[RIDX(i,(j+4),dim)];
			dst[RIDX(dim-1-(j+5),i,dim)] = src[RIDX(i,(j+5),dim)];
			dst[RIDX(dim-1-(j+6),i,dim)] = src[RIDX(i,(j+6),dim)];
			dst[RIDX(dim-1-(j+7),i,dim)] = src[RIDX(i,(j+7),dim)];
			*/
		}
	}
}

char rotate_new_descr[] = "!!!!!!!!!!!!!!!!!!!!!"; 
void rotate_new(int dim1,pixel *src1, pixel *dst1) {
	// need to figure out 2 different Dim's
	//creates a struct for each segment that is divided
	threadInfo funcInfo0 = {dim1,0,dim1/4,src1,dst1};
	threadInfo funcInfo1 = {dim1,(dim1/4),dim1/2,src1,dst1};
	threadInfo funcInfo2 = {dim1,(dim1/2),((3*dim1)/4),src1,dst1};
	threadInfo funcInfo3 = {dim1,((3*dim1)/4),dim1,src1,dst1};
	//initilizes each thread
	pthread_t thread1,thread2,thread3,thread0;
	//Creates each thread with information
	pthread_create(&thread0,NULL,(void *) threadFunc,(void *) &funcInfo0);
	pthread_create(&thread1,NULL,(void *) threadFunc,(void *) &funcInfo1);
	pthread_create(&thread2,NULL,(void *) threadFunc,(void *) &funcInfo2);
	pthread_create(&thread3,NULL,(void *) threadFunc,(void *) &funcInfo3);
	//joins the threads together
	pthread_join(thread1,NULL);
	pthread_join(thread0,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);


}
char rotate_descr[] = "rotate: Current working version!!!!!!!!!!!";
void rotate(int dim, pixel *src, pixel *dst) 
{
        if(dim >256){
                rotate_new(dim,src,dst);
        } else {
                noThreadFunc(dim,src,dst);
        }
}


/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
	add_rotate_function(&rotate_new,rotate_descr);
	add_rotate_function(&naive_rotate, naive_rotate_descr);   
	add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************;*/
/*
typedef struct {
	int dim;
	int rowB;
	int rowE;
	pixel *src;
	pixel *dst;
	//declare things here
} threadInfo;
*/
void threadSmooth(void * arg) {
        threadInfo x =*(threadInfo *) arg;
        int i,j;
	for (i = x.rowB; i < (x.rowE); i++)
	        for (j = 0; j < (x.dim); j++)
        	   x.dst[RIDX(i, j, x.dim)] = avg(x.dim, i, j, x.src);
}
void new_smooth(int dim, pixel *src, pixel *dst) {
        // need to figure out 2 different Dim's
        //creates a struct for each segment that is divided
        threadInfo smoothInfo0 = {dim,0,(dim/4),src,dst};
        threadInfo smoothInfo1 = {dim,(dim/4),(dim/2),src,dst};
        threadInfo smoothInfo2 = {dim,(dim/2),((3*dim)/4),src,dst};
        threadInfo smoothInfo3 = {dim,((3*dim)/4),dim,src,dst};
        //initilizes each thread
        pthread_t thread1,thread2,thread3,thread0;
        //Creates each thread with information
        pthread_create(&thread0,NULL,(void *) threadSmooth,(void *) &smoothInfo0);
        pthread_create(&thread1,NULL,(void *) threadSmooth,(void *) &smoothInfo1);
        pthread_create(&thread2,NULL,(void *) threadSmooth,(void *) &smoothInfo2);
        pthread_create(&thread3,NULL,(void *) threadSmooth,(void *) &smoothInfo3);
        //joins the threads together
        pthread_join(thread1,NULL);
        pthread_join(thread0,NULL);
        pthread_join(thread2,NULL);
        pthread_join(thread3,NULL);
}

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;
    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}
/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version!!!!!!!!!!!!!!!!";
void smooth(int dim, pixel *src, pixel *dst) 
{
   new_smooth(dim, src, dst);
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

