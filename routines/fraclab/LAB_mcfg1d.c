/* This Software is ( Copyright INRIA . 1998  1 )                    */
/*                                                                   */
/* INRIA  holds all the ownership rights on the Software.            */
/* The scientific community is asked to use the SOFTWARE             */
/* in order to test and evaluate it.                                 */
/*                                                                   */
/* INRIA freely grants the right to use modify the Software,         */
/* integrate it in another Software.                                 */
/* Any use or reproduction of this Software to obtain profit or      */
/* for commercial ends being subject to obtaining the prior express  */
/* authorization of INRIA.                                           */
/*                                                                   */
/* INRIA authorizes any reproduction of this Software.               */
/*                                                                   */
/*    - in limits defined in clauses 9 and 10 of the Berne           */
/*    agreement for the protection of literary and artistic works    */
/*    respectively specify in their paragraphs 2 and 3 authorizing   */
/*    only the reproduction and quoting of works on the condition    */
/*    that :                                                         */
/*                                                                   */
/*    - "this reproduction does not adversely affect the normal      */
/*    exploitation of the work or cause any unjustified prejudice    */
/*    to the legitimate interests of the author".                    */
/*                                                                   */
/*    - that the quotations given by way of illustration and/or      */
/*    tuition conform to the proper uses and that it mentions        */
/*    the source and name of the author if this name features        */
/*    in the source",                                                */
/*                                                                   */
/*    - under the condition that this file is included with          */
/*    any reproduction.                                              */
/*                                                                   */
/* Any commercial use made without obtaining the prior express       */
/* agreement of INRIA would therefore constitute a fraudulent        */
/* imitation.                                                        */
/*                                                                   */
/* The Software beeing currently developed, INRIA is assuming no     */
/* liability, and should not be responsible, in any manner or any    */
/* case, for any direct or indirect dammages sustained by the user.  */
/*                                                                   */
/* Any user of the software shall notify at INRIA any comments       */
/* concerning the use of the Sofware (e-mail : FracLab@inria.fr)     */
/*                                                                   */
/* This file is part of FracLab, a Fractal Analysis Software         */

/* Christophe Canus 1997-98 */

#include "C-LAB_Interf.h"
#include "MFAG_continuous.h"

/************  LAB_mcfg1d  ***************************************************/

void LAB_mcfg1d()
{ 
  /* input parameters */
  short J=1,N=100;
  int N_n=256,M=N_n;
  double S_min=1.,S_max=1.;
  MFAMt_prog t_prog=MFAM_LOG; 
  MFAMt_ball t_ball=MFAM_ASYMMETRIC;
  MFAGt_adap t_adap=MFAG_MAXDEV;
  MFAGt_cont t_cont=MFAG_HORIKERN;
  MFAMt_kern t_kern=MFAM_GAUSSIAN;
  MFAGt_norm t_norm=MFAG_SUPPDF;
  /* input measure */
  double* I_n=NULL;
  double* mu_n=NULL;
  /* input precisions */
  double* epsilon=NULL;
  /* output Hoelder exponents, pdfs & spectra */
  double* alpha=NULL;
  double* pc_alpha=NULL;
  double* fgc_alpha=NULL;
  /* output optimal precisions, scales, abscissa & coarse Hoelder exponents */ 
  double* epsilon_star=NULL;
  double* eta=NULL;
  double* x=NULL;
  double* alpha_eta_x=NULL;

  /* Matrix */
  Matrix* MI_n;
  Matrix* Mmu_n;  
  Matrix* Mprogstr;
  Matrix* Mballstr;  
  Matrix* MS_min_S_max_J;
  Matrix* Mcontstr;
  Matrix* Madapstr;
  Matrix* Mepsilon;
  Matrix* Mkernstr;
  Matrix* Mnormstr;
  Matrix* MN;
  Matrix* Malpha;
  Matrix* Mpc_alpha;
  Matrix* Mfgc_alpha;
  Matrix* Mepsilon_star;
  Matrix* Meta;
  Matrix* Malpha_eta_x;

  /* Check the input arguments number */
  if(Interf.NbParamIn<1) 
  {
    InterfError("mcfg1d: You must give at least 1 input arguments\n");
    return;
  }
  if(Interf.NbParamIn>10) 
  {
    InterfError("mcfg1d: You must give at most 10 input arguments\n");
    return;
  }

  /* Check the output arguments number */ 
  if(Interf.NbParamOut<2) 
  {
    InterfError("mcfg1d: You must give at least 2 output arguments\n");
    return;
  }
  if(Interf.NbParamOut>6) 
  {
    InterfError("mcfg1d: You must give at most 6 output arguments\n");
    return;
  }
  
  /* Get the input measure: mu_n and verify it */
  Mmu_n=Interf.Param[0];
  if(!MatrixIsNumeric(Mmu_n))
  {
    InterfError("mcfg1d: The measure: mu_n must be a numeric matrix\n");
    return;
  }
  if(!MatrixIsReal(Mmu_n))
  {
    InterfError("mcfg1d: The measure: mu_n must be a real matrix\n");
    return;
  }
  /* Get the input argument */  
  mu_n=(double*)MatrixGetPr(Mmu_n);
  /* Get the size of the input argument */ 
  M=N_n=(int)MAX(MatrixGetWidth(Mmu_n),MatrixGetHeight(Mmu_n));
  if(N_n<1)
  {
    InterfError("mcfg1d: The size of measure: mu_n must be >=1\n");
    return;
  }

  if(Interf.NbParamIn>1) 
  {
    /* Get the input minimal size: S_min, maximal size: S_max & # of scales: J and verify them */
    MS_min_S_max_J=Interf.Param[1];
    if(!MatrixIsNumeric(MS_min_S_max_J))
    {
      InterfError("mcfg1d: The vector: [S_min S_max J] must be a numeric matrix\n");
      return;
    }
    if(!MatrixIsReal(MS_min_S_max_J))
    {
      InterfError("mcfg1d: The vector: [S_min S_max J] must be a real matrix\n");
      return;
    }
    if(((int)MAX(MatrixGetWidth(MS_min_S_max_J),MatrixGetHeight(MS_min_S_max_J)))!=3)
    {
      InterfError("mcfg1d: The vector: [S_min S_max J] is illegal\n");
      return;
    } 
    /* Get the input argument */
    S_min=*(MatrixGetPr(MS_min_S_max_J));
    if(S_min<1.)
    {
      InterfError("mcfg1d: The minimum size: S_min must be >=1.\n");
      return;
    } 
    S_max=*(MatrixGetPr(MS_min_S_max_J)+1); 
    if(S_max<S_min)
    {
      InterfError("mcfg1d: The maximum size: S_max must be >=S_min\n");
      return;
    } 
    J=(short)*(MatrixGetPr(MS_min_S_max_J)+2); 
    if(J<1)
    {
      InterfError("mcfg1d: The # of scales: J must be >=1\n");
      return;
    } 
  }

  if(Interf.NbParamIn>2)
  {  
    /* Get the input string: progstr and verify it */
    Mprogstr=Interf.Param[2];
    if(!MatrixIsString(Mprogstr))
    {
      InterfError("mcfg1d: The string: progstr must be a string\n");
      return;
    }
    /* Get the input argument */
    if(MFAM_progstr(MatrixReadString(Mprogstr),&t_prog)==0)
    {
      InterfError("mcfg1d: The string: progstr is illegal\n");
      return;
    }
  }

  if(Interf.NbParamIn>3)
  {  
    /* Get the input string: ballstr and verify it */
    Mballstr=Interf.Param[3];
    if(!MatrixIsString(Mballstr))
    {
      InterfError("mcfg1d: The string: ballstr must be a string\n");
      return;
    }
    /* Get the input argument */
    if(MFAM_ballstr(MatrixReadString(Mballstr),&t_ball)==0)
    {
      InterfError("mcfg1d: The string: ballstr is illegal\n");
      return;
    }
  }
  
  if(Interf.NbParamIn>4)
  { 
    /* Get the input # of Hoelder exponents: N and verify it */
    MN=Interf.Param[4];
    if(!MatrixIsNumeric(MN))
    {
      InterfError("mcfg1d: The # of Hoelder exponents: N  must be a numeric matrix\n");
      return;
    }  
    if(!MatrixIsScalar(MN))
    {
      InterfError("mcfg1d: The # of Hoelder exponents: N  must be a scalar\n");
      return;
    }
    /* Get the input argument */
    N=(int)MatrixGetScalar(MN);
    if(N<1)
    {
      InterfError("mcfg1d: The # of Hoelder exponents: N must be >=1\n");
      return;
    }
  }

  if(Interf.NbParamIn>5)
  { 
    /* Get the input precision epsilon and verify it */
    Mepsilon=Interf.Param[5];
    if(!MatrixIsNumeric(Mepsilon))
    {
      InterfError("mcfg1d: The precision: epsilon must be a numeric matrix\n");
      return;
    } 
    if(!MatrixIsReal(Mepsilon))
    {
      InterfError("mcfg1d: The precision: epsilon must be a real matrix\n");
      return;
    }
    /* Get the input argument */  
    epsilon=(double*)MatrixGetPr(Mepsilon);
    /* Get the size of the input argument */ 
    if(((int)MAX(MatrixGetWidth(Mepsilon),MatrixGetHeight(Mepsilon)))!=N)
    {
      InterfError("mcfg1d: The size of the precision: epsilon must be N\n");
      return;
    }  
  }
  else
  {
    /* dynamic memory allocation */
    if((epsilon=(double*)malloc((unsigned)(N*sizeof(double))))==NULL)
    {
      InterfError("mcfg1d: malloc error\n"); 
      return;
    }
  }
   
  if(Interf.NbParamIn>6)
  { 
    /* Get the input string: contstr and verify it */
    Mcontstr=Interf.Param[6];
    if(!MatrixIsString(Mcontstr))
    {
      InterfError("mcfg1d: The string: contstr must be a string\n");
      return;
    }
    /* Get the input argument */
    if(MFAG_contstr(MatrixReadString(Mcontstr),&t_cont)==0)
    {
      InterfError("mcfg1d: The string: contstr is illegal\n");
      return;
    }
  }

  if(Interf.NbParamIn>7)
  { 
    /* Get the input string: adapstr and verify it */
    Madapstr=Interf.Param[7];
    if(!MatrixIsString(Madapstr))
    {
      InterfError("mcfg1d: The string: adapstr must be a string\n");
      return;
    }
    /* Get the input argument */
    if(MFAG_adapstr(MatrixReadString(Madapstr),&t_adap)==0)
    {
      InterfError("mcfg1d: The string: adapstr is illegal\n");
      return;
    }
  }

  if(Interf.NbParamIn>8)
  { 
    /* Get the input string: kernstr and verify it */
    Mkernstr=Interf.Param[8];
    if(!MatrixIsString(Mkernstr))
    {
      InterfError("mcfg1d: The string: kernstr must be a string\n");
      return;
    }
    /* Get the input argument */
    if(MFAM_kernelstr(MatrixReadString(Mkernstr),&t_kern)==0)
    {
      InterfError("mcfg1d: The string: kernstr is illegal\n");
      return;
    }
  }

  if(Interf.NbParamIn>9)
  { 
    /* Get the input string: normstr and verify it */
    Mnormstr=Interf.Param[9];
    if(!MatrixIsString(Mnormstr))
    {
      InterfError("mcfg1d: The string: normstr must be a string\n");
      return;
    }
    /* Get the input argument */
    if(MFAG_normstr(MatrixReadString(Mnormstr),&t_norm)==0)
    {
      InterfError("mcfg1d: The string: normstr is illegal\n");
      return;
    }
  }

  /* Create the output Matrix */ 
  Meta=MatrixCreate(1,J,"real");  
  Malpha_eta_x=MatrixCreate(M,J,"real");
  Malpha=MatrixCreate(1,N,"real");
  Mfgc_alpha=MatrixCreate(N,J,"real"); 
  Mpc_alpha=MatrixCreate(N,J,"real");   
  Mepsilon_star=MatrixCreate(N,J,"real");  

  /* Get the pointer on the output Matrix */ 
  eta=MatrixGetPr(Meta);
  alpha_eta_x=MatrixGetPr(Malpha_eta_x);  
  alpha=MatrixGetPr(Malpha);  
  fgc_alpha=MatrixGetPr(Mfgc_alpha);  
  pc_alpha=MatrixGetPr(Mpc_alpha);
  epsilon_star=MatrixGetPr(Mepsilon_star);

  /* Call of the C function */ 
  if(MFAG_mcfg1d(N_n,I_n,mu_n,S_min,S_max,J,t_prog,t_ball,eta,M,x,alpha_eta_x,N,epsilon,t_cont,t_adap,t_kern,t_norm,alpha,pc_alpha,fgc_alpha,epsilon_star)==0)
  {
    InterfError("mcfg1d: Call of the C function MFAG_mcfg1d failed\n");
    return;
  }   

  /* Transpose output argument */
  MatrixTranspose(Mfgc_alpha); 
  MatrixTranspose(Mpc_alpha);
  MatrixTranspose(Mepsilon_star);
  MatrixTranspose(Malpha_eta_x);

  /* Return the output */
  ReturnParam(Malpha);
  ReturnParam(Mfgc_alpha);
  if(Interf.NbParamOut>2) 
    ReturnParam(Mpc_alpha);
  else
    MatrixFree(Mpc_alpha);
  if(Interf.NbParamOut>3)
    ReturnParam(Mepsilon_star);
  else
    MatrixFree(Mepsilon_star);
  if(Interf.NbParamOut>4) 
    ReturnParam(Meta);
  else
    MatrixFree(Meta); 
  if(Interf.NbParamOut>5) 
    ReturnParam(Malpha_eta_x);
  else
    MatrixFree(Malpha_eta_x);
}


