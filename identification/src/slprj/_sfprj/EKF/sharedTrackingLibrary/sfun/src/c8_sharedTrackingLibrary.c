/* Include files */

#include "sharedTrackingLibrary_sfun.h"
#include "c8_sharedTrackingLibrary.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "sharedTrackingLibrary_sfun_debug_macros.h"
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
static const char * c8_debug_family_names[10] = { "pM", "nargin", "nargout", "x",
  "P", "yMeas", "R", "blockOrdering", "xNew", "PNew" };

/* Function Declarations */
static void initialize_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance);
static void initialize_params_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance);
static void enable_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance);
static void disable_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance);
static void c8_update_debugger_state_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance);
static void set_sim_state_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance, const mxArray *c8_st);
static void finalize_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance);
static void sf_gateway_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance);
static void mdl_start_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance);
static void initSimStructsc8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance);
static void c8_measFcn1_invoke(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, real_T c8_b_x[6], real_T c8_v[3], real_T c8_y[3]);
static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber, uint32_T c8_instanceNumber);
static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData);
static boolean_T c8_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_c_blockOrdering, const char_T *c8_identifier);
static boolean_T c8_b_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct *
  chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static void c8_c_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_b_PNew, const char_T *c8_identifier, real_T
  c8_y[36]);
static void c8_d_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[36]);
static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static void c8_e_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_b_xNew, const char_T *c8_identifier, real_T
  c8_y[6]);
static void c8_f_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[6]);
static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_e_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_f_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static real_T c8_g_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_g_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static void c8_EKFCorrectorNonAdditive_correct
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance, real_T c8_z[3],
   real_T c8_zcov[9], real_T c8_b_x[6], real_T c8_b_P[36], real_T c8_c_x[6],
   real_T c8_c_P[36]);
static void c8_warning(SFc8_sharedTrackingLibraryInstanceStruct *chartInstance);
static const mxArray *c8_h_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static int32_T c8_h_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static c8_scGUHJGjGVqH0aOEVjksvlC c8_i_emlrt_marshallIn
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance, const mxArray *c8_u,
   const emlrtMsgIdentifier *c8_parentId);
static void c8_j_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  char_T c8_y[8]);
static void c8_k_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static uint8_T c8_l_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_b_is_active_c8_sharedTrackingLibrary, const
  char_T *c8_identifier);
static uint8_T c8_m_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_b_EKFCorrectorNonAdditive_correct
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance, real_T c8_z[3],
   real_T c8_zcov[9], real_T c8_b_x[6], real_T c8_b_P[36]);
static void init_dsm_address_info(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc8_sharedTrackingLibrary(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c8_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c8_is_active_c8_sharedTrackingLibrary = 0U;
}

static void initialize_params_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance)
{
  const mxArray *c8_m0 = NULL;
  static const char * c8_fieldNames[4] = { "FcnName", "JacobianFcnName",
    "HasJacobian", "HasAdditiveNoise" };

  const mxArray *c8_mxField;
  c8_scGUHJGjGVqH0aOEVjksvlC c8_r0;
  c8_m0 = sf_mex_get_sfun_param(chartInstance->S, 0, 1);
  sf_mex_check_bus_parameter(c8_m0, 0, NULL, 4, c8_fieldNames, "pM",
    "scGUHJGjGVqH0aOEVjksvlC");
  c8_mxField = sf_mex_getfield(c8_m0, "FcnName", "pM", 0);
  sf_mex_import_named("pM", sf_mex_dup(c8_mxField), c8_r0.FcnName, 1, 10, 0U, 1,
                      0U, 2, 1, 8);
  c8_mxField = sf_mex_getfield(c8_m0, "JacobianFcnName", "pM", 0);
  sf_mex_import_named("pM", sf_mex_dup(c8_mxField), NULL, 1, 10, 0U, 1, 0U, 2, 0,
                      0);
  c8_mxField = sf_mex_getfield(c8_m0, "HasJacobian", "pM", 0);
  sf_mex_import_named("pM", sf_mex_dup(c8_mxField), &c8_r0.HasJacobian, 1, 11,
                      0U, 0, 0U, 0);
  c8_mxField = sf_mex_getfield(c8_m0, "HasAdditiveNoise", "pM", 0);
  sf_mex_import_named("pM", sf_mex_dup(c8_mxField), &c8_r0.HasAdditiveNoise, 1,
                      11, 0U, 0, 0U, 0);
  sf_mex_destroy(&c8_m0);
  chartInstance->c8_pM = c8_r0;
}

static void enable_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c8_update_debugger_state_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance)
{
  const mxArray *c8_st;
  const mxArray *c8_y = NULL;
  const mxArray *c8_b_y = NULL;
  boolean_T c8_hoistedGlobal;
  const mxArray *c8_c_y = NULL;
  const mxArray *c8_d_y = NULL;
  uint8_T c8_b_hoistedGlobal;
  const mxArray *c8_e_y = NULL;
  c8_st = NULL;
  c8_st = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_createcellmatrix(4, 1), false);
  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", *chartInstance->c8_PNew, 0, 0U, 1U,
    0U, 2, 6, 6), false);
  sf_mex_setcell(c8_y, 0, c8_b_y);
  c8_hoistedGlobal = *chartInstance->c8_b_blockOrdering;
  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", &c8_hoistedGlobal, 11, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c8_y, 1, c8_c_y);
  c8_d_y = NULL;
  sf_mex_assign(&c8_d_y, sf_mex_create("y", *chartInstance->c8_xNew, 0, 0U, 1U,
    0U, 1, 6), false);
  sf_mex_setcell(c8_y, 2, c8_d_y);
  c8_b_hoistedGlobal = chartInstance->c8_is_active_c8_sharedTrackingLibrary;
  c8_e_y = NULL;
  sf_mex_assign(&c8_e_y, sf_mex_create("y", &c8_b_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c8_y, 3, c8_e_y);
  sf_mex_assign(&c8_st, c8_y, false);
  return c8_st;
}

static void set_sim_state_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance, const mxArray *c8_st)
{
  const mxArray *c8_u;
  real_T c8_dv0[36];
  int32_T c8_i0;
  real_T c8_dv1[6];
  int32_T c8_i1;
  chartInstance->c8_doneDoubleBufferReInit = true;
  c8_u = sf_mex_dup(c8_st);
  c8_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 0)),
                        "PNew", c8_dv0);
  for (c8_i0 = 0; c8_i0 < 36; c8_i0++) {
    (*chartInstance->c8_PNew)[c8_i0] = c8_dv0[c8_i0];
  }

  *chartInstance->c8_b_blockOrdering = c8_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c8_u, 1)), "blockOrdering");
  c8_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 2)),
                        "xNew", c8_dv1);
  for (c8_i1 = 0; c8_i1 < 6; c8_i1++) {
    (*chartInstance->c8_xNew)[c8_i1] = c8_dv1[c8_i1];
  }

  chartInstance->c8_is_active_c8_sharedTrackingLibrary = c8_l_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 3)),
     "is_active_c8_sharedTrackingLibrary");
  sf_mex_destroy(&c8_u);
  c8_update_debugger_state_c8_sharedTrackingLibrary(chartInstance);
  sf_mex_destroy(&c8_st);
}

static void finalize_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance)
{
  int32_T c8_i2;
  int32_T c8_i3;
  int32_T c8_i4;
  int32_T c8_i5;
  int32_T c8_i6;
  int32_T c8_i7;
  real_T c8_b_x[6];
  int32_T c8_i8;
  real_T c8_b_P[36];
  int32_T c8_i9;
  real_T c8_b_yMeas[3];
  boolean_T c8_c_blockOrdering;
  real_T c8_b_R[9];
  uint32_T c8_debug_family_var_map[10];
  c8_scGUHJGjGVqH0aOEVjksvlC c8_b_pM;
  real_T c8_nargin = 5.0;
  real_T c8_nargout = 3.0;
  real_T c8_b_xNew[6];
  real_T c8_b_PNew[36];
  boolean_T c8_d_blockOrdering;
  static c8_scGUHJGjGVqH0aOEVjksvlC c8_r1 = { { 'm', 'e', 'a', 's', 'F', 'c',
      'n', '1' },                      /* FcnName */
    false,                             /* HasJacobian */
    false                              /* HasAdditiveNoise */
  };

  int32_T c8_i10;
  int32_T c8_i11;
  int32_T c8_i12;
  int32_T c8_i13;
  real_T c8_c_xNew[6];
  int32_T c8_i14;
  real_T c8_c_PNew[36];
  int32_T c8_i15;
  real_T c8_c_yMeas[3];
  real_T c8_c_R[9];
  int32_T c8_i16;
  int32_T c8_i17;
  int32_T c8_i18;
  int32_T c8_i19;
  int32_T c8_i20;
  int32_T c8_i21;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c8_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c8_blockOrdering, 4U);
  for (c8_i2 = 0; c8_i2 < 9; c8_i2++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c8_R)[c8_i2], 3U);
  }

  for (c8_i3 = 0; c8_i3 < 3; c8_i3++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c8_yMeas)[c8_i3], 2U);
  }

  for (c8_i4 = 0; c8_i4 < 36; c8_i4++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c8_P)[c8_i4], 1U);
  }

  for (c8_i5 = 0; c8_i5 < 6; c8_i5++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c8_x)[c8_i5], 0U);
  }

  chartInstance->c8_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c8_sfEvent);
  for (c8_i6 = 0; c8_i6 < 6; c8_i6++) {
    c8_b_x[c8_i6] = (*chartInstance->c8_x)[c8_i6];
  }

  for (c8_i7 = 0; c8_i7 < 36; c8_i7++) {
    c8_b_P[c8_i7] = (*chartInstance->c8_P)[c8_i7];
  }

  for (c8_i8 = 0; c8_i8 < 3; c8_i8++) {
    c8_b_yMeas[c8_i8] = (*chartInstance->c8_yMeas)[c8_i8];
  }

  for (c8_i9 = 0; c8_i9 < 9; c8_i9++) {
    c8_b_R[c8_i9] = (*chartInstance->c8_R)[c8_i9];
  }

  c8_c_blockOrdering = *chartInstance->c8_blockOrdering;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 11U, c8_debug_family_names,
    c8_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_b_pM, 0U, c8_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargin, 1U, c8_f_sf_marshallOut,
    c8_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargout, 2U, c8_f_sf_marshallOut,
    c8_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_b_x, 3U, c8_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_b_P, 4U, c8_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_b_yMeas, 5U, c8_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_b_R, 6U, c8_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_c_blockOrdering, 7U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_b_xNew, 8U, c8_c_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_b_PNew, 9U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_d_blockOrdering, MAX_uint32_T,
    c8_sf_marshallOut, c8_sf_marshallIn);
  c8_b_pM = c8_r1;
  c8_d_blockOrdering = c8_c_blockOrdering;
  _SFD_SYMBOL_SWITCH(7U, 10U);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 2);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 3);
  CV_EML_IF(0, 1, 0, false);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 7);
  for (c8_i10 = 0; c8_i10 < 6; c8_i10++) {
    c8_b_xNew[c8_i10] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 8);
  for (c8_i11 = 0; c8_i11 < 36; c8_i11++) {
    c8_b_PNew[c8_i11] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 9);
  CV_EML_IF(0, 1, 1, false);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 18);
  CV_EML_IF(0, 1, 3, false);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 22);
  for (c8_i12 = 0; c8_i12 < 6; c8_i12++) {
    c8_c_xNew[c8_i12] = c8_b_x[c8_i12];
  }

  for (c8_i13 = 0; c8_i13 < 36; c8_i13++) {
    c8_c_PNew[c8_i13] = c8_b_P[c8_i13];
  }

  for (c8_i14 = 0; c8_i14 < 3; c8_i14++) {
    c8_c_yMeas[c8_i14] = c8_b_yMeas[c8_i14];
  }

  for (c8_i15 = 0; c8_i15 < 9; c8_i15++) {
    c8_c_R[c8_i15] = c8_b_R[c8_i15];
  }

  c8_b_EKFCorrectorNonAdditive_correct(chartInstance, c8_c_yMeas, c8_c_R,
    c8_c_xNew, c8_c_PNew);
  for (c8_i16 = 0; c8_i16 < 6; c8_i16++) {
    c8_b_xNew[c8_i16] = c8_c_xNew[c8_i16];
  }

  for (c8_i17 = 0; c8_i17 < 36; c8_i17++) {
    c8_b_PNew[c8_i17] = c8_c_PNew[c8_i17];
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, -22);
  _SFD_SYMBOL_SCOPE_POP();
  for (c8_i18 = 0; c8_i18 < 6; c8_i18++) {
    (*chartInstance->c8_xNew)[c8_i18] = c8_b_xNew[c8_i18];
  }

  for (c8_i19 = 0; c8_i19 < 36; c8_i19++) {
    (*chartInstance->c8_PNew)[c8_i19] = c8_b_PNew[c8_i19];
  }

  *chartInstance->c8_b_blockOrdering = c8_d_blockOrdering;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c8_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_sharedTrackingLibraryMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c8_i20 = 0; c8_i20 < 6; c8_i20++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c8_xNew)[c8_i20], 5U);
  }

  for (c8_i21 = 0; c8_i21 < 36; c8_i21++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c8_PNew)[c8_i21], 6U);
  }

  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c8_b_blockOrdering, 7U);
}

static void mdl_start_c8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void initSimStructsc8_sharedTrackingLibrary
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c8_measFcn1_invoke(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, real_T c8_b_x[6], real_T c8_v[3], real_T c8_y[3])
{
  _ssFcnCallExecArgInfo c8_args[3];
  c8_args[0U].dataPtr = (void *)c8_b_x;
  c8_args[1U].dataPtr = (void *)c8_v;
  c8_args[2U].dataPtr = (void *)c8_y;
  slcsInvokeSimulinkFunction(chartInstance->S, "measFcn1", &c8_args[0U]);
}

static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber, uint32_T c8_instanceNumber)
{
  (void)(c8_machineNumber);
  (void)(c8_chartNumber);
  (void)(c8_instanceNumber);
}

static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  boolean_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  c8_u = *(boolean_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static boolean_T c8_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_c_blockOrdering, const char_T *c8_identifier)
{
  boolean_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = (const char *)c8_identifier;
  c8_thisId.fParent = NULL;
  c8_thisId.bParentIsCell = false;
  c8_y = c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_c_blockOrdering),
    &c8_thisId);
  sf_mex_destroy(&c8_c_blockOrdering);
  return c8_y;
}

static boolean_T c8_b_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct *
  chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  boolean_T c8_y;
  boolean_T c8_b0;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_b0, 1, 11, 0U, 0, 0U, 0);
  c8_y = c8_b0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_c_blockOrdering;
  emlrtMsgIdentifier c8_thisId;
  boolean_T c8_y;
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_c_blockOrdering = sf_mex_dup(c8_mxArrayInData);
  c8_thisId.fIdentifier = (const char *)c8_varName;
  c8_thisId.fParent = NULL;
  c8_thisId.bParentIsCell = false;
  c8_y = c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_c_blockOrdering),
    &c8_thisId);
  sf_mex_destroy(&c8_c_blockOrdering);
  *(boolean_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  int32_T c8_i22;
  int32_T c8_i23;
  const mxArray *c8_y = NULL;
  int32_T c8_i24;
  real_T c8_u[36];
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  c8_i22 = 0;
  for (c8_i23 = 0; c8_i23 < 6; c8_i23++) {
    for (c8_i24 = 0; c8_i24 < 6; c8_i24++) {
      c8_u[c8_i24 + c8_i22] = (*(real_T (*)[36])c8_inData)[c8_i24 + c8_i22];
    }

    c8_i22 += 6;
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 6, 6), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static void c8_c_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_b_PNew, const char_T *c8_identifier, real_T
  c8_y[36])
{
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = (const char *)c8_identifier;
  c8_thisId.fParent = NULL;
  c8_thisId.bParentIsCell = false;
  c8_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_PNew), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_b_PNew);
}

static void c8_d_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[36])
{
  real_T c8_dv2[36];
  int32_T c8_i25;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv2, 1, 0, 0U, 1, 0U, 2, 6, 6);
  for (c8_i25 = 0; c8_i25 < 36; c8_i25++) {
    c8_y[c8_i25] = c8_dv2[c8_i25];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_b_PNew;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[36];
  int32_T c8_i26;
  int32_T c8_i27;
  int32_T c8_i28;
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_b_PNew = sf_mex_dup(c8_mxArrayInData);
  c8_thisId.fIdentifier = (const char *)c8_varName;
  c8_thisId.fParent = NULL;
  c8_thisId.bParentIsCell = false;
  c8_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_PNew), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_b_PNew);
  c8_i26 = 0;
  for (c8_i27 = 0; c8_i27 < 6; c8_i27++) {
    for (c8_i28 = 0; c8_i28 < 6; c8_i28++) {
      (*(real_T (*)[36])c8_outData)[c8_i28 + c8_i26] = c8_y[c8_i28 + c8_i26];
    }

    c8_i26 += 6;
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  int32_T c8_i29;
  const mxArray *c8_y = NULL;
  real_T c8_u[6];
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  for (c8_i29 = 0; c8_i29 < 6; c8_i29++) {
    c8_u[c8_i29] = (*(real_T (*)[6])c8_inData)[c8_i29];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static void c8_e_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_b_xNew, const char_T *c8_identifier, real_T
  c8_y[6])
{
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = (const char *)c8_identifier;
  c8_thisId.fParent = NULL;
  c8_thisId.bParentIsCell = false;
  c8_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_xNew), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_b_xNew);
}

static void c8_f_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  real_T c8_y[6])
{
  real_T c8_dv3[6];
  int32_T c8_i30;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv3, 1, 0, 0U, 1, 0U, 1, 6);
  for (c8_i30 = 0; c8_i30 < 6; c8_i30++) {
    c8_y[c8_i30] = c8_dv3[c8_i30];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_b_xNew;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[6];
  int32_T c8_i31;
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_b_xNew = sf_mex_dup(c8_mxArrayInData);
  c8_thisId.fIdentifier = (const char *)c8_varName;
  c8_thisId.fParent = NULL;
  c8_thisId.bParentIsCell = false;
  c8_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_xNew), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_b_xNew);
  for (c8_i31 = 0; c8_i31 < 6; c8_i31++) {
    (*(real_T (*)[6])c8_outData)[c8_i31] = c8_y[c8_i31];
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  int32_T c8_i32;
  int32_T c8_i33;
  const mxArray *c8_y = NULL;
  int32_T c8_i34;
  real_T c8_u[9];
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  c8_i32 = 0;
  for (c8_i33 = 0; c8_i33 < 3; c8_i33++) {
    for (c8_i34 = 0; c8_i34 < 3; c8_i34++) {
      c8_u[c8_i34 + c8_i32] = (*(real_T (*)[9])c8_inData)[c8_i34 + c8_i32];
    }

    c8_i32 += 3;
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static const mxArray *c8_e_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  int32_T c8_i35;
  const mxArray *c8_y = NULL;
  real_T c8_u[3];
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  for (c8_i35 = 0; c8_i35 < 3; c8_i35++) {
    c8_u[c8_i35] = (*(real_T (*)[3])c8_inData)[c8_i35];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static const mxArray *c8_f_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  real_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  c8_u = *(real_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static real_T c8_g_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  real_T c8_y;
  real_T c8_d0;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_d0, 1, 0, 0U, 0, 0U, 0);
  c8_y = c8_d0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_nargout;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y;
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_nargout = sf_mex_dup(c8_mxArrayInData);
  c8_thisId.fIdentifier = (const char *)c8_varName;
  c8_thisId.fParent = NULL;
  c8_thisId.bParentIsCell = false;
  c8_y = c8_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_nargout), &c8_thisId);
  sf_mex_destroy(&c8_nargout);
  *(real_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_g_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  c8_scGUHJGjGVqH0aOEVjksvlC c8_u;
  const mxArray *c8_y = NULL;
  int32_T c8_i36;
  const mxArray *c8_b_y = NULL;
  char_T c8_b_u[8];
  const mxArray *c8_c_y = NULL;
  boolean_T c8_c_u;
  const mxArray *c8_d_y = NULL;
  boolean_T c8_d_u;
  const mxArray *c8_e_y = NULL;
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  c8_u = *(c8_scGUHJGjGVqH0aOEVjksvlC *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  for (c8_i36 = 0; c8_i36 < 8; c8_i36++) {
    c8_b_u[c8_i36] = c8_u.FcnName[c8_i36];
  }

  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", c8_b_u, 10, 0U, 1U, 0U, 2, 1, 8),
                false);
  sf_mex_addfield(c8_y, c8_b_y, "FcnName", "FcnName", 0);
  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", NULL, 10, 0U, 1U, 0U, 2, 0, 0),
                false);
  sf_mex_addfield(c8_y, c8_c_y, "JacobianFcnName", "JacobianFcnName", 0);
  c8_c_u = c8_u.HasJacobian;
  c8_d_y = NULL;
  sf_mex_assign(&c8_d_y, sf_mex_create("y", &c8_c_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c8_y, c8_d_y, "HasJacobian", "HasJacobian", 0);
  c8_d_u = c8_u.HasAdditiveNoise;
  c8_e_y = NULL;
  sf_mex_assign(&c8_e_y, sf_mex_create("y", &c8_d_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c8_y, c8_e_y, "HasAdditiveNoise", "HasAdditiveNoise", 0);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

const mxArray *sf_c8_sharedTrackingLibrary_get_eml_resolved_functions_info(void)
{
  const mxArray *c8_nameCaptureInfo = NULL;
  c8_nameCaptureInfo = NULL;
  sf_mex_assign(&c8_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c8_nameCaptureInfo;
}

static void c8_EKFCorrectorNonAdditive_correct
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance, real_T c8_z[3],
   real_T c8_zcov[9], real_T c8_b_x[6], real_T c8_b_P[36], real_T c8_c_x[6],
   real_T c8_c_P[36])
{
  int32_T c8_i37;
  int32_T c8_i38;
  int32_T c8_i39;
  int32_T c8_i40;
  real_T c8_b_z[3];
  real_T c8_b_zcov[9];
  for (c8_i37 = 0; c8_i37 < 6; c8_i37++) {
    c8_c_x[c8_i37] = c8_b_x[c8_i37];
  }

  for (c8_i38 = 0; c8_i38 < 36; c8_i38++) {
    c8_c_P[c8_i38] = c8_b_P[c8_i38];
  }

  for (c8_i39 = 0; c8_i39 < 3; c8_i39++) {
    c8_b_z[c8_i39] = c8_z[c8_i39];
  }

  for (c8_i40 = 0; c8_i40 < 9; c8_i40++) {
    c8_b_zcov[c8_i40] = c8_zcov[c8_i40];
  }

  c8_b_EKFCorrectorNonAdditive_correct(chartInstance, c8_b_z, c8_b_zcov, c8_c_x,
    c8_c_P);
}

static void c8_warning(SFc8_sharedTrackingLibraryInstanceStruct *chartInstance)
{
  const mxArray *c8_y = NULL;
  static char_T c8_cv0[7] = { 'w', 'a', 'r', 'n', 'i', 'n', 'g' };

  const mxArray *c8_b_y = NULL;
  static char_T c8_cv1[7] = { 'm', 'e', 's', 's', 'a', 'g', 'e' };

  const mxArray *c8_c_y = NULL;
  static char_T c8_msgID[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a', 't',
    'r', 'i', 'x' };

  (void)chartInstance;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_cv0, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", c8_cv1, 10, 0U, 1U, 0U, 2, 1, 7),
                false);
  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", c8_msgID, 10, 0U, 1U, 0U, 2, 1, 27),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 0U, 2U, 14, c8_y, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "feval", 1U,
    2U, 14, c8_b_y, 14, c8_c_y));
}

static const mxArray *c8_h_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  int32_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  c8_u = *(int32_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static int32_T c8_h_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int32_T c8_y;
  int32_T c8_i41;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_i41, 1, 6, 0U, 0, 0U, 0);
  c8_y = c8_i41;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_b_sfEvent;
  emlrtMsgIdentifier c8_thisId;
  int32_T c8_y;
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_b_sfEvent = sf_mex_dup(c8_mxArrayInData);
  c8_thisId.fIdentifier = (const char *)c8_varName;
  c8_thisId.fParent = NULL;
  c8_thisId.bParentIsCell = false;
  c8_y = c8_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_sfEvent),
    &c8_thisId);
  sf_mex_destroy(&c8_b_sfEvent);
  *(int32_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static c8_scGUHJGjGVqH0aOEVjksvlC c8_i_emlrt_marshallIn
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance, const mxArray *c8_u,
   const emlrtMsgIdentifier *c8_parentId)
{
  c8_scGUHJGjGVqH0aOEVjksvlC c8_y;
  emlrtMsgIdentifier c8_thisId;
  static const char * c8_fieldNames[4] = { "FcnName", "JacobianFcnName",
    "HasJacobian", "HasAdditiveNoise" };

  c8_thisId.fParent = c8_parentId;
  c8_thisId.bParentIsCell = false;
  sf_mex_check_struct(c8_parentId, c8_u, 4, c8_fieldNames, 0U, NULL);
  c8_thisId.fIdentifier = "FcnName";
  c8_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c8_u,
    "FcnName", "FcnName", 0)), &c8_thisId, c8_y.FcnName);
  c8_thisId.fIdentifier = "JacobianFcnName";
  c8_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c8_u,
    "JacobianFcnName", "JacobianFcnName", 0)), &c8_thisId);
  c8_thisId.fIdentifier = "HasJacobian";
  c8_y.HasJacobian = c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c8_u, "HasJacobian", "HasJacobian", 0)), &c8_thisId);
  c8_thisId.fIdentifier = "HasAdditiveNoise";
  c8_y.HasAdditiveNoise = c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c8_u, "HasAdditiveNoise", "HasAdditiveNoise", 0)),
    &c8_thisId);
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_j_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId,
  char_T c8_y[8])
{
  char_T c8_cv2[8];
  int32_T c8_i42;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_cv2, 1, 10, 0U, 1, 0U, 2, 1, 8);
  for (c8_i42 = 0; c8_i42 < 8; c8_i42++) {
    c8_y[c8_i42] = c8_cv2[c8_i42];
  }

  sf_mex_destroy(&c8_u);
}

static void c8_k_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), NULL, 1, 10, 0U, 1, 0U, 2, 0, 0);
  sf_mex_destroy(&c8_u);
}

static void c8_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_b_pM;
  emlrtMsgIdentifier c8_thisId;
  c8_scGUHJGjGVqH0aOEVjksvlC c8_y;
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)chartInstanceVoid;
  c8_b_pM = sf_mex_dup(c8_mxArrayInData);
  c8_thisId.fIdentifier = (const char *)c8_varName;
  c8_thisId.fParent = NULL;
  c8_thisId.bParentIsCell = false;
  c8_y = c8_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_pM), &c8_thisId);
  sf_mex_destroy(&c8_b_pM);
  *(c8_scGUHJGjGVqH0aOEVjksvlC *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static uint8_T c8_l_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_b_is_active_c8_sharedTrackingLibrary, const
  char_T *c8_identifier)
{
  uint8_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = (const char *)c8_identifier;
  c8_thisId.fParent = NULL;
  c8_thisId.bParentIsCell = false;
  c8_y = c8_m_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c8_b_is_active_c8_sharedTrackingLibrary), &c8_thisId);
  sf_mex_destroy(&c8_b_is_active_c8_sharedTrackingLibrary);
  return c8_y;
}

static uint8_T c8_m_emlrt_marshallIn(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  uint8_T c8_u0;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_u0, 1, 3, 0U, 0, 0U, 0);
  c8_y = c8_u0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_b_EKFCorrectorNonAdditive_correct
  (SFc8_sharedTrackingLibraryInstanceStruct *chartInstance, real_T c8_z[3],
   real_T c8_zcov[9], real_T c8_b_x[6], real_T c8_b_P[36])
{
  int32_T c8_i43;
  c8_cell_2 c8_vec;
  int32_T c8_i44;
  int32_T c8_i45;
  real_T c8_c_x[6];
  real_T c8_b_vec[3];
  real_T c8_b_z[3];
  int32_T c8_j;
  int32_T c8_i46;
  int32_T c8_i47;
  c8_cell_2 c8_c_vec;
  real_T c8_imvec[6];
  int32_T c8_i48;
  real_T c8_maxval;
  int32_T c8_i49;
  real_T c8_d_x[6];
  int32_T c8_i50;
  real_T c8_d_vec[3];
  real_T c8_e_vec[3];
  real_T c8_imz[3];
  int32_T c8_b_j;
  int32_T c8_i51;
  int32_T c8_i52;
  int32_T c8_i53;
  int32_T c8_i54;
  real_T c8_dHdx[18];
  int32_T c8_i55;
  int32_T c8_i56;
  real_T c8_b_imvec[3];
  int32_T c8_i57;
  real_T c8_b_maxval;
  int32_T c8_i58;
  int32_T c8_i59;
  int32_T c8_i60;
  real_T c8_Pxy[18];
  int32_T c8_i61;
  int32_T c8_i62;
  int32_T c8_i63;
  int32_T c8_i64;
  int32_T c8_i65;
  int32_T c8_i66;
  int32_T c8_i67;
  int32_T c8_i68;
  real_T c8_e_x[6];
  real_T c8_b_dHdx[18];
  int32_T c8_i69;
  int32_T c8_i70;
  int32_T c8_i71;
  int32_T c8_i72;
  int32_T c8_i73;
  int32_T c8_i74;
  real_T c8_dHdv[9];
  int32_T c8_i75;
  int32_T c8_i76;
  int32_T c8_i77;
  int32_T c8_i78;
  int32_T c8_i79;
  real_T c8_b_dHdv[9];
  int32_T c8_i80;
  int32_T c8_i81;
  real_T c8_c_dHdx[9];
  int32_T c8_i82;
  int32_T c8_i83;
  int32_T c8_i84;
  real_T c8_c_dHdv[9];
  int32_T c8_i85;
  int32_T c8_i86;
  int32_T c8_i87;
  real_T c8_Pyy[9];
  int32_T c8_i88;
  real_T c8_f_x[6];
  real_T c8_dv4[3];
  int32_T c8_r1;
  int32_T c8_r2;
  int32_T c8_r3;
  real_T c8_c_maxval;
  real_T c8_a21;
  int32_T c8_rtemp;
  int32_T c8_k;
  int32_T c8_i89;
  real_T c8_gain[18];
  int32_T c8_i90;
  real_T c8_c_z[3];
  int32_T c8_i91;
  real_T c8_d1;
  int32_T c8_i92;
  int32_T c8_i93;
  int32_T c8_i94;
  int32_T c8_i95;
  int32_T c8_i96;
  int32_T c8_i97;
  int32_T c8_i98;
  int32_T c8_i99;
  int32_T c8_i100;
  int32_T c8_i101;
  real_T c8_b_gain[36];
  int32_T c8_i102;
  int32_T c8_i103;
  real_T c8_d2;
  int32_T c8_i104;
  int32_T c8_i105;
  int32_T c8_i106;
  real_T c8_c_P[36];
  for (c8_i43 = 0; c8_i43 < 3; c8_i43++) {
    c8_vec.f2[c8_i43] = 0.0;
  }

  CV_EML_FCN(0, 6);
  for (c8_i44 = 0; c8_i44 < 6; c8_i44++) {
    c8_c_x[c8_i44] = c8_b_x[c8_i44];
  }

  for (c8_i45 = 0; c8_i45 < 3; c8_i45++) {
    c8_b_vec[c8_i45] = c8_vec.f2[c8_i45];
  }

  c8_measFcn1_invoke(chartInstance, c8_c_x, c8_b_vec, c8_b_z);
  for (c8_j = 0; c8_j < 6; c8_j++) {
    for (c8_i47 = 0; c8_i47 < 6; c8_i47++) {
      c8_imvec[c8_i47] = c8_b_x[c8_i47];
    }

    (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 0, 0, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 0U, 0U, 1.0 + (real_T)c8_j), 1, 6);
    c8_maxval = muDoubleScalarMax(1.4901161193847656E-8, 1.4901161193847656E-8 *
      muDoubleScalarAbs(c8_b_x[c8_j]));
    c8_imvec[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 0, 0, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 0U, 0U, 1.0 + (real_T)c8_j), 1, 6) - 1] =
      c8_b_x[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 0, 0, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 0U, 0U, 1.0 + (real_T)c8_j), 1, 6) - 1] + c8_maxval;
    CV_EML_FCN(0, 6);
    for (c8_i50 = 0; c8_i50 < 3; c8_i50++) {
      c8_e_vec[c8_i50] = c8_vec.f2[c8_i50];
    }

    c8_measFcn1_invoke(chartInstance, c8_imvec, c8_e_vec, c8_imz);
    c8_i51 = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 0, 0, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 0U, 0U, 1.0 + (real_T)c8_j), 1, 6) - 1;
    for (c8_i52 = 0; c8_i52 < 3; c8_i52++) {
      c8_dHdx[c8_i52 + 3 * c8_i51] = (c8_imz[c8_i52] - c8_b_z[c8_i52]) /
        c8_maxval;
    }
  }

  for (c8_i46 = 0; c8_i46 < 3; c8_i46++) {
    c8_c_vec.f2[c8_i46] = 0.0;
  }

  CV_EML_FCN(0, 6);
  for (c8_i48 = 0; c8_i48 < 6; c8_i48++) {
    c8_d_x[c8_i48] = c8_b_x[c8_i48];
  }

  for (c8_i49 = 0; c8_i49 < 3; c8_i49++) {
    c8_d_vec[c8_i49] = c8_c_vec.f2[c8_i49];
  }

  c8_measFcn1_invoke(chartInstance, c8_d_x, c8_d_vec, c8_b_z);
  for (c8_b_j = 0; c8_b_j < 3; c8_b_j++) {
    for (c8_i54 = 0; c8_i54 < 3; c8_i54++) {
      c8_b_imvec[c8_i54] = c8_c_vec.f2[c8_i54];
    }

    (real_T)sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 0, 0, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 0U, 0U, 1.0 + (real_T)c8_b_j), 1, 3);
    c8_b_maxval = muDoubleScalarMax(1.4901161193847656E-8, 1.4901161193847656E-8
      * muDoubleScalarAbs(c8_c_vec.f2[c8_b_j]));
    c8_b_imvec[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 0, 0, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 0U, 0U, 1.0 + (real_T)c8_b_j), 1, 3) - 1] =
      c8_c_vec.f2[sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 0, 0, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 0U, 0U, 1.0 + (real_T)c8_b_j), 1, 3) - 1] +
      c8_b_maxval;
    CV_EML_FCN(0, 6);
    for (c8_i61 = 0; c8_i61 < 6; c8_i61++) {
      c8_e_x[c8_i61] = c8_b_x[c8_i61];
    }

    c8_measFcn1_invoke(chartInstance, c8_e_x, c8_b_imvec, c8_imz);
    c8_i69 = sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 0, 0, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 0U, 0U, 1.0 + (real_T)c8_b_j), 1, 3) - 1;
    for (c8_i73 = 0; c8_i73 < 3; c8_i73++) {
      c8_b_dHdv[c8_i73 + 3 * c8_i69] = (c8_imz[c8_i73] - c8_b_z[c8_i73]) /
        c8_b_maxval;
    }
  }

  for (c8_i53 = 0; c8_i53 < 6; c8_i53++) {
    c8_i56 = 0;
    for (c8_i57 = 0; c8_i57 < 3; c8_i57++) {
      c8_Pxy[c8_i56 + c8_i53] = 0.0;
      c8_i63 = 0;
      c8_i66 = 0;
      for (c8_i68 = 0; c8_i68 < 6; c8_i68++) {
        c8_Pxy[c8_i56 + c8_i53] += c8_b_P[c8_i63 + c8_i53] * c8_dHdx[c8_i66 +
          c8_i57];
        c8_i63 += 6;
        c8_i66 += 3;
      }

      c8_i56 += 6;
    }
  }

  for (c8_i55 = 0; c8_i55 < 3; c8_i55++) {
    c8_i59 = 0;
    c8_i60 = 0;
    for (c8_i62 = 0; c8_i62 < 6; c8_i62++) {
      c8_b_dHdx[c8_i59 + c8_i55] = 0.0;
      c8_i72 = 0;
      for (c8_i75 = 0; c8_i75 < 6; c8_i75++) {
        c8_b_dHdx[c8_i59 + c8_i55] += c8_dHdx[c8_i72 + c8_i55] * c8_b_P[c8_i75 +
          c8_i60];
        c8_i72 += 3;
      }

      c8_i59 += 3;
      c8_i60 += 6;
    }
  }

  for (c8_i58 = 0; c8_i58 < 3; c8_i58++) {
    c8_i65 = 0;
    for (c8_i67 = 0; c8_i67 < 3; c8_i67++) {
      c8_dHdv[c8_i65 + c8_i58] = 0.0;
      c8_i76 = 0;
      for (c8_i79 = 0; c8_i79 < 3; c8_i79++) {
        c8_dHdv[c8_i65 + c8_i58] += c8_b_dHdv[c8_i76 + c8_i58] * c8_zcov[c8_i79
          + c8_i65];
        c8_i76 += 3;
      }

      c8_i65 += 3;
    }
  }

  for (c8_i64 = 0; c8_i64 < 3; c8_i64++) {
    c8_i71 = 0;
    for (c8_i74 = 0; c8_i74 < 3; c8_i74++) {
      c8_c_dHdx[c8_i71 + c8_i64] = 0.0;
      c8_i82 = 0;
      for (c8_i83 = 0; c8_i83 < 6; c8_i83++) {
        c8_c_dHdx[c8_i71 + c8_i64] += c8_b_dHdx[c8_i82 + c8_i64] *
          c8_dHdx[c8_i82 + c8_i74];
        c8_i82 += 3;
      }

      c8_i71 += 3;
    }
  }

  for (c8_i70 = 0; c8_i70 < 3; c8_i70++) {
    c8_i78 = 0;
    for (c8_i81 = 0; c8_i81 < 3; c8_i81++) {
      c8_c_dHdv[c8_i78 + c8_i70] = 0.0;
      c8_i86 = 0;
      for (c8_i87 = 0; c8_i87 < 3; c8_i87++) {
        c8_c_dHdv[c8_i78 + c8_i70] += c8_dHdv[c8_i86 + c8_i70] *
          c8_b_dHdv[c8_i86 + c8_i81];
        c8_i86 += 3;
      }

      c8_i78 += 3;
    }
  }

  c8_i77 = 0;
  for (c8_i80 = 0; c8_i80 < 3; c8_i80++) {
    for (c8_i84 = 0; c8_i84 < 3; c8_i84++) {
      c8_Pyy[c8_i84 + c8_i77] = c8_c_dHdx[c8_i84 + c8_i77] + c8_c_dHdv[c8_i84 +
        c8_i77];
    }

    c8_i77 += 3;
  }

  CV_EML_FCN(0, 6);
  for (c8_i85 = 0; c8_i85 < 6; c8_i85++) {
    c8_f_x[c8_i85] = c8_b_x[c8_i85];
  }

  for (c8_i88 = 0; c8_i88 < 3; c8_i88++) {
    c8_dv4[c8_i88] = 0.0;
  }

  c8_measFcn1_invoke(chartInstance, c8_f_x, c8_dv4, c8_b_z);
  c8_r1 = 0;
  c8_r2 = 1;
  c8_r3 = 2;
  c8_c_maxval = muDoubleScalarAbs(c8_Pyy[0]) + muDoubleScalarAbs(0.0);
  c8_a21 = muDoubleScalarAbs(c8_Pyy[1]) + muDoubleScalarAbs(0.0);
  if (c8_a21 > c8_c_maxval) {
    c8_c_maxval = c8_a21;
    c8_r1 = 1;
    c8_r2 = 0;
  }

  if (muDoubleScalarAbs(c8_Pyy[2]) + muDoubleScalarAbs(0.0) > c8_c_maxval) {
    c8_r1 = 2;
    c8_r2 = 1;
    c8_r3 = 0;
  }

  c8_Pyy[c8_r2] /= c8_Pyy[c8_r1];
  c8_Pyy[c8_r3] /= c8_Pyy[c8_r1];
  c8_Pyy[3 + c8_r2] -= c8_Pyy[c8_r2] * c8_Pyy[3 + c8_r1];
  c8_Pyy[3 + c8_r3] -= c8_Pyy[c8_r3] * c8_Pyy[3 + c8_r1];
  c8_Pyy[6 + c8_r2] -= c8_Pyy[c8_r2] * c8_Pyy[6 + c8_r1];
  c8_Pyy[6 + c8_r3] -= c8_Pyy[c8_r3] * c8_Pyy[6 + c8_r1];
  if (muDoubleScalarAbs(c8_Pyy[3 + c8_r3]) + muDoubleScalarAbs(0.0) >
      muDoubleScalarAbs(c8_Pyy[3 + c8_r2]) + muDoubleScalarAbs(0.0)) {
    c8_rtemp = c8_r2 + 1;
    c8_r2 = c8_r3;
    c8_r3 = c8_rtemp - 1;
  }

  c8_Pyy[3 + c8_r3] /= c8_Pyy[3 + c8_r2];
  c8_Pyy[6 + c8_r3] -= c8_Pyy[3 + c8_r3] * c8_Pyy[6 + c8_r2];
  if ((c8_Pyy[c8_r1] == 0.0) || (c8_Pyy[3 + c8_r2] == 0.0) || (c8_Pyy[6 + c8_r3]
       == 0.0)) {
    c8_warning(chartInstance);
  }

  for (c8_k = 0; c8_k < 6; c8_k++) {
    c8_gain[c8_k + 6 * c8_r1] = c8_Pxy[c8_k] / c8_Pyy[c8_r1];
    c8_gain[c8_k + 6 * c8_r2] = c8_Pxy[6 + c8_k] - c8_gain[c8_k + 6 * c8_r1] *
      c8_Pyy[3 + c8_r1];
    c8_gain[c8_k + 6 * c8_r3] = c8_Pxy[12 + c8_k] - c8_gain[c8_k + 6 * c8_r1] *
      c8_Pyy[6 + c8_r1];
    c8_gain[c8_k + 6 * c8_r2] /= c8_Pyy[3 + c8_r2];
    c8_gain[c8_k + 6 * c8_r3] -= c8_gain[c8_k + 6 * c8_r2] * c8_Pyy[6 + c8_r2];
    c8_gain[c8_k + 6 * c8_r3] /= c8_Pyy[6 + c8_r3];
    c8_gain[c8_k + 6 * c8_r2] -= c8_gain[c8_k + 6 * c8_r3] * c8_Pyy[3 + c8_r3];
    c8_gain[c8_k + 6 * c8_r1] -= c8_gain[c8_k + 6 * c8_r3] * c8_Pyy[c8_r3];
    c8_gain[c8_k + 6 * c8_r1] -= c8_gain[c8_k + 6 * c8_r2] * c8_Pyy[c8_r2];
  }

  for (c8_i89 = 0; c8_i89 < 3; c8_i89++) {
    c8_c_z[c8_i89] = c8_z[c8_i89] - c8_b_z[c8_i89];
  }

  for (c8_i90 = 0; c8_i90 < 6; c8_i90++) {
    c8_d1 = 0.0;
    c8_i92 = 0;
    for (c8_i93 = 0; c8_i93 < 3; c8_i93++) {
      c8_d1 += c8_gain[c8_i92 + c8_i90] * c8_c_z[c8_i93];
      c8_i92 += 6;
    }

    c8_b_x[c8_i90] += c8_d1;
  }

  for (c8_i91 = 0; c8_i91 < 6; c8_i91++) {
    c8_i95 = 0;
    c8_i96 = 0;
    for (c8_i97 = 0; c8_i97 < 6; c8_i97++) {
      c8_b_gain[c8_i95 + c8_i91] = 0.0;
      c8_i102 = 0;
      for (c8_i104 = 0; c8_i104 < 3; c8_i104++) {
        c8_b_gain[c8_i95 + c8_i91] += c8_gain[c8_i102 + c8_i91] *
          c8_dHdx[c8_i104 + c8_i96];
        c8_i102 += 6;
      }

      c8_i95 += 6;
      c8_i96 += 3;
    }
  }

  for (c8_i94 = 0; c8_i94 < 6; c8_i94++) {
    c8_i99 = 0;
    for (c8_i101 = 0; c8_i101 < 6; c8_i101++) {
      c8_d2 = 0.0;
      c8_i105 = 0;
      for (c8_i106 = 0; c8_i106 < 6; c8_i106++) {
        c8_d2 += c8_b_gain[c8_i105 + c8_i94] * c8_b_P[c8_i106 + c8_i99];
        c8_i105 += 6;
      }

      c8_c_P[c8_i99 + c8_i94] = c8_b_P[c8_i99 + c8_i94] - c8_d2;
      c8_i99 += 6;
    }
  }

  c8_i98 = 0;
  for (c8_i100 = 0; c8_i100 < 6; c8_i100++) {
    for (c8_i103 = 0; c8_i103 < 6; c8_i103++) {
      c8_b_P[c8_i103 + c8_i98] = c8_c_P[c8_i103 + c8_i98];
    }

    c8_i98 += 6;
  }
}

static void init_dsm_address_info(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc8_sharedTrackingLibraryInstanceStruct
  *chartInstance)
{
  chartInstance->c8_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c8_x = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c8_xNew = (real_T (*)[6])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c8_P = (real_T (*)[36])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c8_PNew = (real_T (*)[36])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c8_yMeas = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c8_R = (real_T (*)[9])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c8_blockOrdering = (boolean_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c8_b_blockOrdering = (boolean_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
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

void sf_c8_sharedTrackingLibrary_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2653185389U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3698185745U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3657896002U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2448035453U);
}

mxArray* sf_c8_sharedTrackingLibrary_get_post_codegen_info(void);
mxArray *sf_c8_sharedTrackingLibrary_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("B16ANhpKlcG56Iy9VhIrOH");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

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
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(6);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

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
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(6);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo =
      sf_c8_sharedTrackingLibrary_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c8_sharedTrackingLibrary_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c8_sharedTrackingLibrary_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("client_server");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("measFcn1");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c8_sharedTrackingLibrary_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c8_sharedTrackingLibrary_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString(
      "KweCzxtQnmlHxuV2hsqQF");
    mwSize exp_dims[2] = { 1, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);

    {
      mxArray* mxFcnName = mxCreateString("measFcn1");
      mxSetCell(mxExportedFunctionsUsedByThisChart, 0, mxFcnName);
    }

    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c8_sharedTrackingLibrary(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[8],T\"PNew\",},{M[1],M[21],T\"blockOrdering\",},{M[1],M[5],T\"xNew\",},{M[8],M[0],T\"is_active_c8_sharedTrackingLibrary\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c8_sharedTrackingLibrary_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc8_sharedTrackingLibraryInstanceStruct *chartInstance =
      (SFc8_sharedTrackingLibraryInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _sharedTrackingLibraryMachineNumber_,
           8,
           1,
           1,
           0,
           9,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_sharedTrackingLibraryMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_sharedTrackingLibraryMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _sharedTrackingLibraryMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"x");
          _SFD_SET_DATA_PROPS(1,1,1,0,"P");
          _SFD_SET_DATA_PROPS(2,1,1,0,"yMeas");
          _SFD_SET_DATA_PROPS(3,1,1,0,"R");
          _SFD_SET_DATA_PROPS(4,1,1,0,"blockOrdering");
          _SFD_SET_DATA_PROPS(5,2,0,1,"xNew");
          _SFD_SET_DATA_PROPS(6,2,0,1,"PNew");
          _SFD_SET_DATA_PROPS(7,2,0,1,"blockOrdering");
          _SFD_SET_DATA_PROPS(8,10,0,0,"pM");
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
        _SFD_CV_INIT_EML(0,1,7,0,4,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1033);
        _SFD_CV_INIT_EML_FCN(0,1,"",437,-1,460);
        _SFD_CV_INIT_EML_FCN(0,2,"",461,-1,492);
        _SFD_CV_INIT_EML_FCN(0,3,"",614,-1,637);
        _SFD_CV_INIT_EML_FCN(0,4,"",791,-1,820);
        _SFD_CV_INIT_EML_FCN(0,5,"",821,-1,858);
        _SFD_CV_INIT_EML_FCN(0,6,"",983,-1,1012);
        _SFD_CV_INIT_EML_IF(0,1,0,123,140,-1,216);
        _SFD_CV_INIT_EML_IF(0,1,1,282,304,651,1029);
        _SFD_CV_INIT_EML_IF(0,1,2,309,326,499,650);
        _SFD_CV_INIT_EML_IF(0,1,3,660,677,865,1025);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6U;
          dimVector[1]= 6U;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6U;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_c_sf_marshallOut,(MexInFcnForType)
            c8_c_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6U;
          dimVector[1]= 6U;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)
            c8_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)c8_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c8_g_sf_marshallOut,(MexInFcnForType)c8_f_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _sharedTrackingLibraryMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc8_sharedTrackingLibraryInstanceStruct *chartInstance =
      (SFc8_sharedTrackingLibraryInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c8_x);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c8_xNew);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c8_P);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c8_PNew);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c8_yMeas);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c8_R);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c8_blockOrdering);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)&chartInstance->c8_pM);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)chartInstance->c8_b_blockOrdering);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sFGfHySsRhJiu4dYdumhD8F";
}

static void sf_opaque_initialize_c8_sharedTrackingLibrary(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc8_sharedTrackingLibraryInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c8_sharedTrackingLibrary
    ((SFc8_sharedTrackingLibraryInstanceStruct*) chartInstanceVar);
  initialize_c8_sharedTrackingLibrary((SFc8_sharedTrackingLibraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c8_sharedTrackingLibrary(void *chartInstanceVar)
{
  enable_c8_sharedTrackingLibrary((SFc8_sharedTrackingLibraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c8_sharedTrackingLibrary(void *chartInstanceVar)
{
  disable_c8_sharedTrackingLibrary((SFc8_sharedTrackingLibraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c8_sharedTrackingLibrary(void *chartInstanceVar)
{
  sf_gateway_c8_sharedTrackingLibrary((SFc8_sharedTrackingLibraryInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c8_sharedTrackingLibrary(SimStruct*
  S)
{
  return get_sim_state_c8_sharedTrackingLibrary
    ((SFc8_sharedTrackingLibraryInstanceStruct *)sf_get_chart_instance_ptr(S));/* raw sim ctx */
}

static void sf_opaque_set_sim_state_c8_sharedTrackingLibrary(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c8_sharedTrackingLibrary
    ((SFc8_sharedTrackingLibraryInstanceStruct*)sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c8_sharedTrackingLibrary(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc8_sharedTrackingLibraryInstanceStruct*) chartInstanceVar)
      ->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_sharedTrackingLibrary_optimization_info();
    }

    finalize_c8_sharedTrackingLibrary((SFc8_sharedTrackingLibraryInstanceStruct*)
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
  initSimStructsc8_sharedTrackingLibrary
    ((SFc8_sharedTrackingLibraryInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c8_sharedTrackingLibrary(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c8_sharedTrackingLibrary
      ((SFc8_sharedTrackingLibraryInstanceStruct*)sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c8_sharedTrackingLibrary(SimStruct *S)
{
  /* Actual parameters from chart:
     pM
   */
  const char_T *rtParamNames[] = { "pM" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* Set overwritable ports for inplace optimization */
  ssSetInputPortOverWritable(S, 4, 1);
  ssSetOutputPortOverwritesInputPort(S, 3, 4);
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetInputPortDirectFeedThrough(S, 3, 1);
  ssSetInputPortDirectFeedThrough(S, 4, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_sharedTrackingLibrary_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,8);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,8,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 8);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,8);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,8,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,8,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,8);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(439571104U));
  ssSetChecksum1(S,(41976316U));
  ssSetChecksum2(S,(4051230688U));
  ssSetChecksum3(S,(559754404U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,0);
}

static void mdlRTW_c8_sharedTrackingLibrary(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c8_sharedTrackingLibrary(SimStruct *S)
{
  SFc8_sharedTrackingLibraryInstanceStruct *chartInstance;
  chartInstance = (SFc8_sharedTrackingLibraryInstanceStruct *)utMalloc(sizeof
    (SFc8_sharedTrackingLibraryInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc8_sharedTrackingLibraryInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  if (ssGetSampleTime(S, 0) == CONTINUOUS_SAMPLE_TIME && ssGetOffsetTime(S, 0) ==
      0 && ssGetNumContStates(ssGetRootSS(S)) > 0) {
    sf_error_out_about_continuous_sample_time_with_persistent_vars(S);
  }

  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c8_sharedTrackingLibrary;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c8_sharedTrackingLibrary;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c8_sharedTrackingLibrary;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c8_sharedTrackingLibrary;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c8_sharedTrackingLibrary;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c8_sharedTrackingLibrary;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c8_sharedTrackingLibrary;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c8_sharedTrackingLibrary;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c8_sharedTrackingLibrary;
  chartInstance->chartInfo.mdlStart = mdlStart_c8_sharedTrackingLibrary;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c8_sharedTrackingLibrary;
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
  mdl_start_c8_sharedTrackingLibrary(chartInstance);
}

void c8_sharedTrackingLibrary_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c8_sharedTrackingLibrary(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c8_sharedTrackingLibrary(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c8_sharedTrackingLibrary(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c8_sharedTrackingLibrary_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
