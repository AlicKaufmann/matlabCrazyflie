/* Include files */

#include "call_stats_block1_sfun.h"
#include "c2_call_stats_block1.h"
#include <math.h>
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "call_stats_block1_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[7] = { "s", "tf", "t", "nargin",
  "nargout", "x", "w" };

static const char * c2_b_debug_family_names[9] = { "uTrans", "uTransTime",
  "uRot", "uRotTime", "nargin", "nargout", "t", "s", "ds" };

static emlrtRTEInfo c2_emlrtRTEI = { 7,/* lineNo */
  8,                                   /* colNo */
  "MATLAB Function",                   /* fName */
  "#call_stats_block1:29"              /* pName */
};

static emlrtRTEInfo c2_b_emlrtRTEI = { 17,/* lineNo */
  1,                                   /* colNo */
  "ode45",                             /* fName */
  "/usr/local/MATLAB/R2017b/toolbox/eml/lib/matlab/funfun/ode45.m"/* pName */
};

static const real_T c2_dv0[21] = { 0.2, 0.075, 0.225, 0.97777777777777775,
  -3.7333333333333334, 3.5555555555555554, 2.9525986892242035,
  -11.595793324188385, 9.8228928516994358, -0.29080932784636487,
  2.8462752525252526, -10.757575757575758, 8.9064227177434727,
  0.27840909090909088, -0.2735313036020583, 0.091145833333333329, 0.0,
  0.44923629829290207, 0.65104166666666663, -0.322376179245283,
  0.13095238095238096 };

/* Function Declarations */
static void initialize_c2_call_stats_block1(SFc2_call_stats_block1InstanceStruct
  *chartInstance);
static void initialize_params_c2_call_stats_block1
  (SFc2_call_stats_block1InstanceStruct *chartInstance);
static void enable_c2_call_stats_block1(SFc2_call_stats_block1InstanceStruct
  *chartInstance);
static void disable_c2_call_stats_block1(SFc2_call_stats_block1InstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_call_stats_block1
  (SFc2_call_stats_block1InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_call_stats_block1
  (SFc2_call_stats_block1InstanceStruct *chartInstance);
static void set_sim_state_c2_call_stats_block1
  (SFc2_call_stats_block1InstanceStruct *chartInstance, const mxArray *c2_st);
static void finalize_c2_call_stats_block1(SFc2_call_stats_block1InstanceStruct
  *chartInstance);
static void sf_gateway_c2_call_stats_block1(SFc2_call_stats_block1InstanceStruct
  *chartInstance);
static void mdl_start_c2_call_stats_block1(SFc2_call_stats_block1InstanceStruct *
  chartInstance);
static void c2_chartstep_c2_call_stats_block1
  (SFc2_call_stats_block1InstanceStruct *chartInstance);
static void initSimStructsc2_call_stats_block1
  (SFc2_call_stats_block1InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_c_x, const char_T *c2_identifier, real_T
  c2_y[6]);
static void c2_b_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[6]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, real_T
  c2_inData_data[], int32_T c2_inData_size[2]);
static void c2_d_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y_data[], int32_T c2_y_size[2]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, real_T c2_outData_data[], int32_T
  c2_outData_size[2]);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_e_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[600]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_ode45(SFc2_call_stats_block1InstanceStruct *chartInstance, real_T
                     c2_y0[6], real_T c2_varargout_1_data[], int32_T
                     c2_varargout_1_size[1], real_T c2_varargout_2_data[],
                     int32_T c2_varargout_2_size[2]);
static void c2_callODEFunctionNSM(SFc2_call_stats_block1InstanceStruct
  *chartInstance, real_T c2_t, real_T c2_y[6], real_T c2_yp[6]);
static real_T c2_interp1(SFc2_call_stats_block1InstanceStruct *chartInstance,
  real_T c2_varargin_1[10], real_T c2_varargin_2[10], real_T c2_varargin_3);
static void c2_error(SFc2_call_stats_block1InstanceStruct *chartInstance);
static void c2_b_error(SFc2_call_stats_block1InstanceStruct *chartInstance);
static void c2_abs(SFc2_call_stats_block1InstanceStruct *chartInstance, real_T
                   c2_c_x[6], real_T c2_y[6]);
static real_T c2_norm(SFc2_call_stats_block1InstanceStruct *chartInstance,
                      real_T c2_c_x[6]);
static void c2_c_error(SFc2_call_stats_block1InstanceStruct *chartInstance);
static real_T c2_eps(SFc2_call_stats_block1InstanceStruct *chartInstance, real_T
                     c2_c_x);
static void c2_xgemv(SFc2_call_stats_block1InstanceStruct *chartInstance,
                     int32_T c2_n, real_T c2_alpha1, real_T c2_A[42], int32_T
                     c2_ix0, real_T c2_y[6], real_T c2_b_y[6]);
static void c2_b_xgemv(SFc2_call_stats_block1InstanceStruct *chartInstance,
  real_T c2_alpha1, real_T c2_A[42], int32_T c2_ix0, real_T c2_y[6], real_T
  c2_b_y[6]);
static void c2_maxAbsThresh(SFc2_call_stats_block1InstanceStruct *chartInstance,
  real_T c2_a[6], real_T c2_b[6], real_T c2_thresh, real_T c2_y[6]);
static void c2_warning(SFc2_call_stats_block1InstanceStruct *chartInstance,
  char_T c2_varargin_1[23], char_T c2_varargin_2[23]);
static void c2_ntrp45(SFc2_call_stats_block1InstanceStruct *chartInstance,
                      real_T c2_t, real_T c2_t0, real_T c2_y0[6], real_T c2_h,
                      real_T c2_f[42], real_T c2_y[6]);
static void c2_f_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_sprintf, const char_T *c2_identifier, char_T
  c2_y[23]);
static void c2_g_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  char_T c2_y[23]);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_h_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_i_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_call_stats_block1, const
  char_T *c2_identifier);
static uint8_T c2_j_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_xgemv(SFc2_call_stats_block1InstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_alpha1, real_T c2_A[42], int32_T c2_ix0, real_T c2_y[6]);
static void c2_d_xgemv(SFc2_call_stats_block1InstanceStruct *chartInstance,
  real_T c2_alpha1, real_T c2_A[42], int32_T c2_ix0, real_T c2_y[6]);
static void init_dsm_address_info(SFc2_call_stats_block1InstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc2_call_stats_block1InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_call_stats_block1(SFc2_call_stats_block1InstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc2_call_stats_block1(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_call_stats_block1 = 0U;
}

static void initialize_params_c2_call_stats_block1
  (SFc2_call_stats_block1InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_call_stats_block1(SFc2_call_stats_block1InstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_call_stats_block1(SFc2_call_stats_block1InstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_call_stats_block1
  (SFc2_call_stats_block1InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_call_stats_block1
  (SFc2_call_stats_block1InstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  const mxArray *c2_b_y = NULL;
  uint8_T c2_hoistedGlobal;
  const mxArray *c2_c_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(2, 1), false);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", *chartInstance->c2_b_x, 0, 0U, 1U,
    0U, 1, 6), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_call_stats_block1;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_hoistedGlobal, 3, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_call_stats_block1
  (SFc2_call_stats_block1InstanceStruct *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv1[6];
  int32_T c2_i0;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "x",
                      c2_dv1);
  for (c2_i0 = 0; c2_i0 < 6; c2_i0++) {
    (*chartInstance->c2_b_x)[c2_i0] = c2_dv1[c2_i0];
  }

  chartInstance->c2_is_active_c2_call_stats_block1 = c2_i_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
     "is_active_c2_call_stats_block1");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_call_stats_block1(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_call_stats_block1(SFc2_call_stats_block1InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_call_stats_block1(SFc2_call_stats_block1InstanceStruct
  *chartInstance)
{
  int32_T c2_i1;
  int32_T c2_i2;
  int32_T c2_i3;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i1 = 0; c2_i1 < 6; c2_i1++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_w)[c2_i1], 1U);
  }

  for (c2_i2 = 0; c2_i2 < 6; c2_i2++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_x)[c2_i2], 0U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_call_stats_block1(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_call_stats_block1MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c2_i3 = 0; c2_i3 < 6; c2_i3++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_b_x)[c2_i3], 2U);
  }
}

static void mdl_start_c2_call_stats_block1(SFc2_call_stats_block1InstanceStruct *
  chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void c2_chartstep_c2_call_stats_block1
  (SFc2_call_stats_block1InstanceStruct *chartInstance)
{
  int32_T c2_i4;
  int32_T c2_i5;
  real_T c2_c_x[6];
  uint32_T c2_debug_family_var_map[7];
  real_T c2_b_w[6];
  real_T c2_s[600];
  real_T c2_tf;
  real_T c2_t[100];
  real_T c2_s_data[600];
  int32_T c2_s_size[2];
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  real_T c2_d_x[6];
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  real_T c2_e_x[6];
  real_T c2_unusedU0_data[100];
  int32_T c2_unusedU0_size[1];
  real_T c2_b_s_data[600];
  int32_T c2_b_s_size[2];
  int32_T c2_b_s;
  int32_T c2_c_s;
  int32_T c2_loop_ub;
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i4 = 0; c2_i4 < 6; c2_i4++) {
    c2_c_x[c2_i4] = (*chartInstance->c2_x)[c2_i4];
  }

  for (c2_i5 = 0; c2_i5 < 6; c2_i5++) {
    c2_b_w[c2_i5] = (*chartInstance->c2_w)[c2_i5];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 7U, 9U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_s, MAX_uint32_T, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_tf, 1U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_t, 2U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_EMX_IMPORTABLE((void *)&c2_s_data, (const
    int32_T *)&c2_s_size, NULL, 0, -1, (void *)c2_c_sf_marshallOut, (void *)
    c2_c_sf_marshallIn, (void *)&c2_s_data, false);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 3U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 4U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_c_x, 5U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_w, 6U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_d_x, MAX_uint32_T, c2_sf_marshallOut,
    c2_sf_marshallIn);
  for (c2_i6 = 0; c2_i6 < 6; c2_i6++) {
    c2_d_x[c2_i6] = c2_c_x[c2_i6];
  }

  _SFD_SYMBOL_SWITCH(5U, 8U);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  for (c2_i7 = 0; c2_i7 < 600; c2_i7++) {
    c2_s[c2_i7] = 0.0;
  }

  _SFD_SYMBOL_SWITCH(0U, 0U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  c2_tf = 3.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  for (c2_i8 = 0; c2_i8 < 100; c2_i8++) {
    c2_t[c2_i8] = 0.030303030303030304 * (real_T)c2_i8;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
  for (c2_i9 = 0; c2_i9 < 6; c2_i9++) {
    c2_e_x[c2_i9] = c2_d_x[c2_i9];
  }

  c2_ode45(chartInstance, c2_e_x, c2_unusedU0_data, c2_unusedU0_size,
           c2_b_s_data, c2_b_s_size);
  c2_s_size[0] = c2_b_s_size[0];
  c2_s_size[1] = 6;
  c2_b_s = c2_s_size[0];
  c2_c_s = c2_s_size[1];
  c2_loop_ub = c2_b_s_size[0] * c2_b_s_size[1] - 1;
  for (c2_i10 = 0; c2_i10 <= c2_loop_ub; c2_i10++) {
    c2_s_data[c2_i10] = c2_b_s_data[c2_i10];
  }

  _SFD_SYMBOL_SWITCH(0U, 3U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
    chartInstance->S, 1U, 197, 3, MAX_uint32_T, 100, 1, c2_s_size[0]);
  for (c2_i11 = 0; c2_i11 < 6; c2_i11++) {
    c2_d_x[c2_i11] = c2_s_data[99 + c2_s_size[0] * c2_i11];
  }

  _SFD_SYMBOL_SWITCH(5U, 8U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -8);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i12 = 0; c2_i12 < 6; c2_i12++) {
    (*chartInstance->c2_b_x)[c2_i12] = c2_d_x[c2_i12];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_call_stats_block1
  (SFc2_call_stats_block1InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)(c2_machineNumber);
  (void)(c2_chartNumber);
  (void)(c2_instanceNumber);
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, c2_instanceNumber, 0U,
    sf_debug_get_script_id(
    "/home/alic/Documents/MATLAB/crazyflie/identification/src/stateTransition.m"));
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i13;
  const mxArray *c2_y = NULL;
  real_T c2_u[6];
  SFc2_call_stats_block1InstanceStruct *chartInstance;
  chartInstance = (SFc2_call_stats_block1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i13 = 0; c2_i13 < 6; c2_i13++) {
    c2_u[c2_i13] = (*(real_T (*)[6])c2_inData)[c2_i13];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_c_x, const char_T *c2_identifier, real_T
  c2_y[6])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_c_x), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_c_x);
}

static void c2_b_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[6])
{
  real_T c2_dv2[6];
  int32_T c2_i14;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv2, 1, 0, 0U, 1, 0U, 1, 6);
  for (c2_i14 = 0; c2_i14 < 6; c2_i14++) {
    c2_y[c2_i14] = c2_dv2[c2_i14];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_c_x;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[6];
  int32_T c2_i15;
  SFc2_call_stats_block1InstanceStruct *chartInstance;
  chartInstance = (SFc2_call_stats_block1InstanceStruct *)chartInstanceVoid;
  c2_c_x = sf_mex_dup(c2_mxArrayInData);
  c2_thisId.fIdentifier = (const char *)c2_varName;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_c_x), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_c_x);
  for (c2_i15 = 0; c2_i15 < 6; c2_i15++) {
    (*(real_T (*)[6])c2_outData)[c2_i15] = c2_y[c2_i15];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_call_stats_block1InstanceStruct *chartInstance;
  chartInstance = (SFc2_call_stats_block1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_call_stats_block1InstanceStruct *chartInstance;
  chartInstance = (SFc2_call_stats_block1InstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_thisId.fIdentifier = (const char *)c2_varName;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, real_T
  c2_inData_data[], int32_T c2_inData_size[2])
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_u_size[2];
  int32_T c2_u;
  int32_T c2_b_u;
  int32_T c2_loop_ub;
  int32_T c2_i16;
  const mxArray *c2_y = NULL;
  real_T c2_u_data[600];
  SFc2_call_stats_block1InstanceStruct *chartInstance;
  chartInstance = (SFc2_call_stats_block1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_u_size[0] = c2_inData_size[0];
  c2_u_size[1] = 6;
  c2_u = c2_u_size[0];
  c2_b_u = c2_u_size[1];
  c2_loop_ub = c2_inData_size[0] * c2_inData_size[1] - 1;
  for (c2_i16 = 0; c2_i16 <= c2_loop_ub; c2_i16++) {
    c2_u_data[c2_i16] = c2_inData_data[c2_i16];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", (void *)&c2_u_data, 0, 0U, 1U, 0U, 2,
    c2_u_size[0], c2_u_size[1]), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_d_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y_data[], int32_T c2_y_size[2])
{
  int32_T c2_i17;
  int32_T c2_tmp_size[2];
  uint32_T c2_uv0[2];
  int32_T c2_i18;
  real_T c2_tmp_data[600];
  boolean_T c2_bv0[2];
  static boolean_T c2_bv1[2] = { true, false };

  int32_T c2_y;
  int32_T c2_b_y;
  int32_T c2_loop_ub;
  int32_T c2_i19;
  (void)chartInstance;
  for (c2_i17 = 0; c2_i17 < 2; c2_i17++) {
    c2_uv0[c2_i17] = 100U + (uint32_T)(-94 * c2_i17);
  }

  c2_tmp_size[0] = sf_mex_get_dimension(c2_u, 0);
  c2_tmp_size[1] = sf_mex_get_dimension(c2_u, 1);
  for (c2_i18 = 0; c2_i18 < 2; c2_i18++) {
    c2_bv0[c2_i18] = c2_bv1[c2_i18];
  }

  sf_mex_import_vs(c2_parentId, sf_mex_dup(c2_u), (void *)&c2_tmp_data, 1, 0, 0U,
                   1, 0U, 2, c2_bv0, c2_uv0, c2_tmp_size);
  c2_y_size[0] = c2_tmp_size[0];
  c2_y_size[1] = 6;
  c2_y = c2_y_size[0];
  c2_b_y = c2_y_size[1];
  c2_loop_ub = c2_tmp_size[0] * c2_tmp_size[1] - 1;
  for (c2_i19 = 0; c2_i19 <= c2_loop_ub; c2_i19++) {
    c2_y_data[c2_i19] = c2_tmp_data[c2_i19];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, real_T c2_outData_data[], int32_T
  c2_outData_size[2])
{
  const mxArray *c2_s;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y_data[600];
  int32_T c2_y_size[2];
  int32_T c2_i20;
  int32_T c2_loop_ub;
  int32_T c2_i21;
  SFc2_call_stats_block1InstanceStruct *chartInstance;
  chartInstance = (SFc2_call_stats_block1InstanceStruct *)chartInstanceVoid;
  c2_s = sf_mex_dup(c2_mxArrayInData);
  c2_thisId.fIdentifier = (const char *)c2_varName;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_s), &c2_thisId, c2_y_data,
                        c2_y_size);
  sf_mex_destroy(&c2_s);
  c2_outData_size[0] = c2_y_size[0];
  c2_outData_size[1] = 6;
  for (c2_i20 = 0; c2_i20 < 6; c2_i20++) {
    c2_loop_ub = c2_y_size[0] - 1;
    for (c2_i21 = 0; c2_i21 <= c2_loop_ub; c2_i21++) {
      c2_outData_data[c2_i21 + c2_outData_size[0] * c2_i20] = c2_y_data[c2_i21 +
        c2_y_size[0] * c2_i20];
    }
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i22;
  const mxArray *c2_y = NULL;
  real_T c2_u[100];
  SFc2_call_stats_block1InstanceStruct *chartInstance;
  chartInstance = (SFc2_call_stats_block1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i22 = 0; c2_i22 < 100; c2_i22++) {
    c2_u[c2_i22] = (*(real_T (*)[100])c2_inData)[c2_i22];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 100), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i23;
  int32_T c2_i24;
  const mxArray *c2_y = NULL;
  int32_T c2_i25;
  real_T c2_u[600];
  SFc2_call_stats_block1InstanceStruct *chartInstance;
  chartInstance = (SFc2_call_stats_block1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_i23 = 0;
  for (c2_i24 = 0; c2_i24 < 6; c2_i24++) {
    for (c2_i25 = 0; c2_i25 < 100; c2_i25++) {
      c2_u[c2_i25 + c2_i23] = (*(real_T (*)[600])c2_inData)[c2_i25 + c2_i23];
    }

    c2_i23 += 100;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 100, 6), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[600])
{
  real_T c2_dv3[600];
  int32_T c2_i26;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv3, 1, 0, 0U, 1, 0U, 2, 100,
                6);
  for (c2_i26 = 0; c2_i26 < 600; c2_i26++) {
    c2_y[c2_i26] = c2_dv3[c2_i26];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_s;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[600];
  int32_T c2_i27;
  int32_T c2_i28;
  int32_T c2_i29;
  SFc2_call_stats_block1InstanceStruct *chartInstance;
  chartInstance = (SFc2_call_stats_block1InstanceStruct *)chartInstanceVoid;
  c2_s = sf_mex_dup(c2_mxArrayInData);
  c2_thisId.fIdentifier = (const char *)c2_varName;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_s), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_s);
  c2_i27 = 0;
  for (c2_i28 = 0; c2_i28 < 6; c2_i28++) {
    for (c2_i29 = 0; c2_i29 < 100; c2_i29++) {
      (*(real_T (*)[600])c2_outData)[c2_i29 + c2_i27] = c2_y[c2_i29 + c2_i27];
    }

    c2_i27 += 100;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i30;
  const mxArray *c2_y = NULL;
  real_T c2_u[10];
  SFc2_call_stats_block1InstanceStruct *chartInstance;
  chartInstance = (SFc2_call_stats_block1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i30 = 0; c2_i30 < 10; c2_i30++) {
    c2_u[c2_i30] = (*(real_T (*)[10])c2_inData)[c2_i30];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 10), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

const mxArray *sf_c2_call_stats_block1_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  const char * c2_data[5] = {
    "789ced54cd4edb40101e57101589504e3d549c3976f9a9d46bd32601a4040289040255ea7a3369b6dd9fc85ed3d04b1f8057e0c023f0083c05cfc3c66461b1b0"
    "8c400dad94952dfbf3e79d6fe7d3cc40b0d50c0060c1de7b7f00cee7215de5315ebc81f00aeeaf2c1f64fe0bc6bc5bb33093e2b2c7b72c3e1b63a695c1a1b901",
    "822bdc4e648891058a4abc0dd3d5922baa4ce764801061acc5317653a6c70576b8c486f6c026b740d63dea168ca8d1fb973eb29fed4442d48fef8e2b7c009e3f"
    "df72f29f29f027bbb2fe2c6670915ea9402f78e0e9c79f83d71e5efae4f4064fcccfe9bc29c8cff1b1a1063b115531375cab17f3f7e299f9360bf41c7f54fb4a",
    "fa5a22a1823352d52c91a84c4c9a954ea3f299b088fe3ee9098e8477ed77dee38c8e7c2171c448c6abf71226591f97efcaa75795c9d6e3a4ebffe5f48639f11e"
    "5b7f6f73f45cfd391e7fadf39d1fbb1fc2cdea9adc1f7cdf68efd66bb5bb73b40a748ace011e7e28cfbf1dff3267ff637d3ccc89ef7c74fcd156e3a0657b3989",
    "232234a3c275f0dedacaeac79018ad45a88704a520828744522368487a89b2171944fcd8f632b1fbc44eb5564f141b75f476bb9936354cba0e97fffbb9eff44b"
    "1ebeaf5f4a715727a1c0e9dc9fcefd7f436f3af79f17ff1a07a62022", "" };

  c2_nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(c2_data, 3256U, &c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_ode45(SFc2_call_stats_block1InstanceStruct *chartInstance, real_T
                     c2_y0[6], real_T c2_varargout_1_data[], int32_T
                     c2_varargout_1_size[1], real_T c2_varargout_2_data[],
                     int32_T c2_varargout_2_size[2])
{
  int32_T c2_i31;
  real_T c2_b_y0[6];
  real_T c2_f0[6];
  int32_T c2_i32;
  int32_T c2_i33;
  real_T c2_tout[100];
  int32_T c2_nout;
  real_T c2_yout[600];
  int32_T c2_i34;
  real_T c2_absh;
  int32_T c2_i35;
  real_T c2_c_y0[6];
  real_T c2_ynew[6];
  int32_T c2_k;
  int32_T c2_i36;
  real_T c2_maxval[6];
  real_T c2_rh;
  real_T c2_b_f0[6];
  real_T c2_t;
  int32_T c2_i37;
  int32_T c2_i38;
  real_T c2_y[6];
  int32_T c2_i39;
  real_T c2_f[42];
  int32_T c2_next;
  boolean_T c2_MinStepExit;
  boolean_T c2_Done;
  real_T c2_hmin;
  real_T c2_h;
  boolean_T c2_NoFailedAttempts;
  int32_T c2_Bcolidx;
  int32_T c2_j;
  real_T c2_tnew;
  int32_T c2_i40;
  int32_T c2_i41;
  int32_T c2_i42;
  int32_T c2_i43;
  real_T c2_b_f[42];
  static real_T c2_dv4[6] = { 0.2, 0.3, 0.8, 0.88888888888888884, 1.0, 1.0 };

  real_T c2_c_f[42];
  int32_T c2_i44;
  real_T c2_b_ynew[6];
  int32_T c2_i45;
  int32_T c2_i46;
  real_T c2_b_y[6];
  real_T c2_c_ynew[6];
  int32_T c2_i47;
  real_T c2_err;
  real_T c2_d_f[6];
  real_T c2_d1;
  int32_T c2_i48;
  int32_T c2_i49;
  real_T c2_c_x;
  int32_T c2_nnxt;
  const mxArray *c2_c_y = NULL;
  real_T c2_d_y;
  static char_T c2_rfmt[7] = { '%', '2', '3', '.', '1', '5', 'e' };

  static real_T c2_b[7] = { 0.0012326388888888888, 0.0, -0.0042527702905061394,
    0.036979166666666667, -0.05086379716981132, 0.0419047619047619, -0.025 };

  int32_T c2_loop_ub;
  boolean_T c2_p;
  const mxArray *c2_e_y = NULL;
  int32_T c2_i50;
  int32_T c2_noutnew;
  char_T c2_str[23];
  real_T c2_d_x;
  int32_T c2_b_k;
  const mxArray *c2_f_y = NULL;
  int32_T c2_i51;
  const mxArray *c2_g_y = NULL;
  real_T c2_h_y;
  boolean_T c2_b_p;
  int32_T c2_i52;
  char_T c2_b_str[23];
  int32_T c2_i53;
  int32_T c2_i54;
  int32_T c2_i55;
  int32_T c2_b_loop_ub;
  int32_T c2_i56;
  real_T c2_temp;
  int32_T c2_i57;
  real_T c2_i_y[6];
  int32_T c2_i58;
  real_T c2_e_f[42];
  real_T c2_f_f[42];
  int32_T exitg1;
  int32_T exitg2;
  for (c2_i31 = 0; c2_i31 < 6; c2_i31++) {
    c2_b_y0[c2_i31] = c2_y0[c2_i31];
  }

  c2_callODEFunctionNSM(chartInstance, 0.0, c2_b_y0, c2_f0);
  for (c2_i32 = 0; c2_i32 < 100; c2_i32++) {
    c2_tout[c2_i32] = 0.0;
  }

  for (c2_i33 = 0; c2_i33 < 600; c2_i33++) {
    c2_yout[c2_i33] = 0.0;
  }

  c2_nout = 1;
  c2_tout[0] = 0.0;
  for (c2_i34 = 0; c2_i34 < 6; c2_i34++) {
    c2_yout[c2_i34] = c2_y0[c2_i34];
  }

  c2_absh = 0.030303030303030304;
  for (c2_i35 = 0; c2_i35 < 6; c2_i35++) {
    c2_c_y0[c2_i35] = c2_y0[c2_i35];
  }

  c2_abs(chartInstance, c2_c_y0, c2_ynew);
  for (c2_k = 0; c2_k < 6; c2_k++) {
    c2_maxval[c2_k] = muDoubleScalarMax(c2_ynew[c2_k], 0.001);
  }

  for (c2_i36 = 0; c2_i36 < 6; c2_i36++) {
    c2_b_f0[c2_i36] = c2_f0[c2_i36] / c2_maxval[c2_i36];
  }

  c2_rh = c2_norm(chartInstance, c2_b_f0) / 0.20095091452076641;
  if (0.030303030303030304 * c2_rh > 1.0) {
    c2_absh = 1.0 / c2_rh;
  }

  c2_absh = muDoubleScalarMax(c2_absh, 7.90505033345994E-323);
  c2_t = 0.0;
  for (c2_i37 = 0; c2_i37 < 6; c2_i37++) {
    c2_y[c2_i37] = c2_y0[c2_i37];
  }

  for (c2_i38 = 0; c2_i38 < 42; c2_i38++) {
    c2_f[c2_i38] = 0.0;
  }

  for (c2_i39 = 0; c2_i39 < 6; c2_i39++) {
    c2_f[c2_i39] = c2_f0[c2_i39];
  }

  c2_next = 2;
  c2_MinStepExit = false;
  c2_Done = false;
  do {
    exitg1 = 0;
    c2_hmin = 16.0 * c2_eps(chartInstance, c2_t);
    c2_absh = muDoubleScalarMin(0.30000000000000004, muDoubleScalarMax(c2_hmin,
      c2_absh));
    c2_h = c2_absh;
    if (1.1 * c2_absh >= muDoubleScalarAbs(3.0 - c2_t)) {
      c2_h = 3.0 - c2_t;
      c2_absh = muDoubleScalarAbs(3.0 - c2_t);
      c2_Done = true;
    }

    c2_NoFailedAttempts = true;
    do {
      exitg2 = 0;
      c2_Bcolidx = 1;
      for (c2_j = 0; c2_j < 5; c2_j++) {
        c2_Bcolidx += c2_j;
        for (c2_i40 = 0; c2_i40 < 6; c2_i40++) {
          c2_maxval[c2_i40] = c2_y[c2_i40];
        }

        for (c2_i42 = 0; c2_i42 < 42; c2_i42++) {
          c2_b_f[c2_i42] = c2_f[c2_i42];
        }

        c2_c_xgemv(chartInstance, c2_j + 1, c2_h, c2_b_f, c2_Bcolidx, c2_maxval);
        c2_callODEFunctionNSM(chartInstance, c2_t + c2_h * c2_dv4[c2_j],
                              c2_maxval, *(real_T (*)[6])&c2_f[6 * (c2_j + 1)]);
      }

      c2_tnew = c2_t + c2_h;
      if (c2_Done) {
        c2_tnew = 3.0;
      }

      c2_Bcolidx;
      for (c2_i41 = 0; c2_i41 < 6; c2_i41++) {
        c2_ynew[c2_i41] = c2_y[c2_i41];
      }

      for (c2_i43 = 0; c2_i43 < 42; c2_i43++) {
        c2_c_f[c2_i43] = c2_f[c2_i43];
      }

      c2_d_xgemv(chartInstance, c2_h, c2_c_f, c2_Bcolidx + 5, c2_ynew);
      for (c2_i44 = 0; c2_i44 < 6; c2_i44++) {
        c2_b_ynew[c2_i44] = c2_ynew[c2_i44];
      }

      c2_callODEFunctionNSM(chartInstance, c2_tnew, c2_b_ynew, *(real_T (*)[6])&
                            c2_f[36]);
      c2_h = c2_tnew - c2_t;
      for (c2_i45 = 0; c2_i45 < 6; c2_i45++) {
        c2_b_y[c2_i45] = c2_y[c2_i45];
      }

      for (c2_i46 = 0; c2_i46 < 6; c2_i46++) {
        c2_c_ynew[c2_i46] = c2_ynew[c2_i46];
      }

      c2_maxAbsThresh(chartInstance, c2_b_y, c2_c_ynew, 0.001, c2_maxval);
      for (c2_i47 = 0; c2_i47 < 6; c2_i47++) {
        c2_d1 = 0.0;
        c2_i48 = 0;
        for (c2_i49 = 0; c2_i49 < 7; c2_i49++) {
          c2_d1 += c2_f[c2_i48 + c2_i47] * c2_b[c2_i49];
          c2_i48 += 6;
        }

        c2_d_f[c2_i47] = c2_d1 / c2_maxval[c2_i47];
      }

      c2_err = c2_absh * c2_norm(chartInstance, c2_d_f);
      if (c2_err > 0.001) {
        if (c2_absh <= c2_hmin) {
          c2_c_x = c2_t;
          c2_c_y = NULL;
          sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_rfmt, 10, 0U, 1U, 0U, 2,
            1, 7), false);
          c2_e_y = NULL;
          sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_c_x, 0, 0U, 0U, 0U, 0),
                        false);
          c2_f_emlrt_marshallIn(chartInstance, sf_mex_call_debug
                                (sfGlobalDebugInstanceStruct, "sprintf", 1U, 2U,
            14, c2_c_y, 14, c2_e_y), "sprintf", c2_str);
          c2_d_x = c2_hmin;
          c2_f_y = NULL;
          sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_rfmt, 10, 0U, 1U, 0U, 2,
            1, 7), false);
          c2_g_y = NULL;
          sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_d_x, 0, 0U, 0U, 0U, 0),
                        false);
          c2_f_emlrt_marshallIn(chartInstance, sf_mex_call_debug
                                (sfGlobalDebugInstanceStruct, "sprintf", 1U, 2U,
            14, c2_f_y, 14, c2_g_y), "sprintf", c2_b_str);
          c2_warning(chartInstance, c2_str, c2_b_str);
          c2_MinStepExit = true;
          exitg2 = 1;
        } else {
          if (c2_NoFailedAttempts) {
            c2_NoFailedAttempts = false;
            c2_d_y = 0.001 / c2_err;
            c2_p = (c2_d_y < 0.0);
            if (c2_p) {
              c2_c_error(chartInstance);
            }

            c2_absh = muDoubleScalarMax(c2_hmin, c2_absh * muDoubleScalarMax(0.1,
              0.8 * muDoubleScalarPower(c2_d_y, 0.2)));
          } else {
            c2_absh = muDoubleScalarMax(c2_hmin, 0.5 * c2_absh);
          }

          c2_h = c2_absh;
          c2_Done = false;
        }
      } else {
        exitg2 = 1;
      }
    } while (exitg2 == 0);

    if (c2_MinStepExit) {
      exitg1 = 1;
    } else {
      c2_nnxt = c2_next - 2;
      while (((real_T)(c2_nnxt + 2) <= 100.0) && (c2_tnew - 0.030303030303030304
              * (real_T)(c2_nnxt + 1) >= 0.0)) {
        c2_nnxt++;
      }

      c2_noutnew = (c2_nnxt - c2_next) + 2;
      if (c2_noutnew > 0) {
        for (c2_b_k = c2_next - 1; c2_b_k + 1 <= c2_nnxt; c2_b_k++) {
          c2_tout[c2_b_k] = 0.030303030303030304 * (real_T)c2_b_k;
          for (c2_i52 = 0; c2_i52 < 6; c2_i52++) {
            c2_i_y[c2_i52] = c2_y[c2_i52];
          }

          for (c2_i57 = 0; c2_i57 < 42; c2_i57++) {
            c2_f_f[c2_i57] = c2_f[c2_i57];
          }

          c2_ntrp45(chartInstance, 0.030303030303030304 * (real_T)c2_b_k, c2_t,
                    c2_i_y, c2_h, c2_f_f, *(real_T (*)[6])&c2_yout[6 * c2_b_k]);
        }

        c2_tout[c2_nnxt] = 0.030303030303030304 * (real_T)c2_nnxt;
        if (0.030303030303030304 * (real_T)c2_nnxt == c2_tnew) {
          for (c2_i55 = 0; c2_i55 < 6; c2_i55++) {
            c2_yout[c2_i55 + 6 * c2_nnxt] = c2_ynew[c2_i55];
          }
        } else {
          for (c2_i54 = 0; c2_i54 < 42; c2_i54++) {
            c2_e_f[c2_i54] = c2_f[c2_i54];
          }

          c2_ntrp45(chartInstance, 0.030303030303030304 * (real_T)c2_nnxt, c2_t,
                    c2_y, c2_h, c2_e_f, *(real_T (*)[6])&c2_yout[6 * c2_nnxt]);
        }

        c2_nout += c2_noutnew;
        c2_next = c2_nnxt + 2;
      }

      if (c2_Done) {
        exitg1 = 1;
      } else {
        if (c2_NoFailedAttempts) {
          c2_h_y = c2_err / 0.001;
          c2_b_p = (c2_h_y < 0.0);
          if (c2_b_p) {
            c2_c_error(chartInstance);
          }

          c2_temp = 1.25 * muDoubleScalarPower(c2_h_y, 0.2);
          if (c2_temp > 0.2) {
            c2_absh /= c2_temp;
          } else {
            c2_absh *= 5.0;
          }
        }

        c2_t = c2_tnew;
        for (c2_i53 = 0; c2_i53 < 6; c2_i53++) {
          c2_y[c2_i53] = c2_ynew[c2_i53];
        }

        for (c2_i58 = 0; c2_i58 < 6; c2_i58++) {
          c2_f[c2_i58] = c2_f[c2_i58 + 36];
        }
      }
    }
  } while (exitg1 == 0);

  c2_varargout_1_size[0] = c2_nout;
  c2_loop_ub = c2_nout - 1;
  for (c2_i50 = 0; c2_i50 <= c2_loop_ub; c2_i50++) {
    c2_varargout_1_data[c2_i50] = c2_tout[c2_i50];
  }

  c2_varargout_2_size[0] = c2_nout;
  c2_varargout_2_size[1] = 6;
  for (c2_i51 = 0; c2_i51 < 6; c2_i51++) {
    c2_b_loop_ub = c2_nout - 1;
    for (c2_i56 = 0; c2_i56 <= c2_b_loop_ub; c2_i56++) {
      c2_varargout_2_data[c2_i56 + c2_varargout_2_size[0] * c2_i51] =
        c2_yout[c2_i51 + 6 * c2_i56];
    }
  }
}

static void c2_callODEFunctionNSM(SFc2_call_stats_block1InstanceStruct
  *chartInstance, real_T c2_t, real_T c2_y[6], real_T c2_yp[6])
{
  real_T c2_b_t;
  int32_T c2_i59;
  uint32_T c2_debug_family_var_map[9];
  real_T c2_s[6];
  real_T c2_uTrans[10];
  real_T c2_uTransTime[10];
  real_T c2_uRot[10];
  real_T c2_uRotTime[10];
  real_T c2_b_uTrans;
  real_T c2_b_uRot;
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i60;
  int32_T c2_i61;
  int32_T c2_i62;
  int32_T c2_i63;
  int32_T c2_i64;
  int32_T c2_i65;
  int32_T c2_i66;
  real_T c2_dv5[10];
  real_T c2_dv6[10];
  int32_T c2_i67;
  int32_T c2_i68;
  real_T c2_dv7[10];
  real_T c2_dv8[10];
  real_T c2_xi;
  real_T c2_yi;
  real_T c2_c_x;
  real_T c2_b_xi;
  real_T c2_b_yi;
  real_T c2_d_x;
  real_T c2_varargin_3;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_Vq;
  int32_T c2_i69;
  int32_T c2_low_i;
  int32_T c2_low_ip1;
  int32_T c2_high_i;
  int32_T c2_i70;
  real_T c2_b_yp[6];
  real_T c2_xn;
  int32_T c2_mid_i;
  int32_T c2_i71;
  real_T c2_r;
  static real_T c2_varargin_2[11] = { 0.0, 6.3632, 16.8374, 25.6822, 35.581,
    45.7588, 53.0103, 60.5996, 83.5957, 89.0708, 96.1055 };

  int32_T c2_i72;
  real_T c2_y1;
  real_T c2_y2;
  int32_T exitg1;
  c2_b_t = c2_t;
  for (c2_i59 = 0; c2_i59 < 6; c2_i59++) {
    c2_s[c2_i59] = c2_y[c2_i59];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 9U, 11U, c2_b_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_uTrans, MAX_uint32_T, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_uTransTime, 1U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_uRot, MAX_uint32_T, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_uRotTime, 3U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_uTrans, MAX_uint32_T,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_uRot, MAX_uint32_T,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 4U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 5U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_t, 6U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_s, 7U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_yp, 8U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 6);
  for (c2_i60 = 0; c2_i60 < 6; c2_i60++) {
    c2_yp[c2_i60] = 0.0;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 8);
  for (c2_i61 = 0; c2_i61 < 10; c2_i61++) {
    c2_uTrans[c2_i61] = 1.0;
  }

  _SFD_SYMBOL_SWITCH(0U, 0U);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 9);
  for (c2_i62 = 0; c2_i62 < 10; c2_i62++) {
    c2_uTransTime[c2_i62] = (real_T)c2_i62;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 11);
  for (c2_i63 = 0; c2_i63 < 10; c2_i63++) {
    c2_uRot[c2_i63] = 1.0;
  }

  _SFD_SYMBOL_SWITCH(2U, 2U);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 12);
  for (c2_i64 = 0; c2_i64 < 10; c2_i64++) {
    c2_uRotTime[c2_i64] = (real_T)c2_i64;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 14);
  for (c2_i65 = 0; c2_i65 < 10; c2_i65++) {
    c2_dv5[c2_i65] = (real_T)c2_i65;
  }

  for (c2_i66 = 0; c2_i66 < 10; c2_i66++) {
    c2_dv6[c2_i66] = 1.0;
  }

  c2_b_uTrans = c2_interp1(chartInstance, c2_dv5, c2_dv6, c2_b_t);
  _SFD_SYMBOL_SWITCH(0U, 4U);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 15);
  for (c2_i67 = 0; c2_i67 < 10; c2_i67++) {
    c2_dv7[c2_i67] = (real_T)c2_i67;
  }

  for (c2_i68 = 0; c2_i68 < 10; c2_i68++) {
    c2_dv8[c2_i68] = 1.0;
  }

  c2_b_uRot = c2_interp1(chartInstance, c2_dv7, c2_dv8, c2_b_t);
  _SFD_SYMBOL_SWITCH(2U, 5U);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 16);
  c2_yp[0] = c2_s[3];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 17);
  c2_yp[1] = c2_s[4];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 18);
  c2_yp[2] = c2_s[5];
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 19);
  c2_xi = c2_b_uTrans;
  c2_yi = rtNaN;
  if (c2_xi >= 0.0) {
    c2_yi = 0.1122;
  }

  c2_c_x = c2_s[2];
  c2_yp[3] = c2_yi * muDoubleScalarCos(c2_c_x);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 20);
  c2_b_xi = c2_b_uTrans;
  c2_b_yi = rtNaN;
  if (c2_b_xi >= 0.0) {
    c2_b_yi = 0.1122;
  }

  c2_d_x = c2_s[2];
  c2_yp[4] = c2_b_yi * muDoubleScalarSin(c2_d_x);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 21);
  c2_varargin_3 = c2_b_uRot;
  c2_k = 0;
  do {
    exitg1 = 0;
    if (c2_k + 1 < 12) {
      if (muDoubleScalarIsNaN(10.0 * (real_T)c2_k)) {
        c2_error(chartInstance);
        exitg1 = 1;
      } else {
        c2_k++;
      }
    } else {
      for (c2_b_k = 0; c2_b_k < 10; c2_b_k++) {
        if (10.0 * (real_T)(c2_b_k + 1) <= 10.0 * (real_T)c2_b_k) {
          c2_b_error(chartInstance);
        }
      }

      c2_Vq = rtNaN;
      if (muDoubleScalarIsNaN(c2_varargin_3) || (c2_varargin_3 > 100.0) ||
          (c2_varargin_3 < 0.0)) {
      } else {
        c2_low_i = 1;
        c2_low_ip1 = 1;
        c2_high_i = 11;
        while (c2_high_i > c2_low_ip1 + 1) {
          c2_mid_i = (c2_low_i + c2_high_i) >> 1;
          if (c2_varargin_3 >= 10.0 * (real_T)(c2_mid_i - 1)) {
            c2_low_i = c2_mid_i;
            c2_low_ip1 = c2_mid_i;
          } else {
            c2_high_i = c2_mid_i;
          }
        }

        c2_xn = 10.0 * (real_T)(c2_low_i - 1);
        c2_r = (c2_varargin_3 - c2_xn) / (10.0 * (real_T)c2_low_i - c2_xn);
        if (c2_r == 0.0) {
          c2_Vq = c2_varargin_2[c2_low_i - 1];
        } else if (c2_r == 1.0) {
          c2_Vq = c2_varargin_2[c2_low_i];
        } else {
          c2_y1 = c2_varargin_2[c2_low_i - 1];
          c2_y2 = c2_varargin_2[c2_low_i];
          if (c2_y1 == c2_y2) {
            c2_Vq = c2_y1;
          } else {
            c2_Vq = (1.0 - c2_r) * c2_y1 + c2_r * c2_y2;
          }
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  c2_yp[5] = c2_Vq;
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -21);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i69 = 0; c2_i69 < 6; c2_i69++) {
    c2_b_yp[c2_i69] = c2_yp[c2_i69];
  }

  for (c2_i70 = 0; c2_i70 < 6; c2_i70++) {
    c2_yp[c2_i70] = c2_b_yp[c2_i70];
  }

  for (c2_i71 = 0; c2_i71 < 6; c2_i71++) {
    c2_b_yp[c2_i71] = c2_yp[c2_i71];
  }

  for (c2_i72 = 0; c2_i72 < 6; c2_i72++) {
    c2_yp[c2_i72] = c2_b_yp[c2_i72];
  }
}

static real_T c2_interp1(SFc2_call_stats_block1InstanceStruct *chartInstance,
  real_T c2_varargin_1[10], real_T c2_varargin_2[10], real_T c2_varargin_3)
{
  real_T c2_Vq;
  int32_T c2_k;
  int32_T c2_b_k;
  int32_T c2_low_i;
  int32_T c2_low_ip1;
  int32_T c2_high_i;
  int32_T c2_mid_i;
  int32_T exitg1;
  (void)c2_varargin_2;
  c2_k = 0;
  do {
    exitg1 = 0;
    if (c2_k + 1 < 11) {
      if (muDoubleScalarIsNaN(c2_varargin_1[c2_k])) {
        c2_error(chartInstance);
        exitg1 = 1;
      } else {
        c2_k++;
      }
    } else {
      for (c2_b_k = 0; c2_b_k < 9; c2_b_k++) {
        if (c2_varargin_1[c2_b_k + 1] <= c2_varargin_1[c2_b_k]) {
          c2_b_error(chartInstance);
        }
      }

      c2_Vq = rtNaN;
      if (muDoubleScalarIsNaN(c2_varargin_3) || (c2_varargin_3 > 9.0) ||
          (c2_varargin_3 < 0.0)) {
      } else {
        c2_low_i = 1;
        c2_low_ip1 = 1;
        c2_high_i = 10;
        while (c2_high_i > c2_low_ip1 + 1) {
          c2_mid_i = (c2_low_i + c2_high_i) >> 1;
          if (c2_varargin_3 >= c2_varargin_1[c2_mid_i - 1]) {
            c2_low_i = c2_mid_i;
            c2_low_ip1 = c2_mid_i;
          } else {
            c2_high_i = c2_mid_i;
          }
        }

        c2_Vq = 1.0;
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return c2_Vq;
}

static void c2_error(SFc2_call_stats_block1InstanceStruct *chartInstance)
{
  const mxArray *c2_y = NULL;
  static char_T c2_cv0[21] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'i', 'n', 't',
    'e', 'r', 'p', '1', ':', 'N', 'a', 'N', 'i', 'n', 'X' };

  (void)chartInstance;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_cv0, 10, 0U, 1U, 0U, 2, 1, 21),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c2_y));
}

static void c2_b_error(SFc2_call_stats_block1InstanceStruct *chartInstance)
{
  const mxArray *c2_y = NULL;
  static char_T c2_cv1[35] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', 'e', 'r', 'p', '1', '_', 'n', 'o', 'n',
    'M', 'o', 'n', 'o', 't', 'o', 'n', 'i', 'c', 'X' };

  (void)chartInstance;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_cv1, 10, 0U, 1U, 0U, 2, 1, 35),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c2_y));
}

static void c2_abs(SFc2_call_stats_block1InstanceStruct *chartInstance, real_T
                   c2_c_x[6], real_T c2_y[6])
{
  int32_T c2_k;
  (void)chartInstance;
  for (c2_k = 0; c2_k < 6; c2_k++) {
    c2_y[c2_k] = muDoubleScalarAbs(c2_c_x[c2_k]);
  }
}

static real_T c2_norm(SFc2_call_stats_block1InstanceStruct *chartInstance,
                      real_T c2_c_x[6])
{
  real_T c2_y;
  int32_T c2_k;
  real_T c2_absx;
  boolean_T exitg1;
  (void)chartInstance;
  c2_y = 0.0;
  c2_k = 0;
  exitg1 = false;
  while ((!exitg1) && (c2_k < 6)) {
    c2_absx = muDoubleScalarAbs(c2_c_x[c2_k]);
    if (muDoubleScalarIsNaN(c2_absx)) {
      c2_y = rtNaN;
      exitg1 = true;
    } else {
      if (c2_absx > c2_y) {
        c2_y = c2_absx;
      }

      c2_k++;
    }
  }

  return c2_y;
}

static void c2_c_error(SFc2_call_stats_block1InstanceStruct *chartInstance)
{
  const mxArray *c2_y = NULL;
  static char_T c2_cv2[31] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'p', 'o', 'w', 'e', 'r', '_', 'd', 'o', 'm', 'a', 'i',
    'n', 'E', 'r', 'r', 'o', 'r' };

  (void)chartInstance;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_cv2, 10, 0U, 1U, 0U, 2, 1, 31),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c2_y));
}

static real_T c2_eps(SFc2_call_stats_block1InstanceStruct *chartInstance, real_T
                     c2_c_x)
{
  real_T c2_r;
  real_T c2_absxk;
  int32_T c2_exponent;
  (void)chartInstance;
  c2_absxk = muDoubleScalarAbs(c2_c_x);
  if ((!muDoubleScalarIsInf(c2_absxk)) && (!muDoubleScalarIsNaN(c2_absxk))) {
    if (c2_absxk <= 2.2250738585072014E-308) {
      c2_r = 4.94065645841247E-324;
    } else {
      frexp(c2_absxk, &c2_exponent);
      c2_r = ldexp(1.0, c2_exponent - 53);
    }
  } else {
    c2_r = rtNaN;
  }

  return c2_r;
}

static void c2_xgemv(SFc2_call_stats_block1InstanceStruct *chartInstance,
                     int32_T c2_n, real_T c2_alpha1, real_T c2_A[42], int32_T
                     c2_ix0, real_T c2_y[6], real_T c2_b_y[6])
{
  int32_T c2_i73;
  int32_T c2_i74;
  real_T c2_b_A[42];
  for (c2_i73 = 0; c2_i73 < 6; c2_i73++) {
    c2_b_y[c2_i73] = c2_y[c2_i73];
  }

  for (c2_i74 = 0; c2_i74 < 42; c2_i74++) {
    c2_b_A[c2_i74] = c2_A[c2_i74];
  }

  c2_c_xgemv(chartInstance, c2_n, c2_alpha1, c2_b_A, c2_ix0, c2_b_y);
}

static void c2_b_xgemv(SFc2_call_stats_block1InstanceStruct *chartInstance,
  real_T c2_alpha1, real_T c2_A[42], int32_T c2_ix0, real_T c2_y[6], real_T
  c2_b_y[6])
{
  int32_T c2_i75;
  int32_T c2_i76;
  real_T c2_b_A[42];
  for (c2_i75 = 0; c2_i75 < 6; c2_i75++) {
    c2_b_y[c2_i75] = c2_y[c2_i75];
  }

  for (c2_i76 = 0; c2_i76 < 42; c2_i76++) {
    c2_b_A[c2_i76] = c2_A[c2_i76];
  }

  c2_d_xgemv(chartInstance, c2_alpha1, c2_b_A, c2_ix0, c2_b_y);
}

static void c2_maxAbsThresh(SFc2_call_stats_block1InstanceStruct *chartInstance,
  real_T c2_a[6], real_T c2_b[6], real_T c2_thresh, real_T c2_y[6])
{
  int32_T c2_k;
  real_T c2_b_y;
  real_T c2_c_y;
  real_T c2_d_y;
  (void)chartInstance;
  (void)c2_thresh;
  for (c2_k = 0; c2_k < 6; c2_k++) {
    c2_b_y = muDoubleScalarAbs(c2_a[c2_k]);
    c2_c_y = muDoubleScalarAbs(c2_b[c2_k]);
    if ((c2_b_y > c2_c_y) || muDoubleScalarIsNaN(c2_c_y)) {
      c2_d_y = muDoubleScalarMax(c2_b_y, 0.001);
    } else {
      c2_d_y = muDoubleScalarMax(c2_c_y, 0.001);
    }

    c2_y[c2_k] = c2_d_y;
  }
}

static void c2_warning(SFc2_call_stats_block1InstanceStruct *chartInstance,
  char_T c2_varargin_1[23], char_T c2_varargin_2[23])
{
  const mxArray *c2_y = NULL;
  static char_T c2_cv3[7] = { 'w', 'a', 'r', 'n', 'i', 'n', 'g' };

  const mxArray *c2_b_y = NULL;
  static char_T c2_cv4[7] = { 'm', 'e', 's', 's', 'a', 'g', 'e' };

  const mxArray *c2_c_y = NULL;
  static char_T c2_msgID[33] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'o', 'd',
    'e', '4', '5', ':', 'I', 'n', 't', 'e', 'g', 'r', 'a', 't', 'i', 'o', 'n',
    'T', 'o', 'l', 'N', 'o', 't', 'M', 'e', 't' };

  const mxArray *c2_d_y = NULL;
  const mxArray *c2_e_y = NULL;
  (void)chartInstance;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_cv3, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_cv4, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_msgID, 10, 0U, 1U, 0U, 2, 1, 33),
                false);
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_varargin_1, 10, 0U, 1U, 0U, 2, 1,
    23), false);
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_varargin_2, 10, 0U, 1U, 0U, 2, 1,
    23), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 0U, 2U, 14, c2_y, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 1U,
    4U, 14, c2_b_y, 14, c2_c_y, 14, c2_d_y, 14, c2_e_y));
}

static void c2_ntrp45(SFc2_call_stats_block1InstanceStruct *chartInstance,
                      real_T c2_t, real_T c2_t0, real_T c2_y0[6], real_T c2_h,
                      real_T c2_f[42], real_T c2_y[6])
{
  int32_T c2_i77;
  int32_T c2_i78;
  real_T c2_fhBI1[6];
  int32_T c2_i79;
  real_T c2_fhBI2[6];
  int32_T c2_i80;
  int32_T c2_i81;
  int32_T c2_i82;
  real_T c2_fhBI3[6];
  int32_T c2_i83;
  int32_T c2_i84;
  static real_T c2_b[7] = { -2.859375, 0.0, 4.0431266846361185, -3.90625,
    2.7939268867924527, -1.5714285714285714, 1.5 };

  real_T c2_s;
  real_T c2_fhBI4[6];
  int32_T c2_k;
  int32_T c2_i85;
  int32_T c2_i86;
  static real_T c2_b_b[7] = { 3.0833333333333335, 0.0, -6.2893081761006293,
    10.416666666666666, -6.8773584905660377, 3.6666666666666665, -4.0 };

  static real_T c2_c_b[7] = { -1.1328125, 0.0, 2.6954177897574123, -5.859375,
    3.7610554245283021, -1.9642857142857142, 2.5 };

  (void)chartInstance;
  for (c2_i77 = 0; c2_i77 < 6; c2_i77++) {
    c2_fhBI1[c2_i77] = c2_f[c2_i77] * c2_h;
  }

  for (c2_i78 = 0; c2_i78 < 6; c2_i78++) {
    c2_fhBI2[c2_i78] = 0.0;
    c2_i80 = 0;
    for (c2_i81 = 0; c2_i81 < 7; c2_i81++) {
      c2_fhBI2[c2_i78] += c2_f[c2_i80 + c2_i78] * (c2_h * c2_b[c2_i81]);
      c2_i80 += 6;
    }
  }

  for (c2_i79 = 0; c2_i79 < 6; c2_i79++) {
    c2_fhBI3[c2_i79] = 0.0;
    c2_i83 = 0;
    for (c2_i84 = 0; c2_i84 < 7; c2_i84++) {
      c2_fhBI3[c2_i79] += c2_f[c2_i83 + c2_i79] * (c2_h * c2_b_b[c2_i84]);
      c2_i83 += 6;
    }
  }

  for (c2_i82 = 0; c2_i82 < 6; c2_i82++) {
    c2_fhBI4[c2_i82] = 0.0;
    c2_i85 = 0;
    for (c2_i86 = 0; c2_i86 < 7; c2_i86++) {
      c2_fhBI4[c2_i82] += c2_f[c2_i85 + c2_i82] * (c2_h * c2_c_b[c2_i86]);
      c2_i85 += 6;
    }
  }

  c2_s = (c2_t - c2_t0) / c2_h;
  for (c2_k = 0; c2_k < 6; c2_k++) {
    c2_y[c2_k] = (((c2_fhBI4[c2_k] * c2_s + c2_fhBI3[c2_k]) * c2_s +
                   c2_fhBI2[c2_k]) * c2_s + c2_fhBI1[c2_k]) * c2_s + c2_y0[c2_k];
  }
}

static void c2_f_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_sprintf, const char_T *c2_identifier, char_T
  c2_y[23])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_sprintf), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_sprintf);
}

static void c2_g_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  char_T c2_y[23])
{
  char_T c2_cv5[23];
  int32_T c2_i87;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_cv5, 1, 10, 0U, 1, 0U, 2, 1,
                23);
  for (c2_i87 = 0; c2_i87 < 23; c2_i87++) {
    c2_y[c2_i87] = c2_cv5[c2_i87];
  }

  sf_mex_destroy(&c2_u);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_call_stats_block1InstanceStruct *chartInstance;
  chartInstance = (SFc2_call_stats_block1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_h_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i88;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i88, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i88;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_call_stats_block1InstanceStruct *chartInstance;
  chartInstance = (SFc2_call_stats_block1InstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_thisId.fIdentifier = (const char *)c2_varName;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_i_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_call_stats_block1, const
  char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_call_stats_block1), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_call_stats_block1);
  return c2_y;
}

static uint8_T c2_j_emlrt_marshallIn(SFc2_call_stats_block1InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_xgemv(SFc2_call_stats_block1InstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_alpha1, real_T c2_A[42], int32_T c2_ix0, real_T c2_y[6])
{
  int32_T c2_ix;
  int32_T c2_c;
  int32_T c2_iac;
  real_T c2_b_c;
  int32_T c2_iy;
  int32_T c2_ia;
  (void)chartInstance;
  if (c2_alpha1 == 0.0) {
  } else {
    c2_ix = c2_ix0 - 1;
    c2_c = 6 * (c2_n - 1) + 1;
    for (c2_iac = 1; c2_iac <= c2_c; c2_iac += 6) {
      c2_b_c = c2_alpha1 * c2_dv0[c2_ix];
      c2_iy = 0;
      for (c2_ia = c2_iac; c2_ia <= c2_iac + 5; c2_ia++) {
        c2_y[c2_iy] += c2_A[c2_ia - 1] * c2_b_c;
        c2_iy++;
      }

      c2_ix++;
    }
  }
}

static void c2_d_xgemv(SFc2_call_stats_block1InstanceStruct *chartInstance,
  real_T c2_alpha1, real_T c2_A[42], int32_T c2_ix0, real_T c2_y[6])
{
  int32_T c2_ix;
  int32_T c2_iac;
  real_T c2_c;
  int32_T c2_iy;
  int32_T c2_ia;
  (void)chartInstance;
  if (c2_alpha1 == 0.0) {
  } else {
    c2_ix = c2_ix0 - 1;
    for (c2_iac = 0; c2_iac < 32; c2_iac += 6) {
      c2_c = c2_alpha1 * c2_dv0[c2_ix];
      c2_iy = 0;
      for (c2_ia = c2_iac + 1; c2_ia <= c2_iac + 6; c2_ia++) {
        c2_y[c2_iy] += c2_A[c2_ia - 1] * c2_c;
        c2_iy++;
      }

      c2_ix++;
    }
  }
}

static void init_dsm_address_info(SFc2_call_stats_block1InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_call_stats_block1InstanceStruct
  *chartInstance)
{
  chartInstance->c2_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c2_x = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_b_x = (real_T (*)[6])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_w = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_call_stats_block1_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2867268634U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2416211520U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(484859065U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3429361034U);
}

mxArray* sf_c2_call_stats_block1_get_post_codegen_info(void);
mxArray *sf_c2_call_stats_block1_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("yE80Wi6AH8sT75kUFMWHXF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_call_stats_block1_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_call_stats_block1_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_call_stats_block1_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_call_stats_block1_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_call_stats_block1_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c2_call_stats_block1(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"x\",},{M[8],M[0],T\"is_active_c2_call_stats_block1\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_call_stats_block1_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_call_stats_block1InstanceStruct *chartInstance =
      (SFc2_call_stats_block1InstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _call_stats_block1MachineNumber_,
           2,
           1,
           1,
           0,
           3,
           0,
           0,
           0,
           0,
           1,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_call_stats_block1MachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_call_stats_block1MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _call_stats_block1MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"x");
          _SFD_SET_DATA_PROPS(1,1,1,0,"w");
          _SFD_SET_DATA_PROPS(2,2,0,1,"x");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,231);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"stateTransition",0,-1,852);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _call_stats_block1MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_call_stats_block1InstanceStruct *chartInstance =
      (SFc2_call_stats_block1InstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c2_x);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c2_b_x);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c2_w);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sBmoMttBaAMcIphCrmqQGwC";
}

static void sf_opaque_initialize_c2_call_stats_block1(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_call_stats_block1InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_call_stats_block1((SFc2_call_stats_block1InstanceStruct*)
    chartInstanceVar);
  initialize_c2_call_stats_block1((SFc2_call_stats_block1InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_call_stats_block1(void *chartInstanceVar)
{
  enable_c2_call_stats_block1((SFc2_call_stats_block1InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_call_stats_block1(void *chartInstanceVar)
{
  disable_c2_call_stats_block1((SFc2_call_stats_block1InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_call_stats_block1(void *chartInstanceVar)
{
  sf_gateway_c2_call_stats_block1((SFc2_call_stats_block1InstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_call_stats_block1(SimStruct* S)
{
  return get_sim_state_c2_call_stats_block1
    ((SFc2_call_stats_block1InstanceStruct *)sf_get_chart_instance_ptr(S));/* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_call_stats_block1(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c2_call_stats_block1((SFc2_call_stats_block1InstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c2_call_stats_block1(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_call_stats_block1InstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_call_stats_block1_optimization_info();
    }

    finalize_c2_call_stats_block1((SFc2_call_stats_block1InstanceStruct*)
      chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_call_stats_block1((SFc2_call_stats_block1InstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_call_stats_block1(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_call_stats_block1((SFc2_call_stats_block1InstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c2_call_stats_block1(SimStruct *S)
{
  /* Set overwritable ports for inplace optimization */
  ssSetInputPortOverWritable(S, 0, 1);
  ssSetOutputPortOverwritesInputPort(S, 1, 0);
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 1);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 1);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_call_stats_block1_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 2);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(981867876U));
  ssSetChecksum1(S,(2313349381U));
  ssSetChecksum2(S,(3553288662U));
  ssSetChecksum3(S,(1515299525U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_call_stats_block1(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_call_stats_block1(SimStruct *S)
{
  SFc2_call_stats_block1InstanceStruct *chartInstance;
  chartInstance = (SFc2_call_stats_block1InstanceStruct *)utMalloc(sizeof
    (SFc2_call_stats_block1InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_call_stats_block1InstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_call_stats_block1;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_call_stats_block1;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_call_stats_block1;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_call_stats_block1;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_call_stats_block1;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_call_stats_block1;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_call_stats_block1;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_call_stats_block1;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_call_stats_block1;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_call_stats_block1;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_call_stats_block1;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c2_call_stats_block1(chartInstance);
}

void c2_call_stats_block1_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_call_stats_block1(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_call_stats_block1(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_call_stats_block1(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_call_stats_block1_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
