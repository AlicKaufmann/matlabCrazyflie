/*
 * call_stats_block1.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "call_stats_block1".
 *
 * Model version              : 1.3
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C source code generated on : Fri Dec  8 23:03:40 2017
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "call_stats_block1.h"
#include "call_stats_block1_private.h"

/* Real-time model */
RT_MODEL_call_stats_block1_T call_stats_block1_M_;
RT_MODEL_call_stats_block1_T *const call_stats_block1_M = &call_stats_block1_M_;
real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void call_stats_block1_step(void)
{
  real_T absh;
  real_T t;
  real_T y[2];
  real_T f[14];
  boolean_T MinStepExit;
  boolean_T Done;
  real_T h;
  boolean_T NoFailedAttempts;
  int32_T Bcolidx;
  real_T ystage[2];
  real_T ynew[2];
  int32_T j;
  real_T absxk;
  int32_T exponent;
  real_T c;
  int32_T b_ix;
  real_T b_c;
  int32_T b_iy;
  int32_T b_iac;
  int32_T b_ia;
  int32_T c_c;
  static const real_T x[21] = { 0.2, 0.075, 0.225, 0.97777777777777775,
    -3.7333333333333334, 3.5555555555555554, 2.9525986892242035,
    -11.595793324188385, 9.8228928516994358, -0.29080932784636487,
    2.8462752525252526, -10.757575757575758, 8.9064227177434727,
    0.27840909090909088, -0.2735313036020583, 0.091145833333333329, 0.0,
    0.44923629829290207, 0.65104166666666663, -0.322376179245283,
    0.13095238095238096 };

  static const real_T b_b[7] = { 0.0012326388888888888, 0.0,
    -0.0042527702905061394, 0.036979166666666667, -0.05086379716981132,
    0.0419047619047619, -0.025 };

  int32_T exitg1;
  int32_T exitg2;
  boolean_T exitg3;

  /* MATLAB Function: '<Root>/MATLAB Function' */
  absh = 0.00020095091452076639;
  t = 0.0;
  y[0] = 0.0;
  y[1] = 0.0;
  memset(&f[0], 0, 14U * sizeof(real_T));
  f[0] = 0.0;
  f[1] = 1.0;
  MinStepExit = false;
  Done = false;
  do {
    exitg1 = 0;
    absxk = fabs(t);
    if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
      if (absxk <= 2.2250738585072014E-308) {
        absxk = 4.94065645841247E-324;
      } else {
        frexp(absxk, &exponent);
        absxk = ldexp(1.0, exponent - 53);
      }
    } else {
      absxk = (rtNaN);
    }

    absxk *= 16.0;
    absh = fmin(0.30000000000000004, fmax(absxk, absh));
    h = absh;
    c = fabs(3.0 - t);
    if (1.1 * absh >= c) {
      h = 3.0 - t;
      absh = c;
      Done = true;
    }

    NoFailedAttempts = true;
    do {
      exitg2 = 0;
      Bcolidx = 0;
      for (j = 0; j < 5; j++) {
        Bcolidx += j;
        ystage[0] = y[0];
        ystage[1] = y[1];
        if (!(h == 0.0)) {
          b_ix = Bcolidx;
          c_c = j << 1;
          for (b_iac = 1; b_iac <= c_c + 1; b_iac += 2) {
            b_c = h * x[b_ix];
            b_iy = 0;
            for (b_ia = b_iac; b_ia <= b_iac + 1; b_ia++) {
              ystage[b_iy] += f[b_ia - 1] * b_c;
              b_iy++;
            }

            b_ix++;
          }
        }

        f[(j + 1) << 1] = ystage[1];
        f[1 + ((j + 1) << 1)] = 1.0;
      }

      b_c = t + h;
      if (Done) {
        b_c = 3.0;
      }

      ynew[0] = y[0];
      ynew[1] = y[1];
      if (!(h == 0.0)) {
        for (j = 0; j <= 11; j += 2) {
          c = x[Bcolidx + 5] * h;
          b_ix = 0;
          for (c_c = j; c_c + 1 <= j + 2; c_c++) {
            ynew[b_ix] += f[c_c] * c;
            b_ix++;
          }

          Bcolidx++;
        }
      }

      f[12] = ynew[1];
      f[13] = 1.0;
      for (Bcolidx = 0; Bcolidx < 2; Bcolidx++) {
        h = fabs(y[Bcolidx]);
        c = fabs(ynew[Bcolidx]);
        if ((h > c) || rtIsNaN(c)) {
          h = fmax(h, 0.001);
        } else {
          h = fmax(c, 0.001);
        }

        c = 0.0;
        for (j = 0; j < 7; j++) {
          c += f[(j << 1) + Bcolidx] * b_b[j];
        }

        ystage[Bcolidx] = c / h;
      }

      h = 0.0;
      Bcolidx = 0;
      exitg3 = false;
      while ((!exitg3) && (Bcolidx < 2)) {
        c = fabs(ystage[Bcolidx]);
        if (rtIsNaN(c)) {
          h = (rtNaN);
          exitg3 = true;
        } else {
          if (c > h) {
            h = c;
          }

          Bcolidx++;
        }
      }

      h *= absh;
      if (h > 0.001) {
        if (absh <= absxk) {
          MinStepExit = true;
          exitg2 = 1;
        } else {
          if (NoFailedAttempts) {
            NoFailedAttempts = false;
            absh = fmax(absxk, fmax(0.1, rt_powd_snf(0.001 / h, 0.2) * 0.8) *
                        absh);
          } else {
            absh = fmax(absxk, 0.5 * absh);
          }

          h = absh;
          Done = false;
        }
      } else {
        exitg2 = 1;
      }
    } while (exitg2 == 0);

    if (MinStepExit || Done) {
      exitg1 = 1;
    } else {
      if (NoFailedAttempts) {
        t = rt_powd_snf(h / 0.001, 0.2) * 1.25;
        if (t > 0.2) {
          absh /= t;
        } else {
          absh *= 5.0;
        }
      }

      t = b_c;
      y[0] = ynew[0];
      f[0] = ynew[1];
      y[1] = ynew[1];
      f[1] = 1.0;
    }
  } while (exitg1 == 0);

  /* Matfile logging */
  rt_UpdateTXYLogVars(call_stats_block1_M->rtwLogInfo,
                      (&call_stats_block1_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.2s, 0.0s] */
    if ((rtmGetTFinal(call_stats_block1_M)!=-1) &&
        !((rtmGetTFinal(call_stats_block1_M)-
           call_stats_block1_M->Timing.taskTime0) >
          call_stats_block1_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(call_stats_block1_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++call_stats_block1_M->Timing.clockTick0)) {
    ++call_stats_block1_M->Timing.clockTickH0;
  }

  call_stats_block1_M->Timing.taskTime0 = call_stats_block1_M->Timing.clockTick0
    * call_stats_block1_M->Timing.stepSize0 +
    call_stats_block1_M->Timing.clockTickH0 *
    call_stats_block1_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void call_stats_block1_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)call_stats_block1_M, 0,
                sizeof(RT_MODEL_call_stats_block1_T));
  rtmSetTFinal(call_stats_block1_M, 10.0);
  call_stats_block1_M->Timing.stepSize0 = 0.2;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    call_stats_block1_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(call_stats_block1_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(call_stats_block1_M->rtwLogInfo, (NULL));
    rtliSetLogT(call_stats_block1_M->rtwLogInfo, "tout");
    rtliSetLogX(call_stats_block1_M->rtwLogInfo, "");
    rtliSetLogXFinal(call_stats_block1_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(call_stats_block1_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(call_stats_block1_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(call_stats_block1_M->rtwLogInfo, 0);
    rtliSetLogDecimation(call_stats_block1_M->rtwLogInfo, 1);
    rtliSetLogY(call_stats_block1_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(call_stats_block1_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(call_stats_block1_M->rtwLogInfo, (NULL));
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(call_stats_block1_M->rtwLogInfo, 0.0,
    rtmGetTFinal(call_stats_block1_M), call_stats_block1_M->Timing.stepSize0,
    (&rtmGetErrorStatus(call_stats_block1_M)));
}

/* Model terminate function */
void call_stats_block1_terminate(void)
{
  /* (no terminate code required) */
}
