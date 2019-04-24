#ifndef __FUZZYLOGIC_H__
#define __FUZZYLOGIC_H__

#include <math.h>
#include <set>
#include <stack>
#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>

using namespace std;

/////////////////////////////////////////////////////

#define MAX_NO_OF_INPUTS 6 //[PF] X and Y have 6 inputs
#define MAX_NO_OF_INP_REGIONS 5
#define MAX_NO_OF_OUTPUT_VALUES 7 //[PF] (NM / ZR / PM / NS / PS / PL / NL)

#define TOO_SMALL 1e-6

//Constants for Yamakawas formulas
#define A 5
#define B 1
#define C 2
#define D 1
#define theta 0.5
#define thetaDot 0.5
#define x_ 1
#define xDot 1

//Force applied constant
#define force 300

//Trapezoidal membership function types
typedef enum
{
   regular_trapezoid,
   left_trapezoid,
   right_trapezoid
} trapz_type;

//Input parameters -//[PF] X & Y added
enum
{
   in_theta,
   in_theta_dot,
   in_x,
   in_x_dot,
   X,
   Y
};

//Fuzzy sets //[PF] (5: NM / ZR / PM / NS / PS ) Angle AND Position
enum
{
   in_nm,
   in_ns,
   in_zr,
   in_ps,
   in_pm
};

//Fuzzy output terms //[PF] (7: NM / ZR / PM / NS / PS / PL /NL) Angle AND Speed
enum
{
   out_nl,
   out_nm,
   out_ns,
   out_zr,
   out_ps,
   out_pm,
   out_pl
};

//Trapeziod
typedef struct
{
   trapz_type tp;                      //Type of trapexiod
   float a, b, c, d, l_slope, r_slope; //Parameters
} trapezoid;

//Fuzzy rule
typedef struct
{
   short inp_index[MAX_NO_OF_INPUTS],   //Input index
       inp_fuzzy_set[MAX_NO_OF_INPUTS], //Input fuzzy set index
       out_fuzzy_set;                   //Output index
} rule;

//Complete fuzzy system
//Zero - order Sugeno Fuzzy Inference system
typedef struct
{
   bool allocated;
   trapezoid inp_mem_fns[MAX_NO_OF_INPUTS][MAX_NO_OF_INP_REGIONS];
   rule *rules;                                  //Allocate memory for the rules
   int no_of_inputs,                             //Number of inputs
       no_of_inp_regions,                        //Number of fuzzy sets associated with each input
       no_of_rules,                              //Number of rules
       no_of_outputs;                            //Number of fuzzy outputs
   float output_values[MAX_NO_OF_OUTPUT_VALUES]; //Value of the outputs
} fuzzy_system_rec;

extern fuzzy_system_rec g_fuzzy_system;

//---------------------------------------------------------------------------

trapezoid init_trapz(float x1, float x2, float x3, float x4, trapz_type typ);
float fuzzy_system(float inputs[], fuzzy_system_rec fl);
void free_fuzzy_rules(fuzzy_system_rec *fz);

//-------------------------------------------------------------------------
void initFuzzyRules(fuzzy_system_rec *fl);
void initMembershipFunctions(fuzzy_system_rec *fl);
void initFuzzySystem(fuzzy_system_rec *fl);

trapezoid init_trapz(float x1, float x2, float x3, float x4, trapz_type typ);
float trapz(float x, trapezoid trz);
float min_of(float values[], int no_of_inps);
float fuzzy_system(float inputs[], fuzzy_system_rec fz);
void free_fuzzy_rules(fuzzy_system_rec *fz);

#endif
