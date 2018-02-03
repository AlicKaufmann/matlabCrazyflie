#ifndef __c8_sharedTrackingLibrary_h__
#define __c8_sharedTrackingLibrary_h__

/* Type Definitions */
#ifndef typedef_c8_cell_2
#define typedef_c8_cell_2

typedef struct {
  real_T f1[6];
  real_T f2[3];
} c8_cell_2;

#endif                                 /*typedef_c8_cell_2*/

#ifndef struct_tag_scGUHJGjGVqH0aOEVjksvlC
#define struct_tag_scGUHJGjGVqH0aOEVjksvlC

struct tag_scGUHJGjGVqH0aOEVjksvlC
{
  char_T FcnName[8];
  boolean_T HasJacobian;
  boolean_T HasAdditiveNoise;
};

#endif                                 /*struct_tag_scGUHJGjGVqH0aOEVjksvlC*/

#ifndef typedef_c8_scGUHJGjGVqH0aOEVjksvlC
#define typedef_c8_scGUHJGjGVqH0aOEVjksvlC

typedef struct tag_scGUHJGjGVqH0aOEVjksvlC c8_scGUHJGjGVqH0aOEVjksvlC;

#endif                                 /*typedef_c8_scGUHJGjGVqH0aOEVjksvlC*/

#ifndef typedef_SFc8_sharedTrackingLibraryInstanceStruct
#define typedef_SFc8_sharedTrackingLibraryInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c8_sfEvent;
  boolean_T c8_doneDoubleBufferReInit;
  uint8_T c8_is_active_c8_sharedTrackingLibrary;
  c8_scGUHJGjGVqH0aOEVjksvlC c8_pM;
  void *c8_fEmlrtCtx;
  real_T (*c8_x)[6];
  real_T (*c8_xNew)[6];
  real_T (*c8_P)[36];
  real_T (*c8_PNew)[36];
  real_T (*c8_yMeas)[3];
  real_T (*c8_R)[9];
  boolean_T *c8_blockOrdering;
  boolean_T *c8_b_blockOrdering;
} SFc8_sharedTrackingLibraryInstanceStruct;

#endif                                 /*typedef_SFc8_sharedTrackingLibraryInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c8_sharedTrackingLibrary_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c8_sharedTrackingLibrary_get_check_sum(mxArray *plhs[]);
extern void c8_sharedTrackingLibrary_method_dispatcher(SimStruct *S, int_T
  method, void *data);

#endif
